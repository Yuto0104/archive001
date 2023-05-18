//=============================================================================
//
// ���[�V�����{�X�N���X(motion_boss.cpp)
// Author : �������l
// �T�v : ���[�V�����{�X�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "motion_boss.h"
#include "motion.h"
#include "renderer.h"
#include "application.h"
#include "game.h"
#include "sound.h"
#include "particle.h"
#include "score.h"
#include "bullet3D.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : 3D���[�V�����v���C���[�𐶐�����
//=============================================================================
CMotionBoss * CMotionBoss::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CMotionBoss *pMotionBoss = nullptr;

	// �������̉��
	pMotionBoss = new CMotionBoss;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pMotionBoss != nullptr);

	// ���l�̏�����
	pMotionBoss->Init();

	// �C���X�^���X��Ԃ�
	return pMotionBoss;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CMotionBoss::CMotionBoss()
{
	m_pMotion = nullptr;						// ���[�V�����C���X�^���X
	m_actionType = ACTION_NONE;					// �A�N�V�����^�C�v
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
	m_fMoveVec = 0.0f;							// �ړ�����
	m_fWave = 0.0f;								// �g
	m_fSpeed = 0.0f;							// �ړ����x
	m_fAddRot = 0.0f;							// �p�x�̉��Z
	m_nNumMotion = 0;							// ���݂̃��[�V�����ԍ�
	m_nNumMotionOld = 0;						// �ߋ��̃��[�V�����ԍ�
	m_nLife = 0;								// ����
	m_nScore = 0;								// �X�R�A
	m_nCntShot = 0;								// �e���˂܂ł̃J�E���g
	m_nMaxShot = 0;								// �e���˂���J�E���g
	m_nCntFrame = 0;							// �t���[���J�E���g
	m_bMotion = false;							// ���[�V�����̎g�p��
	m_bMotionBlend = false;						// ���[�V�����u�����h�̎g�p��
	m_bUse = false;								// �g�p��
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CMotionBoss::~CMotionBoss()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CMotionBoss::Init()
{
	// ������
	CModel3D::Init();

	// ���[�V�������
	m_pMotion = new CMotion("data/MOTION/boss.txt");
	assert(m_pMotion != nullptr);

	m_bUse = true;
	SetColisonPos(D3DXVECTOR3(0.0f, 0.0f, 100.0f));
	SetColisonSize(D3DXVECTOR3(100.0f, 100.0f, 100.0f));
	SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));
	SetSize(D3DXVECTOR3(1.2f, 1.2f, 1.2f));
	SetColorType(CObject::TYPE_WHITE);
	m_nLife = 10000;
	m_actionType = ACTION_NONE;
	m_fMoveVec = D3DX_PI * 0.5f;	
	m_fSpeed = 2.0f;	

	SetObjType(CObject::OBJTYPE_3DBOSS);

	return E_NOTIMPL;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CMotionBoss::Uninit()
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
// �T�v : �X�V���s��
//=============================================================================
void CMotionBoss::Update()
{
	// ���̎擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	// �j���[�g�������[�V�����̓���
	m_nNumMotion = TYPE_NEUTRAL;

	// �e�̔���
	Shot();

	// �ړ�
	Move();

	// ���[�V�����̐ݒ�
	MotionSet();

	// �ʒu�̐ݒ�
	SetPos(pos + m_move);

	if (CollisionScreen())
	{// �X�N���[�������蔻��
		m_fMoveVec *= -1;
	}

	// �X�V
	CModel3D::Update();
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CMotionBoss::Draw()
{
	// �`��
	CModel3D::Draw();

	// ���[���h�}�g���b�N�X�̎擾
	D3DXMATRIX mtxWorld = GetMtxWorld();

	// �p�[�c�̕`��ݒ�
	m_pMotion->SetParts(mtxWorld);
}

//=============================================================================
// �e�̔���
// Author : �������l
// �T�v : �L�[���͂��s��ꂽ�ꍇ�A�e�𔭎˂���
//=============================================================================
void CMotionBoss::Shot()
{
	if (m_actionType == ACTION_DIFFUSIONSHOT)
	{
		m_fAddRot += 0.01f;

		// �T�E���h���̎擾
		CSound *pSound = CApplication::GetSound();

		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 rot = GetRot();
		D3DXCOLOR bulletColor;					// �e�̐F

		if (GetColorType() == CObject::TYPE_WHITE)
		{// �e�̐F�̐ݒ�
			bulletColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			m_nNumMotion = TYPE_ATTACK2;
		}
		else if (GetColorType() == CObject::TYPE_BLACK)
		{// �e�̐F�̐ݒ�
			bulletColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			m_nNumMotion = TYPE_ATTACK1;
		}

		m_nCntShot++;

		if (m_nCntShot % 10 == 0)
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

			// �v�Z�p�ϐ��̐ݒ�
			CBullet3D * pBullet3D = nullptr;
			D3DXVECTOR3 targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 diffPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 diffRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			float fBulletRot = 0.0f;

			for (int nCntBullet = 0; nCntBullet < 7; nCntBullet++)
			{// �e�̔��ˊp�x�̐ݒ�
				fBulletRot = 0.0f - (D3DX_PI * 0.75f / 2) + (D3DX_PI * 0.75f / 7 * nCntBullet);
				fBulletRot = CApplication::RotNormalization(fBulletRot + sinf(m_fAddRot), -(D3DX_PI * 0.5f / 2), (D3DX_PI * 0.5f / 2));

				// �e�̐���
				pBullet3D = CBullet3D::Create();

				if (GetColorType() == CObject::TYPE_WHITE)
				{
					pBullet3D->SetPos(D3DXVECTOR3(pos.x + 55.0f, 0.0f, pos.z + 75.0f));
				}
				else if (GetColorType() == CObject::TYPE_BLACK)
				{
					pBullet3D->SetPos(D3DXVECTOR3(pos.x - 30.0f, 0.0f, pos.z + 60.0f));
				}

				pBullet3D->SetSize(D3DXVECTOR3(10.0f, 10.0f, 0.0f));
				pBullet3D->SetMoveVec(D3DXVECTOR3(D3DX_PI * -0.5f, fBulletRot, 0.0f));
				pBullet3D->SetSpeed(10.0f);
				pBullet3D->SetColor(bulletColor);
				pBullet3D->SetColorType(GetColorType());
				pBullet3D->SetParent(CObject::OBJTYPE_3DBOSS);
			}
		}
	}
}

//=============================================================================
// ���[�V�����̐ݒ�
// Author : �������l
// �T�v : ���[�V�����̕ύX�⃂�[�V�����u�����h�̐ݒ���s��
//=============================================================================
void CMotionBoss::MotionSet()
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	m_nNumMotionOld = m_nNumMotion;

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
// �q�b�g
// Author : �������l
// �T�v : �_���[�W��^����
//=============================================================================
void CMotionBoss::Hit(COLOR_TYPE colorType, int nAttack)
{
	// �T�E���h���̎擾
	CSound *pSound = CApplication::GetSound();

	if (m_bUse)
	{// �ϐ��錾
		COLOR_TYPE MyColorType = GetColorType();
		int nMyAttack = nAttack;

		pSound->PlaySound(CSound::SOUND_LABEL_SE_HIT);

		if (MyColorType != colorType)
		{// �F�̃^�C�v������̏ꍇ
			nMyAttack *= 2;
		}

		// �̗͂̌��Z
		m_nLife -= nMyAttack;

		if (m_nLife <= 0)
		{// �̗͂�0�̏ꍇ
			m_nLife = 0;

			if (CApplication::GetMode() == CApplication::MODE_GAME)
			{
				CScore *pScore = CGame::GetScore();
				pScore->AddScore(m_nScore);
			}

			pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);

			// �f�[�^�i�[�p�ϐ�
			D3DXVECTOR3 pos = GetPos();
			D3DXVECTOR3 rot = GetRot();

			// �p�[�e�B�N���̐���
			CParticle *pParticle = CParticle::Create();
			pParticle->SetPos(pos);
			pParticle->SetSize(D3DXVECTOR3(40.0f, 40.0f, 0.0f));
			pParticle->SetPopRange(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
			pParticle->SetSpeed(5.0f);
			pParticle->SetEffectLife(30);
			pParticle->SetMoveVec(D3DXVECTOR3(D3DX_PI * 2.0f, D3DX_PI * 2.0f, 0.0f));
			pParticle->SetLife(10);
			pParticle->SetColor(D3DXCOLOR(1.0f, 0.4f, 0.1f, 1.0f));
			pParticle->SetMaxEffect(3);

			Uninit();
		}
	}
}

//=============================================================================
// �ړ����̐ݒ�
// Author : �������l
// �T�v : �ړ����̐ݒ�
//=============================================================================
void CMotionBoss::Move()
{
	if (m_actionType == ACTION_DIFFUSIONSHOT)
	{
		m_fWave += 0.1f;
		m_move.x = sinf(m_fMoveVec) * m_fSpeed;
		m_move.z = sinf(m_fWave) * 5.0f;
	}
}

//=============================================================================
// �X�N���[���̂����蔻��
// Author : �������l
// �T�v : �X�N���[���ƃv���C���[�̂����蔻����s��
//=============================================================================
bool CMotionBoss::CollisionScreen()
{
	// �ʒu�̎擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 worldPos;
	bool bCollision = false;

	// �����蔻��̎擾
	D3DXVECTOR3 collision = CObject::GetColisonSize();

	// �X�N���[�����W�ɃL���X�g
	D3DXVECTOR3 screenPos = CApplication::ScreenCastWorld(pos);
	D3DXVECTOR3 screenPosUp = CApplication::ScreenCastWorld(pos + collision);
	D3DXVECTOR3 screenPosUnder = CApplication::ScreenCastWorld(pos - collision);

	if (screenPosUnder.x < 0.0f)
	{
		worldPos = CApplication::WorldCastScreen(D3DXVECTOR3(collision.x, screenPos.y, screenPos.z));
		SetPos(D3DXVECTOR3(worldPos.x, pos.y, worldPos.z));
		screenPos = CApplication::ScreenCastWorld(GetPos());
		bCollision = true;
	}
	else if (screenPosUp.x >(float)CRenderer::SCREEN_WIDTH)
	{
		worldPos = CApplication::WorldCastScreen(D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH - collision.x, screenPos.y, screenPos.z));
		SetPos(D3DXVECTOR3(worldPos.x, pos.y, worldPos.z));
		screenPos = CApplication::ScreenCastWorld(GetPos());
		bCollision = true;
	}

	if (screenPosUp.y < 0.0f)
	{
		worldPos = CApplication::WorldCastScreen(D3DXVECTOR3(screenPos.x, collision.y, screenPos.z));
		SetPos(D3DXVECTOR3(worldPos.x, pos.y, worldPos.z));
		screenPos = CApplication::ScreenCastWorld(GetPos());
		bCollision = true;
	}
	else if (screenPosUnder.y >(float)CRenderer::SCREEN_HEIGHT)
	{
		worldPos = CApplication::WorldCastScreen(D3DXVECTOR3(screenPos.x, (float)CRenderer::SCREEN_HEIGHT - collision.y, screenPos.z));
		SetPos(D3DXVECTOR3(worldPos.x, pos.y, worldPos.z));
		screenPos = CApplication::ScreenCastWorld(GetPos());
		bCollision = true;
	}

	return bCollision;
}

