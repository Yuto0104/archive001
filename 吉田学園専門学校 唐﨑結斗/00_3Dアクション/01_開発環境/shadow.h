//**************************************************************************************************
//
// 影描画処理(shadow.h)
// Auther：唐﨑結斗
//
//**************************************************************************************************
#ifndef _SHADOW_H_			// このマクロ定義がされてなかったら
#define _SHADOW_H_			// 二重インクルード防止のマクロ定義

//***************************************************************************
// インクルード
//***************************************************************************
#include "main.h"

//***************************************************************
// ポリゴン構造体を定義
//***************************************************************
typedef struct
{
	D3DXVECTOR3		pos;			// 位置
	D3DXVECTOR3		rot;			// 向き
	D3DXMATRIX		mtxWorld;		// ワールドマトリックス
	D3DXVECTOR3		size;			// 大きさ
	bool			bUse;			// 使用状況
}Shadow;

//***************************************************************
// プロトタイプ宣言
//***************************************************************
// 制御関数
void	InitShadow		(void);
void	UninitShadow	(void);
void	UpdateShadow	(void);
void	DrawShadow		(void);

// 副制御関数
int		SetShadow				(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
void	SetPositionShadow		(int nIdxShadow, D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR3 size);
void	DeleteShadow			(int nIdxShadow);

#endif
