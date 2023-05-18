//**************************************************************************************************
//
// 球描画処理(sphere.cpp)
// Auther：唐﨑結斗
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include "main.h"
#include "sphere.h"
#include"file.h"

//***************************************************************************
// マクロ定義
//***************************************************************************
#define SPHERE_X_BLOCK2				(100)						// X方向のブロック数
#define SPHERE_Z_BLOCK2				(10)						// Z方向のブロック数

// ブロック数 + 1
#define MESHBLOCK_X_ADD_ONE			(SPHERE_X_BLOCK2 + 1)
#define MESHBLOCK_Z_ADD_ONE			(SPHERE_Z_BLOCK2 + 1)

// 1列頂点数
#define SPHERE_RHINE_VTX_ONE		(SPHERE_X_BLOCK2 * 2 + 2)

// 球の頂点数
#define MAX_SPHERE_VERTEX			(MESHBLOCK_X_ADD_ONE * MESHBLOCK_Z_ADD_ONE)		

// 球のポリゴン数
#define MAX_SPHERE_POLYGON			((SPHERE_X_BLOCK2 * SPHERE_Z_BLOCK2 * 2) + (((SPHERE_Z_BLOCK2 - 1) * 2) * 2))

// 球のインデックス数
#define MAX_SPHERE_INDEX			((SPHERE_RHINE_VTX_ONE * SPHERE_Z_BLOCK2) + ((SPHERE_Z_BLOCK2 - 1) * 2))	

// 球サイズ
#define MAX_SPHERE_SIZE				(10.0f)

// 球の半径の長さ
#define SPHERE_RADIUS				(50.0f)


//***************************************************************************
// グローバル変数
//***************************************************************************
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffSphere = NULL;		// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9			g_pTextureSphere = NULL;		// テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9		g_pIdzBuffSphere = NULL;		// インデックスバッファへのポインタ
Sphere						g_Sphere;						// 球情報の取得

//---------------------------------------------------------------------------
// 球初期化処理
//---------------------------------------------------------------------------
void InitSphere(void)
{
	// ファイル変数の宣言と代入
	char aFile[128] = FILE_TEXTURE_DATA;
	strcat(aFile, "sky001.jpg");

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 球に張り付けるテクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, aFile, &g_pTextureSphere);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_SPHERE_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSphere,
		NULL);

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_SPHERE_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdzBuffSphere,
		NULL);

	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffSphere->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntV = 0; nCntV < SPHERE_Z_BLOCK2 + 1; nCntV++)
	{
		for (int nCntH = 0; nCntH < SPHERE_X_BLOCK2 + 1; nCntH++)
		{// 変数宣言
			float fRot = ((-D3DX_PI * 2.0f) / SPHERE_X_BLOCK2) * nCntH;			// Y軸の角度の設定
			float fHalfRot = (-D3DX_PI / SPHERE_Z_BLOCK2) * nCntV;				// 半球のZ軸の角度の半分

			// 高さと半径の設定
			D3DXVECTOR2 radius = D3DXVECTOR2(sinf(fHalfRot) * SPHERE_RADIUS, cosf(fHalfRot) * SPHERE_RADIUS);

			//// 頂点座標の設定
			//pVtx[0].pos.x = sinf(fRot) * radius.y;
			//pVtx[0].pos.z = cosf(fRot) * radius.y;
			//pVtx[0].pos.y = radius.x;

			// 注視点の算出
			pVtx[0].pos.z = sinf(fHalfRot) * cosf(fRot) * SPHERE_RADIUS;
			pVtx[0].pos.x = sinf(fHalfRot) * sinf(fRot) * SPHERE_RADIUS;
			pVtx[0].pos.y = cosf(fHalfRot) * SPHERE_RADIUS;

			// 各頂点の法線の設定(*ベクトルの大きさは1にする必要がある)
			pVtx[0].nor.x = pVtx[0].pos.x;
			pVtx[0].nor.z = pVtx[0].pos.z;
			pVtx[0].nor.y = 0.0f;
			D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);

			// 頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(1.0f / SPHERE_X_BLOCK2 * nCntH, 1.0f / SPHERE_Z_BLOCK2 * nCntV);

			pVtx++;
		}
	}

	// インデックスバッファをロック
	WORD *pIdx;
	g_pIdzBuffSphere->Lock(0, 0, (void**)&pIdx, 0);

	// インデックスの設定
	for (int nCntZ = 0; nCntZ < SPHERE_Z_BLOCK2; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESHBLOCK_X_ADD_ONE; nCntX++)
		{// インデックス数の設定
			pIdx[0] = MESHBLOCK_X_ADD_ONE + nCntX + nCntZ * MESHBLOCK_X_ADD_ONE;
			pIdx[1] = MESHBLOCK_X_ADD_ONE + nCntX + nCntZ * MESHBLOCK_X_ADD_ONE - MESHBLOCK_X_ADD_ONE;

			pIdx += 2;
		}

		if (nCntZ != SPHERE_Z_BLOCK2)
		{// 最大数以下の時
		 // 縮退ポリゴンインデックス数の設定
			pIdx[0] = MESHBLOCK_X_ADD_ONE * nCntZ + SPHERE_X_BLOCK2;
			pIdx[1] = MESHBLOCK_X_ADD_ONE * (nCntZ + 2);

			pIdx += 2;
		}
	}

	// 頂点バッファのアンロック
	g_pVtxBuffSphere->Unlock();

	// 頂点バッファのアンロック
	g_pIdzBuffSphere->Unlock();
}

//---------------------------------------------------------------------------
// 球終了処理
//---------------------------------------------------------------------------
void UninitSphere(void)
{
	// テクスチャの破棄	  
	if (g_pTextureSphere != NULL)
	{
		g_pTextureSphere->Release();
		g_pTextureSphere = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffSphere != NULL)
	{
		g_pVtxBuffSphere->Release();
		g_pVtxBuffSphere = NULL;
	}

	// インデックスバッファの破棄	  
	if (g_pIdzBuffSphere != NULL)
	{
		g_pIdzBuffSphere->Release();
		g_pIdzBuffSphere = NULL;
	}
}

//---------------------------------------------------------------------------
// 球更新処理
//---------------------------------------------------------------------------
void UpdateSphere(void)
{

}

//---------------------------------------------------------------------------
// 球描画処理
//---------------------------------------------------------------------------
void DrawSphere(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// 計算用マトリックス

	// ワールドマトリックスの初期化
	// 行列初期化関数(第一引数の[行列]を[単位行列]に初期化)
	D3DXMatrixIdentity(&g_Sphere.mtxWorld);

	// 向きの反映
	// 行列回転関数 (第一引数に[ヨー(y)ピッチ(x)ロール(z)]方向の回転行列を作成)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Sphere.rot.y, g_Sphere.rot.x, g_Sphere.rot.z);

	// 行列掛け算関数 (第二引数 * 第三引数を第一引数に格納)
	D3DXMatrixMultiply(&g_Sphere.mtxWorld, &g_Sphere.mtxWorld, &mtxRot);

	// 位置を反映
	// 行列移動関数 (第一引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, g_Sphere.pos.x, g_Sphere.pos.y, g_Sphere.pos.z);
	D3DXMatrixMultiply(&g_Sphere.mtxWorld, &g_Sphere.mtxWorld, &mtxTrans);						// 行列掛け算関数

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Sphere.mtxWorld);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSphere, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdzBuffSphere);

	// 頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureSphere);

	// 球描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_SPHERE_VERTEX, 0, MAX_SPHERE_POLYGON);

	// テクスチャの解除
	pDevice->SetTexture(0, NULL);
}