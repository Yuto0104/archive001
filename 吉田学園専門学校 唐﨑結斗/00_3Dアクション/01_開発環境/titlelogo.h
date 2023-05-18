//**************************************************************************************************
//
// タイトルロゴの設定処理
// Auther：唐﨑結斗
//
//**************************************************************************************************
#ifndef _TITLE_LOGO_H_		// このマクロ定義がされてなかったら
#define _TITLE_LOGO_H_		// 二重インク―ルード防止のマクロ定義

#include"main.h"

//*************************************************************
// マクロ定義
//*************************************************************
#define		MAX_OFFSET_TL_X		(640.0f)		// 大きさ(幅)
#define		MAX_OFFSET_TL_Y		(300.0f)		// 大きさ(高さ)
#define		MAX_MOVE_SPEED		(2.0f)			// 移動速度
#define		MAX_MOVED			(240.0f)		// 移動最大距離

//************************************************************
// タイトルロゴの構造体を定義
//************************************************************
typedef struct
{
	D3DXVECTOR3		pos;							// 中心点
	D3DXVECTOR3		offset;							// 中心点からの差
	D3DXVECTOR3		rot;							// 向き
	D3DXVECTOR3		move;							// 移動距離
	float			fLength;						// 対角線の長さ
	float			fAngele;						// 対角線の角度
	float			fSpeed;							// 移動速度
	bool			bUse;							// 使用してるかどうか
}Logo;

//****************************************
// プロトタイプ宣言
//****************************************
void	InitTitleLogo		(void);
void	UninitTitleLogo		(void);
void	UpdateTitleLogo		(void);
void	DrawTitleLogo		(void);
void	SetTitleLogo		(void);

#endif
