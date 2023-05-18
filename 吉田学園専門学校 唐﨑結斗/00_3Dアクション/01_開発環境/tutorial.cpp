//**************************************************************************************************
//
// �`���[�g���A������
// Auther�F�������l
//
//**************************************************************************************************
#include"tutorial.h"
#include"main.h"
#include"press enter.h"
#include"sound.h"
#include"input.h"
#include"calculation.h"

//*******************************************************************************
// �}�N����`
//*******************************************************************************
#define		MAX_ANIMPATTEN_TUTORIAL			(2)		// �A�j���[�V�����p�^�[���̍ő�l 

//*******************************************************************************
// �O���[�o���ϐ�
//*******************************************************************************
static LPDIRECT3DTEXTURE9			g_pTextureTutorial = NULL;			// �e�N�X�`���ւ̃|�C���^
static LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffTutorial = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
static float						g_nMaxAnimU;						// �e�N�X�`����X���̍ő�l 

//********************************************************************************
// �`���[�g���A���̏���������
//********************************************************************************
void InitTutorial(void)
{
	// �O���[�o���ϐ��̐ݒ�
	g_nMaxAnimU = 1.0f / MAX_ANIMPATTEN_TUTORIAL;

	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �|���S���ɒ���t����e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/�`���[�g���A�����.png",
		&g_pTextureTutorial);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// ���_�t�@�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	// ���_���ւ̃|�C���^�𐶐�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W
	SetVtxTexture(pVtx, 1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffTutorial->Unlock();

	// �v���X�G���^�[�̏���������
	InitPressEnter();

	// �v���X�G���^�[�̐ݒ菈��
	SetPressEnter(D3DXVECTOR3(1180.0f, 700.0f, 0.0f), D3DXVECTOR3(MAX_OFFSET_PE_X / 2, MAX_OFFSET_PE_Y / 2, 0.0f));

	//�T�E���h�Đ�
	PlaySound(SOUND_LABEL_BGM004);
}

//********************************************************************************
// �`���[�g���A���̏I������
//********************************************************************************
void UninitTutorial(void)
{
	//�T�E���h�I������
	StopSound();

	// �v���X�G���^�[�̏I������
	UninitPressEnter();

	// �e�N�X�`���̔j��	  
	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();

		g_pTextureTutorial = NULL;
	}

	// ���_�o�b�t�@��j��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();

		g_pVtxBuffTutorial = NULL;
	}
}

//********************************************************************************
// �`���[�g���A���̍X�V����
//********************************************************************************
void UpdateTutorial(void)
{
	// �ϐ��錾
	int nPage = 0;

	//// �W���C�p�b�h�̎g�p���̎擾
	//bool bUseJoyPad = GetUseJoyPad();

	//if (bUseJoyPad == true)
	//{// �g�p����Ă�ꍇ
	//	nPage = 1;
	//}

	// ���_���ւ̃|�C���^�𐶐�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	// �v���X�G���^�[�̍X�V����
	UpdatePressEnter();

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffTutorial->Unlock();
}

//********************************************************************************
// �`���[�g���A���̕`�揈��
//********************************************************************************
void DrawTutorial(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTutorial);

	// �|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// �v���X�G���^�[�̕`�揈��
	DrawPressEnter();
}