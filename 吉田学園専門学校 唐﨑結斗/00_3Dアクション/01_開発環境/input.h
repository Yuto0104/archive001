//**************************************************************************************************
//
// �O�����͏���(input.h)
// Auther�F�������l
//
//**************************************************************************************************
#ifndef _INPUT_H_		// ���̃}�N����`������ĂȂ�������
#define _INPUT_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include"main.h"

/****************************************************************
* �L�[�̎��
****************************************************************/
typedef enum
{
	JOYKEY_UP = 0,				// �\���L�[(��)
	JOYKEY_DOWN,				// �\���L�[(��)
	JOYKEY_LEFT,				// �\���L�[(��)
	JOYKEY_RIGHT,				// �\���L�[(�E)
	JOYKEY_START,				// Start�{�^��
	JOYKEY_BACK,				// Back�{�^��
	JOYKEY_L_STICK_DOWN,		// L�X�e�B�b�N��������
	JOYKEY_R_STICK_DOWN,		// R�X�e�B�b�N��������
	JOYKEY_L_B,					// LB�L�[
	JOYKEY_R_B,					// RB�L�[
	JOYKEY_NONE0,				// ���蓖�ăL�[�Ȃ�
	JOYKEY_NONE1,				// ���蓖�ăL�[�Ȃ�
	JOYKEY_A,					// A�L�[
	JOYKEY_B,					// B�L�[
	JOYKEY_X,					// X�L�[
	JOYKEY_Y,					// Y�L�[
	JOYKEY_L_STICK,				// L�X�e�B�b�N
	JOYKEY_R_STICK,				// R�X�e�B�b�N
	JOYKEY_NONE4,				// ���蓖�ăL�[�Ȃ�
	JOYKEY_NONE5,				// ���蓖�ăL�[�Ȃ�
	JOYKEY_NONE6,				// ���蓖�ăL�[�Ȃ�
	JOYKEY_NONE7,				// ���蓖�ăL�[�Ȃ�
	JOYKEY_NONE8,				// ���蓖�ăL�[�Ȃ�
	JOYKEY_NONE9,				// ���蓖�ăL�[�Ȃ�
	JOYKEY_NONE10,				// ���蓖�ăL�[�Ȃ�
	JOYKEY_NONE11,				// ���蓖�ăL�[�Ȃ�
	JOYKEY_NONE12,				// ���蓖�ăL�[�Ȃ�
	JOYKEY_NONE13,				// ���蓖�ăL�[�Ȃ�
	JOYKEY_NONE14,				// ���蓖�ăL�[�Ȃ�
	JOYKEY_NONE15,				// ���蓖�ăL�[�Ȃ�
	JOYKEY_NONE16,				// ���蓖�ăL�[�Ȃ�
	JOYKEY_NONE17,				// ���蓖�ăL�[�Ȃ�
	MAX_JOYKEY
}JOYKEY;

/****************************************************************
* �U�����̍\����
****************************************************************/
typedef struct
{
	int			nTime;			// ��������
	int			nStrength;		// ����(0 - 65535)
}VIBRATION;

//***************************************
// �v���g�^�C�v�錾
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

