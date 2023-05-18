//**************************************************************************************************
//
// 時間の処理
// Auther：唐﨑結斗
//
//**************************************************************************************************

#include"main.h"
//#include"sound.h"

#include"time.h"
#include"player.h"
#include"score.h"
#include"fade.h"

//*************************************************************
// グローバル変数
//*************************************************************
static LPDIRECT3DTEXTURE9			g_pTextureTime = NULL;			// テクスチャへのポインタ
static LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffTime = NULL;			// 頂点バッファへのポインタ
static Time							g_Time;							// 時間情報

//---------------------------------------------------------------------------
// 時間の初期化処理
//---------------------------------------------------------------------------
void InitTime(void)
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
		&g_pTextureTime);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * MAX_VERTEX * MAX_TIME_DIGITS * MAX_TIME_SEPARATION,	// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,																					// 頂点ファーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	// 数値の初期化
	g_Time.size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 中心点からの差
	g_Time.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向き
	g_Time.nTime = 0;
	g_Time.nMinutes = 0;
	g_Time.nSeconds = 0;
	g_Time.nMillisecond = 0;	

	// 時間の位置の初期化
	for (nCountDigits = 0; nCountDigits < MAX_TIME_DIGITS * MAX_TIME_SEPARATION; nCountDigits++)
	{
		g_Time.pos[nCountDigits] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// 頂点情報へのポインタを生成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	// 対角線の長さを算出する
	g_Time.fLength = sqrtf(((g_Time.size.x * g_Time.size.x) + (g_Time.size.y * g_Time.size.y)) / 2.0f);

	// 対角線の角度を算出
	g_Time.fAngele = atan2f(g_Time.size.x, g_Time.size.y);

	for (nCountDigits = 0; nCountDigits < MAX_TIME_DIGITS * MAX_TIME_SEPARATION; nCountDigits++)
	{
		// 頂点座標の設定
		pVtx[0].pos.x = g_Time.pos[nCountDigits].x + sinf(g_Time.rot.z + (D3DX_PI + g_Time.fAngele)) * g_Time.fLength;
		pVtx[0].pos.y = g_Time.pos[nCountDigits].y + cosf(g_Time.rot.z + (D3DX_PI + g_Time.fAngele)) * g_Time.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Time.pos[nCountDigits].x + sinf(g_Time.rot.z + (D3DX_PI - g_Time.fAngele)) *  g_Time.fLength;
		pVtx[1].pos.y = g_Time.pos[nCountDigits].y + cosf(g_Time.rot.z + (D3DX_PI - g_Time.fAngele)) *  g_Time.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Time.pos[nCountDigits].x + sinf(g_Time.rot.z - (0 + g_Time.fAngele)) * g_Time.fLength;
		pVtx[2].pos.y = g_Time.pos[nCountDigits].y + cosf(g_Time.rot.z - (0 + g_Time.fAngele)) * g_Time.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Time.pos[nCountDigits].x + sinf(g_Time.rot.z - (0 - g_Time.fAngele)) *  g_Time.fLength;
		pVtx[3].pos.y = g_Time.pos[nCountDigits].y + cosf(g_Time.rot.z - (0 - g_Time.fAngele)) *  g_Time.fLength;
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
		float fDivision = 1.0f / 10.0f;
		pVtx[0].tex = D3DXVECTOR2(0.0f + (g_Time.nTime * fDivision), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(fDivision + (g_Time.nTime * fDivision), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (g_Time.nTime * fDivision), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(fDivision + (g_Time.nTime * fDivision), 1.0f);

		pVtx += 4;		// 頂点データのポインタを4つ分進める
	}

	// 頂点バッファをアンロック
	g_pVtxBuffTime->Unlock();
}

//---------------------------------------------------------------------------
// 時間の終了処理
//---------------------------------------------------------------------------
void UninitTime(void)
{
	// テクスチャの破棄	  
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();

		g_pTextureTime = NULL;
	}

	// 頂点バッファを破棄
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();

		g_pVtxBuffTime = NULL;
	}
}

//---------------------------------------------------------------------------
// 時間の更新処理
//---------------------------------------------------------------------------
void UpdateTime(void)
{
	// 時間の更新
	SubTime();

	if (g_Time.nTime == 0 && g_Time.nMillisecond == 0)
	{
		//フェード情報の取得
		FADE fade;			//フェード情報へのポインタ
		fade = GetFade();

		//プレイヤー情報の取得
		Player *pPlayer;
		pPlayer = GetPlayer();

		if (pPlayer->nMaxCombo < pPlayer->nCntCombo)
		{
			pPlayer->nMaxCombo = pPlayer->nCntCombo;
		}

		if (fade == FADE_NONE)
		{//フェードが行われてないとき
			//リザルト画面へ移動
			SetFade(MODE_RESULT);
		}
	}
	
}

//---------------------------------------------------------------------------
// 時間の描画処理
//---------------------------------------------------------------------------
void DrawTime(void)
{
	// 変数宣言
	int nCountDigits;		// 桁数をカウントする

	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0,sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCountDigits = 0; nCountDigits < MAX_TIME_DIGITS * MAX_TIME_SEPARATION; nCountDigits++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTime);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCountDigits * 4,
			2);
	}
}

//---------------------------------------------------------------------------
// 時間の設定処理
//---------------------------------------------------------------------------
void SetTime(int nTime, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 変数宣言
	int aPosTexU[MAX_TIME_DIGITS];		// 各桁の数値を格納
	int nCountDigits;					// 桁数をカウントする

	// 変数に引数を代入
	g_Time.size = size;
	g_Time.nTime = nTime;

	// 分の算出
	g_Time.nMinutes = g_Time.nTime / 60;

	if (g_Time.nTime >= 60)
	{// 時間が60を超えたとき
		g_Time.nSeconds = g_Time.nTime - (60 * g_Time.nMinutes);
	}
	else
	{// 60以外の時
		g_Time.nSeconds = g_Time.nTime;
	}
	
	// ミリ秒に0を代入
	g_Time.nMillisecond = 0;

	// 頂点情報へのポインタを生成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTime = 0; nCntTime < MAX_TIME_SEPARATION; nCntTime++)
	{
		// 変数宣言
		int nNumTime;

		if (nCntTime == 0)
		{// 分を代入
			nNumTime = g_Time.nMinutes;
		}
		else if (nCntTime == 1)
		{// 秒の代入
			nNumTime = g_Time.nSeconds;
		}
		else
		{// ミリ秒の代入
			nNumTime = g_Time.nMillisecond;
		}

		// 数値の分解と格納
		aPosTexU[0] = nNumTime % 100 / 10;
		aPosTexU[1] = nNumTime % 10 / 1;

		// 時間の位置の設定
		for (nCountDigits = nCntTime * MAX_TIME_DIGITS; nCountDigits < MAX_TIME_DIGITS + nCntTime * MAX_TIME_DIGITS; nCountDigits++)
		{
			g_Time.pos[nCountDigits] = D3DXVECTOR3(pos.x + (g_Time.size.x * nCntTime) + (g_Time.size.x + (g_Time.size.x * 2) * nCountDigits), pos.y + g_Time.size.y, 0.0f);
		}

		// 対角線の長さを算出する
		g_Time.fLength = sqrtf(((g_Time.size.x * g_Time.size.x) + (g_Time.size.y * g_Time.size.y)) / 2.0f);

		// 対角線の角度を算出
		g_Time.fAngele = atan2f(g_Time.size.x, g_Time.size.y);

		for (nCountDigits = nCntTime * MAX_TIME_DIGITS; nCountDigits < MAX_TIME_DIGITS + nCntTime * MAX_TIME_DIGITS; nCountDigits++)
		{
			// 頂点座標の設定
			pVtx[0].pos.x = g_Time.pos[nCountDigits].x + sinf(g_Time.rot.z + (D3DX_PI + g_Time.fAngele)) * g_Time.fLength;
			pVtx[0].pos.y = g_Time.pos[nCountDigits].y + cosf(g_Time.rot.z + (D3DX_PI + g_Time.fAngele)) * g_Time.fLength;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_Time.pos[nCountDigits].x + sinf(g_Time.rot.z + (D3DX_PI - g_Time.fAngele)) *  g_Time.fLength;
			pVtx[1].pos.y = g_Time.pos[nCountDigits].y + cosf(g_Time.rot.z + (D3DX_PI - g_Time.fAngele)) *  g_Time.fLength;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_Time.pos[nCountDigits].x + sinf(g_Time.rot.z - (0 + g_Time.fAngele)) * g_Time.fLength;
			pVtx[2].pos.y = g_Time.pos[nCountDigits].y + cosf(g_Time.rot.z - (0 + g_Time.fAngele)) * g_Time.fLength;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_Time.pos[nCountDigits].x + sinf(g_Time.rot.z - (0 - g_Time.fAngele)) *  g_Time.fLength;
			pVtx[3].pos.y = g_Time.pos[nCountDigits].y + cosf(g_Time.rot.z - (0 - g_Time.fAngele)) *  g_Time.fLength;
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

			int nNumTex = (nCountDigits - (nCntTime * MAX_TIME_DIGITS));

			// テクスチャ座標
			float fDivision = 1.0f / 10.0f;
			pVtx[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[nNumTex] * fDivision), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(fDivision + (aPosTexU[nNumTex] * fDivision), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[nNumTex] * fDivision), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(fDivision + (aPosTexU[nNumTex] * fDivision), 1.0f);

			pVtx += 4;			// 頂点データのポインタを4つ分進める
		}
	}

	// 頂点バッファをアンロック
	g_pVtxBuffTime->Unlock();
}

//---------------------------------------------------------------------------
// 時間の減算処理
//---------------------------------------------------------------------------
void SubTime(void)
{
	// 変数宣言
	int aPosTexU[MAX_TIME_DIGITS];		// 各桁の数値を格納
	int nCountDigits;					// 桁数をカウントする

	g_Time.nTime = (g_Time.nMinutes * 60) + g_Time.nSeconds;

	if (g_Time.nTime >= 0)
	{
		g_Time.nMillisecond--;

		if (g_Time.nMillisecond < 0)
		{
			g_Time.nMillisecond = 59;
			g_Time.nTime--;

			if (g_Time.nTime <= 0)
			{
				g_Time.nTime = 0;
				g_Time.nMillisecond = 0;
			}
		}
	}
	
	g_Time.nMinutes = g_Time.nTime / 60;

	if (g_Time.nTime >= 60)
	{
		g_Time.nSeconds = g_Time.nTime - (60 * g_Time.nMinutes);
	}
	else
	{
		g_Time.nSeconds = g_Time.nTime;
	}

	// 頂点情報へのポインタを生成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTime = 0; nCntTime < MAX_TIME_SEPARATION; nCntTime++)
	{
		int nNumTime;

		if (nCntTime == 0)
		{
			nNumTime = g_Time.nMinutes;
		}
		else if (nCntTime == 1)
		{
			nNumTime = g_Time.nSeconds;
		}
		else
		{
			nNumTime = g_Time.nMillisecond;
		}

		// 数値の分解と格納
		aPosTexU[0] = nNumTime % 100 / 10;
		aPosTexU[1] = nNumTime % 10 / 1;

		// 対角線の長さを算出する
		g_Time.fLength = sqrtf(((g_Time.size.x * g_Time.size.x) + (g_Time.size.y * g_Time.size.y)) / 2.0f);

		// 対角線の角度を算出
		g_Time.fAngele = atan2f(g_Time.size.x, g_Time.size.y);

		for (nCountDigits = nCntTime * MAX_TIME_DIGITS; nCountDigits < MAX_TIME_DIGITS + nCntTime * MAX_TIME_DIGITS; nCountDigits++)
		{
			// 頂点座標の設定
			pVtx[0].pos.x = g_Time.pos[nCountDigits].x + sinf(g_Time.rot.z + (D3DX_PI + g_Time.fAngele)) * g_Time.fLength;
			pVtx[0].pos.y = g_Time.pos[nCountDigits].y + cosf(g_Time.rot.z + (D3DX_PI + g_Time.fAngele)) * g_Time.fLength;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_Time.pos[nCountDigits].x + sinf(g_Time.rot.z + (D3DX_PI - g_Time.fAngele)) *  g_Time.fLength;
			pVtx[1].pos.y = g_Time.pos[nCountDigits].y + cosf(g_Time.rot.z + (D3DX_PI - g_Time.fAngele)) *  g_Time.fLength;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_Time.pos[nCountDigits].x + sinf(g_Time.rot.z - (0 + g_Time.fAngele)) * g_Time.fLength;
			pVtx[2].pos.y = g_Time.pos[nCountDigits].y + cosf(g_Time.rot.z - (0 + g_Time.fAngele)) * g_Time.fLength;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_Time.pos[nCountDigits].x + sinf(g_Time.rot.z - (0 - g_Time.fAngele)) *  g_Time.fLength;
			pVtx[3].pos.y = g_Time.pos[nCountDigits].y + cosf(g_Time.rot.z - (0 - g_Time.fAngele)) *  g_Time.fLength;
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

			int nNumTex = (nCountDigits - (nCntTime * MAX_TIME_DIGITS));

			// テクスチャ座標
			float fDivision = 1.0f / 10.0f;
			pVtx[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[nNumTex] * fDivision), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(fDivision + (aPosTexU[nNumTex] * fDivision), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[nNumTex] * fDivision), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(fDivision + (aPosTexU[nNumTex] * fDivision), 1.0f);

			pVtx += 4;		// 頂点データのポインタを4つ分進める
		}
	}

	// 頂点バッファをアンロック
	g_pVtxBuffTime->Unlock();
}

//---------------------------------------------------------------------------
// 時間の情報の取得
//---------------------------------------------------------------------------
int GetTime(void)
{
	return g_Time.nTime;
}