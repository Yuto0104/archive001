//**************************************************************************************************
//
//クワイエットの設定処理
//Auther：唐﨑結斗
//
//**************************************************************************************************
#include"main.h"
#include"quit.h"
#include"input.h"
#include"pause.h"

//*******************************************************************************
//グローバル変数
//*******************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureQuit = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffQuit = NULL;		//頂点バッファへのポインタ
Quit g_Quit;

//********************************************************************************
//クワイエットの初期化処理
//********************************************************************************
void InitQuit(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//ポリゴンに張り付けるテクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/pause002.png",
		&g_pTextureQuit);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									//頂点ファーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffQuit,
		NULL);

	//タイトルロゴ情報の初期化
	g_Quit.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//中心点
	g_Quit.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//中心点からの差
	g_Quit.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向き
	g_Quit.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//カラー
	g_Quit.bUse = false;								//使用してない

														//頂点情報へのポインタを生成						
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffQuit->Lock(0, 0, (void**)&pVtx, 0);

	//対角線の長さを算出する
	g_Quit.fLength = sqrtf(((g_Quit.offset.x * g_Quit.offset.x) + (g_Quit.offset.y * g_Quit.offset.y)) / 2.0f);

	//対角線の角度を算出
	g_Quit.fAngele = atan2f(g_Quit.offset.x, g_Quit.offset.y);

	//頂点座標の設定
	pVtx[0].pos.x = g_Quit.pos.x + sinf(g_Quit.rot.z + (D3DX_PI + g_Quit.fAngele)) * g_Quit.fLength;
	pVtx[0].pos.y = g_Quit.pos.y + cosf(g_Quit.rot.z + (D3DX_PI + g_Quit.fAngele)) * g_Quit.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Quit.pos.x + sinf(g_Quit.rot.z + (D3DX_PI - g_Quit.fAngele)) *  g_Quit.fLength;
	pVtx[1].pos.y = g_Quit.pos.y + cosf(g_Quit.rot.z + (D3DX_PI - g_Quit.fAngele)) *  g_Quit.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Quit.pos.x + sinf(g_Quit.rot.z - (0 + g_Quit.fAngele)) * g_Quit.fLength;
	pVtx[2].pos.y = g_Quit.pos.y + cosf(g_Quit.rot.z - (0 + g_Quit.fAngele)) * g_Quit.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Quit.pos.x + sinf(g_Quit.rot.z - (0 - g_Quit.fAngele)) *  g_Quit.fLength;
	pVtx[3].pos.y = g_Quit.pos.y + cosf(g_Quit.rot.z - (0 - g_Quit.fAngele)) *  g_Quit.fLength;
	pVtx[3].pos.z = 0.0f;

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = g_Quit.col;
	pVtx[1].col = g_Quit.col;
	pVtx[2].col = g_Quit.col;
	pVtx[3].col = g_Quit.col;

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffQuit->Unlock();
}

//********************************************************************************
//クワイエットの終了処理
//********************************************************************************
void UninitQuit(void)
{
	//テクスチャの破棄	  
	if (g_pTextureQuit != NULL)
	{
		g_pTextureQuit->Release();

		g_pTextureQuit = NULL;
	}

	//頂点バッファを破棄
	if (g_pVtxBuffQuit != NULL)
	{
		g_pVtxBuffQuit->Release();

		g_pVtxBuffQuit = NULL;
	}
}

//********************************************************************************
//クワイエットの更新処理
//********************************************************************************
void UpdateQuit(void)
{
	if (g_Quit.bUse == true)
	{//使用されてる場合
	 //ポーズ情報の取得
		Pause *pPause;				//ポーズ情報へのポインタ
		pPause = GetPause();

		if (pPause->state == NEXTPROCESS_QUIT)
		{//次に行われる処理がゲーム画面(継続)の時
			g_Quit.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//頂点情報へのポインタを生成						
			VERTEX_2D *pVtx;

			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffQuit->Lock(0, 0, (void**)&pVtx, 0);

			//頂点カラーの設定
			pVtx[0].col = g_Quit.col;
			pVtx[1].col = g_Quit.col;
			pVtx[2].col = g_Quit.col;
			pVtx[3].col = g_Quit.col;

			//頂点バッファをアンロック
			g_pVtxBuffQuit->Unlock();
		}
		else if (pPause->state != NEXTPROCESS_QUIT)
		{//次に行われる処理がゲーム画面(継続)以外の時
			g_Quit.col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

			//頂点情報へのポインタを生成						
			VERTEX_2D *pVtx;

			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffQuit->Lock(0, 0, (void**)&pVtx, 0);

			//頂点カラーの設定
			pVtx[0].col = g_Quit.col;
			pVtx[1].col = g_Quit.col;
			pVtx[2].col = g_Quit.col;
			pVtx[3].col = g_Quit.col;

			//頂点バッファをアンロック
			g_pVtxBuffQuit->Unlock();
		}
	}
}

//********************************************************************************
//クワイエットの描画処理
//********************************************************************************
void DrawQuit(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffQuit, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_Quit.bUse == true)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureQuit);

		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//********************************************************************************
//クワイエットの設定処理
//********************************************************************************
void SetQuit(void)
{
	//頂点情報へのポインタを生成						
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffQuit->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Quit.bUse == false)
	{//使用されてない場合
	 //タイトルロゴ情報の設定
		g_Quit.offset = D3DXVECTOR3(MAX_OFFSET_QUIT_X, MAX_OFFSET_QUIT_Y, 0.0f);		//中心点からの差
		g_Quit.pos = D3DXVECTOR3(POS_QUIT_X, POS_QUIT_Y, 0.0f);						//中心点
		g_Quit.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//向き
		g_Quit.col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);								//カラー
		g_Quit.bUse = true;															//使用してる

																						//対角線の長さを算出する
		g_Quit.fLength = sqrtf(((g_Quit.offset.x * g_Quit.offset.x) + (g_Quit.offset.y * g_Quit.offset.y)) / 2.0f);

		//対角線の角度を算出
		g_Quit.fAngele = atan2f(g_Quit.offset.x, g_Quit.offset.y);

		//頂点座標の設定
		pVtx[0].pos.x = g_Quit.pos.x + sinf(g_Quit.rot.z + (D3DX_PI + g_Quit.fAngele)) * g_Quit.fLength;
		pVtx[0].pos.y = g_Quit.pos.y + cosf(g_Quit.rot.z + (D3DX_PI + g_Quit.fAngele)) * g_Quit.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Quit.pos.x + sinf(g_Quit.rot.z + (D3DX_PI - g_Quit.fAngele)) *  g_Quit.fLength;
		pVtx[1].pos.y = g_Quit.pos.y + cosf(g_Quit.rot.z + (D3DX_PI - g_Quit.fAngele)) *  g_Quit.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Quit.pos.x + sinf(g_Quit.rot.z - (0 + g_Quit.fAngele)) * g_Quit.fLength;
		pVtx[2].pos.y = g_Quit.pos.y + cosf(g_Quit.rot.z - (0 + g_Quit.fAngele)) * g_Quit.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Quit.pos.x + sinf(g_Quit.rot.z - (0 - g_Quit.fAngele)) *  g_Quit.fLength;
		pVtx[3].pos.y = g_Quit.pos.y + cosf(g_Quit.rot.z - (0 - g_Quit.fAngele)) *  g_Quit.fLength;
		pVtx[3].pos.z = 0.0f;

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = g_Quit.col;
		pVtx[1].col = g_Quit.col;
		pVtx[2].col = g_Quit.col;
		pVtx[3].col = g_Quit.col;

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//頂点バッファをアンロック
	g_pVtxBuffQuit->Unlock();
}