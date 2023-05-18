//=============================================================================
//
// 2D����(explosion2D.cpp)
// Author : �������l
// �T�v : 2D�����������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "explosion2D.h"
#include "renderer.h"
#include "application.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : 2D�o���b�g�𐶐�����
//=============================================================================
CExplosion2D * CExplosion2D::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	// �I�u�W�F�N�g�C���X�^���X
	CExplosion2D *pExplosion2D = nullptr;

	pExplosion2D = new CExplosion2D;

	if (pExplosion2D != nullptr)
	{// ���l�̏�����
		pExplosion2D->Init();
		pExplosion2D->SetPos(pos);
		pExplosion2D->SetRot(rot);
	}
	else
	{// �������̊m�ۂ��ł��Ȃ�����
		assert(false);
	}

	// �C���X�^���X��Ԃ�
	return pExplosion2D;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CExplosion2D::CExplosion2D()
{
	// �������̊m��
	m_pTexAnim = new CTexAnim;
	assert(m_pTexAnim != nullptr);
	m_nLife = 0;										// ����
	SetObjType(CObject::OBJTYPE_2DEXPLOSION);			// �I�u�W�F�N�g�̎�ʐݒ�
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CExplosion2D::~CExplosion2D()
{

}

//=============================================================================
// �|���S���̏�����
// Author : �������l
// �T�v : �e�N�X�`���̐ݒ肵�A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CExplosion2D::Init()
{
	// �I�u�W�F�N�g2D�̏�����
	CObject2D::Init();

	// �e�N�X�`���̐ݒ�
	LoadTex(3);

	// �T�C�Y
	D3DXVECTOR3 size = GetSize();
	size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	SetSize(size);

	// ����
	m_nLife = 50;

	// �A�j���[�V�����̏�����
	m_pTexAnim->SetAnim(8, 1, m_nLife, false);

	// �e�N�X�`�����W�̐ݒ�
	SetTex(D3DXVECTOR2(0.0f, 0.0f), m_pTexAnim->GetAddTex());

	return S_OK;
}

//=============================================================================
// �|���S���̏I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CExplosion2D::Uninit()
{
	if (m_pTexAnim != nullptr)
	{// �I������
	 // �������̉��
		delete m_pTexAnim;
		m_pTexAnim = nullptr;
	}

	// �I�u�W�F�N�g2D�̏I��
	CObject2D::Uninit();
}

//=============================================================================
// �|���S���̍X�V
// Author : �������l
// �T�v : 2D�|���S���̍X�V���s��
//=============================================================================
void CExplosion2D::Update()
{
	// �I�u�W�F�N�g2D�̍X�V
	CObject2D::Update();

	// �A�j���[�V�����̍Đ�
	m_pTexAnim->PlayAnim();
	D3DXVECTOR2 texAddAnim = m_pTexAnim->GetAddTex();
	CTexAnim::TEX_PATTERN texNumAnim = m_pTexAnim->GetNumAnim();

	// �e�N�X�`�����W�̐ݒ�
	SetTex(D3DXVECTOR2(0.0f + (texAddAnim.x * texNumAnim.x), 0.0f + (texAddAnim.y * texNumAnim.y)),
		D3DXVECTOR2(texAddAnim.x + (texAddAnim.x * texNumAnim.x), texAddAnim.y + (texAddAnim.y * texNumAnim.y)));

	if (m_nLife > 0)
	{// ���C�t������ꍇ
		m_nLife--;

		if (m_nLife <= 0)
		{// 0�ȉ��̏ꍇ
			m_nLife = 0;
			Uninit();
		}
	}
}

//=============================================================================
// �|���S���̕`��
// Author : �������l
// �T�v : 2D�|���S���̕`����s��
//=============================================================================
void CExplosion2D::Draw()
{// �v���C���[2D�̕`��
	CObject2D::Draw();
}

