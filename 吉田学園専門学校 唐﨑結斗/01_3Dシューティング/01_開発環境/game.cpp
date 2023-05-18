//=============================================================================
//
// �Q�[���N���X(game.cpp)
// Author : �������l
// �T�v : �Q�[���N���X�̊Ǘ����s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "game.h"
#include "keyboard.h"
#include "application.h"
#include "sound.h"
#include "model_manager.h"
#include "enemy_manager.h"
#include "camera_manager.h"
#include "renderer.h"
#include "object.h"
#include "object3D.h"
#include "model3D.h"
#include "enemy3D.h"
#include "motion_char3D.h"
#include "motion_player3D.h"
#include "mesh.h"
#include "sphere.h"
#include "circle_polygon3D.h"
#include "number.h"
#include "score.h"
#include "life.h"
#include "life_manager.h"
#include "energy_gage.h"
#include "particle.h"
#include "motion_boss.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CMotionPlayer3D *CGame::m_MotionPlayer3D = nullptr;		// ���[�V�����v���C���[�C���X�^���X
CScore *CGame::m_pScore = nullptr;						// �X�R�A�C���X�^���X
CLifeManager *CGame::m_pLifeManager = nullptr;			// ���C�t�}�l�[�W���[�C���X�^���X
CEnergyGage *CGame::m_pEnergyGage = nullptr;			// �G�l���M�[�Q�[�W�}�l�[�W���[
CEnemyManager *CGame::m_pEnemyManager = nullptr;		// �G�l�~�[�}�l�[�W���[�N���X
bool CGame::m_bUsePlayer = false;						// �v���C���[���g�p���Ă��邩
bool CGame::m_bGame = false;							// �Q�[���̏�

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CGame::CGame()
{

}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CGame::Init()
{
	// �T�E���h���̎擾
	CSound *pSound = CApplication::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM001);

	// �w�i���f���̐ݒu
	CApplication::GetModelManager()->SetModelBG();

	// �J�����}�l�[�W���[�̃C���X�^���X�擾
	CCameraManager *pCameraManager = CApplication::GetCameraManager();
	CApplication::GetCameraBG()->MotionReset();
	CApplication::GetCameraBG()->SetCamera(pCameraManager->GetPosV(), pCameraManager->GetPosR(), pCameraManager->GetRot());
	CApplication::GetCameraBG()->SetNumMotion(0);

	m_pEnemyManager = CEnemyManager::Create();
	m_pEnemyManager->LoadFile("data/FILE/stage000.txt");

	/*CMotionChar3D *pMotionChar3D = CMotionChar3D::Create("data/MOTION/motion.txt");
	pMotionChar3D->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pMotionChar3D->SetObjectDrowType(CObject::DROWTYPE_BG);*/

	m_MotionPlayer3D = CMotionPlayer3D::Create();
	m_MotionPlayer3D->SetPos(D3DXVECTOR3(40.0f, 0.0f, -50.0f));
	m_MotionPlayer3D->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	m_bUsePlayer = true;

	CMesh3D *pMesh3D = CMesh3D::Create();
	pMesh3D->SetRot(D3DXVECTOR3(D3DX_PI * -0.15f, 0.0f, 0.0f));
	pMesh3D->SetSize(D3DXVECTOR3(100000.0f, 0, 100000.0f));
	pMesh3D->SetBlock(CMesh3D::DOUBLE_INT(100, 100));
	pMesh3D->SetSplitTex(true);
	pMesh3D->SetObjectDrowType(CObject::DROWTYPE_BG);
	pMesh3D->LoadTex(13);
	pMesh3D->SetScrollTex(D3DXVECTOR2(-0.08f, -0.06f), true);

	CSphere *pSphere = CSphere::Create();
	pSphere->SetRot(D3DXVECTOR3(D3DX_PI * 0.85f, 0.0f, 0.0f));
	pSphere->SetSize(D3DXVECTOR3(100.0f, 0, 100.0f));
	pSphere->SetBlock(CMesh3D::DOUBLE_INT(100, 100));
	pSphere->SetRadius(50000.0f);
	pSphere->SetSphereRange(D3DXVECTOR2(D3DX_PI * 2.0f, D3DX_PI * -0.5f));
	pSphere->SetObjectDrowType(CObject::DROWTYPE_BG);
	pSphere->SetScrollTex(D3DXVECTOR2(0.005f, 0.0f), true);
	pSphere->LoadTex(12);

	m_pScore = CScore::Create(10, false);
	m_pScore->SetScore(0);
	m_pScore->SetPos(D3DXVECTOR3(1280.0f, m_pScore->GetSize().y / 2.0f, 0.0f));

	m_pLifeManager = CLifeManager::Create();
	m_pLifeManager->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	m_pLifeManager->SetPos(D3DXVECTOR3(0.0f, m_pLifeManager->GetSize().y / 2.0f, 0.0f));

	m_pEnergyGage = CEnergyGage::Create();
	m_pEnergyGage->SetPos(D3DXVECTOR3(0.0f + m_pEnergyGage->GetSize().x / 2.0f + 20.0f, 450.0f, 0.0f));

	/*CMotionBoss *pMotionBoss = CMotionBoss::Create();
	pMotionBoss->SetPos(D3DXVECTOR3(0.0f, 0.0f, -0.0f));*/
	/*pMotionBoss->SetObjectDrowType(CObject::DROWTYPE_BG);*/

	m_bGame = true;

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CGame::Uninit()
{
	// �T�E���h���̎擾
	CSound *pSound = CApplication::GetSound();

	// �T�E���h�I��
	pSound->StopSound();

	m_pEnergyGage->Uninit();

	// �X�R�A�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V���s��
//=============================================================================
void CGame::Update()
{
	if (!m_bGame)
	{
		CApplication::SetScore(m_pScore->GetScore());
		CApplication::SetNextMode(CApplication::MODE_RESULT);
	}
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CGame::Draw()
{

}
