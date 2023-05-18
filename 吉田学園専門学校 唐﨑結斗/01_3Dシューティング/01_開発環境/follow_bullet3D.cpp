//=============================================================================
//
// 3D�Ǐ]�o���b�g�N���X(follow_bullet3D.cpp)
// Author : �������l
// �T�v : �I�u�W�F�N�g�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "follow_bullet3D.h"
#include "renderer.h"
#include "application.h"

#include "motion_player3D.h"
#include "enemy3D.h"
#include "score.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : 3D�o���b�g�𐶐�����
//=============================================================================
CFollowBullet3D * CFollowBullet3D::Create(void)
{
	// �I�u�W�F�N�g�C���X�^���X
	CFollowBullet3D *pFollowBullet3D = nullptr;

	// �������̉��
	pFollowBullet3D = new CFollowBullet3D;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pFollowBullet3D != nullptr);

	// ���l�̏�����
	pFollowBullet3D->Init();

	// �C���X�^���X��Ԃ�
	return pFollowBullet3D;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CFollowBullet3D::CFollowBullet3D()
{
	m_pTarget = nullptr;				// �Ǐ]�̃^�[�Q�b�g
	m_fCoefficient = 0.0f;				// �����W��
	m_fAddCoefficient = 0.0f;			// �����W���̉��Z�l

	// �I�u�W�F�N�g�̎�ʐݒ�
	SetObjType(CObject::OBJTYPE_3DBULLET);
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CFollowBullet3D::~CFollowBullet3D()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CFollowBullet3D::Init()
{
	// ������
	CBullet3D::Init();

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CFollowBullet3D::Uninit()
{
	// �I��
	CBullet3D::Uninit();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V���s��
//=============================================================================
void CFollowBullet3D::Update()
{
	// �^�[�Q�b�g���ݒ肳��Ă��Ȃ��ꍇ
	SetTarget();

	// �����W���̉��Z
	AddCoefficient();

	// �Ǐ]
	Follow();

	// �X�V
	CBullet3D::Update();
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CFollowBullet3D::Draw()
{
	// �`��
	CBullet3D::Draw();
}

//=============================================================================
// �^�[�Q�b�g�̐ݒ�
// Author : �������l
// �T�v : ��ԋ߂��I�u�W�F�N�g���^�[�Q�b�g�ɐݒ�
//=============================================================================
void CFollowBullet3D::SetTarget()
{
	// �������i�[
	m_pTarget = nullptr;
	float fDistance = FLT_MAX;
	float fDistanceCopy = 0;

	for (int nCntPriority = 0; nCntPriority < CObject::MAX_LEVEL; nCntPriority++)
	{
		if (m_pTarget == nullptr)
		{
			for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
			{
				// �I�u�W�F�N�g�C���X�^���X�̎擾
				CObject *pObject = CObject::MyGetObject(nCntPriority, nCntObj);

				if (pObject != nullptr
					&& (pObject->GetObjType() == CObject::OBJTYPE_3DENEMY
						|| pObject->GetObjType() == CObject::OBJTYPE_3DBOSS
						|| pObject->GetObjType() == CObject::OBJTYPE_3DPLAYER)
					&& pObject->GetObjType() != CObject::OBJTYPE_3DBULLET
					&& pObject->GetObjType() != GetParent())
				{// �^�C�v����v�����ꍇ
					// �I�u�W�F�N�g�̋������Z�o
					fDistanceCopy = D3DXVec3Length(&(pObject->GetPos() - GetPos()));

					if (fDistanceCopy < fDistance)
					{// ���������݂̂��̂��Z���ꍇ
						// �����̕ۑ�
						fDistance = fDistanceCopy;

						// �I�u�W�F�N�g���^�[�Q�b�g�ɐݒ�
						m_pTarget = pObject;
					}
				}
			}
		}
	}
}

//=============================================================================
// �Ǐ]
// Author : �������l
// �T�v : �ړI�̕����ɏ��X�Ɉړ�����
//=============================================================================
void CFollowBullet3D::Follow()
{
	D3DXVECTOR3 moveVec = GetMoveVec();
	D3DXVECTOR3 moveVecDest = moveVec;

	if (m_pTarget != nullptr)
	{
		D3DXVECTOR3 distance = m_pTarget->GetPos() - GetPos();

		moveVecDest.y = atan2f(distance.x, distance.z);
		moveVecDest.x = atan2f(sqrtf((distance.x * distance.x) + (distance.z * distance.z)), distance.y);
		moveVecDest.z = moveVec.z;

		// �ړ������̐ݒ�
		D3DXVECTOR3 add = (moveVecDest - moveVec);

		// ���K��
		add.x = CApplication::RotNormalization(add.x);
		add.y = CApplication::RotNormalization(add.y);
		add.z = CApplication::RotNormalization(add.z);

		// �ړ������̎Z�o
		moveVec += add * m_fCoefficient;

		// ���K��
		moveVec.x = CApplication::RotNormalization(moveVec.x);
		moveVec.y = CApplication::RotNormalization(moveVec.y);
		moveVec.z = CApplication::RotNormalization(moveVec.z);
	}

	// �ړ������̐ݒ�
	SetMoveVec(moveVec);
}

//=============================================================================
// �����W���̉��Z
// Author : �������l
// �T�v : �����W���̉��Z�l��0�ȏ�̏ꍇ���Z����
//=============================================================================
void CFollowBullet3D::AddCoefficient()
{
	if (m_fAddCoefficient > 0.0f
		&& m_fCoefficient < 1.0f)
	{
		m_fCoefficient += m_fAddCoefficient;

		if (m_fCoefficient > 1.0f)
		{
			m_fCoefficient = 1.0f;
		}
	}
}

