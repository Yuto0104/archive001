//**************************************************************************************************
//
//酸素ゲージの設定処理
//Auther：唐﨑結斗
//
//**************************************************************************************************
#include"main.h"
#include"input.h"
#include"pause.h"
#include"fade.h"
#include"stamina_gauge.h"
#include"player.h"

//*******************************************************************************
// グローバル変数
//*******************************************************************************
//LPDIRECT3DTEXTURE9 g_pTextureStaminaGauge = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStaminaGauge = NULL;		//頂点バッファへのポインタ
StaminaGauge g_StaminaGauge[MAX_STAMINA_GAUGE];				// スタミナゲージ

//---------------------------------------------------------------------------
// スタミナゲージの初期化処理
//---------------------------------------------------------------------------
void InitStaminaGauge(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	////ポリゴンに張り付けるテクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,
	//	"data/TEXTURE/酸素ボンベ.png",
	//	&g_pTextureStaminaGauge);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_STAMINA_GAUGE,		// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,															// 頂点ファーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffStaminaGauge,
		NULL);

	for (int nCnt = 0; nCnt < MAX_STAMINA_GAUGE; nCnt++)
	{
		// スタミナゲージ情報の初期化
		g_StaminaGauge[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);												// 中心点
		g_StaminaGauge[nCnt].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);												// 大きさ
		g_StaminaGauge[nCnt].maxSize = g_StaminaGauge[nCnt].size;												// 大きさの最大値
		D3DXVECTOR3 sizePos = D3DXVECTOR3(g_StaminaGauge[nCnt].size.x, 0.0f, 0.0f);								// 半分側の大きさ
		g_StaminaGauge[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);												// 向き
		g_StaminaGauge[nCnt].type = TYPE_GAUGE;																	// タイプ
		g_StaminaGauge[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);											// カラー
		g_StaminaGauge[nCnt].bUse = false;																		// 使用してる

		// 頂点情報へのポインタを生成						
		VERTEX_2D *pVtx;

		// 頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffStaminaGauge->Lock(0, 0, (void**)&pVtx, 0);

		// 対角線の長さ[0]を算出する
		g_StaminaGauge[nCnt].fLength = sqrtf(((g_StaminaGauge[nCnt].size.x * g_StaminaGauge[nCnt].size.x) + (g_StaminaGauge[nCnt].size.y * g_StaminaGauge[nCnt].size.y)) / 2.0f);
		float fLengthPos = sqrtf(((sizePos.x * sizePos.x) + (sizePos.y * sizePos.y)) / 2.0f);

		// 対角線の角度[0]を算出
		g_StaminaGauge[nCnt].fAngele = atan2f(g_StaminaGauge[nCnt].size.x, g_StaminaGauge[nCnt].size.y);
		float fAngelePos = atan2f(sizePos.x, sizePos.y);

		// 頂点座標の設定
		pVtx[0].pos.x = g_StaminaGauge[nCnt].pos.x + sinf(g_StaminaGauge[nCnt].rot.z + (D3DX_PI + g_StaminaGauge[nCnt].fAngele)) * g_StaminaGauge[nCnt].fLength;
		pVtx[0].pos.y = g_StaminaGauge[nCnt].pos.y + cosf(g_StaminaGauge[nCnt].rot.z + (D3DX_PI + g_StaminaGauge[nCnt].fAngele)) * g_StaminaGauge[nCnt].fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_StaminaGauge[nCnt].pos.x + sinf(g_StaminaGauge[nCnt].rot.z + (D3DX_PI - g_StaminaGauge[nCnt].fAngele)) *  g_StaminaGauge[nCnt].fLength;
		pVtx[1].pos.y = g_StaminaGauge[nCnt].pos.y + cosf(g_StaminaGauge[nCnt].rot.z + (D3DX_PI - g_StaminaGauge[nCnt].fAngele)) *  g_StaminaGauge[nCnt].fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_StaminaGauge[nCnt].pos.x + sinf(g_StaminaGauge[nCnt].rot.z - (0 + fAngelePos)) * fLengthPos;
		pVtx[2].pos.y = g_StaminaGauge[nCnt].pos.y + cosf(g_StaminaGauge[nCnt].rot.z - (0 + fAngelePos)) * fLengthPos;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_StaminaGauge[nCnt].pos.x + sinf(g_StaminaGauge[nCnt].rot.z - (0 - fAngelePos)) * fLengthPos;
		pVtx[3].pos.y = g_StaminaGauge[nCnt].pos.y + cosf(g_StaminaGauge[nCnt].rot.z - (0 - fAngelePos)) * fLengthPos;
		pVtx[3].pos.z = 0.0f;

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = g_StaminaGauge[nCnt].col;
		pVtx[1].col = g_StaminaGauge[nCnt].col;
		pVtx[2].col = g_StaminaGauge[nCnt].col;
		pVtx[3].col = g_StaminaGauge[nCnt].col;

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// 頂点バッファをアンロック
	g_pVtxBuffStaminaGauge->Unlock();
}

//---------------------------------------------------------------------------
// スタミナゲージの終了処理
//---------------------------------------------------------------------------
void UninitStaminaGauge(void)
{
	//// テクスチャの破棄	  
	//if (g_pTextureStaminaGauge != NULL)
	//{
	//	g_pTextureStaminaGauge->Release();

	//	g_pTextureStaminaGauge = NULL;
	//}

	// 頂点バッファを破棄
	if (g_pVtxBuffStaminaGauge != NULL)
	{
		g_pVtxBuffStaminaGauge->Release();

		g_pVtxBuffStaminaGauge = NULL;
	}
}

//---------------------------------------------------------------------------
// スタミナゲージの更新処理
//---------------------------------------------------------------------------
void UpdateStaminaGauge(void)
{
	for (int nCnt = 0; nCnt < MAX_STAMINA_GAUGE; nCnt++)
	{
		if (g_StaminaGauge[nCnt].bUse)
		{
			SubStaminaGauge(nCnt);
		}
	}
}

//---------------------------------------------------------------------------
// スタミナゲージの描画処理
//---------------------------------------------------------------------------
void DrawStaminaGauge(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffStaminaGauge, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_STAMINA_GAUGE; nCnt++)
	{
		if (g_StaminaGauge[nCnt].bUse)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, NULL);

			// ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 
				nCnt * 4,
				2);
		}
	}
}

//---------------------------------------------------------------------------
// スタミナゲージの設定処理
//---------------------------------------------------------------------------
void SetStaminaGauge(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nType)
{
	for (int nCntType = 0; nCntType < MAX_STAMINA_GAUGE; nCntType++)
	{
		if (g_StaminaGauge[nCntType].bUse == false)
		{
			// スタミナゲージ情報の初期化
			g_StaminaGauge[nCntType].pos = pos;																			// 中心点
			g_StaminaGauge[nCntType].size = D3DXVECTOR3(size.x, size.y * 2.0f, size.z);									// 大きさ
			g_StaminaGauge[nCntType].maxSize = g_StaminaGauge[nCntType].size;											// 大きさの最大値
			g_StaminaGauge[nCntType].type = (STAMINA_GAUGE_TYPE)(nType);												// タイプ
			D3DXVECTOR3 sizePos = D3DXVECTOR3(g_StaminaGauge[nCntType].size.x, 0.0f, 0.0f);								// 半分側の大きさ
			g_StaminaGauge[nCntType].rot = rot;																			// 向き
			g_StaminaGauge[nCntType].bUse = true;																		// 使用してる

			switch (g_StaminaGauge[nCntType].type)
			{
			case TYPE_GAUGE:
				g_StaminaGauge[nCntType].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);					// カラー
				break;

			case TYPE_BG:
				g_StaminaGauge[nCntType].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);					// カラー
				break;
			}
			

			//頂点情報へのポインタを生成						
			VERTEX_2D *pVtx;

			// 頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffStaminaGauge->Lock(0, 0, (void**)&pVtx, 0);

			// 対角線の長さを算出する
			g_StaminaGauge[nCntType].fLength = sqrtf(((g_StaminaGauge[nCntType].size.x * g_StaminaGauge[nCntType].size.x) + (g_StaminaGauge[nCntType].size.y * g_StaminaGauge[nCntType].size.y)) / 2.0f);
			float fLengthPos = sqrtf(((sizePos.x * sizePos.x) + (sizePos.y * sizePos.y)) / 2.0f);

			// 対角線の角度を算出
			g_StaminaGauge[nCntType].fAngele = atan2f(g_StaminaGauge[nCntType].size.x, g_StaminaGauge[nCntType].size.y);
			float fAngelePos = atan2f(sizePos.x, sizePos.y);

			// 頂点座標の設定
			pVtx[0].pos.x = g_StaminaGauge[nCntType].pos.x + sinf(g_StaminaGauge[nCntType].rot.z + (D3DX_PI + g_StaminaGauge[nCntType].fAngele)) * g_StaminaGauge[nCntType].fLength;
			pVtx[0].pos.y = g_StaminaGauge[nCntType].pos.y + cosf(g_StaminaGauge[nCntType].rot.z + (D3DX_PI + g_StaminaGauge[nCntType].fAngele)) * g_StaminaGauge[nCntType].fLength;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_StaminaGauge[nCntType].pos.x + sinf(g_StaminaGauge[nCntType].rot.z + (D3DX_PI - g_StaminaGauge[nCntType].fAngele)) *  g_StaminaGauge[nCntType].fLength;
			pVtx[1].pos.y = g_StaminaGauge[nCntType].pos.y + cosf(g_StaminaGauge[nCntType].rot.z + (D3DX_PI - g_StaminaGauge[nCntType].fAngele)) *  g_StaminaGauge[nCntType].fLength;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_StaminaGauge[nCntType].pos.x + sinf(g_StaminaGauge[nCntType].rot.z - (0 + fAngelePos)) * fLengthPos;
			pVtx[2].pos.y = g_StaminaGauge[nCntType].pos.y + cosf(g_StaminaGauge[nCntType].rot.z - (0 + fAngelePos)) * fLengthPos;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_StaminaGauge[nCntType].pos.x + sinf(g_StaminaGauge[nCntType].rot.z - (0 - fAngelePos)) * fLengthPos;
			pVtx[3].pos.y = g_StaminaGauge[nCntType].pos.y + cosf(g_StaminaGauge[nCntType].rot.z - (0 - fAngelePos)) * fLengthPos;
			pVtx[3].pos.z = 0.0f;

			// rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			// 頂点カラーの設定
			pVtx[0].col = g_StaminaGauge[nCntType].col;
			pVtx[1].col = g_StaminaGauge[nCntType].col;
			pVtx[2].col = g_StaminaGauge[nCntType].col;
			pVtx[3].col = g_StaminaGauge[nCntType].col;

			// テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			// 頂点バッファをアンロック
			g_pVtxBuffStaminaGauge->Unlock();

			break;
		}
	}
}

//---------------------------------------------------------------------------
// スタミナゲージの減少処理
//---------------------------------------------------------------------------
void SubStaminaGauge(int nCnt)
{
	if (g_StaminaGauge[nCnt].bUse)
	{
		//プレイヤー情報の取得
		Player *pPlayer = GetPlayer();

		switch (g_StaminaGauge[nCnt].type)
		{
		case TYPE_GAUGE:
			// 大きさに数値を代入
			g_StaminaGauge[nCnt].size.y = (g_StaminaGauge[nCnt].maxSize.y / (float)(pPlayer->nMaxStamina)) * (float)(pPlayer->nStamina);

			if (pPlayer->nStamina <= pPlayer->nMaxStamina)
			{// スタミナが半分以下の時
				g_StaminaGauge[nCnt].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);			// カラー
				if (pPlayer->nStamina <= pPlayer->nMaxStamina / 2)
				{// スタミナが半分以下の時
					g_StaminaGauge[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);			// カラー

					if (pPlayer->nStamina <= DASH_STAMINA)
					{// スタミナがダッシュ消費量以下
						g_StaminaGauge[nCnt].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);			// カラー
					}
				}
			}
			break;

		case TYPE_BG:
			break;
		}

		// 半分側の大きさ
		D3DXVECTOR3 sizePos = D3DXVECTOR3(g_StaminaGauge[nCnt].size.x, 0.0f, 0.0f);

		//頂点情報へのポインタを生成						
		VERTEX_2D *pVtx;

		// 頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffStaminaGauge->Lock(0, 0, (void**)&pVtx, 0);

		// 対角線の長さを算出する
		g_StaminaGauge[nCnt].fLength = sqrtf(((g_StaminaGauge[nCnt].size.x * g_StaminaGauge[nCnt].size.x) + (g_StaminaGauge[nCnt].size.y * g_StaminaGauge[nCnt].size.y)) / 2.0f);
		float fLengthPos = sqrtf(((sizePos.x * sizePos.x) + (sizePos.y * sizePos.y)) / 2.0f);

		// 対角線の角度を算出
		g_StaminaGauge[nCnt].fAngele = atan2f(g_StaminaGauge[nCnt].size.x, g_StaminaGauge[nCnt].size.y);
		float fAngelePos = atan2f(sizePos.x, sizePos.y);

		// 頂点座標の設定
		pVtx[0].pos.x = g_StaminaGauge[nCnt].pos.x + sinf(g_StaminaGauge[nCnt].rot.z + (D3DX_PI + g_StaminaGauge[nCnt].fAngele)) * g_StaminaGauge[nCnt].fLength;
		pVtx[0].pos.y = g_StaminaGauge[nCnt].pos.y + cosf(g_StaminaGauge[nCnt].rot.z + (D3DX_PI + g_StaminaGauge[nCnt].fAngele)) * g_StaminaGauge[nCnt].fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_StaminaGauge[nCnt].pos.x + sinf(g_StaminaGauge[nCnt].rot.z + (D3DX_PI - g_StaminaGauge[nCnt].fAngele)) *  g_StaminaGauge[nCnt].fLength;
		pVtx[1].pos.y = g_StaminaGauge[nCnt].pos.y + cosf(g_StaminaGauge[nCnt].rot.z + (D3DX_PI - g_StaminaGauge[nCnt].fAngele)) *  g_StaminaGauge[nCnt].fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_StaminaGauge[nCnt].pos.x + sinf(g_StaminaGauge[nCnt].rot.z - (0 + fAngelePos)) * fLengthPos;
		pVtx[2].pos.y = g_StaminaGauge[nCnt].pos.y + cosf(g_StaminaGauge[nCnt].rot.z - (0 + fAngelePos)) * fLengthPos;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_StaminaGauge[nCnt].pos.x + sinf(g_StaminaGauge[nCnt].rot.z - (0 - fAngelePos)) * fLengthPos;
		pVtx[3].pos.y = g_StaminaGauge[nCnt].pos.y + cosf(g_StaminaGauge[nCnt].rot.z - (0 - fAngelePos)) * fLengthPos;
		pVtx[3].pos.z = 0.0f;

		// 頂点カラーの設定
		pVtx[0].col = g_StaminaGauge[nCnt].col;
		pVtx[1].col = g_StaminaGauge[nCnt].col;
		pVtx[2].col = g_StaminaGauge[nCnt].col;
		pVtx[3].col = g_StaminaGauge[nCnt].col;

		// 頂点バッファをアンロック
		g_pVtxBuffStaminaGauge->Unlock();
	}
}

//---------------------------------------------------------------------------
// スタミナゲージの情報取得
//---------------------------------------------------------------------------
StaminaGauge *GetStaminaGauge(void)
{
	return &g_StaminaGauge[0];
}