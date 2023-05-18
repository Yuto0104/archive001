//=============================================================================
//
// ���[�V�����L�����N�^�[3D�N���X(model3D.h)
// Author : �������l
// �T�v : ���[�V�����L�����N�^�[3D�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "motion_char3D.h"
#include "motion.h"
#include "renderer.h"
#include "application.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : ���[�V�����L�����N�^�[3D�𐶐�����
//=============================================================================
CMotionChar3D * CMotionChar3D::Create(const char * pName)
{
	// �I�u�W�F�N�g�C���X�^���X
	CMotionChar3D *pMotionChar3D = nullptr;

	// �������̉��
	pMotionChar3D = new CMotionChar3D;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pMotionChar3D != nullptr);

	// ���l�̏�����
	pMotionChar3D->Init(pName);

	// �C���X�^���X��Ԃ�
	return pMotionChar3D;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CMotionChar3D::CMotionChar3D()
{
	
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CMotionChar3D::~CMotionChar3D()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CMotionChar3D::Init(const char *pName)
{
	// ������
	CModel3D::Init();

	// ���[�V�������
	m_pMotion = new CMotion(pName);
	assert(m_pMotion != nullptr);

	// �����o�ϐ��̏�����
	m_nNumMotion = 0;
	m_nNumMotionOld = m_nNumMotion;
	m_bMotion = false;
	m_bMotionBlend = false;

	return E_NOTIMPL;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CMotionChar3D::Uninit()
{
	if (m_pMotion != nullptr)
	{// �I������
		m_pMotion->Uninit();

		// �������̉��
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	// �I��
	CModel3D::Uninit();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : 2D�X�V���s��
//=============================================================================
void CMotionChar3D::Update()
{
	// �X�V
	CModel3D::Update();

	// ���݂̃��[�V�����ԍ��̕ۊ�
	m_nNumMotionOld = m_nNumMotion;

	if (!m_bMotion)
	{// �g�p���Ă郂�[�V�������Ȃ��ꍇ
		m_nNumMotion = 0;
	}

	if (m_nNumMotionOld != m_nNumMotion)
	{// ���[�V�����^�C�v���ύX���ꂽ��
		m_pMotion->CntReset((int)(m_nNumMotionOld));
		m_bMotionBlend = true;
	}

	if (m_bMotionBlend)
	{// ���[�V�����u�����h���g�p���Ă�
		m_bMotionBlend = m_pMotion->MotionBlend((int)(m_nNumMotion));
	}
	else if (!m_bMotionBlend)
	{// ���[�V�����u�����h���g�p���ĂȂ��ꍇ
		m_bMotion = m_pMotion->PlayMotion((int)(m_nNumMotion));
	}
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : 2D�`����s��
//=============================================================================
void CMotionChar3D::Draw()
{
	// �`��
	CModel3D::Draw();

	// ���[���h�}�g���b�N�X�̎擾
	D3DXMATRIX mtxWorld = GetMtxWorld();

	// �p�[�c�̕`��ݒ�
	m_pMotion->SetParts(mtxWorld);
}

//=============================================================================
// ���[�V�����̍ēǂݍ���
// Author : �������l
// �T�v : ���[�V�����̍ēǂݍ��݂��s��
//=============================================================================
void CMotionChar3D::ReloadMotion(const char * pName)
{// ���[�V�����̍ēǂݍ���
	m_pMotion->ReloadMotion(pName);
}
