//**************************************************************************************************
//
//�X�R�A�̏���
//Auther�F�������l
//
//**************************************************************************************************
#ifndef _SCORE_H_		//���̃}�N����`������ĂȂ�������
#define _SCORE_H_		//��d�C���N�\���[�h�h�~�̃}�N����`

//*************************************************************
//�}�N����`
//*************************************************************
#define MAX_DIGITS		(8)			//�X�R�A�̌���
#define MAX_VERTEX		(4)			//���_�̍ő吔

//************************************************************
//�X�R�A�\���̂��`
//************************************************************
typedef struct
{
	D3DXVECTOR3 pos[MAX_DIGITS];			//���S�_
	D3DXVECTOR3 offset;						//���S�_����̍�
	D3DXVECTOR3 rot;						//����
	D3DXCOLOR col;							//�J���[
	float fLength;							//�Ίp���̒���
	float fAngele;							//�Ίp���̊p�x
	int nScore;								//�X�R�A
}Score;

//****************************************
//�v���g�^�C�v�錾
//****************************************
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore, D3DXVECTOR3 pos, D3DXVECTOR3 offset);
void AddScore(int nValue);
int GetScore(void);

#endif