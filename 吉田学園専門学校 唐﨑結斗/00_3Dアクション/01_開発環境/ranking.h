//**************************************************************************************************
//
//ランキングの設定処理
//Auther：唐﨑結斗
//
//**************************************************************************************************
#ifndef _RANKING_H_		//このマクロ定義がされてなかったら
#define _RANKING_H_		//二重インク―ルード防止のマクロ定義

#include"main.h"

#include"file.h"

//*************************************************************
//マクロ定義
//*************************************************************
#define MAX_RANK						(5)						// ランキングランクの最大数
#define MAX_RANK_DIGITS					(8)						// ランキングスコアの桁数
#define POS_RANK_X						(360.0f)				// ランキングランク位置(X)
#define POS_RANK_Y						(220.0f)				// ランキングランク位置(Y)
#define MAX_OFFSET_RANK_X				(100.0f)				// ランキングランク大きさ(幅)
#define MAX_OFFSET_RANK_Y				(60.0f)					// ランキングランク大きさ(高さ)
#define POS_RANKING_SCORE_X				(950.0f)				// ランキングスコア位置(X)
#define MAX_OFFSET_RANKING_SCORE_X		(30.0f)					// ランキングスコア大きさ(幅)
#define MAX_OFFSET_RANKING_SCORE_Y		(60.0f)					// ランキングスコア大きさ(高さ)
#define INTERVAL_FLASHING				(3)						// 更新スコアの点滅頻度
#define MAX_TIME						(600)					// ランキング表示時間
#define FILE_RANKING_NAME000			"ranking_score.txt"		// ランキングファイル名(txt)
#define FILE_RANKING_NAME001			"ranking_score.bin"		// ランキングファイル名(bin)


//************************************************************
//ランキングランクの構造体を定義
//************************************************************
typedef struct
{
	D3DXVECTOR3 pos;							//中心点
	D3DXVECTOR3 offset;							//中心点からの差
	D3DXVECTOR3 rot;							//向き
	D3DXCOLOR col;								//カラー
	float fLength;								//対角線の長さ
	float fAngele;								//対角線の角度
}Rank;

//************************************************************
//ランキングスコアの構造体を定義
//************************************************************
typedef struct
{
	D3DXVECTOR3 pos[MAX_RANK_DIGITS];			//中心点
	D3DXVECTOR3 offset;							//中心点からの差
	D3DXVECTOR3 rot;							//向き
	D3DXCOLOR col;								//カラー
	float fLength;								//対角線の長さ
	float fAngele;								//対角線の角度
	int nScore;									//スコアの値
}RankingScore;

//****************************************
//プロトタイプ宣言
//****************************************
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void ResetRanking(void);
void SetRanking(int nScore);

#endif
