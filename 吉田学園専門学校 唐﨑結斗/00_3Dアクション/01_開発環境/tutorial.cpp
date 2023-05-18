//**************************************************************************************************
//
// チュートリアル処理
// Auther：唐﨑結斗
//
//**************************************************************************************************
#include"tutorial.h"
#include"main.h"
#include"press enter.h"
#include"sound.h"
#include"input.h"
#include"calculation.h"

//*******************************************************************************
// マクロ定義
//*******************************************************************************
#define		MAX_ANIMPATTEN_TUTORIAL			(2)		// アニメーションパターンの最大値 

//*******************************************************************************
// グローバル変数
//*******************************************************************************
static LPDIRECT3DTEXTURE9			g_pTextureTutorial = NULL;			// テクスチャへのポインタ
static LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffTutorial = NULL;			// 頂点バッファへのポインタ
static float						g_nMaxAnimU;						// テクスチャのX軸の最大値 

//********************************************************************************
// チュートリアルの初期化処理
//********************************************************************************
void InitTutorial(void)
{
	// グローバル変数の設定
	g_nMaxAnimU = 1.0f / MAX_ANIMPATTEN_TUTORIAL;

	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// ポリゴンに張り付けるテクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/チュートリアル画面.png",
		&g_pTextureTutorial);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// 頂点ファーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	// 頂点情報へのポインタを生成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標
	SetVtxTexture(pVtx, 1.0f, 1.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffTutorial->Unlock();

	// プレスエンターの初期化処理
	InitPressEnter();

	// プレスエンターの設定処理
	SetPressEnter(D3DXVECTOR3(1180.0f, 700.0f, 0.0f), D3DXVECTOR3(MAX_OFFSET_PE_X / 2, MAX_OFFSET_PE_Y / 2, 0.0f));

	//サウンド再生
	PlaySound(SOUND_LABEL_BGM004);
}

//********************************************************************************
// チュートリアルの終了処理
//********************************************************************************
void UninitTutorial(void)
{
	//サウンド終了処理
	StopSound();

	// プレスエンターの終了処理
	UninitPressEnter();

	// テクスチャの破棄	  
	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();

		g_pTextureTutorial = NULL;
	}

	// 頂点バッファを破棄
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();

		g_pVtxBuffTutorial = NULL;
	}
}

//********************************************************************************
// チュートリアルの更新処理
//********************************************************************************
void UpdateTutorial(void)
{
	// 変数宣言
	int nPage = 0;

	//// ジョイパッドの使用情報の取得
	//bool bUseJoyPad = GetUseJoyPad();

	//if (bUseJoyPad == true)
	//{// 使用されてる場合
	//	nPage = 1;
	//}

	// 頂点情報へのポインタを生成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	// プレスエンターの更新処理
	UpdatePressEnter();

	// 頂点バッファをアンロック
	g_pVtxBuffTutorial->Unlock();
}

//********************************************************************************
// チュートリアルの描画処理
//********************************************************************************
void DrawTutorial(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTutorial);

	// ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// プレスエンターの描画処理
	DrawPressEnter();
}