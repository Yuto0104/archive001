//**************************************************************************************************
//
// ポリゴン描画処理(polygon.cpp)
// Auther：唐﨑結斗
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include "main.h"
#include "polygon.h"
#include"file.h"

//***************************************************************************
// マクロ定義
//***************************************************************************
#define MAX_POLYGON_VERTEX		(4)				// ポリゴンの頂点数
#define MAX_POLYGON_SIZE		(200.0f)		// ポリゴンサイズ

//***************************************************************************
// グローバル変数
//***************************************************************************
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffPolygon = NULL;		// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9			g_pTexturePolygon = NULL;		// テクスチャへのポインタ
POLYGON						g_polygon;						// ポリゴン情報の取得

//---------------------------------------------------------------------------
// ポリゴン初期化処理
//---------------------------------------------------------------------------
void InitPolygon(void)
{
	// ファイル変数の宣言と代入
	char aFile[128] = FILE_TEXTURE_DATA;
	strcat(aFile, "field000.jpg");

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_POLYGON_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	// ポリゴンに張り付けるテクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, aFile, &g_pTexturePolygon);

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(-MAX_POLYGON_SIZE, 0.0f, MAX_POLYGON_SIZE);
	pVtx[1].pos = D3DXVECTOR3(MAX_POLYGON_SIZE, 0.0f, MAX_POLYGON_SIZE);
	pVtx[2].pos = D3DXVECTOR3(-MAX_POLYGON_SIZE, 0.0f, -MAX_POLYGON_SIZE);
	pVtx[3].pos = D3DXVECTOR3(MAX_POLYGON_SIZE, 0.0f, -MAX_POLYGON_SIZE);

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

	// 頂点バッファのアンロック
	g_pVtxBuffPolygon->Unlock();
}

//---------------------------------------------------------------------------
// ポリゴン終了処理
//---------------------------------------------------------------------------
void UninitPolygon(void)
{
	//テクスチャの破棄	  
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon->Release();

		g_pTexturePolygon = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}

//---------------------------------------------------------------------------
// ポリゴン更新処理
//---------------------------------------------------------------------------
void UpdatePolygon(void)
{

}

//---------------------------------------------------------------------------
// ポリゴン描画処理
//---------------------------------------------------------------------------
void DrawPolygon(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// 計算用マトリックス

	// ワールドマトリックスの初期化
	// 行列初期化関数(第一引数の[行列]を[単位行列]に初期化)
	D3DXMatrixIdentity(&g_polygon.mtxWorld);

	// 向きの反映
	// 行列回転関数 (第一引数に[ヨー(y)ピッチ(x)ロール(z)]方向の回転行列を作成)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_polygon.rot.y, g_polygon.rot.x, g_polygon.rot.z);

	// 行列掛け算関数 (第二引数 * 第三引数を第一引数に格納)
	D3DXMatrixMultiply(&g_polygon.mtxWorld, &g_polygon.mtxWorld, &mtxRot);

	// 位置を反映
	// 行列移動関数 (第一引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, g_polygon.pos.x, g_polygon.pos.y, g_polygon.pos.z);
	D3DXMatrixMultiply(&g_polygon.mtxWorld, &g_polygon.mtxWorld, &mtxTrans);						// 行列掛け算関数

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_polygon.mtxWorld);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	// 頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePolygon);

	// ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// テクスチャの解除
	pDevice->SetTexture(0, NULL);
}