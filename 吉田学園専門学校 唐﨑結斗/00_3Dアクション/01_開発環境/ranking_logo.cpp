//**************************************************************************************************
//
//ランキングロゴの設定処理
//Auther：唐﨑結斗
//
//**************************************************************************************************
#include"main.h"
#include"ranking_logo.h"

//*******************************************************************************
//グローバル変数
//*******************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureRankingLogo = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingLogo = NULL;		//頂点バッファへのポインタ
RankingLogo g_RankingLogo;									//ランキングロゴ情報

//********************************************************************************
//ランキングロゴの初期化処理
//********************************************************************************
void InitRankingLogo(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//ポリゴンに張り付けるテクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ranking_logo.png",
		&g_pTextureRankingLogo);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									//頂点ファーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingLogo,
		NULL);

	//ランキングロゴ情報の初期化
	g_RankingLogo.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//中心点
	g_RankingLogo.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//中心点からの差
	g_RankingLogo.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向き
	g_RankingLogo.bUse = false;									//使用してない
														
	//頂点情報へのポインタを生成						
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankingLogo->Lock(0, 0, (void**)&pVtx, 0);

	//対角線の長さを算出する
	g_RankingLogo.fLength = sqrtf(((g_RankingLogo.offset.x * g_RankingLogo.offset.x) + (g_RankingLogo.offset.y * g_RankingLogo.offset.y)) / 2.0f);

	//対角線の角度を算出
	g_RankingLogo.fAngele = atan2f(g_RankingLogo.offset.x, g_RankingLogo.offset.y);

	//頂点座標の設定
	pVtx[0].pos.x = g_RankingLogo.pos.x + sinf(g_RankingLogo.rot.z + (D3DX_PI + g_RankingLogo.fAngele)) * g_RankingLogo.fLength;
	pVtx[0].pos.y = g_RankingLogo.pos.y + cosf(g_RankingLogo.rot.z + (D3DX_PI + g_RankingLogo.fAngele)) * g_RankingLogo.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_RankingLogo.pos.x + sinf(g_RankingLogo.rot.z + (D3DX_PI - g_RankingLogo.fAngele)) *  g_RankingLogo.fLength;
	pVtx[1].pos.y = g_RankingLogo.pos.y + cosf(g_RankingLogo.rot.z + (D3DX_PI - g_RankingLogo.fAngele)) *  g_RankingLogo.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_RankingLogo.pos.x + sinf(g_RankingLogo.rot.z - (0 + g_RankingLogo.fAngele)) * g_RankingLogo.fLength;
	pVtx[2].pos.y = g_RankingLogo.pos.y + cosf(g_RankingLogo.rot.z - (0 + g_RankingLogo.fAngele)) * g_RankingLogo.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_RankingLogo.pos.x + sinf(g_RankingLogo.rot.z - (0 - g_RankingLogo.fAngele)) *  g_RankingLogo.fLength;
	pVtx[3].pos.y = g_RankingLogo.pos.y + cosf(g_RankingLogo.rot.z - (0 - g_RankingLogo.fAngele)) *  g_RankingLogo.fLength;
	pVtx[3].pos.z = 0.0f;

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffRankingLogo->Unlock();
}

//********************************************************************************
//ランキングロゴの終了処理
//********************************************************************************
void UninitRankingLogo(void)
{
	//テクスチャの破棄	  
	if (g_pTextureRankingLogo != NULL)
	{
		g_pTextureRankingLogo->Release();

		g_pTextureRankingLogo = NULL;
	}

	//頂点バッファを破棄
	if (g_pVtxBuffRankingLogo != NULL)
	{
		g_pVtxBuffRankingLogo->Release();

		g_pVtxBuffRankingLogo = NULL;
	}
}

//********************************************************************************
//ランキングロゴの更新処理
//********************************************************************************
void UpdateRankingLogo(void)
{

}

//********************************************************************************
//ランキングロゴの描画処理
//********************************************************************************
void DrawRankingLogo(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRankingLogo, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_RankingLogo.bUse == true)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureRankingLogo);

		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//********************************************************************************
//ランキングロゴの設定処理
//********************************************************************************
void SetRankingLogo(void)
{
	//頂点情報へのポインタを生成						
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankingLogo->Lock(0, 0, (void**)&pVtx, 0);

	if (g_RankingLogo.bUse == false)
	{//使用されてない場合
		//ランキングロゴ情報の設定
		g_RankingLogo.offset = D3DXVECTOR3(MAX_OFFSET_RL_X, MAX_OFFSET_RL_Y, 0.0f);				//中心点からの差
		g_RankingLogo.pos = D3DXVECTOR3(SCREEN_WIDH / 2, 0.0f + g_RankingLogo.offset.y, 0.0f);	//中心点
		g_RankingLogo.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										//向き
		g_RankingLogo.bUse = true;																//使用してる

		//対角線の長さを算出する
		g_RankingLogo.fLength = sqrtf(((g_RankingLogo.offset.x * g_RankingLogo.offset.x) + (g_RankingLogo.offset.y * g_RankingLogo.offset.y)) / 2.0f);

		//対角線の角度を算出
		g_RankingLogo.fAngele = atan2f(g_RankingLogo.offset.x, g_RankingLogo.offset.y);

		//頂点座標の設定
		pVtx[0].pos.x = g_RankingLogo.pos.x + sinf(g_RankingLogo.rot.z + (D3DX_PI + g_RankingLogo.fAngele)) * g_RankingLogo.fLength;
		pVtx[0].pos.y = g_RankingLogo.pos.y + cosf(g_RankingLogo.rot.z + (D3DX_PI + g_RankingLogo.fAngele)) * g_RankingLogo.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_RankingLogo.pos.x + sinf(g_RankingLogo.rot.z + (D3DX_PI - g_RankingLogo.fAngele)) *  g_RankingLogo.fLength;
		pVtx[1].pos.y = g_RankingLogo.pos.y + cosf(g_RankingLogo.rot.z + (D3DX_PI - g_RankingLogo.fAngele)) *  g_RankingLogo.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_RankingLogo.pos.x + sinf(g_RankingLogo.rot.z - (0 + g_RankingLogo.fAngele)) * g_RankingLogo.fLength;
		pVtx[2].pos.y = g_RankingLogo.pos.y + cosf(g_RankingLogo.rot.z - (0 + g_RankingLogo.fAngele)) * g_RankingLogo.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_RankingLogo.pos.x + sinf(g_RankingLogo.rot.z - (0 - g_RankingLogo.fAngele)) *  g_RankingLogo.fLength;
		pVtx[3].pos.y = g_RankingLogo.pos.y + cosf(g_RankingLogo.rot.z - (0 - g_RankingLogo.fAngele)) *  g_RankingLogo.fLength;
		pVtx[3].pos.z = 0.0f;

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//頂点バッファをアンロック
	g_pVtxBuffRankingLogo->Unlock();
}