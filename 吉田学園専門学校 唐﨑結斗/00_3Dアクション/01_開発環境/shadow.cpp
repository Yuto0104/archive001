//**************************************************************************************************
//
// 影描画処理(shadow.cpp)
// Auther：唐﨑結斗
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include "main.h"
#include "shadow.h"
#include"file.h"
#include"model.h"

//***************************************************************************
// マクロ定義
//***************************************************************************
#define MAX_SHADOW_VERTEX		(4)				// 影の頂点数
#define MAX_SHADOW				(12800)			// 影の最大数
#define MAX_SHADOW_SIZE			(10.0f)			// 影サイズ
#define ATTENUATION_SHADOW		(0.01f)			// 影の減衰係数

//***************************************************************************
// グローバル変数
//***************************************************************************
static LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffShadow = NULL;		// 頂点バッファへのポインタ
static LPDIRECT3DTEXTURE9			g_pTextureShadow = NULL;		// テクスチャへのポインタ
static Shadow						g_Shadow[MAX_SHADOW];			// 影情報の取得

//---------------------------------------------------------------------------
// 影初期化処理
//---------------------------------------------------------------------------
void InitShadow(void)
{
	// ファイル変数の宣言と代入
	char aFile[128] = FILE_TEXTURE_DATA;
	strcat(aFile, "shadow000.jpg");

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_SHADOW_VERTEX * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	// 影に張り付けるテクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, aFile, &g_pTextureShadow);

	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		// 影情報の初期化
		g_Shadow[nCntShadow].pos = {};						// 位置
		g_Shadow[nCntShadow].rot = {};						// 向き
		g_Shadow[nCntShadow].size = {};						// 半径
		g_Shadow[nCntShadow].mtxWorld = {};					// ワールドマトリックス
		g_Shadow[nCntShadow].bUse = false;					// 使用状況

		// 頂点座標
		pVtx[0].pos = D3DXVECTOR3(-g_Shadow[nCntShadow].size.x, 0.0f, g_Shadow[nCntShadow].size.z);
		pVtx[1].pos = D3DXVECTOR3(g_Shadow[nCntShadow].size.x, 0.0f, g_Shadow[nCntShadow].size.z);
		pVtx[2].pos = D3DXVECTOR3(-g_Shadow[nCntShadow].size.x, 0.0f, -g_Shadow[nCntShadow].size.z);
		pVtx[3].pos = D3DXVECTOR3(g_Shadow[nCntShadow].size.x, 0.0f, -g_Shadow[nCntShadow].size.z);

		// 各頂点の法線の設定(*ベクトルの大きさは1にする必要がある)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		//頂点データのポインタを4つ分進める
	}

	// 頂点バッファのアンロック
	g_pVtxBuffShadow->Unlock();
}

//---------------------------------------------------------------------------
// 影終了処理
//---------------------------------------------------------------------------
void UninitShadow(void)
{
	//テクスチャの破棄	  
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();

		g_pTextureShadow = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//---------------------------------------------------------------------------
// 影更新処理
//---------------------------------------------------------------------------
void UpdateShadow(void)
{

}

//---------------------------------------------------------------------------
// 影描画処理
//---------------------------------------------------------------------------
void DrawShadow(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// 計算用マトリックス

	// αブレンディングを減算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureShadow);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == true)
		{// 影が使用されているとき
			// ワールドマトリックスの初期化
			// 行列初期化関数(第一引数の[行列]を[単位行列]に初期化)
			D3DXMatrixIdentity(&g_Shadow[nCntShadow].mtxWorld);

			// 向きの反映
			// 行列回転関数 (第一引数に[ヨー(y)ピッチ(x)ロール(z)]方向の回転行列を作成)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow[nCntShadow].rot.y, g_Shadow[nCntShadow].rot.x, g_Shadow[nCntShadow].rot.z);

			// 行列掛け算関数 (第二引数 * 第三引数を第一引数に格納)
			D3DXMatrixMultiply(&g_Shadow[nCntShadow].mtxWorld, &g_Shadow[nCntShadow].mtxWorld, &mtxRot);

			// 位置を反映
			// 行列移動関数 (第一引数にX,Y,Z方向の移動行列を作成)
			D3DXMatrixTranslation(&mtxTrans, g_Shadow[nCntShadow].pos.x, g_Shadow[nCntShadow].pos.y, g_Shadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_Shadow[nCntShadow].mtxWorld, &g_Shadow[nCntShadow].mtxWorld, &mtxTrans);		// 行列掛け算関数

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Shadow[nCntShadow].mtxWorld);

			// 頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			// 頂点フォーマット
			pDevice->SetFVF(FVF_VERTEX_3D);

			// 影描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, MAX_SHADOW_VERTEX * nCntShadow, 2);
		}
	}

	// テクスチャの解除
	pDevice->SetTexture(0, NULL);

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//---------------------------------------------------------------------------
// 影設定処理
//---------------------------------------------------------------------------
int	SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// 変数宣言
	int nCntShadow;

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == false)
		{
			// 変数宣言
			float fDiffPos = pos.y * 0.01f;

			// 影情報の設定
			g_Shadow[nCntShadow].pos.x = pos.x;																			// 位置(x)
			g_Shadow[nCntShadow].pos.y = 0.1f;																			// 位置(y)
			g_Shadow[nCntShadow].pos.z = pos.z;																			// 位置(z)
			g_Shadow[nCntShadow].rot = rot;																				// 向き
			g_Shadow[nCntShadow].mtxWorld = {};																			// ワールドマトリックス
			g_Shadow[nCntShadow].size = D3DXVECTOR3(size.x + (size.x * fDiffPos),0.0f, size.z + (size.z * fDiffPos));	// 大きさ						// 半径
			g_Shadow[nCntShadow].bUse = true;																			// 使用状況

			break;
		}
	}

	return nCntShadow;		// 影の番号(index)を返す
}

//---------------------------------------------------------------------------
// 影移動処理
//---------------------------------------------------------------------------
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// 変数宣言
	float fDiffPos = pos.y * ATTENUATION_SHADOW;
	float fAlpha = pos.y * ATTENUATION_SHADOW;

	// 影情報の設定
	g_Shadow[nIdxShadow].pos.x = pos.x;																			// 位置(x)
	g_Shadow[nIdxShadow].pos.y = 0.1f;																			// 位置(y)
	g_Shadow[nIdxShadow].pos.z = pos.z;																			// 位置(z)
	g_Shadow[nIdxShadow].rot.x = 0.0f;																			// 向き(x)
	g_Shadow[nIdxShadow].rot.y = rot.y;																			// 向き(y)
	g_Shadow[nIdxShadow].rot.z = 0.0f;																			// 向き(z)
	g_Shadow[nIdxShadow].size = D3DXVECTOR3(size.x + (size.x * fDiffPos), 0.0f, size.z + (size.z * fDiffPos));	// 大きさ	

	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdxShadow * 4;		//頂点データのポインタを4つ分進める

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(-g_Shadow[nIdxShadow].size.x, 0.0f, g_Shadow[nIdxShadow].size.z);
	pVtx[1].pos = D3DXVECTOR3(g_Shadow[nIdxShadow].size.x, 0.0f, g_Shadow[nIdxShadow].size.z);
	pVtx[2].pos = D3DXVECTOR3(-g_Shadow[nIdxShadow].size.x, 0.0f, -g_Shadow[nIdxShadow].size.z);
	pVtx[3].pos = D3DXVECTOR3(g_Shadow[nIdxShadow].size.x, 0.0f, -g_Shadow[nIdxShadow].size.z);

	// 各頂点の法線の設定(*ベクトルの大きさは1にする必要がある)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (1.0f * fAlpha));
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (1.0f * fAlpha));
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (1.0f * fAlpha));
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (1.0f * fAlpha));

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファのアンロック
	g_pVtxBuffShadow->Unlock();
}

//---------------------------------------------------------------------------
// 影削除処理
//---------------------------------------------------------------------------
void DeleteShadow(int nIdxShadow)
{
	// 影情報の初期化
	g_Shadow[nIdxShadow].pos = {};						// 位置
	g_Shadow[nIdxShadow].rot = {};						// 向き
	g_Shadow[nIdxShadow].size = {};						// 半径
	g_Shadow[nIdxShadow].mtxWorld = {};					// ワールドマトリックス
	g_Shadow[nIdxShadow].bUse = false;					// 使用状況
}