//**************************************************************************************************
//
// プレイヤー描画処理(player.cpp)
// Auther：唐﨑結斗
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include "main.h"
#include "player.h"
#include"file.h"
#include"input.h"
#include"camera.h"
#include"shadow.h"
#include"billboard.h"
#include"effect.h"
#include"line.h"
#include"model.h"
#include"camera.h"
#include"feed.h"
#include"calculation.h"
#include"combo.h"
#include"mouse.h"
#include"fade.h"
#include"sound.h"

//***************************************************************************
// マクロ定義
//***************************************************************************
#define INIT_NUM_PLAYER				(10000)				// 頂点座標の最大最小の初期値
#define PLAYER_MOVE_SPEED			(2.0f)				// 移動速度
#define PLAYER_MAX_SPEED			(5.0f)				// 移動速度
#define PLAYER_ROTATE_SPEED			(0.1f)				// 回転速度
#define CAMERA_ROTATE_INTERVAL		(60)				// カメラの自動回転までのタイミング
#define	MAX_MOTION					(64)				// モーション最大数
#define MAX_VIEW_ROT				(0.25f)				// 視野角
#define MAX_COUNT_STATE				(60)				// 状態カウンタの最大値
#define MAX_STAMINA					(200)				// スタミナの最大値

//***************************************************************************
// グローバル変数
//***************************************************************************
static int				nCntFrame = 0;					// 現在のフレーム数
static int				nCntNumKeySet;					// 再生中のキー設定番号
static int				nNumMotionCnt;					// 再生するモーション番号
static int				nNumMotionCntOld;				// ひとつ前の再生するモーション番号
static Player			g_Player;						// プレイヤー情報
static MotionSet		g_MotionSet[MAX_MOTION];		// モーション設定情報
static PlayerFile		g_PlayerFile[MAX_MOTION];		// プレイヤーファイル情報

//---------------------------------------------------------------------------
// プレイヤー初期化処理
//---------------------------------------------------------------------------
void InitPlayer(void)
{
	// プレイヤーファイル情報の初期化
	memset(&g_PlayerFile[0], 0, sizeof(g_PlayerFile));

	// プレイヤー情報の初期化
	memset(&g_Player, 0, sizeof(g_Player));

	// モデルパーツの初期化
	memset(&g_Player.modeParts[0], 0, sizeof(g_Player.modeParts));

	// モーション設定の初期化
	memset(&g_MotionSet[0], 0, sizeof(g_MotionSet));
}

//---------------------------------------------------------------------------
// プレイヤー終了処理
//---------------------------------------------------------------------------
void UninitPlayer(void)
{
	for (int i = 0; i < g_Player.nMaxModelParts; i++)
	{
		// メッシュの破棄
		if (g_Player.modeParts[i].pMesh != NULL)
		{
			g_Player.modeParts[i].pMesh->Release();
			g_Player.modeParts[i].pMesh = NULL;
		}

		// マテリアルの破棄
		if (g_Player.modeParts[i].pBuffer != NULL)
		{
			g_Player.modeParts[i].pBuffer->Release();
			g_Player.modeParts[i].pBuffer = NULL;
		}
	}
}

//---------------------------------------------------------------------------
// プレイヤー更新処理
//---------------------------------------------------------------------------
void UpdatePlayer(void)
{
	if (g_Player.bUse == true)
	{// 使用している
		// カウントをインクリメント
		g_Player.nCntNotMove++;

		// 過去位置の更新
		g_Player.posOld = g_Player.pos;

		nNumMotionCntOld = nNumMotionCnt;

		// ニュートラルモーション
		g_Player.MotionState = NEUTRAL_MOTION;

		// ダッシュ処理
		DashPlayer();

		if (g_Player.PlayerState == NORMAL_STATE)
		{// プレイヤーの移動
			MovePlayer();
		}
		// モーション
		MotionPlayer((int)(g_Player.MotionState));

		//プレイヤーの回転
		RotatePlayer();

		// モデルとの当たり判定
		D3DXVECTOR3 aVtxA = WorldCastVtx(D3DXVECTOR3(-(g_Player.size.x / 2.0f), g_Player.pos.y, +(g_Player.size.z / 2.0f)), g_Player.pos, g_Player.rot);
		D3DXVECTOR3 aVtxB = WorldCastVtx(D3DXVECTOR3(+(g_Player.size.x / 2.0f), g_Player.pos.y, +(g_Player.size.z / 2.0f)), g_Player.pos, g_Player.rot);
		D3DXVECTOR3 aVtxC = WorldCastVtx(D3DXVECTOR3(+(g_Player.size.x / 2.0f), g_Player.pos.y, -(g_Player.size.z / 2.0f)), g_Player.pos, g_Player.rot);
		D3DXVECTOR3 aVtxD = WorldCastVtx(D3DXVECTOR3(-(g_Player.size.x / 2.0f), g_Player.pos.y, -(g_Player.size.z / 2.0f)), g_Player.pos, g_Player.rot);
		D3DXVECTOR3 aVtxAOld = WorldCastVtx(D3DXVECTOR3(g_Player.posOld.x - (g_Player.size.x / 2.0f), g_Player.posOld.y, g_Player.posOld.z + (g_Player.size.z / 2.0f)), g_Player.posOld, g_Player.rot);
		D3DXVECTOR3 aVtxBOld = WorldCastVtx(D3DXVECTOR3(g_Player.posOld.x + (g_Player.size.x / 2.0f), g_Player.posOld.y, g_Player.posOld.z + (g_Player.size.z / 2.0f)), g_Player.posOld, g_Player.rot);
		D3DXVECTOR3 aVtxCOld = WorldCastVtx(D3DXVECTOR3(g_Player.posOld.x + (g_Player.size.x / 2.0f), g_Player.posOld.y, g_Player.posOld.z - (g_Player.size.z / 2.0f)), g_Player.posOld, g_Player.rot);
		D3DXVECTOR3 aVtxDOld = WorldCastVtx(D3DXVECTOR3(g_Player.posOld.x - (g_Player.size.x / 2.0f), g_Player.posOld.y, g_Player.posOld.z - (g_Player.size.z / 2.0f)), g_Player.posOld, g_Player.rot);
		CollisionModel(&g_Player.pos, &g_Player.posOld, &aVtxA, &aVtxAOld);
		CollisionModel(&g_Player.pos, &g_Player.posOld, &aVtxB, &aVtxBOld);
		CollisionModel(&g_Player.pos, &g_Player.posOld, &aVtxC, &aVtxCOld);
		CollisionModel(&g_Player.pos, &g_Player.posOld, &aVtxD, &aVtxDOld);

		CollisionFeed(&g_Player.pos, &g_Player.posOld, &aVtxA, &aVtxAOld);
		CollisionFeed(&g_Player.pos, &g_Player.posOld, &aVtxB, &aVtxBOld);
		CollisionFeed(&g_Player.pos, &g_Player.posOld, &aVtxC, &aVtxCOld);
		CollisionFeed(&g_Player.pos, &g_Player.posOld, &aVtxD, &aVtxDOld);

		// カメラの回り込み
		if (g_Player.nCntNotMove >= CAMERA_ROTATE_INTERVAL)
		{
			//AutoRotateCamera();
		}

		// 影の移動
		SetPositionShadow(g_Player.nIdx, g_Player.pos, g_Player.rot, g_Player.size);

		//if (GetKeyboardTrigger(DIK_SPACE))
		//{// [SPACE]キーが押された時
		//	SetBillboard(g_Player.pos, g_Player.rot,1.0f);

		//	// エフェクトの生成
		//	SetEffect(g_Player.pos,
		//		D3DXVECTOR3(0.0f,0.0f,0.0f),
		//		D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f),
		//		D3DCMP_ALWAYS,
		//		EFFECTTYPE_FIELD,
		//		10.0f,
		//		0.0f,
		//		0.0f,
		//		30,
		//		1,
		//		false);
		//}

		if (g_Player.PlayerState == NORMAL_STATE)
		{// コンボ時間のデクリメント
			g_Player.nCntComboTime--;
		}

		if (g_Player.nCntComboTime == 0)
		{// コンボ加算時間が0の時
			if (g_Player.nMaxCombo < g_Player.nCntCombo)
			{
				g_Player.nMaxCombo = g_Player.nCntCombo;
			}
			g_Player.nCntCombo = 0;
		}

		// コンボセット
		SetCombo(g_Player.nCntCombo, D3DXVECTOR3((30.0f * 2) * 3.0f + 1080.0f, 230.0f, 0.0f), D3DXVECTOR3(30.0f, 60.0f, 0.0f));

		// コンボカウンターの更新
		AddCombo(g_Player.nCntCombo);

		// スタミナの減少
		if ((int)(g_Player.fMoveDistance) % 20 == 0 
			&& (int)(g_Player.fMoveDistance) > 0
			&& g_Player.PlayerState == NORMAL_STATE)
		{// 一定以上移動した
			g_Player.nStamina--;

			if (g_Player.nStamina == 0)
			{// 0以下の時
				//フェード情報の取得
				FADE fade;			//フェード情報へのポインタ
				fade = GetFade();

				if (g_Player.nMaxCombo < g_Player.nCntCombo)
				{
					g_Player.nMaxCombo = g_Player.nCntCombo;
				}

				if (fade == FADE_NONE)
				{//フェードが行われてないとき
					//リザルト画面へ移動
					SetFade(MODE_RESULT);
				}
			}
		}
	}
}

//---------------------------------------------------------------------------
// プレイヤー描画処理
//---------------------------------------------------------------------------
void DrawPlayer(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	D3DXMATRIX			mtxRot, mtxTrans;			// 計算用マトリックス
	D3DMATERIAL9		matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL		*pMat;						// マテリアルデータへのポインタ

	if (g_Player.bUse == true)
	{// 使用している
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player.mtxWorld);			// 行列初期化関数

		// 向きの反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);		// 行列回転関数
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);							// 行列掛け算関数 

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);				// 行列移動関数
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);							// 行列掛け算関数

		//// サイズの反映
		//D3DXMatrixScaling()

		for (int i = 0; i < g_Player.nMaxModelParts; i++)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Player.modeParts[i].mtxWorld);			// 行列初期化関数

			// 向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, 
				g_Player.modeParts[i].rot.y, 
				g_Player.modeParts[i].rot.x, 
				g_Player.modeParts[i].rot.z);								// 行列回転関数
			D3DXMatrixMultiply(&g_Player.modeParts[i].mtxWorld, 
				&g_Player.modeParts[i].mtxWorld,
				&mtxRot);													// 行列掛け算関数 

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, 
				g_Player.modeParts[i].pos.x, 
				g_Player.modeParts[i].pos.y,
				g_Player.modeParts[i].pos.z);								// 行列移動関数
			D3DXMatrixMultiply(&g_Player.modeParts[i].mtxWorld, 
				&g_Player.modeParts[i].mtxWorld,
				&mtxTrans);													// 行列掛け算関数

			// 親パーツのワールドマトリックスを保持
			D3DXMATRIX mtxParent;

			if (g_Player.modeParts[i].nIdxModelParent == -1)
			{// 親モデルのインデックス数が-1の時
				mtxParent = g_Player.mtxWorld;
			}
			else
			{
				mtxParent = g_Player.modeParts[g_Player.modeParts[i].nIdxModelParent].mtxWorld;
			}

			// 自分の親マトリックスとの掛け算
			D3DXMatrixMultiply(&g_Player.modeParts[i].mtxWorld, &g_Player.modeParts[i].mtxWorld, &mtxParent);

			//// サイズの反映
			//D3DXMatrixScaling()

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Player.modeParts[i].mtxWorld);

			// 現在のマテリアルを保持
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Player.modeParts[i].pBuffer->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Player.modeParts[i].nNumMat; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// プレイヤーパーツの描画
				g_Player.modeParts[i].pMesh->DrawSubset(nCntMat);
			}

			// 保持していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//---------------------------------------------------------------------------
// プレイヤー移動処理
//---------------------------------------------------------------------------
void MovePlayer(void)
{
	if (GetKeyboardPress(DIK_W)
		|| GetKeyboardPress(DIK_A)
		|| GetKeyboardPress(DIK_D)
		|| GetKeyboardPress(DIK_S))
	{// 移動キーが押された
		 // 移動モーション
		g_Player.MotionState = MOVE_MOTION;

		if (GetKeyboardPress(DIK_W))
		{// [↑]キーが押された時
			if (GetKeyboardPress(DIK_A))
			{// [→]キーが押された時
				// 移動方向の更新
				g_Player.rotDest.y = D3DX_PI * -0.25f;
			}
			else if (GetKeyboardPress(DIK_D))
			{// [←]キーが押された時
				// 移動方向の更新
				g_Player.rotDest.y = D3DX_PI * 0.25f;
			}
			else
			{// 移動方向の更新
				g_Player.rotDest.y = D3DX_PI * 0.0f;
			}
		}
		else if (GetKeyboardPress(DIK_S))
		{// [↓]キーが押された時
			if (GetKeyboardPress(DIK_A))
			{// [→]キーが押された時
				// 移動方向の更新
				g_Player.rotDest.y = D3DX_PI * -0.75f;
			}
			else if (GetKeyboardPress(DIK_D))
			{// [←]キーが押された時
				// 移動方向の更新
				g_Player.rotDest.y = D3DX_PI * 0.75f;
			}
			else
			{// 移動方向の更新q
				g_Player.rotDest.y = D3DX_PI;
			}
		}
		else if (GetKeyboardPress(DIK_A))
		{// [→]キーが押された時
			// 移動方向の更新
			g_Player.rotDest.y = D3DX_PI * -0.5f;
		}
		else if (GetKeyboardPress(DIK_D))
		{// [←]キーが押された時
			// 移動方向の更新
			g_Player.rotDest.y = D3DX_PI * 0.5f;
		}

		// カメラ情報の取得
		Camera *pCamera = GetCamera();

		// 移動方向の算出
		g_Player.rotDest.y += pCamera->rot.y;

		if (g_Player.rotDest.y > D3DX_PI)
		{// 移動方向の正規化
			g_Player.rotDest.y -= D3DX_PI * 2;
		}
		else if (g_Player.rotDest.y < -D3DX_PI)
		{// 移動方向の正規化
			g_Player.rotDest.y += D3DX_PI * 2;
		}

		// 視点位置と向きの更新
		g_Player.fSpeed = PLAYER_MOVE_SPEED + (0.1f * g_Player.nCntCombo);

		if (g_Player.fSpeed >= PLAYER_MAX_SPEED)
		{// 速度が一定以上いった
			g_Player.fSpeed = PLAYER_MAX_SPEED;
		}

		// 移動量の計算
		D3DXVECTOR3 move = D3DXVECTOR3(sinf(g_Player.rotDest.y), 0.0f, cosf(g_Player.rotDest.y));

		// 移動
		g_Player.pos += move * g_Player.fSpeed;

		// 移動距離の加算
		g_Player.fMoveDistance += sqrtf((move.x * move.x) + (move.z * move.z));

		g_Player.rotDest.y -= D3DX_PI;

		// カウントを0にする
		g_Player.nCntNotMove = 0;
	}

	//if (GetKeyboardPress(DIK_I) || GetKeyboardPress(DIK_K))
	//{
	//	if (GetKeyboardPress(DIK_I))
	//	{// [I]キーが押された時
	//	 // 移動方向の更新
	//		g_Player.pos.y += PLAYER_MOVE_SPEED;
	//	}
	//	else if (GetKeyboardPress(DIK_K))
	//	{// [K]キーが押された時
	//	 // 移動方向の更新
	//		g_Player.pos.y -= PLAYER_MOVE_SPEED;
	//	}

	//	// カウントを0にする
	//	g_Player.nCntNotMove = 0;
	//}

	// 目的の向きの補正
	if (g_Player.rotDest.y - g_Player.rot.y >= D3DX_PI)
	{// 移動方向の正規化
		g_Player.rotDest.y -= D3DX_PI * 2;
	}
	else if (g_Player.rotDest.y - g_Player.rot.y <= -D3DX_PI)
	{// 移動方向の正規化
		g_Player.rotDest.y += D3DX_PI * 2;
	}
}

//---------------------------------------------------------------------------
// プレイヤー回転処理
//---------------------------------------------------------------------------
void RotatePlayer(void)
{
	// 向きの更新
	g_Player.rot.y += (g_Player.rotDest.y - g_Player.rot.y) * PLAYER_ROTATE_SPEED;

	if (g_Player.rot.y >= D3DX_PI)
	{// 移動方向の正規化
		g_Player.rot.y -= D3DX_PI * 2;
	}
	else if (g_Player.rot.y <= -D3DX_PI)
	{// 移動方向の正規化
		g_Player.rot.y += D3DX_PI * 2;
	}
}

//---------------------------------------------------------------------------
// プレイヤー設定処理
//---------------------------------------------------------------------------
void SetPlayer(D3DXVECTOR3 pos,D3DXVECTOR3 rot,int	nMaxModelType,int	nMaxMotion)
{
	// プレイヤー情報の初期化
	g_Player.pos = pos;																		// 位置の初期化
	g_Player.posOld = g_Player.pos;															// 過去位置の初期化
	g_Player.rot = rot;																		// 向きの初期化
	g_Player.vtxMin = D3DXVECTOR3(INIT_NUM_PLAYER, INIT_NUM_PLAYER, INIT_NUM_PLAYER);		// 頂点座標の最小値
	g_Player.vtxMax = D3DXVECTOR3(-INIT_NUM_PLAYER, -INIT_NUM_PLAYER, -INIT_NUM_PLAYER);	// 頂点座標の最大値
	g_Player.size = D3DXVECTOR3(35.0f, 50.0f, 110.0f);										// 大きさ
	g_Player.PlayerState = NORMAL_STATE;													// 通常状態
	g_Player.attackPos = D3DXVECTOR3(0.0f, 0.0f, -20.0f);									// 当たり判定のローカル座標
	g_Player.fAttackRadius = 20.0f;															// 当たり判定の大きさ
	g_Player.mtxWorld = {};																	// ワールドマトリックス
	g_Player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										// 目的の向き
	g_Player.nMaxModelType = nMaxModelType;													// モデルのタイプ数
	g_Player.nMaxMotion = nMaxMotion;														// モーション数
	g_Player.nCntCombo = 0;																	// コンボ数
	g_Player.nMaxCombo = 0;																	// コンボ最大値
	g_Player.nMaxStamina = MAX_STAMINA;														// スタミナの最大値
	g_Player.nStamina = g_Player.nMaxStamina;												// スタミナ
	g_Player.nCntState = 0;																	// 状態カウンタ
	g_Player.fSpeed = PLAYER_MOVE_SPEED + (0.1f * g_Player.nCntCombo);						// 移動速度
	g_Player.fMoveDistance = 0.0f;															// 移動距離
	g_Player.bUse = true;																	// 使用状況
	g_Player.nCntNotMove = CAMERA_ROTATE_INTERVAL;

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < g_Player.nMaxModelParts; i++)
	{
		// 位置と向きの初期値を保存
		g_Player.modeParts[i].posOrigin = g_Player.modeParts[i].pos;
		g_Player.modeParts[i].rotOrigin = g_Player.modeParts[i].rot;

		// パーツ情報の初期化
		g_Player.modeParts[i].mtxWorld = {};																// ワールドマトリックス
		g_Player.modeParts[i].vtxMin = D3DXVECTOR3(INIT_NUM_PLAYER, INIT_NUM_PLAYER, INIT_NUM_PLAYER);		// 頂点座標の最小値
		g_Player.modeParts[i].vtxMax = D3DXVECTOR3(-INIT_NUM_PLAYER, -INIT_NUM_PLAYER, -INIT_NUM_PLAYER);	// 頂点座標の最大値

		// Xファイルの読み込み
		D3DXLoadMeshFromX(&g_PlayerFile[g_Player.modeParts[i].nType].aName[0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Player.modeParts[i].pBuffer,
			NULL,
			&g_Player.modeParts[i].nNumMat,
			&g_Player.modeParts[i].pMesh);

		// 頂点座標の最小値・最大値の算出
		int			nNumVtx;		// 頂点数
		DWORD		sizeFVF;		// 頂点フォーマットのサイズ
		BYTE		*pVtxBuff;		// 頂点バッファへのポインタ

		// 頂点数の取得
		nNumVtx = g_Player.modeParts[i].pMesh->GetNumVertices();

		// 頂点フォーマットのサイズの取得
		sizeFVF = D3DXGetFVFVertexSize(g_Player.modeParts[i].pMesh->GetFVF());

		// 頂点バッファのロック
		g_Player.modeParts[i].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			// 頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			if (vtx.x < g_Player.modeParts[i].vtxMin.x)
			{// 比較対象が現在の頂点座標(X)の最小値より小さい
				g_Player.modeParts[i].vtxMin.x = vtx.x;
			}
			if (vtx.y < g_Player.modeParts[i].vtxMin.y)
			{// 比較対象が現在の頂点座標(Y)の最小値より小さい
				g_Player.modeParts[i].vtxMin.y = vtx.y;
			}
			if (vtx.z < g_Player.modeParts[i].vtxMin.z)
			{// 比較対象が現在の頂点座標(Z)の最小値より小さい
				g_Player.modeParts[i].vtxMin.z = vtx.z;
			}

			if (vtx.x > g_Player.modeParts[i].vtxMax.x)
			{// 比較対象が現在の頂点座標(X)の最大値より大きい
				g_Player.modeParts[i].vtxMax.x = vtx.x;
			}
			if (vtx.y > g_Player.modeParts[i].vtxMax.y)
			{// 比較対象が現在の頂点座標(Y)の最大値より大きい
				g_Player.modeParts[i].vtxMax.y = vtx.y;
			}
			if (vtx.z > g_Player.modeParts[i].vtxMax.z)
			{// 比較対象が現在の頂点座標(Z)の最大値より大きい
				g_Player.modeParts[i].vtxMax.z = vtx.z;
			}

			// 頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}

		// 頂点の算出
		D3DXVECTOR3 aVtxMin = D3DXVECTOR3(g_Player.modeParts[i].vtxMin.x, g_Player.modeParts[i].vtxMin.y, g_Player.modeParts[i].vtxMin.z);
		D3DXVECTOR3 aVtxMax = D3DXVECTOR3(g_Player.modeParts[i].vtxMax.x, g_Player.modeParts[i].vtxMax.y, g_Player.modeParts[i].vtxMax.z);

		// 頂点をワールド座標へキャスト
		aVtxMin = WorldCastVtx(aVtxMin, g_Player.modeParts[i].pos, g_Player.modeParts[i].rot);
		aVtxMax = WorldCastVtx(aVtxMax, g_Player.modeParts[i].pos, g_Player.modeParts[i].rot);

		if (aVtxMin.x < g_Player.vtxMin.x)
		{// 比較対象が現在の頂点座標(X)の最小値より小さい
			g_Player.vtxMin.x = aVtxMin.x;
		}
		if (aVtxMin.y < g_Player.vtxMin.y)
		{// 比較対象が現在の頂点座標(Y)の最小値より小さい
			g_Player.vtxMin.y = aVtxMin.y;
		}
		if (aVtxMin.z < g_Player.vtxMin.z)
		{// 比較対象が現在の頂点座標(Z)の最小値より小さい
			g_Player.vtxMin.z = aVtxMin.z;
		}

		if (aVtxMax.x > g_Player.vtxMax.x)
		{// 比較対象が現在の頂点座標(X)の最大値より大きい
			g_Player.vtxMax.x = aVtxMax.x;
		}
		if (aVtxMax.y > g_Player.vtxMax.y)
		{// 比較対象が現在の頂点座標(Y)の最大値より大きい
			g_Player.vtxMax.y = aVtxMax.y;
		}
		if (aVtxMax.z > g_Player.vtxMax.z)
		{// 比較対象が現在の頂点座標(Z)の最大値より大きい
			g_Player.vtxMax.z = aVtxMax.z;
		}

		// 頂点バッファのアンロック
		g_Player.modeParts[i].pMesh->UnlockVertexBuffer();
	}

	// ラインの設定
#ifndef _DEBUG
	SetLine(g_Player.pos, g_Player.rot, D3DXVECTOR3(-g_Player.size.x / 2.0f, -g_Player.size.y, g_Player.size.z / 2.0f), D3DXVECTOR3(g_Player.size.x / 2.0f, -g_Player.size.y, g_Player.size.z / 2.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	SetLine(g_Player.pos, g_Player.rot, D3DXVECTOR3(-g_Player.size.x / 2.0f, -g_Player.size.y, -g_Player.size.z / 2.0f), D3DXVECTOR3(-g_Player.size.x / 2.0f, -g_Player.size.y, g_Player.size.z / 2.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	SetLine(g_Player.pos, g_Player.rot, D3DXVECTOR3(-g_Player.size.x / 2.0f, -g_Player.size.y, -g_Player.size.z / 2.0f), D3DXVECTOR3(g_Player.size.x / 2.0f, -g_Player.size.y, -g_Player.size.z / 2.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	SetLine(g_Player.pos, g_Player.rot, D3DXVECTOR3(g_Player.size.x / 2.0f, -g_Player.size.y, -g_Player.size.z / 2.0f), D3DXVECTOR3(g_Player.size.x / 2.0f, -g_Player.size.y, g_Player.size.z / 2.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

	SetLine(g_Player.pos, g_Player.rot, D3DXVECTOR3(-g_Player.size.x / 2.0f, g_Player.size.y, g_Player.size.z / 2.0f), D3DXVECTOR3(g_Player.size.x / 2.0f, g_Player.size.y, g_Player.size.z / 2.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	SetLine(g_Player.pos, g_Player.rot, D3DXVECTOR3(-g_Player.size.x / 2.0f, g_Player.size.y, -g_Player.size.z / 2.0f), D3DXVECTOR3(-g_Player.size.x / 2.0f, g_Player.size.y, g_Player.size.z / 2.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	SetLine(g_Player.pos, g_Player.rot, D3DXVECTOR3(-g_Player.size.x / 2.0f, g_Player.size.y, -g_Player.size.z / 2.0f), D3DXVECTOR3(g_Player.size.x / 2.0f, g_Player.size.y, -g_Player.size.z / 2.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	SetLine(g_Player.pos, g_Player.rot, D3DXVECTOR3(g_Player.size.x / 2.0f, g_Player.size.y, -g_Player.size.z / 2.0f), D3DXVECTOR3(g_Player.size.x / 2.0f, g_Player.size.y, g_Player.size.z / 2.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

	SetLine(g_Player.pos, g_Player.rot, D3DXVECTOR3(-g_Player.size.x / 2.0f, -g_Player.size.y, g_Player.size.z / 2.0f), D3DXVECTOR3(-g_Player.size.x / 2.0f, g_Player.size.y, g_Player.size.z / 2.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	SetLine(g_Player.pos, g_Player.rot, D3DXVECTOR3(-g_Player.size.x / 2.0f, -g_Player.size.y, -g_Player.size.z / 2.0f), D3DXVECTOR3(-g_Player.size.x / 2.0f, g_Player.size.y, -g_Player.size.z / 2.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	SetLine(g_Player.pos, g_Player.rot, D3DXVECTOR3(g_Player.size.x / 2.0f, -g_Player.size.y, -g_Player.size.z / 2.0f), D3DXVECTOR3(g_Player.size.x / 2.0f, g_Player.size.y, -g_Player.size.z / 2.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	SetLine(g_Player.pos, g_Player.rot, D3DXVECTOR3(g_Player.size.x / 2.0f, -g_Player.size.y, g_Player.size.z / 2.0f), D3DXVECTOR3(g_Player.size.x / 2.0f, g_Player.size.y, g_Player.size.z / 2.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
#endif // _DEBUG

	// 影の設定
	g_Player.nIdx = SetShadow(g_Player.pos, g_Player.rot, g_Player.size);

	AutoRotateCamera();
}

//---------------------------------------------------------------------------
// プレイヤーのモーション処理
//---------------------------------------------------------------------------
void MotionPlayer(int nCntMotionSet)
{
	KeySet* keyset = &g_MotionSet[nCntMotionSet].keySet[g_MotionSet[nCntMotionSet].nCntKeySet];
	MotionSet* motionSet = &g_MotionSet[nCntMotionSet];

	for (int nCntParts = 0; nCntParts < g_Player.nMaxModelParts; nCntParts++)
	{
		ModelParts* modelParts = &g_Player.modeParts[nCntParts];

		if (motionSet->nCntFrame == 0)
		{// フレームカウントが0の時
			// 目的の位置と向きの算出
			modelParts->posDest = (modelParts->posOrigin + keyset->key[nCntParts].pos) - modelParts->pos;
			modelParts->rotDest = (modelParts->rotOrigin + keyset->key[nCntParts].rot) - modelParts->rot;

			// 移動方向の正規化
			RotNormalization(modelParts->rotDest.x);
			RotNormalization(modelParts->rotDest.y);
			RotNormalization(modelParts->rotDest.z);
		}
				
		// 変数宣言
		D3DXVECTOR3 addPos = D3DXVECTOR3(modelParts->posDest / (float)(keyset->nFrame));
		D3DXVECTOR3 addRot = D3DXVECTOR3(modelParts->rotDest / (float)(keyset->nFrame));

		// 位置の加算
		modelParts->pos += addPos;

		//	向きの加算
		modelParts->rot += addRot;

		// 移動方向の正規化
		RotNormalization(modelParts->rot.x);
		RotNormalization(modelParts->rot.y);
		RotNormalization(modelParts->rot.z);
	}

	// フレームカウントの加算
	motionSet->nCntFrame++;

	if (motionSet->nCntFrame >= keyset->nFrame)
	{// フレームカウントが指定のフレーム数を超えた場合
		// フレーム数の初期化
		motionSet->nCntFrame = 0;

		// 再生中のキー番号数の加算
		motionSet->nCntKeySet++;

		if ((motionSet->nCntKeySet >= motionSet->nNumKey) && motionSet->bLoop)
		{// 再生中のキー数カウントがキー数の最大値を超えたとき、そのモーションがループを使用している
			// 再生中のキー数カウントを初期化
			motionSet->nCntKeySet = 0;
		}
	}
}

//---------------------------------------------------------------------------
// プレイヤーのモーションブレンド処理
//---------------------------------------------------------------------------
void MotionBlend(int nCntMotionSet)
{
	for (int nCntParts = 0; nCntParts < g_Player.nMaxModelParts; nCntParts++)
	{
		if (g_MotionSet[nCntMotionSet].nCntFrame == 0)
		{// フレームカウントが0の時
		 // 目的の位置と向きの算出
			g_Player.modeParts[nCntParts].posDest = (g_Player.modeParts[nCntParts].posOrigin + g_MotionSet[nCntMotionSet].keySet[g_MotionSet[nCntMotionSet].nCntKeySet].key[nCntParts].pos) - g_Player.modeParts[nCntParts].pos;
			g_Player.modeParts[nCntParts].rotDest = (g_Player.modeParts[nCntParts].rotOrigin + g_MotionSet[nCntMotionSet].keySet[g_MotionSet[nCntMotionSet].nCntKeySet].key[nCntParts].rot) - g_Player.modeParts[nCntParts].rot;

			if (g_Player.modeParts[nCntParts].rotDest.x >= D3DX_PI)
			{// 移動方向の正規化
				g_Player.modeParts[nCntParts].rotDest.x -= D3DX_PI * 2;
			}
			else if (g_Player.modeParts[nCntParts].rotDest.x <= -D3DX_PI)
			{// 移動方向の正規化
				g_Player.modeParts[nCntParts].rotDest.x += D3DX_PI * 2;
			}
			if (g_Player.modeParts[nCntParts].rotDest.y >= D3DX_PI)
			{// 移動方向の正規化
				g_Player.modeParts[nCntParts].rotDest.y -= D3DX_PI * 2;
			}
			else if (g_Player.modeParts[nCntParts].rotDest.y <= -D3DX_PI)
			{// 移動方向の正規化
				g_Player.modeParts[nCntParts].rotDest.y += D3DX_PI * 2;
			}
			if (g_Player.modeParts[nCntParts].rotDest.z >= D3DX_PI)
			{// 移動方向の正規化
				g_Player.modeParts[nCntParts].rotDest.z -= D3DX_PI * 2;
			}
			else if (g_Player.modeParts[nCntParts].rotDest.z <= -D3DX_PI)
			{// 移動方向の正規化
				g_Player.modeParts[nCntParts].rotDest.z += D3DX_PI * 2;
			}
		}

		// 変数宣言
		D3DXVECTOR3 addPos = D3DXVECTOR3(g_Player.modeParts[nCntParts].posDest / (float)(g_MotionSet[nCntMotionSet].keySet[g_MotionSet[nCntMotionSet].nCntKeySet].nFrame));
		D3DXVECTOR3 addRot = D3DXVECTOR3(g_Player.modeParts[nCntParts].rotDest / (float)(g_MotionSet[nCntMotionSet].keySet[g_MotionSet[nCntMotionSet].nCntKeySet].nFrame));

		// 位置の加算
		g_Player.modeParts[nCntParts].pos += addPos;

		//	向きの加算
		g_Player.modeParts[nCntParts].rot += addRot;

		if (g_Player.modeParts[nCntParts].rot.x >= D3DX_PI)
		{// 移動方向の正規化
			g_Player.modeParts[nCntParts].rot.x -= D3DX_PI * 2;
		}
		else if (g_Player.modeParts[nCntParts].rot.x <= -D3DX_PI)
		{// 移動方向の正規化
			g_Player.modeParts[nCntParts].rot.x += D3DX_PI * 2;
		}
		if (g_Player.modeParts[nCntParts].rot.y >= D3DX_PI)
		{// 移動方向の正規化
			g_Player.modeParts[nCntParts].rot.y -= D3DX_PI * 2;
		}
		else if (g_Player.modeParts[nCntParts].rot.y <= -D3DX_PI)
		{// 移動方向の正規化
			g_Player.modeParts[nCntParts].rot.y += D3DX_PI * 2;
		}
		if (g_Player.modeParts[nCntParts].rot.z >= D3DX_PI)
		{// 移動方向の正規化
			g_Player.modeParts[nCntParts].rot.z -= D3DX_PI * 2;
		}
		else if (g_Player.modeParts[nCntParts].rot.z <= -D3DX_PI)
		{// 移動方向の正規化
			g_Player.modeParts[nCntParts].rot.z += D3DX_PI * 2;
		}
	}

	// フレームカウントの加算
	g_MotionSet[nCntMotionSet].nCntFrame++;

	if (g_MotionSet[nCntMotionSet].nCntFrame >= g_MotionSet[nCntMotionSet].keySet[g_MotionSet[nCntMotionSet].nCntKeySet].nFrame)
	{// フレームカウントが指定のフレーム数を超えた場合
		// フレーム数の初期化
		g_MotionSet[nCntMotionSet].nCntFrame = 0;

		// 再生中のキー番号数の加算
		g_MotionSet[nCntMotionSet].nCntKeySet++;

		if (g_MotionSet[nCntMotionSet].nCntKeySet >= g_MotionSet[nCntMotionSet].nNumKey && g_MotionSet[nCntMotionSet].bLoop == true)
		{// 再生中のキー数カウントがキー数の最大値を超えたとき、そのモーションがループを使用している
			// 再生中のキー数カウントを初期化
			g_MotionSet[nCntMotionSet].nCntKeySet = 0;
		}
	}
}

//---------------------------------------------------------------------------
// プレイヤー視野角処理
//---------------------------------------------------------------------------
bool SearchPlayer(D3DXVECTOR3 *pos)
{
	// 変数宣言
	bool bSearchIn = false;

	// 視野角の半分を算出
	float fSearchRot = (D3DX_PI * MAX_VIEW_ROT);

	// 仲間のいる向き
	D3DXVECTOR3 aVtxPos = g_Player.pos;
	float fFellowRot = atan2f(aVtxPos.x - pos->x, aVtxPos.z - pos->z);
	fFellowRot = RotNormalization(fFellowRot);

	// 比較用の向きの算出
	D3DXVECTOR3 sen = g_Player.pos;
	float fSearchRotRight = g_Player.rot.y - fSearchRot;
	float fSRROld = fSearchRotRight;
	fSearchRotRight = RotNormalization(fSearchRotRight);

	float fSearchRotLeft = g_Player.rot.y + fSearchRot;
	float fSRLOld = fSearchRotLeft;
	fSearchRotLeft = RotNormalization(fSearchRotLeft);

	if (fSRROld == fSearchRotRight && fSRLOld == fSearchRotLeft)
	{// 正規化前の数値が同じ場合
		if (fSearchRotRight <= fFellowRot
			&& fSearchRotLeft >= fFellowRot)
		{// 視野角内に目標がいる
			bSearchIn = true;
		}
	}
	else
	{// 正規化前の数値が違う場合
		if (fSearchRotRight <= fFellowRot
			|| fSearchRotLeft >= fFellowRot)
		{// 視野角内に目標がいる
			bSearchIn = true;
		}
	}

	return bSearchIn;
}

//---------------------------------------------------------------------------
// プレイヤー攻撃判定処理
//---------------------------------------------------------------------------
bool EatPlayer(D3DXVECTOR3 *pos, D3DXVECTOR3 size)
{
	// 変数宣言
	bool bOnCollison = false;
	D3DXVECTOR3 distance;

	// 半径の算出
	float fRadius = sqrtf((size.x * size.x) + (size.z * size.z)) / 2.0f;
	fRadius += g_Player.fAttackRadius / 2.0f;

	// 当たり判定の位置をワールド座標にキャスト
	distance = WorldCastVtx(g_Player.attackPos, g_Player.pos, g_Player.rot);

	// 目標と差分
	distance = *pos - distance;
	float fDistance = sqrtf((distance.x * distance.x) + (distance.z * distance.z));
	
	if (fDistance <= fRadius)
	{// 当たり判定オン
		bOnCollison = true;
	}

	return bOnCollison;
}

//---------------------------------------------------------------------------
// プレイヤー当たり判定処理
//---------------------------------------------------------------------------
bool CollisionPlayer(D3DXVECTOR3 *vtx)
{
	// 変数宣言
	bool OnCollision = false;

	// 頂点の算出
	D3DXVECTOR3 aVecA = D3DXVECTOR3(-(g_Player.size.x / 2.0f), g_Player.pos.y, +(g_Player.size.z / 2.0f));
	D3DXVECTOR3 aVecB = D3DXVECTOR3(+(g_Player.size.x / 2.0f), g_Player.pos.y, +(g_Player.size.z / 2.0f));
	D3DXVECTOR3 aVecC = D3DXVECTOR3(+(g_Player.size.x / 2.0f), g_Player.pos.y, -(g_Player.size.z / 2.0f));
	D3DXVECTOR3 aVecD = D3DXVECTOR3(-(g_Player.size.x / 2.0f), g_Player.pos.y, -(g_Player.size.z / 2.0f));

	// 頂点をワールド座標へキャスト
	aVecA = WorldCastVtx(aVecA, g_Player.pos, g_Player.rot);
	aVecB = WorldCastVtx(aVecB, g_Player.pos, g_Player.rot);
	aVecC = WorldCastVtx(aVecC, g_Player.pos, g_Player.rot);
	aVecD = WorldCastVtx(aVecD, g_Player.pos, g_Player.rot);

	if (g_Player.pos.x < g_Player.pos.x)g_Player.pos.x = g_Player.pos.x;

	// ベクトルの算出
	D3DXVECTOR3 aVecLineA = aVecB - aVecA;
	D3DXVECTOR3 aVecLineB = aVecC - aVecB;
	D3DXVECTOR3 aVecLineC = aVecD - aVecC;
	D3DXVECTOR3 aVecLineD = aVecA - aVecD;
	D3DXVECTOR3 aVecPosA = *vtx - aVecA;
	D3DXVECTOR3 aVecPosB = *vtx - aVecB;
	D3DXVECTOR3 aVecPosC = *vtx - aVecC;
	D3DXVECTOR3 aVecPosD = *vtx - aVecD;

	// 比較演算用の変数の定義と代入
	float fA = (aVecLineA.z * aVecPosA.x) - (aVecLineA.x * aVecPosA.z);
	float fB = (aVecLineB.z * aVecPosB.x) - (aVecLineB.x * aVecPosB.z);
	float fC = (aVecLineC.z * aVecPosC.x) - (aVecLineC.x * aVecPosC.z);
	float fD = (aVecLineD.z * aVecPosD.x) - (aVecLineD.x * aVecPosD.z);

	if (0.0f < fA
		&& 0.0f < fB
		&& 0.0f < fC
		&& 0.0f < fD)
	{// モデルのうちにいる
		// 交点の算出
		g_Player.pos.x = g_Player.posOld.x;
		g_Player.pos.z = g_Player.posOld.z;
		OnCollision = true;
	}

	return OnCollision;
}

//---------------------------------------------------------------------------
// プレイヤーのダッシュ処理
//---------------------------------------------------------------------------
void DashPlayer(void)
{
	if(GetKeyboardTrigger(DIK_LSHIFT))
	{// 左シフトボタンを押された
		if (g_Player.nStamina > DASH_STAMINA)
		{// ダッシュに使うスタミナ以上ある
			if (g_Player.PlayerState == NORMAL_STATE)
			{// 通常状態の時
				g_Player.PlayerState = DASH_STATE;
				g_Player.nCntState = MAX_COUNT_STATE;
				g_Player.nStamina -= DASH_STAMINA;
				g_Player.fSpeed = PLAYER_MOVE_SPEED + (0.1f * g_Player.nCntCombo);

				if (g_Player.fSpeed >= PLAYER_MAX_SPEED)
				{// 速度が一定以上いった
					g_Player.fSpeed = PLAYER_MAX_SPEED;
				}

				//サウンドの再生
				PlaySound(SOUND_LABEL_SE_APPEAR);
			}
		}
	}

	if (g_Player.PlayerState == DASH_STATE)
	{// ダッシュ状態
		// 移動モーション
		g_Player.MotionState = MOVE_MOTION;
		float fMaxSpeed = 3.0f;
		g_Player.fSpeed += fMaxSpeed / (float)(g_Player.nCntState);

		// 移動処理
		g_Player.pos.x += sinf(g_Player.rot.y - D3DX_PI) * g_Player.fSpeed;
		g_Player.pos.z += cosf(g_Player.rot.y - D3DX_PI) * g_Player.fSpeed;

		g_Player.nCntState--;

		if (g_Player.nCntState <= 0)
		{
			g_Player.PlayerState = NORMAL_STATE;
		}
	}
}

//---------------------------------------------------------------------------
// プレイヤー取得処理
//---------------------------------------------------------------------------
Player *GetPlayer(void)
{
	return &g_Player;
}

//---------------------------------------------------------------------------
// プレイヤーファイル取得処理
//---------------------------------------------------------------------------
PlayerFile	*GetPlayerFile(void)
{
	return &g_PlayerFile[0];
}

//---------------------------------------------------------------------------
// モーション取得処理
//---------------------------------------------------------------------------
MotionSet	*GetMotionSet(void)
{
	return &g_MotionSet[0];
}