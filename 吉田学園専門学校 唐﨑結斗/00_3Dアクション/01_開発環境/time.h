//**************************************************************************************************
//
// 時間の処理
// Auther：唐﨑結斗
//
//**************************************************************************************************
#ifndef _TIME_H_		// このマクロ定義がされてなかったら
#define _TIME_H_		// 二重インク―ルード防止のマクロ定義

#include"main.h"

//*************************************************************
// マクロ定義
//*************************************************************
#define MAX_TIME_SEPARATION		(3)				// 時間の分、秒、ミリ秒のやつ
#define MAX_TIME_DIGITS			(2)				// 時間の桁数
#define MAX_VERTEX				(4)				// 頂点の最大数

//************************************************************
// 時間構造体を定義
//************************************************************
typedef struct
{
	D3DXVECTOR3		pos[MAX_TIME_DIGITS * MAX_TIME_SEPARATION];			// 中心点
	D3DXVECTOR3		size;												// 高さと幅の数値を格納
	D3DXVECTOR3		rot;												// 向き
	D3DXCOLOR		col;												// カラー
	float			fLength;											// 対角線の長さ
	float			fAngele;											// 対角線の角度
	int				nTime;												// タイム
	int				nMinutes;											// 分
	int				nSeconds;											// 秒
	int				nMillisecond;										// ミリ秒
}Time;

//****************************************
//プロトタイプ宣言
//****************************************
void	InitTime	(void);
void	UninitTime	(void);
void	UpdateTime	(void);
void	DrawTime	(void);
void	SetTime		(int nTime, D3DXVECTOR3 pos, D3DXVECTOR3 size);
void	SubTime		(void);
int		GetTime		(void);

#endif
