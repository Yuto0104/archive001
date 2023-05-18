//**************************************************************************************************
//
// ���Ԃ̏���
// Auther�F�������l
//
//**************************************************************************************************
#ifndef _TIME_H_		// ���̃}�N����`������ĂȂ�������
#define _TIME_H_		// ��d�C���N�\���[�h�h�~�̃}�N����`

#include"main.h"

//*************************************************************
// �}�N����`
//*************************************************************
#define MAX_TIME_SEPARATION		(3)				// ���Ԃ̕��A�b�A�~���b�̂��
#define MAX_TIME_DIGITS			(2)				// ���Ԃ̌���
#define MAX_VERTEX				(4)				// ���_�̍ő吔

//************************************************************
// ���ԍ\���̂��`
//************************************************************
typedef struct
{
	D3DXVECTOR3		pos[MAX_TIME_DIGITS * MAX_TIME_SEPARATION];			// ���S�_
	D3DXVECTOR3		size;												// �����ƕ��̐��l���i�[
	D3DXVECTOR3		rot;												// ����
	D3DXCOLOR		col;												// �J���[
	float			fLength;											// �Ίp���̒���
	float			fAngele;											// �Ίp���̊p�x
	int				nTime;												// �^�C��
	int				nMinutes;											// ��
	int				nSeconds;											// �b
	int				nMillisecond;										// �~���b
}Time;

//****************************************
//�v���g�^�C�v�錾
//****************************************
void	InitTime	(void);
void	UninitTime	(void);
void	UpdateTime	(void);
void	DrawTime	(void);
void	SetTime		(int nTime, D3DXVECTOR3 pos, D3DXVECTOR3 size);
void	SubTime		(void);
int		GetTime		(void);

#endif
