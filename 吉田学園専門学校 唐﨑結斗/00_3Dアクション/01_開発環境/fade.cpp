//**************************************************************************************************
//
// フェード処理
// Auther：唐�ｱ結斗
//
//**************************************************************************************************
#include"fade.h"
#include"main.h"

//*******************************************************************************
// マクロ定義
//*******************************************************************************
#define	MAX_COUNT_FADE		(60)

//*******************************************************************************
// グローバル変数
//*******************************************************************************
/*LPDIRECT3DTEXTURE9 g_pTextureFade = NULL*/;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffFade = NULL;		// 頂点バッファへのポインタ
FADE						g_fade;						// フェード状態
MODE						g_modeNext;					// 次の画面モード
D3DXCOLOR					g_colorFade;				// ポリゴン(フェード)の色

//********************************************************************************
// フェードの初期化処理
//********************************************************************************
void InitFade(MODE modeNext)
{
	// データの代入
	g_modeNext = modeNext;

	// フェードインにする
	g_fade = FADE_IN;

	// ポリゴンを黒(不透明)にしておく
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	////ポリゴンに張り付けるテクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,
	//	"data/TEXTURE/FadeBlack000.png",
	//	&g_pTextureFade);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// 頂点ファーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	// 頂点情報へのポインタを生成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffFade->Unlock();

	// 画面モードの設定
	SetMode(modeNext);
}

//********************************************************************************
// フェードの終了処理
//********************************************************************************
void UninitFade(void)
{
	////テクスチャの破棄	  
	//if (g_pTextureFade != NULL)
	//{
	//	g_pTextureFade->Release();

	//	g_pTextureFade = NULL;
	//}

	// 頂点バッファを破棄
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();

		g_pVtxBuffFade = NULL;
	}
}

//********************************************************************************
// フェードの更新処理
//********************************************************************************
void UpdateFade(void)
{
	if (g_fade != FADE_NONE)
	{// フェードが行われている
		if (g_fade == FADE_IN)
		{// フェードイン状態

			// ポリゴンを透明にしていく
			g_colorFade.a -= (1.0f / MAX_COUNT_FADE);

			if (g_colorFade.a <= 0.0f)
			{
				// ポリゴンの色の設定
				g_colorFade.a = 0.0f;

				// フェード状態の切り替え
				g_fade = FADE_NONE;
			}
		}
		else if (g_fade == FADE_OUT)
		{// フェードアウト状態

			// ポリゴンを透明にしていく
			g_colorFade.a += (1.0f / MAX_COUNT_FADE);

			if (g_colorFade.a >= 1.0f)
			{
				// ポリゴンの色の設定
				g_colorFade.a = 1.0f;

				// フェード状態の切り替え
				g_fade = FADE_IN;

				// 画面モードの設定
				SetMode(g_modeNext);
			}
		}

		// 頂点情報へのポインタを生成
		VERTEX_2D *pVtx;

		// 頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点カラーの設定
		pVtx[0].col = g_colorFade;
		pVtx[1].col = g_colorFade;
		pVtx[2].col = g_colorFade;
		pVtx[3].col = g_colorFade;

		// 頂点バッファをアンロック
		g_pVtxBuffFade->Unlock();
	}
}

//********************************************************************************
// フェードの描画処理
//********************************************************************************
void DrawFade(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//********************************************************************************
// フェードの設定処理
//********************************************************************************
void SetFade(MODE modeNext)
{
	// データの代入
	g_modeNext = modeNext;

	// フェードインにする
	g_fade = FADE_OUT;

	// ポリゴンを黒(透明)にしておく
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//********************************************************************************
// フェードの取得
//********************************************************************************
FADE GetFade(void)
{
	return g_fade;
}