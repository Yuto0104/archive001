//**************************************************************************************************
//
// �e�`�揈��(shadow.h)
// Auther�F�������l
//
//**************************************************************************************************
#ifndef _SHADOW_H_			// ���̃}�N����`������ĂȂ�������
#define _SHADOW_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"

//***************************************************************
// �|���S���\���̂��`
//***************************************************************
typedef struct
{
	D3DXVECTOR3		pos;			// �ʒu
	D3DXVECTOR3		rot;			// ����
	D3DXMATRIX		mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXVECTOR3		size;			// �傫��
	bool			bUse;			// �g�p��
}Shadow;

//***************************************************************
// �v���g�^�C�v�錾
//***************************************************************
// ����֐�
void	InitShadow		(void);
void	UninitShadow	(void);
void	UpdateShadow	(void);
void	DrawShadow		(void);

// ������֐�
int		SetShadow				(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
void	SetPositionShadow		(int nIdxShadow, D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR3 size);
void	DeleteShadow			(int nIdxShadow);

#endif
