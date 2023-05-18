//**************************************************************************************************
//
// ���C���`�揈��(line.h)
// Auther�F�������l
//
//**************************************************************************************************
#ifndef _LINE_H_			// ���̃}�N����`������ĂȂ�������
#define _LINE_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"

//***************************************************************
// ���C���\���̂��`
//***************************************************************
typedef struct
{
	D3DXVECTOR3		pos;			// �ʒu
	D3DXVECTOR3		rot;			// ����
	D3DXVECTOR3		start;			// �n�_
	D3DXVECTOR3		goal;			// �I�_
	D3DXMATRIX		mtxWorld;		// ���[���h�}�g���b�N�X
	float			fLength;		// ����
	bool			bUse;			// �g�p��
}Line;

//***************************************************************
// �v���g�^�C�v�錾
//***************************************************************
// ����֐�
void	InitLine(void);
void	UninitLine(void);
void	UpdateLine(void);
void	DrawLine(void);

// ������֐�
int SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 start, D3DXVECTOR3 goal, D3DXCOLOR col);
void MoveLine(int nCnt, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void DeleteLine(int nCnt);
#endif
