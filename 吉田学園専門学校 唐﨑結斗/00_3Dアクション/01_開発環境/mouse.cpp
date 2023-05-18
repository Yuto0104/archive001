//**************************************************************************************************
//
// マウス入力処理(mouse.cpp)
// Auther：唐﨑結斗
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include<stdio.h>
#include"main.h"
#include "mouse.h"

//***************************************************************************
// グローバル変数
//***************************************************************************
static LPDIRECTINPUT8			g_pMouseInput = NULL;			// Directinutオブジェクトへのポインタ
static LPDIRECTINPUTDEVICE8		g_pDevMouse = NULL;				// 入力でパスへのポインタ
static DIMOUSESTATE2			g_aKeyState;					// キーボードの入力情報
static DIMOUSESTATE2			g_aKeyStatetrigger;				// キーボートのトリガー情報
static POINT					g_mousePos;						// マウスポインタの現在位置
static LPARAM					lParam;

//---------------------------------------------------------------------------
// マウス初期化処理
//---------------------------------------------------------------------------
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	// Directinputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pMouseInput, NULL)))
	{
		return E_FAIL;
	}

	// 入力デバイスの生成
	if (FAILED(g_pMouseInput->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		return E_FAIL;
	}

	g_pDevMouse->SetDataFormat(&c_dfDIMouse2);		// ﾏｳｽ用のﾃﾞｰﾀ・ﾌｫｰﾏｯﾄ設定
	g_pDevMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;				// 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）
	g_pDevMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph);

	g_pDevMouse->Acquire();
	return S_OK;
}

//---------------------------------------------------------------------------
// マウス終了処理
//---------------------------------------------------------------------------
void UninitMouse(void)
{
	if (g_pDevMouse != NULL)
	{
		g_pDevMouse->Unacquire();
		g_pDevMouse = NULL;
	}
}


//---------------------------------------------------------------------------
// マウス更新処理
//---------------------------------------------------------------------------
void UpdateMouse(void)
{
	//// マウス座標の設定
	//SetCursorPos(10, 20);

	/*GetMouseMovePointsEx(MOUSEMOVEPOINT)*/

	DIMOUSESTATE2 aKeyState;	// キーボードの入力情報

	g_pDevMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &aKeyState);

	for ( int Count = 0; Count < 8 ; Count++)
	{
		g_aKeyStatetrigger.rgbButtons[Count] = (g_aKeyState.rgbButtons[Count] ^ aKeyState.rgbButtons[Count]) & aKeyState.rgbButtons[Count];
	}

	g_aKeyState = aKeyState;

	g_pDevMouse->Acquire();
}

//---------------------------------------------------------------------------
// マウスプレス処理
//---------------------------------------------------------------------------
bool GetMousePress(MOUSE mouse)
{
	return (g_aKeyState.rgbButtons[mouse] & 0x80) ? true : false;
}

//---------------------------------------------------------------------------
// マウストリガー処理
//---------------------------------------------------------------------------
bool GetMouseTrigger(MOUSE mouse)
{
	return (g_aKeyStatetrigger.rgbButtons[mouse] & 0x80) ? true : false;

	///* 前に取得した時のマウスの状態 */
	//static bool prevState[sizeof(g_aKeyState.rgbButtons) / sizeof(g_aKeyState.rgbButtons[0])];							// トリガー処理
	///* 今のマウスの状態 */
	//bool current = GetMouse(mouse);
	///* 前の状態がfalseで、今の状態がtrueならば、クリックした瞬間と判定する */
	//bool ret = current && !prevState[mouse];
	///* 今の状態を保存する */
	//prevState[mouse] = current;
	///* 判定結果を返す */
	//return ret;

}

//---------------------------------------------------------------------------
// マウス情報取得処理
//---------------------------------------------------------------------------
D3DXVECTOR3 GetMouse(void)
{
	//g_mousePos.x = LOWORD(lParam);
	//g_mousePos.y = HIWORD(lParam);

	// 画面上のマウスポインターの位置
	GetCursorPos(&g_mousePos);		// どこにカーソルがあるのか？

	// ウィンドウ条のマウスポインタ～の位置
	ScreenToClient(GetWnd(), &g_mousePos);

	return D3DXVECTOR3((float)g_mousePos.x,(float)g_mousePos.y, 0.0f);
}

//---------------------------------------------------------------------------
// マウス移動情報取得処理
//---------------------------------------------------------------------------
D3DXVECTOR3	GetMouseMove(void)
{
	return D3DXVECTOR3((float)(g_aKeyState.lX), (float)(g_aKeyState.lY), (float)(g_aKeyState.lZ));
}