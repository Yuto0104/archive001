//**************************************************************************************************
//
// 外部入力処理(input.cpp)
// Auther：唐﨑結斗
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include "input.h"

//***************************************************************************
// マクロ定義
//***************************************************************************
#define NUM_KEY_MAX		(256)	//キーの最大数

//***************************************************************************
// グローバル変数
//***************************************************************************
LPDIRECTINPUT8				g_pInput = NULL;						// DirectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8		g_pDevKeyboard = NULL;					// 入力デバイス(キーボード)へのポインタ
BYTE						g_aKeyState[NUM_KEY_MAX];				// キーボードのプレス情報
BYTE						g_aKeyStateTrigger[NUM_KEY_MAX];		// キーボードのトリガー情報
BYTE						g_aKeyStateRelease[NUM_KEY_MAX];		// キーボードの	リリース情報
XINPUT_STATE				g_joykeystate;							// ジョイパッドのプレス情報
XINPUT_STATE				g_joykeystateTrigger;					// ジョイパッドのトリガー情報
XINPUT_VIBRATION			g_joyMoter;								// ジョイパットのモーター
VIBRATION					g_Vibration;							// 振動情報の取得
float						g_JoypadLStickAngle;					// スティックの角度

//---------------------------------------------------------------------------
// キーボード入力の初期化処理
//---------------------------------------------------------------------------
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//入力デバイス(キーボード)の生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//---------------------------------------------------------------------------
// キーボード入力の終了処理
//---------------------------------------------------------------------------
void UninitKeyboard(void)
{
	//入力デバイスの破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();	//キーボードのアクセス権を破棄
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//---------------------------------------------------------------------------
// キーボード入力の更新処理
//---------------------------------------------------------------------------
void UpdateKeyboard(void)
{
	//変数宣言
	BYTE aKeyState[NUM_KEY_MAX];	//キーボードの入力情報
	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];			//キーボードのトリガー情報を保存

			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & g_aKeyState[nCntKey];		//キーボードのリリース情報を保存

			g_aKeyState[nCntKey] = aKeyState[nCntKey];																//キーボードのプレス情報を保存
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();	//キーボードへのアクセス権を獲得
	}
}

//---------------------------------------------------------------------------
// キーボード入力のプレス情報を獲得
//---------------------------------------------------------------------------
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}

//---------------------------------------------------------------------------
// キーボード入力のトリガー情報を獲得
//---------------------------------------------------------------------------
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//---------------------------------------------------------------------------
// キーボード入力のリリース情報を獲得
//---------------------------------------------------------------------------
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//---------------------------------------------------------------------------
// ジョイパッドの初期化処理
//---------------------------------------------------------------------------
HRESULT InitJoypad(void)
{
	//メモリのクリア
	memset(&g_joykeystate, 0, sizeof(XINPUT_STATE));

	// XInputのステートを設定(有効にする)
	XInputEnable(true);

	// ジョイスティックの角度を初期化
	g_JoypadLStickAngle = 0;

	// ジョイパッドの振動制御の0クリア
	ZeroMemory(&g_joyMoter, sizeof(XINPUT_VIBRATION));

	// 振動制御用の初期化
	g_Vibration.nTime = 0;
	g_Vibration.nStrength = 0;

	return S_OK;
}

//---------------------------------------------------------------------------
// ジョイパッドの終了処理
//---------------------------------------------------------------------------
void UninitJoypad(void)
{
	//XInputのステートを設定(無効にする)
	XInputEnable(false);
}

//---------------------------------------------------------------------------
// ジョイパッドの更新処理
//---------------------------------------------------------------------------
void UpdateJoypad(void)
{
	XINPUT_STATE joykeyState;	//ジョイパッドの入力

	//ジョイパッドの状態を取得
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		g_joykeystateTrigger.Gamepad.wButtons = (g_joykeystate.Gamepad.wButtons ^ joykeyState.Gamepad.wButtons) & joykeyState.Gamepad.wButtons;	  //ジョイパッドのトリガー情報を保存
		g_joykeystate = joykeyState;		//ジョイパッドのプレス情報を保存
	}

	g_joyMoter.wLeftMotorSpeed = g_Vibration.nStrength;
	g_joyMoter.wRightMotorSpeed = g_Vibration.nStrength;

	//振動させるコントローラーの数値
	XInputSetState(0, &g_joyMoter);

	if (g_Vibration.nTime > 0)
	{
		g_Vibration.nTime--;
	}
	else
	{
		g_Vibration.nStrength = 0;
		g_Vibration.nTime = 0;
	}
}

//---------------------------------------------------------------------------
// ジョイパッドのプレス情報を獲得
//---------------------------------------------------------------------------
bool GetJoypadPress(JOYKEY nKey)
{
	return(g_joykeystate.Gamepad.wButtons &(0x01 << nKey)) ? true : false;
}

//---------------------------------------------------------------------------
// ジョイパッドのトリガー情報を獲得
//---------------------------------------------------------------------------
bool GetJoypadTrigger(JOYKEY nKey)
{
	return (g_joykeystateTrigger.Gamepad.wButtons &(0x01 << nKey)) ? true : false;
}

/*---------------------------------------------------------------------------
| ジョイキースティック処理
---------------------------------------------------------------------------*/
D3DXVECTOR3 GetJoypadStick(JOYKEY nKey)
{
	// 変数宣言
	D3DXVECTOR3 stick;

	switch (nKey)
	{
	case JOYKEY_L_STICK:
		stick = D3DXVECTOR3(g_joykeystate.Gamepad.sThumbLX / 30000.0f, -g_joykeystate.Gamepad.sThumbLY / 30000.0f, 0.0f);

		g_JoypadLStickAngle = atan2f(g_joykeystate.Gamepad.sThumbLX / 30000.0f, -g_joykeystate.Gamepad.sThumbLY / 30000.0f);
		break;

	case JOYKEY_R_STICK:
		stick = D3DXVECTOR3(g_joykeystate.Gamepad.sThumbRX / 30000.0f, -g_joykeystate.Gamepad.sThumbRY / 30000.0f, 0.0f);
		break;
	}

	return stick;
}

/*---------------------------------------------------------------------------
| ジョイパッドの振動制御
---------------------------------------------------------------------------*/
void JoypadVib(int nVibTime, int nVibStrength)
{
	g_Vibration.nTime = nVibTime;
	g_Vibration.nStrength = nVibStrength;
}

/*---------------------------------------------------------------------------
| ジョイキースティックの角度情報の取得処理
---------------------------------------------------------------------------*/
float GetJoyStickAngle(void)
{
	return g_JoypadLStickAngle;
}