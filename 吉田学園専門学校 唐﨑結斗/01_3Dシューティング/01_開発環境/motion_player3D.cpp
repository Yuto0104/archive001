//=============================================================================
//
// 3D���[�V�����v���C���[�N���X(model3D.h)
// Author : �������l
// �T�v : 3D���[�V�����v���C���[�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "motion_player3D.h"
#include "motion.h"
#include "move.h"
#include "renderer.h"
#include "application.h"
#include "keyboard.h"
#include "sound.h"
#include "mouse.h"
#include "game.h"
#include "tutorial.h"

#include "calculation.h"
#include "bullet3D.h"
#include "follow_bullet3D.h"
#include "camera.h"
#include "life_manager.h"
#include "gauge2D.h"
#include "score.h"
#include "energy_gage.h"
#include "effect3D.h"
#include "particle.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************
const float CMotionPlayer3D::ROTATE_SPEED = (0.1f);

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : 3D���[�V�����v���C���[�𐶐�����
//=============================================================================
CMotionPlayer3D * CMotionPlayer3D::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CMotionPlayer3D *pMotionPlayer3D = nullptr;

	// �������̉��
	pMotionPlayer3D = new CMotionPlayer3D;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pMotionPlayer3D != nullptr);

	// ���l�̏�����
	pMotionPlayer3D->Init();

	// �C���X�^���X��Ԃ�
	return pMotionPlayer3D;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CMotionPlayer3D::CMotionPlayer3D()
{
	m_pEffect3D = nullptr;							// �G�t�F�N�g�̃C���X�^���X
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌���
	m_nNumMotion = TYPE_NEUTRAL;					// ���[�V�����^�C�v
	m_state = STATE_NEUTRAL;						// ���
	m_nCntShot = 0;									// �e���˂܂ł̃J�E���g
	m_nLife = 0;									// ����
	m_nInvalidLife = 0;								// �ǉ����C�t
	m_nEnergy = 0;									// �G�l���M�[
	m_nCntState = 0;								// ��Ԑ���̃J�E���g
	m_nCntFrame = 0;								// �t���[���J�E���g
	m_bPressShot = false;							// �������e���g�p���Ă邩�ǂ���
	m_bLockShot = false;							// �e���˂��\���ǂ���
	m_bFollowShot = false;							// �Ǐ]�e�𔭎˂��Ă��邩��
	m_bUse = false;									// �g�p��

	// �I�u�W�F�N�g�̎�ʐݒ�
	SetObjType(CObject::OBJTYPE_3DPLAYER);
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CMotionPlayer3D::~CMotionPlayer3D()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CMotionPlayer3D::Init()
{
	// ������
	CModel3D::Init();

	if (m_pMotion[0] == nullptr
		&& m_pMotion[1] == nullptr)
	{// ���[�V�������
		m_pMotion[0] = new CMotion("data/MOTION/white.txt");
		assert(m_pMotion[0] != nullptr);
		m_pMotion[1] = new CMotion("data/MOTION/black.txt");
		assert(m_pMotion[1] != nullptr);
	}

	if (m_pMove == nullptr)
	{// �ړ�
		m_pMove = new CMove;
		assert(m_pMove != nullptr);
	}

	// �ړ����̏�����
	m_pMove->SetMoving(1.0f, 15.0f, 0.0f, 0.1f);

	// �����o�ϐ��̏�����
	m_nNumMotion = 0;
	m_nNumMotionOld = m_nNumMotion;
	m_pMotion[0]->SetMotion(m_nNumMotion);
	m_pMotion[1]->SetMotion(m_nNumMotion);
	m_bMotion = true;
	m_bMotionBlend = false;
	SetColorType(CModel3D::TYPE_WHITE);
	SetColisonSize(D3DXVECTOR3(50.0f, 50.0f, 50.0f));
	m_nLife = 5;
	m_nInvalidLife = 0;
	SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetSize(D3DXVECTOR3(1.2f, 1.2f, 1.2f));
	m_pEffect3D = CEffect3D::Create();
	m_pEffect3D->SetPos(GetPos());
	m_pEffect3D->SetSize(D3DXVECTOR3(60.0f, 60.0f, 60.0f));
	m_pEffect3D->SetLife(-1);
	m_pEffect3D->SetRenderMode(CEffect3D::MODE_ADD);
	m_pEffect3D->LoadTex(27);
	m_bUse = true;

	switch (CApplication::GetMode())
	{
	case CApplication::MODE_GAME:
		// �v���C���[�̎擾
		CGame::SetUsePlayer(m_bUse);
		break;

	case CApplication::MODE_TUTORIAL:
		// �v���C���[�̎擾
		CTutorial::SetUsePlayer(m_bUse);
		break;

	default:
		break;
	}

	return E_NOTIMPL;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CMotionPlayer3D::Uninit()
{
	if (m_pMove != nullptr)
	{// �I������
		// �������̉��
		delete m_pMove;
		m_pMove = nullptr;
	}

	for (int nCntMotion = 0; nCntMotion < MAX_MOTION; nCntMotion++)
	{
		if (m_pMotion[nCntMotion] != nullptr)
		{// �I������
			m_pMotion[nCntMotion]->Uninit();

			// �������̉��
			delete m_pMotion[nCntMotion];
			m_pMotion[nCntMotion] = nullptr;
		}
	}	

	// �I��
	CModel3D::Uninit();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V���s��
//=============================================================================
void CMotionPlayer3D::Update()
{
	switch (CApplication::GetMode())
	{
	case CApplication::MODE_GAME:
		// �v���C���[�̎擾
		m_bUse = CGame::GetUsePlayer();
		break;

	case CApplication::MODE_TUTORIAL:
		// �v���C���[�̎擾
		m_bUse = CTutorial::GetUsePlayer();
		break;

	default:
		break;
	}

	if (m_bUse)
	{// ���̎擾
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 rot = GetRot();

		if (!m_bFollowShot)
		{// �j���[�g�������[�V�����̓���
			m_nNumMotion = TYPE_NEUTRAL;
		}

		// �ړ�
		pos += Move();

		// ��]
		Rotate();

		// �e�̔���
		Shot();

		// �G�l���M�[����
		Consumption();

		// �F�̕ύX
		ChangeColor();

		// ���[�V�����̐ݒ�
		MotionSet();

		// y���W�̏C��
		pos.y = 0.0f;

		// �ړ����̐ݒ�
		SetPos(pos);
		m_pEffect3D->SetPos(pos);

		if (GetColorType() == CObject::TYPE_WHITE)
		{
			m_pEffect3D->SetColor(D3DXCOLOR(0.5f, 0.7f, 1.0f, 0.5f));
		}
		else if (GetColorType() == CObject::TYPE_BLACK)
		{
			m_pEffect3D->SetColor(D3DXCOLOR(1.0f, 0.1f, 0.1f, 0.5f));
		}

		// �G�Ƃ̓����蔻��
		CollisionEnemy();

		// �X�N���[���̂����蔻��
		CollisionScreen();

		// ��Ԃ̐���
		SetState();

		// �X�V
		CModel3D::Update();

		// ���S����
		Death();
	}
	else if (!m_bUse)
	{
		switch (CApplication::GetMode())
		{
		case CApplication::MODE_GAME:
			// �J�E���g�A�b�v
			m_nCntFrame++;

			if (m_nCntFrame >= 40)
			{// �I��
				Uninit();
				CGame::SetGame(false);
			}

			break;

		case CApplication::MODE_TUTORIAL:
			Init();

			// ���C�t�̐ݒ�
			CTutorial::GetLifeManager()->SetLife();
			break;

		default:
			break;
		}	
	}
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CMotionPlayer3D::Draw()
{
	switch (CApplication::GetMode())
	{
	case CApplication::MODE_GAME:
		// �v���C���[�̎擾
		m_bUse = CGame::GetUsePlayer();
		break;

	case CApplication::MODE_TUTORIAL:
		// �v���C���[�̎擾
		m_bUse = CTutorial::GetUsePlayer();
		break;

	default:
		break;
	}

	if (m_bUse)
	{// �`��
		CModel3D::Draw();

		// ���[���h�}�g���b�N�X�̎擾
		D3DXMATRIX mtxWorld = GetMtxWorld();

		switch (m_state)
		{
		case CMotionPlayer3D::STATE_NEUTRAL:
			// �p�[�c�̕`��ݒ�
			m_pMotion[GetColorType() - 1]->SetParts(mtxWorld);
			break;

		case CMotionPlayer3D::STATE_DAMAGE:
			// �p�[�c�̕`��ݒ�
			m_pMotion[GetColorType() - 1]->SetParts(mtxWorld, D3DXCOLOR(0.5f, 0.0f, 0.0f, 1.0f));
			break;

		default:
			break;
		}
	}
}

//=============================================================================
// ��]
// Author : �������l
// �T�v : ��]���s��
//=============================================================================
void CMotionPlayer3D::Rotate()
{
	// �����̎擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	// �����̍X�V
	rot.y += (m_rotDest.y - rot.y) * ROTATE_SPEED;

	if (rot.y >= D3DX_PI)
	{// �ړ������̐��K��
		rot.y -= D3DX_PI * 2;
	}
	else if (rot.y <= -D3DX_PI)
	{// �ړ������̐��K��
		rot.y += D3DX_PI * 2;
	}

	// �����̐ݒ�
	//SetRot(rot);
}

//=============================================================================
// �ړ�
// Author : �������l
// �T�v : �ړ����s��
//=============================================================================
D3DXVECTOR3 CMotionPlayer3D::Move()
{
	// ���͏��̎擾
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	// �����o�ϐ��̎擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (pKeyboard->GetPress(DIK_W)
		|| pKeyboard->GetPress(DIK_A)
		|| pKeyboard->GetPress(DIK_D)
		|| pKeyboard->GetPress(DIK_S))
	{// �ړ��L�[�������ꂽ
		if (!m_bFollowShot)
		{// �ړ����[�V����
			m_nNumMotion = TYPE_MOVE;
		}

		if (pKeyboard->GetPress(DIK_W))
		{// [��]�L�[�������ꂽ��
			if (pKeyboard->GetPress(DIK_A))
			{// [��]�L�[�������ꂽ��
			 // �ړ������̍X�V
				m_rotDest.y = D3DX_PI * -0.25f;
			}
			else if (pKeyboard->GetPress(DIK_D))
			{// [��]�L�[�������ꂽ��
			 // �ړ������̍X�V
				m_rotDest.y = D3DX_PI * 0.25f;
			}
			else
			{// �ړ������̍X�V
				m_rotDest.y = D3DX_PI * 0.0f;
			}
		}
		else if (pKeyboard->GetPress(DIK_S))
		{// [��]�L�[�������ꂽ��
			if (pKeyboard->GetPress(DIK_A))
			{// [��]�L�[�������ꂽ��
			 // �ړ������̍X�V
				m_rotDest.y = D3DX_PI * -0.75f;
			}
			else if (pKeyboard->GetPress(DIK_D))
			{// [��]�L�[�������ꂽ��
			 // �ړ������̍X�V
				m_rotDest.y = D3DX_PI * 0.75f;
			}
			else
			{// �ړ������̍X�Vq
				m_rotDest.y = D3DX_PI;
			}
		}
		else if (pKeyboard->GetPress(DIK_A))
		{// [��]�L�[�������ꂽ��
		 // �ړ������̍X�V
			m_rotDest.y = D3DX_PI * -0.5f;
		}
		else if (pKeyboard->GetPress(DIK_D))
		{// [��]�L�[�������ꂽ��
		 // �ړ������̍X�V
			m_rotDest.y = D3DX_PI * 0.5f;
		}

		if (m_rotDest.y > D3DX_PI)
		{// �ړ������̐��K��
			m_rotDest.y -= D3DX_PI * 2;
		}
		else if (m_rotDest.y < -D3DX_PI)
		{// �ړ������̐��K��
			m_rotDest.y += D3DX_PI * 2;
		}

		// �ړ��ʂ̌v�Z
		move = D3DXVECTOR3(sinf(m_rotDest.y), 0.0f, cosf(m_rotDest.y));

		// �ړI�̌����̔��]
		m_rotDest.y -= D3DX_PI;
	}

	// �ړI�̌����̕␳
	if (m_rotDest.y - rot.y >= D3DX_PI)
	{// �ړ������̐��K��
		m_rotDest.y -= D3DX_PI * 2;
	}
	else if (m_rotDest.y - rot.y <= -D3DX_PI)
	{// �ړ������̐��K��
		m_rotDest.y += D3DX_PI * 2;
	}

	// ���C�W�����l�������ړ�
	m_pMove->Moving(move);

	return m_pMove->GetMove();
}

//=============================================================================
// �e�̔���
// Author : �������l
// �T�v : �L�[���͂��s��ꂽ�ꍇ�A�e�𔭎˂���
//=============================================================================
void CMotionPlayer3D::Shot()
{
	// �T�E���h���̎擾
	CSound *pSound = CApplication::GetSound();
	
	// ���͏��̎擾
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	// Object2D�̃����o�ϐ��̎擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 size = GetSize();

	// �ϐ��錾
	D3DXVECTOR3 bulletPos;		// �e�̔��ˈʒu
	CBullet3D *pBullet3D;		// 3D�e�̐���
	D3DXCOLOR bulletColor;		// �e�̐F

	if (GetColorType() == CObject::TYPE_WHITE)
	{// �e�̐F�̐ݒ�
		bulletColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if (GetColorType() == CObject::TYPE_BLACK)
	{// �e�̐F�̐ݒ�
		bulletColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	}

	if (pKeyboard->GetPress(DIK_SPACE)
		&& !m_bLockShot)
	{// �e�̔���
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

		// �e�̔��ˈʒu
		bulletPos = D3DXVECTOR3(0.0f, 18.0f, -45.0f);

		// ���[���h���W�ɃL���X�g
		bulletPos = WorldCastVtx(bulletPos, pos, rot);

		// �e�̐���
		pBullet3D = CBullet3D::Create();
		pBullet3D->SetPos(bulletPos);
		pBullet3D->SetSize(D3DXVECTOR3(10.0f, 10.0f, 0.0f));
		pBullet3D->SetMoveVec(D3DXVECTOR3(rot.x + D3DX_PI * -0.5f, rot.y, 0.0f));
		pBullet3D->SetSpeed(10.0f);
		pBullet3D->SetColor(bulletColor);
		pBullet3D->SetColorType(GetColorType());
		pBullet3D->SetParent(CObject::OBJTYPE_3DPLAYER);

		// �J�E���g�̏�����
		m_nCntShot = 0;

		// �v���X�I��
		m_bPressShot = true;

		// �e�����˂��ł��邩�ǂ���
		m_bLockShot = true;
	}

	if (pKeyboard->GetRelease(DIK_SPACE))
	{// �v���X�I�t
		m_bPressShot = false;
	}

	if (m_bPressShot)
	{// �v���X�I��
		m_nCntShot++;

		if (m_nCntShot >= MAX_CNT_SHOT)
		{// �J�E���g���e���˂܂ł̃J�E���g�ɒB����

			pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

			// �e�̔��ˈʒu
			bulletPos = D3DXVECTOR3(20.0f, 18.0f, -45.0f);

			// ���[���h���W�ɃL���X�g
			bulletPos = WorldCastVtx(bulletPos, pos, rot);

			// �e�̐���
			pBullet3D = CBullet3D::Create();
			pBullet3D->SetPos(bulletPos);
			pBullet3D->SetSize(D3DXVECTOR3(10.0f, 10.0f, 0.0f));
			pBullet3D->SetMoveVec(D3DXVECTOR3(rot.x + D3DX_PI * -0.5f, rot.y, 0.0f));
			pBullet3D->SetSpeed(10.0f);
			pBullet3D->SetColor(bulletColor);
			pBullet3D->SetColorType(GetColorType());
			pBullet3D->SetParent(CObject::OBJTYPE_3DPLAYER);

			// �e�̍��W�̎Z�o
			bulletPos = D3DXVECTOR3(-20.0f, 18.0f, -45.0f);

			// ���[���h���W�ɃL���X�g
			bulletPos = WorldCastVtx(bulletPos, pos, rot);

			// �e�̐���
			pBullet3D = CBullet3D::Create();
			pBullet3D->SetPos(bulletPos);
			pBullet3D->SetSize(D3DXVECTOR3(10.0f, 10.0f, 0.0f));
			pBullet3D->SetMoveVec(D3DXVECTOR3(rot.x + D3DX_PI * -0.5f, rot.y, 0.0f));
			pBullet3D->SetSpeed(10.0f);
			pBullet3D->SetColor(bulletColor);
			pBullet3D->SetColorType(GetColorType());
			pBullet3D->SetParent(CObject::OBJTYPE_3DPLAYER);

			// �J�E���g�̏�����
			m_nCntShot = 0;
		}
	}
	else if (m_bLockShot)
	{// ���b�N������Ă�ꍇ
		m_nCntShot++;

		if (m_nCntShot >= MAX_CNT_SHOT)
		{// �J�E���g�̏�����
			m_nCntShot = 0;
			m_bLockShot = false;
		}
	}
}

//=============================================================================
// �X�N���[���̂����蔻��
// Author : �������l
// �T�v : �X�N���[���ƃv���C���[�̂����蔻����s��
//=============================================================================
void CMotionPlayer3D::CollisionScreen()
{
	// �ʒu�̎擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 worldPos;

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
	}
	else if (screenPosUp.x > (float)CRenderer::SCREEN_WIDTH)
	{
		worldPos = CApplication::WorldCastScreen(D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH - collision.x, screenPos.y, screenPos.z));
		SetPos(D3DXVECTOR3(worldPos.x, pos.y, worldPos.z));
		screenPos = CApplication::ScreenCastWorld(GetPos());
	}

	if (screenPosUp.y < 0.0f)
	{
		worldPos = CApplication::WorldCastScreen(D3DXVECTOR3(screenPos.x, collision.y, screenPos.z));
		SetPos(D3DXVECTOR3(worldPos.x, pos.y, worldPos.z));
		screenPos = CApplication::ScreenCastWorld(GetPos());
	}
	else if (screenPosUnder.y > (float)CRenderer::SCREEN_HEIGHT)
	{
		worldPos = CApplication::WorldCastScreen(D3DXVECTOR3(screenPos.x, (float)CRenderer::SCREEN_HEIGHT - collision.y, screenPos.z));
		SetPos(D3DXVECTOR3(worldPos.x, pos.y, worldPos.z));
		screenPos = CApplication::ScreenCastWorld(GetPos());
	}
}

//=============================================================================
// �F�̕ύX
// Author : �������l
// �T�v : �L�[���������ƐF��ύX����
//=============================================================================
void CMotionPlayer3D::ChangeColor()
{
	// �T�E���h���̎擾
	CSound *pSound = CApplication::GetSound();

	// ���͏��̎擾
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_Q))
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_TRANCEFARM);

		if (GetColorType() == CObject::TYPE_WHITE)
		{
			SetColorType(CObject::TYPE_BLACK);
		}
		else if (GetColorType() == CObject::TYPE_BLACK)
		{
			SetColorType(CObject::TYPE_WHITE);
		}
	}
}

//=============================================================================
// ���[�V�����̐ݒ�
// Author : �������l
// �T�v : ���[�V�����̕ύX�⃂�[�V�����u�����h�̐ݒ���s��
//=============================================================================
void CMotionPlayer3D::MotionSet()
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	m_nNumMotionOld = m_nNumMotion;

	if (!m_bMotion)
	{// �g�p���Ă郂�[�V�������Ȃ��ꍇ
		m_nNumMotion = TYPE_NEUTRAL;
	}

	if (m_nNumMotionOld != m_nNumMotion)
	{// ���[�V�����^�C�v���ύX���ꂽ��
		m_pMotion[GetColorType() - 1]->CntReset((int)(m_nNumMotionOld));
		m_bMotionBlend = true;
	}

	if (m_bMotionBlend)
	{// ���[�V�����u�����h���g�p���Ă�
		m_bMotionBlend = m_pMotion[GetColorType() - 1]->MotionBlend((int)(m_nNumMotion));
	}
	else if (!m_bMotionBlend)
	{// ���[�V�����u�����h���g�p���ĂȂ��ꍇ
		m_bMotion = m_pMotion[GetColorType() - 1]->PlayMotion((int)(m_nNumMotion));
		m_bFollowShot = false;
	}
}

//=============================================================================
// ��
// Author : �������l
// �T�v : ���C�t�̉񕜂��s��
//=============================================================================
void CMotionPlayer3D::Recovery()
{
	// �T�E���h���̎擾
	CSound *pSound = CApplication::GetSound();

	if (m_nLife < MAX_LIFE
		&& m_nEnergy >= ENERGY_RECOVERY)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_HEEL);

		int nRecoveryEnergy = (int)ENERGY_RECOVERY;

		// �G�l���M�[�̏���
		Charge(-nRecoveryEnergy);

		m_nLife++;

		if (m_nLife >= MAX_LIFE)
		{
			m_nLife = MAX_LIFE;
		}

		switch (CApplication::GetMode())
		{
		case CApplication::MODE_GAME:
			// ���C�t�̐ݒ�
			CGame::GetLifeManager()->SetLife();
			break;

		case CApplication::MODE_TUTORIAL:
			// ���C�t�̐ݒ�
			CTutorial::GetLifeManager()->SetLife();
			break;

		default:
			break;
		}

		// �ϐ��錾
		D3DXVECTOR3 pos = GetPos();

		// �p�[�e�B�N���̐���
		CParticle *pParticle = CParticle::Create();
		pParticle->SetPos(pos);
		pParticle->SetSize(D3DXVECTOR3(10.0f, 10.0f, 0.0f));
		pParticle->SetPopRange(D3DXVECTOR3(100.0f, 0.0f, 100.0f));
		pParticle->SetSpeed(10.0f);
		pParticle->SetEffectLife(60);
		pParticle->SetMoveVec(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		pParticle->SetLife(10);
		pParticle->SetColor(D3DXCOLOR(0.1f, 1.0f, 0.5f, 1.0f));
		pParticle->SetMaxEffect(5);

		m_bRecovery = true;
	}
}

//=============================================================================
// �Ǐ]�e�̔���
// Author : �������l
// �T�v : �Ǐ]�e�𔭎˂���
//=============================================================================
void CMotionPlayer3D::FollowShot()
{
	// �T�E���h���̎擾
	CSound *pSound = CApplication::GetSound();

	if (m_nEnergy >= ENERGY_FOLLOW_SHOT)
	{
		// �U�����[�V����
		m_nNumMotion = TYPE_ATTACK;
		m_bFollowShot = true;

		int nFollowShotEnergy = (int)ENERGY_FOLLOW_SHOT;

		// �G�l���M�[�̏���
		Charge(-nFollowShotEnergy);

		// Object2D�̃����o�ϐ��̎擾
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 rot = GetRot();

		// �ϐ��錾
		D3DXVECTOR3 bulletPos;					// �e�̔��ˈʒu
		CFollowBullet3D *pFollowBullet3D;		// �Ǐ]�e�̐���
		D3DXCOLOR bulletColor;					// �e�̐F

		if (GetColorType() == CObject::TYPE_WHITE)
		{// �e�̐F�̐ݒ�
			bulletColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else if (GetColorType() == CObject::TYPE_BLACK)
		{// �e�̐F�̐ݒ�
			bulletColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		}

		// �e�̔��ˈʒu
		bulletPos = D3DXVECTOR3(0.0f, 18.0f, 45.0f);

		// ���[���h���W�ɃL���X�g
		bulletPos = WorldCastVtx(bulletPos, pos, rot);

		// �e�̐���
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

			float fAttRot = 0.5f / 4 * nCnt;
			pFollowBullet3D = CFollowBullet3D::Create();
			pFollowBullet3D->SetPos(bulletPos);
			pFollowBullet3D->SetSize(D3DXVECTOR3(10.0f, 10.0f, 0.0f));
			pFollowBullet3D->SetMoveVec(D3DXVECTOR3(rot.x + D3DX_PI * -0.5f, rot.y - D3DX_PI * (0.5f - fAttRot), 0.0f));
			pFollowBullet3D->SetSpeed(30.0f);
			pFollowBullet3D->SetColor(bulletColor);
			pFollowBullet3D->SetColorType(GetColorType());
			pFollowBullet3D->SetCoefficient(0.01f);
			pFollowBullet3D->SetAddCoefficient(0.01f);
			pFollowBullet3D->SetParent(CObject::OBJTYPE_3DPLAYER);

			pFollowBullet3D = CFollowBullet3D::Create();
			pFollowBullet3D->SetPos(bulletPos);
			pFollowBullet3D->SetSize(D3DXVECTOR3(10.0f, 10.0f, 0.0f));
			pFollowBullet3D->SetMoveVec(D3DXVECTOR3(rot.x + D3DX_PI * -0.5f, rot.y - D3DX_PI * (-0.5f + fAttRot), 0.0f));
			pFollowBullet3D->SetSpeed(30.0f);
			pFollowBullet3D->SetColor(bulletColor);
			pFollowBullet3D->SetColorType(GetColorType());
			pFollowBullet3D->SetCoefficient(0.01f);
			pFollowBullet3D->SetAddCoefficient(0.01f);
			pFollowBullet3D->SetParent(CObject::OBJTYPE_3DPLAYER);
		}
	}
}

//=============================================================================
// �G�l���M�[����
// Author : �������l
// �T�v : �G�l���M�[������A�������s��
//=============================================================================
void CMotionPlayer3D::Consumption()
{
	// ���͏��̎擾
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	if (pKeyboard->GetPress(DIK_RETURN)
		&& !m_bPressConsumption)
	{// �e�̔���
		// �J�E���g�̏�����
		m_nCntConsumption = 0;

		// �v���X�I��
		m_bPressConsumption = true;
	}

	if (pKeyboard->GetRelease(DIK_RETURN))
	{// �v���X�I�t
		m_bPressConsumption = false;

		if (m_bRecovery)
		{
			m_bRecovery = false;
		}
		else
		{
			FollowShot();
		}

		m_nCntConsumption = 0;
	}

	if (m_bPressConsumption)
	{// �v���X�I��
		m_nCntConsumption++;

		if (m_nCntConsumption >= MAX_CNT_RECOVERY)
		{// �J�E���g���e���˂܂ł̃J�E���g�ɒB����
			// �J�E���g�̏�����
			m_nCntConsumption = 0;

			// ��
			Recovery();
		}
	}
}

//=============================================================================
// ��Ԃ̐���
// Author : �������l
// �T�v : ��Ԃ̐�����s��
//=============================================================================
void CMotionPlayer3D::SetState()
{
	switch (m_state)
	{
	case CMotionPlayer3D::STATE_NEUTRAL:
		break;

	case CMotionPlayer3D::STATE_DAMAGE:
		m_nCntState++;

		if (m_nCntState >= INVINCIBLE_TIME)
		{
			m_nCntState = 0;
			m_state = STATE_NEUTRAL;
		}

		break;

	case CMotionPlayer3D::MAX_STATE:
		break;

	default:
		break;
	}
}

//=============================================================================
// �G�Ƃ̓����蔻��
// Author : �������l
// �T�v : �G�Ƃ̓����蔻��
//=============================================================================
void CMotionPlayer3D::CollisionEnemy()
{
	for (int nCntPriority = 0; nCntPriority < CObject::MAX_LEVEL; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			// �I�u�W�F�N�g�C���X�^���X�̎擾
			CObject *pObject = CObject::MyGetObject(nCntPriority, nCntObj);

			if (pObject != nullptr)
			{
				if ((pObject->GetObjType() == CObject::OBJTYPE_3DENEMY
					|| pObject->GetObjType() == CObject::OBJTYPE_3DBOSS))
				{// �^�C�v����v�����ꍇ
					if (ColisonSphere3D(pObject, GetColisonSize(), pObject->GetColisonSize(), true))
					{
						Hit();
						break;
					}
				}
			}
		}
	}
}

//=============================================================================
// ���S����
// Author : �������l
// �T�v : ���ʂƂ��̏������s��
//=============================================================================
void CMotionPlayer3D::Death()
{
	if (m_nLife == 0)
	{
		// �T�E���h���̎擾
		CSound *pSound = CApplication::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);

		// �ϐ��錾
		D3DXVECTOR3 pos = GetPos();
		m_pEffect3D->Uninit();

		// �p�[�e�B�N���̐���
		CParticle *pParticle = CParticle::Create();
		pParticle->SetPos(pos);
		pParticle->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		pParticle->SetPopRange(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
		pParticle->SetSpeed(5.0f);
		pParticle->SetEffectLife(30);
		pParticle->SetMoveVec(D3DXVECTOR3(D3DX_PI * 2.0f, D3DX_PI * 2.0f, 0.0f));
		pParticle->SetLife(10);
		pParticle->SetColor(D3DXCOLOR(1.0f, 0.4f, 0.1f, 1.0f));
		pParticle->SetMaxEffect(5);

		switch (CApplication::GetMode())
		{
		case CApplication::MODE_GAME:
			// �v���C���[�̎擾
			CGame::SetUsePlayer(false);
			break;

		case CApplication::MODE_TUTORIAL:
			// �v���C���[�̎擾
			CTutorial::SetUsePlayer(false);
			break;

		default:
			break;
		}
	}
}

//=============================================================================
// �q�b�g
// Author : �������l
// �T�v : �_���[�W��^����
//=============================================================================
void CMotionPlayer3D::Hit()
{
	// �T�E���h���̎擾
	CSound *pSound = CApplication::GetSound();

	if (m_state == STATE_NEUTRAL)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_HIT);

		m_state = STATE_DAMAGE;

		if (m_nInvalidLife > 0)
		{// �ǉ����C�t�̏���
			m_nInvalidLife--;

			if (m_nInvalidLife <= 0)
			{
				m_nInvalidLife = 0;
			}
		}
		else
		{// ���C�t�̏���
			m_nLife--;

			if (m_nLife <= 0)
			{
				m_nLife = 0;
			}
		}

		switch (CApplication::GetMode())
		{
		case CApplication::MODE_GAME:
			// ���C�t�̐ݒ�
			CGame::GetLifeManager()->SetLife();
			break;

		case CApplication::MODE_TUTORIAL:
			// ���C�t�̐ݒ�
			CTutorial::GetLifeManager()->SetLife();
			break;

		default:
			break;
		}
	}
}

//=============================================================================
// �`���[�W
// Author : �������l
// �T�v : �G�l���M�[���z������
//=============================================================================
void CMotionPlayer3D::Charge(const int nEnergy)
{
	CEnergyGage *pEnergyGage = nullptr;

	switch (CApplication::GetMode())
	{
	case CApplication::MODE_GAME:
		pEnergyGage = CGame::GetEnergyGage();
		break;

	case CApplication::MODE_TUTORIAL:
		pEnergyGage = CTutorial::GetEnergyGage();
		break;

	default:
		break;
	}

	CGauge2D *pEnergyGauge2D = pEnergyGage->GetGauge2D();
	CScore *pEnergy = pEnergyGage->GetScore();

	// �G�l���M�[�̃C���N�������g
	int nEnergyPoint = pEnergy->GetScore();
	int nEnergyPointOld = nEnergyPoint;
	int nDiffEP = 0;

	// �G�l���M�[�̉��Z
	nEnergyPoint += nEnergy;

	// ���Z�l�̍����̎Z�o
	nDiffEP = nEnergyPoint - nEnergyPointOld;

	// ���l�̐ݒ�
	pEnergy->AddScore(nDiffEP);

	if (nEnergyPoint >= MAX_ENERGY)
	{
		nDiffEP = MAX_ENERGY - nEnergyPoint;
		nEnergyPoint = MAX_ENERGY;
		pEnergy->AddScore(nDiffEP);
	}
	else if (nEnergyPoint <= 0)
	{
		nDiffEP = 0 - nEnergyPoint;
		nEnergyPoint = 0;
		pEnergy->AddScore(nDiffEP);
	}

	// �Q�[�W�̐ݒ�
	pEnergyGauge2D->SetNumber((float)nEnergyPoint);

	// �G�l���M�[�Q�[�W�̐ݒ�
	m_nEnergy = nEnergyPoint;
}


