//**************************************************************************************************
//
//ランキングの設定処理
//Auther：唐﨑結斗
//
//**************************************************************************************************
#include"main.h"
#include"ranking.h"
#include"input.h"
#include"fade.h"
#include"score.h"
#include<stdio.h>
//#include"context.h"
#include"sound.h"
#include"ranking_logo.h"

#include"camera.h"
#include"light.h"
#include"model.h"
#include"shadow.h"
#include"set_motion.h"
#include"feed.h"
#include"skybox.h"
#include"effect.h"
#include"particle.h"
#include"set_file.h"
#include"meshfield.h"
#include"line.h"

//*******************************************************************************
//グローバル変数
//*******************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureRank = NULL;				//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRankScore = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;			//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankScore = NULL;		//頂点バッファへのポインタ
Rank g_aRank[MAX_RANK];									//ランキングランク情報
RankingScore g_aRankScore[MAX_RANK];					//ランキングスコア情報
int g_nRankUpdate = -1;									//更新ランクNo.
int g_nTimerRanking;									//ランキング画面表示タイマー
int g_nScoreState;										//ランキングスコアの状態
int g_nCountState;										//ランキングスコアの状態カウンター

//********************************************************************************
//ランキングの初期化処理
//********************************************************************************
void InitRanking(void)
{
	//変数宣言
	int nCountRank;
	int nCountDigits;
	int aPosTexU[MAX_RANK][MAX_RANK_DIGITS];

	//数値の分解と格納
	for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
	{
		aPosTexU[nCountRank][0] = g_aRankScore[nCountRank].nScore % 100000000 / 10000000;
		aPosTexU[nCountRank][1] = g_aRankScore[nCountRank].nScore % 10000000 / 1000000;
		aPosTexU[nCountRank][2] = g_aRankScore[nCountRank].nScore % 1000000 / 100000;
		aPosTexU[nCountRank][3] = g_aRankScore[nCountRank].nScore % 100000 / 10000;
		aPosTexU[nCountRank][4] = g_aRankScore[nCountRank].nScore % 10000 / 1000;
		aPosTexU[nCountRank][5] = g_aRankScore[nCountRank].nScore % 1000 / 100;
		aPosTexU[nCountRank][6] = g_aRankScore[nCountRank].nScore % 100 / 10;
		aPosTexU[nCountRank][7] = g_aRankScore[nCountRank].nScore % 10 / 1;
	}

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM005);

	// ライト初期化処理
	InitLight();

	// メッシュフィールド初期化処理
	InitMeshField();

	// スカイボックス初期化処理
	InitSkyBox();

	// 影初期化処理
	InitShadow();

	// ライン初期化処理
	InitLine();

	// モデル初期化処理
	InitModel();

	// 餌初期化処理
	InitFeed();

	// エフェクト初期化処理
	InitEffect();

	//// パーティクル初期化処理
	InitParticle();

	// ファイル読み込み
	LoodSetFile();

	// カメラ初期化処理
	InitCamera(D3DXVECTOR3(0.0f, 100.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.65f, D3DX_PI, 0.0f));

	//ランキングロゴの初期化処理
	InitRankingLogo();

	//ランキングロゴの設定処理
	SetRankingLogo();

	//グローバル変数の初期化
	g_nTimerRanking = MAX_TIME;
	g_nScoreState = 0;
	g_nCountState = 0;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//ポリゴンに張り付けるテクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ranking_rank.png",
		&g_pTextureRank);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK,	//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,												//頂点ファーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);

	//タイトルロゴ情報の初期化
	for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
	{
		g_aRank[nCountRank].offset = D3DXVECTOR3(MAX_OFFSET_RANK_X, MAX_OFFSET_RANK_Y, 0.0f);											//中心点からの差
		g_aRank[nCountRank].pos = D3DXVECTOR3(POS_RANK_X, POS_RANK_Y + ((g_aRank[nCountRank].offset.y  * 1.7f) * nCountRank), 0.0f);	//中心点
		g_aRank[nCountRank].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);																		//向き	 
		g_aRank[nCountRank].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);																	//カラー
	}

	//頂点情報へのポインタを生成						
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	//タイトルロゴ情報の初期化
	for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
	{
		//対角線の長さを算出する
		g_aRank[nCountRank].fLength = sqrtf(((g_aRank[nCountRank].offset.x * g_aRank[nCountRank].offset.x) + (g_aRank[nCountRank].offset.y * g_aRank[nCountRank].offset.y)) / 2.0f);

		//対角線の角度を算出
		g_aRank[nCountRank].fAngele = atan2f(g_aRank[nCountRank].offset.x, g_aRank[nCountRank].offset.y);

		//頂点座標の設定
		pVtx[0].pos.x = g_aRank[nCountRank].pos.x + sinf(g_aRank[nCountRank].rot.z + (D3DX_PI + g_aRank[nCountRank].fAngele)) * g_aRank[nCountRank].fLength;
		pVtx[0].pos.y = g_aRank[nCountRank].pos.y + cosf(g_aRank[nCountRank].rot.z + (D3DX_PI + g_aRank[nCountRank].fAngele)) * g_aRank[nCountRank].fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_aRank[nCountRank].pos.x + sinf(g_aRank[nCountRank].rot.z + (D3DX_PI - g_aRank[nCountRank].fAngele)) *  g_aRank[nCountRank].fLength;
		pVtx[1].pos.y = g_aRank[nCountRank].pos.y + cosf(g_aRank[nCountRank].rot.z + (D3DX_PI - g_aRank[nCountRank].fAngele)) *  g_aRank[nCountRank].fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_aRank[nCountRank].pos.x + sinf(g_aRank[nCountRank].rot.z - (0 + g_aRank[nCountRank].fAngele)) * g_aRank[nCountRank].fLength;
		pVtx[2].pos.y = g_aRank[nCountRank].pos.y + cosf(g_aRank[nCountRank].rot.z - (0 + g_aRank[nCountRank].fAngele)) * g_aRank[nCountRank].fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_aRank[nCountRank].pos.x + sinf(g_aRank[nCountRank].rot.z - (0 - g_aRank[nCountRank].fAngele)) *  g_aRank[nCountRank].fLength;
		pVtx[3].pos.y = g_aRank[nCountRank].pos.y + cosf(g_aRank[nCountRank].rot.z - (0 - g_aRank[nCountRank].fAngele)) *  g_aRank[nCountRank].fLength;
		pVtx[3].pos.z = 0.0f;

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = g_aRank[nCountRank].col;
		pVtx[1].col = g_aRank[nCountRank].col;
		pVtx[2].col = g_aRank[nCountRank].col;
		pVtx[3].col = g_aRank[nCountRank].col;

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + (nCountRank * 0.2f));
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + (nCountRank * 0.2f));
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.2f + (nCountRank * 0.2f));
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.2f + (nCountRank * 0.2f));

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロック
	g_pVtxBuffRank->Unlock();

	//ポリゴンに張り付けるテクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureRankScore);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK * MAX_RANK_DIGITS,			//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,																		//頂点ファーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankScore,
		NULL);

	//数値の初期化
	for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
	{
		g_aRankScore[nCountRank].offset = D3DXVECTOR3(MAX_OFFSET_RANKING_SCORE_X, MAX_OFFSET_RANKING_SCORE_Y, 0.0f);			//中心点からの差
		g_aRankScore[nCountRank].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);															//向き
		g_aRankScore[nCountRank].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);														//カラー
		g_aRankScore[nCountRank].nScore = 0;																					//スコアの値
	}
	
	//スコアの位置の初期化
	for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
	{
		for (nCountDigits = 0; nCountDigits < MAX_RANK_DIGITS; nCountDigits++)
		{
			g_aRankScore[nCountRank].pos[nCountDigits] = D3DXVECTOR3(POS_RANKING_SCORE_X - (g_aRankScore[nCountRank].offset.x * 2 * nCountDigits), g_aRank[nCountRank].pos.y, 0.0f);
		}
	}

	//頂点情報へのポインタを生成
	VERTEX_2D *pVtx0;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx0, 0);

	for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
	{
		//対角線の長さを算出する
		g_aRankScore[nCountRank].fLength = sqrtf(((g_aRankScore[nCountRank].offset.x * g_aRankScore[nCountRank].offset.x) + (g_aRankScore[nCountRank].offset.y * g_aRankScore[nCountRank].offset.y)) / 2.0f);

		//対角線の角度を算出
		g_aRankScore[nCountRank].fAngele = atan2f(g_aRankScore[nCountRank].offset.x, g_aRankScore[nCountRank].offset.y);

		for (nCountDigits = 0; nCountDigits < MAX_RANK_DIGITS; nCountDigits++)
		{
			//頂点座標の設定
			pVtx0[0].pos.x = g_aRankScore[nCountRank].pos[nCountDigits].x + sinf(g_aRankScore[nCountRank].rot.z + (D3DX_PI + g_aRankScore[nCountRank].fAngele)) * g_aRankScore[nCountRank].fLength;
			pVtx0[0].pos.y = g_aRankScore[nCountRank].pos[nCountDigits].y + cosf(g_aRankScore[nCountRank].rot.z + (D3DX_PI + g_aRankScore[nCountRank].fAngele)) * g_aRankScore[nCountRank].fLength;
			pVtx0[0].pos.z = 0.0f;

			pVtx0[1].pos.x = g_aRankScore[nCountRank].pos[nCountDigits].x + sinf(g_aRankScore[nCountRank].rot.z + (D3DX_PI - g_aRankScore[nCountRank].fAngele)) *  g_aRankScore[nCountRank].fLength;
			pVtx0[1].pos.y = g_aRankScore[nCountRank].pos[nCountDigits].y + cosf(g_aRankScore[nCountRank].rot.z + (D3DX_PI - g_aRankScore[nCountRank].fAngele)) *  g_aRankScore[nCountRank].fLength;
			pVtx0[1].pos.z = 0.0f;

			pVtx0[2].pos.x = g_aRankScore[nCountRank].pos[nCountDigits].x + sinf(g_aRankScore[nCountRank].rot.z - (0 + g_aRankScore[nCountRank].fAngele)) * g_aRankScore[nCountRank].fLength;
			pVtx0[2].pos.y = g_aRankScore[nCountRank].pos[nCountDigits].y + cosf(g_aRankScore[nCountRank].rot.z - (0 + g_aRankScore[nCountRank].fAngele)) * g_aRankScore[nCountRank].fLength;
			pVtx0[2].pos.z = 0.0f;

			pVtx0[3].pos.x = g_aRankScore[nCountRank].pos[nCountDigits].x + sinf(g_aRankScore[nCountRank].rot.z - (0 - g_aRankScore[nCountRank].fAngele)) *  g_aRankScore[nCountRank].fLength;
			pVtx0[3].pos.y = g_aRankScore[nCountRank].pos[nCountDigits].y + cosf(g_aRankScore[nCountRank].rot.z - (0 - g_aRankScore[nCountRank].fAngele)) *  g_aRankScore[nCountRank].fLength;
			pVtx0[3].pos.z = 0.0f;

			//rhwの設定
			pVtx0[0].rhw = 1.0f;
			pVtx0[1].rhw = 1.0f;
			pVtx0[2].rhw = 1.0f;
			pVtx0[3].rhw = 1.0f;

			//頂点カラーの設定
			pVtx0[0].col = g_aRankScore[nCountRank].col;
			pVtx0[1].col = g_aRankScore[nCountRank].col;
			pVtx0[2].col = g_aRankScore[nCountRank].col;
			pVtx0[3].col = g_aRankScore[nCountRank].col;

			//テクスチャ座標
			pVtx0[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCountRank][(MAX_RANK_DIGITS - 1) - nCountDigits] * 0.1f), 0.0f);
			pVtx0[1].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCountRank][(MAX_RANK_DIGITS - 1) - nCountDigits] * 0.1f), 0.0f);
			pVtx0[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCountRank][(MAX_RANK_DIGITS - 1) - nCountDigits] * 0.1f), 1.0f);
			pVtx0[3].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCountRank][(MAX_RANK_DIGITS - 1) - nCountDigits] * 0.1f), 1.0f);

			pVtx0 += 4;	//頂点データのポインタを4つ分進める
		}
	}

	//頂点バッファをアンロック
	g_pVtxBuffRankScore->Unlock();
}

//********************************************************************************
//ランキングの終了処理
//********************************************************************************
void UninitRanking(void)
{
	//数値の初期化
	g_nRankUpdate = -1;

	//サウンド終了処理
	StopSound();

	// カメラ終了処理
	UninitCamera();

	// ライト終了処理
	UninitLight();

	// メッシュフィールド終了処理
	UninitMeshField();

	// スカイボックス終了処理
	UninitSkyBox();

	// モデル終了処理
	UninitModel();

	// 餌終了処理
	UninitFeed();

	// 影終了処理
	UninitShadow();

	// エフェクト終了処理
	UninitEffect();

	//ランキングロゴの終了処理
	UninitRankingLogo();

	//テクスチャの破棄	  
	if (g_pTextureRank != NULL)
	{
		g_pTextureRank->Release();

		g_pTextureRank = NULL;
	}
	if (g_pTextureRankScore != NULL)
	{
		g_pTextureRankScore->Release();

		g_pTextureRankScore = NULL;
	}

	//頂点バッファを破棄
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();

		g_pVtxBuffRank = NULL;
	}
	if (g_pVtxBuffRankScore != NULL)
	{
		g_pVtxBuffRankScore->Release();

		g_pVtxBuffRankScore = NULL;
	}
}

//********************************************************************************
//ランキングの更新処理
//********************************************************************************
void UpdateRanking(void)
{
	//// ジョイパッドの使用情報の取得
	//bool bUseJoyPad = GetUseJoyPad();

	// カメラ更新処理
	UpdateCamera();

	// ライト更新処理
	UpdateLight();

	// メッシュフィールド更新処理
	UpdateMeshField();

	// スカイボックス更新処理
	UpdateSkyBox();

	// モデル更新処理
	UpdateModel();

	// 餌更新処理
	UpdateFeed();

	// 魚の設置
	SetControllerFeed();

	// 影更新処理
	UpdateShadow();

	// エフェクト更新処理
	UpdateEffect();

	//ランキングロゴの更新処理
	UpdateRankingLogo();

	//変数宣言
	int nCountDigits;

	//フェード情報の取得
	FADE fade;			//フェード情報へのポインタ
	fade = GetFade();

	//頂点情報へのポインタを生成
	VERTEX_2D *pVtx0;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx0, 0);

	if (g_nRankUpdate != -1)
	{//スコアが更新された
		//カラーの更新
		g_aRankScore[g_nRankUpdate].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		g_nCountState++;

		if (g_nCountState % 3 == 0)
		{
			g_nScoreState ^= 1;

			g_aRankScore[g_nRankUpdate].col.a = (1.0f * g_nScoreState);
		}

		//頂点情報を更新
		pVtx0 += MAX_RANK_DIGITS * g_nRankUpdate * 4;

		for (nCountDigits = 0; nCountDigits < MAX_RANK_DIGITS; nCountDigits++)
		{
			//頂点カラーの設定
			pVtx0[0].col = g_aRankScore[g_nRankUpdate].col;
			pVtx0[1].col = g_aRankScore[g_nRankUpdate].col;
			pVtx0[2].col = g_aRankScore[g_nRankUpdate].col;
			pVtx0[3].col = g_aRankScore[g_nRankUpdate].col;

			pVtx0 += 4;	//頂点データのポインタを4つ分進める
		}
	}

	//時間の更新
	g_nTimerRanking--;

	if (g_nTimerRanking <= 0 || GetKeyboardTrigger(DIK_RETURN) == true)
	{//一定時間経過、又はEnterキーが押された
		if (fade == FADE_NONE)
		{//フェードが行われてないとき
		 //フェードの設定
			SetFade(MODE_TITLE);
		}
	}

	//頂点バッファをアンロック
	g_pVtxBuffRankScore->Unlock();
}

//********************************************************************************
//ランキングの描画処理
//********************************************************************************
void DrawRanking(void)
{
	// カメラ設定処理
	SetCamera();

	// メッシュフィールド描画処理
	DrawMeshField();

	// スカイボックス描画処理
	DrawSkyBox();

	// モデル描画処理
	DrawModel();

	// 餌描画処理
	DrawFeed();

	// 影描画処理
	DrawShadow();

	// エフェクト描画処理
	DrawEffect();

	//ランキングロゴの描画処理
	DrawRankingLogo();

	//変数宣言
	int nCountRank;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureRank);

		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCountRank * 4,
			2);
	}

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRankScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCountRank = 0; nCountRank < MAX_RANK * MAX_RANK_DIGITS; nCountRank++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureRankScore);

		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCountRank * 4,
			2);
	}
}

//********************************************************************************
//ランキングのリセット処理
//********************************************************************************
void ResetRanking(void)
{
	//変数宣言
	int nCountRank;
	FILE * pFile;

#ifdef	NDEBUG
	char aFile[128] = FILE_RANKING_DATA;
	strcat(aFile, FILE_RANKING_NAME001);

	//ファイルを開く
	pFile = fopen(aFile, "rb");

	//条件式が真の場合実行
	if (pFile != NULL)
	{//ファイルが開けた場合
		for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
		{
			fread(&g_aRankScore[nCountRank].nScore, sizeof(int), 1, pFile);
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("\n * * * ファイルが開けませんでした * * * \n");
	}
#endif
#ifdef _DEBUG
	char aFile[128] = FILE_RANKING_DATA;
	strcat(aFile, FILE_RANKING_NAME000);

	//ファイルを開く
	pFile = fopen(aFile, "r");

	//条件式が真の場合
	if (pFile != NULL)
	{//ファイルが開いた場合
		for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
		{
			//データの読み込み
			fscanf(pFile, "%d", &g_aRankScore[nCountRank].nScore);
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けない場合
		printf("\n * * * ファイルが開けません * * * \n");
	}
#endif
}

//********************************************************************************
//ランキングの設定処理
//********************************************************************************
void SetRanking(int nScore)
{
	//変数宣言
	int nCountRank;
	int nCountRank1;
	int nReplacementScore;
	int nCntReplacement;
	FILE * pFile;

	if (g_aRankScore[MAX_RANK - 1].nScore < nScore)
	{//スコアが更新された
		g_aRankScore[MAX_RANK - 1].nScore = nScore;
		g_nRankUpdate++;

		for (nCountRank = 0; nCountRank < MAX_RANK - 1; nCountRank++)
		{
			//代入した回数をカウントする数値をリセット
			nCntReplacement = nCountRank;

			for (nCountRank1 = nCountRank + 1; nCountRank1 < MAX_RANK; nCountRank1++)
			{
				//条件式が真の場合実行
				if (g_aRankScore[nCntReplacement].nScore < g_aRankScore[nCountRank1].nScore)
				{
					//代入した回数をカウント
					nCntReplacement = nCountRank1;

					g_nRankUpdate++;
				}
			}

			//数値の入れ替え
			nReplacementScore = g_aRankScore[nCntReplacement].nScore;
			g_aRankScore[nCntReplacement].nScore = g_aRankScore[nCountRank].nScore;
			g_aRankScore[nCountRank].nScore = nReplacementScore;
		}

		g_nRankUpdate = ((MAX_RANK - 1) - g_nRankUpdate);
	}

#ifdef	NDEBUG
	char aFile[128] = FILE_RANKING_DATA;
	strcat(aFile, FILE_RANKING_NAME001);

	//ファイルを開く
	pFile = fopen(aFile, "wb");

	if (pFile != NULL)
	{//ファイルが開けた場合
		for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
		{
			fwrite(&g_aRankScore[nCountRank].nScore, sizeof(int), 1, pFile);
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("\n * * * ファイルが開けませんでした * * * \n");
	}
#endif
#ifdef _DEBUG
	char aFile[128] = FILE_RANKING_DATA;
	strcat(aFile, FILE_RANKING_NAME000);
	//ファイルを開く
	pFile = fopen(aFile, "w");

	if (pFile != NULL)
	{//ファイルが開いた場合
		for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
		{
			//データの読み込み
			fprintf(pFile, "%d\n", g_aRankScore[nCountRank].nScore);
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けない場合
		printf("\n * * * ファイルが開けません * * * \n");
	}
#endif
}