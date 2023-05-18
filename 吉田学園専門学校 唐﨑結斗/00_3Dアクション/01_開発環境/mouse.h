//**************************************************************************************************
//
// マウス入力処理(mouse.h)
// Auther：唐�ｱ結斗
//
//**************************************************************************************************
#ifndef _MOUSE_H_		// このマクロ定義がされてなかったら
#define _MOUSE_H_		// 二重インクルード防止のマクロ定義

//***************************************************************************
// インクルード
//***************************************************************************
#include "main.h"

//***************************************************************
// マウス構造体を定義
//***************************************************************
typedef enum
{
	MOUSE_INPUT_LEFT,			//マウス左ボタン
	MOUSE_INPUT_RIGHT,			//マウス右ボタン
	MOUSE_INPUT_MIDDLE,			//マウス中央ボタン
	MOUSE_INPUT_4,				//マウスボタン4
	MOUSE_INPUT_5,				//マウスボタン5
	MOUSE_INPUT_6,				//マウスボタン6
	MOUSE_INPUT_7,				//マウスボタン7
	MOUSE_INPUT_8,				//マウスボタン8
}MOUSE;

//***************************************************************
// プロトタイプ宣言
//***************************************************************
HRESULT			InitMouse			(HINSTANCE hlnstance, HWND hWnd);
void			UninitMouse			(void);
void			UpdateMouse			(void);
bool			GetMousePress		(MOUSE mouse);
bool			GetMouseTrigger		(MOUSE mouse);
D3DXVECTOR3		GetMouse			(void);
D3DXVECTOR3		GetMouseMove		(void);

#endif