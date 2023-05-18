//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_BGM003,			// BGM3
	SOUND_LABEL_BGM004,			// BGM4
	SOUND_LABEL_BGM005,			// BGM5
	SOUND_LABEL_BGM006,			// BGM6
	SOUND_LABEL_BGM007,			// BGM7
	SOUND_LABEL_SE_DECIDE,		// ���։�
	SOUND_LABEL_SE_SELECT,		// �I����
	SOUND_LABEL_SE_PAUSE,		// �|�[�Y��
	SOUND_LABEL_SE_COIN000,		// �R�C����
	SOUND_LABEL_SE_DAMAGE000,	// �_���[�W��
	SOUND_LABEL_SE_DEATH,		// ���ʉ�
	SOUND_LABEL_SE_JUMP,		// �W�����v��
	SOUND_LABEL_SE_BGM_CLER,	// �N���A��
	SOUND_LABEL_SE_POWER,		// �p���[��
	SOUND_LABEL_SE_DESTROY,		// �j��
	SOUND_LABEL_SE_COUNT,		// �J�E���^�[��
	SOUND_LABEL_SE_DAMAGE001,	// �_���[�W��1
	SOUND_LABEL_SE_APPEAR,		// �L�m�R��
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
