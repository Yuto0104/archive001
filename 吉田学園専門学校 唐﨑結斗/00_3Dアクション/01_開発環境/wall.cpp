//**************************************************************************************************
//
// 壁描画処理(wall.cpp)
// Auther：唐﨑結斗
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include "main.h"
#include "wall.h"
#include"file.h"
#include"model.h"
#include"billboard.h"
#include"shadow.h"
#include"effect.h"
#include "calculation.h"

//***************************************************************************
// マクロ定義
//***************************************************************************
#define MAX_WALL_VERTEX			(4)					// 壁の頂点数
#define MAX_WALL				(128)				// 壁の最大数
#define MAX_WALL_WIDH			(200.0f)			// 壁の幅
#define MAX_WALL_HEIGHT			(100.0f)			// 壁の高さ

//***************************************************************************
// グローバル変数
//***************************************************************************
static LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffWall = NULL;		// 頂点バッファへのポインタ
static LPDIRECT3DTEXTURE9			g_pTextureWall = NULL;		// テクスチャへのポインタ
static Wall							g_Wall[MAX_WALL];			// 壁情報の取得

//---------------------------------------------------------------------------
// 壁初期化処理
//---------------------------------------------------------------------------
void InitWall(void)
{
	// ファイル変数の宣言と代入
	char aFile[128] = FILE_TEXTURE_DATA;
	strcat(aFile, "wall000.jpg");

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_WALL_VERTEX * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	// 壁に張り付けるテクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, aFile, &g_pTextureWall);

	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		// 壁情報の初期化
		g_Wall[nCntWall].pos = {};											// 位置
		g_Wall[nCntWall].rot = {};											// 向き
		g_Wall[nCntWall].mtxWorld = {};										// ワールドマトリックス
		g_Wall[nCntWall].col = {};											// カラー
		g_Wall[nCntWall].bUse = false;										// 使用状況

		// 頂点座標
		pVtx[0].pos = D3DXVECTOR3(-MAX_WALL_WIDH, MAX_WALL_HEIGHT,0.0f);
		pVtx[1].pos = D3DXVECTOR3(MAX_WALL_WIDH, MAX_WALL_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-MAX_WALL_WIDH, -MAX_WALL_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(MAX_WALL_WIDH, -MAX_WALL_HEIGHT, 0.0f);

		// 各頂点の法線の設定(*ベクトルの大きさは1にする必要がある)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		// 頂点カラーの設定
		pVtx[0].col = g_Wall[nCntWall].col;
		pVtx[1].col = g_Wall[nCntWall].col;
		pVtx[2].col = g_Wall[nCntWall].col;
		pVtx[3].col = g_Wall[nCntWall].col;

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		//頂点データのポインタを4つ分進める
	}

	// 頂点バッファのアンロック
	g_pVtxBuffWall->Unlock();
}

//---------------------------------------------------------------------------
// 壁終了処理
//---------------------------------------------------------------------------
void UninitWall(void)
{
	//テクスチャの破棄	  
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();

		g_pTextureWall = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//---------------------------------------------------------------------------
// 壁更新処理
//---------------------------------------------------------------------------
void UpdateWall(void)
{
	
}

//---------------------------------------------------------------------------
// 壁描画処理
//---------------------------------------------------------------------------
void DrawWall(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// 計算用マトリックス

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureWall);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == true)
		{// 壁が使用されているとき
			// ワールドマトリックスの初期化
			// 行列初期化関数(第一引数の[行列]を[単位行列]に初期化)
			D3DXMatrixIdentity(&g_Wall[nCntWall].mtxWorld);

			// 向きの反映
			// 行列回転関数 (第一引数に[ヨー(y)ピッチ(x)ロール(z)]方向の回転行列を作成)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[nCntWall].rot.y, g_Wall[nCntWall].rot.x, g_Wall[nCntWall].rot.z);

			// 行列掛け算関数 (第二引数 * 第三引数を第一引数に格納)
			D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorld, &g_Wall[nCntWall].mtxWorld, &mtxRot);

			// 位置を反映
			// 行列移動関数 (第一引数にX,Y,Z方向の移動行列を作成)
			D3DXMatrixTranslation(&mtxTrans, g_Wall[nCntWall].pos.x, g_Wall[nCntWall].pos.y, g_Wall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorld, &g_Wall[nCntWall].mtxWorld, &mtxTrans);		// 行列掛け算関数

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Wall[nCntWall].mtxWorld);

			// 頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			// 頂点フォーマット
			pDevice->SetFVF(FVF_VERTEX_3D);

			// 壁描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, MAX_WALL_VERTEX * nCntWall, 2);
		}
	}

	// テクスチャの解除
	pDevice->SetTexture(0, NULL);
}

//---------------------------------------------------------------------------
// 壁設定処理
//---------------------------------------------------------------------------
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	// 変数宣言
	int nCntWall;

	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == false)
		{
			// 壁情報の設定
			g_Wall[nCntWall].pos = pos;																		// 位置
			g_Wall[nCntWall].rot = D3DXVECTOR3((D3DX_PI * rot.x),(D3DX_PI * rot.y),(D3DX_PI * rot.z));		// 向き
			g_Wall[nCntWall].mtxWorld = {};																	// ワールドマトリックス
			g_Wall[nCntWall].col = col;																		// カラー
			g_Wall[nCntWall].bUse = true;																	// 使用状況

			// 頂点カラーの設定
			pVtx[0].col = g_Wall[nCntWall].col;
			pVtx[1].col = g_Wall[nCntWall].col;
			pVtx[2].col = g_Wall[nCntWall].col;
			pVtx[3].col = g_Wall[nCntWall].col;
			break;
		}

		pVtx += 4;		//頂点データのポインタを4つ分進める
	}

	// 頂点バッファのアンロック
	g_pVtxBuffWall->Unlock();
}

//---------------------------------------------------------------------------
// 壁とビルボードの当たり判定処理
//---------------------------------------------------------------------------
bool	CollisionWallBillBoard(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, int nIdx)
{
	// 変数宣言
	int		nCntWall;
	bool	bIsLanding = false;

	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == true)
		{
			// 変数宣言
			D3DXVECTOR3 aVtx0 = WorldCastVtx(pVtx[0].pos, g_Wall[nCntWall].pos, g_Wall[nCntWall].rot);
			D3DXVECTOR3 aVtx1 = WorldCastVtx(pVtx[1].pos, g_Wall[nCntWall].pos, g_Wall[nCntWall].rot);
			D3DXVECTOR3 aVecLine = aVtx1 - aVtx0;															// 壁のベクトル
			D3DXVECTOR3 aVecPos = D3DXVECTOR3(pos->x - aVtx0.x, pos->y - aVtx0.y, pos->z - aVtx0.z);		// 位置のベクトル
			// 外積を使用した当たり判定
			if (0.0f > (aVecLine.z * aVecPos.x) - (aVecLine.x * aVecPos.z))
			{
				/*bIsLanding = true;*/
				Billboard *pBillboard = GetBillboard();
				pBillboard += nIdx;

				D3DXVECTOR3 VecC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				D3DXVECTOR3 aVtx0 = WorldCastVtx(pVtx[0].pos, g_Wall[nCntWall].pos, g_Wall[nCntWall].rot);
				D3DXVECTOR3 aVtx1 = WorldCastVtx(pVtx[1].pos, g_Wall[nCntWall].pos, g_Wall[nCntWall].rot);
				D3DXVECTOR3 aVtx2 = WorldCastVtx(pVtx[2].pos, g_Wall[nCntWall].pos, g_Wall[nCntWall].rot);
				D3DXVECTOR3 aVecA = aVtx1 - aVtx0;		// 壁のベクトル
				D3DXVECTOR3 aVecB = aVtx2 - aVtx0;		// 壁のベクトル

				// 外積を使用して法線の算出
				D3DXVec3Cross(&VecC, &aVecA, &aVecB);
				D3DXVec3Normalize(&VecC, &VecC);

				VecC *= (-pBillboard->move.x * VecC.x) + (-pBillboard->move.z * VecC.z);

				// 反射
				pBillboard->move += VecC * 2.0f;

				break;
			}
		}
	}

	return bIsLanding;

	// 頂点バッファのアンロック
	g_pVtxBuffWall->Unlock();
}