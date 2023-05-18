//**************************************************************************************************
//
// プレスエンターの設定処理
// Auther：唐﨑結斗
//
//**************************************************************************************************
#include"main.h"
#include"press enter.h"
#include"input.h"
#include"fade.h"
#include"sound.h"
#include"calculation.h"

//*******************************************************************************
// マクロ定義
//*******************************************************************************
#define		MAX_ANIMPATTEN_PRESS_ENTER			(2)		// アニメーションパターンの最大値 

//*******************************************************************************
// グローバル変数
//*******************************************************************************
static LPDIRECT3DTEXTURE9		g_pTexturePressEnter = NULL;		//テクスチャへのポインタ
static LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPressEnter = NULL;		//頂点バッファへのポインタ
static PressEnter				g_PE;								//プレスエンターの情報
static float					g_nMaxAnimU;						// テクスチャのX軸の最大値 

//********************************************************************************
// プレスエンターの初期化処理
//********************************************************************************
void InitPressEnter(void)
{
	// グローバル変数の設定
	g_nMaxAnimU = 1.0f / MAX_ANIMPATTEN_PRESS_ENTER;

	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// ポリゴンに張り付けるテクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/press_enter.png",
		&g_pTexturePressEnter);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// 頂点ファーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffPressEnter,
		NULL);

	// タイトルロゴ情報の初期化
	g_PE.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 中心点
	g_PE.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 中心点からの差
	g_PE.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向き
	g_PE.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);		// カラー
	g_PE.state = PRESSENTERSTATE_NORMAL;				// 通常状態
	g_PE.nCountState = 0;								// 状態カウンター
	g_PE.nCountFlashing = 0;							// 点滅回数のカウンター
	g_PE.nDecision = 0;									// 点滅状態時の判定
	g_PE.bUse = false;									// 使用してない
														
	//頂点情報へのポインタを生成						
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPressEnter->Lock(0, 0, (void**)&pVtx, 0);

	// 対角線の長さを算出する
	g_PE.fLength = sqrtf(((g_PE.offset.x * g_PE.offset.x) + (g_PE.offset.y * g_PE.offset.y)) / 2.0f);

	// 対角線の角度を算出
	g_PE.fAngele = atan2f(g_PE.offset.x, g_PE.offset.y);

	// 頂点座標の設定
	pVtx[0].pos.x = g_PE.pos.x + sinf(g_PE.rot.z + (D3DX_PI + g_PE.fAngele)) * g_PE.fLength;
	pVtx[0].pos.y = g_PE.pos.y + cosf(g_PE.rot.z + (D3DX_PI + g_PE.fAngele)) * g_PE.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_PE.pos.x + sinf(g_PE.rot.z + (D3DX_PI - g_PE.fAngele)) *  g_PE.fLength;
	pVtx[1].pos.y = g_PE.pos.y + cosf(g_PE.rot.z + (D3DX_PI - g_PE.fAngele)) *  g_PE.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_PE.pos.x + sinf(g_PE.rot.z - (0 + g_PE.fAngele)) * g_PE.fLength;
	pVtx[2].pos.y = g_PE.pos.y + cosf(g_PE.rot.z - (0 + g_PE.fAngele)) * g_PE.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_PE.pos.x + sinf(g_PE.rot.z - (0 - g_PE.fAngele)) *  g_PE.fLength;
	pVtx[3].pos.y = g_PE.pos.y + cosf(g_PE.rot.z - (0 - g_PE.fAngele)) *  g_PE.fLength;
	pVtx[3].pos.z = 0.0f;

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = g_PE.col;
	pVtx[1].col = g_PE.col;
	pVtx[2].col = g_PE.col;
	pVtx[3].col = g_PE.col;

	// テクスチャ座標
	SetVtxTexture(pVtx, g_nMaxAnimU, 1.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffPressEnter->Unlock();
}

//********************************************************************************
// プレスエンターの終了処理
//********************************************************************************
void UninitPressEnter(void)
{
	// テクスチャの破棄	  
	if (g_pTexturePressEnter != NULL)
	{
		g_pTexturePressEnter->Release();

		g_pTexturePressEnter = NULL;
	}

	// 頂点バッファを破棄
	if (g_pVtxBuffPressEnter != NULL)
	{
		g_pVtxBuffPressEnter->Release();

		g_pVtxBuffPressEnter = NULL;
	}
}

//********************************************************************************
// プレスエンターの更新処理
//********************************************************************************
void UpdatePressEnter(void)
{
	// 変数宣言
	int nPage = 0;

	// 頂点情報へのポインタを生成						
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPressEnter->Lock(0, 0, (void**)&pVtx, 0);

	// フェード情報の取得
	FADE fade;			// フェード情報へのポインタ
	fade = GetFade();

	if (g_PE.bUse == true)
	{// プレスエンターが使用されてる

		if (g_PE.state != PRESSENTERSTATE_FLASHING)
		{// 点滅状態でないとき
			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{// [Enter]キーが押された
			 // 点滅状態にし各値の設定
				g_PE.state = PRESSENTERSTATE_FLASHING;
				g_PE.nCountState = FLASHING_COUNT_STATE_PE;
				g_PE.nDecision = 1;

				//サウンド再生
				PlaySound(SOUND_LABEL_SE_DECIDE);
			}
		}

		switch (g_PE.state)
		{
		case PRESSENTERSTATE_NORMAL:
			g_PE.nCountState--;

			if (g_PE.nCountState == 0)
			{// 状態カウンターの設定
				g_PE.nCountState = 0;

				// 状態の設定
				g_PE.state = PRESSENTERSTATE_TRANSPARENCY;

				// 透明に設定
				g_PE.col.a = 0.0f;
			}
			break;

		case PRESSENTERSTATE_TRANSPARENCY:
			g_PE.nCountState++;

			if (g_PE.nCountState == MAX_COUNT_STATE_PE)
			{// 状態カウンターの設定
				g_PE.nCountState = MAX_COUNT_STATE_PE;

				// 状態の設定
				g_PE.state = PRESSENTERSTATE_NORMAL;

				// 不透明に設定
				g_PE.col.a = 1.0f;
			}
			break;

		case PRESSENTERSTATE_FLASHING:
			if (g_PE.nCountFlashing != 0)
			{
				g_PE.nCountState--;

				if (g_PE.nCountState <= 0)
				{
					if (g_PE.nDecision == 1)
					{// 不透明に設定
						g_PE.col.a = 1.0f;

						g_PE.nDecision ^= 1;
						g_PE.nCountFlashing--;
						g_PE.nCountState = FLASHING_COUNT_STATE_PE;
					}
					else
					{// 透明に設定
						g_PE.col.a = 0.0f;

						g_PE.nDecision ^= 1;
						g_PE.nCountFlashing--;
						g_PE.nCountState = FLASHING_COUNT_STATE_PE;
					}
				}
			}
			else
			{
				if (fade == FADE_NONE)
				{// フェードが行われてないとき

					MODE mode = GetMode();

					if (mode == MODE_TITLE)
					{// フェード設定処理
						SetFade(MODE_TUTORIAL);
					}
					if (mode == MODE_TUTORIAL)
					{// フェード設定処理
						SetFade(MODE_GAME);
					}
				}
			}
			break;
		}
	}

	// 頂点カラーの設定
	pVtx[0].col = g_PE.col;
	pVtx[1].col = g_PE.col;
	pVtx[2].col = g_PE.col;
	pVtx[3].col = g_PE.col;

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f , 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f , 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f , 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f , 1.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffPressEnter->Unlock();
}

//********************************************************************************
// プレスエンターの描画処理
//********************************************************************************
void DrawPressEnter(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPressEnter, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// αテストを使用する
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// αテストの設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	if (g_PE.bUse == true)
	{// テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePressEnter);

		// ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	// αテストの終了
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//********************************************************************************
// プレスエンターの設定処理
//********************************************************************************
void SetPressEnter(D3DXVECTOR3 pos, D3DXVECTOR3 offset)
{
	// 頂点情報へのポインタを生成						
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPressEnter->Lock(0, 0, (void**)&pVtx, 0);

	if (g_PE.bUse == false)
	{// 使用されてない場合
		// タイトルロゴ情報の設定
		g_PE.offset = offset;														// 中心点からの差
		g_PE.pos = pos;																// 中心点
		g_PE.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									// 向き
		g_PE.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);								// カラー
		g_PE.state = PRESSENTERSTATE_TRANSPARENCY;									// 通常状態
		g_PE.nCountState = 0;														// 状態カウンター
		g_PE.nCountFlashing = MAX_FLASHING;											// 点滅回数のカウンター
		g_PE.bUse = true;															// 使用してる

		// 対角線の長さを算出する
		g_PE.fLength = sqrtf(((g_PE.offset.x * g_PE.offset.x) + (g_PE.offset.y * g_PE.offset.y)) / 2.0f);

		// 対角線の角度を算出
		g_PE.fAngele = atan2f(g_PE.offset.x, g_PE.offset.y);

		// 頂点座標の設定
		pVtx[0].pos.x = g_PE.pos.x + sinf(g_PE.rot.z + (D3DX_PI + g_PE.fAngele)) * g_PE.fLength;
		pVtx[0].pos.y = g_PE.pos.y + cosf(g_PE.rot.z + (D3DX_PI + g_PE.fAngele)) * g_PE.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_PE.pos.x + sinf(g_PE.rot.z + (D3DX_PI - g_PE.fAngele)) *  g_PE.fLength;
		pVtx[1].pos.y = g_PE.pos.y + cosf(g_PE.rot.z + (D3DX_PI - g_PE.fAngele)) *  g_PE.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_PE.pos.x + sinf(g_PE.rot.z - (0 + g_PE.fAngele)) * g_PE.fLength;
		pVtx[2].pos.y = g_PE.pos.y + cosf(g_PE.rot.z - (0 + g_PE.fAngele)) * g_PE.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_PE.pos.x + sinf(g_PE.rot.z - (0 - g_PE.fAngele)) *  g_PE.fLength;
		pVtx[3].pos.y = g_PE.pos.y + cosf(g_PE.rot.z - (0 - g_PE.fAngele)) *  g_PE.fLength;
		pVtx[3].pos.z = 0.0f;

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = g_PE.col;
		pVtx[1].col = g_PE.col;
		pVtx[2].col = g_PE.col;
		pVtx[3].col = g_PE.col;

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// 頂点バッファをアンロック
	g_pVtxBuffPressEnter->Unlock();
}