//=============================================================================
//
// 2D�o���b�g(bullet2D.h)
// Author : �������l
// �T�v : 2D�o���b�g�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "bullet2D.h"
#include "renderer.h"
#include "application.h"
#include "explosion2D.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : 2D�o���b�g�𐶐�����
//=============================================================================
CBullet2D * CBullet2D::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const float fSpeed)
{
	// �I�u�W�F�N�g�C���X�^���X
	CBullet2D *pBullet2D = nullptr;

	pBullet2D = new CBullet2D;

	if (pBullet2D != nullptr)
	{// ���l�̏�����
		pBullet2D->Init();
		pBullet2D->SetPos(pos);
		pBullet2D->SetPosOld(pos);
		pBullet2D->SetRot(rot);
		pBullet2D->SetSpeed(fSpeed);
		pBullet2D->Move();
	}
	else
	{// �������̊m�ۂ��ł��Ȃ�����
		assert(false);
	}

	// �C���X�^���X��Ԃ�
	return pBullet2D;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CBullet2D::CBullet2D()
{
	m_move = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	m_fSpeed = 0.0f;
	SetObjType(CObject::OBJTYPE_2DBULLET);				// �I�u�W�F�N�g�̎�ʐݒ�
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CBullet2D::~CBullet2D()
{

}

//=============================================================================
// 2D�o���b�g������
// Author : �������l
// �T�v : �e�N�X�`���̐ݒ肵�A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CBullet2D::Init()
{
	// �I�u�W�F�N�g2D�̏�����
	CObject2D::Init();

	// �e�N�X�`���̐ݒ�
	LoadTex(0);

	// �T�C�Y
	D3DXVECTOR3 size = GetSize();
	size = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
	SetSize(size);

	// ����
	m_nLife = 60;

	// �e�N�X�`�����W�̐ݒ�
	SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// 2D�o���b�g�I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CBullet2D::Uninit()
{
	// �I�u�W�F�N�g2D�̏I��
	CObject2D::Uninit();
}

//=============================================================================
// 2D�o���b�g�X�V
// Author : �������l
// �T�v : 2D�o���b�g�̍X�V���s��
//=============================================================================
void CBullet2D::Update()
{
	// Object2D�̃����o�ϐ��̎擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 size = GetSize();
	SetPosOld(pos);

	// �I�u�W�F�N�g2D�̍X�V
	CObject2D::Update();

	// �ړ�
	pos -= m_move;
	SetPos(pos);

	for (int nCntPriority = 0; nCntPriority < CObject::MAX_LEVEL; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			// �I�u�W�F�N�g�C���X�^���X�̎擾
			CObject *pObject = CObject::MyGetObject(nCntPriority, nCntObj);

			if (pObject != nullptr)
			{
				if ((pObject->GetObjType() == CObject::OBJTYPE_2DENEMY
					|| pObject->GetObjType() == CObject::OBJTYPE_2DPLAYER)
					&& ColisonCircle2D(pObject, false))
				{// �^�C�v����v�����ꍇ
					//m_nLife = 1;

					// �ΏۂƂ̋����̎Z�o
					D3DXVECTOR3 posDiff = pObject->GetPos() - GetPos();

					// �Ώۂ܂ł̊p�x�̎Z�o
					float fRotDest = atan2f(posDiff.x, posDiff.y);

					// �p�x�̔��]
					fRotDest *= 1.0f;

					if (fRotDest >= D3DX_PI)
					{// �ړ������̐��K��
						fRotDest -= D3DX_PI * 2;
					}
					else if (fRotDest <= -D3DX_PI)
					{// �ړ������̐��K��
						fRotDest += D3DX_PI * 2;
					}

					// �ړ���(�����Ƒ���)�̎Z�o
					m_move.x = sinf(fRotDest) * 5.0f;
					m_move.y = cosf(fRotDest) * 5.0f;

					break;
				}
			}
		}
	}

	if (m_nLife > 0)
	{// ���C�t������ꍇ
		m_nLife--;

		if (m_nLife <= 0)
		{// 0�ȉ��̏ꍇ

			m_nLife = 0;
			CExplosion2D::Create(pos, rot);
			Uninit();
		}
	}
}

//=============================================================================
// 2D�o���b�g�`��
// Author : �������l
// �T�v : 2D�o���b�g�̕`����s��
//=============================================================================
void CBullet2D::Draw()
{// �v���C���[2D�̕`��
	CObject2D::Draw();
}

//=============================================================================
// �ړ�
// Author : �������l
// �T�v : ���x�ƕ������������ړ��ʂ��Z�o���Ԃ�
//=============================================================================
D3DXVECTOR3 CBullet2D::Move(void)
{
	// �ړ��ʂ̎Z�o
	D3DXVECTOR3 rot = GetRot();
	m_move.x = sinf(rot.z) * m_fSpeed;
	m_move.y = cosf(rot.z) * m_fSpeed;

	return m_move;
}
