//**************************************************************************************************
//
// ビルボード描画処理(billboard.cpp)
// Auther：唐﨑結斗
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include "main.h"
#include "billboard.h"
#include"file.h"
#include"model.h"
#include"shadow.h"
#include"effect.h"
#include"wall.h"

//***************************************************************************
// マクロ定義
//***************************************************************************
#define MAX_BILLBOARD_VERTEX			(4)					// ビルボードの頂点数
#define MAX_BILLBOARD					(128)				// ビルボードの最大数
#define MAX_BILLBOARD_SIZE				(10.0f)				// ビルボードの大きさ

//***************************************************************************
// グローバル変数
//***************************************************************************
static LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffBillboard = NULL;			// 頂点バッファへのポインタ
static LPDIRECT3DTEXTURE9			g_pTextureBillboard = NULL;			// テクスチャへのポインタ
static Billboard					g_Billboard[MAX_BILLBOARD];			// ビルボード情報の取得

//---------------------------------------------------------------------------
// ビルボード初期化処理
//---------------------------------------------------------------------------
void InitBillboard(void)
{
	// ファイル変数の宣言と代入
	char aFile[128] = FILE_TEXTURE_DATA;
	strcat(aFile, "bullet000.png");

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_BILLBOARD_VERTEX * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	// ビルボードに張り付けるテクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, aFile, &g_pTextureBillboard);

	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		// ビルボード情報の初期化
		g_Billboard[nCntBillboard].pos = {};											// 位置
		g_Billboard[nCntBillboard].posOld = {};											// 過去位置
		g_Billboard[nCntBillboard].move = {};											// 移動量
		g_Billboard[nCntBillboard].rot = {};											// 向き
		g_Billboard[nCntBillboard].mtxWorld = {};										// ワールドマトリックス
		g_Billboard[nCntBillboard].fRadius = MAX_BILLBOARD_SIZE;						// 半径
		g_Billboard[nCntBillboard].bUse = false;										// 使用状況

		// 頂点座標
		pVtx[0].pos = D3DXVECTOR3(-g_Billboard[nCntBillboard].fRadius, g_Billboard[nCntBillboard].fRadius, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Billboard[nCntBillboard].fRadius, g_Billboard[nCntBillboard].fRadius, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_Billboard[nCntBillboard].fRadius, -g_Billboard[nCntBillboard].fRadius, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Billboard[nCntBillboard].fRadius, -g_Billboard[nCntBillboard].fRadius, 0.0f);

		// 各頂点の法線の設定(*ベクトルの大きさは1にする必要がある)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
	g_pVtxBuffBillboard->Unlock();
}

//---------------------------------------------------------------------------
// ビルボード終了処理
//---------------------------------------------------------------------------
void UninitBillboard(void)
{
	//テクスチャの破棄	  
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();

		g_pTextureBillboard = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//---------------------------------------------------------------------------
// ビルボード更新処理
//---------------------------------------------------------------------------
void UpdateBillboard(void)
{
	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_Billboard[nCntBillboard].bUse == true)
		{// ビルボードが使用されているとき
			// 過去位置の算出
			g_Billboard[nCntBillboard].posOld = g_Billboard[nCntBillboard].pos;

			// 位置の更新
			g_Billboard[nCntBillboard].pos -= g_Billboard[nCntBillboard].move;

			if (CollisionWallBillBoard(&g_Billboard[nCntBillboard].pos, &g_Billboard[nCntBillboard].posOld, nCntBillboard))
			{
				/*g_Billboard[nCntBillboard].bUse = false;
				DeleteShadow(g_Billboard[nCntBillboard].nIdx);*/

				// エフェクトの生成
				SetEffect(g_Billboard[nCntBillboard].pos,
					g_Billboard[nCntBillboard].rot,
					D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f),
					D3DCMP_ALWAYS,
					EFFECTTYPE_WALL,
					EFFECTALPHABLEND_ADDITIVE,
					g_Billboard[nCntBillboard].fRadius,
					0.0f,
					0.0f,
					60,
					1,
					false);
			}

			// 影の移動
			SetPositionShadow(g_Billboard[nCntBillboard].nIdx, g_Billboard[nCntBillboard].pos, g_Billboard[nCntBillboard].rot,D3DXVECTOR3(g_Billboard[nCntBillboard].fRadius, 0.0f, g_Billboard[nCntBillboard].fRadius));

			// モデルの移動判定
			//if (g_Billboard[nCntBillboard].pos.x > 190.0f
			//	|| g_Billboard[nCntBillboard].pos.x < -190.0f
			//	|| g_Billboard[nCntBillboard].pos.z > 190.0f
			//	|| g_Billboard[nCntBillboard].pos.z < -190.0f)
			//{
			//	g_Billboard[nCntBillboard].bUse = false;
			//	DeleteShadow(g_Billboard[nCntBillboard].nIdx);

			//	// エフェクトの生成
			//	SetEffect(g_Billboard[nCntBillboard].pos,
			//		g_Billboard[nCntBillboard].rot,
			//		D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f),
			//		D3DCMP_ALWAYS,
			//		EFFECTTYPE_WALL,
			//		g_Billboard[nCntBillboard].fRadius,
			//		0.0f,
			//		0.0f,
			//		60,
			//		1,
			//		false);
			//}

			// エフェクトの生成
			SetEffect(g_Billboard[nCntBillboard].pos,
				g_Billboard[nCntBillboard].rot,
				D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f),
				D3DCMP_ALWAYS,
				EFFECTTYPE_NORMAL,
				EFFECTALPHABLEND_ADDITIVE,
				g_Billboard[nCntBillboard].fRadius,
				0.0f,
				0.0f,
				60,
				0,
				false);
		}
	}
}

//---------------------------------------------------------------------------
// ビルボード描画処理
//---------------------------------------------------------------------------
void DrawBillboard(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans,mtxView;		// 計算用マトリックス

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBillboard);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_Billboard[nCntBillboard].bUse == true)
		{// ビルボードが使用されているとき
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
			D3DXMatrixIdentity(&g_Billboard[nCntBillboard].mtxWorld);
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// カメラ逆行列を設定
			g_Billboard[nCntBillboard].mtxWorld._11 = mtxView._11;
			g_Billboard[nCntBillboard].mtxWorld._12 = mtxView._21;
			g_Billboard[nCntBillboard].mtxWorld._13 = mtxView._31;
			g_Billboard[nCntBillboard].mtxWorld._21 = mtxView._12;
			g_Billboard[nCntBillboard].mtxWorld._22 = mtxView._22;
			g_Billboard[nCntBillboard].mtxWorld._23 = mtxView._32;
			g_Billboard[nCntBillboard].mtxWorld._31 = mtxView._13;
			g_Billboard[nCntBillboard].mtxWorld._32 = mtxView._23;
			g_Billboard[nCntBillboard].mtxWorld._33 = mtxView._33;

			// 位置を反映
			// 行列移動関数 (第一引数にX,Y,Z方向の移動行列を作成)
			D3DXMatrixTranslation(&mtxTrans, g_Billboard[nCntBillboard].pos.x, g_Billboard[nCntBillboard].pos.y, g_Billboard[nCntBillboard].pos.z);
			D3DXMatrixMultiply(&g_Billboard[nCntBillboard].mtxWorld, &g_Billboard[nCntBillboard].mtxWorld, &mtxTrans);		// 行列掛け算関数

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Billboard[nCntBillboard].mtxWorld);

			// 頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			// 頂点フォーマット
			pDevice->SetFVF(FVF_VERTEX_3D);

			// ビルボード描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, MAX_BILLBOARD_VERTEX * nCntBillboard, 2);

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
// ビルボード設定処理
//---------------------------------------------------------------------------
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSpeed)
{
	// 変数宣言
	int nCntBillboard;

	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_Billboard[nCntBillboard].bUse == false)
		{
			// ビルボード情報の設定
			g_Billboard[nCntBillboard].pos = pos;								// 位置
			g_Billboard[nCntBillboard].rot = rot;								// 向き
			g_Billboard[nCntBillboard].mtxWorld = {};							// ワールドマトリックス
			g_Billboard[nCntBillboard].fRadius = MAX_BILLBOARD_SIZE;			// 半径
			g_Billboard[nCntBillboard].bUse = true;								// 使用状況

			// 頂点座標
			pVtx[0].pos = D3DXVECTOR3(-g_Billboard[nCntBillboard].fRadius, g_Billboard[nCntBillboard].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Billboard[nCntBillboard].fRadius, g_Billboard[nCntBillboard].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_Billboard[nCntBillboard].fRadius, -g_Billboard[nCntBillboard].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Billboard[nCntBillboard].fRadius, -g_Billboard[nCntBillboard].fRadius, 0.0f);

			// 移動量
			g_Billboard[nCntBillboard].move.x = sinf(g_Billboard[nCntBillboard].rot.y) * fSpeed;
			g_Billboard[nCntBillboard].move.z = cosf(g_Billboard[nCntBillboard].rot.y) * fSpeed;
			g_Billboard[nCntBillboard].move.y = 0.0f;

			// 影の設定
			g_Billboard[nCntBillboard].nIdx = SetShadow(g_Billboard[nCntBillboard].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(g_Billboard[nCntBillboard].fRadius, 0.0f, g_Billboard[nCntBillboard].fRadius));

			break;
		}

		pVtx += 4;		//頂点データのポインタを4つ分進める
	}

	// 頂点バッファのアンロック
	g_pVtxBuffBillboard->Unlock();
}

//---------------------------------------------------------------------------
// ビルボード情報の取得
//---------------------------------------------------------------------------
Billboard *GetBillboard(void)
{
	return &g_Billboard[0];
}