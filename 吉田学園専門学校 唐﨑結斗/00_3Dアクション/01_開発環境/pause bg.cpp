//**************************************************************************************************
//
// ポーズ背景の設定処理
// Auther：唐﨑結斗
//
//**************************************************************************************************
#include"main.h"
#include"pause bg.h"
#include"input.h"

//*******************************************************************************
// グローバル変数
//*******************************************************************************
LPDIRECT3DTEXTURE9			g_pTexturePauseBG = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffPauseBG = NULL;			// 頂点バッファへのポインタ
PauseBG						g_PauseBG;

//********************************************************************************
// ポーズ背景の初期化処理
//********************************************************************************
void InitPauseBG(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// ポリゴンに張り付けるテクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/pause100.png",
		&g_pTexturePauseBG);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,								   
		FVF_VERTEX_2D,									// 頂点ファーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseBG,
		NULL);

	// タイトルロゴ情報の初期化
	g_PauseBG.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 中心点
	g_PauseBG.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 中心点からの差
	g_PauseBG.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向き
	g_PauseBG.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// カラー
	g_PauseBG.bUse = false;									// 使用してない
														
	// 頂点情報へのポインタを生成						
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseBG->Lock(0, 0, (void**)&pVtx, 0);

	// 対角線の長さを算出する
	g_PauseBG.fLength = sqrtf(((g_PauseBG.offset.x * g_PauseBG.offset.x) + (g_PauseBG.offset.y * g_PauseBG.offset.y)) / 2.0f);

	// 対角線の角度を算出
	g_PauseBG.fAngele = atan2f(g_PauseBG.offset.x, g_PauseBG.offset.y);

	// 頂点座標の設定
	pVtx[0].pos.x = g_PauseBG.pos.x + sinf(g_PauseBG.rot.z + (D3DX_PI + g_PauseBG.fAngele)) * g_PauseBG.fLength;
	pVtx[0].pos.y = g_PauseBG.pos.y + cosf(g_PauseBG.rot.z + (D3DX_PI + g_PauseBG.fAngele)) * g_PauseBG.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_PauseBG.pos.x + sinf(g_PauseBG.rot.z + (D3DX_PI - g_PauseBG.fAngele)) *  g_PauseBG.fLength;
	pVtx[1].pos.y = g_PauseBG.pos.y + cosf(g_PauseBG.rot.z + (D3DX_PI - g_PauseBG.fAngele)) *  g_PauseBG.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_PauseBG.pos.x + sinf(g_PauseBG.rot.z - (0 + g_PauseBG.fAngele)) * g_PauseBG.fLength;
	pVtx[2].pos.y = g_PauseBG.pos.y + cosf(g_PauseBG.rot.z - (0 + g_PauseBG.fAngele)) * g_PauseBG.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_PauseBG.pos.x + sinf(g_PauseBG.rot.z - (0 - g_PauseBG.fAngele)) *  g_PauseBG.fLength;
	pVtx[3].pos.y = g_PauseBG.pos.y + cosf(g_PauseBG.rot.z - (0 - g_PauseBG.fAngele)) *  g_PauseBG.fLength;
	pVtx[3].pos.z = 0.0f;

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = g_PauseBG.col;
	pVtx[1].col = g_PauseBG.col;
	pVtx[2].col = g_PauseBG.col;
	pVtx[3].col = g_PauseBG.col;

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffPauseBG->Unlock();
}

//********************************************************************************
// ポーズ背景の終了処理
//********************************************************************************
void UninitPauseBG(void)
{
	// テクスチャの破棄	  
	if (g_pTexturePauseBG != NULL)
	{
		g_pTexturePauseBG->Release();

		g_pTexturePauseBG = NULL;
	}

	// 頂点バッファを破棄
	if (g_pVtxBuffPauseBG != NULL)
	{
		g_pVtxBuffPauseBG->Release();

		g_pVtxBuffPauseBG = NULL;
	}
}

//********************************************************************************
// ポーズ背景の更新処理
//********************************************************************************
void UpdatePauseBG(void)
{

}

//********************************************************************************
// ポーズ背景の描画処理
//********************************************************************************
void DrawPauseBG(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseBG, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_PauseBG.bUse == true)
	{// テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePauseBG);

		// ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//********************************************************************************
// ポーズ背景の設定処理
//********************************************************************************
void SetPauseBG(void)
{
	// 頂点情報へのポインタを生成						
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseBG->Lock(0, 0, (void**)&pVtx, 0);

	if (g_PauseBG.bUse == false)
	{// 使用されてない場合
		// タイトルロゴ情報の設定
		g_PauseBG.offset = D3DXVECTOR3(MAX_OFFSET_PBG_X, MAX_OFFSET_PBG_Y, 0.0f);		// 中心点からの差
		g_PauseBG.pos = D3DXVECTOR3(SCREEN_WIDH / 2, SCREEN_HEIGHT / 2, 0.0f);			// 中心点
		g_PauseBG.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									// 向き
		g_PauseBG.col = D3DXCOLOR(0.5f, 0.5f, 1.0f, 0.5f);								// カラー
		g_PauseBG.bUse = true;															// 使用してる

		// 対角線の長さを算出する
		g_PauseBG.fLength = sqrtf(((g_PauseBG.offset.x * g_PauseBG.offset.x) + (g_PauseBG.offset.y * g_PauseBG.offset.y)) / 2.0f);

		// 対角線の角度を算出
		g_PauseBG.fAngele = atan2f(g_PauseBG.offset.x, g_PauseBG.offset.y);

		// 頂点座標の設定
		pVtx[0].pos.x = g_PauseBG.pos.x + sinf(g_PauseBG.rot.z + (D3DX_PI + g_PauseBG.fAngele)) * g_PauseBG.fLength;
		pVtx[0].pos.y = g_PauseBG.pos.y + cosf(g_PauseBG.rot.z + (D3DX_PI + g_PauseBG.fAngele)) * g_PauseBG.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_PauseBG.pos.x + sinf(g_PauseBG.rot.z + (D3DX_PI - g_PauseBG.fAngele)) *  g_PauseBG.fLength;
		pVtx[1].pos.y = g_PauseBG.pos.y + cosf(g_PauseBG.rot.z + (D3DX_PI - g_PauseBG.fAngele)) *  g_PauseBG.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_PauseBG.pos.x + sinf(g_PauseBG.rot.z - (0 + g_PauseBG.fAngele)) * g_PauseBG.fLength;
		pVtx[2].pos.y = g_PauseBG.pos.y + cosf(g_PauseBG.rot.z - (0 + g_PauseBG.fAngele)) * g_PauseBG.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_PauseBG.pos.x + sinf(g_PauseBG.rot.z - (0 - g_PauseBG.fAngele)) *  g_PauseBG.fLength;
		pVtx[3].pos.y = g_PauseBG.pos.y + cosf(g_PauseBG.rot.z - (0 - g_PauseBG.fAngele)) *  g_PauseBG.fLength;
		pVtx[3].pos.z = 0.0f;

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = g_PauseBG.col;
		pVtx[1].col = g_PauseBG.col;
		pVtx[2].col = g_PauseBG.col;
		pVtx[3].col = g_PauseBG.col;

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// 頂点バッファをアンロック
	g_pVtxBuffPauseBG->Unlock();
}