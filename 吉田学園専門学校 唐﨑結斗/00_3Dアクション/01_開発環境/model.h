//**************************************************************************************************
//
// ���f������(model.h)
// Auther�F�������l
//
//**************************************************************************************************
#ifndef _MODEL_H_			// ���̃}�N����`������ĂȂ�������
#define _MODEL_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include"main.h"

//***************************************************************************
// �}�N����`
//***************************************************************************
#define	MAX_MODEL			(128)		// ���f�����̍ő吔
#define	MAX_MODEL_NAME		(128)		// ���f�����̍ő吔

//***************************************************************
// ���f���t�@�C���\���̂��`
//***************************************************************
typedef struct
{
	char	aName[MAX_MODEL_NAME];		// ���O
}ModelFile;

//***************************************************************
// ���f���\���̂��`
//***************************************************************
typedef struct
{
	LPD3DXMESH		pMesh;			// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER	pBuffer;		// �}�e���A�����ւ̃|�C���^
	DWORD			nNumMat;		// �}�e���A�����̐�
	D3DXMATRIX		mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXVECTOR3		pos;			// �ʒu
	D3DXVECTOR3		rot;			// ���݂̌���
	D3DXVECTOR3		rotDest;		// �ړI�̌���
	D3DXVECTOR3		vtxMin;			// ���_���W�̍ŏ��l
	D3DXVECTOR3		vtxMax;			// ���_���W�̍ő�l
	int				nType;			// �^�C�v
	int				nIdx;			// �C���f�b�N�X
	bool			bUse;			// �g�p��
}Model;

//***************************************************************
// �v���g�^�C�v�錾
//***************************************************************
// ����֐�
void	InitModel		(void);
void	UninitModel		(void);
void	UpdateModel		(void);
void	DrawModel		(void);

// ���͊֐�
void	MoveModel		(int nCnt);
void	RotateModel		(int nCnt);
bool	CollisionModel(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *vtx, D3DXVECTOR3 *vtxOld);
void	SetModel		(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);

// �o�͊֐�
Model		*GetModel		(void);
ModelFile	*GetModelFile	(void);

#endif
