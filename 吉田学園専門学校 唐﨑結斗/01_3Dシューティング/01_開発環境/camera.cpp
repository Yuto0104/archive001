//**************************************************************************************************
//
// カメラ処理(camera.h)
// Auther：唐�ｱ結斗
// 概要 : カメラの設定処理
//
//**************************************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "camera.h"
#include "camera_manager.h"
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "mouse.h"
#include "keyboard.h"
#include "move.h"
#include "calculation.h"
#include "motion_player3D.h"
#include "game.h"

//*****************************************************************************
// 定数定義
//*****************************************************************************
const float CCamera::CAMERA_NEAR = (10.0f);				// ニア
const float CCamera::CAMERA_FUR = (100000.0f);			// ファー

//=============================================================================
// コンストラクタ
// Author : 唐�ｱ結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CCamera::CCamera()
{
	m_pMotion = nullptr;							// カメラのモーション情報
	m_pRoll = nullptr;								// 移動クラスのインスタンス(角度)
	m_mtxWorld = {};								// ワールドマトリックス
	m_mtxProj = {};									// プロジェクションマトリックス
	m_mtxView = {};									// ビューマトリックス
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 視点
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 注視点
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 上方向ベクトル
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向き
	m_rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動方向
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 視点の目的の位置
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 注視点の目的の位置
	m_viewType = TYPE_CLAIRVOYANCE;					// 投影の種別
	m_fDistance = 0.0f;								// 視点から注視点までの距離
	m_fRotMove = 0.0f;								// 移動方向
	m_nCntFrame = 0;								// フレームカウント
	m_nCntKey = 0;									// キーカウント
	m_nNumMotion = 0;								// モーションカウント
	m_nMaxMotion = 0;								// モーションの最大数
	m_bAutoMove = false;							// 自動移動
	m_bAction = false;								// アクションを行うか否か
}

//=============================================================================
// デストラクタ
// Author : 唐�ｱ結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CCamera::~CCamera()
{

}

//=============================================================================
// 初期化
// Author : 唐�ｱ結斗
// 概要 : 視点と注視点の間の距離を算出する
//=============================================================================
HRESULT CCamera::Init()
{
	m_pMotion = CApplication::GetCameraManager()->GetCameraMotion();
	m_nMaxMotion = CApplication::GetCameraManager()->GetMaxMotion();

	m_posV = D3DXVECTOR3(0.0f, 500.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			// 固定
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 視点と注視点の距離
	SetDistance();

	// 向きの設定
	SetRot();

	// メモリの確保
	m_pRoll = new CMove;
	assert(m_pRoll != nullptr);
	m_pRoll->SetMoving(2.0f, 10.0f, 0.0f, 0.7f);

	// 注視点の算出
	SetPosR();

	// 視点の算出
	SetPosV();

	return S_OK;
}

//=============================================================================
// 終了
// Author : 唐�ｱ結斗
// 概要 : 終了
//=============================================================================
void CCamera::Uninit(void)
{
	if (m_pRoll != nullptr)
	{// 終了処理
	 // メモリの解放
		delete m_pRoll;
		m_pRoll = nullptr;
	}
}

//=============================================================================
// 更新
// Author : 唐�ｱ結斗
// 概要 : 更新
//=============================================================================
void CCamera::Update(void)
{
	if(m_viewType == TYPE_CLAIRVOYANCE)
	{
		Action();

		/*Move();
		Rotate();
		Zoom();*/
	}
}

//=============================================================================
// カメラの設定
// Author : 唐�ｱ結斗
// 概要 : ビューマトリックスの設定
//=============================================================================
void CCamera::Set()
{// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);			// 行列初期化関数

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProj);			// 行列初期化関数

	switch (m_viewType)
	{
	case TYPE_CLAIRVOYANCE:
		// プロジェクションマトリックスの作成(透視投影)
		D3DXMatrixPerspectiveFovLH(&m_mtxProj,											// プロジェクションマトリックス
			D3DXToRadian(45.0f),														// 視野角
			(float)CRenderer::SCREEN_WIDTH / (float)CRenderer::SCREEN_HEIGHT,			// アスペクト比
			CAMERA_NEAR,																// ニア
			CAMERA_FUR);																// ファー
		break;

	case TYPE_PARALLEL:
		// プロジェクションマトリックスの作成(平行投影)
		D3DXMatrixOrthoLH(&m_mtxProj,							// プロジェクションマトリックス
			(float)CRenderer::SCREEN_WIDTH,						// 幅
			(float)CRenderer::SCREEN_HEIGHT,					// 高さ
			CAMERA_NEAR,										// ニア
			CAMERA_FUR);										// ファー
		break;

	default:
		assert(false);
		break;
	}

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProj);
}

//=============================================================================
// カメラの投影方法の設定
// Author : 唐�ｱ結斗
// 概要 : 
//=============================================================================
void CCamera::SetViewType(VIEW_TYPE type)
{
	m_viewType = type;
}

//=============================================================================
// カメラの視点の設定
// Author : 唐�ｱ結斗
// 概要 : 引数から視点を設定する
//=============================================================================
void CCamera::SetPosV(const D3DXVECTOR3 posV)
{
	// 視点の設定
	m_posV = posV;

	// 視点と注視点の距離
	SetDistance();

	// 向きの設定
	SetRot();

	// 視点の算出
	SetPosV();
}

//=============================================================================
// カメラの注視点の設定
// Author : 唐�ｱ結斗
// 概要 : 引数から注視点を設定する
//=============================================================================
void CCamera::SetPosR(const D3DXVECTOR3 posR)
{
	// 注視点の設定
	m_posR = posR;

	// 視点と注視点の距離
	SetDistance();

	// 向きの設定
	SetRot();

	// 注視点の算出
	SetPosR();
}

//=============================================================================
// カメラの視点から注視点までの距離を設定する
// Author : 唐�ｱ結斗
// 概要 : 視点から注視点までの距離を算出する
//=============================================================================
void CCamera::SetRot(const D3DXVECTOR3 rot, const int nShaft)
{
	// 向きの算出
	m_rot = rot;

	if (m_rot.y < -D3DX_PI)
	{// 向きが-D3DX_PI未満の時
		m_rot.y += D3DX_PI * 2;
	}
	if (m_rot.y > D3DX_PI)
	{// 向きがD3DX_PI以上の時
		m_rot.y -= D3DX_PI * 2;
	}
	if (m_rot.x < 0.0f + 0.1f)
	{// 向きが0以下の時
		m_rot.x = 0.0f + 0.1f;
	}
	if (m_rot.x > D3DX_PI - 0.1f)
	{// 向きがD3DX_PI以上の時
		m_rot.x = D3DX_PI - 0.1f;
	}

	if (nShaft == 0)
	{// 注視点の算出
		SetPosR();
	}
	else
	{// 視点の算出
		SetPosV();
	}
}

//=============================================================================
// カメラの設定
// Author : 唐�ｱ結斗
// 概要 : 
//=============================================================================
void CCamera::SetCamera(const D3DXVECTOR3 posV, const D3DXVECTOR3 posR, const D3DXVECTOR3 rot)
{
	m_posV = posV;
	m_posR = posR;
	m_rot = rot;

	// 視点と注視点の距離
	SetDistance();

	// 向きの設定
	SetRot();

	// 注視点の算出
	SetPosR();

	// 視点の算出
	SetPosV();
}

//=============================================================================
// モーション関係のカウントの初期化
// Author : 唐�ｱ結斗
// 概要 : 
//=============================================================================
void CCamera::MotionReset(void)
{
	m_nCntFrame = 0;								// フレームカウント
	m_nCntKey = 0;									// キーカウント
	m_nNumMotion = 0;								// モーションカウント
}

//=============================================================================
// モーション番号の設定
// Author : 唐�ｱ結斗
// 概要 : 
//=============================================================================
void CCamera::SetNumMotion(const int nNumMotion)
{
	MotionReset();
	m_nNumMotion = nNumMotion;
	m_bAction = true;
}

//=============================================================================
// カメラの回転
// Author : 唐�ｱ結斗
// 概要 : 
//=============================================================================
void CCamera::Rotate(void)
{
	// 入力情報の取得
	const float MIN_MOUSE_MOVED = 1.0f;
	const float ROTATE_MOUSE_MOVED = 0.45f;

	CMouse *pMouse = CApplication::GetMouse();
	D3DXVECTOR3 rollDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int nRotateType = -1;

	if (pMouse->GetPress(CMouse::MOUSE_KEY_LEFT)
		|| pMouse->GetPress(CMouse::MOUSE_KEY_RIGHT))
	{// マウスの移動量の取得
		D3DXVECTOR3 mouseMove = D3DXVECTOR3(pMouse->GetMouseMove().y, pMouse->GetMouseMove().x, pMouse->GetMouseMove().z);

		if (D3DXVec3Length(&mouseMove) > MIN_MOUSE_MOVED || D3DXVec3Length(&mouseMove) < -MIN_MOUSE_MOVED)
		{// マウスの移動方向のノーマライズ
			D3DXVec3Normalize(&mouseMove, &mouseMove);

			// 移動方向の算出
			rollDir = mouseMove * (D3DX_PI / 180.0f) * ROTATE_MOUSE_MOVED;
		}

		if (pMouse->GetPress(CMouse::MOUSE_KEY_LEFT))
		{// 回転タイプの更新
			nRotateType = 1;
		}
		else
		{// 回転タイプの更新
			nRotateType = 0;
		}
	}

	// 摩擦係数の計算
	m_pRoll->Moving(rollDir);

	// カメラの向きの正規化
	RotNormalization(rollDir.x);
	RotNormalization(rollDir.y);
	RotNormalization(rollDir.z);

	// 回転
	m_rot += m_pRoll->GetMove();

	if (m_rot.y < -D3DX_PI)
	{// 向きが-D3DX_PI未満の時
		m_rot.y += D3DX_PI * 2;
	}
	if (m_rot.y > D3DX_PI)
	{// 向きがD3DX_PI以上の時
		m_rot.y -= D3DX_PI * 2;
	}
	if (m_rot.x < 0.0f + 0.1f)
	{// 向きが0以下の時
		m_rot.x = 0.0f + 0.1f;
	}
	if (m_rot.x > D3DX_PI - 0.1f)
	{// 向きがD3DX_PI以上の時
		m_rot.x = D3DX_PI - 0.1f;
	}

	if (nRotateType == 0)
	{// 注視点の算出
		m_posR.z = m_posV.z + sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
		m_posR.x = m_posV.x + sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		m_posR.y = m_posV.y + cosf(m_rot.x) * m_fDistance;
	}
	else
	{// 視点の算出
		m_posV.z = m_posR.z - sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
		m_posV.x = m_posR.x - sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		m_posV.y = m_posR.y - cosf(m_rot.x) * m_fDistance;
	}
}

//=============================================================================
// カメラの移動
// Author : 唐�ｱ結斗
// 概要 : カメラの移動
//=============================================================================
void CCamera::Move(void)
{
	const float CAMERA_MOVE_SPEED = 5.0f;
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	if (pKeyboard->GetPress(DIK_W) == true
		|| pKeyboard->GetPress(DIK_A) == true
		|| pKeyboard->GetPress(DIK_D) == true
		|| pKeyboard->GetPress(DIK_S) == true)
	{// 移動キーが押された
	 // 前後左右移動
		if (pKeyboard->GetPress(DIK_W) == true)
		{// [W]キーが押された時
			if (pKeyboard->GetPress(DIK_A) == true)
			{// [A]キーが押された時
			 // 移動方向の更新
				m_rotMove.y = D3DX_PI * -0.25f;
				m_rotMove.x = D3DX_PI * -0.25f;
			}
			else if (pKeyboard->GetPress(DIK_D) == true)
			{// [D]キーが押された時
			 // 移動方向の更新
				m_rotMove.y = D3DX_PI * 0.25f;
				m_rotMove.x = D3DX_PI * 0.25f;
			}
			else
			{// 移動方向の更新
				m_rotMove.y = D3DX_PI * 0.0f;
				m_rotMove.x = D3DX_PI * 0.0f;
			}
		}
		else if (pKeyboard->GetPress(DIK_S) == true)
		{// [S]キーが押された時
			if (pKeyboard->GetPress(DIK_A) == true)
			{// [A]キーが押された時
			 // 移動方向の更新
				m_rotMove.y = D3DX_PI * -0.75f;
				m_rotMove.x = D3DX_PI * -0.75f;
			}
			else if (pKeyboard->GetPress(DIK_D) == true)
			{// [D]キーが押された時
			 // 移動方向の更新
				m_rotMove.y = D3DX_PI * 0.75f;
				m_rotMove.x = D3DX_PI * 0.75f;
			}
			else
			{// 移動方向の更新
				m_rotMove.y = 0.0f;
				m_rotMove.x = D3DX_PI;
			}
		}
		else if (pKeyboard->GetPress(DIK_A) == true)
		{// [A]キーが押された時
		 // 移動方向の更新
			m_rotMove.y = D3DX_PI * -0.5f;
			m_rotMove.x = D3DX_PI * 0.0f;
		}
		else if (pKeyboard->GetPress(DIK_D) == true)
		{// [D]キーが押された時
		 // 移動方向の更新
			m_rotMove.y = D3DX_PI * 0.5f;
			m_rotMove.x = D3DX_PI * 0.0f;
		}

		// 移動方向の算出
		m_rotMove.x += m_rot.x;

		if (m_rotMove.x > D3DX_PI)
		{// 移動方向の正規化
			m_rotMove.x -= D3DX_PI * 2;
		}
		else if (m_rotMove.x < -D3DX_PI)
		{// 移動方向の正規化
			m_rotMove.x += D3DX_PI * 2;
		}

		m_rotMove.y += m_rot.y;

		if (m_rotMove.y > D3DX_PI)
		{// 移動方向の正規化
			m_rotMove.y -= D3DX_PI * 2;
		}
		else if (m_rotMove.y < -D3DX_PI)
		{// 移動方向の正規化
			m_rotMove.y += D3DX_PI * 2;
		}

		// 視点位置の更新
		m_posV.z += sinf(m_rotMove.x) * cosf(m_rotMove.y) * CAMERA_MOVE_SPEED;
		m_posV.x += sinf(m_rotMove.x) * sinf(m_rotMove.y) * CAMERA_MOVE_SPEED;
		m_posV.y += cosf(m_rotMove.x) * CAMERA_MOVE_SPEED;

		// 注視点の算出
		m_posR.z = m_posV.z + sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
		m_posR.x = m_posV.x + sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		m_posR.y = m_posV.y + cosf(m_rot.x) * m_fDistance;
	}
}

//=============================================================================
// カメラの追従
// Author : 唐�ｱ結斗
// 概要 : カメラの追従
//=============================================================================
void CCamera::FollowCamera(void)
{// プレイヤー情報の取得
	CMotionPlayer3D *pMotionPlayer3D = CGame::GetMotionPlayer3D();
	D3DXVECTOR3 posPlayer = pMotionPlayer3D->GetPos();
	D3DXVECTOR3 rotPlayer = pMotionPlayer3D->GetRot();

	//// 目的の注視点の算出
	//m_posRDest.z = posPlayer.z + sinf(rotPlayer.x) * cosf(rotPlayer.y) * m_fDistance;
	//m_posRDest.x = posPlayer.x + sinf(rotPlayer.x) * sinf(rotPlayer.y) * m_fDistance;
	//m_posRDest.y = posPlayer.y + cosf(rotPlayer.x) * m_fDistance;

	m_posRDest.z = posPlayer.z + cosf(rotPlayer.y) * -10.0f;
	m_posRDest.x = posPlayer.x + sinf(rotPlayer.y) * -10.0f;
	m_posRDest.y = posPlayer.y;

	//// 目的の視点の算出
	//m_posVDest.z = posPlayer.z - sinf(rotPlayer.x) * cosf(rotPlayer.y) * m_fDistance;
	//m_posVDest.x = posPlayer.x - sinf(rotPlayer.x) * sinf(rotPlayer.y) * m_fDistance;
	//m_posVDest.y = posPlayer.y - cosf(rotPlayer.x) * m_fDistance;

	m_posVDest.z = posPlayer.z - cosf(m_rot.y) * m_fDistance;
	m_posVDest.x = posPlayer.x - sinf(m_rot.y) * m_fDistance;
	m_posVDest.y = 80.0f;

	// 注視点の移動
	m_posR += (m_posRDest - m_posR) * 0.1f;

	// 視点の移動
	m_posV += (m_posVDest - m_posV) * 0.1f;
}

//=============================================================================
// カメラのアクション
// Author : 唐�ｱ結斗
// 概要 : カメラのアクション設定
//=============================================================================
void CCamera::Action()
{
	if (m_pMotion != nullptr
		&& m_bAction)
	{
		if (m_nCntFrame == 0)
		{// 追加する数値の算出
			m_posVDest = m_pMotion[m_nNumMotion].pCameraAction[m_nCntKey].posVDest - m_posV;
			m_posRDest = m_pMotion[m_nNumMotion].pCameraAction[m_nCntKey].posRDest - m_posR;
		}

		m_nCntFrame++;

		D3DXVECTOR3 addPosV = m_posVDest / (float)m_pMotion[m_nNumMotion].pCameraAction[m_nCntKey].nFrame;
		D3DXVECTOR3 addPosR = m_posRDest / (float)m_pMotion[m_nNumMotion].pCameraAction[m_nCntKey].nFrame;

		// 視点の移動
		D3DXVECTOR3 posV = GetPosV() + addPosV;

		// 視点の設定
		SetPosV(posV);

		// 注視点の移動
		D3DXVECTOR3 posR = GetPosR() + addPosR;

		// 注視点の設定
		SetPosR(posR);

		if (m_nCntFrame >= m_pMotion[m_nNumMotion].pCameraAction[m_nCntKey].nFrame)
		{
			m_nCntKey++;
			m_nCntFrame = 0;

			if (m_nCntKey >= m_pMotion[m_nNumMotion].nMaxKey)
			{
				if (m_pMotion[m_nNumMotion].bLoop)
				{
					m_nCntKey = 0;
				}
				else if(!m_pMotion[m_nNumMotion].bLoop)
				{
					m_bAction = false;
				}
			}
		}
	}
}

//=============================================================================
// カメラの拡縮処理
// Author : 唐�ｱ結斗
// 概要 : マウスホイールでカメラの拡縮を行う
//=============================================================================
void CCamera::Zoom()
{// マウス情報の取得
	CMouse *pMouse = CApplication::GetMouse();

	m_fDistance += (float)pMouse->GetMouseWheel() * 1.0f;

	if (m_fDistance >= CAMERA_FUR / 2.0f)
	{
		m_fDistance = CAMERA_FUR / 2.0f;
	}
	else if (m_fDistance <= CAMERA_NEAR * 2.0f)
	{
		m_fDistance = CAMERA_NEAR * 2.0f;
	}

	SetPosV();
}

//=============================================================================
// カメラの視点の設定
// Author : 唐�ｱ結斗
// 概要 : 視点を設定する
//=============================================================================
void CCamera::SetPosV()
{
	// 視点の算出
	m_posV.z = m_posR.z - sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
	m_posV.x = m_posR.x - sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
	m_posV.y = m_posR.y - cosf(m_rot.x) * m_fDistance;
}

//=============================================================================
// カメラの注視点の設定
// Author : 唐�ｱ結斗
// 概要 : 注視点を設定する
//=============================================================================
void CCamera::SetPosR()
{
	// 注視点の算出
	m_posR.z = m_posV.z + sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
	m_posR.x = m_posV.x + sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
	m_posR.y = m_posV.y + cosf(m_rot.x) * m_fDistance;
}

//=============================================================================
// カメラの角度の設定
// Author : 唐�ｱ結斗
// 概要 : カメラの角度
//=============================================================================
void CCamera::SetRot()
{
	// 視点と注視点の距離
	D3DXVECTOR3 posDiss = m_posR - m_posV;

	// 角度の算出
	m_rot.y = atan2f(posDiss.x, posDiss.z);
	m_rot.x = atan2f(sqrtf((posDiss.x * posDiss.x) + (posDiss.z * posDiss.z)), posDiss.y);
	m_rot.z = 0.0f;

	if (m_rot.y < -D3DX_PI)
	{// 向きが-D3DX_PI未満の時
		m_rot.y += D3DX_PI * 2;
	}
	if (m_rot.y > D3DX_PI)
	{// 向きがD3DX_PI以上の時
		m_rot.y -= D3DX_PI * 2;
	}
	if (m_rot.x < 0.0f + 0.1f)
	{// 向きが0以下の時
		m_rot.x = 0.0f + 0.1f;
	}
	if (m_rot.x > D3DX_PI - 0.1f)
	{// 向きがD3DX_PI以上の時
		m_rot.x = D3DX_PI - 0.1f;
	}
}

//=============================================================================
// カメラの視点から注視点までの距離を設定する
// Author : 唐�ｱ結斗
// 概要 : 視点から注視点までの距離を算出する
//=============================================================================
void CCamera::SetDistance()
{
	// 視点と注視点の距離
	D3DXVECTOR3 posDiss = m_posR - m_posV;
	m_fDistance = sqrtf((posDiss.y * posDiss.y) + (posDiss.x * posDiss.x) + (posDiss.z * posDiss.z));
}


