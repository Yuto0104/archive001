//**************************************************************************************************
//
// �t�F�[�h����
// Auther�F�������l
//
//**************************************************************************************************
#include"fade.h"
#include"main.h"

//*******************************************************************************
// �}�N����`
//*******************************************************************************
#define	MAX_COUNT_FADE		(60)

//*******************************************************************************
// �O���[�o���ϐ�
//*******************************************************************************
/*LPDIRECT3DTEXTURE9 g_pTextureFade = NULL*/;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffFade = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
FADE						g_fade;						// �t�F�[�h���
MODE						g_modeNext;					// ���̉�ʃ��[�h
D3DXCOLOR					g_colorFade;				// �|���S��(�t�F�[�h)�̐F

//********************************************************************************
// �t�F�[�h�̏���������
//********************************************************************************
void InitFade(MODE modeNext)
{
	// �f�[�^�̑��
	g_modeNext = modeNext;

	// �t�F�[�h�C���ɂ���
	g_fade = FADE_IN;

	// �|���S������(�s����)�ɂ��Ă���
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	////�|���S���ɒ���t����e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	"data/TEXTURE/FadeBlack000.png",
	//	&g_pTextureFade);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// ���_�t�@�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	// ���_���ւ̃|�C���^�𐶐�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffFade->Unlock();

	// ��ʃ��[�h�̐ݒ�
	SetMode(modeNext);
}

//********************************************************************************
// �t�F�[�h�̏I������
//********************************************************************************
void UninitFade(void)
{
	////�e�N�X�`���̔j��	  
	//if (g_pTextureFade != NULL)
	//{
	//	g_pTextureFade->Release();

	//	g_pTextureFade = NULL;
	//}

	// ���_�o�b�t�@��j��
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();

		g_pVtxBuffFade = NULL;
	}
}

//********************************************************************************
// �t�F�[�h�̍X�V����
//********************************************************************************
void UpdateFade(void)
{
	if (g_fade != FADE_NONE)
	{// �t�F�[�h���s���Ă���
		if (g_fade == FADE_IN)
		{// �t�F�[�h�C�����

			// �|���S���𓧖��ɂ��Ă���
			g_colorFade.a -= (1.0f / MAX_COUNT_FADE);

			if (g_colorFade.a <= 0.0f)
			{
				// �|���S���̐F�̐ݒ�
				g_colorFade.a = 0.0f;

				// �t�F�[�h��Ԃ̐؂�ւ�
				g_fade = FADE_NONE;
			}
		}
		else if (g_fade == FADE_OUT)
		{// �t�F�[�h�A�E�g���

			// �|���S���𓧖��ɂ��Ă���
			g_colorFade.a += (1.0f / MAX_COUNT_FADE);

			if (g_colorFade.a >= 1.0f)
			{
				// �|���S���̐F�̐ݒ�
				g_colorFade.a = 1.0f;

				// �t�F�[�h��Ԃ̐؂�ւ�
				g_fade = FADE_IN;

				// ��ʃ��[�h�̐ݒ�
				SetMode(g_modeNext);
			}
		}

		// ���_���ւ̃|�C���^�𐶐�
		VERTEX_2D *pVtx;

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = g_colorFade;
		pVtx[1].col = g_colorFade;
		pVtx[2].col = g_colorFade;
		pVtx[3].col = g_colorFade;

		// ���_�o�b�t�@���A�����b�N
		g_pVtxBuffFade->Unlock();
	}
}

//********************************************************************************
// �t�F�[�h�̕`�揈��
//********************************************************************************
void DrawFade(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//********************************************************************************
// �t�F�[�h�̐ݒ菈��
//********************************************************************************
void SetFade(MODE modeNext)
{
	// �f�[�^�̑��
	g_modeNext = modeNext;

	// �t�F�[�h�C���ɂ���
	g_fade = FADE_OUT;

	// �|���S������(����)�ɂ��Ă���
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//********************************************************************************
// �t�F�[�h�̎擾
//********************************************************************************
FADE GetFade(void)
{
	return g_fade;
}