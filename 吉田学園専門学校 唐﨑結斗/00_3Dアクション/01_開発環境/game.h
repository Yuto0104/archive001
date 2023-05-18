//**************************************************************************************************
//
// ゲーム画面の設定処理
// Auther：唐�ｱ結斗
//
//**************************************************************************************************
#ifndef _GAME_H_		// このマクロ定義がされてなかったら
#define _GAME_H_		// 二重インク―ルード防止のマクロ定義

#include"main.h"

//****************************************
// プロトタイプ宣言
//****************************************
void	InitGame	(void);
void	UninitGame	(void);
void	UpdateGame	(void);
void	DrawGame	(void);

#endif
