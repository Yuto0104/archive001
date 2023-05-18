//**************************************************************************************************
//
//ポーズ背景の設定処理
//Auther：唐﨑結斗
//
//**************************************************************************************************
#include"main.h"
#include"result bg.h"
#include"input.h"

//*******************************************************************************
//グローバル変数
//*******************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureResultBG = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultBG = NULL;		//頂点バッファへのポインタ
ResultBG g_ResultBG;

//********************************************************************************
//ポーズ背景の初期化処理
//********************************************************************************
void InitResultBG(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//ポリゴンに張り付けるテクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RESULT.png",
		&g_pTextureResultBG);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									//頂点ファーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultBG,
		NULL);

	//タイトルロゴ情報の初期化
	g_ResultBG.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//中心点
	g_ResultBG.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//中心点からの差
	g_ResultBG.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向き
	g_ResultBG.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//カラー
	g_ResultBG.bUse = false;								//使用してない

	//頂点情報へのポインタを生成						
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResultBG->Lock(0, 0, (void**)&pVtx, 0);

	//対角線の長さを算出する
	g_ResultBG.fLength = sqrtf(((g_ResultBG.offset.x * g_ResultBG.offset.x) + (g_ResultBG.offset.y * g_ResultBG.offset.y)) / 2.0f);

	//対角線の角度を算出
	g_ResultBG.fAngele = atan2f(g_ResultBG.offset.x, g_ResultBG.offset.y);

	//頂点座標の設定
	pVtx[0].pos.x = g_ResultBG.pos.x + sinf(g_ResultBG.rot.z + (D3DX_PI + g_ResultBG.fAngele)) * g_ResultBG.fLength;
	pVtx[0].pos.y = g_ResultBG.pos.y + cosf(g_ResultBG.rot.z + (D3DX_PI + g_ResultBG.fAngele)) * g_ResultBG.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_ResultBG.pos.x + sinf(g_ResultBG.rot.z + (D3DX_PI - g_ResultBG.fAngele)) *  g_ResultBG.fLength;
	pVtx[1].pos.y = g_ResultBG.pos.y + cosf(g_ResultBG.rot.z + (D3DX_PI - g_ResultBG.fAngele)) *  g_ResultBG.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_ResultBG.pos.x + sinf(g_ResultBG.rot.z - (0 + g_ResultBG.fAngele)) * g_ResultBG.fLength;
	pVtx[2].pos.y = g_ResultBG.pos.y + cosf(g_ResultBG.rot.z - (0 + g_ResultBG.fAngele)) * g_ResultBG.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_ResultBG.pos.x + sinf(g_ResultBG.rot.z - (0 - g_ResultBG.fAngele)) *  g_ResultBG.fLength;
	pVtx[3].pos.y = g_ResultBG.pos.y + cosf(g_ResultBG.rot.z - (0 - g_ResultBG.fAngele)) *  g_ResultBG.fLength;
	pVtx[3].pos.z = 0.0f;

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = g_ResultBG.col;
	pVtx[1].col = g_ResultBG.col;
	pVtx[2].col = g_ResultBG.col;
	pVtx[3].col = g_ResultBG.col;

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffResultBG->Unlock();
}

//********************************************************************************
//ポーズ背景の終了処理
//********************************************************************************
void UninitResultBG(void)
{
	//テクスチャの破棄	  
	if (g_pTextureResultBG != NULL)
	{
		g_pTextureResultBG->Release();

		g_pTextureResultBG = NULL;
	}

	//頂点バッファを破棄
	if (g_pVtxBuffResultBG != NULL)
	{
		g_pVtxBuffResultBG->Release();

		g_pVtxBuffResultBG = NULL;
	}
}

//********************************************************************************
//ポーズ背景の更新処理
//********************************************************************************
void UpdateResultBG(void)
{

}

//********************************************************************************
//ポーズ背景の描画処理
//********************************************************************************
void DrawResultBG(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResultBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// αテストを使用する
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// αテストの設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	if (g_ResultBG.bUse == true)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureResultBG);

		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	// αテストの終了
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//********************************************************************************
//ポーズ背景の設定処理
//********************************************************************************
void SetResultBG(void)
{
	//頂点情報へのポインタを生成						
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResultBG->Lock(0, 0, (void**)&pVtx, 0);

	if (g_ResultBG.bUse == false)
	{//使用されてない場合
	 //タイトルロゴ情報の設定
		g_ResultBG.offset = D3DXVECTOR3(MAX_OFFSET_RBG_X, MAX_OFFSET_RBG_Y, 0.0f);		//中心点からの差
		g_ResultBG.pos = D3DXVECTOR3(SCREEN_WIDH / 2, 120.0f, 0.0f);					//中心点
		g_ResultBG.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//向き
		g_ResultBG.col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);								//カラー
		g_ResultBG.bUse = true;															//使用してる

		//対角線の長さを算出する
		g_ResultBG.fLength = sqrtf(((g_ResultBG.offset.x * g_ResultBG.offset.x) + (g_ResultBG.offset.y * g_ResultBG.offset.y)) / 2.0f);

		//対角線の角度を算出
		g_ResultBG.fAngele = atan2f(g_ResultBG.offset.x, g_ResultBG.offset.y);

		//頂点座標の設定
		pVtx[0].pos.x = g_ResultBG.pos.x + sinf(g_ResultBG.rot.z + (D3DX_PI + g_ResultBG.fAngele)) * g_ResultBG.fLength;
		pVtx[0].pos.y = g_ResultBG.pos.y + cosf(g_ResultBG.rot.z + (D3DX_PI + g_ResultBG.fAngele)) * g_ResultBG.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_ResultBG.pos.x + sinf(g_ResultBG.rot.z + (D3DX_PI - g_ResultBG.fAngele)) *  g_ResultBG.fLength;
		pVtx[1].pos.y = g_ResultBG.pos.y + cosf(g_ResultBG.rot.z + (D3DX_PI - g_ResultBG.fAngele)) *  g_ResultBG.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_ResultBG.pos.x + sinf(g_ResultBG.rot.z - (0 + g_ResultBG.fAngele)) * g_ResultBG.fLength;
		pVtx[2].pos.y = g_ResultBG.pos.y + cosf(g_ResultBG.rot.z - (0 + g_ResultBG.fAngele)) * g_ResultBG.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_ResultBG.pos.x + sinf(g_ResultBG.rot.z - (0 - g_ResultBG.fAngele)) *  g_ResultBG.fLength;
		pVtx[3].pos.y = g_ResultBG.pos.y + cosf(g_ResultBG.rot.z - (0 - g_ResultBG.fAngele)) *  g_ResultBG.fLength;
		pVtx[3].pos.z = 0.0f;

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = g_ResultBG.col;
		pVtx[1].col = g_ResultBG.col;
		pVtx[2].col = g_ResultBG.col;
		pVtx[3].col = g_ResultBG.col;

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//頂点バッファをアンロック
	g_pVtxBuffResultBG->Unlock();
}