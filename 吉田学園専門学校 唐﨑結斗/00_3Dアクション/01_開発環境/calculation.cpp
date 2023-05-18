//**************************************************************************************************
//
// 計算処理(calculation.cpp)
// Auther：唐﨑結斗
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include "main.h"
#include "calculation.h"

//---------------------------------------------------------------------------
// ワールド座標へのキャスト処理
//---------------------------------------------------------------------------
D3DXVECTOR3	WorldCastVtx(D3DXVECTOR3 vtx, D3DXVECTOR3 FormerPos, D3DXVECTOR3 FormerRot)
{
	// 変数宣言
	D3DXMATRIX		mtxWorldVtx;				// ワールドマトリックス
	D3DXMATRIX		mtxRot, mtxTrans;			// 計算用マトリックス

	// ワールドマトリックスの初期化
	// 行列初期化関数(第一引数の[行列]を[単位行列]に初期化)
	D3DXMatrixIdentity(&mtxWorldVtx);

	// 位置を反映
	// 行列移動関数 (第一引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, vtx.x, vtx.y, vtx.z);
	D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxTrans);		// 行列掛け算関数

	// 向きの反映
	// 行列回転関数 (第一引数に[ヨー(y)ピッチ(x)ロール(z)]方向の回転行列を作成)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, FormerRot.y, FormerRot.x, FormerRot.z);

	// 行列掛け算関数 (第二引数 * 第三引数を第一引数に格納)
	D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxRot);

	// 位置を反映
	// 行列移動関数 (第一引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, FormerPos.x, FormerPos.y, FormerPos.z);
	D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxTrans);		// 行列掛け算関数

	return D3DXVECTOR3(mtxWorldVtx._41, mtxWorldVtx._42, mtxWorldVtx._43);
}

//---------------------------------------------------------------------------
// 角度の正規化処理
//---------------------------------------------------------------------------
float RotNormalization(float fRot)
{
	if (fRot >= D3DX_PI)
	{// 移動方向の正規化
		fRot -= D3DX_PI * 2;
	}
	else if (fRot <= -D3DX_PI)
	{// 移動方向の正規化
		fRot += D3DX_PI * 2;
	}

	return fRot;
}

//---------------------------------------------------------------------------
// 頂点座標の設定処理
//---------------------------------------------------------------------------
void SetVertex(VERTEX_2D *pVtx, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fAngele, float fLength, float SizeX, int nType)
{
	if (nType == 0)
	{// 頂点座標の設定
		pVtx[0].pos.x = pos.x + sinf(rot.z + (D3DX_PI + fAngele)) * fLength;
		pVtx[0].pos.y = pos.y + cosf(rot.z + (D3DX_PI + fAngele)) * fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = pos.x + sinf(rot.z + (D3DX_PI - fAngele)) * fLength;
		pVtx[1].pos.y = pos.y + cosf(rot.z + (D3DX_PI - fAngele)) * fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = pos.x + sinf(rot.z - (D3DX_PI / 2)) * SizeX / 2;
		pVtx[2].pos.y = pos.y + cosf(rot.z - (D3DX_PI / 2)) * SizeX / 2;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = pos.x + sinf(rot.z - (-D3DX_PI / 2)) * SizeX / 2;
		pVtx[3].pos.y = pos.y + cosf(rot.z - (-D3DX_PI / 2)) * SizeX / 2;
		pVtx[3].pos.z = 0.0f;
	}
	else if (nType == 1)
	{// 頂点座標の設定
		pVtx[0].pos.x = pos.x + sinf(rot.z + (D3DX_PI + fAngele)) * fLength;
		pVtx[0].pos.y = pos.y + cosf(rot.z + (D3DX_PI + fAngele)) * fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = pos.x + sinf(rot.z + (D3DX_PI - fAngele)) * fLength;
		pVtx[1].pos.y = pos.y + cosf(rot.z + (D3DX_PI - fAngele)) * fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = pos.x + sinf(rot.z - (0 + fAngele)) * fLength;
		pVtx[2].pos.y = pos.y + cosf(rot.z - (0 + fAngele)) * fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = pos.x + sinf(rot.z - (0 - fAngele)) * fLength;
		pVtx[3].pos.y = pos.y + cosf(rot.z - (0 - fAngele)) * fLength;
		pVtx[3].pos.z = 0.0f;
	}
}

//---------------------------------------------------------------------------
// rhwの設定の設定処理
//---------------------------------------------------------------------------
void SetRhw(VERTEX_2D *pVtx)
{
	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
}

//---------------------------------------------------------------------------
// 頂点カラーの設定処理
//---------------------------------------------------------------------------
void SetVtxColor(VERTEX_2D *pVtx, float fRed, float fGreen, float fBlue, float fAlpha)
{
	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(fRed, fGreen, fBlue, fAlpha);
	pVtx[1].col = D3DXCOLOR(fRed, fGreen, fBlue, fAlpha);
	pVtx[2].col = D3DXCOLOR(fRed, fGreen, fBlue, fAlpha);
	pVtx[3].col = D3DXCOLOR(fRed, fGreen, fBlue, fAlpha);
}

//---------------------------------------------------------------------------
// テクスチャ座標の設定処理
//---------------------------------------------------------------------------
void SetVtxTexture(VERTEX_2D *pVtx, float fTexU, float fTexV)
{
	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fTexU, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, fTexV);
	pVtx[3].tex = D3DXVECTOR2(fTexU, fTexV);
}