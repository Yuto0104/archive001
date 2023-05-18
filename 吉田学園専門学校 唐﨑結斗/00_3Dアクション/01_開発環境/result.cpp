//**************************************************************************************************
//
//リザルト画面の設定処理
//Auther：唐﨑結斗
//
//**************************************************************************************************
#include "main.h"

#include"result.h"
#include"input.h"
#include"sound.h"
#include"fade.h"
//#include"context.h"
#include"result bg.h"
#include"score.h"
#include"ranking.h"
#include"player.h"
#include"time.h"
#include"result_menu.h"
#include"combo.h"

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
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;		//頂点バッファへのポインタ

//********************************************************************************
//リザルト画面の初期化処理
//********************************************************************************
void InitResult(void)
{
	// プレイヤー情報の取得
	Player *pPlayer = GetPlayer();

	////背景の初期化処理
	//InitContext();

	//リザルト背景の初期化処理
	InitResultBG();
	SetResultBG();

	//スコア情報の取得
	int pScore;							//スコア情報のポインタ
	pScore = GetScore();
	
	//スコアの初期化処理
	InitScore();

	//スコアの設定処理
	SetScore(pScore, D3DXVECTOR3(1200, 440.0f, 0.0f), D3DXVECTOR3(30.0f, 60.0f, 0.0f));

	//時間の初期化処理
	InitTime();

	// コンボの初期化
	InitCombo();
	SetCombo(pPlayer->nMaxCombo, D3DXVECTOR3((30.0f * 2) * 3.0f + 1020.0f, 330.0f, 0.0f), D3DXVECTOR3(30.0f, 60.0f, 0.0f));

	// リザルトメニューの初期化
	InitResultMenu();
	SetResultMenu();

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

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM007);
}

//********************************************************************************
//リザルト画面の終了処理
//********************************************************************************
void UninitResult(void)
{
	//サウンド終了処理
	StopSound();

	////背景の終了処理
	//UninitContext();

	//スコアの終了処理
	UninitScore();

	//時間の終了処理
	UninitTime();

	// コンボの終了処理
	UninitCombo();

	//リザルト背景の終了処理
	UninitResultBG();

	// リザルトメニューの終了処理
	UninitResultMenu();

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
//リザルト画面の更新処理
//********************************************************************************
void UpdateResult(void)
{
	//// ジョイパッドの使用情報の取得
	//bool bUseJoyPad = GetUseJoyPad();

	////背景の更新処理
	//UpdateContext();

	//リザルト背景の更新処理
	UpdateResultBG();

	//スコアの更新処理
	UpdateScore();

	// コンボの更新処理
	UpdateCombo();

	// リザルトメニューの更新処理
	UpdateResultMenu();

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

	//フェード情報の取得
	FADE fade;			//フェード情報へのポインタ
	fade = GetFade();

	if (fade == FADE_NONE)
	{//フェードが行われてないとき
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{//[Enter]キーが押された
			//フェードの設定
			SetFade(MODE_RANKING);

			//ランキングリセット
			ResetRanking();

			//ランキング設定処理
			SetRanking(GetScore());
		}
	}
}

//********************************************************************************
//リザルト画面の描画処理
//********************************************************************************
void DrawResult(void)
{
	////背景の描画処理
	//DrawContext();

	//リザルト背景の描画処理
	DrawResultBG();

	//スコアの描画処理
	DrawScore();

	//時間の描画処理
	DrawTime();

	// コンボの描画処理
	DrawCombo();

	// リザルトメニューの画処理
	DrawResultMenu();

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