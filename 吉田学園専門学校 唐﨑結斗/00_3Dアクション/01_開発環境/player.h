//**************************************************************************************************
//
// �v���C���[����(Player.h)
// Auther�F�������l
//
//**************************************************************************************************
#ifndef _Player_H_			// ���̃}�N����`������ĂȂ�������
#define _Player_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include"main.h"

//***************************************************************************
// �}�N����`
//***************************************************************************
#define	MAX_MODEL_PARTS				(128)				// ���f�����̍ő吔
#define MAX_KEY						(64)				// �L�[�̍ő吔
#define MAX_KEYSET					(64)				// �L�[�ݒ�̍ő吔
#define DASH_STAMINA				(20)				// �_�b�V���̏���X�^�~�i

//**********************************************************
// ���[�V�������[�h�̗񋓌^
//**********************************************************
typedef enum
{
	NEUTRAL_MOTION = 0,			// �j���[�g�������[�V����
	MOVE_MOTION,				// �ړ����[�V����
	MAX_MOTION_STATE			// ���[�V�����X�e�C�g�̍ő吔
}MotionState;

//**********************************************************
// �v���C���[��Ԃ̗񋓌^
//**********************************************************
typedef enum
{
	NORMAL_STATE = 0,			// �ʏ���
	DASH_STATE,					// �_�b�V�����
	MAX_PLAYER_STATE			// ���[�V�����X�e�C�g�̍ő吔
}PlayerState;

//***************************************************************
// �v���C���[�t�@�C���\���̂��`
//***************************************************************
typedef struct
{
	char	aName[MAX_MODEL_PARTS];		// ���O
}PlayerFile;

//***************************************************************
// �L�[�\���̂��`
//***************************************************************
typedef struct
{
	D3DXVECTOR3		pos;	// ���݈ʒu
	D3DXVECTOR3		rot;	// ���݂̌���
}Key;

//***************************************************************
// �L�[�ݒ�\���̂��`
//***************************************************************
typedef struct
{
	int		nFrame;				// �t���[����
	Key		key[MAX_KEY];		// �L�[���
}KeySet;

//***************************************************************
// ���[�V�����ݒ�\���̂��`
//***************************************************************
typedef struct
{
	int			nNumKey;				// �L�[��
	int			nCntKeySet;				// �L�[�Z�b�g�J�E���g
	int			nCntFrame;				// �t���[���J�E���g
	bool		bLoop;					// ���[�v�g�p��
	KeySet		keySet[MAX_KEYSET];		// �L�[�ݒ���
}MotionSet;

//***************************************************************
// ���f���p�[�c�\���̂��`
//***************************************************************
typedef struct
{
	LPD3DXMESH		pMesh;					// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER	pBuffer;				// �}�e���A�����ւ̃|�C���^
	DWORD			nNumMat;				// �}�e���A�����̐�
	D3DXMATRIX		mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3		posOrigin;				// ���̈ʒu
	D3DXVECTOR3		rotOrigin;				// ���̌���
	D3DXVECTOR3		pos;					// ���݂̈ʒu
	D3DXVECTOR3		rot;					// ���݂̌���
	D3DXVECTOR3		posDest;				// �ړI�̈ʒu
	D3DXVECTOR3		rotDest;				// �ړI�̌���
	D3DXVECTOR3		vtxMin;					// ���_���W�̍ŏ��l
	D3DXVECTOR3		vtxMax;					// ���_���W�̍ő�l
	int				nIdxModelParent;		// �e���f���̃C���f�b�N�X��
	int				nType;					// �p�[�c�̃^�C�v
}ModelParts;

//***************************************************************
// �v���C���[�\���̂��`
//***************************************************************
typedef struct
{
	D3DXVECTOR3		pos;							// ���݈ʒu
	D3DXVECTOR3		posOld;							// �ߋ��ʒu
	D3DXVECTOR3		rot;							// ���݂̌���
	D3DXVECTOR3		rotDest;						// �ړI�̌���
	D3DXVECTOR3		vtxMin;							// ���_���W�̍ŏ��l
	D3DXVECTOR3		vtxMax;							// ���_���W�̍ő�l
	D3DXVECTOR3		size;							// �傫��
	D3DXVECTOR3		attackPos;						// �U������̈ʒu
	D3DXMATRIX		mtxWorld;						// ���[���h�}�g���b�N�X
	ModelParts		modeParts[MAX_MODEL_PARTS];		// ���f���p�[�c
	MotionState		MotionState;					// ���[�V�����X�e�C�g
	PlayerState		PlayerState;					// �v���C���[�̏��
	int				nMaxModelType;					// ���f���̃^�C�v��
	int				nMaxModelParts;					// �������f���p�[�c��
	int				nMaxMotion;						// ���[�V������
	int				nIdx;							// �C���f�b�N�X
	int				nCntNotMove;					// �����Ȃ�������
	int				nCntComboTime;					// �R���{���Z����
	int				nCntCombo;						// �R���{�J�E���g
	int				nMaxCombo;						// �R���{�̍ő吔
	int				nCntState;						// ��ԃJ�E���g
	int				nStamina;						// �X�^�~�i
	int				nMaxStamina;					// �X�^�~�i�̍ő�l
	float			fAttackRadius;					// �U������̔��a
	float			fSpeed;							// �ړ����x
	float			fMoveDistance;					// �ړ�����
	bool			bUse;							// �g�p��
}Player;

//***************************************************************
// �v���g�^�C�v�錾
//***************************************************************
// ����֐�
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

// ���͊֐�
void MovePlayer(void);
void RotatePlayer(void);
void SetPlayer(D3DXVECTOR3 pos, 
	D3DXVECTOR3 rot,
	int	nMaxModelType,
	int	nMaxMotion);
void MotionPlayer(int nCntMotionSet);
void MotionBlend(int nCntMotionSet);
bool SearchPlayer(D3DXVECTOR3 *pos);
bool EatPlayer(D3DXVECTOR3 *pos, D3DXVECTOR3 size);
bool CollisionPlayer(D3DXVECTOR3 *vtx);
void DashPlayer(void);

// �o�͊֐�
Player *GetPlayer(void);
PlayerFile *GetPlayerFile(void);
MotionSet *GetMotionSet(void);

#endif

