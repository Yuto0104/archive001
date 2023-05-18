//**************************************************************************************************
//
//スコアの処理
//Auther：唐﨑結斗
//
//**************************************************************************************************
#ifndef _SCORE_H_		//このマクロ定義がされてなかったら
#define _SCORE_H_		//二重インク―ルード防止のマクロ定義

//*************************************************************
//マクロ定義
//*************************************************************
#define MAX_DIGITS		(8)			//スコアの桁数
#define MAX_VERTEX		(4)			//頂点の最大数

//************************************************************
//スコア構造体を定義
//************************************************************
typedef struct
{
	D3DXVECTOR3 pos[MAX_DIGITS];			//中心点
	D3DXVECTOR3 offset;						//中心点からの差
	D3DXVECTOR3 rot;						//向き
	D3DXCOLOR col;							//カラー
	float fLength;							//対角線の長さ
	float fAngele;							//対角線の角度
	int nScore;								//スコア
}Score;

//****************************************
//プロトタイプ宣言
//****************************************
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore, D3DXVECTOR3 pos, D3DXVECTOR3 offset);
void AddScore(int nValue);
int GetScore(void);

#endif