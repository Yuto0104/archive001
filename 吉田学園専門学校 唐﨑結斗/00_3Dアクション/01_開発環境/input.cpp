//**************************************************************************************************
//
// �O�����͏���(input.cpp)
// Auther�F�������l
//
//**************************************************************************************************

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "input.h"

//***************************************************************************
// �}�N����`
//***************************************************************************
#define NUM_KEY_MAX		(256)	//�L�[�̍ő吔

//***************************************************************************
// �O���[�o���ϐ�
//***************************************************************************
LPDIRECTINPUT8				g_pInput = NULL;						// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8		g_pDevKeyboard = NULL;					// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
BYTE						g_aKeyState[NUM_KEY_MAX];				// �L�[�{�[�h�̃v���X���
BYTE						g_aKeyStateTrigger[NUM_KEY_MAX];		// �L�[�{�[�h�̃g���K�[���
BYTE						g_aKeyStateRelease[NUM_KEY_MAX];		// �L�[�{�[�h��	�����[�X���
XINPUT_STATE				g_joykeystate;							// �W���C�p�b�h�̃v���X���
XINPUT_STATE				g_joykeystateTrigger;					// �W���C�p�b�h�̃g���K�[���
XINPUT_VIBRATION			g_joyMoter;								// �W���C�p�b�g�̃��[�^�[
VIBRATION					g_Vibration;							// �U�����̎擾
float						g_JoypadLStickAngle;					// �X�e�B�b�N�̊p�x

//---------------------------------------------------------------------------
// �L�[�{�[�h���͂̏���������
//---------------------------------------------------------------------------
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//---------------------------------------------------------------------------
// �L�[�{�[�h���͂̏I������
//---------------------------------------------------------------------------
void UninitKeyboard(void)
{
	//���̓f�o�C�X�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();	//�L�[�{�[�h�̃A�N�Z�X����j��
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//---------------------------------------------------------------------------
// �L�[�{�[�h���͂̍X�V����
//---------------------------------------------------------------------------
void UpdateKeyboard(void)
{
	//�ϐ��錾
	BYTE aKeyState[NUM_KEY_MAX];	//�L�[�{�[�h�̓��͏��
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];			//�L�[�{�[�h�̃g���K�[����ۑ�

			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & g_aKeyState[nCntKey];		//�L�[�{�[�h�̃����[�X����ۑ�

			g_aKeyState[nCntKey] = aKeyState[nCntKey];																//�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//---------------------------------------------------------------------------
// �L�[�{�[�h���͂̃v���X�����l��
//---------------------------------------------------------------------------
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}

//---------------------------------------------------------------------------
// �L�[�{�[�h���͂̃g���K�[�����l��
//---------------------------------------------------------------------------
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//---------------------------------------------------------------------------
// �L�[�{�[�h���͂̃����[�X�����l��
//---------------------------------------------------------------------------
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//---------------------------------------------------------------------------
// �W���C�p�b�h�̏���������
//---------------------------------------------------------------------------
HRESULT InitJoypad(void)
{
	//�������̃N���A
	memset(&g_joykeystate, 0, sizeof(XINPUT_STATE));

	// XInput�̃X�e�[�g��ݒ�(�L���ɂ���)
	XInputEnable(true);

	// �W���C�X�e�B�b�N�̊p�x��������
	g_JoypadLStickAngle = 0;

	// �W���C�p�b�h�̐U�������0�N���A
	ZeroMemory(&g_joyMoter, sizeof(XINPUT_VIBRATION));

	// �U������p�̏�����
	g_Vibration.nTime = 0;
	g_Vibration.nStrength = 0;

	return S_OK;
}

//---------------------------------------------------------------------------
// �W���C�p�b�h�̏I������
//---------------------------------------------------------------------------
void UninitJoypad(void)
{
	//XInput�̃X�e�[�g��ݒ�(�����ɂ���)
	XInputEnable(false);
}

//---------------------------------------------------------------------------
// �W���C�p�b�h�̍X�V����
//---------------------------------------------------------------------------
void UpdateJoypad(void)
{
	XINPUT_STATE joykeyState;	//�W���C�p�b�h�̓���

	//�W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		g_joykeystateTrigger.Gamepad.wButtons = (g_joykeystate.Gamepad.wButtons ^ joykeyState.Gamepad.wButtons) & joykeyState.Gamepad.wButtons;	  //�W���C�p�b�h�̃g���K�[����ۑ�
		g_joykeystate = joykeyState;		//�W���C�p�b�h�̃v���X����ۑ�
	}

	g_joyMoter.wLeftMotorSpeed = g_Vibration.nStrength;
	g_joyMoter.wRightMotorSpeed = g_Vibration.nStrength;

	//�U��������R���g���[���[�̐��l
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
// �W���C�p�b�h�̃v���X�����l��
//---------------------------------------------------------------------------
bool GetJoypadPress(JOYKEY nKey)
{
	return(g_joykeystate.Gamepad.wButtons &(0x01 << nKey)) ? true : false;
}

//---------------------------------------------------------------------------
// �W���C�p�b�h�̃g���K�[�����l��
//---------------------------------------------------------------------------
bool GetJoypadTrigger(JOYKEY nKey)
{
	return (g_joykeystateTrigger.Gamepad.wButtons &(0x01 << nKey)) ? true : false;
}

/*---------------------------------------------------------------------------
| �W���C�L�[�X�e�B�b�N����
---------------------------------------------------------------------------*/
D3DXVECTOR3 GetJoypadStick(JOYKEY nKey)
{
	// �ϐ��錾
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
| �W���C�p�b�h�̐U������
---------------------------------------------------------------------------*/
void JoypadVib(int nVibTime, int nVibStrength)
{
	g_Vibration.nTime = nVibTime;
	g_Vibration.nStrength = nVibStrength;
}

/*---------------------------------------------------------------------------
| �W���C�L�[�X�e�B�b�N�̊p�x���̎擾����
---------------------------------------------------------------------------*/
float GetJoyStickAngle(void)
{
	return g_JoypadLStickAngle;
}