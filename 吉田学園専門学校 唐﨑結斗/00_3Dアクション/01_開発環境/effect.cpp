//**************************************************************************************************
//
// エフェクト描画処理(effect.cpp)
// Auther：唐﨑結斗
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include "main.h"
#include "effect.h"
#include"file.h"
#include"model.h"
#include"shadow.h"

//***************************************************************************
// マクロ定義
//***************************************************************************
#define MAX_EFFECT_VERTEX		(4)				// エフェクトの頂点数
#define MAX_EFFECT				(12800)			// エフェクトの最大数

//***************************************************************************
// グローバル変数
//***************************************************************************
static LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffEffect = NULL;						// 頂点バッファへのポインタ
static LPDIRECT3DTEXTURE9			g_pTextureEffect[MAX_EFFECTTEXTURE] = {};		// テクスチャへのポインタ
static Effect						g_Effect[MAX_EFFECT];							// エフェクト情報の取得

//---------------------------------------------------------------------------
// エフェクト初期化処理
//---------------------------------------------------------------------------
void InitEffect(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ファイル変数の宣言と代入
	char aFile[MAX_EFFECTTEXTURE][128];
	memset(&aFile[0][0], 0, sizeof(aFile));
	
	for (int i = 0; i < MAX_EFFECTTEXTURE; i++)
	{// 相対パスの取得
		strcpy(&aFile[i][0], FILE_TEXTURE_DATA);
	}
	
	// テクスチャの割り振り
	strcat(&aFile[(int)(EFFECTTEXTURE_000)][0], "effect/Particle01.png");
	strcat(&aFile[(int)(EFFECTTEXTURE_001)][0], "effect/Shock_wave003.png");
	strcat(&aFile[(int)(EFFECTTEXTURE_002)][0], "effect/Particle02.png");
	strcat(&aFile[(int)(EFFECTTEXTURE_003)][0], "effect/樹枝六花.jpg");
	strcat(&aFile[(int)(EFFECTTEXTURE_004)][0], "effect/幅広六花.jpg");
	strcat(&aFile[(int)(EFFECTTEXTURE_005)][0], "effect/泡.jpg");

	for (int nCnt = 0; nCnt < MAX_EFFECTTEXTURE; nCnt++)
	{
		// エフェクトに張り付けるテクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, &aFile[(EFFECTTEXTURE)(nCnt)][0], &g_pTextureEffect[(EFFECTTEXTURE)(nCnt)]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_EFFECT_VERTEX * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		// エフェクト情報の初期化
		g_Effect[nCntEffect].pos = {};											// 位置
		g_Effect[nCntEffect].rot = {};											// 向き
		g_Effect[nCntEffect].move = {};											// 移動量
		g_Effect[nCntEffect].mtxWorld = {};										// ワールドマトリックス
		g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			// カラー
		g_Effect[nCntEffect].zFuncType = D3DCMP_LESS;							// Zバッファの比較タイプ
		g_Effect[nCntEffect].EffectType = EFFECTTYPE_NORMAL;					// エフェクトタイプ
		g_Effect[nCntEffect].EffectTexture = EFFECTTEXTURE_000;					// テクスチャタイプ
		g_Effect[nCntEffect].EffectAlphaBlend = EFFECTALPHABLEND_ADDITIVE;		// αブレンド
		g_Effect[nCntEffect].fRadius = 0.0f;									// 半径
		g_Effect[nCntEffect].fSpeed = 0.0f;										// 移動速度
		g_Effect[nCntEffect].fGravity = 0.0f;									// 重力
		g_Effect[nCntEffect].nIdx = 0;											// インデックス
		g_Effect[nCntEffect].nLife = 0;											// 寿命
		g_Effect[nCntEffect].bShadow = false;									// 影の使用状況
		g_Effect[nCntEffect].bUse = false;										// 使用状況

		// 減衰量の計算
		g_Effect[nCntEffect].fAttenuationRadius = g_Effect[nCntEffect].fRadius / (float)(g_Effect[nCntEffect].nLife);	// 半径
		g_Effect[nCntEffect].fAttenuationAlpha = g_Effect[nCntEffect].col.a / (float)(g_Effect[nCntEffect].nLife);		// α値

		// 頂点座標
		pVtx[0].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);

		// 各頂点の法線の設定(*ベクトルの大きさは1にする必要がある)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 頂点カラーの設定
		pVtx[0].col = g_Effect[nCntEffect].col;
		pVtx[1].col = g_Effect[nCntEffect].col;
		pVtx[2].col = g_Effect[nCntEffect].col;
		pVtx[3].col = g_Effect[nCntEffect].col;

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		//頂点データのポインタを4つ分進める
	}

	// 頂点バッファのアンロック
	g_pVtxBuffEffect->Unlock();
}

//---------------------------------------------------------------------------
// エフェクト終了処理
//---------------------------------------------------------------------------
void UninitEffect(void)
{
	for (int nCnt = 0; nCnt < MAX_EFFECTTEXTURE; nCnt++)
	{
		//テクスチャの破棄	  
		if (g_pTextureEffect[nCnt] != NULL)
		{
			g_pTextureEffect[nCnt]->Release();

			g_pTextureEffect[nCnt] = NULL;
		}
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//---------------------------------------------------------------------------
// エフェクト更新処理
//---------------------------------------------------------------------------
void UpdateEffect(void)
{
	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == true)
		{// 使用されている
			// 位置の更新
			g_Effect[nCntEffect].pos += g_Effect[nCntEffect].move;

			// 重力の付与
			g_Effect[nCntEffect].pos.y -= g_Effect[nCntEffect].fGravity;

			// 寿命の減衰
			g_Effect[nCntEffect].nLife--;

			if (g_Effect[nCntEffect].nLife == 0)
			{// 寿命がなくなった時
				g_Effect[nCntEffect].bUse = false;

				if (g_Effect[nCntEffect].bShadow == true)
				{// 影を使用する
					DeleteShadow(g_Effect[nCntEffect].nIdx);
				}
			}

			if (g_Effect[nCntEffect].bShadow == true)
			{// 影を使用する
				// 影の移動
				SetPositionShadow(g_Effect[nCntEffect].nIdx, g_Effect[nCntEffect].pos, g_Effect[nCntEffect].rot,D3DXVECTOR3(g_Effect[nCntEffect].fRadius,0.0f, g_Effect[nCntEffect].fRadius));
			}

			switch (g_Effect[nCntEffect].EffectType)
			{
			case EFFECTTYPE_NORMAL:		// 通常エフェクト
				// サイズの減衰
				g_Effect[nCntEffect].fRadius -= g_Effect[nCntEffect].fAttenuationRadius;

				// α値の減衰
				g_Effect[nCntEffect].col.a -= g_Effect[nCntEffect].fAttenuationAlpha;

				// 頂点座標
				pVtx[0].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
				break;

			case EFFECTTYPE_WALL:		// 壁エフェクト
				// サイズの減衰
				g_Effect[nCntEffect].fRadius += g_Effect[nCntEffect].fAttenuationRadius;

				// α値の減衰
				g_Effect[nCntEffect].col.a -= g_Effect[nCntEffect].fAttenuationAlpha;

				// 頂点座標
				pVtx[0].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
				break;

			case EFFECTTYPE_FIELD:		// 地面エフェクト
				// サイズの減衰
				g_Effect[nCntEffect].fRadius += g_Effect[nCntEffect].fAttenuationRadius;

				// α値の減衰
				g_Effect[nCntEffect].col.a -= g_Effect[nCntEffect].fAttenuationAlpha;

				// 向きの加算
				g_Effect[nCntEffect].rot.y += 0.1f;

				// 頂点座標
				pVtx[0].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, 0.0f, g_Effect[nCntEffect].fRadius);
				pVtx[1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, 0.0f, g_Effect[nCntEffect].fRadius);
				pVtx[2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, 0.0f, -g_Effect[nCntEffect].fRadius);
				pVtx[3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, 0.0f, -g_Effect[nCntEffect].fRadius);
				break;
			}

			// 頂点カラーの設定
			pVtx[0].col = g_Effect[nCntEffect].col;
			pVtx[1].col = g_Effect[nCntEffect].col;
			pVtx[2].col = g_Effect[nCntEffect].col;
			pVtx[3].col = g_Effect[nCntEffect].col;
		}

		pVtx += 4;		//頂点データのポインタを4つ分進める
	}

	// 頂点バッファのアンロック
	g_pVtxBuffEffect->Unlock();
}

//---------------------------------------------------------------------------
// エフェクト描画処理
//---------------------------------------------------------------------------
void DrawEffect(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans, mtxView;			// 計算用マトリックス

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == true)
		{// エフェクトが使用されているとき
			
			switch (g_Effect[nCntEffect].EffectAlphaBlend)
			{// αブレンドの設定
			case EFFECTALPHABLEND_ADDITIVE:
				// αブレンディングを加算合成に設定
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
				break;

			case EFFECTALPHABLEND_SUBTRACTIVE:
				// αブレンディングを減算合成に設定
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
				break;
			}

			// ワールドマトリックスの初期化
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEffect[(int)(g_Effect[nCntEffect].EffectTexture)]);

			// Zテストを使用する
			pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

			// Zテストの設定
			pDevice->SetRenderState(D3DRS_ZFUNC, g_Effect[nCntEffect].zFuncType);

			// αテストを使用する
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

			// αテストの設定
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			// ライトを無効
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// ワールドマトリックスの初期化
			// 行列初期化関数(第一引数の[行列]を[単位行列]に初期化)
			D3DXMatrixIdentity(&g_Effect[nCntEffect].mtxWorld);

			switch (g_Effect[nCntEffect].EffectType)
			{
			case EFFECTTYPE_NORMAL:		// 通常エフェクト
				pDevice->GetTransform(D3DTS_VIEW, &mtxView);

				// カメラ逆行列を設定
				g_Effect[nCntEffect].mtxWorld._11 = mtxView._11;
				g_Effect[nCntEffect].mtxWorld._12 = mtxView._21;
				g_Effect[nCntEffect].mtxWorld._13 = mtxView._31;
				g_Effect[nCntEffect].mtxWorld._21 = mtxView._12;
				g_Effect[nCntEffect].mtxWorld._22 = mtxView._22;
				g_Effect[nCntEffect].mtxWorld._23 = mtxView._32;
				g_Effect[nCntEffect].mtxWorld._31 = mtxView._13;
				g_Effect[nCntEffect].mtxWorld._32 = mtxView._23;
				g_Effect[nCntEffect].mtxWorld._33 = mtxView._33;
				break;

			case EFFECTTYPE_WALL:		// 壁エフェクト
				pDevice->GetTransform(D3DTS_VIEW, &mtxView);

				// カメラ逆行列を設定
				g_Effect[nCntEffect].mtxWorld._11 = mtxView._11;
				g_Effect[nCntEffect].mtxWorld._13 = mtxView._31;
				g_Effect[nCntEffect].mtxWorld._31 = mtxView._13;
				g_Effect[nCntEffect].mtxWorld._33 = mtxView._33;
				break;

			case EFFECTTYPE_FIELD:		// 地面エフェクト
				// 向きの反映
				// 行列回転関数 (第一引数に[ヨー(y)ピッチ(x)ロール(z)]方向の回転行列を作成)
				D3DXMatrixRotationYawPitchRoll(&mtxRot,
					g_Effect[nCntEffect].rot.y,
					g_Effect[nCntEffect].rot.x,
					g_Effect[nCntEffect].rot.z);

				// 行列掛け算関数 (第二引数 * 第三引数を第一引数に格納)
				D3DXMatrixMultiply(&g_Effect[nCntEffect].mtxWorld, &g_Effect[nCntEffect].mtxWorld, &mtxRot);
				break;
			}		

			// 位置を反映
			// 行列移動関数 (第一引数にX,Y,Z方向の移動行列を作成)
			D3DXMatrixTranslation(&mtxTrans, g_Effect[nCntEffect].pos.x, g_Effect[nCntEffect].pos.y, g_Effect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_Effect[nCntEffect].mtxWorld, &g_Effect[nCntEffect].mtxWorld, &mtxTrans);		// 行列掛け算関数

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Effect[nCntEffect].mtxWorld);

			// 頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// 頂点フォーマット
			pDevice->SetFVF(FVF_VERTEX_3D);

			// エフェクト描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, MAX_EFFECT_VERTEX * nCntEffect, 2);

			// ライトを有効	
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// Zテストの終了
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

			// αテストの終了
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

			// テクスチャの解除
			pDevice->SetTexture(0, NULL);

			// αブレンディングを元に戻す
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
	}
}

//---------------------------------------------------------------------------
// エフェクト設定処理
//---------------------------------------------------------------------------
void SetEffect(D3DXVECTOR3 pos,
	D3DXVECTOR3 rot,
	D3DXCOLOR col,
	D3DCMPFUNC zFuncType,
	EFFECTTYPE EffectType,
	EFFECTALPHABLEND EffectAlphaBlend,
	float fRadius,
	float fSpeed,
	float fGravity,
	int nLife,
	int nTexture,
	bool bShadow)
{
	// 変数宣言
	int nCntEffect;

	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == false)
		{// 使用されていない
			// エフェクト情報の初期化
			g_Effect[nCntEffect].pos = pos;										// 位置
			g_Effect[nCntEffect].rot = rot;										// 向き
			g_Effect[nCntEffect].mtxWorld = {};									// ワールドマトリックス
			g_Effect[nCntEffect].col = col;										// カラー
			g_Effect[nCntEffect].zFuncType = zFuncType;							// Zバッファの比較タイプ
			g_Effect[nCntEffect].EffectType = EffectType;						// エフェクトタイプ
			g_Effect[nCntEffect].EffectTexture = (EFFECTTEXTURE)(nTexture);		// テクスチャタイプ
			g_Effect[nCntEffect].EffectAlphaBlend = EffectAlphaBlend;			// αブレンド
			g_Effect[nCntEffect].fRadius = fRadius;								// 半径
			g_Effect[nCntEffect].fSpeed = fSpeed;								// 移動速度
			g_Effect[nCntEffect].fGravity = fGravity;							// 重力
			g_Effect[nCntEffect].nLife = nLife;									// 寿命
			g_Effect[nCntEffect].bShadow = bShadow;								// 影の使用状況
			g_Effect[nCntEffect].bUse = true;									// 使用状況

			// 減衰量の計算
			g_Effect[nCntEffect].fAttenuationRadius = g_Effect[nCntEffect].fRadius / (float)(g_Effect[nCntEffect].nLife);	// 半径
			g_Effect[nCntEffect].fAttenuationAlpha = g_Effect[nCntEffect].col.a / (float)(g_Effect[nCntEffect].nLife);		// α値

			// 移動量の算出
			g_Effect[nCntEffect].move.z = sinf(g_Effect[nCntEffect].rot.x) * cosf(g_Effect[nCntEffect].rot.y) * g_Effect[nCntEffect].fSpeed;
			g_Effect[nCntEffect].move.x = sinf(g_Effect[nCntEffect].rot.x) * sinf(g_Effect[nCntEffect].rot.y) * g_Effect[nCntEffect].fSpeed;
			g_Effect[nCntEffect].move.y = cosf(g_Effect[nCntEffect].rot.x) * g_Effect[nCntEffect].fSpeed;

			switch (g_Effect[nCntEffect].EffectType)
			{
			case EFFECTTYPE_NORMAL:		// 通常エフェクト
			case EFFECTTYPE_WALL:		// 壁エフェクト
				// 頂点座標
				pVtx[0].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);

				break;

			case EFFECTTYPE_FIELD:		// 地面エフェクト
				// エフェクト情報の初期化
				g_Effect[nCntEffect].pos.y = 0.5f;													// 位置
				g_Effect[nCntEffect].rot = rot;														// 向き
				g_Effect[nCntEffect].fAttenuationRadius = g_Effect[nCntEffect].fRadius / 10.0f;		// 半径の減衰量

				// 頂点座標
				pVtx[0].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, 0.0f, g_Effect[nCntEffect].fRadius);
				pVtx[1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, 0.0f, g_Effect[nCntEffect].fRadius);
				pVtx[2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, 0.0f, -g_Effect[nCntEffect].fRadius);
				pVtx[3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, 0.0f, -g_Effect[nCntEffect].fRadius);
				break;
			}

			if (g_Effect[nCntEffect].bShadow == true)
			{// 影を使用する
				// 影の設定
				g_Effect[nCntEffect].nIdx = SetShadow(g_Effect[nCntEffect].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(g_Effect[nCntEffect].fRadius, 0.0f, g_Effect[nCntEffect].fRadius));
			}

			// 各頂点の法線の設定(*ベクトルの大きさは1にする必要がある)
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 頂点カラーの設定
			pVtx[0].col = g_Effect[nCntEffect].col;
			pVtx[1].col = g_Effect[nCntEffect].col;
			pVtx[2].col = g_Effect[nCntEffect].col;
			pVtx[3].col = g_Effect[nCntEffect].col;

			// テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}

		pVtx += 4;		//頂点データのポインタを4つ分進める
	}

	// 頂点バッファのアンロック
	g_pVtxBuffEffect->Unlock();
}