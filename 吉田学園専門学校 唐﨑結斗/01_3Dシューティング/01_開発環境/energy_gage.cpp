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

#include "energy_gage.h"
#include "object.h"
#include "object2D.h"
#include "score.h"
#include "gauge2D.h"
#include "motion_player3D.h"
#include "renderer.h"
#include "application.h"
#include "texture.h"
#include "game.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : �X�R�A�𐶐�����
//=============================================================================
CEnergyGage *CEnergyGage::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CEnergyGage *pEnergyGage = nullptr;

	pEnergyGage = new CEnergyGage;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pEnergyGage != nullptr);

	// ���l�̏�����
	pEnergyGage->Init();

	// �C���X�^���X��Ԃ�
	return pEnergyGage;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CEnergyGage::CEnergyGage(int nPriority /*= CObject::PRIORITY_LEVEL3*/) : CObject(nPriority)
{
	m_pObject2D = nullptr;								// 2D�I�u�W�F�N�g
	m_pScore = nullptr;									// �X�R�A
	m_pGauge2D = nullptr;								// �Q�[�W
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ߋ��̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �傫��
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CEnergyGage::~CEnergyGage()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CEnergyGage::Init()
{
	// 2D�I�u�W�F�N�g�̐���
	m_pObject2D = CObject2D::Create();
	assert(m_pObject2D != nullptr);
	m_pObject2D->LoadTex(-1);
	m_pObject2D->SetCol(D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f));

	// �X�R�A�̐���
	m_pScore = CScore::Create(6, true);
	assert(m_pScore != nullptr);
	m_pScore->SetScore(0);

	// �Q�[�W�̐���
	m_pGauge2D = CGauge2D::Create();
	assert(m_pGauge2D != nullptr);
	m_pGauge2D->SetCol(D3DXCOLOR(0.2f, 0.9f, 1.0f, 1.0f));
	m_pGauge2D->SetMaxNumber((float)CMotionPlayer3D::MAX_ENERGY);
	m_pGauge2D->SetCoefficient(0.06f);

	// �傫���̐ݒ�
	SetSize(D3DXVECTOR3(70.0f, 500.0f, 0.0f));

	// �ʒu�̐ݒ�
	SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));

	// �����̐ݒ�
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CEnergyGage::Uninit()
{
	m_pScore->Uninit();
	m_pGauge2D->Uninit();

	// �C���X�^���X�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V���s��
//=============================================================================
void CEnergyGage::Update()
{
	CMotionPlayer3D *pPlayer = CGame::GetMotionPlayer3D();

	if (pPlayer != nullptr)
	{
		CObject::COLOR_TYPE colorType = pPlayer->GetColorType();

		if (colorType == CObject::TYPE_WHITE)
		{
			m_pGauge2D->SetCol(D3DXCOLOR(0.2f, 0.9f, 1.0f, 1.0f));
		}
		else if (colorType == CObject::TYPE_BLACK)
		{
			m_pGauge2D->SetCol(D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f));
		}
	}
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CEnergyGage::Draw()
{
	
}

//=============================================================================
// �ʒu�̃Z�b�^�[
// Author : �������l
// �T�v : �ʒu�̃����o�ϐ��Ɉ�������
//=============================================================================
void CEnergyGage::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;

	m_pObject2D->SetPos(m_pos);
	m_pScore->SetPos(D3DXVECTOR3(m_pos.x, (m_pos.y - m_size.y / 2.0f) + m_pScore->GetSize().y / 2.0f, m_pos.z));
	m_pGauge2D->SetPos(D3DXVECTOR3(m_pos.x, (m_pos.y + m_size.y / 2.0f - 7.0f), m_pos.z));
}

//=============================================================================
// �����̃Z�b�^�[
// Author : �������l
// �T�v : �����̃����o�ϐ��Ɉ�������
//=============================================================================
void CEnergyGage::SetRot(const D3DXVECTOR3 &rot)
{
	m_rot = rot;

	m_pObject2D->SetRot(m_rot);
	m_pScore->SetRot(m_rot);
	m_pGauge2D->SetRot(m_rot);
}

//=============================================================================
// �傫���̃Z�b�^�[
// Author : �������l
// �T�v : �傫���̃����o�ϐ��Ɉ�������
//=============================================================================
void CEnergyGage::SetSize(const D3DXVECTOR3 & size)
{
	m_size = size;

	m_pObject2D->SetSize(m_size);
	m_pScore->SetWholeSize(D3DXVECTOR3(m_size.x, size.y / 10.0f, size.z));
	m_pScore->SetSize(D3DXVECTOR3(m_size.x / 3.0f, size.y / 10.0f, size.z));
	m_pGauge2D->SetSize(D3DXVECTOR3(m_size.x / 10.0f * 8.0f, size.y / 10.0f * 9.0f, size.z));
}