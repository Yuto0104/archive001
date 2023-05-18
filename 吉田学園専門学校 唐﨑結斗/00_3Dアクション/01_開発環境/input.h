//**************************************************************************************************
//
// 外部入力処理(input.h)
// Auther：唐﨑結斗
//
//**************************************************************************************************
#ifndef _INPUT_H_		// このマクロ定義がされてなかったら
#define _INPUT_H_		// 二重インクルード防止のマクロ定義

//***************************************************************************
// インクルード
//***************************************************************************
#include"main.h"

/****************************************************************
* キーの種類
****************************************************************/
typedef enum
{
	JOYKEY_UP = 0,				// 十字キー(上)
	JOYKEY_DOWN,				// 十字キー(下)
	JOYKEY_LEFT,				// 十字キー(左)
	JOYKEY_RIGHT,				// 十字キー(右)
	JOYKEY_START,				// Startボタン
	JOYKEY_BACK,				// Backボタン
	JOYKEY_L_STICK_DOWN,		// Lスティック押し込み
	JOYKEY_R_STICK_DOWN,		// Rスティック押し込み
	JOYKEY_L_B,					// LBキー
	JOYKEY_R_B,					// RBキー
	JOYKEY_NONE0,				// 割り当てキーなし
	JOYKEY_NONE1,				// 割り当てキーなし
	JOYKEY_A,					// Aキー
	JOYKEY_B,					// Bキー
	JOYKEY_X,					// Xキー
	JOYKEY_Y,					// Yキー
	JOYKEY_L_STICK,				// Lスティック
	JOYKEY_R_STICK,				// Rスティック
	JOYKEY_NONE4,				// 割り当てキーなし
	JOYKEY_NONE5,				// 割り当てキーなし
	JOYKEY_NONE6,				// 割り当てキーなし
	JOYKEY_NONE7,				// 割り当てキーなし
	JOYKEY_NONE8,				// 割り当てキーなし
	JOYKEY_NONE9,				// 割り当てキーなし
	JOYKEY_NONE10,				// 割り当てキーなし
	JOYKEY_NONE11,				// 割り当てキーなし
	JOYKEY_NONE12,				// 割り当てキーなし
	JOYKEY_NONE13,				// 割り当てキーなし
	JOYKEY_NONE14,				// 割り当てキーなし
	JOYKEY_NONE15,				// 割り当てキーなし
	JOYKEY_NONE16,				// 割り当てキーなし
	JOYKEY_NONE17,				// 割り当てキーなし
	MAX_JOYKEY
}JOYKEY;

/****************************************************************
* 振動情報の構造体
****************************************************************/
typedef struct
{
	int			nTime;			// 持続時間
	int			nStrength;		// 強さ(0 - 65535)
}VIBRATION;

//***************************************
// プロトタイプ宣言
//***************************************
HRESULT			InitKeyboard		(HINSTANCE hInstance, HWND hWnd);
void			UninitKeyboard		(void);
void			UpdateKeyboard		(void);
bool			GetKeyboardPress	(int nKey);
bool			GetKeyboardTrigger	(int nKey);
bool			GetKeyboardRelease	(int nKey);
HRESULT			InitJoypad			(void);
void			UninitJoypad		(void);
void			UpdateJoypad		(void);
bool			GetJoypadPress		(JOYKEY nKey);
bool			GetJoypadTrigger	(JOYKEY nKey);
D3DXVECTOR3		GetJoypadStick		(JOYKEY nKey);
void			JoypadVib			(int nVibTime, int nVibStrength);
float			GetJoyStickAngle	(void);

#endif

