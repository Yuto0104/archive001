//**************************************************************************************************
//
//�����L���O�̐ݒ菈��
//Auther�F�������l
//
//**************************************************************************************************
#include"main.h"
#include"ranking.h"
#include"input.h"
#include"fade.h"
#include"score.h"
#include<stdio.h>
//#include"context.h"
#include"sound.h"
#include"ranking_logo.h"

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
LPDIRECT3DTEXTURE9 g_pTextureRank = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRankScore = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;			//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankScore = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Rank g_aRank[MAX_RANK];									//�����L���O�����N���
RankingScore g_aRankScore[MAX_RANK];					//�����L���O�X�R�A���
int g_nRankUpdate = -1;									//�X�V�����NNo.
int g_nTimerRanking;									//�����L���O��ʕ\���^�C�}�[
int g_nScoreState;										//�����L���O�X�R�A�̏��
int g_nCountState;										//�����L���O�X�R�A�̏�ԃJ�E���^�[

//********************************************************************************
//�����L���O�̏���������
//********************************************************************************
void InitRanking(void)
{
	//�ϐ��錾
	int nCountRank;
	int nCountDigits;
	int aPosTexU[MAX_RANK][MAX_RANK_DIGITS];

	//���l�̕����Ɗi�[
	for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
	{
		aPosTexU[nCountRank][0] = g_aRankScore[nCountRank].nScore % 100000000 / 10000000;
		aPosTexU[nCountRank][1] = g_aRankScore[nCountRank].nScore % 10000000 / 1000000;
		aPosTexU[nCountRank][2] = g_aRankScore[nCountRank].nScore % 1000000 / 100000;
		aPosTexU[nCountRank][3] = g_aRankScore[nCountRank].nScore % 100000 / 10000;
		aPosTexU[nCountRank][4] = g_aRankScore[nCountRank].nScore % 10000 / 1000;
		aPosTexU[nCountRank][5] = g_aRankScore[nCountRank].nScore % 1000 / 100;
		aPosTexU[nCountRank][6] = g_aRankScore[nCountRank].nScore % 100 / 10;
		aPosTexU[nCountRank][7] = g_aRankScore[nCountRank].nScore % 10 / 1;
	}

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM005);

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

	//�����L���O���S�̏���������
	InitRankingLogo();

	//�����L���O���S�̐ݒ菈��
	SetRankingLogo();

	//�O���[�o���ϐ��̏�����
	g_nTimerRanking = MAX_TIME;
	g_nScoreState = 0;
	g_nCountState = 0;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�|���S���ɒ���t����e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ranking_rank.png",
		&g_pTextureRank);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,												//���_�t�@�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);

	//�^�C�g�����S���̏�����
	for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
	{
		g_aRank[nCountRank].offset = D3DXVECTOR3(MAX_OFFSET_RANK_X, MAX_OFFSET_RANK_Y, 0.0f);											//���S�_����̍�
		g_aRank[nCountRank].pos = D3DXVECTOR3(POS_RANK_X, POS_RANK_Y + ((g_aRank[nCountRank].offset.y  * 1.7f) * nCountRank), 0.0f);	//���S�_
		g_aRank[nCountRank].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);																		//����	 
		g_aRank[nCountRank].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);																	//�J���[
	}

	//���_���ւ̃|�C���^�𐶐�						
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	//�^�C�g�����S���̏�����
	for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
	{
		//�Ίp���̒������Z�o����
		g_aRank[nCountRank].fLength = sqrtf(((g_aRank[nCountRank].offset.x * g_aRank[nCountRank].offset.x) + (g_aRank[nCountRank].offset.y * g_aRank[nCountRank].offset.y)) / 2.0f);

		//�Ίp���̊p�x���Z�o
		g_aRank[nCountRank].fAngele = atan2f(g_aRank[nCountRank].offset.x, g_aRank[nCountRank].offset.y);

		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_aRank[nCountRank].pos.x + sinf(g_aRank[nCountRank].rot.z + (D3DX_PI + g_aRank[nCountRank].fAngele)) * g_aRank[nCountRank].fLength;
		pVtx[0].pos.y = g_aRank[nCountRank].pos.y + cosf(g_aRank[nCountRank].rot.z + (D3DX_PI + g_aRank[nCountRank].fAngele)) * g_aRank[nCountRank].fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_aRank[nCountRank].pos.x + sinf(g_aRank[nCountRank].rot.z + (D3DX_PI - g_aRank[nCountRank].fAngele)) *  g_aRank[nCountRank].fLength;
		pVtx[1].pos.y = g_aRank[nCountRank].pos.y + cosf(g_aRank[nCountRank].rot.z + (D3DX_PI - g_aRank[nCountRank].fAngele)) *  g_aRank[nCountRank].fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_aRank[nCountRank].pos.x + sinf(g_aRank[nCountRank].rot.z - (0 + g_aRank[nCountRank].fAngele)) * g_aRank[nCountRank].fLength;
		pVtx[2].pos.y = g_aRank[nCountRank].pos.y + cosf(g_aRank[nCountRank].rot.z - (0 + g_aRank[nCountRank].fAngele)) * g_aRank[nCountRank].fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_aRank[nCountRank].pos.x + sinf(g_aRank[nCountRank].rot.z - (0 - g_aRank[nCountRank].fAngele)) *  g_aRank[nCountRank].fLength;
		pVtx[3].pos.y = g_aRank[nCountRank].pos.y + cosf(g_aRank[nCountRank].rot.z - (0 - g_aRank[nCountRank].fAngele)) *  g_aRank[nCountRank].fLength;
		pVtx[3].pos.z = 0.0f;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_aRank[nCountRank].col;
		pVtx[1].col = g_aRank[nCountRank].col;
		pVtx[2].col = g_aRank[nCountRank].col;
		pVtx[3].col = g_aRank[nCountRank].col;

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + (nCountRank * 0.2f));
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + (nCountRank * 0.2f));
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.2f + (nCountRank * 0.2f));
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.2f + (nCountRank * 0.2f));

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRank->Unlock();

	//�|���S���ɒ���t����e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureRankScore);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK * MAX_RANK_DIGITS,			//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,																		//���_�t�@�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankScore,
		NULL);

	//���l�̏�����
	for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
	{
		g_aRankScore[nCountRank].offset = D3DXVECTOR3(MAX_OFFSET_RANKING_SCORE_X, MAX_OFFSET_RANKING_SCORE_Y, 0.0f);			//���S�_����̍�
		g_aRankScore[nCountRank].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);															//����
		g_aRankScore[nCountRank].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);														//�J���[
		g_aRankScore[nCountRank].nScore = 0;																					//�X�R�A�̒l
	}
	
	//�X�R�A�̈ʒu�̏�����
	for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
	{
		for (nCountDigits = 0; nCountDigits < MAX_RANK_DIGITS; nCountDigits++)
		{
			g_aRankScore[nCountRank].pos[nCountDigits] = D3DXVECTOR3(POS_RANKING_SCORE_X - (g_aRankScore[nCountRank].offset.x * 2 * nCountDigits), g_aRank[nCountRank].pos.y, 0.0f);
		}
	}

	//���_���ւ̃|�C���^�𐶐�
	VERTEX_2D *pVtx0;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx0, 0);

	for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
	{
		//�Ίp���̒������Z�o����
		g_aRankScore[nCountRank].fLength = sqrtf(((g_aRankScore[nCountRank].offset.x * g_aRankScore[nCountRank].offset.x) + (g_aRankScore[nCountRank].offset.y * g_aRankScore[nCountRank].offset.y)) / 2.0f);

		//�Ίp���̊p�x���Z�o
		g_aRankScore[nCountRank].fAngele = atan2f(g_aRankScore[nCountRank].offset.x, g_aRankScore[nCountRank].offset.y);

		for (nCountDigits = 0; nCountDigits < MAX_RANK_DIGITS; nCountDigits++)
		{
			//���_���W�̐ݒ�
			pVtx0[0].pos.x = g_aRankScore[nCountRank].pos[nCountDigits].x + sinf(g_aRankScore[nCountRank].rot.z + (D3DX_PI + g_aRankScore[nCountRank].fAngele)) * g_aRankScore[nCountRank].fLength;
			pVtx0[0].pos.y = g_aRankScore[nCountRank].pos[nCountDigits].y + cosf(g_aRankScore[nCountRank].rot.z + (D3DX_PI + g_aRankScore[nCountRank].fAngele)) * g_aRankScore[nCountRank].fLength;
			pVtx0[0].pos.z = 0.0f;

			pVtx0[1].pos.x = g_aRankScore[nCountRank].pos[nCountDigits].x + sinf(g_aRankScore[nCountRank].rot.z + (D3DX_PI - g_aRankScore[nCountRank].fAngele)) *  g_aRankScore[nCountRank].fLength;
			pVtx0[1].pos.y = g_aRankScore[nCountRank].pos[nCountDigits].y + cosf(g_aRankScore[nCountRank].rot.z + (D3DX_PI - g_aRankScore[nCountRank].fAngele)) *  g_aRankScore[nCountRank].fLength;
			pVtx0[1].pos.z = 0.0f;

			pVtx0[2].pos.x = g_aRankScore[nCountRank].pos[nCountDigits].x + sinf(g_aRankScore[nCountRank].rot.z - (0 + g_aRankScore[nCountRank].fAngele)) * g_aRankScore[nCountRank].fLength;
			pVtx0[2].pos.y = g_aRankScore[nCountRank].pos[nCountDigits].y + cosf(g_aRankScore[nCountRank].rot.z - (0 + g_aRankScore[nCountRank].fAngele)) * g_aRankScore[nCountRank].fLength;
			pVtx0[2].pos.z = 0.0f;

			pVtx0[3].pos.x = g_aRankScore[nCountRank].pos[nCountDigits].x + sinf(g_aRankScore[nCountRank].rot.z - (0 - g_aRankScore[nCountRank].fAngele)) *  g_aRankScore[nCountRank].fLength;
			pVtx0[3].pos.y = g_aRankScore[nCountRank].pos[nCountDigits].y + cosf(g_aRankScore[nCountRank].rot.z - (0 - g_aRankScore[nCountRank].fAngele)) *  g_aRankScore[nCountRank].fLength;
			pVtx0[3].pos.z = 0.0f;

			//rhw�̐ݒ�
			pVtx0[0].rhw = 1.0f;
			pVtx0[1].rhw = 1.0f;
			pVtx0[2].rhw = 1.0f;
			pVtx0[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�
			pVtx0[0].col = g_aRankScore[nCountRank].col;
			pVtx0[1].col = g_aRankScore[nCountRank].col;
			pVtx0[2].col = g_aRankScore[nCountRank].col;
			pVtx0[3].col = g_aRankScore[nCountRank].col;

			//�e�N�X�`�����W
			pVtx0[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCountRank][(MAX_RANK_DIGITS - 1) - nCountDigits] * 0.1f), 0.0f);
			pVtx0[1].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCountRank][(MAX_RANK_DIGITS - 1) - nCountDigits] * 0.1f), 0.0f);
			pVtx0[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCountRank][(MAX_RANK_DIGITS - 1) - nCountDigits] * 0.1f), 1.0f);
			pVtx0[3].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCountRank][(MAX_RANK_DIGITS - 1) - nCountDigits] * 0.1f), 1.0f);

			pVtx0 += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRankScore->Unlock();
}

//********************************************************************************
//�����L���O�̏I������
//********************************************************************************
void UninitRanking(void)
{
	//���l�̏�����
	g_nRankUpdate = -1;

	//�T�E���h�I������
	StopSound();

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

	//�����L���O���S�̏I������
	UninitRankingLogo();

	//�e�N�X�`���̔j��	  
	if (g_pTextureRank != NULL)
	{
		g_pTextureRank->Release();

		g_pTextureRank = NULL;
	}
	if (g_pTextureRankScore != NULL)
	{
		g_pTextureRankScore->Release();

		g_pTextureRankScore = NULL;
	}

	//���_�o�b�t�@��j��
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();

		g_pVtxBuffRank = NULL;
	}
	if (g_pVtxBuffRankScore != NULL)
	{
		g_pVtxBuffRankScore->Release();

		g_pVtxBuffRankScore = NULL;
	}
}

//********************************************************************************
//�����L���O�̍X�V����
//********************************************************************************
void UpdateRanking(void)
{
	//// �W���C�p�b�h�̎g�p���̎擾
	//bool bUseJoyPad = GetUseJoyPad();

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

	//�����L���O���S�̍X�V����
	UpdateRankingLogo();

	//�ϐ��錾
	int nCountDigits;

	//�t�F�[�h���̎擾
	FADE fade;			//�t�F�[�h���ւ̃|�C���^
	fade = GetFade();

	//���_���ւ̃|�C���^�𐶐�
	VERTEX_2D *pVtx0;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx0, 0);

	if (g_nRankUpdate != -1)
	{//�X�R�A���X�V���ꂽ
		//�J���[�̍X�V
		g_aRankScore[g_nRankUpdate].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		g_nCountState++;

		if (g_nCountState % 3 == 0)
		{
			g_nScoreState ^= 1;

			g_aRankScore[g_nRankUpdate].col.a = (1.0f * g_nScoreState);
		}

		//���_�����X�V
		pVtx0 += MAX_RANK_DIGITS * g_nRankUpdate * 4;

		for (nCountDigits = 0; nCountDigits < MAX_RANK_DIGITS; nCountDigits++)
		{
			//���_�J���[�̐ݒ�
			pVtx0[0].col = g_aRankScore[g_nRankUpdate].col;
			pVtx0[1].col = g_aRankScore[g_nRankUpdate].col;
			pVtx0[2].col = g_aRankScore[g_nRankUpdate].col;
			pVtx0[3].col = g_aRankScore[g_nRankUpdate].col;

			pVtx0 += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
		}
	}

	//���Ԃ̍X�V
	g_nTimerRanking--;

	if (g_nTimerRanking <= 0 || GetKeyboardTrigger(DIK_RETURN) == true)
	{//��莞�Ԍo�߁A����Enter�L�[�������ꂽ
		if (fade == FADE_NONE)
		{//�t�F�[�h���s���ĂȂ��Ƃ�
		 //�t�F�[�h�̐ݒ�
			SetFade(MODE_TITLE);
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRankScore->Unlock();
}

//********************************************************************************
//�����L���O�̕`�揈��
//********************************************************************************
void DrawRanking(void)
{
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

	//�����L���O���S�̕`�揈��
	DrawRankingLogo();

	//�ϐ��錾
	int nCountRank;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRank);

		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCountRank * 4,
			2);
	}

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCountRank = 0; nCountRank < MAX_RANK * MAX_RANK_DIGITS; nCountRank++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRankScore);

		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCountRank * 4,
			2);
	}
}

//********************************************************************************
//�����L���O�̃��Z�b�g����
//********************************************************************************
void ResetRanking(void)
{
	//�ϐ��錾
	int nCountRank;
	FILE * pFile;

#ifdef	NDEBUG
	char aFile[128] = FILE_RANKING_DATA;
	strcat(aFile, FILE_RANKING_NAME001);

	//�t�@�C�����J��
	pFile = fopen(aFile, "rb");

	//���������^�̏ꍇ���s
	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
		{
			fread(&g_aRankScore[nCountRank].nScore, sizeof(int), 1, pFile);
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("\n * * * �t�@�C�����J���܂���ł��� * * * \n");
	}
#endif
#ifdef _DEBUG
	char aFile[128] = FILE_RANKING_DATA;
	strcat(aFile, FILE_RANKING_NAME000);

	//�t�@�C�����J��
	pFile = fopen(aFile, "r");

	//���������^�̏ꍇ
	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
		{
			//�f�[�^�̓ǂݍ���
			fscanf(pFile, "%d", &g_aRankScore[nCountRank].nScore);
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ��ꍇ
		printf("\n * * * �t�@�C�����J���܂��� * * * \n");
	}
#endif
}

//********************************************************************************
//�����L���O�̐ݒ菈��
//********************************************************************************
void SetRanking(int nScore)
{
	//�ϐ��錾
	int nCountRank;
	int nCountRank1;
	int nReplacementScore;
	int nCntReplacement;
	FILE * pFile;

	if (g_aRankScore[MAX_RANK - 1].nScore < nScore)
	{//�X�R�A���X�V���ꂽ
		g_aRankScore[MAX_RANK - 1].nScore = nScore;
		g_nRankUpdate++;

		for (nCountRank = 0; nCountRank < MAX_RANK - 1; nCountRank++)
		{
			//��������񐔂��J�E���g���鐔�l�����Z�b�g
			nCntReplacement = nCountRank;

			for (nCountRank1 = nCountRank + 1; nCountRank1 < MAX_RANK; nCountRank1++)
			{
				//���������^�̏ꍇ���s
				if (g_aRankScore[nCntReplacement].nScore < g_aRankScore[nCountRank1].nScore)
				{
					//��������񐔂��J�E���g
					nCntReplacement = nCountRank1;

					g_nRankUpdate++;
				}
			}

			//���l�̓���ւ�
			nReplacementScore = g_aRankScore[nCntReplacement].nScore;
			g_aRankScore[nCntReplacement].nScore = g_aRankScore[nCountRank].nScore;
			g_aRankScore[nCountRank].nScore = nReplacementScore;
		}

		g_nRankUpdate = ((MAX_RANK - 1) - g_nRankUpdate);
	}

#ifdef	NDEBUG
	char aFile[128] = FILE_RANKING_DATA;
	strcat(aFile, FILE_RANKING_NAME001);

	//�t�@�C�����J��
	pFile = fopen(aFile, "wb");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
		{
			fwrite(&g_aRankScore[nCountRank].nScore, sizeof(int), 1, pFile);
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("\n * * * �t�@�C�����J���܂���ł��� * * * \n");
	}
#endif
#ifdef _DEBUG
	char aFile[128] = FILE_RANKING_DATA;
	strcat(aFile, FILE_RANKING_NAME000);
	//�t�@�C�����J��
	pFile = fopen(aFile, "w");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
		{
			//�f�[�^�̓ǂݍ���
			fprintf(pFile, "%d\n", g_aRankScore[nCountRank].nScore);
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ��ꍇ
		printf("\n * * * �t�@�C�����J���܂��� * * * \n");
	}
#endif
}