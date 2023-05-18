//**************************************************************************************************
//
// スカイボックス描画処理(skybox.cpp)
// Auther：唐﨑結斗
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include "main.h"
#include "skybox.h"
#include"file.h"

//***************************************************************************
// マクロ定義
//***************************************************************************
#define HEMISPHERE_X_BLOCK2				(10)						// X方向のブロック数
#define HEMISPHERE_Z_BLOCK2				(10)						// Z方向のブロック数

// ブロック数 + 1
#define MESHBLOCK_X_ADD_ONE			(HEMISPHERE_X_BLOCK2 + 1)
#define MESHBLOCK_Z_ADD_ONE			(HEMISPHERE_Z_BLOCK2 + 1)

// 1列頂点数
#define HEMISPHERE_RHINE_VTX_ONE		(HEMISPHERE_X_BLOCK2 * 2 + 2)

// 半球の頂点数
#define MAX_HEMISPHERE_VERTEX			(MESHBLOCK_X_ADD_ONE * MESHBLOCK_Z_ADD_ONE)		

// 半球のポリゴン数
#define MAX_HEMISPHERE_POLYGON			((HEMISPHERE_X_BLOCK2 * HEMISPHERE_Z_BLOCK2 * 2) + (((HEMISPHERE_Z_BLOCK2 - 1) * 2) * 2))

// 半球のインデックス数
#define MAX_HEMISPHERE_INDEX			((HEMISPHERE_RHINE_VTX_ONE * HEMISPHERE_Z_BLOCK2) + ((HEMISPHERE_Z_BLOCK2 - 1) * 2))

// スカイリブの頂点数
#define MAX_SKYLID_VERTEX				(MESHBLOCK_X_ADD_ONE + 1)

// スカイリブのポリゴン数
#define MAX_SKYLID_POLYGON				(HEMISPHERE_X_BLOCK2)

// スカイリブのインデックス数
#define MAX_SKYLID_INDEX				((HEMISPHERE_X_BLOCK2 * 2) + 1)

// スカイボックスサイズ
#define MAX_HEMISPHERE_SIZE				(10.0f)

// スカイボックスの半径の長さ
#define HEMISPHERE_RADIUS				(1000.0f)

//***************************************************************************
// グローバル変数
//***************************************************************************
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffSkybox = NULL;		// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9			g_pTextureSkybox = NULL;		// テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9		g_pIdzBuffSkybox = NULL;		// インデックスバッファへのポインタ
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffSkyLid = NULL;		// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9			g_pTextureSkyLid = NULL;		// スカイリブテクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9		g_pIdzBuffSkyLid = NULL;		// スカイリブインデックスバッファへのポインタ
SkyBox						g_Skybox;						// スカイリブスカイボックス情報の取得

//---------------------------------------------------------------------------
// スカイボックス初期化処理
//---------------------------------------------------------------------------
void InitSkyBox(void)
{
	// ファイル変数の宣言と代入
	char aFile[128] = FILE_TEXTURE_DATA;
	strcat(aFile, "海背景.png");

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// スカイボックスに張り付けるテクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, aFile, &g_pTextureSkybox);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_HEMISPHERE_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSkybox,
		NULL);

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_HEMISPHERE_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdzBuffSkybox,
		NULL);

	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffSkybox->Lock(0, 0, (void**)&pVtx, 0);

	// インデックスバッファをロック
	WORD *pIdx;
	g_pIdzBuffSkybox->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntV = 0; nCntV < HEMISPHERE_Z_BLOCK2 + 1; nCntV++)
	{
		for (int nCntH = 0; nCntH < HEMISPHERE_X_BLOCK2 + 1; nCntH++)
		{// 変数宣言
			float fRot = ((-D3DX_PI * 2.0f) / HEMISPHERE_X_BLOCK2) * nCntH;				// Y軸の角度の設定
			float fHalfRot = (D3DX_PI / HEMISPHERE_Z_BLOCK2) * nCntV;			// 半スカイボックスのZ軸の角度の半分

			// 高さと半径の設定
			D3DXVECTOR2 radius = D3DXVECTOR2(sinf(fHalfRot) * HEMISPHERE_RADIUS, cosf(fHalfRot) * HEMISPHERE_RADIUS);

			// 頂点座標の設定
			pVtx[0].pos.x = sinf(fRot) * radius.y;
			pVtx[0].pos.z = cosf(fRot) * radius.y;
			pVtx[0].pos.y = radius.x;

			// 各頂点の法線の設定(*ベクトルの大きさは1にする必要がある)
			pVtx[0].nor.x = pVtx[0].pos.x;
			pVtx[0].nor.z = pVtx[0].pos.z;
			pVtx[0].nor.y = 0.0f;
			D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);

			// 頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(1.0f / HEMISPHERE_X_BLOCK2 * (HEMISPHERE_X_BLOCK2 - nCntH),
				1.0f / HEMISPHERE_Z_BLOCK2 * (HEMISPHERE_Z_BLOCK2 - nCntV));

			// 頂点情報へのポインタを進める
			pVtx++;
		}
	}

	// インデックスの設定
	for (int nCntZ = 0; nCntZ < HEMISPHERE_Z_BLOCK2; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESHBLOCK_X_ADD_ONE; nCntX++)
		{// インデックス数の設定
			pIdx[0] = MESHBLOCK_X_ADD_ONE + nCntX + nCntZ * MESHBLOCK_X_ADD_ONE;
			pIdx[1] = MESHBLOCK_X_ADD_ONE + nCntX + nCntZ * MESHBLOCK_X_ADD_ONE - MESHBLOCK_X_ADD_ONE;

			pIdx += 2;
		}

		if (nCntZ != HEMISPHERE_Z_BLOCK2)
		{// 最大数以下の時
		 // 縮退ポリゴンインデックス数の設定
			pIdx[0] = MESHBLOCK_X_ADD_ONE * nCntZ + HEMISPHERE_X_BLOCK2;
			pIdx[1] = MESHBLOCK_X_ADD_ONE * (nCntZ + 2);

			pIdx += 2;
		}
	}

	// 頂点バッファのアンロック
	g_pVtxBuffSkybox->Unlock();

	// 頂点バッファのアンロック
	g_pIdzBuffSkybox->Unlock();

	/*InitSkyLid();*/
}

//---------------------------------------------------------------------------
// スカイボックス終了処理
//---------------------------------------------------------------------------
void UninitSkyBox(void)
{
	// テクスチャの破棄	  
	if (g_pTextureSkybox != NULL)
	{
		g_pTextureSkybox->Release();
		g_pTextureSkybox = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffSkybox != NULL)
	{
		g_pVtxBuffSkybox->Release();
		g_pVtxBuffSkybox = NULL;
	}

	// インデックスバッファの破棄	  
	if (g_pIdzBuffSkybox != NULL)
	{
		g_pIdzBuffSkybox->Release();
		g_pIdzBuffSkybox = NULL;
	}
}

//---------------------------------------------------------------------------
// スカイボックス更新処理
//---------------------------------------------------------------------------
void UpdateSkyBox(void)
{

}

//---------------------------------------------------------------------------
// スカイボックス描画処理
//---------------------------------------------------------------------------
void DrawSkyBox(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// 計算用マトリックス

	// ライトを無効
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ワールドマトリックスの初期化
	// 行列初期化関数(第一引数の[行列]を[単位行列]に初期化)
	D3DXMatrixIdentity(&g_Skybox.mtxWorld);

	// 向きの反映
	// 行列回転関数 (第一引数に[ヨー(y)ピッチ(x)ロール(z)]方向の回転行列を作成)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Skybox.rot.y, g_Skybox.rot.x, g_Skybox.rot.z);

	// 行列掛け算関数 (第二引数 * 第三引数を第一引数に格納)
	D3DXMatrixMultiply(&g_Skybox.mtxWorld, &g_Skybox.mtxWorld, &mtxRot);

	// 位置を反映
	// 行列移動関数 (第一引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, g_Skybox.pos.x, g_Skybox.pos.y, g_Skybox.pos.z);
	D3DXMatrixMultiply(&g_Skybox.mtxWorld, &g_Skybox.mtxWorld, &mtxTrans);						// 行列掛け算関数

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Skybox.mtxWorld);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSkybox, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdzBuffSkybox);

	// 頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureSkybox);

	// スカイボックス描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_HEMISPHERE_VERTEX, 0, MAX_HEMISPHERE_POLYGON);

	// テクスチャの解除
	pDevice->SetTexture(0, NULL);

	// ライトを有効	
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	/*DrawSkyLid();*/
}

//---------------------------------------------------------------------------
// スカイリブ初期化処理
//---------------------------------------------------------------------------
void InitSkyLid(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_HEMISPHERE_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSkyLid,
		NULL);

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_HEMISPHERE_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdzBuffSkyLid,
		NULL);

	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffSkyLid->Lock(0, 0, (void**)&pVtx, 0);

	// インデックスバッファをロック
	WORD *pIdx;
	g_pIdzBuffSkyLid->Lock(0, 0, (void**)&pIdx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, HEMISPHERE_RADIUS, 0.0f);

	// 各頂点の法線の設定(*ベクトルの大きさは1にする必要がある)
	pVtx[0].nor = pVtx[0].pos;
	D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 頂点情報へのポインタを進める
	pVtx++;

	for (int nCnt = 1; nCnt < MAX_SKYLID_VERTEX - 1; nCnt++)
	{
		// 変数宣言
		float fRot = ((-D3DX_PI * 2.0f) / HEMISPHERE_X_BLOCK2) * nCnt;				// Y軸の角度の設定

		// 頂点座標の設定
		pVtx[0].pos.x = sinf(fRot) * HEMISPHERE_RADIUS;
		pVtx[0].pos.z = cosf(fRot) * HEMISPHERE_RADIUS;
		pVtx[0].pos.y = HEMISPHERE_RADIUS;

		// 各頂点の法線の設定(*ベクトルの大きさは1にする必要がある)
		pVtx[0].nor = pVtx[0].pos;
		D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// 頂点情報へのポインタを進める
		pVtx++;
	}

	pIdx[0] = 0;
	pIdx++;

	// インデックスの設定
	for (int nCnt = 1; nCnt < MAX_SKYLID_INDEX - 1; nCnt += 3)
	{
		pIdx[0] = nCnt;
		pIdx[1] = nCnt + 1;
		pIdx[2] = 0;

		pIdx += 3;
	}

	// 頂点バッファのアンロック
	g_pVtxBuffSkyLid->Unlock();

	// 頂点バッファのアンロック
	g_pIdzBuffSkyLid->Unlock();
}

//---------------------------------------------------------------------------
// スカイリブ描画処理
//---------------------------------------------------------------------------
void DrawSkyLid(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// 計算用マトリックス

	// ライトを無効
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ワールドマトリックスの初期化
	// 行列初期化関数(第一引数の[行列]を[単位行列]に初期化)
	D3DXMatrixIdentity(&g_Skybox.mtxWorld);

	// 向きの反映
	// 行列回転関数 (第一引数に[ヨー(y)ピッチ(x)ロール(z)]方向の回転行列を作成)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Skybox.rot.y, g_Skybox.rot.x, g_Skybox.rot.z);

	// 行列掛け算関数 (第二引数 * 第三引数を第一引数に格納)
	D3DXMatrixMultiply(&g_Skybox.mtxWorld, &g_Skybox.mtxWorld, &mtxRot);

	// 位置を反映
	// 行列移動関数 (第一引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, g_Skybox.pos.x, g_Skybox.pos.y, g_Skybox.pos.z);
	D3DXMatrixMultiply(&g_Skybox.mtxWorld, &g_Skybox.mtxWorld, &mtxTrans);						// 行列掛け算関数

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Skybox.mtxWorld);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSkybox, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdzBuffSkybox);

	// 頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// スカイボックス描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN, 0, 0, MAX_SKYLID_VERTEX, 0, MAX_SKYLID_POLYGON);

	// テクスチャの解除
	pDevice->SetTexture(0, NULL);

	// ライトを有効	
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}