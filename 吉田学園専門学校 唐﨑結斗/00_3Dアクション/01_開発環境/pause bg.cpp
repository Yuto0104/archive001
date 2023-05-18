//**************************************************************************************************
//
// �|�[�Y�w�i�̐ݒ菈��
// Auther�F�������l
//
//**************************************************************************************************
#include"main.h"
#include"pause bg.h"
#include"input.h"

//*******************************************************************************
// �O���[�o���ϐ�
//*******************************************************************************
LPDIRECT3DTEXTURE9			g_pTexturePauseBG = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffPauseBG = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
PauseBG						g_PauseBG;

//********************************************************************************
// �|�[�Y�w�i�̏���������
//********************************************************************************
void InitPauseBG(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �|���S���ɒ���t����e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/pause100.png",
		&g_pTexturePauseBG);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,								   
		FVF_VERTEX_2D,									// ���_�t�@�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseBG,
		NULL);

	// �^�C�g�����S���̏�����
	g_PauseBG.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���S�_
	g_PauseBG.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���S�_����̍�
	g_PauseBG.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����
	g_PauseBG.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �J���[
	g_PauseBG.bUse = false;									// �g�p���ĂȂ�
														
	// ���_���ւ̃|�C���^�𐶐�						
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseBG->Lock(0, 0, (void**)&pVtx, 0);

	// �Ίp���̒������Z�o����
	g_PauseBG.fLength = sqrtf(((g_PauseBG.offset.x * g_PauseBG.offset.x) + (g_PauseBG.offset.y * g_PauseBG.offset.y)) / 2.0f);

	// �Ίp���̊p�x���Z�o
	g_PauseBG.fAngele = atan2f(g_PauseBG.offset.x, g_PauseBG.offset.y);

	// ���_���W�̐ݒ�
	pVtx[0].pos.x = g_PauseBG.pos.x + sinf(g_PauseBG.rot.z + (D3DX_PI + g_PauseBG.fAngele)) * g_PauseBG.fLength;
	pVtx[0].pos.y = g_PauseBG.pos.y + cosf(g_PauseBG.rot.z + (D3DX_PI + g_PauseBG.fAngele)) * g_PauseBG.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_PauseBG.pos.x + sinf(g_PauseBG.rot.z + (D3DX_PI - g_PauseBG.fAngele)) *  g_PauseBG.fLength;
	pVtx[1].pos.y = g_PauseBG.pos.y + cosf(g_PauseBG.rot.z + (D3DX_PI - g_PauseBG.fAngele)) *  g_PauseBG.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_PauseBG.pos.x + sinf(g_PauseBG.rot.z - (0 + g_PauseBG.fAngele)) * g_PauseBG.fLength;
	pVtx[2].pos.y = g_PauseBG.pos.y + cosf(g_PauseBG.rot.z - (0 + g_PauseBG.fAngele)) * g_PauseBG.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_PauseBG.pos.x + sinf(g_PauseBG.rot.z - (0 - g_PauseBG.fAngele)) *  g_PauseBG.fLength;
	pVtx[3].pos.y = g_PauseBG.pos.y + cosf(g_PauseBG.rot.z - (0 - g_PauseBG.fAngele)) *  g_PauseBG.fLength;
	pVtx[3].pos.z = 0.0f;

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = g_PauseBG.col;
	pVtx[1].col = g_PauseBG.col;
	pVtx[2].col = g_PauseBG.col;
	pVtx[3].col = g_PauseBG.col;

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffPauseBG->Unlock();
}

//********************************************************************************
// �|�[�Y�w�i�̏I������
//********************************************************************************
void UninitPauseBG(void)
{
	// �e�N�X�`���̔j��	  
	if (g_pTexturePauseBG != NULL)
	{
		g_pTexturePauseBG->Release();

		g_pTexturePauseBG = NULL;
	}

	// ���_�o�b�t�@��j��
	if (g_pVtxBuffPauseBG != NULL)
	{
		g_pVtxBuffPauseBG->Release();

		g_pVtxBuffPauseBG = NULL;
	}
}

//********************************************************************************
// �|�[�Y�w�i�̍X�V����
//********************************************************************************
void UpdatePauseBG(void)
{

}

//********************************************************************************
// �|�[�Y�w�i�̕`�揈��
//********************************************************************************
void DrawPauseBG(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseBG, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_PauseBG.bUse == true)
	{// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePauseBG);

		// �|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//********************************************************************************
// �|�[�Y�w�i�̐ݒ菈��
//********************************************************************************
void SetPauseBG(void)
{
	// ���_���ւ̃|�C���^�𐶐�						
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseBG->Lock(0, 0, (void**)&pVtx, 0);

	if (g_PauseBG.bUse == false)
	{// �g�p����ĂȂ��ꍇ
		// �^�C�g�����S���̐ݒ�
		g_PauseBG.offset = D3DXVECTOR3(MAX_OFFSET_PBG_X, MAX_OFFSET_PBG_Y, 0.0f);		// ���S�_����̍�
		g_PauseBG.pos = D3DXVECTOR3(SCREEN_WIDH / 2, SCREEN_HEIGHT / 2, 0.0f);			// ���S�_
		g_PauseBG.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									// ����
		g_PauseBG.col = D3DXCOLOR(0.5f, 0.5f, 1.0f, 0.5f);								// �J���[
		g_PauseBG.bUse = true;															// �g�p���Ă�

		// �Ίp���̒������Z�o����
		g_PauseBG.fLength = sqrtf(((g_PauseBG.offset.x * g_PauseBG.offset.x) + (g_PauseBG.offset.y * g_PauseBG.offset.y)) / 2.0f);

		// �Ίp���̊p�x���Z�o
		g_PauseBG.fAngele = atan2f(g_PauseBG.offset.x, g_PauseBG.offset.y);

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = g_PauseBG.pos.x + sinf(g_PauseBG.rot.z + (D3DX_PI + g_PauseBG.fAngele)) * g_PauseBG.fLength;
		pVtx[0].pos.y = g_PauseBG.pos.y + cosf(g_PauseBG.rot.z + (D3DX_PI + g_PauseBG.fAngele)) * g_PauseBG.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_PauseBG.pos.x + sinf(g_PauseBG.rot.z + (D3DX_PI - g_PauseBG.fAngele)) *  g_PauseBG.fLength;
		pVtx[1].pos.y = g_PauseBG.pos.y + cosf(g_PauseBG.rot.z + (D3DX_PI - g_PauseBG.fAngele)) *  g_PauseBG.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_PauseBG.pos.x + sinf(g_PauseBG.rot.z - (0 + g_PauseBG.fAngele)) * g_PauseBG.fLength;
		pVtx[2].pos.y = g_PauseBG.pos.y + cosf(g_PauseBG.rot.z - (0 + g_PauseBG.fAngele)) * g_PauseBG.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_PauseBG.pos.x + sinf(g_PauseBG.rot.z - (0 - g_PauseBG.fAngele)) *  g_PauseBG.fLength;
		pVtx[3].pos.y = g_PauseBG.pos.y + cosf(g_PauseBG.rot.z - (0 - g_PauseBG.fAngele)) *  g_PauseBG.fLength;
		pVtx[3].pos.z = 0.0f;

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = g_PauseBG.col;
		pVtx[1].col = g_PauseBG.col;
		pVtx[2].col = g_PauseBG.col;
		pVtx[3].col = g_PauseBG.col;

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffPauseBG->Unlock();
}