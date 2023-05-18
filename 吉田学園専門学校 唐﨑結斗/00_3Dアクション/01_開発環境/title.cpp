//**************************************************************************************************
//
// タイトル画面の設定処理
// Auther：唐﨑結斗
//
//**************************************************************************************************

#include"title.h"
#include"input.h"
#include"sound.h"
#include"fade.h"
#include"titlelogo.h"
#include"press enter.h"
#include"ranking.h"

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
#include"combo.h"

//*******************************************************************************
// グローバル変数
//*******************************************************************************
int g_nCntTimeRanking;

//********************************************************************************
// タイトル画面の初期化処理
//********************************************************************************
void InitTitle(void)
{
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

	// 時間を初期化
	g_nCntTimeRanking = 0;

	// タイトルロゴの初期化処理
	InitTitleLogo();

	// プレスエンターの初期化処理
	InitPressEnter();

	// コンボの初期化
	InitCombo();

	// サウンド再生
	PlaySound(SOUND_LABEL_BGM000);
}

//********************************************************************************
// タイトル画面の終了処理
//********************************************************************************
void UninitTitle(void)
{ 
	//サウンド終了処理
	StopSound();

	// プレスエンターの終了処理
	UninitPressEnter();

	// タイトルロゴの終了処理
	UninitTitleLogo();

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
}

//********************************************************************************
//タイトル画面の更新処理
//********************************************************************************
void UpdateTitle(void)
{
	// フェード情報の取得
	FADE fade;			// フェード情報へのポインタ
	fade = GetFade();

	// 時間の加算
	g_nCntTimeRanking++;

	// プレスエンターの更新処理
	UpdatePressEnter();

	// タイトルロゴの更新処理
	UpdateTitleLogo();

	//// 背景の更新処理
	//UpdateContext();

	// タイトルロゴの設定処理
	SetTitleLogo();

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

	// パーティクル更新処理
	UpdateParticle();

	// 一定時間でランキング画面に遷移
	if (g_nCntTimeRanking % MAX_RANKING_TIME == 0)
	{
		if (fade == FADE_NONE)
		{// フェードが行われてないとき
			// フェードの設定
			SetFade(MODE_RANKING);

			// ランキングリセット
			ResetRanking();
		}
	}
}

//********************************************************************************
// タイトル画面の描画処理
//********************************************************************************
void DrawTitle(void)
{
	//// 背景の描画処理
	//DrawContext();

	// タイトルロゴの描画処理
	DrawTitleLogo();

	// プレスエンターの描画処理
	DrawPressEnter();

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
}