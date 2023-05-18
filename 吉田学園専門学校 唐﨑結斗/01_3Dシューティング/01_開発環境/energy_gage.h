//=============================================================================
//
// �G�l���M�[�Q�[�W�N���X(energy_gage.h)
// Author : �������l
// �T�v : �G�l���M�[�Q�[�W�̐ݒ���s��
//
//=============================================================================
#ifndef _ENERGY_GAGE_H_		// ���̃}�N����`������ĂȂ�������
#define _ENERGY_GAGE_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObject2D;
class CScore;
class CGauge2D;

//=============================================================================
// �G�l���M�[�Q�[�W�N���X
// Author : �������l
// �T�v : �G�l���M�[�Q�[�W�������s���N���X
//=============================================================================
class CEnergyGage : public CObject
{
public:
	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CEnergyGage *Create();			// �G�l���M�[�Q�[�W�̐���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CEnergyGage(int nPriority = CObject::PRIORITY_LEVEL3);
	~CEnergyGage() override;

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
	CScore *GetScore() { return m_pScore; }											// �X�R�A�̃Q�b�^�[
	CGauge2D *GetGauge2D() { return m_pGauge2D; }									// �Q�[�W�̃Q�b�^�[

private:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	CObject2D			*m_pObject2D;		// 2D�I�u�W�F�N�g
	CScore				*m_pScore;			// �X�R�A
	CGauge2D			*m_pGauge2D;		// �Q�[�W
	D3DXVECTOR3			m_pos;				// �ʒu
	D3DXVECTOR3			m_posOld;			// �ߋ��̈ʒu
	D3DXVECTOR3			m_rot;				// ����
	D3DXVECTOR3			m_size;				// �傫��
	int					m_nLife;			// ���C�t
	int					m_nAddLife;			// �ǉ����C�t
	int					m_nMaxLife;			// �ő僉�C�t
};

#endif



