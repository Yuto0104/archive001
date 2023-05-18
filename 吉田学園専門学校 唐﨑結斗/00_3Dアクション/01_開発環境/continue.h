//**************************************************************************************************
//
//�R���e�B�j���[�̐ݒ菈��
//Auther�F�������l
//
//**************************************************************************************************
#ifndef _CONTINUE_H_		//���̃}�N����`������ĂȂ�������
#define _CONTINUE_H_		//��d�C���N�\���[�h�h�~�̃}�N����`

#include"main.h"

//*************************************************************
//�}�N����`
//*************************************************************
#define POS_CONTINUE_X			(640.0f)	//�ʒu(X)
#define POS_CONTINUE_Y			(240.0f)	//�ʒu(Y)
#define MAX_OFFSET_CONTINUE_X	(250.0f)	//�傫��(��)
#define MAX_OFFSET_CONTINUE_Y	(50.0f)		//�傫��(����)

//************************************************************
//�R���e�B�j���[�̍\���̂��`
//************************************************************
typedef struct
{
	D3DXVECTOR3 pos;							//���S�_
	D3DXVECTOR3 offset;							//���S�_����̍�
	D3DXVECTOR3 rot;							//����
	D3DXCOLOR col;								//�J���[
	float fLength;								//�Ίp���̒���
	float fAngele;								//�Ίp���̊p�x
	bool bUse;									//�g�p���Ă邩�ǂ���
}Continue;

//****************************************
//�v���g�^�C�v�錾
//****************************************
void InitContinue(void);
void UninitContinue(void);
void UpdateContinue(void);
void DrawContinue(void);
void SetContinue(void);

#endif