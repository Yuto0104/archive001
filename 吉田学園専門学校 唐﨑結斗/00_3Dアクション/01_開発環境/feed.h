//**************************************************************************************************
//
// �a����(feed.h)
// Auther�F�������l
//
//**************************************************************************************************
#ifndef _FEED_H_			// ���̃}�N����`������ĂȂ�������
#define _FEED_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include"main.h"

//***************************************************************************
// �}�N����`
//***************************************************************************
#define	MAX_FEED			(1280)		// �a���̍ő吔
#define	MAX_FEED_NAME		(128)		// �a���̍ő吔

//***************************************************************
// �a�t�@�C���\���̂��`
//***************************************************************
typedef struct
{
	char	aName[MAX_FEED_NAME];		// ���O
}FeedFile;

//***************************************************************
// �a�\���̂��`
//***************************************************************
typedef struct
{
	LPD3DXMESH		pMesh;			// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER	pBuffer;		// �}�e���A�����ւ̃|�C���^
	DWORD			nNumMat;		// �}�e���A�����̐�
	D3DXMATRIX		mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXVECTOR3		pos;			// �ʒu
	D3DXVECTOR3		posOld;			// �ߋ��ʒu
	D3DXVECTOR3		rot;			// ���݂̌���
	D3DXVECTOR3		rotDest;		// �ړI�̌���
	D3DXVECTOR3		move;			// �ړ���
	D3DXVECTOR3		joinVec;		// �����x�N�g��
	D3DXVECTOR3		leaveVec;		// �����x�N�g��
	D3DXVECTOR3		averageVec;		// ���σx�N�g��
	D3DXVECTOR3		vtxMin;			// ���_���W�̍ŏ��l
	D3DXVECTOR3		vtxMax;			// ���_���W�̍ő�l
	int				nIdx;			// �C���f�b�N�X
	int				nGroup;			// �O���[�v�ԍ�
	int				nIdxLeader;		// ���[�_�[�̔ԍ�(���[�_�����Ȃ��ꍇ-1)
	int				nCntJoinTime;	// ���[�_�[�{���܂ł̎���
	int				nCntMoveTime;	// �ړ��ʎZ�o�܂ł̎���
	float			fJoinRot;		// ��������
	float			fLeaveRot;		// ��������
	float			fSpeed;			// �ړ����x
	bool			bUse;			// �g�p��
	bool			bSearchIn;		// ����p���ɂ��邩�ǂ���
	bool			bEscape;		// �����Ă��邩�ǂ���
}Feed;

//***************************************************************
// �v���g�^�C�v�錾
//***************************************************************
// ����֐�
void InitFeed(void);
void UninitFeed(void);
void UpdateFeed(void);
void DrawFeed(void);

// ���͊֐�
void MoveFeed(int nCnt);
void RotateFeed(int nCnt);
void CollisionFeed(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *vtx, D3DXVECTOR3 *vtxOld);
void SearchLeader(int nCnt);
void LeaveFeed(int nCnt);
void AverageFeed(int nCnt);
void SetFeed(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void RandSetFeed(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSetRot, float fSetLength, int nNumSet);
void LeavePlayer(int nCnt);
void SetControllerFeed(void);

// �o�͊֐�
Feed *GetFeed(void);
FeedFile *GetFeedFile(void);
int GetCntFeed(void);

#endif

