//**************************************************************************************************
//
// コンボの処理
// Auther：唐﨑結斗
//
//**************************************************************************************************

#include"main.h"
//#include"sound.h"

#include"combo.h"
#include"player.h"
#include"score.h"
#include"fade.h"

//*************************************************************
// グローバル変数
//*************************************************************
static LPDIRECT3DTEXTURE9			g_pTextureCombo = NULL;			// テクスチャへのポインタ
static LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffCombo = NULL;			// 頂点バッファへのポインタ
static Combo						g_Combo;						// コンボ情報
static int							g_nCombo;						// コンボの値
static int							g_nCntFrame;					// フレームの計算

//*************************************************************
// コンボの初期化処理
//*************************************************************
void InitCombo(void)
{
	// 変数宣言
	int nCountDigits;	// 桁数をカウントする

	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// ポリゴンに張り付けるテクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureCombo);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * MAX_VERTEX * MAX_COMBO_DIGITS,	// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,																// 頂点ファーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffCombo,
		NULL);

	// 数値の初期化
	g_Combo.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 中心点からの差
	g_Combo.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き
	g_nCombo = 0;										// コンボの値
	g_nCntFrame = 0;									// フレームカウンタを初期化
	g_Combo.bUse = false;								// 使用していない

	// コンボの位置の初期化
	for (nCountDigits = 0; nCountDigits < MAX_COMBO_DIGITS; nCountDigits++)
	{
		g_Combo.pos[nCountDigits] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// 頂点情報へのポインタを生成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCombo->Lock(0, 0, (void**)&pVtx, 0);

	// 対角線の長さを算出する
	g_Combo.fLength = sqrtf(((g_Combo.offset.x * g_Combo.offset.x) + (g_Combo.offset.y * g_Combo.offset.y)) / 2.0f);

	// 対角線の角度を算出
	g_Combo.fAngele = atan2f(g_Combo.offset.x, g_Combo.offset.y);

	for (nCountDigits = 0; nCountDigits < MAX_COMBO_DIGITS; nCountDigits++)
	{
		// 頂点座標の設定
		pVtx[0].pos.x = g_Combo.pos[nCountDigits].x + sinf(g_Combo.rot.z + (D3DX_PI + g_Combo.fAngele)) * g_Combo.fLength;
		pVtx[0].pos.y = g_Combo.pos[nCountDigits].y + cosf(g_Combo.rot.z + (D3DX_PI + g_Combo.fAngele)) * g_Combo.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Combo.pos[nCountDigits].x + sinf(g_Combo.rot.z + (D3DX_PI - g_Combo.fAngele)) *  g_Combo.fLength;
		pVtx[1].pos.y = g_Combo.pos[nCountDigits].y + cosf(g_Combo.rot.z + (D3DX_PI - g_Combo.fAngele)) *  g_Combo.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Combo.pos[nCountDigits].x + sinf(g_Combo.rot.z - (0 + g_Combo.fAngele)) * g_Combo.fLength;
		pVtx[2].pos.y = g_Combo.pos[nCountDigits].y + cosf(g_Combo.rot.z - (0 + g_Combo.fAngele)) * g_Combo.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Combo.pos[nCountDigits].x + sinf(g_Combo.rot.z - (0 - g_Combo.fAngele)) *  g_Combo.fLength;
		pVtx[3].pos.y = g_Combo.pos[nCountDigits].y + cosf(g_Combo.rot.z - (0 - g_Combo.fAngele)) *  g_Combo.fLength;
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
		pVtx[0].tex = D3DXVECTOR2(0.0f + (g_nCombo * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (g_nCombo * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (g_nCombo * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (g_nCombo * 0.1f), 1.0f);

		pVtx += 4;		// 頂点データのポインタを4つ分進める
	}

	// 頂点バッファをアンロック
	g_pVtxBuffCombo->Unlock();
}

//********************************************************************************
// コンボの終了処理
//********************************************************************************
void UninitCombo(void)
{
	// テクスチャの破棄	  
	if (g_pTextureCombo != NULL)
	{
		g_pTextureCombo->Release();

		g_pTextureCombo = NULL;
	}

	// 頂点バッファを破棄
	if (g_pVtxBuffCombo != NULL)
	{
		g_pVtxBuffCombo->Release();

		g_pVtxBuffCombo = NULL;
	}
}

//********************************************************************************
// コンボの更新処理
//********************************************************************************
void UpdateCombo(void)
{
	
}

//********************************************************************************
// コンボの描画処理
//********************************************************************************
void DrawCombo(void)
{
	if (g_Combo.bUse == true)
	{// 使用してる
		// 変数宣言
		int nCountDigits;		// 桁数をカウントする

		// デバイスへのポインタ
		LPDIRECT3DDEVICE9 pDevice;

		// デバイスの取得
		pDevice = GetDevice();

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffCombo, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// αテストを使用する
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

		// αテストの設定
		pDevice->SetRenderState(D3DRS_ALPHAREF, 50);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		for (nCountDigits = 0; nCountDigits < MAX_COMBO_DIGITS; nCountDigits++)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureCombo);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCountDigits * 4,
				2);
		}

		// αテストの終了
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}

//********************************************************************************
// コンボの設定処理
//********************************************************************************
void SetCombo(int nCombo, D3DXVECTOR3 pos, D3DXVECTOR3 offset)
{
	if (g_Combo.bUse == false)
	{// 使用してない
		// 変数宣言
		int aPosTexU[MAX_COMBO_DIGITS];		// 各桁の数値を格納
		int nCountDigits;					// 桁数をカウントする

		// 変数に引数を代入
		g_Combo.offset = offset;
		g_nCombo = nCombo;
		g_Combo.bUse = true;

		// 数値の分解と格納
		aPosTexU[0] = g_nCombo % 1000 / 100;
		aPosTexU[1] = g_nCombo % 100 / 10;
		aPosTexU[2] = g_nCombo % 10 / 1;

		// 頂点情報へのポインタを生成
		VERTEX_2D *pVtx;

		// 頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffCombo->Lock(0, 0, (void**)&pVtx, 0);

		// コンボの位置の設定
		for (nCountDigits = 0; nCountDigits < MAX_COMBO_DIGITS; nCountDigits++)
		{
			g_Combo.pos[nCountDigits] = D3DXVECTOR3(pos.x - (g_Combo.offset.x + (g_Combo.offset.x * 2) * nCountDigits), pos.y + g_Combo.offset.y, 0.0f);
		}

		// 対角線の長さを算出する
		g_Combo.fLength = sqrtf(((g_Combo.offset.x * g_Combo.offset.x) + (g_Combo.offset.y * g_Combo.offset.y)) / 2.0f);

		// 対角線の角度を算出
		g_Combo.fAngele = atan2f(g_Combo.offset.x, g_Combo.offset.y);

		for (nCountDigits = 0; nCountDigits < MAX_COMBO_DIGITS; nCountDigits++)
		{
			// 頂点座標の設定
			pVtx[0].pos.x = g_Combo.pos[nCountDigits].x + sinf(g_Combo.rot.z + (D3DX_PI + g_Combo.fAngele)) * g_Combo.fLength;
			pVtx[0].pos.y = g_Combo.pos[nCountDigits].y + cosf(g_Combo.rot.z + (D3DX_PI + g_Combo.fAngele)) * g_Combo.fLength;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_Combo.pos[nCountDigits].x + sinf(g_Combo.rot.z + (D3DX_PI - g_Combo.fAngele)) *  g_Combo.fLength;
			pVtx[1].pos.y = g_Combo.pos[nCountDigits].y + cosf(g_Combo.rot.z + (D3DX_PI - g_Combo.fAngele)) *  g_Combo.fLength;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_Combo.pos[nCountDigits].x + sinf(g_Combo.rot.z - (0 + g_Combo.fAngele)) * g_Combo.fLength;
			pVtx[2].pos.y = g_Combo.pos[nCountDigits].y + cosf(g_Combo.rot.z - (0 + g_Combo.fAngele)) * g_Combo.fLength;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_Combo.pos[nCountDigits].x + sinf(g_Combo.rot.z - (0 - g_Combo.fAngele)) *  g_Combo.fLength;
			pVtx[3].pos.y = g_Combo.pos[nCountDigits].y + cosf(g_Combo.rot.z - (0 - g_Combo.fAngele)) *  g_Combo.fLength;
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
			pVtx[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[(MAX_COMBO_DIGITS - 1) - nCountDigits] * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (aPosTexU[(MAX_COMBO_DIGITS - 1) - nCountDigits] * 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[(MAX_COMBO_DIGITS - 1) - nCountDigits] * 0.1f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (aPosTexU[(MAX_COMBO_DIGITS - 1) - nCountDigits] * 0.1f), 1.0f);

			pVtx += 4;			// 頂点データのポインタを4つ分進める
		}

		// 頂点バッファをアンロック
		g_pVtxBuffCombo->Unlock();
	}
}

//********************************************************************************
// コンボの計算算処理
//********************************************************************************
void AddCombo(int nCombo)
{
	// 変数宣言
	int aPosTexU[MAX_COMBO_DIGITS];		// 各桁の数値を格納
	int nCountDigits;					// 桁数をカウントする
	g_nCombo = nCombo;					// コンボ数の代入
	
	if (g_nCombo < 2)
	{// 0以下の時
		g_Combo.bUse = false;
	}

	if (g_Combo.bUse == true)
	{// 使用してる
		// 数値の分解と格納
		aPosTexU[0] = g_nCombo % 1000 / 100;
		aPosTexU[1] = g_nCombo % 100 / 10;
		aPosTexU[2] = g_nCombo % 10 / 1;

		// 頂点情報へのポインタを生成
		VERTEX_2D *pVtx;

		// 頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffCombo->Lock(0, 0, (void**)&pVtx, 0);

		// 対角線の長さを算出する
		g_Combo.fLength = sqrtf(((g_Combo.offset.x * g_Combo.offset.x) + (g_Combo.offset.y * g_Combo.offset.y)) / 2.0f);

		// 対角線の角度を算出
		g_Combo.fAngele = atan2f(g_Combo.offset.x, g_Combo.offset.y);

		for (nCountDigits = 0; nCountDigits < MAX_COMBO_DIGITS; nCountDigits++)
		{
			// 頂点座標の設定
			pVtx[0].pos.x = g_Combo.pos[nCountDigits].x + sinf(g_Combo.rot.z + (D3DX_PI + g_Combo.fAngele)) * g_Combo.fLength;
			pVtx[0].pos.y = g_Combo.pos[nCountDigits].y + cosf(g_Combo.rot.z + (D3DX_PI + g_Combo.fAngele)) * g_Combo.fLength;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_Combo.pos[nCountDigits].x + sinf(g_Combo.rot.z + (D3DX_PI - g_Combo.fAngele)) *  g_Combo.fLength;
			pVtx[1].pos.y = g_Combo.pos[nCountDigits].y + cosf(g_Combo.rot.z + (D3DX_PI - g_Combo.fAngele)) *  g_Combo.fLength;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_Combo.pos[nCountDigits].x + sinf(g_Combo.rot.z - (0 + g_Combo.fAngele)) * g_Combo.fLength;
			pVtx[2].pos.y = g_Combo.pos[nCountDigits].y + cosf(g_Combo.rot.z - (0 + g_Combo.fAngele)) * g_Combo.fLength;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_Combo.pos[nCountDigits].x + sinf(g_Combo.rot.z - (0 - g_Combo.fAngele)) *  g_Combo.fLength;
			pVtx[3].pos.y = g_Combo.pos[nCountDigits].y + cosf(g_Combo.rot.z - (0 - g_Combo.fAngele)) *  g_Combo.fLength;
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
			pVtx[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[(MAX_COMBO_DIGITS - 1) - nCountDigits] * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (aPosTexU[(MAX_COMBO_DIGITS - 1) - nCountDigits] * 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[(MAX_COMBO_DIGITS - 1) - nCountDigits] * 0.1f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (aPosTexU[(MAX_COMBO_DIGITS - 1) - nCountDigits] * 0.1f), 1.0f);

			pVtx += 4;		// 頂点データのポインタを4つ分進める
		}

		// 頂点バッファをアンロック
		g_pVtxBuffCombo->Unlock();
	}
}

//********************************************************************************
// コンボの情報の取得
//********************************************************************************
int GetCombo(void)
{
	return g_nCombo;
}