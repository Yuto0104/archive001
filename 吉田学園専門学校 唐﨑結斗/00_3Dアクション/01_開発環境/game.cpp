//**************************************************************************************************
//
// �Q�[����ʂ̐ݒ菈��
// Auther�F�������l
// 
//**************************************************************************************************
#include"game.h"
#include"input.h"
#include"sound.h"
#include"pause.h"
#include"fade.h"

#include"score.h"
#include"time.h"
#include"combo.h"

#include"polygon.h"
#include"camera.h"
#include"light.h"
#include"model.h"
#include"shadow.h"
#include"wall.h"
#include"billboard.h"
#include"set_file.h"
#include"meshfield.h"
#include"cylinder.h"
#include"sphere.h"
#include"skybox.h"
#include"effect.h"
#include"particle.h"
#include"player.h"
#include"line.h"
#include"set_motion.h"
#include"feed.h"
#include"stamina_gauge.h"

//*************************************************************
// �}�N����`
//*************************************************************
#define		MAX_GAME_SPEED		(5)			// �Q�[���̐i�s���x�̍ő�l

//*************************************************************
// �O���[�o���ϐ�
//*************************************************************
int g_nGameSpeed = 1;		// �Q�[���̐i�s���x

//**********************************************************************************
// �Q�[����ʂ̏���������
//**********************************************************************************
void InitGame(void)
{
	// �Q�[���̐i�s���x��������
	g_nGameSpeed = 1;

	// ���C�g����������
	InitLight();

	// �|���S������������
	InitPolygon();

	// ���b�V���t�B�[���h����������
	InitMeshField();

	// �~������������
	//InitCylinder();

	// ������������
	//InitSphere();

	// �X�J�C�{�b�N�X����������
	InitSkyBox();

	// �e����������
	InitShadow();

	// ���f������������
	InitModel();

	// �v���C���[����������
	InitPlayer();

	// �a����������
	InitFeed();

	// ���C������������
	InitLine();

	// �r���{�[�h����������
	InitBillboard();
	/*SetBillboard(D3DXVECTOR3(200.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f);*/

	// �G�t�F�N�g����������
	InitEffect();

	//// �p�[�e�B�N������������
	InitParticle();

	//SetParticle(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//	D3DXVECTOR3(400.0f, 0.0f, 400.0f),
	//	D3DXVECTOR3(0.0f, 1.0f, 0.0f),
	//	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
	//	5.0f,
	//	1.0f,
	//	-1.0f,
	//	180,
	//	5,
	//	0,
	//	5,
	//	false);

	// �Ǐ���������
	InitWall();
	/*SetWall(D3DXVECTOR3(0.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetWall(D3DXVECTOR3(200.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetWall(D3DXVECTOR3(-200.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));*/

	//SetWall(D3DXVECTOR3(0.0f, 0.0f, 200.0f), D3DXVECTOR3(0.5f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	//SetWall(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	//SetWall(D3DXVECTOR3(200.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, -0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	//SetWall(D3DXVECTOR3(-200.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	// �t�@�C���ǂݍ���
	LoodSetFile();

	// �v���C���[�̓ǂݍ���
	LoodSetMotion("motion.txt");
	
	// �X�R�A�̏���������
	InitScore();
	SetScore(0, D3DXVECTOR3(SCREEN_WIDH, 0.0f, 0.0f), D3DXVECTOR3(15.0f, 30.0f, 0.0f));

	// ���Ԃ̏���������
	InitTime();
	SetTime(90, D3DXVECTOR3(640.0f - ((10.0f * 2) * 8), 0.0f, 0.0f), D3DXVECTOR3(20.0f, 40.0f, 0.0f));

	// �R���{�̏�����
	InitCombo();

	// �X�^�~�i�Q�[�W�̏�����
	InitStaminaGauge();
	SetStaminaGauge(D3DXVECTOR3(10.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * -0.5f), D3DXVECTOR3(30.0f, 300.0f, 0.0f), 0);

	// �|�[�Y�̏���������
	InitPause();

	// �J��������������
	InitCamera(D3DXVECTOR3(0.0f, 50.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(2.2f, D3DX_PI, 0.0f));

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM001);
}

//*************************************************************************************
// �Q�[����ʂ̏I������
//*************************************************************************************
void UninitGame(void)
{
	// �J�����I������
	UninitCamera();

	// ���C�g�I������
	UninitLight();

	// �|���S���I������
	UninitPolygon();

	// ���b�V���t�B�[���h�I������
	UninitMeshField();

	// �~���I������
	//UninitCylinder();

	// ���I������
	//UninitSphere();

	// �X�J�C�{�b�N�X�I������
	UninitSkyBox();

	// ���f���I������
	UninitModel();

	// �v���C���[�I������
	UninitPlayer();

	// �a�I������
	UninitFeed();

	// ���C���I������
	UninitLine();

	// �e�I������
	UninitShadow();

	// �r���{�[�h�I������
	UninitBillboard();

	// �ǏI������
	UninitWall();

	// �G�t�F�N�g�I������
	UninitEffect();

	// �X�R�A�̏I������
	UninitScore();

	// ���Ԃ̏I������
	UninitTime();

	// �R���{�̏I������
	UninitCombo();

	// �X�^�~�i�Q�[�W�̏I������
	UninitStaminaGauge();

	// �|�[�Y�̏I������
	UninitPause();

	//�T�E���h�I������
	StopSound();
}

//**************************************************************************************
// �Q�[����ʂ̍X�V����
//**************************************************************************************
void UpdateGame(void)
{
	//// �W���C�p�b�h�̎g�p���̎擾
	//bool bUseJoyPad = GetUseJoyPad();

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_RSHIFT) == true)
	{
		g_nGameSpeed++;

		if (g_nGameSpeed > MAX_GAME_SPEED)
		{
			g_nGameSpeed = 1;
		}
	}
#endif
	//�v���C���[���̎擾
	Player *pPlayer;
	pPlayer = GetPlayer();

	// �|�[�Y���̎擾
	Pause *pPause;				// �|�[�Y���ւ̃|�C���^
	pPause = GetPause();

	// �t�F�[�h���̎擾
	FADE fade;			// �t�F�[�h���ւ̃|�C���^
	fade = GetFade();

	if (pPause->bDisp == false)
	{// �|�[�Y���ĂȂ���

		for (int nCnt = 0; nCnt < g_nGameSpeed; nCnt++)
		{
			// �J�����X�V����
			UpdateCamera();

			// ���C�g�X�V����
			UpdateLight();

			// �|���S���X�V����
			UpdatePolygon();

			// ���b�V���t�B�[���h�X�V����
			UpdateMeshField();

			// �~���X�V����
			//UpdateCylinder();
			
			// ���X�V����
			//UpdateSphere();

			// �X�J�C�{�b�N�X�X�V����
			UpdateSkyBox();

			// ���f���X�V����
			UpdateModel();

			// �v���C���[�X�V����
			UpdatePlayer();

			// �a�X�V����
			UpdateFeed();

			// ���̐ݒu
			SetControllerFeed();

			// ���C���X�V����
			UpdateLine();

			// �e�X�V����
			UpdateShadow();

			// �r���{�[�h�X�V����
			UpdateBillboard();

			// �ǍX�V����
			UpdateWall();

			// �G�t�F�N�g�X�V����
			UpdateEffect();

			// �p�[�e�B�N���X�V����
			UpdateParticle();

			// �X�R�A�̍X�V����
			UpdateScore();

			// �R���{�̍X�V����
			UpdateCombo();

			// �X�^�~�i�Q�[�W�̍X�V����
			UpdateStaminaGauge();

			// ���Ԃ̍X�V����
			UpdateTime();
		}

		if (fade == FADE_NONE)
		{// �t�F�[�h���s���ĂȂ��Ƃ�
			if (GetKeyboardTrigger(DIK_P) == true)
			{// [P]�L�[�������ꂽ
			 // �|�[�Y�̐ݒ菈��
				SetPause();

				// �T�E���h�Đ�
				PlaySound(SOUND_LABEL_SE_PAUSE);
			}
		}
	}
	else if (pPause->bDisp == true)
	{// �|�[�Y��
		// �|�[�Y�̍X�V����
		UpdatePause();
	}
}

//**************************************************************************************
//�Q�[����ʂ̕`�揈��
//**************************************************************************************
void DrawGame(void)
{
	// �J�����ݒ菈��
	SetCamera();
	
	//// �|���S���`�揈��
	//DrawPolygon();

	// ���b�V���t�B�[���h�`�揈��
	DrawMeshField();

	// �~���`�揈��
	//DrawCylinder();

	//// ���`�揈��
	//DrawSphere();

	// �X�J�C�{�b�N�X�`�揈��
	DrawSkyBox();

	// ���f���`�揈��
	DrawModel();

	// �v���C���[�`�揈��
	DrawPlayer();

	// �a�`�揈��
	DrawFeed();

	// ���C���`�揈��
	DrawLine();

	// �Ǖ`�揈��
	DrawWall();

	// �r���{�[�h�`�揈��
	DrawBillboard();

	// �e�`�揈��
	DrawShadow();

	// �G�t�F�N�g�`�揈��
	DrawEffect();

	// �X�R�A�̕`�揈��
	DrawScore();

	// ���Ԃ̕`�揈��
	DrawTime();

	// �R���{�̕`�揈��
	DrawCombo();

	// �X�^�~�i�Q�[�W�̕`�揈��
	DrawStaminaGauge();

	// �|�[�Y�̕`�揈��
	DrawPause();
}