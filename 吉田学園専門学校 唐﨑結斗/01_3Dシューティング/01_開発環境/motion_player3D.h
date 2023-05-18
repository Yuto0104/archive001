//=============================================================================
//
// 3D���[�V�����v���C���[�N���X(motion_player3D.h)
// Author : �������l
// �T�v : 3D���[�V�����v���C���[�������s��
//
//=============================================================================
#ifndef _MOTION_PLAYER3D_H_			// ���̃}�N����`������ĂȂ�������
#define _MOTION_PLAYER3D_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "model3D.h"
#include "main.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CMotion;
class CMove;
class CEffect3D;

//=============================================================================
// 3D���[�V�����v���C���[�N���X
// Author : �������l
// �T�v : 3D���[�V�����v���C���[�������s���N���X
//=============================================================================
class CMotionPlayer3D : public CModel3D
{
public:
	//--------------------------------------------------------------------
	// �萔��`
	//--------------------------------------------------------------------
	static const float				ROTATE_SPEED;
	static const unsigned int		MAX_CNT_SHOT = 15;			// �e���˂܂ł̃J�E���g
	static const unsigned int		MAX_MOTION = 2;				// ���[�V�����̃J�E���g
	static const unsigned int		MAX_LIFE = 5;				// ���C�t�̍ő�l
	static const unsigned int		MAX_ENERGY = 100;			// �G�l���M�[�̍ő�
	static const unsigned int		MAX_CNT_RECOVERY = 60;		// �񕜂܂ł̃J�E���g
	static const unsigned int		ENERGY_RECOVERY = 20;		// �񕜂ɏ����G�l���M�[
	static const unsigned int		ENERGY_FOLLOW_SHOT = 10;	// �Ǐ]�e���˂ɏ����G�l���M�[
	static const unsigned int		INVINCIBLE_TIME = 20;		// ���G����

	//=============================================================================
	// ���[�V�����̃^�C�v�񋓌^
	// Author : �������l
	// �T�v : ���[�V�����̎��
	//=============================================================================
	enum MOTION_TYPE
	{
		TYPE_NEUTRAL = 0,			// �j���[�g�������[�V����
		TYPE_MOVE,					// �ړ����[�V����
		TYPE_ATTACK,				// �U�����[�V����
		MAX_MOTION_TYPE,			// �^�C�v�̍ő吔
	};

	//=============================================================================
	// ��Ԃ̗񋓌^
	// Author : �������l
	// �T�v : ��Ԃ̎��
	//=============================================================================
	enum STATE
	{
		STATE_NEUTRAL = 0,			// �ʏ���
		STATE_DAMAGE,				// �_���[�W���
		MAX_STATE,					// ��Ԃ̍ő吔
	};

	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CMotionPlayer3D *Create();			// 3D���[�V�����v���C���[�̐���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CMotionPlayer3D();
	~CMotionPlayer3D();

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init() override;								// ������
	void Uninit() override;									// �I��
	void Update() override;									// �X�V
	void Draw() override;									// �`��
	void Hit();												// �_���[�W
	void Charge(const int nEnergy);							// �G�l���M�[�z��
	int GetLife() { return m_nLife; }						// �̗͂̃Q�b�^�[
	int GetInvalidLife() { return m_nInvalidLife; }			// �ǉ��̗͂̃Q�b�^�[
	
private:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void Rotate();								// ��]
	D3DXVECTOR3 Move();							// �ړ�
	void Shot();								// �e�̔���
	void CollisionScreen();						// �X�N���[���̂����蔻��
	void ChangeColor();							// �F�̕ύX
	void MotionSet();							// ���[�V�����̐ݒ�
	void Recovery();							// ��
	void FollowShot();							// �Ǐ]�e�̔���
	void Consumption();							// �G�l���M�[����
	void SetState();							// ��Ԃ̐���
	void CollisionEnemy();						// �G�Ƃ̓����蔻��
	void Death();								// ���S����

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	CMotion			*m_pMotion[MAX_MOTION];			// ���[�V�����C���X�^���X
	CMove			*m_pMove;						// �ړ��N���X�̃C���X�^���X
	CEffect3D		*m_pEffect3D;					// �G�t�F�N�g�̃C���X�^���X
	D3DXVECTOR3		m_rotDest;						// �ړI�̌���
	STATE			m_state;						// ���
	int				m_nCntShot;						// �e���˂܂ł̃J�E���g
	int				m_nNumMotion;					// ���݂̃��[�V�����ԍ�
	int				m_nNumMotionOld;				// �ߋ��̃��[�V�����ԍ�
	int				m_nLife;						// ����
	int				m_nInvalidLife;					// �ǉ����C�t
	int				m_nEnergy;						// �G�l���M�[
	int				m_nCntConsumption;				// �G�l���M�[����J�E���g
	int				m_nCombo;						// �R���{
	int				m_nCntState;					// ��Ԑ���̃J�E���g
	int				m_nCntFrame;					// �t���[���J�E���g
	bool			m_bMotion;						// ���[�V�����̎g�p��
	bool			m_bMotionBlend;					// ���[�V�����u�����h�̎g�p��
	bool			m_bPressShot;					// �������e���g�p���Ă邩�ǂ���
	bool			m_bLockShot;					// �e���˂��\���ǂ���
	bool			m_bPressConsumption;			// �G�l���M�[����Ă邩�ǂ���
	bool			m_bLockConsumption;				// �G�l���M�[����\���ǂ���
	bool			m_bRecovery;					// �񕜂��s�������ǂ���
	bool			m_bFollowShot;					// �Ǐ]�e�𔭎˂��Ă��邩��
	bool			m_bUse;							// �g�p��
};

#endif