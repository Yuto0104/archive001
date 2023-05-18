//**************************************************************************************************
//
// プレスエンターの設定処理
// Auther：唐﨑結斗
//
//**************************************************************************************************
#ifndef _PRESS_ENTER_H_		// このマクロ定義がされてなかったら
#define _PRESS_ENTER_H_		// 二重インク―ルード防止のマクロ定義

#include"main.h"

//*************************************************************
// マクロ定義
//*************************************************************
#define		MAX_OFFSET_PE_X					(320.0f)		// 大きさ(幅)
#define		MAX_OFFSET_PE_Y					(50.0f)			// 大きさ(高さ)
#define		PRESS_ENTER_POS_Y				(560.0f)		// 位置
#define		MAX_COUNT_STATE_PE				(30)			// 状態カウンターの最大値
#define		MAX_FLASHING					(5 * 2)			// 点滅回数の最大値
#define		FLASHING_COUNT_STATE_PE			(3)				// 点滅時切り替えのカウンター

//************************************************************
// プレスエンターの状態の列挙型
//************************************************************
typedef enum
{
	PRESSENTERSTATE_NORMAL = 0,			// 通常状態
	PRESSENTERSTATE_TRANSPARENCY,		// 透明状態
	PRESSENTERSTATE_FLASHING,			// 点滅状態
	PRESSENTERSTATE_MAX					// 状態の種類の最大数
}PRESSENTERSTATE;

//************************************************************
// プレスエンターの構造体を定義
//************************************************************
typedef struct
{
	D3DXVECTOR3			pos;							// 中心点
	D3DXVECTOR3			offset;							// 中心点からの差
	D3DXVECTOR3			rot;							// 向き
	D3DXCOLOR			col;							// カラー
	PRESSENTERSTATE		state;							// 状態
	float				fLength;						// 対角線の長さ
	float				fAngele;						// 対角線の角度
	int					nCountState;					// 状態カウンター
	int					nCountFlashing;					// 点滅回数のカウンター
	int					nDecision;						// 点滅状態の判定用
	bool				bUse;							// 使用してるかどうか
}PressEnter;

//****************************************
// プレスエンター宣言
//****************************************
void	InitPressEnter		(void);
void	UninitPressEnter	(void);
void	UpdatePressEnter	(void);
void	DrawPressEnter		(void);
void	SetPressEnter		(D3DXVECTOR3 pos, D3DXVECTOR3 offset);

#endif
