//**************************************************************************************************
//
//���U���g��ʂ̐ݒ菈��
//Auther�F�������l
//
//**************************************************************************************************
#include "main.h"

#include"result.h"
#include"input.h"
#include"sound.h"
#include"fade.h"
//#include"context.h"
#include"result bg.h"
#include"score.h"
#include"ranking.h"
#include"player.h"
#include"time.h"
#include"result_menu.h"
#include"combo.h"

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

//*******************************************************************************
//�O���[�o���ϐ�
//*******************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;		//���_�o�b�t�@�ւ̃|�C���^

//********************************************************************************
//���U���g��ʂ̏���������
//********************************************************************************
void InitResult(void)
{
	// �v���C���[���̎擾
	Player *pPlayer = GetPlayer();

	////�w�i�̏���������
	//InitContext();

	//���U���g�w�i�̏���������
	InitResultBG();
	SetResultBG();

	//�X�R�A���̎擾
	int pScore;							//�X�R�A���̃|�C���^
	pScore = GetScore();
	
	//�X�R�A�̏���������
	InitScore();

	//�X�R�A�̐ݒ菈��
	SetScore(pScore, D3DXVECTOR3(1200, 440.0f, 0.0f), D3DXVECTOR3(30.0f, 60.0f, 0.0f));

	//���Ԃ̏���������
	InitTime();

	// �R���{�̏�����
	InitCombo();
	SetCombo(pPlayer->nMaxCombo, D3DXVECTOR3((30.0f * 2) * 3.0f + 1020.0f, 330.0f, 0.0f), D3DXVECTOR3(30.0f, 60.0f, 0.0f));

	// ���U���g���j���[�̏�����
	InitResultMenu();
	SetResultMenu();

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

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM007);
}

//********************************************************************************
//���U���g��ʂ̏I������
//********************************************************************************
void UninitResult(void)
{
	//�T�E���h�I������
	StopSound();

	////�w�i�̏I������
	//UninitContext();

	//�X�R�A�̏I������
	UninitScore();

	//���Ԃ̏I������
	UninitTime();

	// �R���{�̏I������
	UninitCombo();

	//���U���g�w�i�̏I������
	UninitResultBG();

	// ���U���g���j���[�̏I������
	UninitResultMenu();

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
//���U���g��ʂ̍X�V����
//********************************************************************************
void UpdateResult(void)
{
	//// �W���C�p�b�h�̎g�p���̎擾
	//bool bUseJoyPad = GetUseJoyPad();

	////�w�i�̍X�V����
	//UpdateContext();

	//���U���g�w�i�̍X�V����
	UpdateResultBG();

	//�X�R�A�̍X�V����
	UpdateScore();

	// �R���{�̍X�V����
	UpdateCombo();

	// ���U���g���j���[�̍X�V����
	UpdateResultMenu();

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

	//�t�F�[�h���̎擾
	FADE fade;			//�t�F�[�h���ւ̃|�C���^
	fade = GetFade();

	if (fade == FADE_NONE)
	{//�t�F�[�h���s���ĂȂ��Ƃ�
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{//[Enter]�L�[�������ꂽ
			//�t�F�[�h�̐ݒ�
			SetFade(MODE_RANKING);

			//�����L���O���Z�b�g
			ResetRanking();

			//�����L���O�ݒ菈��
			SetRanking(GetScore());
		}
	}
}

//********************************************************************************
//���U���g��ʂ̕`�揈��
//********************************************************************************
void DrawResult(void)
{
	////�w�i�̕`�揈��
	//DrawContext();

	//���U���g�w�i�̕`�揈��
	DrawResultBG();

	//�X�R�A�̕`�揈��
	DrawScore();

	//���Ԃ̕`�揈��
	DrawTime();

	// �R���{�̕`�揈��
	DrawCombo();

	// ���U���g���j���[�̉揈��
	DrawResultMenu();

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