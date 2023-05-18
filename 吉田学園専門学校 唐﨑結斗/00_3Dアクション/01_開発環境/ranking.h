//**************************************************************************************************
//
//�����L���O�̐ݒ菈��
//Auther�F�������l
//
//**************************************************************************************************
#ifndef _RANKING_H_		//���̃}�N����`������ĂȂ�������
#define _RANKING_H_		//��d�C���N�\���[�h�h�~�̃}�N����`

#include"main.h"

#include"file.h"

//*************************************************************
//�}�N����`
//*************************************************************
#define MAX_RANK						(5)						// �����L���O�����N�̍ő吔
#define MAX_RANK_DIGITS					(8)						// �����L���O�X�R�A�̌���
#define POS_RANK_X						(360.0f)				// �����L���O�����N�ʒu(X)
#define POS_RANK_Y						(220.0f)				// �����L���O�����N�ʒu(Y)
#define MAX_OFFSET_RANK_X				(100.0f)				// �����L���O�����N�傫��(��)
#define MAX_OFFSET_RANK_Y				(60.0f)					// �����L���O�����N�傫��(����)
#define POS_RANKING_SCORE_X				(950.0f)				// �����L���O�X�R�A�ʒu(X)
#define MAX_OFFSET_RANKING_SCORE_X		(30.0f)					// �����L���O�X�R�A�傫��(��)
#define MAX_OFFSET_RANKING_SCORE_Y		(60.0f)					// �����L���O�X�R�A�傫��(����)
#define INTERVAL_FLASHING				(3)						// �X�V�X�R�A�̓_�ŕp�x
#define MAX_TIME						(600)					// �����L���O�\������
#define FILE_RANKING_NAME000			"ranking_score.txt"		// �����L���O�t�@�C����(txt)
#define FILE_RANKING_NAME001			"ranking_score.bin"		// �����L���O�t�@�C����(bin)


//************************************************************
//�����L���O�����N�̍\���̂��`
//************************************************************
typedef struct
{
	D3DXVECTOR3 pos;							//���S�_
	D3DXVECTOR3 offset;							//���S�_����̍�
	D3DXVECTOR3 rot;							//����
	D3DXCOLOR col;								//�J���[
	float fLength;								//�Ίp���̒���
	float fAngele;								//�Ίp���̊p�x
}Rank;

//************************************************************
//�����L���O�X�R�A�̍\���̂��`
//************************************************************
typedef struct
{
	D3DXVECTOR3 pos[MAX_RANK_DIGITS];			//���S�_
	D3DXVECTOR3 offset;							//���S�_����̍�
	D3DXVECTOR3 rot;							//����
	D3DXCOLOR col;								//�J���[
	float fLength;								//�Ίp���̒���
	float fAngele;								//�Ίp���̊p�x
	int nScore;									//�X�R�A�̒l
}RankingScore;

//****************************************
//�v���g�^�C�v�錾
//****************************************
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void ResetRanking(void);
void SetRanking(int nScore);

#endif
