//**************************************************************************************************
//
//コンティニューの設定処理
//Auther：唐﨑結斗
//
//**************************************************************************************************
#ifndef _CONTINUE_H_		//このマクロ定義がされてなかったら
#define _CONTINUE_H_		//二重インク―ルード防止のマクロ定義

#include"main.h"

//*************************************************************
//マクロ定義
//*************************************************************
#define POS_CONTINUE_X			(640.0f)	//位置(X)
#define POS_CONTINUE_Y			(240.0f)	//位置(Y)
#define MAX_OFFSET_CONTINUE_X	(250.0f)	//大きさ(幅)
#define MAX_OFFSET_CONTINUE_Y	(50.0f)		//大きさ(高さ)

//************************************************************
//コンティニューの構造体を定義
//************************************************************
typedef struct
{
	D3DXVECTOR3 pos;							//中心点
	D3DXVECTOR3 offset;							//中心点からの差
	D3DXVECTOR3 rot;							//向き
	D3DXCOLOR col;								//カラー
	float fLength;								//対角線の長さ
	float fAngele;								//対角線の角度
	bool bUse;									//使用してるかどうか
}Continue;

//****************************************
//プロトタイプ宣言
//****************************************
void InitContinue(void);
void UninitContinue(void);
void UpdateContinue(void);
void DrawContinue(void);
void SetContinue(void);

#endif