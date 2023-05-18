//**************************************************************************************************
//
// ライン描画処理(line.h)
// Auther：唐﨑結斗
//
//**************************************************************************************************
#ifndef _LINE_H_			// このマクロ定義がされてなかったら
#define _LINE_H_			// 二重インクルード防止のマクロ定義

//***************************************************************************
// インクルード
//***************************************************************************
#include "main.h"

//***************************************************************
// ライン構造体を定義
//***************************************************************
typedef struct
{
	D3DXVECTOR3		pos;			// 位置
	D3DXVECTOR3		rot;			// 向き
	D3DXVECTOR3		start;			// 始点
	D3DXVECTOR3		goal;			// 終点
	D3DXMATRIX		mtxWorld;		// ワールドマトリックス
	float			fLength;		// 長さ
	bool			bUse;			// 使用状況
}Line;

//***************************************************************
// プロトタイプ宣言
//***************************************************************
// 制御関数
void	InitLine(void);
void	UninitLine(void);
void	UpdateLine(void);
void	DrawLine(void);

// 副制御関数
int SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 start, D3DXVECTOR3 goal, D3DXCOLOR col);
void MoveLine(int nCnt, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void DeleteLine(int nCnt);
#endif
