//**************************************************************************************************
//
//リトライの設定処理
//Auther：唐﨑結斗
//
//**************************************************************************************************
#include"main.h"
#include"retry.h"
#include"input.h"
#include"pause.h"

//*******************************************************************************
//グローバル変数
//*******************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureRetry = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRetry = NULL;		//頂点バッファへのポインタ
Retry g_Retry;

//********************************************************************************
//リトライの初期化処理
//********************************************************************************
void InitRetry(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//ポリゴンに張り付けるテクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/pause001.png",
		&g_pTextureRetry);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									//頂点ファーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffRetry,
		NULL);

	//タイトルロゴ情報の初期化
	g_Retry.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//中心点
	g_Retry.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//中心点からの差
	g_Retry.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向き
	g_Retry.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//カラー
	g_Retry.bUse = false;									//使用してない

	//頂点情報へのポインタを生成						
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRetry->Lock(0, 0, (void**)&pVtx, 0);

	//対角線の長さを算出する
	g_Retry.fLength = sqrtf(((g_Retry.offset.x * g_Retry.offset.x) + (g_Retry.offset.y * g_Retry.offset.y)) / 2.0f);

	//対角線の角度を算出
	g_Retry.fAngele = atan2f(g_Retry.offset.x, g_Retry.offset.y);

	//頂点座標の設定
	pVtx[0].pos.x = g_Retry.pos.x + sinf(g_Retry.rot.z + (D3DX_PI + g_Retry.fAngele)) * g_Retry.fLength;
	pVtx[0].pos.y = g_Retry.pos.y + cosf(g_Retry.rot.z + (D3DX_PI + g_Retry.fAngele)) * g_Retry.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Retry.pos.x + sinf(g_Retry.rot.z + (D3DX_PI - g_Retry.fAngele)) *  g_Retry.fLength;
	pVtx[1].pos.y = g_Retry.pos.y + cosf(g_Retry.rot.z + (D3DX_PI - g_Retry.fAngele)) *  g_Retry.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Retry.pos.x + sinf(g_Retry.rot.z - (0 + g_Retry.fAngele)) * g_Retry.fLength;
	pVtx[2].pos.y = g_Retry.pos.y + cosf(g_Retry.rot.z - (0 + g_Retry.fAngele)) * g_Retry.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Retry.pos.x + sinf(g_Retry.rot.z - (0 - g_Retry.fAngele)) *  g_Retry.fLength;
	pVtx[3].pos.y = g_Retry.pos.y + cosf(g_Retry.rot.z - (0 - g_Retry.fAngele)) *  g_Retry.fLength;
	pVtx[3].pos.z = 0.0f;

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = g_Retry.col;
	pVtx[1].col = g_Retry.col;
	pVtx[2].col = g_Retry.col;
	pVtx[3].col = g_Retry.col;

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffRetry->Unlock();
}

//********************************************************************************
//リトライの終了処理
//********************************************************************************
void UninitRetry(void)
{
	//テクスチャの破棄	  
	if (g_pTextureRetry != NULL)
	{
		g_pTextureRetry->Release();

		g_pTextureRetry = NULL;
	}

	//頂点バッファを破棄
	if (g_pVtxBuffRetry != NULL)
	{
		g_pVtxBuffRetry->Release();

		g_pVtxBuffRetry = NULL;
	}
}

//********************************************************************************
//リトライの更新処理
//********************************************************************************
void UpdateRetry(void)
{
	if (g_Retry.bUse == true)
	{//使用されてる場合
		//ポーズ情報の取得
		Pause *pPause;				//ポーズ情報へのポインタ
		pPause = GetPause();

		if (pPause->state == NEXTPROCESS_RETRY)
		{//次に行われる処理がゲーム画面(継続)の時
			g_Retry.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//頂点情報へのポインタを生成						
			VERTEX_2D *pVtx;

			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffRetry->Lock(0, 0, (void**)&pVtx, 0);

			//頂点カラーの設定
			pVtx[0].col = g_Retry.col;
			pVtx[1].col = g_Retry.col;
			pVtx[2].col = g_Retry.col;
			pVtx[3].col = g_Retry.col;

			//頂点バッファをアンロック
			g_pVtxBuffRetry->Unlock();
		}
		else if (pPause->state != NEXTPROCESS_RETRY)
		{//次に行われる処理がゲーム画面(継続)以外の時
			g_Retry.col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

			//頂点情報へのポインタを生成						
			VERTEX_2D *pVtx;

			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffRetry->Lock(0, 0, (void**)&pVtx, 0);

			//頂点カラーの設定
			pVtx[0].col = g_Retry.col;
			pVtx[1].col = g_Retry.col;
			pVtx[2].col = g_Retry.col;
			pVtx[3].col = g_Retry.col;

			//頂点バッファをアンロック
			g_pVtxBuffRetry->Unlock();
		}
	}
}

//********************************************************************************
//リトライの描画処理
//********************************************************************************
void DrawRetry(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRetry, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_Retry.bUse == true)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureRetry);

		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//********************************************************************************
//リトライの設定処理
//********************************************************************************
void SetRetry(void)
{
	//頂点情報へのポインタを生成						
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRetry->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Retry.bUse == false)
	{//使用されてない場合
	 //タイトルロゴ情報の設定
		g_Retry.offset = D3DXVECTOR3(MAX_OFFSET_RETRY_X, MAX_OFFSET_RETRY_Y, 0.0f);		//中心点からの差
		g_Retry.pos = D3DXVECTOR3(POS_RETRY_X, POS_RETRY_Y, 0.0f);						//中心点
		g_Retry.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//向き
		g_Retry.col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);								//カラー
		g_Retry.bUse = true;															//使用してる

		//対角線の長さを算出する
		g_Retry.fLength = sqrtf(((g_Retry.offset.x * g_Retry.offset.x) + (g_Retry.offset.y * g_Retry.offset.y)) / 2.0f);

		//対角線の角度を算出
		g_Retry.fAngele = atan2f(g_Retry.offset.x, g_Retry.offset.y);

		//頂点座標の設定
		pVtx[0].pos.x = g_Retry.pos.x + sinf(g_Retry.rot.z + (D3DX_PI + g_Retry.fAngele)) * g_Retry.fLength;
		pVtx[0].pos.y = g_Retry.pos.y + cosf(g_Retry.rot.z + (D3DX_PI + g_Retry.fAngele)) * g_Retry.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Retry.pos.x + sinf(g_Retry.rot.z + (D3DX_PI - g_Retry.fAngele)) *  g_Retry.fLength;
		pVtx[1].pos.y = g_Retry.pos.y + cosf(g_Retry.rot.z + (D3DX_PI - g_Retry.fAngele)) *  g_Retry.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Retry.pos.x + sinf(g_Retry.rot.z - (0 + g_Retry.fAngele)) * g_Retry.fLength;
		pVtx[2].pos.y = g_Retry.pos.y + cosf(g_Retry.rot.z - (0 + g_Retry.fAngele)) * g_Retry.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Retry.pos.x + sinf(g_Retry.rot.z - (0 - g_Retry.fAngele)) *  g_Retry.fLength;
		pVtx[3].pos.y = g_Retry.pos.y + cosf(g_Retry.rot.z - (0 - g_Retry.fAngele)) *  g_Retry.fLength;
		pVtx[3].pos.z = 0.0f;

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = g_Retry.col;
		pVtx[1].col = g_Retry.col;
		pVtx[2].col = g_Retry.col;
		pVtx[3].col = g_Retry.col;

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//頂点バッファをアンロック
	g_pVtxBuffRetry->Unlock();
}