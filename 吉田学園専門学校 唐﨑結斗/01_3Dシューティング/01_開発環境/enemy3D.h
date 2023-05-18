//=============================================================================
//
// 3D�G�l�~�[�N���X(enemy3D.h)
// Author : �������l
// �T�v : 3D�G�l�~�[�������s��
//
//=============================================================================
#ifndef _ENEMY3D_H_			// ���̃}�N����`������ĂȂ�������
#define _ENEMY3D_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"
#include "model3D.h"
#include "main.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CEffect3D;

//=============================================================================
// 3D�G�l�~�[�N���X
// Author : �������l
// �T�v : 3D�G�l�~�[�������s���N���X
//=============================================================================
class CEnemy3D : public CModel3D
{
public:
	//--------------------------------------------------------------------
	// �萔��`
	//--------------------------------------------------------------------
	static const unsigned int MAX_LINTERN_BULLET = 5;			// �Ԃ��e�̍ő吔
	static const float LINTERN_BULLET_SPAWN_RANGE;				// �Ԃ��e�̐����͈�
	static const float LINTERN_BULLET_MOVE_VEC;					// �Ԃ��e�̈ړ�����

	//--------------------------------------------------------------------
	// �ړ����@�̎��
	// Author : �������l
	// �T�v : �ړ����@�̎�ʕ������s��
	//--------------------------------------------------------------------
	enum MOVE_MODE
	{
		MODE_NORMAL = 0,		// �ʏ�ړ�
		MODE_SIN,				// �T�C���J�[�u
		MODE_COS,				// �R�T�C���J�[�u
		MODE_CIRCLE,			// �~�ړ�
		MODE_NONE,				// �ړ����Ȃ�
		MAX_MODE,				// �ړ����@�̍ő吔
	};

	//--------------------------------------------------------------------
	// ���˂���e�̎��
	// Author : �������l
	// �T�v : ���˂���e�̎�ʕ������s��
	//--------------------------------------------------------------------
	enum SHOT_MODE
	{
		SHOTMODE_NORMAL = 0,		// �ʏ�
		SHOTMODE_DIFFUSION,			// �g�U
		SHOTMODE_SNIPE,				// �X�i�C�v
		SHOTMODE_FOLLOW,			// �Ǐ]
		SHOTMODE_NONE,				// �e����
		SHOTMAX_MODE,				// �ړ����@�̍ő吔
	};

	//--------------------------------------------------------------------
	// �G�̈ړ��L�[
	// Author : �������l
	// �T�v : �G�̈ړ��L�[�ݒ�
	//--------------------------------------------------------------------
	struct ENEMY_MOVE_KEY
	{
		MOVE_MODE		moveMode;			// �ړ����@
		float			fSpeed;				// �ړ����x
		float			fMoveVec;			// �ړ�����
		float			fAddMoveVec;		// �ړ������̉��Z�l
		float			fWaveLength;		// �g��
		float			fWaveSize;			// �g�̑傫��
		int				nFrame;				// �ړ����s������
	};

	//--------------------------------------------------------------------
	// �G�̈ړ�
	// Author : �������l
	// �T�v : �G�̈ړ��ݒ�
	//--------------------------------------------------------------------
	struct ENEMY_MOVE
	{
		ENEMY_MOVE_KEY		*moveKey;		// �ړ��L�[
		int					nMaxKey;		// �ő�L�[��
		bool				bLoop;			// ���[�v���邩�ǂ���
	};

	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CEnemy3D *Create(const int nNumModel);				// 3D�G�l�~�[�̐���
	static int GetCntSetEnemy() { return s_nCntSetEnemy; }		// �ݒu����Ă���G�̐��̃J�E���g

	//--------------------------------------------------------------------
	// �ÓI�����o�ϐ�
	//--------------------------------------------------------------------
	static int s_nCntSetEnemy;			// �G�̃J�E���g

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CEnemy3D();
	~CEnemy3D();

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init(const int nNumModel);																// ������
	void Uninit() override;																			// �I��
	void Update() override;																			// �X�V
	void Draw() override;																			// �`��
	void Hit(COLOR_TYPE colorType, int nAttack);													// �q�b�g
	void SetLife(int nLife) { m_nLife = nLife; }													// �̗͂̃Z�b�^�[
	void SetScore(int nScore) { m_nScore = nScore; }												// �X�R�A�̃Z�b�^�[
	void SetMoveData(const ENEMY_MOVE moveData);													// �ړ����̃Z�b�^�[
	void SetShotMode(const SHOT_MODE _shotMode) { m_shotMode = _shotMode; }							// �e�̎�ʂ̃Z�b�^�[
	void SetMaxShot(const int nMaxShot) { m_nMaxShot = nMaxShot; }									// �e�̔��˃J�E���g�̐ݒ�
	void SetBulletRot(const float fBulletRot) { m_fBulletRot = fBulletRot; }						// �e�̔��˕����̐ݒ�
	void SetDiffusionWidth(const float fDiffusionWidth) { m_fDiffusionWidth = fDiffusionWidth; }	// �e�̊g�U�͈͂̐ݒ�
	void SetBulletSpeed(const float fBulletSpeed) { m_fBulletSpeed = fBulletSpeed; }				// �e�̔��ˑ��x�̐ݒ�
	void SetCoeffBullet(const float fCoeffBullet) { m_fCoeffBullet = fCoeffBullet; }				// �Ǐ]�e�̌����W���̐ݒ�
	void SetMaxBullet(const int nMaxBullet) { m_nMaxBullet = nMaxBullet; }							// �e�̍ő唭�ː�

private:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void Shot();			// �e�̔���
	void SetMove();			// �ړ��ʂ̐ݒ�
	void Move();			// �ړ����̊Ǘ�
	void SetMoveCopy();		// �ړ����̑��
	void ScreenIn();		// �X�N���[���̔���

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	CEffect3D		*m_pEffect3D;		// �G�t�F�N�g�̃C���X�^���X
	D3DXVECTOR3		m_move;				// �ړ���
	ENEMY_MOVE		m_moveData;			// �ړ����
	MOVE_MODE		m_moveMode;			// �ړ����@
	SHOT_MODE		m_shotMode;			// �e�̎��
	float			m_fSpeed;			// �ړ����x
	float			m_fMoveVec;			// �ړ�����
	float			m_fAddMoveVec;		// �ړ������̉��Z�l
	float			m_fWave;			// �g
	float			m_fWaveLength;		// �g��
	float			m_fWaveSize;		// �g�̑傫��
	float			m_fBulletRot;		// �e�̔��˕���
	float			m_fDiffusionWidth;	// �e�̊g�U�͈�
	float			m_fBulletSpeed;		// �e��
	float			m_fCoeffBullet;		// �e�̒Ǐ]�̌����W��
	int				m_nMaxBullet;		// �e�̔��ː�
	int				m_nCntKey;			// �L�[�J�E���g
	int				m_nCntFrame;		// �t���[���J�E���g
	int				m_nLife;			// �̗�
	int				m_nScore;			// �X�R�A
	int				m_nCntShot;			// �e���˂܂ł̃J�E���g
	int				m_nMaxShot;			// �e���˂���J�E���g
	bool			m_bMove;			// �ړ����s���Ă���
	bool			m_bUse;				// �g�p����Ă��邩�ǂ���
};

#endif
