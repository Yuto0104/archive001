//**************************************************************************************************
//
// モデル描画処理(model.cpp)
// Auther：唐﨑結斗
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include "main.h"
#include "model.h"
#include"file.h"
#include"input.h"
#include"camera.h"
#include"shadow.h"
#include"billboard.h"
#include"effect.h"
#include"line.h"
#include"calculation.h"
#include"player.h"
#include"feed.h"

//***************************************************************************
// マクロ定義
//***************************************************************************
#define INIT_NUM_MODEL			(10000)				// 頂点座標の最大最小の初期値
#define MODEL_MOVE_SPEED		(0.5f)				// 移動速度
#define MODEL_ROTATE_SPEED		(0.1f)				// 回転速度

//***************************************************************************
// グローバル変数
//***************************************************************************
static Model			g_model[MAX_MODEL];				// モデル情報
static ModelFile		g_ModelFile[MAX_MODEL_NAME];	// モデルファイル名情報

//---------------------------------------------------------------------------
// モデル初期化処理
//---------------------------------------------------------------------------
void InitModel(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// モデルファイル名情報の初期化
	memset(&g_ModelFile[0], 0, sizeof(g_ModelFile));

	// モデル情報の初期化
	memset(&g_model[0], 0, sizeof(g_model));
}

//---------------------------------------------------------------------------
// モデル終了処理
//---------------------------------------------------------------------------
void UninitModel(void)
{
	for (int i = 0; i < MAX_MODEL; i++)
	{
		// メッシュの破棄
		if (g_model[i].pMesh != NULL)
		{
			g_model[i].pMesh->Release();
			g_model[i].pMesh = NULL;
		}

		// マテリアルの破棄
		if (g_model[i].pBuffer != NULL)
		{
			g_model[i].pBuffer->Release();
			g_model[i].pBuffer = NULL;
		}
	}
}

//---------------------------------------------------------------------------
// モデル更新処理
//---------------------------------------------------------------------------
void UpdateModel(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_model[nCnt].bUse == true)
		{// 使用している
			bool bSearchIn = false;
			bool bOnCollisionPlayer = false;

			// モデルの移動
			//MoveModel();

			//モデルの回転
			//RotateModel();

			// プレイヤーの視野角内にいるか
			bSearchIn = SearchPlayer(&g_model[nCnt].pos);

			// プレイヤーの当たり判定
			D3DXVECTOR3 aVtxA = WorldCastVtx(D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMax.z), g_model[nCnt].pos, g_model[nCnt].rot);
			D3DXVECTOR3 aVtxB = WorldCastVtx(D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMax.z), g_model[nCnt].pos, g_model[nCnt].rot);
			D3DXVECTOR3 aVtxC = WorldCastVtx(D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMin.z), g_model[nCnt].pos, g_model[nCnt].rot);
			D3DXVECTOR3 aVtxD = WorldCastVtx(D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMin.z), g_model[nCnt].pos, g_model[nCnt].rot);
			CollisionPlayer(&aVtxA);
			CollisionPlayer(&aVtxB);
			CollisionPlayer(&aVtxC);
			CollisionPlayer(&aVtxD);
			CollisionFeed(&g_model[nCnt].pos, &g_model[nCnt].pos, &aVtxA, &aVtxA);
			CollisionFeed(&g_model[nCnt].pos, &g_model[nCnt].pos, &aVtxB, &aVtxB);
			CollisionFeed(&g_model[nCnt].pos, &g_model[nCnt].pos, &aVtxC, &aVtxC);
			CollisionFeed(&g_model[nCnt].pos, &g_model[nCnt].pos, &aVtxD, &aVtxD);

			if (bSearchIn == true && bOnCollisionPlayer == true)
			{// 視野角内にいてプレイヤーに当たっている時
				g_model[nCnt].bUse = false;
			}
			
			// 影の移動
			SetPositionShadow(g_model[nCnt].nIdx, g_model[nCnt].pos, g_model[nCnt].rot,D3DXVECTOR3(g_model[nCnt].vtxMax.x - g_model[nCnt].vtxMin.x, 0.0f, g_model[nCnt].vtxMax.z - g_model[nCnt].vtxMin.z));
		}
	}
}

//---------------------------------------------------------------------------
// モデル描画処理
//---------------------------------------------------------------------------
void DrawModel(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans, mtxScaling;			// 計算用マトリックス
	D3DMATERIAL9		matDef;									// 現在のマテリアル保存用
	D3DXMATERIAL		*pMat;									// マテリアルデータへのポインタ

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_model[nCnt].bUse == true)
		{// 使用している
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_model[nCnt].mtxWorld);			// 行列初期化関数

			// 向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_model[nCnt].rot.y, g_model[nCnt].rot.x, g_model[nCnt].rot.z);		// 行列回転関数
			D3DXMatrixMultiply(&g_model[nCnt].mtxWorld, &g_model[nCnt].mtxWorld, &mtxRot);								// 行列掛け算関数 

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_model[nCnt].pos.x, g_model[nCnt].pos.y, g_model[nCnt].pos.z);				// 行列移動関数
			D3DXMatrixMultiply(&g_model[nCnt].mtxWorld, &g_model[nCnt].mtxWorld, &mtxTrans);								// 行列掛け算関数

			//// サイズの反映
			//D3DXMatrixScaling(&mtxScaling, 0.1f, 0.1f, 0.1f);
			//D3DXMatrixMultiply(&g_model[nCnt].mtxWorld, &g_model[nCnt].mtxWorld, &mtxScaling);						// 行列掛け算関数

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_model[nCnt].mtxWorld);

			// 現在のマテリアルを保持
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_model[nCnt].pBuffer->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_model[nCnt].nNumMat; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// モデルパーツの描画
				g_model[nCnt].pMesh->DrawSubset(nCntMat);
			}

			// 保持していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//---------------------------------------------------------------------------
// モデル移動処理
//---------------------------------------------------------------------------
void MoveModel(int nCnt)
{
	if (GetKeyboardPress(DIK_UP)
		|| GetKeyboardPress(DIK_LEFT)
		|| GetKeyboardPress(DIK_RIGHT)
		|| GetKeyboardPress(DIK_DOWN))
	{// 移動キーが押された
		if (GetKeyboardPress(DIK_UP))
		{// [↑]キーが押された時
			if (GetKeyboardPress(DIK_LEFT))
			{// [→]キーが押された時
				// 移動方向の更新
				g_model[nCnt].rotDest.y = D3DX_PI * -0.25f;
			}
			else if (GetKeyboardPress(DIK_RIGHT))
			{// [←]キーが押された時
				// 移動方向の更新
				g_model[nCnt].rotDest.y = D3DX_PI * 0.25f;
			}
			else
			{// 移動方向の更新
				g_model[nCnt].rotDest.y = D3DX_PI * 0.0f;
			}
		}
		else if (GetKeyboardPress(DIK_DOWN))
		{// [↓]キーが押された時
			if (GetKeyboardPress(DIK_LEFT))
			{// [→]キーが押された時
				// 移動方向の更新
				g_model[nCnt].rotDest.y = D3DX_PI * -0.75f;
			}
			else if (GetKeyboardPress(DIK_RIGHT))
			{// [←]キーが押された時
				// 移動方向の更新
				g_model[nCnt].rotDest.y = D3DX_PI * 0.75f;
			}
			else
			{// 移動方向の更新
				g_model[nCnt].rotDest.y = D3DX_PI;
			}
		}
		else if (GetKeyboardPress(DIK_LEFT))
		{// [→]キーが押された時
			// 移動方向の更新
			g_model[nCnt].rotDest.y = D3DX_PI * -0.5f;
		}
		else if (GetKeyboardPress(DIK_RIGHT))
		{// [←]キーが押された時
			// 移動方向の更新
			g_model[nCnt].rotDest.y = D3DX_PI * 0.5f;
		}

		// カメラ情報の取得
		Camera *pCamera = GetCamera();

		// 移動方向の算出
		g_model[nCnt].rotDest.y += pCamera->rot.y;
		if (g_model[nCnt].rotDest.y > D3DX_PI)
		{// 移動方向の正規化
			g_model[nCnt].rotDest.y -= D3DX_PI * 2;
		}
		else if (g_model[nCnt].rotDest.y < -D3DX_PI)
		{// 移動方向の正規化
			g_model[nCnt].rotDest.y += D3DX_PI * 2;
		}

		// 視点位置と向きの更新
		g_model[nCnt].pos.x += sinf(g_model[nCnt].rotDest.y) * MODEL_MOVE_SPEED;
		g_model[nCnt].pos.z += cosf(g_model[nCnt].rotDest.y) * MODEL_MOVE_SPEED;
		g_model[nCnt].rotDest.y -= D3DX_PI;
	}

	if (GetKeyboardPress(DIK_I))
	{// [I]キーが押された時
		// 移動方向の更新
		g_model[nCnt].pos.y += MODEL_MOVE_SPEED;
	}
	else if (GetKeyboardPress(DIK_K))
	{// [K]キーが押された時
		// 移動方向の更新
		g_model[nCnt].pos.y -= MODEL_MOVE_SPEED;
	}

	// 目的の向きの補正
	if (g_model[nCnt].rotDest.y - g_model[nCnt].rot.y >= D3DX_PI)
	{// 移動方向の正規化
		g_model[nCnt].rotDest.y -= D3DX_PI * 2;
	}
	else if (g_model[nCnt].rotDest.y - g_model[nCnt].rot.y <= -D3DX_PI)
	{// 移動方向の正規化
		g_model[nCnt].rotDest.y += D3DX_PI * 2;
	}
}

//---------------------------------------------------------------------------
// モデル回転処理
//---------------------------------------------------------------------------
void RotateModel(int nCnt)
{
	// 向きの更新
	g_model[nCnt].rot.y += (g_model[nCnt].rotDest.y - g_model[nCnt].rot.y) * MODEL_ROTATE_SPEED;

	if (g_model[nCnt].rot.y >= D3DX_PI)
	{// 移動方向の正規化
		g_model[nCnt].rot.y -= D3DX_PI * 2;
	}
	else if (g_model[nCnt].rot.y <= -D3DX_PI)
	{// 移動方向の正規化
		g_model[nCnt].rot.y += D3DX_PI * 2;
	}
}

//---------------------------------------------------------------------------
// モデルの当たり判定	
//---------------------------------------------------------------------------
bool CollisionModel(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *vtx, D3DXVECTOR3 *vtxOld)
{
	bool bIsLanding = false;

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_model[nCnt].bUse == true)
		{// 使用している
			//if ((int)(pos->z - size.z / 2) < (int)(g_model[nCnt].pos.z + g_model[nCnt].vtxMax.z)
			//	&& (int)(pos->z + size.z / 2) > (int)(g_model[nCnt].pos.z + g_model[nCnt].vtxMin.z)
			//	&& (int)(pos->x - size.x / 2) < (int)(g_model[nCnt].pos.x + g_model[nCnt].vtxMax.x)
			//	&& (int)(pos->x + size.x / 2) > (int)(g_model[nCnt].pos.x + g_model[nCnt].vtxMin.x))
			//{// モデル内にいる(XZ軸)
			//	if ((int)(posOld->y + size.y) <= (int)(g_model[nCnt].pos.y + g_model[nCnt].vtxMin.y)
			//		&& (int)(pos->y + size.y) >(int)(g_model[nCnt].pos.y + g_model[nCnt].vtxMin.y))
			//	{
			//		pos->y = g_model[nCnt].pos.y + g_model[nCnt].vtxMin.y - size.y;
			//	}
			//	if ((int)(posOld->y) >= (int)(g_model[nCnt].pos.y + g_model[nCnt].vtxMax.y)
			//		&& (int)(pos->y) < (int)(g_model[nCnt].pos.y + g_model[nCnt].vtxMax.y))
			//	{
			//		pos->y = g_model[nCnt].pos.y + g_model[nCnt].vtxMax.y;
			//	}
			//}
			//if ((int)(pos->y) < (int)(g_model[nCnt].pos.y + g_model[nCnt].vtxMax.y)
			//	&& (int)(pos->y + size.y) > (int)(g_model[nCnt].pos.y + g_model[nCnt].vtxMin.y))
			//{// モデル内にいる(Y軸)
			//	if ((int)(pos->z - size.z / 2) < (int)(g_model[nCnt].pos.z + g_model[nCnt].vtxMax.z)
			//		&& (int)(pos->z + size.z / 2) > (int)(g_model[nCnt].pos.z + g_model[nCnt].vtxMin.z))
			//	{// モデル内にいる(Z軸)
			//		if ((int)(posOld->x + size.z / 2) <= (int)(g_model[nCnt].pos.x + g_model[nCnt].vtxMin.x)
			//			&& (int)(pos->x + size.z / 2) > (int)(g_model[nCnt].pos.x + g_model[nCnt].vtxMin.x))
			//		{
			//			pos->x = g_model[nCnt].pos.x + g_model[nCnt].vtxMin.x - size.z / 2;
			//		}
			//		if ((int)(posOld->x - size.z / 2) >= (int)(g_model[nCnt].pos.x + g_model[nCnt].vtxMax.x)
			//			&& (int)(pos->x - size.z / 2) < (int)(g_model[nCnt].pos.x + g_model[nCnt].vtxMax.x))
			//		{
			//			pos->x = g_model[nCnt].pos.x + g_model[nCnt].vtxMax.x + size.z / 2;
			//		}
			//	}
			//	if ((int)(pos->x - size.x / 2) < (int)(g_model[nCnt].pos.x + g_model[nCnt].vtxMax.x)
			//		&& (int)(pos->x + size.x / 2) > (int)(g_model[nCnt].pos.x + g_model[nCnt].vtxMin.x))
			//	{// モデル内にいる(X軸)
			//		if ((int)(posOld->z + size.z / 2) <= (int)(g_model[nCnt].pos.z + g_model[nCnt].vtxMin.z)
			//			&& (int)(pos->z + size.z / 2) > (int)(g_model[nCnt].pos.z + g_model[nCnt].vtxMin.z))
			//		{
			//			pos->z = g_model[nCnt].pos.z + g_model[nCnt].vtxMin.z - size.z / 2;
			//		}
			//		if ((int)(posOld->z - size.z / 2) >= (int)(g_model[nCnt].pos.z + g_model[nCnt].vtxMax.z)
			//			&& (int)(pos->z - size.z / 2) < (int)(g_model[nCnt].pos.z + g_model[nCnt].vtxMax.z))
			//		{
			//			pos->z = g_model[nCnt].pos.z + g_model[nCnt].vtxMax.z + size.z / 2;
			//		}
			//	}
			//}

			// 頂点の算出
			D3DXVECTOR3 aVecA = D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMax.z);
			D3DXVECTOR3 aVecB = D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMax.z);
			D3DXVECTOR3 aVecC = D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMin.z);
			D3DXVECTOR3 aVecD = D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMin.z);

			// 頂点をワールド座標へキャスト
			aVecA = WorldCastVtx(aVecA, g_model[nCnt].pos, g_model[nCnt].rot);
			aVecB = WorldCastVtx(aVecB, g_model[nCnt].pos, g_model[nCnt].rot);
			aVecC = WorldCastVtx(aVecC, g_model[nCnt].pos, g_model[nCnt].rot);
			aVecD = WorldCastVtx(aVecD, g_model[nCnt].pos, g_model[nCnt].rot);

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
				/*g_model[nCnt].bUse = false;
				DeleteShadow(g_model[nCnt].nIdx);*/

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

				bIsLanding = true;
			}
		}
	}

	return bIsLanding;
}

//---------------------------------------------------------------------------
// モデル設定処理
//---------------------------------------------------------------------------
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_model[nCnt].bUse == false)
		{
			// モデル情報の初期化
			g_model[nCnt].pos = pos;																// 位置の初期化
			g_model[nCnt].rot = rot;																// 向きの初期化
			g_model[nCnt].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									// 目的の向きの初期化
			g_model[nCnt].vtxMin = D3DXVECTOR3(INIT_NUM_MODEL, INIT_NUM_MODEL, INIT_NUM_MODEL);		// 頂点座標の最小値の初期化
			g_model[nCnt].vtxMax = D3DXVECTOR3(-INIT_NUM_MODEL, -INIT_NUM_MODEL, -INIT_NUM_MODEL);	// 頂点座標の最大値の初期化
			g_model[nCnt].mtxWorld = {};															// ワールドマトリックス
			g_model[nCnt].rotDest = {};																// 目的の向き
			g_model[nCnt].nType = nType;															// タイプ				
			g_model[nCnt].bUse = true;																// 使用状況

			// Xファイルの読み込み
			D3DXLoadMeshFromX(&g_ModelFile[g_model[nCnt].nType].aName[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_model[nCnt].pBuffer,
				NULL,
				&g_model[nCnt].nNumMat,
				&g_model[nCnt].pMesh);

			// 頂点座標の最小値・最大値の算出
			int		nNumVtx;	// 頂点数
			DWORD	sizeFVF;	// 頂点フォーマットのサイズ
			BYTE	*pVtxBuff;	// 頂点バッファへのポインタ

			// 頂点数の取得
			nNumVtx = g_model[nCnt].pMesh->GetNumVertices();

			// 頂点フォーマットのサイズの取得
			sizeFVF = D3DXGetFVFVertexSize(g_model[nCnt].pMesh->GetFVF());

			// 頂点バッファのロック
			g_model[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				// 頂点座標の代入
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				if (vtx.x < g_model[nCnt].vtxMin.x)
				{// 比較対象が現在の頂点座標(X)の最小値より小さい
					g_model[nCnt].vtxMin.x = vtx.x;
				}
				if (vtx.y < g_model[nCnt].vtxMin.y)
				{// 比較対象が現在の頂点座標(Y)の最小値より小さい
					g_model[nCnt].vtxMin.y = vtx.y;
				}
				if (vtx.z < g_model[nCnt].vtxMin.z)
				{// 比較対象が現在の頂点座標(Z)の最小値より小さい
					g_model[nCnt].vtxMin.z = vtx.z;
				}

				if (vtx.x > g_model[nCnt].vtxMax.x)
				{// 比較対象が現在の頂点座標(X)の最大値より大きい
					g_model[nCnt].vtxMax.x = vtx.x;
				}
				if (vtx.y > g_model[nCnt].vtxMax.y)
				{// 比較対象が現在の頂点座標(Y)の最大値より大きい
					g_model[nCnt].vtxMax.y = vtx.y;
				}
				if (vtx.z > g_model[nCnt].vtxMax.z)
				{// 比較対象が現在の頂点座標(Z)の最大値より大きい
					g_model[nCnt].vtxMax.z = vtx.z;
				}

				// 頂点フォーマットのサイズ分ポインタを進める
				pVtxBuff += sizeFVF;
			}

			// 頂点バッファのアンロック
			g_model[nCnt].pMesh->UnlockVertexBuffer();

			// ラインの設定
			SetLine(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMax.z), D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			SetLine(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMin.z), D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			SetLine(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMin.z), D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMin.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			SetLine(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMin.z), D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			
			SetLine(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMax.y, g_model[nCnt].vtxMax.z), D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMax.y, g_model[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			SetLine(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMax.y, g_model[nCnt].vtxMin.z), D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMax.y, g_model[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			SetLine(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMax.y, g_model[nCnt].vtxMin.z), D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMax.y, g_model[nCnt].vtxMin.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			SetLine(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMax.y, g_model[nCnt].vtxMin.z), D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMax.y, g_model[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			
			SetLine(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMax.z), D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMax.y, g_model[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			SetLine(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMin.z), D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMax.y, g_model[nCnt].vtxMin.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			SetLine(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMin.z), D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMax.y, g_model[nCnt].vtxMin.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			SetLine(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMax.z), D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMax.y, g_model[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

			// 影の設定
			g_model[nCnt].nIdx = SetShadow(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMax.x - g_model[nCnt].vtxMin.x, 0.0f, g_model[nCnt].vtxMax.z - g_model[nCnt].vtxMin.z));

			break;
		}
	}
}

//---------------------------------------------------------------------------
// モデル取得処理
//---------------------------------------------------------------------------
Model *GetModel(void)
{
	return &g_model[0];
}

//---------------------------------------------------------------------------
// モデルファイル取得処理
//---------------------------------------------------------------------------
ModelFile *GetModelFile(void)
{
	return &g_ModelFile[0];
}