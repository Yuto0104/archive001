//**************************************************************************************************
//
// メッシュフィールド描画処理(meshmield.cpp)
// Auther：唐﨑結斗
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include "main.h"
#include "meshfield.h"
#include"file.h"

//***************************************************************************
// マクロ定義
//***************************************************************************
#define MESHFIELD_X_BLOCK2			(20)						// X方向のブロック数
#define MESHFIELD_Z_BLOCK2			(20)						// Z方向のブロック数

// ブロック数 + 1
#define MESHBLOCK_X_ADD_ONE		(MESHFIELD_X_BLOCK2 + 1)
#define MESHBLOCK_Z_ADD_ONE		(MESHFIELD_Z_BLOCK2 + 1)

// 1列頂点数
#define MESH_RHINE_VTX_ONE		(MESHFIELD_X_BLOCK2 * 2 + 2)

// メッシュフィールドの頂点数
#define MAX_MESHFIELD_VERTEX		(MESHBLOCK_X_ADD_ONE * MESHBLOCK_Z_ADD_ONE)		

// メッシュフィールドのポリゴン数
#define MAX_MESHFIELD_POLYGON		((MESHFIELD_X_BLOCK2 * MESHFIELD_Z_BLOCK2 * 2) + (((MESHFIELD_Z_BLOCK2 - 1) * 2) * 2))

// メッシュフィールドのインデックス数
#define MAX_MESHFIELD_INDEX			((MESH_RHINE_VTX_ONE * MESHFIELD_Z_BLOCK2) + ((MESHFIELD_Z_BLOCK2 - 1) * 2))	

// メッシュフィールドサイズ
#define MAX_MESHFIELD_SIZE			(150.0f)															

//***************************************************************************
// グローバル変数
//***************************************************************************
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffMeshField = NULL;		// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9			g_pTextureMeshField = NULL;		// テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9		g_pIdzBuffMeshField = NULL;		// インデックスバッファへのポインタ
MeshField					g_MeshField;					// メッシュフィールド情報の取得

//---------------------------------------------------------------------------
// メッシュフィールド初期化処理
//---------------------------------------------------------------------------
void InitMeshField(void)
{
	// ファイル変数の宣言と代入
	char aFile[128] = FILE_TEXTURE_DATA;
	strcat(aFile, "砂.jpg");

	// 初期位置設定
	g_MeshField.pos = D3DXVECTOR3(-(MAX_MESHFIELD_SIZE * MESHFIELD_X_BLOCK2) / 2, 
		0.0f, 
		(MAX_MESHFIELD_SIZE * MESHFIELD_Z_BLOCK2) / 2);

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// メッシュフィールドに張り付けるテクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, aFile, &g_pTextureMeshField);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_MESHFIELD_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_MESHFIELD_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdzBuffMeshField,
		NULL);

	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < MESHFIELD_Z_BLOCK2 + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESHFIELD_X_BLOCK2 + 1; nCntX++)
		{// 変数宣言
			int nCntVtx = nCntX + (nCntZ * (MESHFIELD_X_BLOCK2 + 1));

			// 頂点座標の設定
			pVtx[nCntVtx].pos.x = (nCntVtx % (MESHFIELD_X_BLOCK2 + 1) - 1) * MAX_MESHFIELD_SIZE;
			pVtx[nCntVtx].pos.y = 0.0f;
			pVtx[nCntVtx].pos.z = (nCntVtx / (MESHFIELD_X_BLOCK2 + 1) - 1) * -MAX_MESHFIELD_SIZE;

			// 各頂点の法線の設定(*ベクトルの大きさは1にする必要がある)
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 頂点カラーの設定
			pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[nCntVtx].tex = D3DXVECTOR2(1.0f * nCntX, 1.0f * nCntZ);
		}
	}

	// インデックスバッファをロック
	WORD *pIdx;
	g_pIdzBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	// インデックスの設定
	for (int nCntZ = 0; nCntZ < MESHFIELD_Z_BLOCK2; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESHBLOCK_X_ADD_ONE; nCntX++)
		{// インデックス数の設定
			pIdx[0] = MESHBLOCK_X_ADD_ONE + nCntX + nCntZ * MESHBLOCK_X_ADD_ONE;
			pIdx[1] = MESHBLOCK_X_ADD_ONE + nCntX + nCntZ * MESHBLOCK_X_ADD_ONE - MESHBLOCK_X_ADD_ONE;

			pIdx += 2;
		}

		if (nCntZ != MESHFIELD_Z_BLOCK2)
		{// 最大数以下の時
			// 縮退ポリゴンインデックス数の設定
			pIdx[0] = MESHBLOCK_X_ADD_ONE * nCntZ + MESHFIELD_X_BLOCK2;
			pIdx[1] = MESHBLOCK_X_ADD_ONE * (nCntZ + 2);

			pIdx += 2;
		}
	}

	// 頂点バッファのアンロック
	g_pVtxBuffMeshField->Unlock();

	// 頂点バッファのアンロック
	g_pIdzBuffMeshField->Unlock();
}

//---------------------------------------------------------------------------
// メッシュフィールド終了処理
//---------------------------------------------------------------------------
void UninitMeshField(void)
{
	// テクスチャの破棄	  
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	// インデックスバッファの破棄	  
	if (g_pIdzBuffMeshField != NULL)
	{
		g_pIdzBuffMeshField->Release();
		g_pIdzBuffMeshField = NULL;
	}
}

//---------------------------------------------------------------------------
// メッシュフィールド更新処理
//---------------------------------------------------------------------------
void UpdateMeshField(void)
{

}

//---------------------------------------------------------------------------
// メッシュフィールド描画処理
//---------------------------------------------------------------------------
void DrawMeshField(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// 計算用マトリックス

	// ワールドマトリックスの初期化
	// 行列初期化関数(第一引数の[行列]を[単位行列]に初期化)
	D3DXMatrixIdentity(&g_MeshField.mtxWorld);

	// 向きの反映
	// 行列回転関数 (第一引数に[ヨー(y)ピッチ(x)ロール(z)]方向の回転行列を作成)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshField.rot.y, g_MeshField.rot.x, g_MeshField.rot.z);

	// 行列掛け算関数 (第二引数 * 第三引数を第一引数に格納)
	D3DXMatrixMultiply(&g_MeshField.mtxWorld, &g_MeshField.mtxWorld, &mtxRot);

	// 位置を反映
	// 行列移動関数 (第一引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, g_MeshField.pos.x, g_MeshField.pos.y, g_MeshField.pos.z);
	D3DXMatrixMultiply(&g_MeshField.mtxWorld, &g_MeshField.mtxWorld, &mtxTrans);						// 行列掛け算関数

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshField.mtxWorld);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdzBuffMeshField);

	// 頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshField);

	// メッシュフィールド描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_MESHFIELD_VERTEX, 0, MAX_MESHFIELD_POLYGON);

	// テクスチャの解除
	pDevice->SetTexture(0, NULL);
}