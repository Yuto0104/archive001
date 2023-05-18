//=============================================================================
//
// �I�u�W�F�N�g�N���X(object.h)
// Author : �������l
// �T�v : �I�u�W�F�N�g�������s��
//
//=============================================================================
#ifndef _OBJECT_H_		// ���̃}�N����`������ĂȂ�������
#define _OBJECT_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"

//=============================================================================
// �I�u�W�F�N�g�N���X
// Author : �������l
// �T�v : �I�u�W�F�N�g�������s���N���X
//=============================================================================
class CObject
{
public:
	//--------------------------------------------------------------------
	// �F�̎�ʐݒ�
	// Author : �������l
	// �T�v : ���������𕪂�����
	//--------------------------------------------------------------------
	enum COLOR_TYPE
	{
		TYPE_NONE = 0,		// ��ʖ���
		TYPE_WHITE,			// ��
		TYPE_BLACK,			// ��
		MAX_TYPE,			// ��ʂ̍ő�
	};

	//--------------------------------------------------------------------
	// �I�u�W�F�N�g�̎�ʂ̗񋓌^
	// Author : �������l
	// �T�v : �I�u�W�F�N�g�̎�ʏ����i�[
	//--------------------------------------------------------------------
	enum EObjectType
	{
		OBJTYPE_NONE = 0,			// �^�C�v����
		OBJTYPE_2DPOLYGON,			// 2D�|���S��
		OBJTYPE_2DPLAYER,			// �v���C���[
		OBJTYPE_2DBULLET,			// �o���b�g
		OBJTYPE_2DENEMY,			// �G�l�~�[
		OBJTYPE_2DEXPLOSION,		// ����
		OBJTYPE_3DPLAYER,			// 3D�v���C���[
		OBJTYPE_3DENEMY,			// 3D�G�l�~�[
		OBJTYPE_3DBOSS,				// 3D�{�X
		OBJTYPE_3DBULLET,			// 3D�o���b�g
		OBJTYPE_FADE,				// �t�F�[�h
		OBJTYPE_PAUSE,				// �|�[�Y
		MAX_OBJTYPE,				// ��ʂ̍ő吔
	};

	//--------------------------------------------------------------------
	// �I�u�W�F�N�g�̕`����@�̗񋓌^
	// Author : �������l
	// �T�v : �I�u�W�F�N�g�̕`����@�����i�[
	//--------------------------------------------------------------------
	enum EObjectDrowType
	{
		DROWTYPE_GAME = 0,			// �Q�[���`��
		DROWTYPE_BG,				// �w�i�`��
		MAX_DROWTYPE,				// ��ʂ̍ő吔
	};

	//--------------------------------------------------------------------
	// �v���C�I���e�B�̃��x��
	// Author : �������l
	// �T�v : �v���C�I���e�B�̃��x����ݒ�
	//--------------------------------------------------------------------
	enum PRIORITY_LEVEL
	{
		PRIORITY_LEVEL0 = 0,	// ���x��0
		PRIORITY_LEVEL1,		// ���x��1
		PRIORITY_LEVEL2,		// ���x��2
		PRIORITY_LEVEL3,		// ���x��3
		PRIORITY_LEVEL4,		// ���x��4
		MAX_LEVEL				// �ő僌�x��
	};

	//--------------------------------------------------------------------
	// �萔��`
	//--------------------------------------------------------------------
	static const unsigned int MAX_OBJECT = (0x1000) / MAX_LEVEL;

	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static void ReleaseAll(void);																						// ���ׂẴI�u�W�F�N�g�̉��
	static void ReleaseScene(void);																						// �J�ڂ̃I�u�W�F�N�g�̉��
	static void UpdateAll(void);																						// ���ׂẴI�u�W�F�N�g�̍X�V
	static void DrawAll(EObjectDrowType objectDrowType);																// ���ׂẴI�u�W�F�N�g�̕`��
	static CObject *MyGetObject(const int nPriority, const int nNumID) { return m_apObject[nPriority][nNumID]; }		// �I�u�W�F�N�g���̃Q�b�^�[
	static void SetPause(const bool bPause) { m_bPause = bPause; }														// �|�[�Y��Ԃ̃Z�b�^�[

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CObject(int nPriority = PRIORITY_LEVEL0);
	virtual ~CObject();

	//--------------------------------------------------------------------
	// �������z�֐�
	//--------------------------------------------------------------------
	virtual HRESULT Init() = 0;																			// ������
	virtual void Uninit() = 0;																			// �I��
	virtual void Update() = 0;																			// �X�V
	virtual void Draw() = 0;																			// �`��
	virtual void SetPos(const D3DXVECTOR3 &pos) = 0;													// �ʒu�̃Z�b�^�[
	virtual void SetPosOld(const D3DXVECTOR3 &posOld) = 0;												// �ߋ��ʒu�̃Z�b�^
	virtual void SetRot(const D3DXVECTOR3 &rot) = 0;													// �����̃Z�b�^�[
	virtual void SetSize(const D3DXVECTOR3 &size) = 0;													// �傫���̃Z�b�^�[
	virtual D3DXVECTOR3 GetPos() = 0;																	// �ʒu�̃Q�b�^�[
	virtual D3DXVECTOR3 GetPosOld() = 0;																// �ߋ��ʒu�̃Q�b�^
	virtual D3DXVECTOR3 GetRot() = 0;																	// �����̃Q�b�^�[
	virtual D3DXVECTOR3 GetSize() = 0;																	// �傫���̃Q�b�^�[
	void SetObjType(EObjectType objectType) { m_objectType = objectType; }								// �I�u�W�F�N�g�̎�ʐݒ�
	EObjectType GetObjType() { return m_objectType; }													// �I�u�W�F�N�g�̎�ʐݒ�
	void SetObjectDrowType(EObjectDrowType objectDrowType) { m_objectDrowType = objectDrowType; }		// �I�u�W�F�N�g�̕`����@�̐ݒ�
	EObjectDrowType GetObjectDrowType() { return m_objectDrowType; }									// �I�u�W�F�N�g�̕`����@�̐ݒ�
	void SetColorType(COLOR_TYPE colorType) { m_colorType = colorType; }								// �F�^�C�v�̐ݒ�
	COLOR_TYPE GetColorType() { return m_colorType; }													// �F�^�C�v�̐ݒ�
	void SetColisonPos(const D3DXVECTOR3 &colisonPos) { m_colisonPos = colisonPos; }					// �����蔻��̈ʒu�̃Z�b�^�[
	D3DXVECTOR3 GetColisonPos() { return m_colisonPos; }												// �����蔻��̈ʒu�̎擾
	void SetColisonSize(const D3DXVECTOR3 &colisonSize) { m_colisonSize = colisonSize; }				// �����蔻��̑傫���̃Z�b�^�[
	D3DXVECTOR3 GetColisonSize() { return m_colisonSize; }												// �����蔻��̑傫���̎擾

protected:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void Release(void);																					// �I�u�W�F�N�g�̉��
	bool ColisonRange2D(CObject *target);																// �͈͂̔���(2D)
	bool ColisonRectangle2D(CObject *target,bool bExtrude);												// ��`�̔���(2D)
	bool ColisonCircle2D(CObject *target, bool bExtrude);												// �~�̔���(2D)
	bool ColisonRectangle3D(CObject *target, bool bExtrude);											// ��`�̔���(3D)
	bool ColisonSphere3D(CObject *target, D3DXVECTOR3 size, D3DXVECTOR3 targetSize, bool bExtrude);		// ���̔���(3D)

private:
	//--------------------------------------------------------------------
	// �ÓI�����o�ϐ�
	//--------------------------------------------------------------------
	static CObject *m_apObject[MAX_LEVEL][MAX_OBJECT];		// �I�u�W�F�N�g���
	static bool m_bPause;									// �|�[�Y���g�p���Ă��邩�ǂ���

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	EObjectType			m_objectType;		// �I�u�W�F�N�g�̎��
	EObjectDrowType		m_objectDrowType;	// �I�u�W�F�N�g�̕`����@
	COLOR_TYPE			m_colorType;		// �F�̎��
	D3DXVECTOR3			m_colisonPos;		// �����蔻��̈ʒu
	D3DXVECTOR3			m_colisonSize;		// �����蔻��̑傫��
	int					m_nNumID;			// �i�[��̔ԍ�
	int					m_nLevPriority;		// �v���C�I���e�B�̃��x��
};

#endif

