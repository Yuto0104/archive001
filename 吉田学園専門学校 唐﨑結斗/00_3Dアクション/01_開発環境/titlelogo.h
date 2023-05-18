//**************************************************************************************************
//
// �^�C�g�����S�̐ݒ菈��
// Auther�F�������l
//
//**************************************************************************************************
#ifndef _TITLE_LOGO_H_		// ���̃}�N����`������ĂȂ�������
#define _TITLE_LOGO_H_		// ��d�C���N�\���[�h�h�~�̃}�N����`

#include"main.h"

//*************************************************************
// �}�N����`
//*************************************************************
#define		MAX_OFFSET_TL_X		(640.0f)		// �傫��(��)
#define		MAX_OFFSET_TL_Y		(300.0f)		// �傫��(����)
#define		MAX_MOVE_SPEED		(2.0f)			// �ړ����x
#define		MAX_MOVED			(240.0f)		// �ړ��ő勗��

//************************************************************
// �^�C�g�����S�̍\���̂��`
//************************************************************
typedef struct
{
	D3DXVECTOR3		pos;							// ���S�_
	D3DXVECTOR3		offset;							// ���S�_����̍�
	D3DXVECTOR3		rot;							// ����
	D3DXVECTOR3		move;							// �ړ�����
	float			fLength;						// �Ίp���̒���
	float			fAngele;						// �Ίp���̊p�x
	float			fSpeed;							// �ړ����x
	bool			bUse;							// �g�p���Ă邩�ǂ���
}Logo;

//****************************************
// �v���g�^�C�v�錾
//****************************************
void	InitTitleLogo		(void);
void	UninitTitleLogo		(void);
void	UpdateTitleLogo		(void);
void	DrawTitleLogo		(void);
void	SetTitleLogo		(void);

#endif
