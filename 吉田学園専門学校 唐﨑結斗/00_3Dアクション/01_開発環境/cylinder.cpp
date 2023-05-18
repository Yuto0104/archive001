//**************************************************************************************************
//
// 円柱描画処理(cylinder.cpp)
// Auther：唐﨑結斗
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include "main.h"
#include "cylinder.h"
#include"file.h"

//***************************************************************************
// マクロ定義
//***************************************************************************
#define CYLINDER_X_BLOCK2			(10)						// X方向のブロック数
#define CYLINDER_Z_BLOCK2			(3)						// Z方向のブロック数

// ブロック数 + 1
#define MESHBLOCK_X_ADD_ONE		(CYLINDER_X_BLOCK2 + 1)
#define MESHBLOCK_Z_ADD_ONE		(CYLINDER_Z_BLOCK2 + 1)

// 1列頂点数
#define CYLINDER_RHINE_VTX_ONE		(CYLINDER_X_BLOCK2 * 2 + 2)

// 円柱の頂点数
#define MAX_CYLINDER_VERTEX			(MESHBLOCK_X_ADD_ONE * MESHBLOCK_Z_ADD_ONE)		

// 円柱のポリゴン数
#define MAX_CYLINDER_POLYGON		((CYLINDER_X_BLOCK2 * CYLINDER_Z_BLOCK2 * 2) + (((CYLINDER_Z_BLOCK2 - 1) * 2) * 2))

// 円柱のインデックス数
#define MAX_CYLINDER_INDEX			((CYLINDER_RHINE_VTX_ONE * CYLINDER_Z_BLOCK2) + ((CYLINDER_Z_BLOCK2 - 1) * 2))	

// 円柱サイズ
#define MAX_CYLINDER_SIZE			(10.0f)

// 円柱の半径の長さ
#define CYLINDER_RADIUS				(50.0f)

//***************************************************************************
// グローバル変数
//***************************************************************************
static LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffCylinder = NULL;		// 頂点バッファへのポインタ
static LPDIRECT3DTEXTURE9			g_pTextureCylinder = NULL;		// テクスチャへのポインタ
static LPDIRECT3DINDEXBUFFER9		g_pIdzBuffCylinder = NULL;		// インデックスバッファへのポインタ
static Cylinder						g_Cylinder;						// 円柱情報の取得

//---------------------------------------------------------------------------
// 円柱初期化処理
//---------------------------------------------------------------------------
void InitCylinder(void)
{
	g_Cylinder.pos = D3DXVECTOR3(0.0f, 0.0f, 100.0f);

	// ファイル変数の宣言と代入
	char aFile[128] = FILE_TEXTURE_DATA;
	strcat(aFile, "sky001.jpg");

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 円柱に張り付けるテクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, aFile, &g_pTextureCylinder);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_CYLINDER_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCylinder,
		NULL);

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_CYLINDER_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdzBuffCylinder,
		NULL);

	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffCylinder->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntV = 0; nCntV < CYLINDER_Z_BLOCK2 + 1; nCntV++)
	{
		for (int nCntH = 0; nCntH < CYLINDER_X_BLOCK2 + 1; nCntH++)
		{// 変数宣言
			float fRot = ((D3DX_PI * 2.0f) / CYLINDER_X_BLOCK2) * nCntH;		// 角度の設定

			// 頂点座標の設定
			pVtx[0].pos.x = sinf(fRot) * CYLINDER_RADIUS;
			pVtx[0].pos.z = cosf(fRot) * CYLINDER_RADIUS;
			pVtx[0].pos.y = MAX_CYLINDER_SIZE * nCntV;

			// 各頂点の法線の設定(*ベクトルの大きさは1にする必要がある)
			pVtx[0].nor.x = pVtx[0].pos.x;
			pVtx[0].nor.z = pVtx[0].pos.z;
			pVtx[0].nor.y = 0.0f;
			D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);

			// 頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(1.0f / CYLINDER_X_BLOCK2 * nCntH, 1.0f / CYLINDER_X_BLOCK2 * nCntV);

			pVtx++;
		}
	}

	// インデックスバッファをロック
	WORD *pIdx;
	g_pIdzBuffCylinder->Lock(0, 0, (void**)&pIdx, 0);

	// インデックスの設定
	for (int nCntZ = 0; nCntZ < CYLINDER_Z_BLOCK2; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESHBLOCK_X_ADD_ONE; nCntX++)
		{// インデックス数の設定
			pIdx[0] = MESHBLOCK_X_ADD_ONE + nCntX + nCntZ * MESHBLOCK_X_ADD_ONE;
			pIdx[1] = MESHBLOCK_X_ADD_ONE + nCntX + nCntZ * MESHBLOCK_X_ADD_ONE - MESHBLOCK_X_ADD_ONE;

			pIdx += 2;
		}

		if (nCntZ != CYLINDER_Z_BLOCK2)
		{// 最大数以下の時
		 // 縮退ポリゴンインデックス数の設定
			pIdx[0] = MESHBLOCK_X_ADD_ONE * nCntZ + CYLINDER_X_BLOCK2;
			pIdx[1] = MESHBLOCK_X_ADD_ONE * (nCntZ + 2);

			pIdx += 2;
		}
	}

	// 頂点バッファのアンロック
	g_pVtxBuffCylinder->Unlock();

	// 頂点バッファのアンロック
	g_pIdzBuffCylinder->Unlock();
}

//---------------------------------------------------------------------------
// 円柱終了処理
//---------------------------------------------------------------------------
void UninitCylinder(void)
{
	// テクスチャの破棄	  
	if (g_pTextureCylinder != NULL)
	{
		g_pTextureCylinder->Release();
		g_pTextureCylinder = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffCylinder != NULL)
	{
		g_pVtxBuffCylinder->Release();
		g_pVtxBuffCylinder = NULL;
	}

	// インデックスバッファの破棄	  
	if (g_pIdzBuffCylinder != NULL)
	{
		g_pIdzBuffCylinder->Release();
		g_pIdzBuffCylinder = NULL;
	}
}

//---------------------------------------------------------------------------
// 円柱更新処理
//---------------------------------------------------------------------------
void UpdateCylinder(void)
{

}

//---------------------------------------------------------------------------
// 円柱描画処理
//---------------------------------------------------------------------------
void DrawCylinder(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// 計算用マトリックス

	// ワールドマトリックスの初期化
	// 行列初期化関数(第一引数の[行列]を[単位行列]に初期化)
	D3DXMatrixIdentity(&g_Cylinder.mtxWorld);

	// 向きの反映
	// 行列回転関数 (第一引数に[ヨー(y)ピッチ(x)ロール(z)]方向の回転行列を作成)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Cylinder.rot.y, g_Cylinder.rot.x, g_Cylinder.rot.z);

	// 行列掛け算関数 (第二引数 * 第三引数を第一引数に格納)
	D3DXMatrixMultiply(&g_Cylinder.mtxWorld, &g_Cylinder.mtxWorld, &mtxRot);

	// 位置を反映
	// 行列移動関数 (第一引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, g_Cylinder.pos.x, g_Cylinder.pos.y, g_Cylinder.pos.z);
	D3DXMatrixMultiply(&g_Cylinder.mtxWorld, &g_Cylinder.mtxWorld, &mtxTrans);						// 行列掛け算関数

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Cylinder.mtxWorld);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffCylinder, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdzBuffCylinder);

	// 頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureCylinder);

	// 円柱描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_CYLINDER_VERTEX, 0, MAX_CYLINDER_POLYGON);

	// テクスチャの解除
	pDevice->SetTexture(0, NULL);
}