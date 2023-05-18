//**************************************************************************************************
//
// �r���{�[�h�`�揈��(billboard.h)
// Auther�F�������l
//
//**************************************************************************************************
#ifndef _BILLBOARD_H_			// ���̃}�N����`������ĂȂ�������
#define _BILLBOARD_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"

//***************************************************************
// �r���{�[�h�\���̂��`
//***************************************************************
typedef struct
{
	D3DXVECTOR3		pos;			// �ʒu
	D3DXVECTOR3		posOld;			// �ߋ��ʒu
	D3DXVECTOR3		move;			// �ړ���
	D3DXVECTOR3		rot;			// ����
	D3DXMATRIX		mtxWorld;		// ���[���h�}�g���b�N�X
	float			fRadius;		// ���a
	int				nIdx;			// �C���f�b�N�X
	bool			bUse;			// �g�p��
}Billboard;

//***************************************************************
// �v���g�^�C�v�錾
//***************************************************************
// ����֐�
void	InitBillboard		(void);
void	UninitBillboard		(void);
void	UpdateBillboard		(void);
void	DrawBillboard		(void);

// ������֐�
void	SetBillboard		(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSpeed);
Billboard *GetBillboard		(void);

#endif
