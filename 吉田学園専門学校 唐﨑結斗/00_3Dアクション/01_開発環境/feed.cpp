//**************************************************************************************************
//
// 餌描画処理(feed.cpp)
// Auther：唐﨑結斗
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include "main.h"
#include "feed.h"
#include"file.h"
#include"input.h"
#include"camera.h"
#include"shadow.h"
#include"billboard.h"
#include"effect.h"
#include"line.h"
#include"calculation.h"
#include<time.h>
#include"player.h"
#include"score.h"
#include"particle.h"
#include"model.h"
#include"sound.h"

//***************************************************************************
// マクロ定義
//***************************************************************************
#define INIT_NUM_FEED			(10000)							// 頂点座標の最大最小の初期値
#define FEED_MOVE_SPEED			(0.5f)							// 移動速度
#define FEED_ROTATE_SPEED		(0.1f)							// 回転速度
#define SEARCH_RANGE_LENGTH		(100.0f)						// 捜索範囲の距離
#define LEAVE_RANGE_LENGTH		(25.0f)							// 分離範囲の距離
#define SEARCH_PLAYER_LENGTH	(150.0f)						// 索敵範囲の距離
#define SEARCH_RANGE_ROT		(0.5f)							// 捜索範囲の角度
#define LEAVE_RANGE_ROT			(SEARCH_RANGE_ROT * 1.5f)		// 捜索範囲の角度
#define SEARCH_PLAYER_SPEED		(0.8f)							// 索敵範囲の速度
#define JOINT_TIME				(30)							// 結合を行うまでの時間
#define MOVE_TIME				(600)							// 移動量算出までの時間
#define MAX_SPEED				(0.5f)							// 移動速度の最大
#define MAX_MOVE_ROT			(0.15f)							// 移動方向の最大
#define MAX_COMBO_TIME_FEED		(120)							// コンボ加算時間
#define MIN_SET_FEED			(30)							// 最小設置数
#define MAX_SET_FEED			(60)							// 最大設置数
#define MAX_SET_POS_FEED		(400 * 2)						// 設置範囲

//***************************************************************************
// グローバル変数
//***************************************************************************
static Feed			g_Feed[MAX_FEED];				// 餌情報
static FeedFile		g_FeedFile;						// 餌ファイル名情報
static int			g_nCntFeed = 0;					// 使用されてる餌の数

//---------------------------------------------------------------------------
// 餌初期化処理
//---------------------------------------------------------------------------
void InitFeed(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nCntFeed = 0;

	//乱数の初期化
	srand((unsigned int)time(0));

	// 餌ファイル名情報の初期化
	memset(&g_FeedFile, 0, sizeof(g_FeedFile));

	// 餌情報の初期化
	memset(&g_Feed[0], 0, sizeof(g_Feed));
}

//---------------------------------------------------------------------------
// 餌終了処理
//---------------------------------------------------------------------------
void UninitFeed(void)
{
	for (int i = 0; i < MAX_FEED; i++)
	{
		// メッシュの破棄
		if (g_Feed[i].pMesh != NULL)
		{
			g_Feed[i].pMesh->Release();
			g_Feed[i].pMesh = NULL;
		}

		// マテリアルの破棄
		if (g_Feed[i].pBuffer != NULL)
		{
			g_Feed[i].pBuffer->Release();
			g_Feed[i].pBuffer = NULL;
		}
	}
}

//---------------------------------------------------------------------------
// 餌更新処理
//---------------------------------------------------------------------------
void UpdateFeed(void)
{
	for (int nCnt = 0; nCnt < MAX_FEED; nCnt++)
	{
		if (g_Feed[nCnt].bUse == true)
		{// 使用している
			// 過去位置の更新
			g_Feed[nCnt].posOld = g_Feed[nCnt].pos;

			// 判定用の変数
			g_Feed[nCnt].bSearchIn = false;
			bool bOnCollisionPlayer = false;

			// プレイヤーの視野角内にいるか
			g_Feed[nCnt].bSearchIn = SearchPlayer(&g_Feed[nCnt].pos);

			// プレイヤーの当たり判定
			D3DXVECTOR3 aVtxA = WorldCastVtx(D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMax.z), g_Feed[nCnt].pos, g_Feed[nCnt].rot);
			D3DXVECTOR3 aVtxB = WorldCastVtx(D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMax.z), g_Feed[nCnt].pos, g_Feed[nCnt].rot);
			D3DXVECTOR3 aVtxC = WorldCastVtx(D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMin.z), g_Feed[nCnt].pos, g_Feed[nCnt].rot);
			D3DXVECTOR3 aVtxD = WorldCastVtx(D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMin.z), g_Feed[nCnt].pos, g_Feed[nCnt].rot);

			if (g_Feed[nCnt].bSearchIn == false)
			{// 視野外の時
				CollisionPlayer(&aVtxA);
				CollisionPlayer(&aVtxB);
				CollisionPlayer(&aVtxC);
				CollisionPlayer(&aVtxD);
			}

			bOnCollisionPlayer = EatPlayer(&g_Feed[nCnt].pos, g_Feed[nCnt].vtxMax - g_Feed[nCnt].vtxMin);

			MODE mode = GetMode();

			if (mode == MODE_GAME)
			{// ゲームの時
				if (g_Feed[nCnt].bSearchIn == true && bOnCollisionPlayer == true)
				{// 視野角内にいてプレイヤーに当たっている時
					g_Feed[nCnt].bUse = false;
					DeleteShadow(g_Feed[nCnt].nIdx);
					g_nCntFeed--;

					// プレイヤー情報の取得
					Player *pPlayer = GetPlayer();

					// コンボ加算
					pPlayer->nCntCombo++;

					// コンボ加算時間の更新
					pPlayer->nCntComboTime = MAX_COMBO_TIME_FEED;

					// スタミナをインクリメント
					pPlayer->nStamina += 3;

					if (pPlayer->nStamina >= pPlayer->nMaxStamina)
					{// スタミナを最大値に固定
						pPlayer->nStamina = pPlayer->nMaxStamina;
					}

					//スコアの加算
					AddScore(200 + 100 * pPlayer->nCntCombo);

					// パーティクルの設置
					SetParticle(g_Feed[nCnt].pos,
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						D3DXVECTOR3(1.0f, 1.0f, 0.0f),
						D3DXCOLOR(0.01f, 1.0f, 1.0f, 1.0f),
						5.0f,
						2.0f,
						0.0f,
						60,
						0,
						1,
						30,
						20,
						false);

					//サウンドの再生
					PlaySound(SOUND_LABEL_SE_DAMAGE001);
				}

				// プレイヤーから逃げる処理
				LeavePlayer(nCnt);
			}

			if (g_Feed[nCnt].bEscape == false)
			{// 逃げていないとき
				// リーダーの捜索
				SearchLeader(nCnt);

				// 分離
				LeaveFeed(nCnt);
			}

			// 整理
			AverageFeed(nCnt);

			// 餌の移動
			MoveFeed(nCnt);

			//餌の回転
			RotateFeed(nCnt);

			if (CollisionModel(&g_Feed[nCnt].pos, &g_Feed[nCnt].posOld, &aVtxA, &aVtxA) == true
				|| CollisionModel(&g_Feed[nCnt].pos, &g_Feed[nCnt].posOld, &aVtxB, &aVtxB) == true
				|| CollisionModel(&g_Feed[nCnt].pos, &g_Feed[nCnt].posOld, &aVtxC, &aVtxC) == true
				|| CollisionModel(&g_Feed[nCnt].pos, &g_Feed[nCnt].posOld, &aVtxD, &aVtxD) == true)
			{
				g_Feed[nCnt].bUse = false;
				DeleteShadow(g_Feed[nCnt].nIdx);
			}

			// 影の移動
			SetPositionShadow(g_Feed[nCnt].nIdx, g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMax.x - g_Feed[nCnt].vtxMin.x, 0.0f, g_Feed[nCnt].vtxMax.z - g_Feed[nCnt].vtxMin.z));
		}
	}
}

//---------------------------------------------------------------------------
// 餌描画処理
//---------------------------------------------------------------------------
void DrawFeed(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// 計算用マトリックス
	D3DMATERIAL9		matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL		*pMat;						// マテリアルデータへのポインタ

	for (int nCnt = 0; nCnt < MAX_FEED; nCnt++)
	{
		if (g_Feed[nCnt].bUse == true)
		{// 使用している
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Feed[nCnt].mtxWorld);			// 行列初期化関数

			// 向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Feed[nCnt].rot.y, g_Feed[nCnt].rot.x, g_Feed[nCnt].rot.z);		// 行列回転関数
			D3DXMatrixMultiply(&g_Feed[nCnt].mtxWorld, &g_Feed[nCnt].mtxWorld, &mtxRot);								// 行列掛け算関数 

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Feed[nCnt].pos.x, g_Feed[nCnt].pos.y, g_Feed[nCnt].pos.z);				// 行列移動関数
			D3DXMatrixMultiply(&g_Feed[nCnt].mtxWorld, &g_Feed[nCnt].mtxWorld, &mtxTrans);								// 行列掛け算関数

			//// サイズの反映
			//D3DXMatrixScaling()

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Feed[nCnt].mtxWorld);

			// 現在のマテリアルを保持
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Feed[nCnt].pBuffer->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Feed[nCnt].nNumMat; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				/*if (g_Feed[nCnt].bSearchIn == true)
				{
					D3DMATERIAL9  matD3D = pMat[nCntMat].MatD3D;
					matD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					pDevice->SetMaterial(&matD3D);
				}
				else
				{
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				}*/

				// 餌パーツの描画
				g_Feed[nCnt].pMesh->DrawSubset(nCntMat);
			}

			// 保持していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//---------------------------------------------------------------------------
// 餌移動処理
//---------------------------------------------------------------------------
void MoveFeed(int nCnt)
{
	// 移動量の算出
	if (g_Feed[nCnt].bEscape == false)
	{// 逃げていない
		g_Feed[nCnt].nCntMoveTime++;
		if (g_Feed[nCnt].nCntMoveTime >= MOVE_TIME)
		{// 移動量と速度の算出
			// 移動方向
			if (g_Feed[nCnt].nIdxLeader == -1)
			{
				float fRotMove = ((D3DX_PI * MAX_MOVE_ROT)) - (float)(rand() % (int)(((D3DX_PI * MAX_MOVE_ROT) * 2.0f) * 100.0f) / 100.0f);

				// 移動量の算出
				g_Feed[nCnt].move.x = sinf(g_Feed[nCnt].rot.y + fRotMove);
				g_Feed[nCnt].move.z = cosf(g_Feed[nCnt].rot.y + fRotMove);
				D3DXVec3Normalize(&g_Feed[nCnt].move, &g_Feed[nCnt].move);
			}

			// 移動速度
			g_Feed[nCnt].fSpeed = (float)(rand() % (int)(MAX_SPEED * 100.0f) / 100.0f);

			// カウントの初期化
			g_Feed[nCnt].nCntMoveTime = 0;
		}
	}

	g_Feed[nCnt].move += g_Feed[nCnt].joinVec + g_Feed[nCnt].leaveVec + g_Feed[nCnt].averageVec;
	D3DXVec3Normalize(&g_Feed[nCnt].move, &g_Feed[nCnt].move);		// ベクトルを大きさ1

	// 移動方向の算出
	float fDestRot = atan2f((g_Feed[nCnt].move.x + g_Feed[nCnt].pos.x) - g_Feed[nCnt].pos.x,
		(g_Feed[nCnt].move.z + g_Feed[nCnt].pos.z) - g_Feed[nCnt].pos.z);

	// 移動方向の正規化
	g_Feed[nCnt].rotDest.y = RotNormalization(fDestRot - D3DX_PI);

	// 位置の更新
	g_Feed[nCnt].pos += (g_Feed[nCnt].move * g_Feed[nCnt].fSpeed);
}

//---------------------------------------------------------------------------
// 餌回転処理
//---------------------------------------------------------------------------
void RotateFeed(int nCnt)
{
	// 向きの更新
	g_Feed[nCnt].rot.y += (g_Feed[nCnt].rotDest.y - g_Feed[nCnt].rot.y) * FEED_ROTATE_SPEED;

	// 正規化
	g_Feed[nCnt].rot.y = RotNormalization(g_Feed[nCnt].rot.y);
}

//---------------------------------------------------------------------------
// 餌の当たり判定	
//---------------------------------------------------------------------------
void CollisionFeed(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *vtx, D3DXVECTOR3 *vtxOld)
{
	for (int nCnt = 0; nCnt < MAX_FEED; nCnt++)
	{
		if (g_Feed[nCnt].bUse == true && g_Feed[nCnt].bSearchIn != true)
		{// 使用している
			// 頂点の算出
			D3DXVECTOR3 aVecA = D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMax.z);
			D3DXVECTOR3 aVecB = D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMax.z);
			D3DXVECTOR3 aVecC = D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMin.z);
			D3DXVECTOR3 aVecD = D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMin.z);

			// 頂点をワールド座標へキャスト
			aVecA = WorldCastVtx(aVecA, g_Feed[nCnt].pos, g_Feed[nCnt].rot);
			aVecB = WorldCastVtx(aVecB, g_Feed[nCnt].pos, g_Feed[nCnt].rot);
			aVecC = WorldCastVtx(aVecC, g_Feed[nCnt].pos, g_Feed[nCnt].rot);
			aVecD = WorldCastVtx(aVecD, g_Feed[nCnt].pos, g_Feed[nCnt].rot);

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
			 /*g_Feed[nCnt].bUse = false;
			 DeleteShadow(g_Feed[nCnt].nIdx);*/

			 // ベクトルの算出
				aVecPosA = *vtxOld - aVecA;
				aVecPosB = *vtxOld - aVecB;
				aVecPosC = *vtxOld - aVecC;
				aVecPosD = *vtxOld - aVecD;

				// 比較演算用の変数に代入
				fA = (aVecLineA.z * aVecPosA.x) - (aVecLineA.x * aVecPosA.z);
				fB = (aVecLineB.z * aVecPosB.x) - (aVecLineB.x * aVecPosB.z);
				fC = (aVecLineC.z * aVecPosC.x) - (aVecLineC.x * aVecPosC.z);
				fD = (aVecLineD.z * aVecPosD.x) - (aVecLineD.x * aVecPosD.z);

				// 判定用の変数
				D3DXVECTOR3 aJudgeVec;
				D3DXVECTOR3 aJudgeVecLine;

				if (0.0f >= fA)
				{
					aJudgeVec = aVecA;
					aJudgeVecLine = aVecLineA;
				}
				else if (0.0f >= fB)
				{
					aJudgeVec = aVecB;
					aJudgeVecLine = aVecLineB;
				}
				else if (0.0f >= fC)
				{
					aJudgeVec = aVecC;
					aJudgeVecLine = aVecLineC;
				}
				else if (0.0f >= fD)
				{
					aJudgeVec = aVecD;
					aJudgeVecLine = aVecLineD;
				}

				//D3DXVECTOR3 aVecPosOld = aJudgeVec - *posOld;
				//D3DXVECTOR3 aVecMove = *pos - *posOld;

				//// 交点の位置の割合
				//float fIntersection = ((aVecPosOld.z * aVecMove.x) - (aVecPosOld.x * aVecMove.z))
				//	/ ((aVecMove.z * aJudgeVecLine.x) - (aVecMove.x * aJudgeVecLine.z));

				//// 交点の算出
				//pos->x = aJudgeVec.x + fIntersection * aJudgeVecLine.x;
				//pos->z = aJudgeVec.z + fIntersection * aJudgeVecLine.z;

				// 交点の算出
				pos->x = posOld->x;
				pos->z = posOld->z;
			}
		}
	}
}

//---------------------------------------------------------------------------
// リーダーの捜索処理
//---------------------------------------------------------------------------
void SearchLeader(int nCnt)
{
	// 角度の算出
	float fSearchRot = (D3DX_PI * SEARCH_RANGE_ROT);
	float fDistanceMin = (float)(INIT_NUM_FEED);
	float fJoinRot = 0.0f;
	int nCntSearchIn = 0;

	// 結合までのカウントのインクリメント
	g_Feed[nCnt].nCntJoinTime++;

	for (int nCntFeed = 0; nCntFeed < MAX_FEED; nCntFeed++)
	{
		if (nCntFeed != nCnt && g_Feed[nCntFeed].bUse == true)
		{// 自分以外の時
			bool bSearch = false;

			// 仲間のいる向き
			float fFellowRot = atan2f(g_Feed[nCnt].pos.x - g_Feed[nCntFeed].pos.x, g_Feed[nCnt].pos.z - g_Feed[nCntFeed].pos.z);

			// 比較用の向きの算出
			float fSearchRotRight = g_Feed[nCnt].rot.y - fSearchRot;
			float fSRROld = fSearchRotRight;
			fSearchRotRight = RotNormalization(fSearchRotRight);
	
			float fSearchRotLeft = g_Feed[nCnt].rot.y + fSearchRot;
			float fSRLOld = fSearchRotLeft;
			fSearchRotLeft = RotNormalization(fSearchRotLeft);

			if (fSRROld == fSearchRotRight && fSRLOld == fSearchRotLeft)
			{// 正規化前の数値が同じ場合
				if (fSearchRotRight <= fFellowRot
					&& fSearchRotLeft >= fFellowRot)
				{// 味方を検出
					bSearch = true;
				}
			}
			else
			{// 正規化前の数値が違う
				if (fSearchRotRight <= fFellowRot
					|| fSearchRotLeft >= fFellowRot)
				{// 味方を検出
					bSearch = true;
				}
			}

			// 目標までの距離
			D3DXVECTOR3 distance = g_Feed[nCntFeed].pos - g_Feed[nCnt].pos;
			float fDistance = sqrtf((distance.x * distance.x) + (distance.z * distance.z));

			if (bSearch == true
				&& fDistance <= SEARCH_RANGE_LENGTH)
			{// 捜索範囲内味方がいる
				// 味方の方向
				fFellowRot = atan2f(g_Feed[nCntFeed].pos.x - g_Feed[nCnt].pos.x, g_Feed[nCntFeed].pos.z - g_Feed[nCnt].pos.z);

				// 味方までの距離
				float fFeedDistance = sqrtf((g_Feed[nCntFeed].pos.x - g_Feed[nCnt].pos.x) * (g_Feed[nCntFeed].pos.x - g_Feed[nCnt].pos.x)
					+ (g_Feed[nCntFeed].pos.z - g_Feed[nCnt].pos.z) * (g_Feed[nCntFeed].pos.z - g_Feed[nCnt].pos.z));

				// 味方への向きを加算
				fJoinRot += fFellowRot;

				// 範囲内の味方の数を加算
				nCntSearchIn++;

				if (fDistanceMin > fFeedDistance)
				{// 距離が短ければ
					g_Feed[nCnt].nGroup = g_Feed[nCntFeed].nGroup;						// グループ
					g_Feed[nCnt].nIdxLeader = g_Feed[nCntFeed].nGroup;					// リーダー
					fDistanceMin = fFeedDistance;										// 一番近い目標
				}
			}
		}
	}

	if (nCntSearchIn > 0)
	{// 範囲内に味方がいるとき
		// 味方方向の平均を算出
		g_Feed[nCnt].fJoinRot = fJoinRot / nCntSearchIn;
		g_Feed[nCnt].fJoinRot = RotNormalization(g_Feed[nCnt].fJoinRot - D3DX_PI);

		// 結合ベクトルの算出
		g_Feed[nCnt].joinVec.x = sinf(g_Feed[nCnt].fJoinRot - D3DX_PI);
		g_Feed[nCnt].joinVec.z = cosf(g_Feed[nCnt].fJoinRot - D3DX_PI);

		// 結合
		if (g_Feed[nCnt].nCntJoinTime >= JOINT_TIME)
		{// 一定の時間経過した
			// 結合ベクトルの算出
			g_Feed[nCnt].joinVec.x = sinf(g_Feed[nCnt].fJoinRot - D3DX_PI);
			g_Feed[nCnt].joinVec.z = cosf(g_Feed[nCnt].fJoinRot - D3DX_PI);
			g_Feed[nCnt].nCntJoinTime = 0;		// 結合までのカウントを初期化
			D3DXVec3Normalize(&g_Feed[nCnt].joinVec, &g_Feed[nCnt].joinVec);
		}
	}
	else
	{// 範囲内に味方がいない
		g_Feed[nCnt].nIdxLeader = -1;										// リーダー
		g_Feed[nCnt].nGroup = nCnt;											// グループ
		g_Feed[nCnt].fJoinRot = 0.0f;										// 結合方向

		// 結合ベクトルの算出
		g_Feed[nCnt].joinVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVec3Normalize(&g_Feed[nCnt].joinVec, &g_Feed[nCnt].joinVec);
	}
}

//---------------------------------------------------------------------------
// 分離処理
//---------------------------------------------------------------------------
void LeaveFeed(int nCnt)
{
	// 角度の算出
	float fSearchRot = (D3DX_PI * LEAVE_RANGE_ROT);
	float fDistanceMin = (float)(INIT_NUM_FEED);
	int nCntSearchIn = 0;

	for (int nCntFeed = 0; nCntFeed < MAX_FEED; nCntFeed++)
	{
		if (nCntFeed != nCnt && g_Feed[nCntFeed].bUse == true)
		{// 自分以外の時
			bool bSearch = false;

			// 仲間のいる向き
			float fFellowRot = atan2f(g_Feed[nCnt].pos.x - g_Feed[nCntFeed].pos.x, g_Feed[nCnt].pos.z - g_Feed[nCntFeed].pos.z);

			// 比較用の向きの算出
			float fSearchRotRight = g_Feed[nCnt].rot.y - fSearchRot;
			float fSRROld = fSearchRotRight;
			fSearchRotRight = RotNormalization(fSearchRotRight);

			float fSearchRotLeft = g_Feed[nCnt].rot.y + fSearchRot;
			float fSRLOld = fSearchRotLeft;
			fSearchRotLeft = RotNormalization(fSearchRotLeft);

			if (fSRROld == fSearchRotRight && fSRLOld == fSearchRotLeft)
			{// 正規化前の数値が同じ場合
				if (fSearchRotRight <= fFellowRot
					&& fSearchRotLeft >= fFellowRot)
				{// 味方を検出
					bSearch = true;
				}
			}
			else
			{// 正規化前の数値が違う
				if (fSearchRotRight <= fFellowRot
					|| fSearchRotLeft >= fFellowRot)
				{// 味方を検出
					bSearch = true;
				}
			}

			// 目標までの距離
			D3DXVECTOR3 distance = g_Feed[nCntFeed].pos - g_Feed[nCnt].pos;
			float fDistance = sqrtf((distance.x * distance.x) + (distance.z * distance.z));

			if (bSearch == true
				&& fDistance <= LEAVE_RANGE_LENGTH)
			{// 捜索範囲内味方がいる
				float fFeedDistance = sqrtf((g_Feed[nCntFeed].pos.x - g_Feed[nCnt].pos.x) * (g_Feed[nCntFeed].pos.x - g_Feed[nCnt].pos.x)
					+ (g_Feed[nCntFeed].pos.z - g_Feed[nCnt].pos.z) * (g_Feed[nCntFeed].pos.z - g_Feed[nCnt].pos.z));

				// 範囲内に見方がいる場合
				nCntSearchIn++;

				if (fDistanceMin > fFeedDistance)
				{// 距離が短ければ
					fDistanceMin = fFeedDistance;
					g_Feed[nCnt].fLeaveRot = fFellowRot;
					g_Feed[nCnt].fLeaveRot = RotNormalization(g_Feed[nCnt].fLeaveRot - D3DX_PI);
					g_Feed[nCnt].leaveVec.x = sinf(g_Feed[nCnt].fLeaveRot - D3DX_PI);
					g_Feed[nCnt].leaveVec.z = cosf(g_Feed[nCnt].fLeaveRot - D3DX_PI);
					D3DXVec3Normalize(&g_Feed[nCnt].leaveVec, &g_Feed[nCnt].leaveVec);
				}
			}
		}
	}

	if(nCntSearchIn == 0)
	{// 捜索範囲に味方がいない
		g_Feed[nCnt].leaveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Feed[nCnt].fLeaveRot = 0.0f;
	}
}

//---------------------------------------------------------------------------
// 整理処理
//---------------------------------------------------------------------------
void AverageFeed(int nCnt)
{
	float fSearchRot = (D3DX_PI * SEARCH_RANGE_ROT);
	D3DXVECTOR3 average = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int nCntSearchIn = 0;

	for (int nCntFeed = 0; nCntFeed < MAX_FEED; nCntFeed++)
	{
		if (nCntFeed != nCnt && g_Feed[nCntFeed].bUse == true)
		{// 自分以外の時
			bool bSearch = false;

			// 仲間のいる向き
			float fFellowRot = atan2f(g_Feed[nCnt].pos.x - g_Feed[nCntFeed].pos.x, g_Feed[nCnt].pos.z - g_Feed[nCntFeed].pos.z);

			// 比較用の向きの算出
			float fSearchRotRight = g_Feed[nCnt].rot.y - fSearchRot;
			float fSRROld = fSearchRotRight;
			fSearchRotRight = RotNormalization(fSearchRotRight);
			float fSearchRotLeft = g_Feed[nCnt].rot.y + fSearchRot;
			float fSRLOld = fSearchRotLeft;
			fSearchRotLeft = RotNormalization(fSearchRotLeft);

			if (fSRROld == fSearchRotRight && fSRLOld == fSearchRotLeft)
			{// 正規化前の数値が同じ場合
				if (fSearchRotRight <= fFellowRot
					&& fSearchRotLeft >= fFellowRot)
				{// 味方を検出
					bSearch = true;
				}
			}
			else
			{// 正規化前の数値が違う
				if (fSearchRotRight <= fFellowRot
					|| fSearchRotLeft >= fFellowRot)
				{// 味方を検出
					bSearch = true;
				}
			}

			// 目標までの距離
			D3DXVECTOR3 distance = g_Feed[nCntFeed].pos - g_Feed[nCnt].pos;
			float fDistance = sqrtf((distance.x * distance.x) + (distance.z * distance.z));

			if (bSearch == true
				&& fDistance <= LEAVE_RANGE_LENGTH)
			{// 捜索範囲内味方がいる
				float fFeedDistance = sqrtf((g_Feed[nCntFeed].pos.x - g_Feed[nCnt].pos.x) * (g_Feed[nCntFeed].pos.x - g_Feed[nCnt].pos.x)
					+ (g_Feed[nCntFeed].pos.z - g_Feed[nCnt].pos.z) * (g_Feed[nCntFeed].pos.z - g_Feed[nCnt].pos.z));

				// 範囲内に見方がいる場合
				nCntSearchIn++;

				// 平均に加算
				average += g_Feed[nCntFeed].move + g_Feed[nCntFeed].joinVec + g_Feed[nCntFeed].leaveVec;
			}
		}
	}

	if (nCntSearchIn > 0 && g_Feed[nCnt].nIdxLeader != -1)
	{// 範囲内に味方がいた
		// 平均方向の算出
		g_Feed[nCnt].averageVec = average / (float)(nCntSearchIn);
		D3DXVec3Normalize(&g_Feed[nCnt].averageVec, &g_Feed[nCnt].averageVec);
	}
	else
	{// 範囲内に味方がいない
		// 平均方向を初期化
		g_Feed[nCnt].averageVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//---------------------------------------------------------------------------
// プレイヤーから逃げる処理
//---------------------------------------------------------------------------
void LeavePlayer(int nCnt)
{
	// プレイヤー情報の取得
	Player *pPlayer = GetPlayer();

	// 目標までの距離
	D3DXVECTOR3 distance = pPlayer->pos - g_Feed[nCnt].pos;
	float fDistance = sqrtf((distance.x * distance.x) + (distance.z * distance.z));

	if (fDistance <= SEARCH_PLAYER_LENGTH)
	{// 索敵範囲に敵がいた
		// 仲間のいる向き
		D3DXVECTOR3 distance = g_Feed[nCnt].pos - pPlayer->pos;
		float fFellowRot = atan2f(distance.x, distance.z);

		// 移動方向の算出
		g_Feed[nCnt].move.x = sinf(fFellowRot);
		g_Feed[nCnt].move.z = cosf(fFellowRot);

		// 結合と分離を初期化
		g_Feed[nCnt].joinVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Feed[nCnt].leaveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 移動量の加算
		g_Feed[nCnt].pos += g_Feed[nCnt].move * SEARCH_PLAYER_SPEED;

		// 逃げる
		g_Feed[nCnt].bEscape = true;
	}
	else
	{
		g_Feed[nCnt].bEscape = false;
	}
}

//---------------------------------------------------------------------------
// 餌設定処理
//---------------------------------------------------------------------------
void SetFeed(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_FEED; nCnt++)
	{
		if (g_Feed[nCnt].bUse == false)
		{
			// ファイル変数の宣言と代入
			char aFile[128] = FILE_MODEL_DATA;
			strcat(aFile, "魚.x");

			// 餌情報の初期化
			g_Feed[nCnt].pos = pos;																// 位置の初期化
			g_Feed[nCnt].posOld = g_Feed[nCnt].pos;												// 過去位置の初期化
			g_Feed[nCnt].rot = rot;																// 向きの初期化
			g_Feed[nCnt].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// 目的の向きの初期化
			g_Feed[nCnt].joinVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// 結合のベクトルの初期化
			g_Feed[nCnt].leaveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// 離れるベクトルの初期化
			g_Feed[nCnt].averageVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// 平均ベクトルの初期化
			g_Feed[nCnt].nGroup = -1;															// グループ番号
			g_Feed[nCnt].nIdxLeader = -1;														// リーダー番号
			g_Feed[nCnt].vtxMin = D3DXVECTOR3(INIT_NUM_FEED, INIT_NUM_FEED, INIT_NUM_FEED);		// 頂点座標の最小値の初期化
			g_Feed[nCnt].vtxMax = D3DXVECTOR3(-INIT_NUM_FEED, -INIT_NUM_FEED, -INIT_NUM_FEED);	// 頂点座標の最大値の初期化
			g_Feed[nCnt].mtxWorld = {};															// ワールドマトリックス	
			g_Feed[nCnt].fSpeed = 0.5f;															// 移動速度
			g_Feed[nCnt].fJoinRot = 0.0f;														// 結合方向
			g_Feed[nCnt].fLeaveRot = 0.0f;														// 分離方向
			g_Feed[nCnt].nCntJoinTime = 0;														// 結合までの時間
			g_Feed[nCnt].nCntMoveTime = 0;														// 移動量算出までのカウント
			g_Feed[nCnt].bUse = true;															// 使用状況
			g_Feed[nCnt].bEscape = false;														// 逃げていない

			// 移動量の算出
			g_Feed[nCnt].move.x = sinf(g_Feed[nCnt].rot.y);
			g_Feed[nCnt].move.z = cosf(g_Feed[nCnt].rot.y);
			D3DXVec3Normalize(&g_Feed[nCnt].move, &g_Feed[nCnt].move);

			// Xファイルの読み込み
			D3DXLoadMeshFromX(&aFile[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Feed[nCnt].pBuffer,
				NULL,
				&g_Feed[nCnt].nNumMat,
				&g_Feed[nCnt].pMesh);

			// 頂点座標の最小値・最大値の算出
			int		nNumVtx;	// 頂点数
			DWORD	sizeFVF;	// 頂点フォーマットのサイズ
			BYTE	*pVtxBuff;	// 頂点バッファへのポインタ

			// 頂点数の取得
			nNumVtx = g_Feed[nCnt].pMesh->GetNumVertices();

			// 頂点フォーマットのサイズの取得
			sizeFVF = D3DXGetFVFVertexSize(g_Feed[nCnt].pMesh->GetFVF());

			// 頂点バッファのロック
			g_Feed[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				// 頂点座標の代入
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				if (vtx.x < g_Feed[nCnt].vtxMin.x)
				{// 比較対象が現在の頂点座標(X)の最小値より小さい
					g_Feed[nCnt].vtxMin.x = vtx.x;
				}
				if (vtx.y < g_Feed[nCnt].vtxMin.y)
				{// 比較対象が現在の頂点座標(Y)の最小値より小さい
					g_Feed[nCnt].vtxMin.y = vtx.y;
				}
				if (vtx.z < g_Feed[nCnt].vtxMin.z)
				{// 比較対象が現在の頂点座標(Z)の最小値より小さい
					g_Feed[nCnt].vtxMin.z = vtx.z;
				}

				if (vtx.x > g_Feed[nCnt].vtxMax.x)
				{// 比較対象が現在の頂点座標(X)の最大値より大きい
					g_Feed[nCnt].vtxMax.x = vtx.x;
				}
				if (vtx.y > g_Feed[nCnt].vtxMax.y)
				{// 比較対象が現在の頂点座標(Y)の最大値より大きい
					g_Feed[nCnt].vtxMax.y = vtx.y;
				}
				if (vtx.z > g_Feed[nCnt].vtxMax.z)
				{// 比較対象が現在の頂点座標(Z)の最大値より大きい
					g_Feed[nCnt].vtxMax.z = vtx.z;
				}

				// 頂点フォーマットのサイズ分ポインタを進める
				pVtxBuff += sizeFVF;
			}

			// 頂点バッファのアンロック
			g_Feed[nCnt].pMesh->UnlockVertexBuffer();

			// ラインの設定
			//SetLine(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMax.z), D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//SetLine(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMin.z), D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//SetLine(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMin.z), D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMin.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//SetLine(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMin.z), D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//SetLine(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMax.y, g_Feed[nCnt].vtxMax.z), D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMax.y, g_Feed[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//SetLine(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMax.y, g_Feed[nCnt].vtxMin.z), D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMax.y, g_Feed[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//SetLine(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMax.y, g_Feed[nCnt].vtxMin.z), D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMax.y, g_Feed[nCnt].vtxMin.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//SetLine(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMax.y, g_Feed[nCnt].vtxMin.z), D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMax.y, g_Feed[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//SetLine(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMax.z), D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMax.y, g_Feed[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//SetLine(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMin.z), D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMax.y, g_Feed[nCnt].vtxMin.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//SetLine(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMin.z), D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMax.y, g_Feed[nCnt].vtxMin.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//SetLine(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMax.z), D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMax.y, g_Feed[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

			// 影の設定
			g_Feed[nCnt].nIdx = SetShadow(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMax.x - g_Feed[nCnt].vtxMin.x, 0.0f, g_Feed[nCnt].vtxMax.z - g_Feed[nCnt].vtxMin.z));

			g_nCntFeed++;

			break;
		}
	}
}

//---------------------------------------------------------------------------
// 餌の範囲設置処理
//---------------------------------------------------------------------------
void RandSetFeed(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSetRot, float fSetLength, int nNumSet)
{
	// 先頭の配置
	SetFeed(pos, rot);

	for (int nCntFeed = 0; nCntFeed < nNumSet - 1; nCntFeed++)
	{
		// 変数宣言
		float fSetRandRot = ((D3DX_PI * fSetRot) / 2.0f) - (float)(rand() % (int)(((D3DX_PI * fSetRot)) * 100.0f) / 100.0f);		// 群れの中心からの角度
		float fSetRandLength = (float)(rand() % (int)(fSetLength * 100.0f) / 100.0f);												// 群れの中心からの距離
		
		// 位置の算出
		D3DXVECTOR3 setPos = D3DXVECTOR3(pos.x + sinf(rot.y + fSetRandRot) * fSetRandLength,
			0.0f,
			pos.z + cosf(rot.y + fSetRandRot) * fSetRandLength);

		// 配置
		SetFeed(setPos, rot);
	}
}

//---------------------------------------------------------------------------
// 餌の自動範囲設置処理
//---------------------------------------------------------------------------
void SetControllerFeed(void)
{
	if (g_nCntFeed <= MIN_SET_FEED)
	{// 設置数が最小数を下回った場合
		while (g_nCntFeed < MAX_SET_FEED)
		{
			// 位置の算出
			D3DXVECTOR3 pos = D3DXVECTOR3((float)(-(int)(MAX_SET_POS_FEED / 2.0f) + rand() % ((int)(MAX_SET_POS_FEED)+1)),
				0.0f,
				(float)(-(int)(MAX_SET_POS_FEED / 2.0f) + rand() % ((int)(MAX_SET_POS_FEED)+1)));

			// 向きの算出
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, (D3DX_PI * 2 / 2.0f) - (float)(rand() % (int)((D3DX_PI * 2) * 100.0f) / 100.0f), 0.0f);

			// 設置範囲(向き)の算出
			float fRot = (D3DX_PI * 2 / 2.0f) - (float)(rand() % (int)((D3DX_PI * 2 + 1) * 100.0f) / 100.0f);

			// 設置範囲(距離)の算出
			float fLength = (float)(rand() % (int)((200.0f) * 100.0f) / 100.0f);

			// 設置数の算出
			int nNumSet = rand() % (MAX_SET_FEED - g_nCntFeed);

			// 設置
			RandSetFeed(pos, rot, fRot, fLength, nNumSet);
		}
	}
}

//---------------------------------------------------------------------------
// 餌取得処理
//---------------------------------------------------------------------------
Feed *GetFeed(void)
{
	return &g_Feed[0];
}

//---------------------------------------------------------------------------
// 餌ファイル取得処理
//---------------------------------------------------------------------------
FeedFile *GetFeedFile(void)
{
	return &g_FeedFile;
}