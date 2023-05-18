//**************************************************************************************************
//
// メイン処理(main.cpp)
// Auther：唐﨑結斗
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include<stdio.h>
#include"main.h"

#include"input.h"
#include"mouse.h"
#include"fade.h"
#include"title.h"
#include"tutorial.h"
#include"game.h"
#include"result.h"
#include"ranking.h"

#include"player.h"
#include"camera.h"
#include"sound.h"

//***************************************************************************
// グローバル変数
//***************************************************************************
LPDIRECT3D9					g_pD3D = NULL;							// Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9			g_pD3DDevice = NULL;					// Direct3Dデバイスへのポインタ
LPD3DXFONT					g_pFont = NULL;							// フォントへのポインタ
MODE						g_mode = MODE_TITLE;					// 現在のモード
HWND						g_hWnd;									// ウィンドウハンドル(識別子)
int							g_nCountFPS = 0;						// FPSカウンタ
int							g_nJudgDebagText = 0;					// デバック表示処理の判定用変数
int							g_nUseWireFrame = 0;					// ワイヤーフレームの判定用変数

//---------------------------------------------------------------------------
// メイン関数
//---------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdline, int nCmdshow)
{
	// ウィンドウクラスの構造体
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),						// WNDCLASSEXのメモリサイズ
		CS_CLASSDC,								// ウィンドウのスタイル
		WindowProc,								// ウィンドウプロシージャ
		0,										// 0にする(通常は使用しない)
		0,										// 0にする(通常は使用しない)
		hInstance,								// インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),			// タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),				// マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),				// クライアント領域の背景色
		NULL,									// メニューバー
		CLASS_NAME,								// ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)			// ファイルのアイコン
	};

	// 変数宣言
	MSG			msg;												// メッセージを格納する変数
	RECT		rect = { 0,0,SCREEN_WIDH,SCREEN_HEIGHT };			// 画面サイズ構造体
	DWORD		dwCurrentTime;										// 現在時刻
	DWORD		dwExecLastTime;										// 最後に処理した時刻
	DWORD		dwFrameCount;										// フレームカウント
	DWORD		dwFPSLastTime;										// 最後にFPSを計測した時刻

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// ウィンドウを生成
	g_hWnd = CreateWindowEx(0,				// 拡張ウィンドウスタイル
		CLASS_NAME,							// ウィンドウクラスの名前
		WINDOW_NAME,						// ウィンドウの名前
		WS_OVERLAPPEDWINDOW,				// ウィンドウスタイル
		CW_USEDEFAULT,						// ウィンドウの左上X座標
		CW_USEDEFAULT,						// ウィンドウの左上Y座標
		(rect.right - rect.left),			// ウィンドウの幅
		(rect.bottom - rect.top),			// ウィンドウの高さ
		NULL,								// 親ウィンドウのハンドル
		NULL,								// メニューハンドル又は子ウィンドウID
		hInstance,							// インスタンスハンドル
		NULL);								// ウィンドウ作成データ

	// 初期化処理
#ifdef _DEBUG
	if (FAILED(Init(hInstance, g_hWnd, TRUE)) != 0)
	{// 初期化処理が失敗した場合
		return-1;
	}
#else
	if (FAILED(Init(hInstance, g_hWnd, FALSE)) != 0)
	{// 初期化処理が失敗した場合
		return-1;
	}
#endif
	// 分解能を設定
	timeBeginPeriod(1);

	dwCurrentTime = 0;						// 初期化
	dwExecLastTime = timeGetTime();			// 現在時刻を取得(保存)
	dwFrameCount = 0;						// フレームカウントを初期化
	dwFPSLastTime = timeGetTime();			// 現在時刻を代入(保存)

	// ウィンドウの表示
	ShowWindow(g_hWnd, nCmdshow);		// ウィンドウの表示状態を設定
	UpdateWindow(g_hWnd);				// クライアント領域を更新

	// メッセージループ
	while (1)
	{
		// 条件式が真の場合実行
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// Windowsの処理
			if (msg.message == WM_QUIT)
			{// WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{
				// メッセージの設定
				TranslateMessage(&msg);			// 仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);			// ウィンドウプロシージャへメッセージを送出
			}
		}
		else
		{// DirectXの処理
			dwCurrentTime = timeGetTime();		// 現在時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5秒経過
				// FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;		// FPSを計測した時刻を保存
				dwFrameCount = 0;					// フレームカウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 60分の1秒経過
				dwExecLastTime = dwCurrentTime;		// 処理開始時刻[現在時刻]を保存

				// 更新処理
				Update();
				
				// 描画処理
				Draw();

				dwFrameCount++;			// フレームカウントを加算
			}
		}
	}

	// 終了処理
	Uninit();

	// 分解能を戻す
	timeEndPeriod(1);

	// ウィンドウクラスの登録解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 返り値を送る
	return (int)msg.wParam;
}

//---------------------------------------------------------------------------
// ウィンドウプロシージャ
//---------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// 変数宣言
	int nID;	// 返り値を格納する

   //条件分岐
	switch (uMsg)
	{
	case WM_DESTROY:		// ウィンドウ破棄のメッセージ
		// WM_QUITへメッセージを送る
		PostQuitMessage(0);

		// 処理終了
		break;

	case WM_KEYDOWN:		// キー押したのメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:		 // [ESC]が押された
#ifdef _DEBUG
			DestroyWindow(hWnd);
#else
			// データを代入
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

			// 条件式が真の場合実行
			if (nID == IDYES)
			{
				// ウィンドウを破棄する(WM_DESTROYメッセージを送る)
				DestroyWindow(hWnd);
			}
#endif

			//処理終了
			break;
		}

		// 処理終了
		break;

	case WM_CLOSE: //閉じるボタンを押したメッセージ

		// データを代入
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

		// 条件式が真の場合実行
		if (nID == IDYES)
		{
			// ウィンドウを破棄する(WM_DESTROYメッセージを送る)
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;		// 0を返さないと終了してしまう
		}

		// 処理終了
		break;

	case WM_LBUTTONDOWN:	// マウス左クリックのメッセージ
		// ウィンドウにフォーカスを合わせる
		SetFocus(hWnd);

		// 処理終了
		break;

	}

	// 返り値を送る
	return DefWindowProc(hWnd, uMsg, wParam, lParam); //既存の処理を返す
}

//---------------------------------------------------------------------------
// 初期化処理
//---------------------------------------------------------------------------
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// 変数宣言
	D3DDISPLAYMODE				d3ddm;			// ディスプレイモード
	D3DPRESENT_PARAMETERS		d3dpp;			// プレゼンテーションパラメータ

	// Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	// 条件式が真の場合実行
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードの取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));		// パラメータのゼロクリア

	// アドレスの代入
	d3dpp.BackBufferWidth = SCREEN_WIDH;							// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;							// バックバッファの形式
	d3dpp.BackBufferCount = 1;										// バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;							// デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						// デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;										// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル

	// Direct3Dデバイスの生成
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		// Direct3Dデバイスの生成(描画処理と頂点処理をCPUで行う)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{// Direct3Dデバイスの生成(描画処理と頂点処理をCPUで行う)
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	// レンダ―ステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// サンプラーステ―トの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//テクスチャをリニア補完する
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//テクスチャをリニア補完する
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	// テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// デバック表示用のフォントの生成
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH, "Terminal", &g_pFont);

	// マウスカーソルの非表示
	ShowCursor(FALSE);

	// キーボードの初期化処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// ジョイパッドの初期化処理
	InitJoypad();

	// マウスの初期化
	InitMouse(hInstance, hWnd);

	//サウンド初期化処理
	InitSound(hWnd);

	//フェード初期化処理
	InitFade(g_mode);

	//ランキングリセット
	ResetRanking();

	return S_OK;
}

//---------------------------------------------------------------------------
// 終了処理
//---------------------------------------------------------------------------
void Uninit(void)
{
	// キーボードの終了処理
	UninitKeyboard();

	// ジョイパッドの終了処理
	UninitJoypad();

	// マウスの終了処理
	UninitMouse();

	//サウンドの終了処理
	UninitSound();

	//タイトル画面の終了処理
	UninitTitle();

	//チュートリアル画面の終了処理
	UninitTutorial();

	//ゲーム画面の終了処理
	UninitGame();

	//リザルト画面の終了処理
	UninitResult();

	//ランキング画面の終了処理
	UninitRanking();

	//フェード終了処理
	UninitFade();

	// デバック表示用フォントの破棄
	if (g_pFont != NULL)
	{
		g_pFont->Release();

		g_pFont = NULL;
	}

	// Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();

		g_pD3DDevice = NULL;
	}

	// Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();

		g_pD3D = NULL;
	}
}

//---------------------------------------------------------------------------
// 更新処理
//---------------------------------------------------------------------------
void Update(void)
{
	// キーボードの更新処理
	UpdateKeyboard();

	// ジョイパッドの更新処理
	UpdateJoypad();

	// マウスの更新処理
	UpdateMouse();

	//画面の更新
	switch (g_mode)
	{
	case MODE_TITLE:		//タイトル画面
		UpdateTitle();
		break;

	case MODE_TUTORIAL:		//チュートリアル画面
		UpdateTutorial();
		break;

	case MODE_GAME:			//ゲーム画面
		UpdateGame();
		break;

	case MODE_RESULT:		//リザルト画面
		UpdateResult();
		break;

	case MODE_RANKING:		//ランキング画面
		UpdateRanking();
		break;
	}

	//フェード更新処理
	UpdateFade();

	if (GetKeyboardTrigger(DIK_F1) == true || GetJoypadTrigger(JOYKEY_BACK) == true)
	{// [F1]キーが押されたか、ジョイパッドの[Back]が押された
		g_nJudgDebagText ^= 1;
	}

	if (GetKeyboardTrigger(DIK_F2) == true)
	{// [F2]キーが押されたか、ジョイパッドの[Back]が押された
		g_nUseWireFrame ^= 1;
	}

	if (g_nUseWireFrame == 1)
	{// ワイヤーフレームを使用している
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}

//---------------------------------------------------------------------------
// 描画処理
//---------------------------------------------------------------------------
void Draw(void)
{// 画面のクリア(バックバッファ&Zバッファのクリア)
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// 描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{// 描画開始が成功した場合
		// 画面の描画

		switch (g_mode)
		{
		case MODE_TITLE:		//タイトル画面
			DrawTitle();
			break;

		case MODE_TUTORIAL:		//チュートリアル画面
			DrawTutorial();
			break;

		case MODE_GAME:			//ゲーム画面
			DrawGame();
			break;

		case MODE_RESULT:		//リザルト画面
			DrawResult();
			break;

		case MODE_RANKING:		//ランキング画面
			DrawRanking();
			break;
		}

		//フェード描画処理
		DrawFade();
#ifdef _DEBUG
		if (g_nJudgDebagText == 0)
		{// デバック表示処理の判定用の変数が0の時
			// FPSの描画
			DrawFPS();
		}
#endif

		// 描画終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//*********************************************************************************
//モード設定
//*********************************************************************************
void SetMode(MODE mode)
{
	//現在の画面(モード)の終了処理
	switch (g_mode)
	{
	case MODE_TITLE:		//タイトル画面
		UninitTitle();
		break;

	case MODE_TUTORIAL:		//チュートリアル画面
		UninitTutorial();
		break;

	case MODE_GAME:			//ゲーム画面
		UninitGame();
		break;

	case MODE_RESULT:		//リザルト画面
		UninitResult();
		break;

	case MODE_RANKING:		//ランキング画面
		UninitRanking();
		break;
	}

	//新しい画面(モード)の初期化処理
	switch (mode)
	{
	case MODE_TITLE:		//タイトル画面
		InitTitle();
		break;

	case MODE_TUTORIAL:		//チュートリアル画面
		InitTutorial();
		break;

	case MODE_GAME:			//ゲーム画面
		InitGame();
		break;

	case MODE_RESULT:		//リザルト画面
		InitResult();
		break;

	case MODE_RANKING:		//ランキング画面
		InitRanking();
		break;
	}

	g_mode = mode;			//現在の画面モードを切り替える
}

//*********************************************************************************
//モードの取得
//*********************************************************************************
MODE GetMode(void)
{
	return g_mode;
}

//---------------------------------------------------------------------------
// デバイスの取得
//---------------------------------------------------------------------------
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//---------------------------------------------------------------------------
// FPSの表示
//---------------------------------------------------------------------------
void DrawFPS(void)
{
	// 変数宣言
	RECT rect = { 0,0,SCREEN_WIDH,SCREEN_HEIGHT };
	char aStr[1256];
	char aSrrCopy[256];

	// カメラ情報の取得
	Camera *pCamera = GetCamera();

	// モデル情報の取得
	Player *pPlayer = GetPlayer();

	// 文字列の代入
	wsprintf(&aStr[0], "FPS %d\n", g_nCountFPS);

	// カメラの視点
	strcat(&aStr[0], "*-----カメラの移動 [ W / A / S / D ]-----*\n");
	sprintf(&aSrrCopy[0], "  カメラの視点 | %0.1f | %0.1f | %0.1f |\n", pCamera->posV.x, pCamera->posV.y, pCamera->posV.z);
	strcat(&aStr[0], &aSrrCopy[0]);

	// カメラの注視点
	sprintf(&aSrrCopy[0], "  カメラの注視点 | %0.1f | %0.1f | %0.1f |\n", pCamera->posR.x, pCamera->posR.y, pCamera->posR.z);
	strcat(&aStr[0], &aSrrCopy[0]);

	// カメラの注視点までの向き
	sprintf(&aSrrCopy[0], "  注視点までの向き(θ) [Q / E | Z / C] | %0.3f\n", pCamera->rot.y);
	strcat(&aStr[0], &aSrrCopy[0]);
	sprintf(&aSrrCopy[0], "  注視点までの向き(φ) [Y / H | U / J] | %0.3f\n\n", pCamera->rot.x);
	strcat(&aStr[0], &aSrrCopy[0]);

	// モデルの位置
	strcat(&aStr[0], "*-----モデルの移動(前後左右) [ ↑ / ← / → / ↓ ]-----*\n");
	strcat(&aStr[0], "*-----モデルの移動(上下) [ I / K ]-----*\n");
	sprintf(&aSrrCopy[0], "  モデルの位置 | %0.1f | %0.1f | %0.1f |\n", pPlayer->pos.x, pPlayer->pos.y, pPlayer->pos.z);
	strcat(&aStr[0], &aSrrCopy[0]);
	sprintf(&aSrrCopy[0], "  モデルの向き | %0.2f | %0.2f | %0.2f |\n", pPlayer->rot.x, pPlayer->rot.y, pPlayer->rot.z);
	strcat(&aStr[0], &aSrrCopy[0]);
	strcat(&aStr[0], "弾の発射　[ SPACE ]\n");

	// テキスト描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//---------------------------------------------------------------------------
// ウィンドウハンドルの取得
//---------------------------------------------------------------------------
HWND GetWnd(void)
{
	return g_hWnd;
}