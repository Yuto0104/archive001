//=============================================================================
//
// �X�R�A�N���X(score.cpp)
// Author : �������l
// �T�v : �X�R�A�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>
#include <math.h>

#include "life_manager.h"
#include "life.h"
#include "motion_player3D.h"
#include "renderer.h"
#include "application.h"
#include "game.h"
#include "tutorial.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : �X�R�A�𐶐�����
//=============================================================================
CLifeManager *CLifeManager::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CLifeManager *pLifeManager = nullptr;

	pLifeManager = new CLifeManager;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pLifeManager != nullptr);

	// ���l�̏�����
	pLifeManager->Init();

	// �C���X�^���X��Ԃ�
	return pLifeManager;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CLifeManager::CLifeManager(int nPriority /*= CObject::PRIORITY_LEVEL3*/) : CObject(nPriority)
{
	m_pLife = nullptr;									// ���C�t
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ߋ��̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �傫��
	m_nLife = 0;										// ���C�t
	m_nAddLife = 0;										// �ǉ����C�t
	m_nMaxLife = 0;										// �ő僉�C�t
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CLifeManager::~CLifeManager()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CLifeManager::Init()
{
	// �ʒu�̐ݒ�
	m_pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);

	// �����̐ݒ�
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �傫���̐ݒ�
	m_size = D3DXVECTOR3(300.0f, 50.0f, 0.0f);

	// ���C�t�̐ݒ�
	SetLife();

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CLifeManager::Uninit()
{
	UninitLifeAll();

	// ���C�t�}�l�[�W���[�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V���s��
//=============================================================================
void CLifeManager::Update()
{
	
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CLifeManager::Draw()
{

}

//=============================================================================
// �ʒu�̃Z�b�^�[
// Author : �������l
// �T�v : �ʒu�̃����o�ϐ��Ɉ�������
//=============================================================================
void CLifeManager::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;

	// ���C�t�̐ݒ�
	SetLife();
}

//=============================================================================
// �����̃Z�b�^�[
// Author : �������l
// �T�v : �����̃����o�ϐ��Ɉ�������
//=============================================================================
void CLifeManager::SetRot(const D3DXVECTOR3 &rot)
{
	m_rot = rot;

	// ���C�t�̐ݒ�
	SetLife();
}

//=============================================================================
// �傫���̃Z�b�^�[
// Author : �������l
// �T�v : �傫���̃����o�ϐ��Ɉ�������
//=============================================================================
void CLifeManager::SetSize(const D3DXVECTOR3 & size)
{
	m_size = size;

	// ���C�t�̐ݒ�
	SetLife();
}

//=============================================================================
// ���C�t�̏I��
// Author : �������l
// �T�v : ���C�t�̏I��
//=============================================================================
void CLifeManager::UninitLifeAll()
{
	if (m_pLife != nullptr)
	{// �I������
		for (int nCntLife = 0; nCntLife < m_nMaxLife; nCntLife++)
		{
			m_pLife[nCntLife]->Uninit();
		}

		// �������̉��
		delete[] m_pLife;
		m_pLife = nullptr;
	}
}

//=============================================================================
// ���C�t�̃Z�b�^�[
// Author : �������l
// �T�v : �X�R�A�ɐ��l�������āA�i���o�[�̐ݒ�
//=============================================================================
void CLifeManager::SetLife()
{
	CMotionPlayer3D * pMotionPlayer3D = nullptr;

	switch (CApplication::GetMode())
	{
	case CApplication::MODE_GAME:
		// �v���C���[�̎擾
		pMotionPlayer3D = CGame::GetMotionPlayer3D();
		break;

	case CApplication::MODE_TUTORIAL:
		// �v���C���[�̎擾
		pMotionPlayer3D = CTutorial::GetMotionPlayer3D();
		break;

	default:
		break;
	}

	// ���C�t�̏I��
	UninitLifeAll();

	// ���C�t�̐ݒ�
	m_nLife = pMotionPlayer3D->GetLife();
	m_nAddLife = pMotionPlayer3D->GetInvalidLife();
	m_nMaxLife = CMotionPlayer3D::MAX_LIFE + m_nAddLife;

	// ���C�t�̃������m��
	m_pLife = new CLife*[m_nMaxLife];
	assert(m_pLife != nullptr);

	for (int nCntLife = 0; nCntLife < m_nMaxLife; nCntLife++)
	{// ���C�t�̐ݒ�
		m_pLife[nCntLife] = CLife::Create();

		// �傫���̐ݒ�
		m_pLife[nCntLife]->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));

		// ���C�t�傫���̎擾
		D3DXVECTOR3 lifeSize = m_pLife[nCntLife]->GetSize();

		// �ʒu�̐ݒ�
		m_pLife[nCntLife]->SetPos(D3DXVECTOR3(m_pos.x + lifeSize.x / 2.0f + (lifeSize.x * nCntLife), m_pos.y, 0.0f));

		// �����̐ݒ�
		m_pLife[nCntLife]->SetRot(m_rot);

		m_pLife[nCntLife]->SetLifeState(CLife::STATE_INVALID);
	}

	for (int nCntLife = 0; nCntLife < m_nLife; nCntLife++)
	{
		m_pLife[nCntLife]->SetLifeState(CLife::STATE_NORMAL);
	}

	for (int nCntLife = CMotionPlayer3D::MAX_LIFE; nCntLife < m_nMaxLife; nCntLife++)
	{
		m_pLife[nCntLife]->SetLifeState(CLife::STATE_ADDITION);
	}
}
