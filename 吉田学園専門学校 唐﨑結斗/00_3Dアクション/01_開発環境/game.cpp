//**************************************************************************************************
//
// ゲーム画面の設定処理
// Auther：唐﨑結斗
// 
//**************************************************************************************************
#include"game.h"
#include"input.h"
#include"sound.h"
#include"pause.h"
#include"fade.h"

#include"score.h"
#include"time.h"
#include"combo.h"

#include"polygon.h"
#include"camera.h"
#include"light.h"
#include"model.h"
#include"shadow.h"
#include"wall.h"
#include"billboard.h"
#include"set_file.h"
#include"meshfield.h"
#include"cylinder.h"
#include"sphere.h"
#include"skybox.h"
#include"effect.h"
#include"particle.h"
#include"player.h"
#include"line.h"
#include"set_motion.h"
#include"feed.h"
#include"stamina_gauge.h"

//*************************************************************
// マクロ定義
//*************************************************************
#define		MAX_GAME_SPEED		(5)			// ゲームの進行速度の最大値

//*************************************************************
// グローバル変数
//*************************************************************
int g_nGameSpeed = 1;		// ゲームの進行速度

//**********************************************************************************
// ゲーム画面の初期化処理
//**********************************************************************************
void InitGame(void)
{
	// ゲームの進行速度を初期化
	g_nGameSpeed = 1;

	// ライト初期化処理
	InitLight();

	// ポリゴン初期化処理
	InitPolygon();

	// メッシュフィールド初期化処理
	InitMeshField();

	// 円柱初期化処理
	//InitCylinder();

	// 球初期化処理
	//InitSphere();

	// スカイボックス初期化処理
	InitSkyBox();

	// 影初期化処理
	InitShadow();

	// モデル初期化処理
	InitModel();

	// プレイヤー初期化処理
	InitPlayer();

	// 餌初期化処理
	InitFeed();

	// ライン初期化処理
	InitLine();

	// ビルボード初期化処理
	InitBillboard();
	/*SetBillboard(D3DXVECTOR3(200.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f);*/

	// エフェクト初期化処理
	InitEffect();

	//// パーティクル初期化処理
	InitParticle();

	//SetParticle(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//	D3DXVECTOR3(400.0f, 0.0f, 400.0f),
	//	D3DXVECTOR3(0.0f, 1.0f, 0.0f),
	//	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
	//	5.0f,
	//	1.0f,
	//	-1.0f,
	//	180,
	//	5,
	//	0,
	//	5,
	//	false);

	// 壁初期化処理
	InitWall();
	/*SetWall(D3DXVECTOR3(0.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetWall(D3DXVECTOR3(200.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetWall(D3DXVECTOR3(-200.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));*/

	//SetWall(D3DXVECTOR3(0.0f, 0.0f, 200.0f), D3DXVECTOR3(0.5f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	//SetWall(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	//SetWall(D3DXVECTOR3(200.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, -0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	//SetWall(D3DXVECTOR3(-200.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	// ファイル読み込み
	LoodSetFile();

	// プレイヤーの読み込み
	LoodSetMotion("motion.txt");
	
	// スコアの初期化処理
	InitScore();
	SetScore(0, D3DXVECTOR3(SCREEN_WIDH, 0.0f, 0.0f), D3DXVECTOR3(15.0f, 30.0f, 0.0f));

	// 時間の初期化処理
	InitTime();
	SetTime(90, D3DXVECTOR3(640.0f - ((10.0f * 2) * 8), 0.0f, 0.0f), D3DXVECTOR3(20.0f, 40.0f, 0.0f));

	// コンボの初期化
	InitCombo();

	// スタミナゲージの初期化
	InitStaminaGauge();
	SetStaminaGauge(D3DXVECTOR3(10.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * -0.5f), D3DXVECTOR3(30.0f, 300.0f, 0.0f), 0);

	// ポーズの初期化処理
	InitPause();

	// カメラ初期化処理
	InitCamera(D3DXVECTOR3(0.0f, 50.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(2.2f, D3DX_PI, 0.0f));

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM001);
}

//*************************************************************************************
// ゲーム画面の終了処理
//*************************************************************************************
void UninitGame(void)
{
	// カメラ終了処理
	UninitCamera();

	// ライト終了処理
	UninitLight();

	// ポリゴン終了処理
	UninitPolygon();

	// メッシュフィールド終了処理
	UninitMeshField();

	// 円柱終了処理
	//UninitCylinder();

	// 球終了処理
	//UninitSphere();

	// スカイボックス終了処理
	UninitSkyBox();

	// モデル終了処理
	UninitModel();

	// プレイヤー終了処理
	UninitPlayer();

	// 餌終了処理
	UninitFeed();

	// ライン終了処理
	UninitLine();

	// 影終了処理
	UninitShadow();

	// ビルボード終了処理
	UninitBillboard();

	// 壁終了処理
	UninitWall();

	// エフェクト終了処理
	UninitEffect();

	// スコアの終了処理
	UninitScore();

	// 時間の終了処理
	UninitTime();

	// コンボの終了処理
	UninitCombo();

	// スタミナゲージの終了処理
	UninitStaminaGauge();

	// ポーズの終了処理
	UninitPause();

	//サウンド終了処理
	StopSound();
}

//**************************************************************************************
// ゲーム画面の更新処理
//**************************************************************************************
void UpdateGame(void)
{
	//// ジョイパッドの使用情報の取得
	//bool bUseJoyPad = GetUseJoyPad();

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_RSHIFT) == true)
	{
		g_nGameSpeed++;

		if (g_nGameSpeed > MAX_GAME_SPEED)
		{
			g_nGameSpeed = 1;
		}
	}
#endif
	//プレイヤー情報の取得
	Player *pPlayer;
	pPlayer = GetPlayer();

	// ポーズ情報の取得
	Pause *pPause;				// ポーズ情報へのポインタ
	pPause = GetPause();

	// フェード情報の取得
	FADE fade;			// フェード情報へのポインタ
	fade = GetFade();

	if (pPause->bDisp == false)
	{// ポーズしてない時

		for (int nCnt = 0; nCnt < g_nGameSpeed; nCnt++)
		{
			// カメラ更新処理
			UpdateCamera();

			// ライト更新処理
			UpdateLight();

			// ポリゴン更新処理
			UpdatePolygon();

			// メッシュフィールド更新処理
			UpdateMeshField();

			// 円柱更新処理
			//UpdateCylinder();
			
			// 球更新処理
			//UpdateSphere();

			// スカイボックス更新処理
			UpdateSkyBox();

			// モデル更新処理
			UpdateModel();

			// プレイヤー更新処理
			UpdatePlayer();

			// 餌更新処理
			UpdateFeed();

			// 魚の設置
			SetControllerFeed();

			// ライン更新処理
			UpdateLine();

			// 影更新処理
			UpdateShadow();

			// ビルボード更新処理
			UpdateBillboard();

			// 壁更新処理
			UpdateWall();

			// エフェクト更新処理
			UpdateEffect();

			// パーティクル更新処理
			UpdateParticle();

			// スコアの更新処理
			UpdateScore();

			// コンボの更新処理
			UpdateCombo();

			// スタミナゲージの更新処理
			UpdateStaminaGauge();

			// 時間の更新処理
			UpdateTime();
		}

		if (fade == FADE_NONE)
		{// フェードが行われてないとき
			if (GetKeyboardTrigger(DIK_P) == true)
			{// [P]キーが押された
			 // ポーズの設定処理
				SetPause();

				// サウンド再生
				PlaySound(SOUND_LABEL_SE_PAUSE);
			}
		}
	}
	else if (pPause->bDisp == true)
	{// ポーズ時
		// ポーズの更新処理
		UpdatePause();
	}
}

//**************************************************************************************
//ゲーム画面の描画処理
//**************************************************************************************
void DrawGame(void)
{
	// カメラ設定処理
	SetCamera();
	
	//// ポリゴン描画処理
	//DrawPolygon();

	// メッシュフィールド描画処理
	DrawMeshField();

	// 円柱描画処理
	//DrawCylinder();

	//// 球描画処理
	//DrawSphere();

	// スカイボックス描画処理
	DrawSkyBox();

	// モデル描画処理
	DrawModel();

	// プレイヤー描画処理
	DrawPlayer();

	// 餌描画処理
	DrawFeed();

	// ライン描画処理
	DrawLine();

	// 壁描画処理
	DrawWall();

	// ビルボード描画処理
	DrawBillboard();

	// 影描画処理
	DrawShadow();

	// エフェクト描画処理
	DrawEffect();

	// スコアの描画処理
	DrawScore();

	// 時間の描画処理
	DrawTime();

	// コンボの描画処理
	DrawCombo();

	// スタミナゲージの描画処理
	DrawStaminaGauge();

	// ポーズの描画処理
	DrawPause();
}