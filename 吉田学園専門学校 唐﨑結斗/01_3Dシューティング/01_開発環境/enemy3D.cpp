//=============================================================================
//
// 3D�G�l�~�[�N���X(enemy3D.cpp)
// Author : �������l
// �T�v : 3D�G�l�~�[�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>
#include <time.h>

#include "enemy3D.h"
#include "renderer.h"
#include "application.h"
#include "sound.h"
#include "score.h"
#include "bullet3D.h"
#include "follow_bullet3D.h"
#include "game.h"
#include "motion_player3D.h"
#include "particle.h"
#include "effect3D.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̒�`
//*****************************************************************************
const float CEnemy3D::LINTERN_BULLET_SPAWN_RANGE = 30.0f;				// �Ԃ��e�̐����͈�
const float CEnemy3D::LINTERN_BULLET_MOVE_VEC = 0.15f;					// �Ԃ��e�̈ړ�����
int CEnemy3D::s_nCntSetEnemy = 0;										// �G�̃J�E���g

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : 3D�G�l�~�[�𐶐�����
//=============================================================================
CEnemy3D * CEnemy3D::Create(const int nNumModel)
{
	// �I�u�W�F�N�g�C���X�^���X
	CEnemy3D *pEnemy3D = nullptr;

	// �������̉��
	pEnemy3D = new CEnemy3D;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pEnemy3D != nullptr);

	// ���l�̏�����
	pEnemy3D->Init(nNumModel);

	// �C���X�^���X��Ԃ�
	return pEnemy3D;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CEnemy3D::CEnemy3D()
{// �I�u�W�F�N�g�̎�ʐݒ�
	SetObjType(CObject::OBJTYPE_3DENEMY);

	m_pEffect3D = nullptr;								// �G�t�F�N�g�̃C���X�^���X
	m_moveMode = MODE_NONE;								// �ړ����[�h
	m_shotMode = SHOTMODE_NONE;							// �e�̎��
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ړ���
	m_moveData = {};									// �ړ����
	m_fSpeed = 10.0f;									// �ړ����x
	m_fMoveVec = 0.0f;									// �ړ�����
	m_fAddMoveVec = 0.0f;								// �ړ������̉��Z�l
	m_fWave = 0.0f;										// �g
	m_fWaveLength = 0.0f;								// �g��
	m_fWaveSize = 0.0f;									// �g�̑傫��
	m_fBulletRot = 0.0f;								// �e�̔��˕���
	m_fDiffusionWidth = 0.0f;							// �e�̊g�U�͈�
	m_fBulletSpeed = 0.0f;								// �e��
	m_fCoeffBullet = 0.0f;								// �e�̒Ǐ]�̌����W��
	m_nMaxBullet = 0;									// �e�̔��ː�
	m_nCntKey = 0;										// �L�[�J�E���g
	m_nCntFrame = 0;									// �t���[���J�E���g
	m_nLife = 0;										// �̗�
	m_nScore = 0;										// �X�R�A
	m_nCntShot = 0;										// �e���˂܂ł̃J�E���g
	m_nMaxShot = 0;										// �e���˂���J�E���g
	m_bMove = false;									// �ړ����s���Ă���
	m_bUse = false;										// �g�p����Ă��邩�ǂ���

	// �^�������̏�����
	srand((unsigned int)time(NULL));

	// �ݒu�����G�̐����C���N�������g
	s_nCntSetEnemy++;
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CEnemy3D::~CEnemy3D()
{
	// �ݒu�����G�̐����f�N�������g
	s_nCntSetEnemy--;
}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CEnemy3D::Init(const int nNumModel)
{
	// ���f���̏�����
	CModel3D::Init(nNumModel);

	// �����蔻��̐ݒ�
	SetColisonPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetColisonSize(D3DXVECTOR3(50.0f, 50.0f, 50.0f));

	// �G�t�F�N�g�̐ݒ�
	m_pEffect3D = CEffect3D::Create();
	m_pEffect3D->SetPos(GetPos());
	m_pEffect3D->SetSize(GetColisonSize());
	m_pEffect3D->SetLife(-1);
	m_pEffect3D->SetRenderMode(CEffect3D::MODE_ADD);
	m_pEffect3D->LoadTex(27);

	// �̗�
	m_nLife = 100;

	// �X�R�A
	m_nScore = 100;

	// �e���˂���J�E���g
	m_nMaxShot = 180;

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CEnemy3D::Uninit()
{
	// ���f���̏I��
	CModel3D::Uninit();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : 2D�X�V���s��
//=============================================================================
void CEnemy3D::Update()
{
	// �ϐ��錾
	D3DXVECTOR3 pos = GetPos();

	if (m_bMove)
	{
		// �ړ����̐ݒ�
		Move();

		// �ړ����̃R�s�[
		SetMoveCopy();
	}
	else
	{
		m_moveMode = MODE_NONE;
	}

	// �ړ��ʂ̐ݒ�
	SetMove();

	// �e�̔���
	Shot();

	// �ړ�
	pos += m_move;

	// �ʒu�̐ݒ�
	SetPos(pos);
	m_pEffect3D->SetPos(pos);
	m_pEffect3D->SetSize(GetColisonSize());

	if (GetColorType() == CObject::TYPE_WHITE)
	{
		m_pEffect3D->SetColor(D3DXCOLOR(0.5f, 0.7f, 1.0f, 0.5f));
	}
	else if (GetColorType() == CObject::TYPE_BLACK)
	{
		m_pEffect3D->SetColor(D3DXCOLOR(1.0f, 0.1f, 0.1f, 0.5f));
	}

	// �X�N���[�����̔���
	ScreenIn();

	// ���f���̍X�V
	CModel3D::Update();
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : 2D�`����s��
//=============================================================================
void CEnemy3D::Draw()
{
	// ���f���̕`��
	CModel3D::Draw();
}

//=============================================================================
// �q�b�g
// Author : �������l
// �T�v : �������̃_���[�W��^����
//=============================================================================
void CEnemy3D::Hit(COLOR_TYPE colorType, int nAttack)
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
			m_pEffect3D->Uninit();

			// �f�[�^�i�[�p�ϐ�
			CBullet3D * pBullet3D;
			D3DXVECTOR3 pos = GetPos();
			D3DXVECTOR3 rot = GetRot();
			D3DXVECTOR3 randLinternBulletSpawnRange = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			float fRandMoveVec = 0.0f;

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

			// �e�̐F
			D3DXCOLOR bulletColor;

			if (MyColorType == CObject::TYPE_WHITE)
			{// �e�̐F�̐ݒ�
				bulletColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else if (MyColorType == CObject::TYPE_BLACK)
			{// �e�̐F�̐ݒ�
				bulletColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			}

			for (int nCntBullet = 0; nCntBullet < MAX_LINTERN_BULLET; nCntBullet++)
			{// �����̐ݒ�
				randLinternBulletSpawnRange.x = pos.x - LINTERN_BULLET_SPAWN_RANGE + ((float)(rand() % (int)(LINTERN_BULLET_SPAWN_RANGE * 200.0f) / 100));
				randLinternBulletSpawnRange.z = pos.z - LINTERN_BULLET_SPAWN_RANGE + ((float)(rand() % (int)(LINTERN_BULLET_SPAWN_RANGE * 200.0f) / 100));
				fRandMoveVec = rot.y - D3DX_PI * LINTERN_BULLET_MOVE_VEC + D3DX_PI * ((float)(rand() % (int)(LINTERN_BULLET_MOVE_VEC * 200.0f)) / 100);

				// �e�̐���
				pBullet3D = CBullet3D::Create();
				pBullet3D->SetPos(D3DXVECTOR3(randLinternBulletSpawnRange.x, pos.y, randLinternBulletSpawnRange.z));
				pBullet3D->SetSize(D3DXVECTOR3(5.0f, 5.0f, 0.0f));
				pBullet3D->SetMoveVec(D3DXVECTOR3(rot.x + D3DX_PI * -0.5f, fRandMoveVec, 0.0f));
				pBullet3D->SetSpeed(5.0f);
				pBullet3D->SetColor(bulletColor);
				pBullet3D->SetColorType(MyColorType);
				pBullet3D->SetParent(CObject::OBJTYPE_3DENEMY);
			}

			Uninit();
		}
	}
}

//=============================================================================
// �ړ����̃Z�b�^�[
// Author : �������l
// �T�v : �ړ����̃Z�b�^�[
//=============================================================================
void CEnemy3D::SetMoveData(ENEMY_MOVE moveData)
{
	m_moveData = moveData;
	m_bMove = true;
}

//=============================================================================
// �e�̔���
// Author : �������l
// �T�v : �e�𔭎˂���
//=============================================================================
void CEnemy3D::Shot()
{
	// �T�E���h���̎擾
	CSound *pSound = CApplication::GetSound();

	D3DXVECTOR3 rot = GetRot();
	D3DXCOLOR bulletColor;					// �e�̐F

	if (GetColorType() == CObject::TYPE_WHITE)
	{// �e�̐F�̐ݒ�
		bulletColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if (GetColorType() == CObject::TYPE_BLACK)
	{// �e�̐F�̐ݒ�
		bulletColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	}

	m_nCntShot++;

	if (m_nCntShot % m_nMaxShot == 0)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

		// �v�Z�p�ϐ��̐ݒ�
		CBullet3D * pBullet3D = nullptr;
		CFollowBullet3D* pFollowBullet3D = nullptr;
		CMotionPlayer3D* pPlayer = nullptr;
		D3DXVECTOR3 targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 diffPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 diffRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		float fBulletRot = 0.0f;

		switch (m_shotMode)
		{
		case CEnemy3D::SHOTMODE_NORMAL:
			// �e�̐���
			pBullet3D = CBullet3D::Create();
			pBullet3D->SetPos(GetPos());
			pBullet3D->SetSize(D3DXVECTOR3(10.0f, 10.0f, 0.0f));
			pBullet3D->SetMoveVec(D3DXVECTOR3(rot.x + D3DX_PI * -0.5f, rot.y + m_fBulletRot, 0.0f));
			pBullet3D->SetSpeed(m_fBulletSpeed);
			pBullet3D->SetColor(bulletColor);
			pBullet3D->SetColorType(GetColorType());
			pBullet3D->SetParent(CObject::OBJTYPE_3DENEMY);
			break;

		case CEnemy3D::SHOTMODE_DIFFUSION:

			for (int nCntBullet = 0; nCntBullet < m_nMaxBullet; nCntBullet++)
			{// �e�̔��ˊp�x�̐ݒ�
				fBulletRot = m_fBulletRot - (m_fDiffusionWidth / 2) + (m_fDiffusionWidth / m_nMaxBullet * nCntBullet);
				fBulletRot = CApplication::RotNormalization(fBulletRot);

				// �e�̐���
				pBullet3D = CBullet3D::Create();
				pBullet3D->SetPos(GetPos());
				pBullet3D->SetSize(D3DXVECTOR3(10.0f, 10.0f, 0.0f));
				pBullet3D->SetMoveVec(D3DXVECTOR3(rot.x + D3DX_PI * -0.5f, rot.y + fBulletRot, 0.0f));
				pBullet3D->SetSpeed(m_fBulletSpeed);
				pBullet3D->SetColor(bulletColor);
				pBullet3D->SetColorType(GetColorType());
				pBullet3D->SetParent(CObject::OBJTYPE_3DENEMY);
			}

			break;

		case CEnemy3D::SHOTMODE_SNIPE:
			if (CGame::GetUsePlayer())
			{// �ړI�̌����̎Z�o
				pPlayer = CGame::GetMotionPlayer3D();
				targetPos = pPlayer->GetPos();
				diffPos = targetPos - GetPos();
				diffRot.y = atan2f(diffPos.x, diffPos.z);
				diffRot.x = atan2f(sqrtf((diffPos.x * diffPos.x) + (diffPos.z * diffPos.z)), diffPos.y);
				diffRot.z = 0.0f;
			}

			// �e�̐���
			pBullet3D = CBullet3D::Create();
			pBullet3D->SetPos(GetPos());
			pBullet3D->SetSize(D3DXVECTOR3(10.0f, 10.0f, 0.0f));
			pBullet3D->SetMoveVec(diffRot);
			pBullet3D->SetSpeed(m_fBulletSpeed);
			pBullet3D->SetColor(bulletColor);
			pBullet3D->SetColorType(GetColorType());
			pBullet3D->SetParent(CObject::OBJTYPE_3DENEMY);
			break;

		case CEnemy3D::SHOTMODE_FOLLOW:
			// �e�̐���
			pFollowBullet3D = CFollowBullet3D::Create();
			pFollowBullet3D->SetPos(GetPos());
			pFollowBullet3D->SetSize(D3DXVECTOR3(10.0f, 10.0f, 0.0f));
			pFollowBullet3D->SetMoveVec(D3DXVECTOR3(rot.x + D3DX_PI * -0.5f, rot.y, 0.0f));
			pFollowBullet3D->SetSpeed(m_fBulletSpeed);
			pFollowBullet3D->SetCoefficient(m_fCoeffBullet);
			pFollowBullet3D->SetColor(bulletColor);
			pFollowBullet3D->SetColorType(GetColorType());
			pFollowBullet3D->SetParent(CObject::OBJTYPE_3DENEMY);
			break;

		case CEnemy3D::SHOTMODE_NONE:
			break;

		default:
			assert(false);
			break;
		}
		
	}
}

//=============================================================================
// �ړ��ʂ̐ݒ�
// Author : �������l
// �T�v : �ړ��ʂ̐ݒ�
//=============================================================================
void CEnemy3D::SetMove()
{
	switch (m_moveMode)
	{
	case CEnemy3D::MODE_NONE:
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		break;

	case CEnemy3D::MODE_NORMAL:
		m_move.x = sinf(m_fMoveVec) * m_fSpeed;
		m_move.z = cosf(m_fMoveVec) * m_fSpeed;
		break;

	case CEnemy3D::MODE_SIN:
		m_fWave += m_fWaveLength;
		m_move.x = sinf(m_fMoveVec) * m_fSpeed;
		m_move.z = sinf(m_fWave) * m_fWaveSize;
		break;

	case CEnemy3D::MODE_COS:
		m_fWave += m_fWaveLength;
		m_move.x = cosf(m_fWave) * m_fWaveSize;
		m_move.z = cosf(m_fMoveVec) * m_fSpeed;
		break;

	case CEnemy3D::MODE_CIRCLE:
		m_fMoveVec += m_fAddMoveVec;
		m_fMoveVec = CApplication::RotNormalization(m_fMoveVec);
		m_move.x = sinf(m_fMoveVec) * m_fSpeed;
		m_move.z = cosf(m_fMoveVec) * m_fSpeed;
		break;

	default:
		break;
	}
}

//=============================================================================
// �ړ����̐ݒ�
// Author : �������l
// �T�v : �ړ����̐ݒ�
//=============================================================================
void CEnemy3D::Move()
{
	// �ړ��t���[���̃C���N�������g
	m_nCntFrame++;

	if (m_nCntFrame >= m_moveData.moveKey[m_nCntKey].nFrame)
	{
		m_nCntFrame = 0;
		m_nCntKey++;

		if (m_nCntKey >= m_moveData.nMaxKey)
		{
			if (m_moveData.bLoop)
			{
				m_nCntKey = 0;
			}
			else
			{
				m_bMove = false;
			}
		}
	}
}

//=============================================================================
// �ړ����̃R�s�[
// Author : �������l
// �T�v : �ړ����̃R�s�[
//=============================================================================
void CEnemy3D::SetMoveCopy()
{
	m_moveMode = m_moveData.moveKey[m_nCntKey].moveMode;				// �ړ����[�h
	m_fMoveVec = m_moveData.moveKey[m_nCntKey].fMoveVec;				// �ړ�����
	m_fAddMoveVec = m_moveData.moveKey[m_nCntKey].fAddMoveVec;			// �ړ������̉��Z�l
	m_fWaveLength = m_moveData.moveKey[m_nCntKey].fWaveLength;			// �g��
	m_fWaveSize = m_moveData.moveKey[m_nCntKey].fWaveSize;				// �g�̑傫��
	m_fSpeed = m_moveData.moveKey[m_nCntKey].fSpeed;					// �ړ����x
}

//=============================================================================
// �X�N���[���̔���
// Author : �������l
// �T�v : �X�N���[�����ɂ���Ƃ��A�G���g�p�\�ɂ���
//=============================================================================
void CEnemy3D::ScreenIn()
{
	// �ʒu�̎擾
	D3DXVECTOR3 pos = GetPos();

	// �����蔻��̎擾
	D3DXVECTOR3 collision = CObject::GetColisonSize();

	// �X�N���[�����W�ɃL���X�g
	D3DXVECTOR3 screenPos = CApplication::ScreenCastWorld(pos);

	if (screenPos.x >= 0.0f
		&& screenPos.x <= (float)CRenderer::SCREEN_WIDTH
		&& screenPos.y >= 0.0f
		&& screenPos.y <= (float)CRenderer::SCREEN_HEIGHT
		&& !m_bUse)
	{
		m_bUse = true;
	}
	else if ((screenPos.x + collision.x <= 0.0f
		|| screenPos.x - collision.x >= (float)CRenderer::SCREEN_WIDTH
		|| screenPos.y + collision.y <= 0.0f
		|| screenPos.y - collision.y >= (float)CRenderer::SCREEN_HEIGHT)
		&& m_bUse)
	{
		m_pEffect3D->Uninit();
		Uninit();
	}
}
