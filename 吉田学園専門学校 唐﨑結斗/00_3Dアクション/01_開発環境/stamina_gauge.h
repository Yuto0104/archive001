//**************************************************************************************************
//
//酸素ゲージの設定処理
//Auther：唐﨑結斗
//
//**************************************************************************************************
#ifndef _OXYGEN_GAUGE_H_		//このマクロ定義がされてなかったら
#define _OXYGEN_GAUGE_H_		//二重インク―ルード防止のマクロ定義

#include"main.h"

//**********************************************************
// モーションモードの列挙型
//**********************************************************
typedef enum
{
	TYPE_GAUGE = 0,					// ゲージ
	TYPE_BG,						// 背景
	MAX_STAMINA_GAUGE_TYPE			// スタミナゲージタイプの最大数
}STAMINA_GAUGE_TYPE;

//*************************************************************
//マクロ定義
//*************************************************************
#define MAX_OFFSET_OXYGEN_GAUGE_X0		(40.0f)									// 大きさ(幅)[0]
#define MAX_OFFSET_OXYGEN_GAUGE_Y0		(370.0f)								// 大きさ(高さ)[0]
#define MAX_OFFSET_OXYGEN_GAUGE_X1		(40.0f)									// 大きさ(幅)[1]
#define MAX_OFFSET_OXYGEN_GAUGE_Y1		(0.0f)									// 大きさ(高さ)[1]
#define MAX_STAMINA_GAUGE				(1 * MAX_STAMINA_GAUGE_TYPE)			// 設置数の最大

//************************************************************
//酸素ゲージの構造体を定義
//************************************************************
typedef struct
{
	D3DXVECTOR3				pos;							// 中心点
	D3DXVECTOR3				size;							// 大きさ
	D3DXVECTOR3				maxSize;						// 大きさの最大値
	D3DXVECTOR3				rot;							// 向き
	D3DXCOLOR				col;							// カラー
	STAMINA_GAUGE_TYPE		type;							// タイプ
	float					fLength;						// 対角線の長さ
	float					fAngele;						// 対角線の角度
	bool					bUse;							// 使用してるかどうか
}StaminaGauge;

//****************************************
//プロトタイプ宣言
//****************************************
void InitStaminaGauge(void);
void UninitStaminaGauge(void);
void UpdateStaminaGauge(void);
void DrawStaminaGauge(void);
void SetStaminaGauge(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nType);
void SubStaminaGauge(int nCnt);
StaminaGauge *GetStaminaGauge(void);

#endif
