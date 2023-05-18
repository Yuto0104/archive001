//**************************************************************************************************
//
// ライン描画処理(line.cpp)
// Auther：唐﨑結斗
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include "main.h"
#include "line.h"
#include "file.h"

//***************************************************************************
// マクロ定義
//***************************************************************************
#define MAX_LINE_VERTEX				(2)					// ラインの頂点数
#define MAX_LINE					(128)				// ラインの最大数
#define MAX_LINE_SIZE				(10.0f)				// ラインの大きさ

//***************************************************************************
// グローバル変数
//***************************************************************************
static LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffLine = NULL;			// 頂点バッファへのポインタ
static Line							g_Line[MAX_LINE];				// ライン情報の取得

//---------------------------------------------------------------------------
// ライン初期化処理
//---------------------------------------------------------------------------
void InitLine(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_LINE_VERTEX * MAX_LINE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLine,
		NULL);

	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		// ライン情報の初期化
		g_Line[nCntLine].pos = {};											// 位置
		g_Line[nCntLine].rot = {};											// 向き
		g_Line[nCntLine].start = {};										// 始点
		g_Line[nCntLine].goal = {};											// 終点
		g_Line[nCntLine].mtxWorld = {};										// ワールドマトリックス
		g_Line[nCntLine].fLength = 0.0f;									// 長さ
		g_Line[nCntLine].bUse = false;										// 使用状況

		// 頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_Line[nCntLine].start.x, g_Line[nCntLine].start.y, g_Line[nCntLine].start.z);
		pVtx[1].pos = D3DXVECTOR3(g_Line[nCntLine].goal.x, g_Line[nCntLine].goal.y, g_Line[nCntLine].goal.z);

		// 各頂点の法線の設定(*ベクトルの大きさは1にする必要がある)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 2;		//頂点データのポインタを4つ分進める
	}

	// 頂点バッファのアンロック
	g_pVtxBuffLine->Unlock();
}

//---------------------------------------------------------------------------
// ライン終了処理
//---------------------------------------------------------------------------
void UninitLine(void)
{
	// 頂点バッファの破棄
	if (g_pVtxBuffLine != NULL)
	{
		g_pVtxBuffLine->Release();
		g_pVtxBuffLine = NULL;
	}
}

//---------------------------------------------------------------------------
// ライン更新処理
//---------------------------------------------------------------------------
void UpdateLine(void)
{
	
}

//---------------------------------------------------------------------------
// ライン描画処理
//---------------------------------------------------------------------------
void DrawLine(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans,mtxView;		// 計算用マトリックス

	// テクスチャの設定
	pDevice->SetTexture(0, NULL);

	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		if (g_Line[nCntLine].bUse == true)
		{// ラインが使用されているとき
			// Zテストを使用する
			pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

			// Zテストの設定
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);

			// αテストを使用する
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

			// αテストの設定
			pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			// ライトを無効
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// ワールドマトリックスの初期化
			// 行列初期化関数(第一引数の[行列]を[単位行列]に初期化)
			D3DXMatrixIdentity(&g_Line[nCntLine].mtxWorld);
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// 向きの反映
			// 行列回転関数 (第一引数に[ヨー(y)ピッチ(x)ロール(z)]方向の回転行列を作成)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Line[nCntLine].rot.y, g_Line[nCntLine].rot.x, g_Line[nCntLine].rot.z);

			// 行列掛け算関数 (第二引数 * 第三引数を第一引数に格納)
			D3DXMatrixMultiply(&g_Line[nCntLine].mtxWorld, &g_Line[nCntLine].mtxWorld, &mtxRot);

			// 位置を反映
			// 行列移動関数 (第一引数にX,Y,Z方向の移動行列を作成)
			D3DXMatrixTranslation(&mtxTrans, g_Line[nCntLine].pos.x, g_Line[nCntLine].pos.y, g_Line[nCntLine].pos.z);
			D3DXMatrixMultiply(&g_Line[nCntLine].mtxWorld, &g_Line[nCntLine].mtxWorld, &mtxTrans);		// 行列掛け算関数

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Line[nCntLine].mtxWorld);

			// 頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffLine, 0, sizeof(VERTEX_3D));

			// 頂点フォーマット
			pDevice->SetFVF(FVF_VERTEX_3D);

			// ライン描画
			pDevice->DrawPrimitive(D3DPT_LINELIST, MAX_LINE_VERTEX * nCntLine, 1);

			// ライトを有効	
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// Zテストの終了
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

			// αテストの終了
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		}
	}

	// テクスチャの解除
	pDevice->SetTexture(0, NULL);
}

//---------------------------------------------------------------------------
// ライン設定処理
//---------------------------------------------------------------------------
int SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 start, D3DXVECTOR3 goal, D3DXCOLOR col)
{
	// 変数宣言
	int nCntLine = 0;

	//// 頂点情報の取得
	//VERTEX_3D *pVtx = NULL;

	//// 頂点バッファをロック
	//g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);

	//for (nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	//{
	//	if (g_Line[nCntLine].bUse == false)
	//	{
	//		// ライン情報の設定
	//		g_Line[nCntLine].pos = pos;								// 位置
	//		g_Line[nCntLine].rot = rot;								// 向き
	//		g_Line[nCntLine].start = start;							// 始点
	//		g_Line[nCntLine].goal = goal;							// 終点
	//		g_Line[nCntLine].mtxWorld = {};							// ワールドマトリックス
	//		g_Line[nCntLine].bUse = true;							// 使用状況

	//		// 頂点座標
	//		pVtx[0].pos = D3DXVECTOR3(g_Line[nCntLine].start.x, g_Line[nCntLine].start.y, g_Line[nCntLine].start.z);
	//		pVtx[1].pos = D3DXVECTOR3(g_Line[nCntLine].goal.x, g_Line[nCntLine].goal.y, g_Line[nCntLine].goal.z);

	//		// 頂点カラーの設定
	//		pVtx[0].col = col;
	//		pVtx[1].col = col;


	//		break;
	//	}

	//	pVtx += 2;		//頂点データのポインタを4つ分進める
	//}

	//// 頂点バッファのアンロック
	//g_pVtxBuffLine->Unlock();

	return nCntLine;
}

void MoveLine(int nCnt, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ライン情報の設定
	g_Line[nCnt].pos = pos;	// 位置
	g_Line[nCnt].rot = rot;	// 向き
}

void DeleteLine(int nCnt)
{
	g_Line[nCnt].bUse = false;
}
