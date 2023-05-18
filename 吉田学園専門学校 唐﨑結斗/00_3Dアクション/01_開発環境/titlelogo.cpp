//**************************************************************************************************
//
// タイトルロゴの設定処理
// Auther：唐﨑結斗
//
//**************************************************************************************************
#include"main.h"
#include"titlelogo.h"
#include"input.h"
#include"press enter.h"

//*******************************************************************************
// グローバル変数
//*******************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTitleLogo = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleLogo = NULL;		//頂点バッファへのポインタ
Logo g_Logo;											//タイトルロゴ情報

//********************************************************************************
// タイトルロゴの初期化処理
//********************************************************************************
void InitTitleLogo(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// ポリゴンに張り付けるテクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/タイトル.png",
		&g_pTextureTitleLogo);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// 頂点ファーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitleLogo,
		NULL);

	// タイトルロゴ情報の初期化
	g_Logo.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 中心点
	g_Logo.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 中心点からの差
	g_Logo.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向き
	g_Logo.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動距離
	g_Logo.fSpeed = 0.0f;								// 移動速度
	g_Logo.bUse = false;								// 使用してない
														
	// 頂点情報へのポインタを生成						
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

	// 対角線の長さを算出する
	g_Logo.fLength = sqrtf(((g_Logo.offset.x * g_Logo.offset.x) + (g_Logo.offset.y * g_Logo.offset.y)) / 2.0f);

	// 対角線の角度を算出
	g_Logo.fAngele = atan2f(g_Logo.offset.x, g_Logo.offset.y);

	// 頂点座標の設定
	pVtx[0].pos.x = g_Logo.pos.x + sinf(g_Logo.rot.z + (D3DX_PI + g_Logo.fAngele)) * g_Logo.fLength;
	pVtx[0].pos.y = g_Logo.pos.y + cosf(g_Logo.rot.z + (D3DX_PI + g_Logo.fAngele)) * g_Logo.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Logo.pos.x + sinf(g_Logo.rot.z + (D3DX_PI - g_Logo.fAngele)) *  g_Logo.fLength;
	pVtx[1].pos.y = g_Logo.pos.y + cosf(g_Logo.rot.z + (D3DX_PI - g_Logo.fAngele)) *  g_Logo.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Logo.pos.x + sinf(g_Logo.rot.z - (0 + g_Logo.fAngele)) * g_Logo.fLength;
	pVtx[2].pos.y = g_Logo.pos.y + cosf(g_Logo.rot.z - (0 + g_Logo.fAngele)) * g_Logo.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Logo.pos.x + sinf(g_Logo.rot.z - (0 - g_Logo.fAngele)) *  g_Logo.fLength;
	pVtx[3].pos.y = g_Logo.pos.y + cosf(g_Logo.rot.z - (0 - g_Logo.fAngele)) *  g_Logo.fLength;
	pVtx[3].pos.z = 0.0f;

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffTitleLogo->Unlock();
}

//********************************************************************************
// タイトルロゴの終了処理
//********************************************************************************
void UninitTitleLogo(void)
{
	// テクスチャの破棄	  
	if (g_pTextureTitleLogo != NULL)
	{
		g_pTextureTitleLogo->Release();

		g_pTextureTitleLogo = NULL;
	}

	// 頂点バッファを破棄
	if (g_pVtxBuffTitleLogo != NULL)
	{
		g_pVtxBuffTitleLogo->Release();

		g_pVtxBuffTitleLogo = NULL;
	}
}

//********************************************************************************
// タイトルロゴの更新処理
//********************************************************************************
void UpdateTitleLogo(void)
{
	// 頂点情報へのポインタを生成						
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Logo.bUse == true)
	{// タイトルロゴが使用されてる
		if (g_Logo.pos.y < MAX_MOVED)
		{// 特定の位置まで移動した
			// 位置の更新
			g_Logo.pos.x += g_Logo.move.x;
			g_Logo.pos.y += g_Logo.move.y;

			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{// [Enter]キーが押された
				g_Logo.pos.y = MAX_MOVED;
			}
		}
		else if (g_Logo.pos.y >= MAX_MOVED)
		{// 数値を固定
			g_Logo.pos.y = MAX_MOVED;
			
			// プレスエンターの設定処理
			SetPressEnter(D3DXVECTOR3(SCREEN_WIDH / 2, PRESS_ENTER_POS_Y, 0.0f), D3DXVECTOR3(MAX_OFFSET_PE_X, MAX_OFFSET_PE_Y, 0.0f));
		}

		// 対角線の長さを算出する
		g_Logo.fLength = sqrtf(((g_Logo.offset.x * g_Logo.offset.x) + (g_Logo.offset.y * g_Logo.offset.y)) / 2.0f);

		// 対角線の角度を算出
		g_Logo.fAngele = atan2f(g_Logo.offset.x, g_Logo.offset.y);

		// 頂点座標の設定
		pVtx[0].pos.x = g_Logo.pos.x + sinf(g_Logo.rot.z + (D3DX_PI + g_Logo.fAngele)) * g_Logo.fLength;
		pVtx[0].pos.y = g_Logo.pos.y + cosf(g_Logo.rot.z + (D3DX_PI + g_Logo.fAngele)) * g_Logo.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Logo.pos.x + sinf(g_Logo.rot.z + (D3DX_PI - g_Logo.fAngele)) *  g_Logo.fLength;
		pVtx[1].pos.y = g_Logo.pos.y + cosf(g_Logo.rot.z + (D3DX_PI - g_Logo.fAngele)) *  g_Logo.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Logo.pos.x + sinf(g_Logo.rot.z - (0 + g_Logo.fAngele)) * g_Logo.fLength;
		pVtx[2].pos.y = g_Logo.pos.y + cosf(g_Logo.rot.z - (0 + g_Logo.fAngele)) * g_Logo.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Logo.pos.x + sinf(g_Logo.rot.z - (0 - g_Logo.fAngele)) *  g_Logo.fLength;
		pVtx[3].pos.y = g_Logo.pos.y + cosf(g_Logo.rot.z - (0 - g_Logo.fAngele)) *  g_Logo.fLength;
		pVtx[3].pos.z = 0.0f;

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//頂点バッファをアンロック
	g_pVtxBuffTitleLogo->Unlock();
}

//********************************************************************************
// タイトルロゴの描画処理
//********************************************************************************
void DrawTitleLogo(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitleLogo, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// αテストを使用する
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// αテストの設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	if (g_Logo.bUse == true)
	{// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitleLogo);

		// ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	// αテストの終了
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//********************************************************************************
// タイトルロゴの設定処理
//********************************************************************************
void SetTitleLogo(void)
{
	// 頂点情報へのポインタを生成						
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Logo.bUse == false)
	{// 使用されてない場合
		// タイトルロゴ情報の設定
		g_Logo.offset = D3DXVECTOR3(MAX_OFFSET_TL_X, MAX_OFFSET_TL_Y, 0.0f);		// 中心点からの差
		g_Logo.pos = D3DXVECTOR3(SCREEN_WIDH / 2, 0.0f - g_Logo.offset.y, 0.0f);	// 中心点
		g_Logo.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									// 向き
		g_Logo.fSpeed = MAX_MOVE_SPEED;												// 移動速度
		g_Logo.bUse = true;															// 使用してる

		// 移動量の設定
		g_Logo.move.x += sinf(D3DX_PI - D3DX_PI) * g_Logo.fSpeed;
		g_Logo.move.y += cosf(D3DX_PI - D3DX_PI) * g_Logo.fSpeed;

		// 対角線の長さを算出する
		g_Logo.fLength = sqrtf(((g_Logo.offset.x * g_Logo.offset.x) + (g_Logo.offset.y * g_Logo.offset.y)) / 2.0f);

		// 対角線の角度を算出
		g_Logo.fAngele = atan2f(g_Logo.offset.x, g_Logo.offset.y);

		// 頂点座標の設定
		pVtx[0].pos.x = g_Logo.pos.x + sinf(g_Logo.rot.z + (D3DX_PI + g_Logo.fAngele)) * g_Logo.fLength;
		pVtx[0].pos.y = g_Logo.pos.y + cosf(g_Logo.rot.z + (D3DX_PI + g_Logo.fAngele)) * g_Logo.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Logo.pos.x + sinf(g_Logo.rot.z + (D3DX_PI - g_Logo.fAngele)) *  g_Logo.fLength;
		pVtx[1].pos.y = g_Logo.pos.y + cosf(g_Logo.rot.z + (D3DX_PI - g_Logo.fAngele)) *  g_Logo.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Logo.pos.x + sinf(g_Logo.rot.z - (0 + g_Logo.fAngele)) * g_Logo.fLength;
		pVtx[2].pos.y = g_Logo.pos.y + cosf(g_Logo.rot.z - (0 + g_Logo.fAngele)) * g_Logo.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Logo.pos.x + sinf(g_Logo.rot.z - (0 - g_Logo.fAngele)) *  g_Logo.fLength;
		pVtx[3].pos.y = g_Logo.pos.y + cosf(g_Logo.rot.z - (0 - g_Logo.fAngele)) *  g_Logo.fLength;
		pVtx[3].pos.z = 0.0f;

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// 頂点バッファをアンロック
	g_pVtxBuffTitleLogo->Unlock();
}