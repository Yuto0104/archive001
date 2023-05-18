//**************************************************************************************************
//
// カメラ処理(camera.cpp)
// Auther：唐﨑結斗
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include "main.h"
#include "camera.h"
#include "input.h"
#include "mouse.h"
#include "player.h"
#include "calculation.h"

//***************************************************************************
// マクロ定義
//***************************************************************************
#define CAMERA_NEAR					(10.0f)				// ニア
#define CAMERA_FUR					(2000.0f)			// ファー
#define CAMERA_ROT_MOVE				(D3DX_PI * 10)		// 角度の変動値
#define CAMERA_MOVE_SPEED			(20.0f)				// カメラの移動読度
#define MIN_MOUSE_MOVED				(5.0f)				// マウス判定の最低値
#define ROTATE_MOUSE_MOVED			(0.45f)				// マウスでのカメラ回転値
#define MAX_ROTATE_MOUSE_MOVED		(50.0f)				// マウスでのカメラ回転値の最大
#define MIN_ROTATE_MOUSE_MOVED		(0.1f)				// マウスでのカメラ回転値の最小
#define ROTATE_MOUSE_FRICTION		(0.2f)				// マウスでのカメラ回転値の摩擦係数
#define FOLLOW_DISTANCE				(10.0f)				// 追従時の注視点とプレイヤーの距離

//***************************************************************************
// グローバル変数
//***************************************************************************
static Camera		s_camera;				// カメラ情報
static int			s_nCameraMode = 0;		// カメラ移動モード

//---------------------------------------------------------------------------
// カメラ初期化処理
//---------------------------------------------------------------------------
void InitCamera(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU, D3DXVECTOR3 rot)
{
	// 視点・注視点・上方向を設定する
	s_camera.posV = posV;
	s_camera.posR = posR;
	s_camera.vecU = vecU;

	// 数値の計算
	float fDistanceX = s_camera.posR.x - s_camera.posV.x;
	float fDistanceY = s_camera.posR.y - s_camera.posV.y;
	float fDistanceZ = s_camera.posR.z - s_camera.posV.z;

	// 視点から注視点までの距離を算出
	s_camera.fDistance = sqrtf((fDistanceY * fDistanceY) + (fDistanceX * fDistanceX) + (fDistanceZ * fDistanceZ));

	// 注視点の向きを設定
	s_camera.rot = rot;

	// 移動方向の初期化
	s_camera.rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//---------------------------------------------------------------------------
// カメラ終了処理
//---------------------------------------------------------------------------
void UninitCamera(void)
{

}

//---------------------------------------------------------------------------
// カメラ更新処理
//---------------------------------------------------------------------------
void UpdateCamera(void)
{
	if (GetKeyboardTrigger(DIK_F5) == true)
	{// カメラ移動モードの変更
		s_nCameraMode ^= 1;
	}

	MODE mode = GetMode();

	if (mode == MODE_GAME)
	{
		// カメラの回転
		RotateCamera();

		// カメラ移動
		//MoveCamera();

		// カメラの追従処理
		FollowCamera();
	}
	else if (mode == MODE_TITLE)
	{
		TitleRotateCamera();
	}
}

//---------------------------------------------------------------------------
// カメラ設定処理
//---------------------------------------------------------------------------
void SetCamera(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&s_camera.mtxView);			// 行列初期化関数

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&s_camera.mtxView,
		&s_camera.posV,
		&s_camera.posR,
		&s_camera.vecU);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &s_camera.mtxView);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&s_camera.mtxProjection);			// 行列初期化関数

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&s_camera.mtxProjection,
		D3DXToRadian(45.0f),								// 視野角
		(float)SCREEN_WIDH / (float)SCREEN_HEIGHT,			// アスペクト比
		CAMERA_NEAR,										// ニア
		CAMERA_FUR);										// ファー

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &s_camera.mtxProjection);
}

//---------------------------------------------------------------------------
// カメラ設定処理
//---------------------------------------------------------------------------
Camera *GetCamera(void)
{
	return &s_camera;
}

//---------------------------------------------------------------------------
// カメラ回転処理
//---------------------------------------------------------------------------
void RotateCamera(void)
{
	D3DXVECTOR3 pMouseMove = GetMouseMove();

	if (pMouseMove.x > MIN_MOUSE_MOVED || pMouseMove.x < -MIN_MOUSE_MOVED)
	{// マウスが一定距離(X)移動したとき
		if (pMouseMove.x > MIN_MOUSE_MOVED)
		{
			s_camera.roll.y += (D3DX_PI / 180.0f) * ROTATE_MOUSE_MOVED;
		}
		if (pMouseMove.x < -MIN_MOUSE_MOVED)
		{
			s_camera.roll.y += (D3DX_PI / 180.0f) * -ROTATE_MOUSE_MOVED;
		}
	}

	if (pMouseMove.y > MIN_MOUSE_MOVED || pMouseMove.y < -MIN_MOUSE_MOVED)
	{// マウスが一定距離(Y)移動したとき
		if (pMouseMove.y > MIN_MOUSE_MOVED)
		{
			s_camera.roll.x += (D3DX_PI / 180.0f) * ROTATE_MOUSE_MOVED / 3.0f;
		}
		if (pMouseMove.y < -MIN_MOUSE_MOVED)
		{
			s_camera.roll.x += (D3DX_PI / 180.0f) * -ROTATE_MOUSE_MOVED / 3.0f;
		}
	}

	// 速度リミッター
	float speed = D3DXVec3Length(&s_camera.roll);

	if (speed > (D3DX_PI / 180.0f) * MAX_ROTATE_MOUSE_MOVED)
	{
		s_camera.roll = s_camera.roll / speed * (D3DX_PI / 180.0f) * -ROTATE_MOUSE_MOVED;
	}

	// 動摩擦係数を加える
	s_camera.roll *= (1.0f - ROTATE_MOUSE_FRICTION);

	// 速度リミッター
	if (D3DXVec3Length(&s_camera.roll) < (D3DX_PI / 180.0f) * MIN_ROTATE_MOUSE_MOVED)
	{
		s_camera.roll = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// カメラの向きの正規化
	RotNormalization(s_camera.roll.x);
	RotNormalization(s_camera.roll.y);
	RotNormalization(s_camera.roll.z);

	s_camera.rot += s_camera.roll;

	if (s_camera.rot.y < -D3DX_PI)
	{// 向きが-D3DX_PI未満の時
		s_camera.rot.y += D3DX_PI * 2;
	}
	if (s_camera.rot.y > D3DX_PI)
	{// 向きがD3DX_PI以上の時
		s_camera.rot.y -= D3DX_PI * 2;
	}
	if (s_camera.rot.x < 0.0f + 1.68f)
	{// 向きが0以下の時
		s_camera.rot.x = 0.0f + 1.68f;
	}
	if (s_camera.rot.x > D3DX_PI - 0.1f)
	{// 向きがD3DX_PI以上の時
		s_camera.rot.x = D3DX_PI - 0.1f;
	}

	// 注視点の算出
	s_camera.posR.z = s_camera.posV.z + sinf(s_camera.rot.x) * cosf(s_camera.rot.y) * s_camera.fDistance;
	s_camera.posR.x = s_camera.posV.x + sinf(s_camera.rot.x) * sinf(s_camera.rot.y) * s_camera.fDistance;
	s_camera.posR.y = s_camera.posV.y + cosf(s_camera.rot.x) * s_camera.fDistance;

	//// 注視点の回転
	//if (GetKeyboardPress(DIK_Q) == true
	//	|| GetKeyboardPress(DIK_E) == true
	//	|| GetKeyboardPress(DIK_Y) == true
	//	|| GetKeyboardPress(DIK_H) == true)
	//{
	//	if (GetKeyboardPress(DIK_Q) == true)
	//	{// [Q]キーが押された時
	//		s_camera.rot.y += 1.0f / -CAMERA_ROT_MOVE;
	//	}
	//	if (GetKeyboardPress(DIK_E) == true)
	//	{// [E]キーが押された時
	//		s_camera.rot.y += 1.0f / CAMERA_ROT_MOVE;
	//	}
	//	if (GetKeyboardPress(DIK_Y) == true)
	//	{// [Y]キーが押された時
	//		s_camera.rot.x += 1.0f / -CAMERA_ROT_MOVE;
	//	}
	//	if (GetKeyboardPress(DIK_H) == true)
	//	{// [H]キーが押された時
	//		s_camera.rot.x += 1.0f / CAMERA_ROT_MOVE;
	//	}

	//	// カメラの向きの正規化
	//	if (s_camera.rot.y < -D3DX_PI)
	//	{// 向きが-D3DX_PI未満の時
	//		s_camera.rot.y += D3DX_PI * 2;
	//	}
	//	if (s_camera.rot.y > D3DX_PI)
	//	{// 向きがD3DX_PI以上の時
	//		s_camera.rot.y -= D3DX_PI * 2;
	//	}
	//	if (s_camera.rot.x < 0.0f + 0.1f)
	//	{// 向きが0以下の時
	//		s_camera.rot.x = 0.0f + 0.1f;
	//	}
	//	if (s_camera.rot.x > D3DX_PI - 0.1f)
	//	{// 向きがD3DX_PI以上の時
	//		s_camera.rot.x = D3DX_PI - 0.1f;
	//	}

	//	// 注視点の算出
	//	s_camera.posR.z = s_camera.posV.z + sinf(s_camera.rot.x) * cosf(s_camera.rot.y) * s_camera.fDistance;
	//	s_camera.posR.x = s_camera.posV.x + sinf(s_camera.rot.x) * sinf(s_camera.rot.y) * s_camera.fDistance;
	//	s_camera.posR.y = s_camera.posV.y + cosf(s_camera.rot.x) * s_camera.fDistance;
	//}

	//// 視点の回転
	//if (GetKeyboardPress(DIK_Z) == true
	//	|| GetKeyboardPress(DIK_C) == true
	//	|| GetKeyboardPress(DIK_U) == true
	//	|| GetKeyboardPress(DIK_J) == true)
	//{
	//	if (GetKeyboardPress(DIK_Z) == true)
	//	{// [Z]キーが押された時
	//		s_camera.rot.y += 1.0f / -CAMERA_ROT_MOVE;
	//	}
	//	if (GetKeyboardPress(DIK_C) == true)
	//	{// [C]キーが押された時
	//		s_camera.rot.y += 1.0f / CAMERA_ROT_MOVE;
	//	}
	//	if (GetKeyboardPress(DIK_U) == true)
	//	{// [U]キーが押された時
	//		s_camera.rot.x += 1.0f / -CAMERA_ROT_MOVE;
	//	}
	//	if (GetKeyboardPress(DIK_J) == true)
	//	{// [J]キーが押された時
	//		s_camera.rot.x += 1.0f / CAMERA_ROT_MOVE;
	//	}

	//	// カメラの向きの正規化
	//	if (s_camera.rot.y < -D3DX_PI)
	//	{// 向きが-D3DX_PI未満の時
	//		s_camera.rot.y += D3DX_PI * 2;
	//	}
	//	if (s_camera.rot.y > D3DX_PI)
	//	{// 向きがD3DX_PI以上の時
	//		s_camera.rot.y -= D3DX_PI * 2;
	//	}
	//	if (s_camera.rot.x < 0.0f + 0.1f)
	//	{// 向きが0以下の時
	//		s_camera.rot.x = 0.0f + 0.1f;
	//	}
	//	if (s_camera.rot.x > D3DX_PI - 0.1f)
	//	{// 向きがD3DX_PI以上の時
	//		s_camera.rot.x = D3DX_PI - 0.1f;
	//	}

	//	// 視点の算出
	//	s_camera.posV.z = s_camera.posR.z - sinf(s_camera.rot.x) * cosf(s_camera.rot.y) * s_camera.fDistance;
	//	s_camera.posV.x = s_camera.posR.x - sinf(s_camera.rot.x) * sinf(s_camera.rot.y) * s_camera.fDistance;
	//	s_camera.posV.y = s_camera.posR.y - cosf(s_camera.rot.x) * s_camera.fDistance;
	//}
}

//---------------------------------------------------------------------------
// カメラ移動処理
//---------------------------------------------------------------------------
void MoveCamera(void)
{
	if (GetKeyboardPress(DIK_W) == true
		|| GetKeyboardPress(DIK_A) == true
		|| GetKeyboardPress(DIK_D) == true
		|| GetKeyboardPress(DIK_S) == true)
	{// 移動キーが押された
		// 前後左右移動
		if (GetKeyboardPress(DIK_W) == true)
		{// [W]キーが押された時
			if (GetKeyboardPress(DIK_A) == true)
			{// [A]キーが押された時
				// 移動方向の更新
				s_camera.rotMove.y = D3DX_PI * -0.25f;
			}
			else if (GetKeyboardPress(DIK_D) == true)
			{// [D]キーが押された時
			 // 移動方向の更新
				s_camera.rotMove.y = D3DX_PI * 0.25f;
			}
			else
			{// 移動方向の更新
				s_camera.rotMove.y = D3DX_PI * 0.0f;
			}

			// 移動方向の更新
			s_camera.rotMove.x = D3DX_PI * 0.0f;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{// [S]キーが押された時
			if (GetKeyboardPress(DIK_A) == true)
			{// [A]キーが押された時
				// 移動方向の更新
				s_camera.rotMove.y = D3DX_PI * -0.75f;
			}
			else if (GetKeyboardPress(DIK_D) == true)
			{// [D]キーが押された時
				// 移動方向の更新
				s_camera.rotMove.y = D3DX_PI * 0.75f;
			}
			else
			{// 移動方向の更新
				s_camera.rotMove.y = D3DX_PI;
			}

			// 移動方向の更新
			s_camera.rotMove.x = D3DX_PI * 1.0f;
		}
		else if (GetKeyboardPress(DIK_A) == true)
		{// [A]キーが押された時
			// 移動方向の更新
			s_camera.rotMove.y = D3DX_PI * -0.5f;

			// 移動方向の更新
			s_camera.rotMove.x = D3DX_PI * 0.5f;
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{// [D]キーが押された時
			// 移動方向の更新
			s_camera.rotMove.y = D3DX_PI * 0.5f;

			// 移動方向の更新
			s_camera.rotMove.x = D3DX_PI * 0.5f;
		}

		// 移動方向の算出
		s_camera.rotMove.x += s_camera.rot.x;
		if (s_camera.rotMove.x > D3DX_PI)
		{// 移動方向の正規化
			s_camera.rotMove.x -= D3DX_PI * 2;
		}
		else if (s_camera.rotMove.x < -D3DX_PI)
		{// 移動方向の正規化
			s_camera.rotMove.x += D3DX_PI * 2;
		}

		s_camera.rotMove.y += s_camera.rot.y;
		if (s_camera.rotMove.y > D3DX_PI)
		{// 移動方向の正規化
			s_camera.rotMove.y -= D3DX_PI * 2;
		}
		else if (s_camera.rotMove.y < -D3DX_PI)
		{// 移動方向の正規化
			s_camera.rotMove.y += D3DX_PI * 2;
		}

		// 視点位置の更新
		if (s_nCameraMode == 0)
		{// カメラ移動モード[0]
			s_camera.posV.x += sinf(s_camera.rotMove.y) * CAMERA_MOVE_SPEED;
			s_camera.posV.z += cosf(s_camera.rotMove.y) * CAMERA_MOVE_SPEED;
		}
		else if (s_nCameraMode == 1)
		{// カメラ移動モード[1]
			s_camera.posV.z += sinf(s_camera.rotMove.x) * cosf(s_camera.rotMove.y) * CAMERA_MOVE_SPEED;
			s_camera.posV.x += sinf(s_camera.rotMove.x) * sinf(s_camera.rotMove.y) * CAMERA_MOVE_SPEED;
			s_camera.posV.y += cosf(s_camera.rotMove.x) * CAMERA_MOVE_SPEED;
		}	

		// 注視点の算出
		s_camera.posR.z = s_camera.posV.z + sinf(s_camera.rot.x) * cosf(s_camera.rot.y) * s_camera.fDistance;
		s_camera.posR.x = s_camera.posV.x + sinf(s_camera.rot.x) * sinf(s_camera.rot.y) * s_camera.fDistance;
		s_camera.posR.y = s_camera.posV.y + cosf(s_camera.rot.x) * s_camera.fDistance;
	}
}

//---------------------------------------------------------------------------
// カメラの追従処理
//---------------------------------------------------------------------------
void FollowCamera(void)
{
	// プレイヤー情報の取得
	Player *pPlayer = GetPlayer();

	//// 目的の注視点の算出
	//s_camera.posRDest.z = pPlayer->pos.z + sinf(pPlayer->rot.x) * cosf(pPlayer->rot.y) * s_camera.fDistance;
	//s_camera.posRDest.x = pPlayer->pos.x + sinf(pPlayer->rot.x) * sinf(pPlayer->rot.y) * s_camera.fDistance;
	//s_camera.posRDest.y = pPlayer->pos.y + cosf(pPlayer->rot.x) * s_camera.fDistance;

	s_camera.posRDest.z = pPlayer->pos.z + cosf(pPlayer->rot.y) * -10.0f;
	s_camera.posRDest.x = pPlayer->pos.x + sinf(pPlayer->rot.y) * -10.0f;
	s_camera.posRDest.y = pPlayer->pos.y;

	//// 目的の視点の算出
	//s_camera.posVDest.z = pPlayer->pos.z - sinf(pPlayer->rot.x) * cosf(pPlayer->rot.y) * s_camera.fDistance;
	//s_camera.posVDest.x = pPlayer->pos.x - sinf(pPlayer->rot.x) * sinf(pPlayer->rot.y) * s_camera.fDistance;
	//s_camera.posVDest.y = pPlayer->pos.y - cosf(pPlayer->rot.x) * s_camera.fDistance;

	s_camera.posVDest.z = pPlayer->pos.z - cosf(s_camera.rot.y) * s_camera.fDistance;
	s_camera.posVDest.x = pPlayer->pos.x - sinf(s_camera.rot.y) * s_camera.fDistance;
	s_camera.posVDest.y = 80.0f;

	// 注視点の移動
	s_camera.posR.x += (s_camera.posRDest.x - s_camera.posR.x) * 0.1f;
	s_camera.posR.y += (s_camera.posRDest.y - s_camera.posR.y) * 0.1f;
	s_camera.posR.z += (s_camera.posRDest.z - s_camera.posR.z) * 0.1f;

	// 視点の移動
	s_camera.posV.x += (s_camera.posVDest.x - s_camera.posV.x) * 0.1f;
	s_camera.posV.y += (s_camera.posVDest.y - s_camera.posV.y) * 0.1f;
	s_camera.posV.z += (s_camera.posVDest.z - s_camera.posV.z) * 0.1f;
}

//---------------------------------------------------------------------------
// カメラの自動回転処理
//---------------------------------------------------------------------------
void AutoRotateCamera(void)
{
	// プレイヤー情報の取得
	Player *pPlayer = GetPlayer();

	// 目的の向き
	s_camera.rotDest.x = atan2f(pPlayer->pos.z - s_camera.posV.z, pPlayer->pos.y - s_camera.posV.y);
	s_camera.rotDest.y = pPlayer->rot.y - D3DX_PI;

	// 目的の向きの算出
	s_camera.rotDest.x -= s_camera.rot.x;
	s_camera.rotDest.y -= s_camera.rot.y;

	// カメラの目的の向きの正規化
	if (s_camera.rotDest.y < -D3DX_PI)
	{// 向きが-D3DX_PI未満の時
		s_camera.rotDest.y += D3DX_PI * 2;
	}
	if (s_camera.rotDest.y > D3DX_PI)
	{// 向きがD3DX_PI以上の時
		s_camera.rotDest.y -= D3DX_PI * 2;
	}
	if (s_camera.rotDest.x < 0.0f + 0.1f)
	{// 向きが0以下の時
		s_camera.rotDest.x = 0.0f + 0.1f;
	}
	if (s_camera.rotDest.x > D3DX_PI - 0.1f)
	{// 向きがD3DX_PI以上の時
		s_camera.rotDest.x = D3DX_PI - 0.1f;
	}

	// カメラの向きの更新
	s_camera.rot.x += (s_camera.rotDest.x) * 0.1f;
	s_camera.rot.y += (s_camera.rotDest.y) * 0.1f;

	// カメラの向きの正規化
	if (s_camera.rot.y < -D3DX_PI)
	{// 向きが-D3DX_PI未満の時
		s_camera.rot.y += D3DX_PI * 2;
	}
	if (s_camera.rot.y > D3DX_PI)
	{// 向きがD3DX_PI以上の時
		s_camera.rot.y -= D3DX_PI * 2;
	}
	if (s_camera.rot.x < 0.0f + 0.1f)
	{// 向きが0以下の時
		s_camera.rot.x = 0.0f + 0.1f;
	}
	if (s_camera.rot.x > D3DX_PI - 0.1f)
	{// 向きがD3DX_PI以上の時
		s_camera.rot.x = D3DX_PI - 0.1f;
	}
}

//---------------------------------------------------------------------------
// カメラの回転処理
//---------------------------------------------------------------------------
void TitleRotateCamera(void)
{
	// 視点の回転
	s_camera.rot.y += (D3DX_PI / 180.0f) * 0.5f;

	// カメラの向きの正規化
	if (s_camera.rot.y < -D3DX_PI)
	{// 向きが-D3DX_PI未満の時
		s_camera.rot.y += D3DX_PI * 2;
	}
	if (s_camera.rot.y > D3DX_PI)
	{// 向きがD3DX_PI以上の時
		s_camera.rot.y -= D3DX_PI * 2;
	}
	if (s_camera.rot.x < 0.0f + 0.1f)
	{// 向きが0以下の時
		s_camera.rot.x = 0.0f + 0.1f;
	}
	if (s_camera.rot.x > D3DX_PI - 0.1f)
	{// 向きがD3DX_PI以上の時
		s_camera.rot.x = D3DX_PI - 0.1f;
	}

	// 視点の算出
	s_camera.posV.z = s_camera.posR.z - sinf(s_camera.rot.x) * cosf(s_camera.rot.y) * s_camera.fDistance;
	s_camera.posV.x = s_camera.posR.x - sinf(s_camera.rot.x) * sinf(s_camera.rot.y) * s_camera.fDistance;
	s_camera.posV.y = s_camera.posR.y - cosf(s_camera.rot.x) * s_camera.fDistance;
}