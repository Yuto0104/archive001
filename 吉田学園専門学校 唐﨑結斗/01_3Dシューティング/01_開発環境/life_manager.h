//=============================================================================
//
// ���C�t�}�l�[�W���[�N���X(life_manager.h)
// Author : �������l
// �T�v : ���C�t�}�l�[�W���[�������s��
//
//=============================================================================
#ifndef _LIFE_MANAGER_H_		// ���̃}�N����`������ĂȂ�������
#define _LIFE_MANAGER_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CLife;

//=============================================================================
// ���C�t�}�l�[�W���[�N���X
// Author : �������l
// �T�v : ���C�t�}�l�[�W���[�������s���N���X
//=============================================================================
class CLifeManager : public CObject
{
public:
	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CLifeManager *Create();			// ���C�t�}�l�[�W���[�̐���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CLifeManager(int nPriority = CObject::PRIORITY_LEVEL3);
	~CLifeManager() override;

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init() override;														// ������
	void Uninit() override;															// �I��
	void Update() override;															// �X�V
	void Draw() override;															// �`��
	void SetPos(const D3DXVECTOR3 &pos) override;									// �ʒu�̃Z�b�^�[
	void SetPosOld(const D3DXVECTOR3 &posOld) override { m_posOld = posOld; }		// �ߋ��ʒu�̃Z�b�^�[
	void SetRot(const D3DXVECTOR3 &rot) override;									// �����̃Z�b�^�[
	void SetSize(const D3DXVECTOR3 &size) override;									// �傫���̃Z�b�^�[
	D3DXVECTOR3 GetPos() override { return m_pos; }									// �ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetPosOld()  override { return m_posOld; }							// �ߋ��ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetRot()  override { return m_rot; }								// �����̃Q�b�^�[
	D3DXVECTOR3 GetSize()  override { return m_size; }								// �傫���̃Q�b�^�[
	void UninitLifeAll();															// ���ׂẴ��C�t�̏I��
	void SetLife();																	// ���C�t�̃Z�b�^�[

private:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	CLife				**m_pLife;			// ���C�t
	D3DXVECTOR3			m_pos;				// �ʒu
	D3DXVECTOR3			m_posOld;			// �ߋ��̈ʒu
	D3DXVECTOR3			m_rot;				// ����
	D3DXVECTOR3			m_size;				// �傫��
	int					m_nLife;			// ���C�t
	int					m_nAddLife;			// �ǉ����C�t
	int					m_nMaxLife;			// �ő僉�C�t
};

#endif


