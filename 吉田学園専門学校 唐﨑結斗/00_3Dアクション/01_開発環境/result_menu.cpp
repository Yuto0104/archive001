//**************************************************************************************************
//
//ポーズ背景の設定処理
//Auther：唐﨑結斗
//
//**************************************************************************************************
#include"main.h"
#include"result_menu.h"
#include"input.h"

//*******************************************************************************
//グローバル変数
//*******************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureResultMenu = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultMenu = NULL;		//頂点バッファへのポインタ
ResultMenu g_ResultMenu;

//********************************************************************************
//ポーズ背景の初期化処理
//********************************************************************************
void InitResultMenu(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//ポリゴンに張り付けるテクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/リザルトメニュー.png",
		&g_pTextureResultMenu);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									//頂点ファーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultMenu,
		NULL);

	//タイトルロゴ情報の初期化
	g_ResultMenu.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//中心点
	g_ResultMenu.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//中心点からの差
	g_ResultMenu.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向き
	g_ResultMenu.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//カラー
	g_ResultMenu.bUse = false;								//使用してない

															//頂点情報へのポインタを生成						
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResultMenu->Lock(0, 0, (void**)&pVtx, 0);

	//対角線の長さを算出する
	g_ResultMenu.fLength = sqrtf(((g_ResultMenu.offset.x * g_ResultMenu.offset.x) + (g_ResultMenu.offset.y * g_ResultMenu.offset.y)) / 2.0f);

	//対角線の角度を算出
	g_ResultMenu.fAngele = atan2f(g_ResultMenu.offset.x, g_ResultMenu.offset.y);

	//頂点座標の設定
	pVtx[0].pos.x = g_ResultMenu.pos.x + sinf(g_ResultMenu.rot.z + (D3DX_PI + g_ResultMenu.fAngele)) * g_ResultMenu.fLength;
	pVtx[0].pos.y = g_ResultMenu.pos.y + cosf(g_ResultMenu.rot.z + (D3DX_PI + g_ResultMenu.fAngele)) * g_ResultMenu.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_ResultMenu.pos.x + sinf(g_ResultMenu.rot.z + (D3DX_PI - g_ResultMenu.fAngele)) *  g_ResultMenu.fLength;
	pVtx[1].pos.y = g_ResultMenu.pos.y + cosf(g_ResultMenu.rot.z + (D3DX_PI - g_ResultMenu.fAngele)) *  g_ResultMenu.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_ResultMenu.pos.x + sinf(g_ResultMenu.rot.z - (0 + g_ResultMenu.fAngele)) * g_ResultMenu.fLength;
	pVtx[2].pos.y = g_ResultMenu.pos.y + cosf(g_ResultMenu.rot.z - (0 + g_ResultMenu.fAngele)) * g_ResultMenu.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_ResultMenu.pos.x + sinf(g_ResultMenu.rot.z - (0 - g_ResultMenu.fAngele)) *  g_ResultMenu.fLength;
	pVtx[3].pos.y = g_ResultMenu.pos.y + cosf(g_ResultMenu.rot.z - (0 - g_ResultMenu.fAngele)) *  g_ResultMenu.fLength;
	pVtx[3].pos.z = 0.0f;

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = g_ResultMenu.col;
	pVtx[1].col = g_ResultMenu.col;
	pVtx[2].col = g_ResultMenu.col;
	pVtx[3].col = g_ResultMenu.col;

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffResultMenu->Unlock();
}

//********************************************************************************
//ポーズ背景の終了処理
//********************************************************************************
void UninitResultMenu(void)
{
	//テクスチャの破棄	  
	if (g_pTextureResultMenu != NULL)
	{
		g_pTextureResultMenu->Release();

		g_pTextureResultMenu = NULL;
	}

	//頂点バッファを破棄
	if (g_pVtxBuffResultMenu != NULL)
	{
		g_pVtxBuffResultMenu->Release();

		g_pVtxBuffResultMenu = NULL;
	}
}

//********************************************************************************
//ポーズ背景の更新処理
//********************************************************************************
void UpdateResultMenu(void)
{

}

//********************************************************************************
//ポーズ背景の描画処理
//********************************************************************************
void DrawResultMenu(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResultMenu, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// αテストを使用する
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// αテストの設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	if (g_ResultMenu.bUse == true)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureResultMenu);

		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	// αテストの終了
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//********************************************************************************
//ポーズ背景の設定処理
//********************************************************************************
void SetResultMenu(void)
{
	//頂点情報へのポインタを生成						
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResultMenu->Lock(0, 0, (void**)&pVtx, 0);

	if (g_ResultMenu.bUse == false)
	{//使用されてない場合
	 //タイトルロゴ情報の設定
		g_ResultMenu.offset = D3DXVECTOR3(MAX_OFFSET_RM_X, MAX_OFFSET_RM_Y, 0.0f);			//中心点からの差
		g_ResultMenu.pos = D3DXVECTOR3(300.0f, 420.0f, 0.0f);								//中心点
		g_ResultMenu.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//向き
		g_ResultMenu.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);								//カラー
		g_ResultMenu.bUse = true;															//使用してる

																						//対角線の長さを算出する
		g_ResultMenu.fLength = sqrtf(((g_ResultMenu.offset.x * g_ResultMenu.offset.x) + (g_ResultMenu.offset.y * g_ResultMenu.offset.y)) / 2.0f);

		//対角線の角度を算出
		g_ResultMenu.fAngele = atan2f(g_ResultMenu.offset.x, g_ResultMenu.offset.y);

		//頂点座標の設定
		pVtx[0].pos.x = g_ResultMenu.pos.x + sinf(g_ResultMenu.rot.z + (D3DX_PI + g_ResultMenu.fAngele)) * g_ResultMenu.fLength;
		pVtx[0].pos.y = g_ResultMenu.pos.y + cosf(g_ResultMenu.rot.z + (D3DX_PI + g_ResultMenu.fAngele)) * g_ResultMenu.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_ResultMenu.pos.x + sinf(g_ResultMenu.rot.z + (D3DX_PI - g_ResultMenu.fAngele)) *  g_ResultMenu.fLength;
		pVtx[1].pos.y = g_ResultMenu.pos.y + cosf(g_ResultMenu.rot.z + (D3DX_PI - g_ResultMenu.fAngele)) *  g_ResultMenu.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_ResultMenu.pos.x + sinf(g_ResultMenu.rot.z - (0 + g_ResultMenu.fAngele)) * g_ResultMenu.fLength;
		pVtx[2].pos.y = g_ResultMenu.pos.y + cosf(g_ResultMenu.rot.z - (0 + g_ResultMenu.fAngele)) * g_ResultMenu.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_ResultMenu.pos.x + sinf(g_ResultMenu.rot.z - (0 - g_ResultMenu.fAngele)) *  g_ResultMenu.fLength;
		pVtx[3].pos.y = g_ResultMenu.pos.y + cosf(g_ResultMenu.rot.z - (0 - g_ResultMenu.fAngele)) *  g_ResultMenu.fLength;
		pVtx[3].pos.z = 0.0f;

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = g_ResultMenu.col;
		pVtx[1].col = g_ResultMenu.col;
		pVtx[2].col = g_ResultMenu.col;
		pVtx[3].col = g_ResultMenu.col;

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//頂点バッファをアンロック
	g_pVtxBuffResultMenu->Unlock();
}