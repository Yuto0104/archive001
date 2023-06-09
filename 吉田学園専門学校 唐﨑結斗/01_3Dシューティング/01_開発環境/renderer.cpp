//=============================================================================
//
// レンダラークラス(renderer.cpp)
// Author : 唐�ｱ結斗
// 概要 : 描画を行うクラス
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <stdio.h>
#include <assert.h>

#include "renderer.h"
#include "object.h"
#include "application.h"
#include "game.h"
#include "motion_player3D.h"
#include "camera.h"
#include "enemy3D.h"
#include "enemy_manager.h"

//=============================================================================
// コンストラクタ
// Author : 唐�ｱ結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CRenderer::CRenderer()
{
	m_pD3D = nullptr;				// Direct3Dオブジェクト
	m_pD3DDevice = nullptr;			// Deviceオブジェクト
}

//=============================================================================
// デストラクタ
// Author : 唐�ｱ結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CRenderer::~CRenderer()
{
	assert(m_pD3D == nullptr);
	assert(m_pD3DDevice == nullptr);
}

//=============================================================================
// 初期化
// Author : 唐�ｱ結斗
// 概要 : 描画関係のデバイス設定を行い、他クラスの初期化関数を呼び出す
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == nullptr)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));									// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;											// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;								// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;								// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;								// カラーモードの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;							// 映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil = TRUE;								// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;							// デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;											// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;			// インターバル

	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if ((FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) &&
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) &&
		// 上記の設定が失敗したら
		// 描画と頂点処理をCPUで行なう
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))))
	{
		// 生成失敗
		return E_FAIL;
	}

	// レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//テクスチャをリニア補完する
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//テクスチャをリニア補完する
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

#ifdef _DEBUG
	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);
#endif
	return S_OK;
}

//=============================================================================
// 終了
// Author : 唐�ｱ結斗
// 概要 : ポインタ型のメンバ変数の解放
//=============================================================================
void CRenderer::Uninit()
{
#ifdef _DEBUG
	// デバッグ情報表示用フォントの破棄
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
#endif // _DEBUG

	// デバイスの破棄
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	// Direct3Dオブジェクトの破棄
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}

//=============================================================================
// 更新
// Author : 唐�ｱ結斗
// 概要 : 他クラスの更新を呼び出す
//=============================================================================
void CRenderer::Update()
{
	// ポリゴンの更新処理
	CObject::UpdateAll();
}

//=============================================================================
// 描画
// Author : 唐�ｱ結斗
// 概要 :　スクリーンの描画設定を行い、他クラスの描画を行う
//=============================================================================
void CRenderer::Draw()
{
	// バックバッファ＆Ｚバッファのクリア
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		// ポリゴンの描画処理
		CObject::DrawAll(CObject::DROWTYPE_BG);
		CObject::DrawAll(CObject::DROWTYPE_GAME);

#ifdef _DEBUG
		// FPS表示
		DrawFPS();
#endif // _DEBUG

		// Direct3Dによる描画の終了
		m_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

#ifdef _DEBUG
//=============================================================================
// FPS表示
// Author : 唐�ｱ結斗
// 概要 :　デバック表示の設定
//=============================================================================
void CRenderer::DrawFPS()
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	TCHAR str[0xfff];
	TCHAR strCopy[256];

	wsprintf(str, _T("FPS : %d\n"), GetFps());

	if (CApplication::GetMode() == CApplication::MODE_GAME
		&& CGame::GetMotionPlayer3D() != nullptr
		&& CGame::GetMotionPlayer3D()->GetLife() > 0)
	{
		D3DXVECTOR3 pos = CGame::GetMotionPlayer3D()->GetPos();
		sprintf(strCopy, _T("プレイヤーの位置 | x : %.3f | y : %.3f | z : %.3f |\n"), pos.x, pos.y, pos.z);
		strcat(str, strCopy);

		pos = CApplication::ScreenCastWorld(pos);
		sprintf(strCopy, _T("プレイヤーのスクリーン座標 | x : %.3f | y : %.3f | z : %.3f |\n"), pos.x, pos.y, pos.z);
		strcat(str, strCopy);

		pos = CApplication::WorldCastScreen(pos);
		sprintf(strCopy, _T("プレイヤーのスクリーン座標からワールド座標へ | x : %.3f | y : %.3f | z : %.3f |\n"), pos.x, pos.y, pos.z);
		strcat(str, strCopy);

		CCamera *pCamera = CApplication::GetCameraBG();
		D3DXVECTOR3 posV = pCamera->GetPosV();
		D3DXVECTOR3 posR = pCamera->GetPosR();
		D3DXVECTOR3 rot = pCamera->GetRot();

		sprintf(strCopy, _T("カメラの視点の位置 | x : %.3f | y : %.3f | z : %.3f |\n"), posV.x, posV.y, posV.z);
		strcat(str, strCopy);
		sprintf(strCopy, _T("カメラの注視点の位置 | x : %.3f | y : %.3f | z : %.3f |\n"), posR.x, posR.y, posR.z);
		strcat(str, strCopy);
		sprintf(strCopy, _T("カメラの向き | x : %.3f | y : %.3f | z : %.3f |\n"), rot.x, rot.y, rot.z);
		strcat(str, strCopy);
		sprintf(strCopy, _T("カメラのディスタンス : %.3f\n"), pCamera->GetDistance());
		strcat(str, strCopy);

		int nCntSetEnemy = CEnemy3D::GetCntSetEnemy();
		sprintf(strCopy, _T("敵の設置数 : %d \n"), nCntSetEnemy);
		strcat(str, strCopy);

		int nCntFrame = CGame::GetEnemyManager()->GetCntFrame();
		sprintf(strCopy, _T("現在のフレーム数 : %d \n"), nCntFrame);
		strcat(str, strCopy);
	}


	// テキスト描画
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif // _DEBUG
