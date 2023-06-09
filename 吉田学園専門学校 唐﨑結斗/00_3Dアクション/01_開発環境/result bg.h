//**************************************************************************************************
//
//リザルト背景の設定処理
//Auther：唐�ｱ結斗
//
//**************************************************************************************************
#ifndef _RESULT_BG_H_		//このマクロ定義がされてなかったら
#define _RESULT_BG_H_		//二重インク―ルード防止のマクロ定義

#include"main.h"

//*************************************************************
//マクロ定義
//*************************************************************
#define MAX_OFFSET_RBG_X	(300.0f)	//大きさ(幅)
#define MAX_OFFSET_RBG_Y	(50.0f)		//大きさ(高さ)

//************************************************************
//ポーズ背景の構造体を定義
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
}ResultBG;

//****************************************
//プロトタイプ宣言
//****************************************
void InitResultBG(void);
void UninitResultBG(void);
void UpdateResultBG(void);
void DrawResultBG(void);
void SetResultBG(void);

#endif
