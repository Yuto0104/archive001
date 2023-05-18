//**************************************************************************************************
//
//コンティニューの設定処理
//Auther：唐﨑結斗
//
//**************************************************************************************************
#include"main.h"
#include"continue.h"
#include"input.h"
#include"pause.h"

//*******************************************************************************
//グローバル変数
//*******************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureContinue = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffContinue = NULL;		//頂点バッファへのポインタ
Continue g_Continue;

//********************************************************************************
//コンティニューの初期化処理
//********************************************************************************
void InitContinue(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//ポリゴンに張り付けるテクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/pause000.png",
		&g_pTextureContinue);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									//頂点ファーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffContinue,
		NULL);

	//タイトルロゴ情報の初期化
	g_Continue.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//中心点
	g_Continue.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//中心点からの差
	g_Continue.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向き
	g_Continue.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//カラー
	g_Continue.bUse = false;								//使用してない

	//頂点情報へのポインタを生成						
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffContinue->Lock(0, 0, (void**)&pVtx, 0);

	//対角線の長さを算出する
	g_Continue.fLength = sqrtf(((g_Continue.offset.x * g_Continue.offset.x) + (g_Continue.offset.y * g_Continue.offset.y)) / 2.0f);

	//対角線の角度を算出
	g_Continue.fAngele = atan2f(g_Continue.offset.x, g_Continue.offset.y);

	//頂点座標の設定
	pVtx[0].pos.x = g_Continue.pos.x + sinf(g_Continue.rot.z + (D3DX_PI + g_Continue.fAngele)) * g_Continue.fLength;
	pVtx[0].pos.y = g_Continue.pos.y + cosf(g_Continue.rot.z + (D3DX_PI + g_Continue.fAngele)) * g_Continue.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Continue.pos.x + sinf(g_Continue.rot.z + (D3DX_PI - g_Continue.fAngele)) *  g_Continue.fLength;
	pVtx[1].pos.y = g_Continue.pos.y + cosf(g_Continue.rot.z + (D3DX_PI - g_Continue.fAngele)) *  g_Continue.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Continue.pos.x + sinf(g_Continue.rot.z - (0 + g_Continue.fAngele)) * g_Continue.fLength;
	pVtx[2].pos.y = g_Continue.pos.y + cosf(g_Continue.rot.z - (0 + g_Continue.fAngele)) * g_Continue.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Continue.pos.x + sinf(g_Continue.rot.z - (0 - g_Continue.fAngele)) *  g_Continue.fLength;
	pVtx[3].pos.y = g_Continue.pos.y + cosf(g_Continue.rot.z - (0 - g_Continue.fAngele)) *  g_Continue.fLength;
	pVtx[3].pos.z = 0.0f;

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = g_Continue.col;
	pVtx[1].col = g_Continue.col;
	pVtx[2].col = g_Continue.col;
	pVtx[3].col = g_Continue.col;

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffContinue->Unlock();
}

//********************************************************************************
//コンティニューの終了処理
//********************************************************************************
void UninitContinue(void)
{
	//テクスチャの破棄	  
	if (g_pTextureContinue != NULL)
	{
		g_pTextureContinue->Release();

		g_pTextureContinue = NULL;
	}

	//頂点バッファを破棄
	if (g_pVtxBuffContinue != NULL)
	{
		g_pVtxBuffContinue->Release();

		g_pVtxBuffContinue = NULL;
	}
}

//********************************************************************************
//コンティニューの更新処理
//********************************************************************************
void UpdateContinue(void)
{
	if (g_Continue.bUse == true)
	{//使用されてる場合
		//ポーズ情報の取得
		Pause *pPause;				//ポーズ情報へのポインタ
		pPause = GetPause();

		if (pPause->state == NEXTPROCESS_CONTINUE)
		{//次に行われる処理がゲーム画面(継続)の時
			g_Continue.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//頂点情報へのポインタを生成						
			VERTEX_2D *pVtx;

			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffContinue->Lock(0, 0, (void**)&pVtx, 0);

			//頂点カラーの設定
			pVtx[0].col = g_Continue.col;
			pVtx[1].col = g_Continue.col;
			pVtx[2].col = g_Continue.col;
			pVtx[3].col = g_Continue.col;

			//頂点バッファをアンロック
			g_pVtxBuffContinue->Unlock();
		}
		else if (pPause->state != NEXTPROCESS_CONTINUE)
		{//次に行われる処理がゲーム画面(継続)以外の時
			g_Continue.col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

			//頂点情報へのポインタを生成						
			VERTEX_2D *pVtx;

			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffContinue->Lock(0, 0, (void**)&pVtx, 0);

			//頂点カラーの設定
			pVtx[0].col = g_Continue.col;
			pVtx[1].col = g_Continue.col;
			pVtx[2].col = g_Continue.col;
			pVtx[3].col = g_Continue.col;

			//頂点バッファをアンロック
			g_pVtxBuffContinue->Unlock();
		}
	}
}

//********************************************************************************
//コンティニューの描画処理
//********************************************************************************
void DrawContinue(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffContinue, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_Continue.bUse == true)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureContinue);

		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//********************************************************************************
//コンティニューの設定処理
//********************************************************************************
void SetContinue(void)
{
	//頂点情報へのポインタを生成						
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffContinue->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Continue.bUse == false)
	{//使用されてない場合
		//タイトルロゴ情報の設定
		g_Continue.offset = D3DXVECTOR3(MAX_OFFSET_CONTINUE_X, MAX_OFFSET_CONTINUE_Y, 0.0f);		//中心点からの差
		g_Continue.pos = D3DXVECTOR3(POS_CONTINUE_X, POS_CONTINUE_Y, 0.0f);							//中心点
		g_Continue.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);												//向き
		g_Continue.col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);											//カラー
		g_Continue.bUse = true;																		//使用してる

		//対角線の長さを算出する
		g_Continue.fLength = sqrtf(((g_Continue.offset.x * g_Continue.offset.x) + (g_Continue.offset.y * g_Continue.offset.y)) / 2.0f);

		//対角線の角度を算出
		g_Continue.fAngele = atan2f(g_Continue.offset.x, g_Continue.offset.y);

		//頂点座標の設定
		pVtx[0].pos.x = g_Continue.pos.x + sinf(g_Continue.rot.z + (D3DX_PI + g_Continue.fAngele)) * g_Continue.fLength;
		pVtx[0].pos.y = g_Continue.pos.y + cosf(g_Continue.rot.z + (D3DX_PI + g_Continue.fAngele)) * g_Continue.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Continue.pos.x + sinf(g_Continue.rot.z + (D3DX_PI - g_Continue.fAngele)) *  g_Continue.fLength;
		pVtx[1].pos.y = g_Continue.pos.y + cosf(g_Continue.rot.z + (D3DX_PI - g_Continue.fAngele)) *  g_Continue.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Continue.pos.x + sinf(g_Continue.rot.z - (0 + g_Continue.fAngele)) * g_Continue.fLength;
		pVtx[2].pos.y = g_Continue.pos.y + cosf(g_Continue.rot.z - (0 + g_Continue.fAngele)) * g_Continue.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Continue.pos.x + sinf(g_Continue.rot.z - (0 - g_Continue.fAngele)) *  g_Continue.fLength;
		pVtx[3].pos.y = g_Continue.pos.y + cosf(g_Continue.rot.z - (0 - g_Continue.fAngele)) *  g_Continue.fLength;
		pVtx[3].pos.z = 0.0f;

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = g_Continue.col;
		pVtx[1].col = g_Continue.col;
		pVtx[2].col = g_Continue.col;
		pVtx[3].col = g_Continue.col;

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//頂点バッファをアンロック
	g_pVtxBuffContinue->Unlock();
}