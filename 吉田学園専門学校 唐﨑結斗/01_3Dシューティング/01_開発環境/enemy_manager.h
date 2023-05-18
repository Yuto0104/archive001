//=============================================================================
//
// �G�l�~�[�}�l�[�W���[����(enemy_manager.h)
// Author : �������l
// �T�v : �G�l�~�[�}�l�[�W���[���s��
//
//=============================================================================
#ifndef _ENEMY_MANAGER_H_		// ���̃}�N����`������ĂȂ�������
#define _ENEMY_MANAGER_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"
#include "enemy3D.h"

//=============================================================================
// �G�l�~�[�}�l�[�W���[�N���X
// Author : �������l
// �T�v : �G�l�~�[�}�l�[�W���[���s���N���X
//=============================================================================
class CEnemyManager : public CObject
{
public:
	//--------------------------------------------------------------------
	// �G�̎�ʂ̗񋓌^
	// Author : �������l
	// �T�v : �G�̎�ʕ���������
	//--------------------------------------------------------------------
	enum EENEMY_MOVE_TYPE
	{
		TYPE_NORMAL = 0,		// �ʏ�
		MAX_TYPE,				// ��ʐ��̍ő吔
	};

	//--------------------------------------------------------------------
	// �G�̃X�e�[�^�X
	// Author : �������l
	// �T�v : �G�̃X�e�[�^�X
	//--------------------------------------------------------------------
	struct ENEMY_STATUS
	{
		COLOR_TYPE				colorType;				// �J���[�^�C�v
		CEnemy3D::SHOT_MODE		shotMode;				// �e�̎��
		D3DXVECTOR3				collisionSize;			// �����蔻��̑傫��
		D3DXVECTOR3				size;					// �傫��
		float					fBulletRot;				// �e�̔��˕���
		float					fDiffusionWidth;		// �e�̊g�U�͈�
		float					fBulletSpeed;			// �e��
		float					fCoeffBullet;			// �e�̒Ǐ]�̌����W��
		int						nMaxBullet;				// �e�̔��ː�
		int						nModelID;				// ���f��ID
		int						nLife;					// �̗�
		int						nScore;					// �X�R�A
		int						nMaxShot;				// �e���˂���J�E���g
	};

	//--------------------------------------------------------------------
	// �G�̔z�u���
	// Author : �������l
	// �T�v : �G�̔z�u���
	//--------------------------------------------------------------------
	struct ENEMY_ARRANGEMENT
	{
		D3DXVECTOR3			pos;			// �ʒu
		int					nMoveID;		// �ړ������i�[
		int					nFrame;			// �G�l�~�[�̔����t���[����
		int					nID;			// ���ʔԍ�
		int					nDrawType;		// �`��^�C�v
		EENEMY_MOVE_TYPE	type;			// ���
	};

	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CEnemyManager *Create();			// �G�l���M�[�Q�[�W�̐���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CEnemyManager();
	~CEnemyManager() override;

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init() override;														// ������
	void Uninit() override;															// �I��
	void Update() override;															// �X�V
	void Draw() override;															// �`��
	void SetPos(const D3DXVECTOR3 &pos) override { pos; }							// �ʒu�̃Z�b�^�[
	void SetPosOld(const D3DXVECTOR3 &posOld) override { posOld; }					// �ߋ��ʒu�̃Z�b�^�[
	void SetRot(const D3DXVECTOR3 &rot) override { rot; }							// �����̃Z�b�^�[
	void SetSize(const D3DXVECTOR3 &size) override { size; }						// �傫���̃Z�b�^�[
	D3DXVECTOR3 GetPos() override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }			// �ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetPosOld()  override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		// �ߋ��ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetRot()  override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		// �����̃Q�b�^�[
	D3DXVECTOR3 GetSize()  override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		// �傫���̃Q�b�^�[
	int GetCntFrame() { return m_nCntFrame; }										// �t���[�����̃Q�b�^�[
	void LoadFile(char *pFileName);

private:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void SetEnemy();

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	D3DXVECTOR3				m_pos;					// �ʒu
	D3DXVECTOR3				m_posOld;				// �ߋ��̈ʒu
	D3DXVECTOR3				m_rot;					// ����
	D3DXVECTOR3				m_size;					// �傫��
	ENEMY_STATUS			*m_status;				// �G�̃X�e�[�^�X
	ENEMY_ARRANGEMENT		*m_arrangement;			// �G�̔z�u
	CEnemy3D::ENEMY_MOVE	*m_move;				// �ړ����
	int						m_nMaxType;				// ��ނ̍ő吔
	int						m_nMaxInstall;			// �ő�ݒu��
	int						m_nMaxMove;				// �ړ����
	int						m_nGameEndFrame;		// �Q�[���̏I������
	int						m_nCntFrame;			// �t���[���J�E���g
	int						m_nCntSetEnemy;			// �G�̐ݒu�J�E���g
};

#endif
