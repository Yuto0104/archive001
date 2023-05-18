//**************************************************************************************************
//
// �^�C�g����ʂ̐ݒ菈��
// Auther�F�������l
//
//**************************************************************************************************

#include"title.h"
#include"input.h"
#include"sound.h"
#include"fade.h"
#include"titlelogo.h"
#include"press enter.h"
#include"ranking.h"

#include"camera.h"
#include"light.h"
#include"model.h"
#include"shadow.h"
#include"set_motion.h"
#include"feed.h"
#include"skybox.h"
#include"effect.h"
#include"particle.h"
#include"set_file.h"
#include"meshfield.h"
#include"line.h"
#include"combo.h"

//*******************************************************************************
// �O���[�o���ϐ�
//*******************************************************************************
int g_nCntTimeRanking;

//********************************************************************************
// �^�C�g����ʂ̏���������
//********************************************************************************
void InitTitle(void)
{
	// ���C�g����������
	InitLight();

	// ���b�V���t�B�[���h����������
	InitMeshField();

	// �X�J�C�{�b�N�X����������
	InitSkyBox();

	// �e����������
	InitShadow();

	// ���C������������
	InitLine();

	// ���f������������
	InitModel();

	// �a����������
	InitFeed();

	// �G�t�F�N�g����������
	InitEffect();

	//// �p�[�e�B�N������������
	InitParticle();

	// �t�@�C���ǂݍ���
	LoodSetFile();

	// �J��������������
	InitCamera(D3DXVECTOR3(0.0f, 100.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.65f, D3DX_PI, 0.0f));

	// ���Ԃ�������
	g_nCntTimeRanking = 0;

	// �^�C�g�����S�̏���������
	InitTitleLogo();

	// �v���X�G���^�[�̏���������
	InitPressEnter();

	// �R���{�̏�����
	InitCombo();

	// �T�E���h�Đ�
	PlaySound(SOUND_LABEL_BGM000);
}

//********************************************************************************
// �^�C�g����ʂ̏I������
//********************************************************************************
void UninitTitle(void)
{ 
	//�T�E���h�I������
	StopSound();

	// �v���X�G���^�[�̏I������
	UninitPressEnter();

	// �^�C�g�����S�̏I������
	UninitTitleLogo();

	// �J�����I������
	UninitCamera();

	// ���C�g�I������
	UninitLight();

	// ���b�V���t�B�[���h�I������
	UninitMeshField();

	// �X�J�C�{�b�N�X�I������
	UninitSkyBox();

	// ���f���I������
	UninitModel();

	// �a�I������
	UninitFeed();

	// �e�I������
	UninitShadow();

	// �G�t�F�N�g�I������
	UninitEffect();
}

//********************************************************************************
//�^�C�g����ʂ̍X�V����
//********************************************************************************
void UpdateTitle(void)
{
	// �t�F�[�h���̎擾
	FADE fade;			// �t�F�[�h���ւ̃|�C���^
	fade = GetFade();

	// ���Ԃ̉��Z
	g_nCntTimeRanking++;

	// �v���X�G���^�[�̍X�V����
	UpdatePressEnter();

	// �^�C�g�����S�̍X�V����
	UpdateTitleLogo();

	//// �w�i�̍X�V����
	//UpdateContext();

	// �^�C�g�����S�̐ݒ菈��
	SetTitleLogo();

	// �J�����X�V����
	UpdateCamera();

	// ���C�g�X�V����
	UpdateLight();

	// ���b�V���t�B�[���h�X�V����
	UpdateMeshField();

	// �X�J�C�{�b�N�X�X�V����
	UpdateSkyBox();

	// ���f���X�V����
	UpdateModel();

	// �a�X�V����
	UpdateFeed();

	// ���̐ݒu
	SetControllerFeed();

	// �e�X�V����
	UpdateShadow();

	// �G�t�F�N�g�X�V����
	UpdateEffect();

	// �p�[�e�B�N���X�V����
	UpdateParticle();

	// ��莞�ԂŃ����L���O��ʂɑJ��
	if (g_nCntTimeRanking % MAX_RANKING_TIME == 0)
	{
		if (fade == FADE_NONE)
		{// �t�F�[�h���s���ĂȂ��Ƃ�
			// �t�F�[�h�̐ݒ�
			SetFade(MODE_RANKING);

			// �����L���O���Z�b�g
			ResetRanking();
		}
	}
}

//********************************************************************************
// �^�C�g����ʂ̕`�揈��
//********************************************************************************
void DrawTitle(void)
{
	//// �w�i�̕`�揈��
	//DrawContext();

	// �^�C�g�����S�̕`�揈��
	DrawTitleLogo();

	// �v���X�G���^�[�̕`�揈��
	DrawPressEnter();

	// �J�����ݒ菈��
	SetCamera();

	// ���b�V���t�B�[���h�`�揈��
	DrawMeshField();

	// �X�J�C�{�b�N�X�`�揈��
	DrawSkyBox();

	// ���f���`�揈��
	DrawModel();

	// �a�`�揈��
	DrawFeed();

	// �e�`�揈��
	DrawShadow();

	// �G�t�F�N�g�`�揈��
	DrawEffect();
}