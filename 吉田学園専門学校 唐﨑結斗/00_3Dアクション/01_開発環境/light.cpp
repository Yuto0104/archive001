//**************************************************************************************************
//
// ライト処理(light.cpp)
// Auther：唐�ｱ結斗
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include "main.h"
#include "light.h"

//***************************************************************************
// マクロ定義
//***************************************************************************
#define MAX_LIGHT		(3)		// ライトの最大数

//***************************************************************************
// グローバル変数
//***************************************************************************
D3DLIGHT9		g_light[MAX_LIGHT];		// ライト情報

//---------------------------------------------------------------------------
// ライト初期化処理
//---------------------------------------------------------------------------
void InitLight(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXVECTOR3			vecDir;						// ライト方向ベクトル

	// ライトをクリアする
	ZeroMemory(&g_light[0], sizeof(g_light));		// 構造体変数をゼロクリア(第一変数[クリアする変数]、第二変数[初期化するデータ数])

	// ライト0番目の設定
	// ライトの種類
	g_light[0].Type = D3DLIGHT_DIRECTIONAL;			// 平行光源

	// ライトの拡散光を設定
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// ライトカラー

	// ライト方向を設定
	vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);

	// 正規化する(大きさを1のベクトルにする)
	D3DXVec3Normalize(&vecDir, &vecDir);		// ベクトルを大きさ1にする便利関数
	g_light[0].Direction = vecDir;

	// ライトを設定する
	pDevice->SetLight(0, &g_light[0]);		// 0番目のライトを設定

	// ライトを有効にする
	pDevice->LightEnable(0, TRUE);			// 0番目のライトを有効

	// ライト1番目の設定
	// ライトの種類
	g_light[1].Type = D3DLIGHT_DIRECTIONAL;			// 平行光源

	// ライトの拡散光を設定
	g_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// ライトカラー

	// ライト方向を設定
	vecDir = D3DXVECTOR3(0.2f, 0.8f, -0.4f);

	// 正規化する(大きさを1のベクトルにする)
	D3DXVec3Normalize(&vecDir, &vecDir);		// ベクトルを大きさ1にする便利関数
	g_light[1].Direction = vecDir;

	// ライトを設定する
	pDevice->SetLight(1, &g_light[1]);		// 1番目のライトを設定

	// ライトを有効にする
	pDevice->LightEnable(1, TRUE);			// 1番目のライトを有効

	// ライト2番目の設定
	// ライトの種類
	g_light[2].Type = D3DLIGHT_DIRECTIONAL;			// 平行光源

	// ライトの拡散光を設定
	g_light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// ライトカラー

	// ライト方向を設定
	vecDir = D3DXVECTOR3(-0.2f, -0.5f, 0.7f);

	// 正規化する(大きさを1のベクトルにする)
	D3DXVec3Normalize(&vecDir, &vecDir);		// ベクトルを大きさ1にする便利関数
	g_light[2].Direction = vecDir;

	// ライトを設定する
	pDevice->SetLight(2, &g_light[2]);		// 2番目のライトを設定

	// ライトを有効にする
	pDevice->LightEnable(2, TRUE);			// 2番目のライトを有効
}

//---------------------------------------------------------------------------
// ライト終了処理
//---------------------------------------------------------------------------
void UninitLight(void)
{

}

//---------------------------------------------------------------------------
// ライト更新処理
//---------------------------------------------------------------------------
void UpdateLight(void)
{

}