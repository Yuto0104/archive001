//**************************************************************************************************
//
// 計算処理(calculation.h)
// Auther：唐﨑結斗
//
//**************************************************************************************************
#ifndef _CALCULATION_H_			// このマクロ定義がされてなかったら
#define _CALCULATION_H_			// 二重インクルード防止のマクロ定義

//***************************************************************************
// インクルード
//***************************************************************************
#include "main.h"

//***************************************************************
// プロトタイプ宣言
//***************************************************************
// 制御関数
D3DXVECTOR3	WorldCastVtx(D3DXVECTOR3 vtx, D3DXVECTOR3 FormerPos, D3DXVECTOR3 FormerRot);
float RotNormalization(float fRot);
void SetVertex(VERTEX_2D *pVtx, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fAngele, float fLength, float SizeX, int nType);
void SetRhw(VERTEX_2D *pVtx);
void SetVtxColor(VERTEX_2D *pVtx, float fRed, float fGreen, float fBlue, float fAlpha);
void SetVtxTexture(VERTEX_2D *pVtx, float fTexU, float fTexV);

#endif
