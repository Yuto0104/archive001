//**************************************************************************************************
//
// コンボの処理
// Auther：唐﨑結斗
//
//**************************************************************************************************
#ifndef _COMBO_H_		// このマクロ定義がされてなかったら
#define _COMBO_H_		// 二重インク―ルード防止のマクロ定義

#include"main.h"

//*************************************************************
// マクロ定義
//*************************************************************
#define MAX_COMBO_DIGITS		(3)			// コンボの桁数
#define MAX_VERTEX				(4)			// 頂点の最大数

//************************************************************
// コンボ構造体を定義
//************************************************************
typedef struct
{
	D3DXVECTOR3		pos[MAX_COMBO_DIGITS];		// 中心点
	D3DXVECTOR3		offset;						// 中心点からの差
	D3DXVECTOR3		rot;						// 向き
	D3DXCOLOR		col;						// カラー
	float			fLength;					// 対角線の長さ
	float			fAngele;					// 対角線の角度
	int				nCombo;						// コンボ
	bool			bUse;						// 使用状況
}Combo;

//****************************************
//プロトタイプ宣言
//****************************************
void InitCombo(void);
void UninitCombo(void);
void UpdateCombo(void);
void DrawCombo(void);
void SetCombo(int nCombo, D3DXVECTOR3 pos, D3DXVECTOR3 offset);
void AddCombo(int nCombo);
int GetCombo(void);

#endif
