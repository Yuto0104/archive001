//**************************************************************************************************
//
//ポーズ処理の設定処理
//Auther：唐﨑結斗
//
//**************************************************************************************************
#include"main.h"
#include"pause.h"
#include"input.h"
#include"sound.h"
#include"fade.h"
#include"pause bg.h"
#include"continue.h"
#include"retry.h"
#include"quit.h"

//********************************************************************************
//グローバル変数
//********************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;		//頂点バッファへのポインタ
Pause g_Pause;										//ポーズ情報の取得
D3DXCOLOR g_colorPause;								//ポリゴンの色

//********************************************************************************
//ポーズ処理の初期化処理
//********************************************************************************
void InitPause(void)
{
	//ポーズ情報の初期化
	g_Pause.bDisp = false;					//表示しない
	g_Pause.state = NEXTPROCESS_CONTINUE;	//ゲーム画面(継続)
	g_Pause.nCountKey = 0;					//キーが押された回数

	//ポリゴンを黒(不透明)にしておく
	g_colorPause = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									//頂点ファーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	//頂点情報へのポインタを生成
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = g_colorPause;
	pVtx[1].col = g_colorPause;
	pVtx[2].col = g_colorPause;
	pVtx[3].col = g_colorPause;

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffPause->Unlock();

	//ポーズ背景の初期化処理
	InitPauseBG();

	//コンティニューの初期化処理
	InitContinue();

	//リトライの初期化処理
	InitRetry();

	//クイットの初期化処理
	InitQuit();
}

//********************************************************************************
//ポーズ処理の終了処理
//********************************************************************************
void UninitPause(void)
{
	//頂点バッファを破棄
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();

		g_pVtxBuffPause = NULL;
	}

	//ポーズ背景の終了処理
	UninitPauseBG();

	//コンティニューの終了処理
	UninitContinue();

	//リトライの終了処理
	UninitRetry();

	//クイットの終了処理
	UninitQuit();
}

//********************************************************************************
//ポーズ処理の更新処理
//********************************************************************************
void UpdatePause(void)
{
	//フェード情報の取得
	FADE fade;			//フェード情報へのポインタ
	fade = GetFade();

	if (g_Pause.bDisp == true)
	{//表示されてる
		if (GetKeyboardTrigger(DIK_W) == true || GetJoypadTrigger(JOYKEY_UP) == true)
		{//[W]キーが押された
			g_Pause.nCountKey--;

			//サウンド再生
			PlaySound(SOUND_LABEL_SE_SELECT);

			if (g_Pause.nCountKey < 0)
			{//0より小さい場合
				g_Pause.nCountKey = 2;
			}
		}
		if (GetKeyboardTrigger(DIK_S) == true || GetJoypadTrigger(JOYKEY_DOWN) == true)
		{//[S]キーが押された
			g_Pause.nCountKey++;

			//サウンド再生
			PlaySound(SOUND_LABEL_SE_SELECT);

			if (g_Pause.nCountKey >= 3)
			{//3以上の場合
				g_Pause.nCountKey = 0;
			}
		}

		//次の処理
		switch (g_Pause.nCountKey)
		{
		case 0:
			g_Pause.state = NEXTPROCESS_CONTINUE;	//ゲーム画面(継続)
			break;

		case 1:
			g_Pause.state = NEXTPROCESS_RETRY;		//ゲーム画面(最初から)
			break;

		case 2:
			g_Pause.state = NEXTPROCESS_QUIT;		//タイトル画面
			break;
		}

		if (GetKeyboardTrigger(DIK_C) == true)
		{//[C]キーが押された
			g_Pause.state = NEXTPROCESS_CONTINUE;	//ゲーム画面(継続)

			//サウンド再生
			PlaySound(SOUND_LABEL_SE_SELECT);
		}
		else if (GetKeyboardTrigger(DIK_R) == true)
		{//[R]キーが押された
			g_Pause.state = NEXTPROCESS_RETRY;		//ゲーム画面(最初から)

			//サウンド再生
			PlaySound(SOUND_LABEL_SE_SELECT);
		}
		else if (GetKeyboardTrigger(DIK_Q) == true)
		{//[Q]キーが押された
			g_Pause.state = NEXTPROCESS_QUIT;		//タイトル画面

			//サウンド再生
			PlaySound(SOUND_LABEL_SE_SELECT);
		}
		else if (GetKeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_START) == true)
		{//[P]キーが押された
			//ポーズ情報の初期化
			g_Pause.state = NEXTPROCESS_CONTINUE;	//ゲーム画面(継続)
			g_Pause.bDisp = false;					//表示しない
		}

		if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true)
		{//[Enter]キーが押された

			//次の処理
			switch (g_Pause.state)
			{
			case NEXTPROCESS_CONTINUE:

				//ポーズ情報の初期化
				g_Pause.bDisp = false;					//表示しない
				g_Pause.state = NEXTPROCESS_CONTINUE;	//ゲーム画面(継続)
				break;

			case NEXTPROCESS_RETRY:
				
				if (fade == FADE_NONE)
				{//フェードが行われてないとき
					//フェード設定処理
					SetFade(MODE_GAME);
				}
				break;

			case NEXTPROCESS_QUIT:

				if (fade == FADE_NONE)
				{//フェードが行われてないとき
					//フェード設定処理
					SetFade(MODE_TITLE);
				}
				break;
			}
		}

		//ポーズ背景の更新処理
		UpdatePauseBG();

		//コンティニューの更新処理
		UpdateContinue();

		//リトライの更新処理4
		UpdateRetry();

		//クイットの更新処理
		UpdateQuit();
	}
}

//********************************************************************************
//ポーズ処理の描画処理
//********************************************************************************
void DrawPause(void)
{
	if (g_Pause.bDisp == true)
	{//表示されてる

		//デバイスへのポインタ
		LPDIRECT3DDEVICE9 pDevice;

		//デバイスの取得
		pDevice = GetDevice();

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, NULL);

		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//ポーズ背景の描画処理
		DrawPauseBG();

		//コンティニューの描画処理
		DrawContinue();

		//リトライの描画処理
		DrawRetry();

		//クイットの描画処理
		DrawQuit();
	}
}

//********************************************************************************
//ポーズ処理の設定処理
//********************************************************************************
void SetPause(void)
{
	if (g_Pause.bDisp == false)
	{//表示されてる
		//ポーズ情報の設定
		g_Pause.bDisp = true;					//表示する
		g_Pause.state = NEXTPROCESS_CONTINUE;	//ゲーム画面(継続)
		g_Pause.nCountKey = 0;					//キーが押された回数

		//ポリゴンを黒(不透明)にしておく
		g_colorPause = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);

		//デバイスへのポインタ
		LPDIRECT3DDEVICE9 pDevice;

		//デバイスの取得
		pDevice = GetDevice();

		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//確保するバッファサイズ
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,									//頂点ファーマット
			D3DPOOL_MANAGED,
			&g_pVtxBuffPause,
			NULL);

		//頂点情報へのポインタを生成
		VERTEX_2D *pVtx;

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDH, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDH, SCREEN_HEIGHT, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = g_colorPause;
		pVtx[1].col = g_colorPause;
		pVtx[2].col = g_colorPause;
		pVtx[3].col = g_colorPause;

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファをアンロック
		g_pVtxBuffPause->Unlock();

		//ポーズ背景の設定
		SetPauseBG();

		//コンティニューの設定
		SetContinue();

		//リトライの設定
		SetRetry();

		//クワイエットの設定
		SetQuit();
	}
}

//********************************************************************************
//ポーズ情報の取得処理
//********************************************************************************
Pause *GetPause(void)
{
	return &g_Pause;
}