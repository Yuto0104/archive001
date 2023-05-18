//**************************************************************************************************
//
// �}�E�X���͏���(mouse.cpp)
// Auther�F�������l
//
//**************************************************************************************************

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include<stdio.h>
#include"main.h"
#include "mouse.h"

//***************************************************************************
// �O���[�o���ϐ�
//***************************************************************************
static LPDIRECTINPUT8			g_pMouseInput = NULL;			// Directinut�I�u�W�F�N�g�ւ̃|�C���^
static LPDIRECTINPUTDEVICE8		g_pDevMouse = NULL;				// ���͂Ńp�X�ւ̃|�C���^
static DIMOUSESTATE2			g_aKeyState;					// �L�[�{�[�h�̓��͏��
static DIMOUSESTATE2			g_aKeyStatetrigger;				// �L�[�{�[�g�̃g���K�[���
static POINT					g_mousePos;						// �}�E�X�|�C���^�̌��݈ʒu
static LPARAM					lParam;

//---------------------------------------------------------------------------
// �}�E�X����������
//---------------------------------------------------------------------------
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	// Directinput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pMouseInput, NULL)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X�̐���
	if (FAILED(g_pMouseInput->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		return E_FAIL;
	}

	g_pDevMouse->SetDataFormat(&c_dfDIMouse2);		// ϳ��p���ް��E̫�ϯĐݒ�
	g_pDevMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;				// ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j
	g_pDevMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph);

	g_pDevMouse->Acquire();
	return S_OK;
}

//---------------------------------------------------------------------------
// �}�E�X�I������
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
// �}�E�X�X�V����
//---------------------------------------------------------------------------
void UpdateMouse(void)
{
	//// �}�E�X���W�̐ݒ�
	//SetCursorPos(10, 20);

	/*GetMouseMovePointsEx(MOUSEMOVEPOINT)*/

	DIMOUSESTATE2 aKeyState;	// �L�[�{�[�h�̓��͏��

	g_pDevMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &aKeyState);

	for ( int Count = 0; Count < 8 ; Count++)
	{
		g_aKeyStatetrigger.rgbButtons[Count] = (g_aKeyState.rgbButtons[Count] ^ aKeyState.rgbButtons[Count]) & aKeyState.rgbButtons[Count];
	}

	g_aKeyState = aKeyState;

	g_pDevMouse->Acquire();
}

//---------------------------------------------------------------------------
// �}�E�X�v���X����
//---------------------------------------------------------------------------
bool GetMousePress(MOUSE mouse)
{
	return (g_aKeyState.rgbButtons[mouse] & 0x80) ? true : false;
}

//---------------------------------------------------------------------------
// �}�E�X�g���K�[����
//---------------------------------------------------------------------------
bool GetMouseTrigger(MOUSE mouse)
{
	return (g_aKeyStatetrigger.rgbButtons[mouse] & 0x80) ? true : false;

	///* �O�Ɏ擾�������̃}�E�X�̏�� */
	//static bool prevState[sizeof(g_aKeyState.rgbButtons) / sizeof(g_aKeyState.rgbButtons[0])];							// �g���K�[����
	///* ���̃}�E�X�̏�� */
	//bool current = GetMouse(mouse);
	///* �O�̏�Ԃ�false�ŁA���̏�Ԃ�true�Ȃ�΁A�N���b�N�����u�ԂƔ��肷�� */
	//bool ret = current && !prevState[mouse];
	///* ���̏�Ԃ�ۑ����� */
	//prevState[mouse] = current;
	///* ���茋�ʂ�Ԃ� */
	//return ret;

}

//---------------------------------------------------------------------------
// �}�E�X���擾����
//---------------------------------------------------------------------------
D3DXVECTOR3 GetMouse(void)
{
	//g_mousePos.x = LOWORD(lParam);
	//g_mousePos.y = HIWORD(lParam);

	// ��ʏ�̃}�E�X�|�C���^�[�̈ʒu
	GetCursorPos(&g_mousePos);		// �ǂ��ɃJ�[�\��������̂��H

	// �E�B���h�E���̃}�E�X�|�C���^�`�̈ʒu
	ScreenToClient(GetWnd(), &g_mousePos);

	return D3DXVECTOR3((float)g_mousePos.x,(float)g_mousePos.y, 0.0f);
}

//---------------------------------------------------------------------------
// �}�E�X�ړ����擾����
//---------------------------------------------------------------------------
D3DXVECTOR3	GetMouseMove(void)
{
	return D3DXVECTOR3((float)(g_aKeyState.lX), (float)(g_aKeyState.lY), (float)(g_aKeyState.lZ));
}