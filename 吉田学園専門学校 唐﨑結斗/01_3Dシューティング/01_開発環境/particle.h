//=============================================================================
//
// �p�[�e�B�N���N���X(particle.h)
// Author : �������l
// �T�v : �p�[�e�B�N���������s��
//
//=============================================================================
#ifndef _PARTICLE_H_		// ���̃}�N����`������ĂȂ�������
#define _PARTICLE_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************

//=============================================================================
// �p�[�e�B�N���N���X
// Author : �������l
// �T�v : �p�[�e�B�N���������s���N���X
//=============================================================================
class CParticle : public CObject
{
private:
	//--------------------------------------------------------------------
	// �萔��`
	//--------------------------------------------------------------------

public:
	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CParticle *Create();		// �p�[�e�B�N���̐���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CParticle(int nPriority = CObject::PRIORITY_LEVEL3);
	~CParticle() override;

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
	void SetColor(const D3DXCOLOR &col) { m_color = col; }							// �F�̐ݒ�			
	void SetPopRange(const D3DXVECTOR3 popRange) { m_popRange = popRange; }			// �����͈͂̐ݒ�
	void SetMoveVec(const D3DXVECTOR3 moveVec) { m_moveVec = moveVec; }				// �ړ������̐ݒ�
	void SetSpeed(const float fSpeed) { m_fSpeed = fSpeed; }						// ���x�̐ݒ�
	void SetEffectLife(const int nEffectLife) { m_nEffectLife = nEffectLife; }		// �G�t�F�N�g�̎����̐ݒ�
	void SetLife(const int nLife) { m_nLife = nLife; }								// �����̐ݒ�
	void SetMaxEffect(const int nMaxEffect) { m_nMaxEffect = nMaxEffect; }			// �ʒu�t���[���o���G�t�F�N�g���̃Z�b�^�[

private:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void SetEffect();

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	D3DXVECTOR3			m_pos;				// �ʒu
	D3DXVECTOR3			m_posOld;			// �ߋ��̈ʒu
	D3DXVECTOR3			m_rot;				// ����
	D3DXVECTOR3			m_popRange;			// �����͈�
	D3DXVECTOR3			m_size;				// �傫��
	D3DXVECTOR3			m_moveVec;			// �ړ�����
	D3DXCOLOR			m_color;			// �F
	float				m_fSpeed;			// ���x
	int					m_nEffectLife;		// �G�t�F�N�g�̎���
	int					m_nLife;			// ����
	int					m_nMaxEffect;		// �ʒu�t���[���o���G�t�F�N�g��
};

#endif


