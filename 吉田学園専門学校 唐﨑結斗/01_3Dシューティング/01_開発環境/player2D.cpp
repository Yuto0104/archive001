//=============================================================================
//
// 2D�v���C���[(player2D.h)
// Author : �������l
// �T�v : 2D�v���C���[�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "player2D.h"
#include "bullet2D.h"
#include "renderer.h"
#include "application.h"
#include "keyboard.h"
#include "mouse.h"
#include "sound.h"
#include "move.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************
static const float				MAX_SIZE = (50.0f);				// �傫��
static const float				SPEED = (0.5f);					// �ړ����x
static const float				MAX_SPEED = (15.0f);			// �ō����x
static const float				MIN_SPEED = (0.0f);				// �Œᑬ�x
static const float				FRICTION = (0.1f);				// ���C�W��
static const float				MAX_BULLET_SPEED = (20.0f);		// �e�̑��x
static const unsigned int		MAX_CNT_SHOT = (15);			// �e���˂܂ł̃J�E���g

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : 2D�v���C���[�𐶐�����
//=============================================================================
CPlayer2D * CPlayer2D::Create(void)
{
	// �v���C���[�C���X�^���X
	CPlayer2D *pPlayer2D = nullptr;

	pPlayer2D = new CPlayer2D;

	if (pPlayer2D != nullptr)
	{// ���l�̏�����
		pPlayer2D->Init();
	}
	else
	{// �������̊m�ۂ��ł��Ȃ�����
		assert(false);
	}

	// �C���X�^���X��Ԃ�
	return pPlayer2D;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CPlayer2D::CPlayer2D()
{
	m_pMove = new CMove;
	assert(m_pMove != nullptr);
	m_nCntShot = 0;
	SetObjType(CObject::OBJTYPE_2DPLAYER);
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CPlayer2D::~CPlayer2D()
{

}

//=============================================================================
// �v���C���[�̏�����
// Author : �������l
// �T�v : �e�N�X�`���̐ݒ肵�A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CPlayer2D::Init()
{
	// �v���C���[2D�̏�����
	CObject2D::Init();

	// �e�N�X�`���̐ݒ�
	LoadTex(2);

	// �T�C�Y
	D3DXVECTOR3 size = GetSize();
	size = D3DXVECTOR3(MAX_SIZE, MAX_SIZE, 0.0f);
	SetSize(size);

	// �ړ����̏�����
	m_pMove->SetMoving(SPEED, MAX_SPEED, MIN_SPEED, FRICTION);

	// �e�N�X�`�����W�̐ݒ�
	SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// �v���C���[�̏I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CPlayer2D::Uninit()
{
	if (m_pMove != nullptr)
	{// �I������
		// �������̉��
		delete m_pMove;
		m_pMove = nullptr;
	}

	// �v���C���[2D�̏I��
	CObject2D::Uninit();
}

//=============================================================================
// �v���C���[�̍X�V
// Author : �������l
// �T�v : 2D�v���C���[�̍X�V���s��
//=============================================================================
void CPlayer2D::Update()
{
	// �v���C���[2D�̍X�V
	CObject2D::Update();

	// �ړ�
	D3DXVECTOR3 pos = GetPos();
	SetPosOld(pos);
	pos += Move();
	SetPos(pos);

	// �e�̔���
	Shot();
	
	for (int nCntPriority = 0; nCntPriority < CObject::MAX_LEVEL; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			CObject *pObject = CObject::MyGetObject(nCntPriority, nCntObj);

			if (pObject != nullptr)
			{
				if (pObject->GetObjType() == CObject::OBJTYPE_2DENEMY
					&& ColisonCircle2D(pObject, true))
				{// �^�C�v����v�����ꍇ
					//m_nLife = 1;
					break;
				}
			}
		}
	}
	

	// �e�N�X�`�����W�̐ݒ�
	SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
}

//=============================================================================
// �v���C���[�̕`��
// Author : �������l
// �T�v : 2D�v���C���[�̕`����s��
//=============================================================================
void CPlayer2D::Draw()
{// �v���C���[2D�̕`��
	CObject2D::Draw();
}

//=============================================================================
// �ړ�
// Author : �������l
// �T�v : �L�[���͂��s��ꂽ�ꍇ�ړ�����
//=============================================================================
D3DXVECTOR3 CPlayer2D::Move(void)
{
	// ���͏��̎擾
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	// �ړI�̈ړ������̎Z�o
	D3DXVECTOR3 moveDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (pKeyboard->GetPress(DIK_W))
	{// �����
		moveDir.y += -1.0f;
	}
	if (pKeyboard->GetPress(DIK_A))
	{// ������
		moveDir.x += -1.0f;
	}
	if (pKeyboard->GetPress(DIK_S))
	{// ������
		moveDir.y += 1.0f;
	}
	if (pKeyboard->GetPress(DIK_D))
	{// �E����
		moveDir.x += 1.0f;
	}

	// ���C�W�����l�������ړ�
	m_pMove->Moving(moveDir);

	return m_pMove->GetMove();
}

//=============================================================================
// �e�̔���
// Author : �������l
// �T�v : �L�[���͂��s��ꂽ�ꍇ�A�e�𔭎˂���
//=============================================================================
void CPlayer2D::Shot(void)
{
	// ���͏��̎擾
	CKeyboard *pKeyboard = CApplication::GetKeyboard();
	CSound *pSound = CApplication::GetSound();

	// Object2D�̃����o�ϐ��̎擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 size = GetSize();

	if (pKeyboard->GetPress(DIK_SPACE)
		&& !m_bLockShot)
	{// �e�̔���
		CBullet2D::Create(D3DXVECTOR3(pos.x, pos.y - size.y, 0.0f), rot, MAX_BULLET_SPEED);

		pSound->PlaySound(CSound::SOUND_LABEL_SE_PAUSE);

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
			// �e�̔���
			CBullet2D::Create(D3DXVECTOR3(pos.x - size.x / 2, pos.y - size.y, 0.0f), rot, MAX_BULLET_SPEED);
			pSound->PlaySound(CSound::SOUND_LABEL_SE_PAUSE);

			CBullet2D::Create(D3DXVECTOR3(pos.x + size.x / 2, pos.y - size.y, 0.0f), rot, MAX_BULLET_SPEED);
			pSound->PlaySound(CSound::SOUND_LABEL_SE_PAUSE);

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
