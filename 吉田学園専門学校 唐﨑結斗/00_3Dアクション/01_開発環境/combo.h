//**************************************************************************************************
//
// �R���{�̏���
// Auther�F�������l
//
//**************************************************************************************************
#ifndef _COMBO_H_		// ���̃}�N����`������ĂȂ�������
#define _COMBO_H_		// ��d�C���N�\���[�h�h�~�̃}�N����`

#include"main.h"

//*************************************************************
// �}�N����`
//*************************************************************
#define MAX_COMBO_DIGITS		(3)			// �R���{�̌���
#define MAX_VERTEX				(4)			// ���_�̍ő吔

//************************************************************
// �R���{�\���̂��`
//************************************************************
typedef struct
{
	D3DXVECTOR3		pos[MAX_COMBO_DIGITS];		// ���S�_
	D3DXVECTOR3		offset;						// ���S�_����̍�
	D3DXVECTOR3		rot;						// ����
	D3DXCOLOR		col;						// �J���[
	float			fLength;					// �Ίp���̒���
	float			fAngele;					// �Ίp���̊p�x
	int				nCombo;						// �R���{
	bool			bUse;						// �g�p��
}Combo;

//****************************************
//�v���g�^�C�v�錾
//****************************************
void InitCombo(void);
void UninitCombo(void);
void UpdateCombo(void);
void DrawCombo(void);
void SetCombo(int nCombo, D3DXVECTOR3 pos, D3DXVECTOR3 offset);
void AddCombo(int nCombo);
int GetCombo(void);

#endif
