//=============================================================================
//
// �I�u�W�F�N�g�N���X(object.h)
// Author : �������l
// �T�v : �I�u�W�F�N�g�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "object.h"
#include "renderer.h"
#include "application.h"
#include "camera.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CObject *CObject::m_apObject[MAX_LEVEL][MAX_OBJECT] = {};		// �G�C���X�^���X
bool CObject::m_bPause = false;									// �|�[�Y���g�p���Ă��邩�ǂ���

//=============================================================================
// �C���X�^���X�̉��
// Author : �������l
// �T�v : ���ׂẴC���X�^���X��������鏈��
//=============================================================================
void CObject::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_LEVEL; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr)
			{// �C���X�^���X���g�p����Ă�
				// �I�u�W�F�N�g�I������
				m_apObject[nCntPriority][nCntObject]->Uninit();
			}
		}
	}
}

//=============================================================================
// �J�ڎ��̃C���X�^���X�̉��
// Author : �������l
// �T�v : �J�ڎ��̃C���X�^���X��������鏈��
//=============================================================================
void CObject::ReleaseScene(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_LEVEL; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr
				&& m_apObject[nCntPriority][nCntObject]->GetObjType() != OBJTYPE_FADE
				&& m_apObject[nCntPriority][nCntObject]->GetObjType() != OBJTYPE_PAUSE)
			{// �C���X�^���X���g�p����Ă�
				// �I�u�W�F�N�g�I������
				m_apObject[nCntPriority][nCntObject]->Uninit();
			}
		}
	}
}

//=============================================================================
// ���ׂẴC���X�^���X�̍X�V
// Author : �������l
// �T�v : �g�p����Ă�C���X�^���X�̍X�V�������Ăяo��
//=============================================================================
void CObject::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_LEVEL; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr
				&& !m_bPause)
			{// �C���X�^���X���g�p����Ă�
				// �I�u�W�F�N�g�X�V����
				m_apObject[nCntPriority][nCntObject]->Update();
			}
			else if (m_apObject[nCntPriority][nCntObject] != nullptr
				&& m_bPause
				&& m_apObject[nCntPriority][nCntObject]->m_objectType == OBJTYPE_PAUSE)
			{// �C���X�^���X���g�p����Ă�
				// �I�u�W�F�N�g�X�V����
				m_apObject[nCntPriority][nCntObject]->Update();
			}
		}
	}
}

//=============================================================================
// ���ׂẴC���X�^���X�̕`��
// Author : �������l
// �T�v : �g�p����Ă�C���X�^���X�̕`�揈�����Ăяo��
//=============================================================================
void CObject::DrawAll(EObjectDrowType objectDrowType)
{
	if (objectDrowType == DROWTYPE_GAME)
	{
		CApplication::GetCamera()->Set();
	}
	else
	{
		CApplication::GetCameraBG()->Set();
	}

	for (int nCntPriority = 0; nCntPriority < MAX_LEVEL; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr
				&& m_apObject[nCntPriority][nCntObject]->m_objectDrowType == objectDrowType)
			{// �C���X�^���X���g�p����Ă�
				// �I�u�W�F�N�g�`�揈��
				m_apObject[nCntPriority][nCntObject]->Draw();
			}
		}
	}
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CObject::CObject(int nPriority /*= PRIORITY_LEVEL0*/) :
m_objectType(OBJTYPE_NONE),
m_objectDrowType(DROWTYPE_GAME),
m_colorType(TYPE_NONE),
m_colisonPos(D3DXVECTOR3(0.0f,0.0f,0.0f)),
m_colisonSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
m_nNumID(0),			
m_nLevPriority(0)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nPriority][nCntObject] == nullptr)
		{// �C���X�^���X���g�p����ĂȂ�
			m_apObject[nPriority][nCntObject] = this;
			m_nNumID = nCntObject;
			m_nLevPriority = nPriority;
			break;
		}
	}
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CObject::~CObject()
{
	
}

//=============================================================================
// �C���X�^���X�̉��
// Author : �������l
// �T�v : ���ׂẴC���X�^���X��������鏈��
//=============================================================================
void CObject::Release(void)
{
	if (m_apObject[m_nLevPriority][m_nNumID] != nullptr)
	{// �C���X�^���X���g�p����Ă�
		// �������̉��
		const int nID = m_nNumID;
		const int nLevPriority = m_nLevPriority;
		delete m_apObject[nLevPriority][nID];
		m_apObject[nLevPriority][nID] = nullptr;
	}
}

//=============================================================================
// �͈͓��̔���
// Author : �������l
// �T�v : �^�[�Q�b�g���͈͓��ɓ��������̔���
//=============================================================================
bool CObject::ColisonRange2D(CObject * target)
{// �����̏����擾����
	D3DXVECTOR3 pos = GetPos() + m_colisonPos;
	D3DXVECTOR3 size = GetSize();

	// �ڕW�̏��擾
	D3DXVECTOR3 posTarget = target->GetPos() + target->GetColisonPos();
	D3DXVECTOR3 sizeTarget = target->GetSize();

	if (pos.x - size.x >= posTarget.x - sizeTarget.x
		&& pos.x + size.x <= posTarget.x + sizeTarget.x
		&& pos.y - size.y >= posTarget.y - sizeTarget.y
		&& pos.y + size.y <= posTarget.y + sizeTarget.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//=============================================================================
// ��`�̔���
// Author : �������l
// �T�v : �^�[�Q�b�g�Ƃ̋�`����
//=============================================================================
bool CObject::ColisonRectangle2D(CObject *target, bool bExtrude)
{// �Ԃ�l�p�̕ϐ�
	bool bColision = false;

	// �����̏����擾����
	D3DXVECTOR3 pos = GetPos() + m_colisonPos;
	D3DXVECTOR3 posOld = GetPosOld();
	D3DXVECTOR3 size = GetSize() / 2.0f;

	// �ڕW�̏��擾
	D3DXVECTOR3 posTarget = target->GetPos() + target->GetColisonPos();
	D3DXVECTOR3 sizeTarget = target->GetSize() / 2.0f;

	if (pos.y - size.y  < posTarget.y + sizeTarget.y 
		&& pos.y + size.y  > posTarget.y - sizeTarget.y )
	{// ���f�����ɂ���(Y��)
		if (posOld.x + size.y  <= posTarget.x - sizeTarget.x 
			&& pos.x + size.y  > posTarget.x - sizeTarget.x )
		{
			if (bExtrude)
			{// �����o�����g�p����
				pos.x = posTarget.x - sizeTarget.x  - size.y ;
			}

			bColision = true;
		}
		if (posOld.x - size.y  >= posTarget.x + sizeTarget.x 
			&& pos.x - size.y  < posTarget.x + sizeTarget.x )
		{
			if (bExtrude)
			{// �����o�����g�p����
				pos.x = posTarget.x + sizeTarget.x  + size.y ;
			}

			bColision = true;
		}
	}
	if (pos.x - size.x  < posTarget.x + sizeTarget.x 
		&& pos.x + size.x  > posTarget.x - sizeTarget.x )
	{// ���f�����ɂ���(X��)
		if (posOld.y + size.y  <= posTarget.y - sizeTarget.y 
			&& pos.y + size.y  > posTarget.y - sizeTarget.y )
		{
			if (bExtrude)
			{// �����o�����g�p����
				pos.y = posTarget.y - sizeTarget.y  - size.y ;
			}

			bColision = true;
		}
		if (posOld.y - size.y  >= posTarget.y + sizeTarget.y 
			&& pos.y - size.y  < posTarget.y + sizeTarget.y )
		{
			if (bExtrude)
			{// �����o�����g�p����
				pos.y = posTarget.y + sizeTarget.y  + size.y ;
			}

			bColision = true;
		}
	}

	// �ʒu�̐ݒ�
	SetPos(pos);
	return bColision;
}

//=============================================================================
// �~�̔���
// Author : �������l
// �T�v : �^�[�Q�b�g�Ƃ̉~����
//=============================================================================
bool CObject::ColisonCircle2D(CObject * target, bool bExtrude)
{
	// �ϐ��錾
	bool bCollision = false;

	// �����̏����擾����
	D3DXVECTOR3 pos = GetPos() + m_colisonPos;
	D3DXVECTOR3 size = GetSize() / 2.0f;

	// �ڕW�̏��擾
	D3DXVECTOR3 posTarget = target->GetPos() + target->GetColisonPos();
	D3DXVECTOR3 sizeTarget = target->GetSize() / 2.0f;

	// ������s���������Z�o
	float fJudgeDistance = sqrtf((size.x * size.x) + (size.y * size.y));
	fJudgeDistance += sqrtf((sizeTarget.x * sizeTarget.x) + (sizeTarget.y * sizeTarget.y));

	// ���݂��̈ʒu�̍����Z�o
	D3DXVECTOR3 distance = posTarget - pos;
	float fDistance = sqrtf((distance.x * distance.x) + (distance.y * distance.y));

	if (fDistance <= fJudgeDistance)
	{// �ʒu�̍���������s���������Z���ꍇ
		bCollision = true;

		if (bExtrude)
		{
			float fRotDif = atan2f(distance.x, distance.y);
			pos.x = posTarget.x - (sinf(fRotDif) * fJudgeDistance);
			pos.y = posTarget.y - (cosf(fRotDif) * fJudgeDistance);
		}
	}

	// �ʒu�̐ݒ�
	SetPos(pos);
	return bCollision;
}

//=============================================================================
// ��`�̔���
// Author : �������l
// �T�v : �^�[�Q�b�g�Ƃ̋�`����
//=============================================================================
bool CObject::ColisonRectangle3D(CObject * target, bool bExtrude)
{// �Ԃ�l�p�̕ϐ�
	bool bColision = false;

	// �����̏����擾����
	D3DXVECTOR3 pos = GetPos() + m_colisonPos;
	D3DXVECTOR3 posOld = GetPosOld();
	D3DXVECTOR3 size = GetSize() / 2.0f;

	// �ڕW�̏��擾
	D3DXVECTOR3 posTarget = target->GetPos() + target->GetColisonPos();
	D3DXVECTOR3 sizeTarget = target->GetSize() / 2.0f;

	if ((pos.z - size.z / 2) < (posTarget.z + sizeTarget.z)
		&& (pos.z + size.z / 2) > (posTarget.z - sizeTarget.z)
		&& (pos.x - size.x / 2) < (posTarget.x + sizeTarget.x)
		&& (pos.x + size.x / 2) > (posTarget.x - sizeTarget.x))
	{// ���f�����ɂ���(XZ��)
		if ((posOld.y + size.y) <= (posTarget.y - sizeTarget.y)
			&& (pos.y + size.y) >(posTarget.y - sizeTarget.y))
		{
			bColision = true;

			if (bExtrude)
			{
				pos.y = posTarget.y - sizeTarget.y - size.y;
			}
		}
		if ((posOld.y) >= (posTarget.y + sizeTarget.y)
			&& (pos.y) < (posTarget.y + sizeTarget.y))
		{
			bColision = true;

			if (bExtrude)
			{
				pos.y = posTarget.y + sizeTarget.y;
			}
		}
	}
	if ((pos.y) < (posTarget.y + sizeTarget.y)
		&& (pos.y + size.y) > (posTarget.y - sizeTarget.y))
	{// ���f�����ɂ���(Y��)
		if ((pos.z - size.z / 2) < (posTarget.z + sizeTarget.z)
			&& (pos.z + size.z / 2) > (posTarget.z - sizeTarget.z))
		{// ���f�����ɂ���(Z��)
			if ((posOld.x + size.z / 2) <= (posTarget.x - sizeTarget.x)
				&& (pos.x + size.z / 2) > (posTarget.x - sizeTarget.x))
			{
				bColision = true;

				if (bExtrude)
				{
					pos.x = posTarget.x - sizeTarget.x - size.z / 2;
				}
			}
			if ((posOld.x - size.z / 2) >= (posTarget.x + sizeTarget.x)
				&& (pos.x - size.z / 2) < (posTarget.x + sizeTarget.x))
			{
				bColision = true;

				if (bExtrude)
				{
					pos.x = posTarget.x + sizeTarget.x + size.z / 2;
				}
			}
		}
		if ((pos.x - size.x / 2) < (posTarget.x + sizeTarget.x)
			&& (pos.x + size.x / 2) > (posTarget.x - sizeTarget.x))
		{// ���f�����ɂ���(X��)
			if ((posOld.z + size.z / 2) <= (posTarget.z - sizeTarget.z)
				&& (pos.z + size.z / 2) > (posTarget.z - sizeTarget.z))
			{
				bColision = true;

				if (bExtrude)
				{
					pos.z = posTarget.z - sizeTarget.z - size.z / 2;
				}
			}
			if ((posOld.z - size.z / 2) >= (posTarget.z + sizeTarget.z)
				&& (pos.z - size.z / 2) < (posTarget.z + sizeTarget.z))
			{
				bColision = true;

				if (bExtrude)
				{
					pos.z = posTarget.z + sizeTarget.z + size.z / 2;
				}
			}
		}
	}

	// �ʒu�̐ݒ�
	SetPos(pos);
	return bColision;
}

//=============================================================================
// ���̔���
// Author : �������l
// �T�v : �^�[�Q�b�g�Ƃ̋�����
//=============================================================================
bool CObject::ColisonSphere3D(CObject *target, D3DXVECTOR3 size, D3DXVECTOR3 targetSize, bool bExtrude)
{
	// �ϐ��錾
	bool bCollision = false;

	// �����̏����擾����
	D3DXVECTOR3 pos = GetPos() + m_colisonPos;
	size /= 2.0f;

	// �ڕW�̏��擾
	D3DXVECTOR3 posTarget = target->GetPos() + target->GetColisonPos();
	targetSize /= 2.0f;

	// ������s���������Z�o
	float fJudgeDistance = sqrtf((size.x * size.x) + (size.y * size.y) + (size.z * size.z));
	fJudgeDistance += sqrtf((targetSize.x * targetSize.x) + (targetSize.y * targetSize.y) + (targetSize.z * targetSize.z));

	// ���݂��̈ʒu�̍����Z�o
	D3DXVECTOR3 distance = posTarget - pos;
	float fDistance = sqrtf((distance.x * distance.x) + (distance.y * distance.y) + (distance.z * distance.z));

	if (fDistance <= fJudgeDistance)
	{// �ʒu�̍���������s���������Z���ꍇ
		bCollision = true;

		if (bExtrude)
		{
			// �p�x�̎Z�o
			D3DXVECTOR3 rotDiff;
			rotDiff.y = atan2f(distance.x, distance.z);
			rotDiff.x = atan2f(sqrtf((distance.x * distance.x) + (distance.z * distance.z)), distance.y);
			rotDiff.z = 0.0f;

			// �ʒu�̎Z�o
			pos.z = posTarget.z - sinf(rotDiff.x) * cosf(rotDiff.y) * fJudgeDistance;
			pos.x = posTarget.x - sinf(rotDiff.x) * sinf(rotDiff.y) * fJudgeDistance;
			pos.y = posTarget.y - cosf(rotDiff.x) * fJudgeDistance;

			// �ʒu�̐ݒ�
			SetPos(pos);
		}
	}

	return bCollision;
}
