//**************************************************************************************************
//
// スコアの処理
// Auther：唐﨑結斗
//
//**************************************************************************************************
#include"main.h"
#include"score.h"

//*************************************************************
// グローバル変数
//*************************************************************
LPDIRECT3DTEXTURE9			g_pTextureScore = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffScore = NULL;			//頂点バッファへのポインタ
Score						g_Score;						//スコア情報
int							g_nScore;						//スコアの値

//*************************************************************
// スコアの初期化処理
//*************************************************************
void InitScore(void)
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
		&g_pTextureScore);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * MAX_VERTEX * MAX_DIGITS,	// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,															// 頂点ファーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	// 数値の初期化
	g_Score.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 中心点からの差
	g_Score.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き
	g_nScore = 0;										// スコアの値
	
	// スコアの位置の初期化
	for (nCountDigits = 0; nCountDigits < MAX_DIGITS; nCountDigits++)
	{
		g_Score.pos[nCountDigits] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// 頂点情報へのポインタを生成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	// 対角線の長さを算出する
	g_Score.fLength = sqrtf(((g_Score.offset.x * g_Score.offset.x) + (g_Score.offset.y * g_Score.offset.y)) / 2.0f);

	// 対角線の角度を算出
	g_Score.fAngele = atan2f(g_Score.offset.x, g_Score.offset.y);

	for (nCountDigits = 0; nCountDigits < MAX_DIGITS; nCountDigits++)
	{
		// 頂点座標の設定
		pVtx[0].pos.x = g_Score.pos[nCountDigits].x + sinf(g_Score.rot.z + (D3DX_PI + g_Score.fAngele)) * g_Score.fLength;
		pVtx[0].pos.y = g_Score.pos[nCountDigits].y + cosf(g_Score.rot.z + (D3DX_PI + g_Score.fAngele)) * g_Score.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Score.pos[nCountDigits].x + sinf(g_Score.rot.z + (D3DX_PI - g_Score.fAngele)) *  g_Score.fLength;
		pVtx[1].pos.y = g_Score.pos[nCountDigits].y + cosf(g_Score.rot.z + (D3DX_PI - g_Score.fAngele)) *  g_Score.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Score.pos[nCountDigits].x + sinf(g_Score.rot.z - (0 + g_Score.fAngele)) * g_Score.fLength;
		pVtx[2].pos.y = g_Score.pos[nCountDigits].y + cosf(g_Score.rot.z - (0 + g_Score.fAngele)) * g_Score.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Score.pos[nCountDigits].x + sinf(g_Score.rot.z - (0 - g_Score.fAngele)) *  g_Score.fLength;
		pVtx[3].pos.y = g_Score.pos[nCountDigits].y + cosf(g_Score.rot.z - (0 - g_Score.fAngele)) *  g_Score.fLength;
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
		pVtx[0].tex = D3DXVECTOR2(0.0f + (g_nScore * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (g_nScore * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (g_nScore * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (g_nScore * 0.1f), 1.0f);

		pVtx += 4;		// 頂点データのポインタを4つ分進める
	}

	// 頂点バッファをアンロック
	g_pVtxBuffScore->Unlock();
}

//********************************************************************************
// スコアの終了処理
//********************************************************************************
void UninitScore(void)
{
	// テクスチャの破棄	  
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();

		g_pTextureScore = NULL;
	}

	// 頂点バッファを破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();

		g_pVtxBuffScore = NULL;
	}
}

//********************************************************************************
// スコアの更新処理
//********************************************************************************
void UpdateScore(void)
{

}

//********************************************************************************
// スコアの描画処理
//********************************************************************************
void DrawScore(void)
{
	// 変数宣言
	int nCountDigits;		// 桁数をカウントする

	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// αテストを使用する
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// αテストの設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 50);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (nCountDigits = 0; nCountDigits < MAX_DIGITS; nCountDigits++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureScore);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCountDigits * 4,
			2);
	}
	
	// αテストの終了
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//********************************************************************************
// スコアの設定処理
//********************************************************************************
void SetScore(int nScore, D3DXVECTOR3 pos, D3DXVECTOR3 offset)
{
	// 変数宣言
	int aPosTexU[8];		// 各桁の数値を格納
	int nCountDigits;		// 桁数をカウントする

	// 変数に引数を代入
	g_Score.offset = offset;
	g_nScore = nScore;

	// 数値の分解と格納
	aPosTexU[0] = g_nScore % 100000000 / 10000000;
	aPosTexU[1] = g_nScore % 10000000 / 1000000;
	aPosTexU[2] = g_nScore % 1000000 / 100000;
	aPosTexU[3] = g_nScore % 100000 / 10000;
	aPosTexU[4] = g_nScore % 10000 / 1000;
	aPosTexU[5] = g_nScore % 1000 / 100;
	aPosTexU[6] = g_nScore % 100 / 10;
	aPosTexU[7] = g_nScore % 10 / 1;

	// 頂点情報へのポインタを生成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	// スコアの位置の設定
	for (nCountDigits = 0; nCountDigits < MAX_DIGITS; nCountDigits++)
	{
		g_Score.pos[nCountDigits] = D3DXVECTOR3(pos.x - (g_Score.offset.x + (g_Score.offset.x * 2) * nCountDigits), pos.y + g_Score.offset.y, 0.0f);
	}

	// 対角線の長さを算出する
	g_Score.fLength = sqrtf(((g_Score.offset.x * g_Score.offset.x) + (g_Score.offset.y * g_Score.offset.y)) / 2.0f);

	// 対角線の角度を算出
	g_Score.fAngele = atan2f(g_Score.offset.x, g_Score.offset.y);

	for (nCountDigits = 0; nCountDigits < MAX_DIGITS; nCountDigits++)
	{
		// 頂点座標の設定
		pVtx[0].pos.x = g_Score.pos[nCountDigits].x + sinf(g_Score.rot.z + (D3DX_PI + g_Score.fAngele)) * g_Score.fLength;
		pVtx[0].pos.y = g_Score.pos[nCountDigits].y + cosf(g_Score.rot.z + (D3DX_PI + g_Score.fAngele)) * g_Score.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Score.pos[nCountDigits].x + sinf(g_Score.rot.z + (D3DX_PI - g_Score.fAngele)) *  g_Score.fLength;
		pVtx[1].pos.y = g_Score.pos[nCountDigits].y + cosf(g_Score.rot.z + (D3DX_PI - g_Score.fAngele)) *  g_Score.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Score.pos[nCountDigits].x + sinf(g_Score.rot.z - (0 + g_Score.fAngele)) * g_Score.fLength;
		pVtx[2].pos.y = g_Score.pos[nCountDigits].y + cosf(g_Score.rot.z - (0 + g_Score.fAngele)) * g_Score.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Score.pos[nCountDigits].x + sinf(g_Score.rot.z - (0 - g_Score.fAngele)) *  g_Score.fLength;
		pVtx[3].pos.y = g_Score.pos[nCountDigits].y + cosf(g_Score.rot.z - (0 - g_Score.fAngele)) *  g_Score.fLength;
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
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[(MAX_DIGITS - 1) - nCountDigits] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aPosTexU[(MAX_DIGITS - 1) - nCountDigits] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[(MAX_DIGITS - 1) - nCountDigits] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aPosTexU[(MAX_DIGITS - 1) - nCountDigits] * 0.1f), 1.0f);

		pVtx += 4;			// 頂点データのポインタを4つ分進める
	}

	// 頂点バッファをアンロック
	g_pVtxBuffScore->Unlock();
}

//********************************************************************************
// スコアの加算処理
//********************************************************************************
void AddScore(int nValue)
{
	// 変数宣言
	int aPosTexU[8];		// 各桁の数値を格納
	int nCountDigits;		// 桁数をカウントする

	// 変数に引数を代入
	g_nScore += nValue;

	// 数値の分解と格納
	aPosTexU[0] = g_nScore % 100000000 / 10000000;
	aPosTexU[1] = g_nScore % 10000000 / 1000000;
	aPosTexU[2] = g_nScore % 1000000 / 100000;
	aPosTexU[3] = g_nScore % 100000 / 10000;
	aPosTexU[4] = g_nScore % 10000 / 1000;
	aPosTexU[5] = g_nScore % 1000 / 100;
	aPosTexU[6] = g_nScore % 100 / 10;
	aPosTexU[7] = g_nScore % 10 / 1;

	// 頂点情報へのポインタを生成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	// 対角線の長さを算出する
	g_Score.fLength = sqrtf(((g_Score.offset.x * g_Score.offset.x) + (g_Score.offset.y * g_Score.offset.y)) / 2.0f);

	// 対角線の角度を算出
	g_Score.fAngele = atan2f(g_Score.offset.x, g_Score.offset.y);

	for (nCountDigits = 0; nCountDigits < MAX_DIGITS; nCountDigits++)
	{
		// 頂点座標の設定
		pVtx[0].pos.x = g_Score.pos[nCountDigits].x + sinf(g_Score.rot.z + (D3DX_PI + g_Score.fAngele)) * g_Score.fLength;
		pVtx[0].pos.y = g_Score.pos[nCountDigits].y + cosf(g_Score.rot.z + (D3DX_PI + g_Score.fAngele)) * g_Score.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Score.pos[nCountDigits].x + sinf(g_Score.rot.z + (D3DX_PI - g_Score.fAngele)) *  g_Score.fLength;
		pVtx[1].pos.y = g_Score.pos[nCountDigits].y + cosf(g_Score.rot.z + (D3DX_PI - g_Score.fAngele)) *  g_Score.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Score.pos[nCountDigits].x + sinf(g_Score.rot.z - (0 + g_Score.fAngele)) * g_Score.fLength;
		pVtx[2].pos.y = g_Score.pos[nCountDigits].y + cosf(g_Score.rot.z - (0 + g_Score.fAngele)) * g_Score.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Score.pos[nCountDigits].x + sinf(g_Score.rot.z - (0 - g_Score.fAngele)) *  g_Score.fLength;
		pVtx[3].pos.y = g_Score.pos[nCountDigits].y + cosf(g_Score.rot.z - (0 - g_Score.fAngele)) *  g_Score.fLength;
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
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[(MAX_DIGITS - 1) - nCountDigits] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aPosTexU[(MAX_DIGITS - 1) - nCountDigits] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[(MAX_DIGITS - 1) - nCountDigits] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aPosTexU[(MAX_DIGITS - 1) - nCountDigits] * 0.1f), 1.0f);

		pVtx += 4;		// 頂点データのポインタを4つ分進める
	}

	// 頂点バッファをアンロック
	g_pVtxBuffScore->Unlock();
}

//********************************************************************************
// スコアの情報の取得
//********************************************************************************
int GetScore(void)
{
	return g_nScore;
}