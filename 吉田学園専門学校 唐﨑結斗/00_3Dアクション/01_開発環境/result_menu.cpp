//**************************************************************************************************
//
//�|�[�Y�w�i�̐ݒ菈��
//Auther�F�������l
//
//**************************************************************************************************
#include"main.h"
#include"result_menu.h"
#include"input.h"

//*******************************************************************************
//�O���[�o���ϐ�
//*******************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureResultMenu = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultMenu = NULL;		//���_�o�b�t�@�ւ̃|�C���^
ResultMenu g_ResultMenu;

//********************************************************************************
//�|�[�Y�w�i�̏���������
//********************************************************************************
void InitResultMenu(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�|���S���ɒ���t����e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/���U���g���j���[.png",
		&g_pTextureResultMenu);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									//���_�t�@�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultMenu,
		NULL);

	//�^�C�g�����S���̏�����
	g_ResultMenu.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���S�_
	g_ResultMenu.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���S�_����̍�
	g_ResultMenu.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����
	g_ResultMenu.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//�J���[
	g_ResultMenu.bUse = false;								//�g�p���ĂȂ�

															//���_���ւ̃|�C���^�𐶐�						
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResultMenu->Lock(0, 0, (void**)&pVtx, 0);

	//�Ίp���̒������Z�o����
	g_ResultMenu.fLength = sqrtf(((g_ResultMenu.offset.x * g_ResultMenu.offset.x) + (g_ResultMenu.offset.y * g_ResultMenu.offset.y)) / 2.0f);

	//�Ίp���̊p�x���Z�o
	g_ResultMenu.fAngele = atan2f(g_ResultMenu.offset.x, g_ResultMenu.offset.y);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_ResultMenu.pos.x + sinf(g_ResultMenu.rot.z + (D3DX_PI + g_ResultMenu.fAngele)) * g_ResultMenu.fLength;
	pVtx[0].pos.y = g_ResultMenu.pos.y + cosf(g_ResultMenu.rot.z + (D3DX_PI + g_ResultMenu.fAngele)) * g_ResultMenu.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_ResultMenu.pos.x + sinf(g_ResultMenu.rot.z + (D3DX_PI - g_ResultMenu.fAngele)) *  g_ResultMenu.fLength;
	pVtx[1].pos.y = g_ResultMenu.pos.y + cosf(g_ResultMenu.rot.z + (D3DX_PI - g_ResultMenu.fAngele)) *  g_ResultMenu.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_ResultMenu.pos.x + sinf(g_ResultMenu.rot.z - (0 + g_ResultMenu.fAngele)) * g_ResultMenu.fLength;
	pVtx[2].pos.y = g_ResultMenu.pos.y + cosf(g_ResultMenu.rot.z - (0 + g_ResultMenu.fAngele)) * g_ResultMenu.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_ResultMenu.pos.x + sinf(g_ResultMenu.rot.z - (0 - g_ResultMenu.fAngele)) *  g_ResultMenu.fLength;
	pVtx[3].pos.y = g_ResultMenu.pos.y + cosf(g_ResultMenu.rot.z - (0 - g_ResultMenu.fAngele)) *  g_ResultMenu.fLength;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_ResultMenu.col;
	pVtx[1].col = g_ResultMenu.col;
	pVtx[2].col = g_ResultMenu.col;
	pVtx[3].col = g_ResultMenu.col;

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffResultMenu->Unlock();
}

//********************************************************************************
//�|�[�Y�w�i�̏I������
//********************************************************************************
void UninitResultMenu(void)
{
	//�e�N�X�`���̔j��	  
	if (g_pTextureResultMenu != NULL)
	{
		g_pTextureResultMenu->Release();

		g_pTextureResultMenu = NULL;
	}

	//���_�o�b�t�@��j��
	if (g_pVtxBuffResultMenu != NULL)
	{
		g_pVtxBuffResultMenu->Release();

		g_pVtxBuffResultMenu = NULL;
	}
}

//********************************************************************************
//�|�[�Y�w�i�̍X�V����
//********************************************************************************
void UpdateResultMenu(void)
{

}

//********************************************************************************
//�|�[�Y�w�i�̕`�揈��
//********************************************************************************
void DrawResultMenu(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResultMenu, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ���e�X�g���g�p����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// ���e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	if (g_ResultMenu.bUse == true)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureResultMenu);

		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	// ���e�X�g�̏I��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//********************************************************************************
//�|�[�Y�w�i�̐ݒ菈��
//********************************************************************************
void SetResultMenu(void)
{
	//���_���ւ̃|�C���^�𐶐�						
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResultMenu->Lock(0, 0, (void**)&pVtx, 0);

	if (g_ResultMenu.bUse == false)
	{//�g�p����ĂȂ��ꍇ
	 //�^�C�g�����S���̐ݒ�
		g_ResultMenu.offset = D3DXVECTOR3(MAX_OFFSET_RM_X, MAX_OFFSET_RM_Y, 0.0f);			//���S�_����̍�
		g_ResultMenu.pos = D3DXVECTOR3(300.0f, 420.0f, 0.0f);								//���S�_
		g_ResultMenu.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//����
		g_ResultMenu.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);								//�J���[
		g_ResultMenu.bUse = true;															//�g�p���Ă�

																						//�Ίp���̒������Z�o����
		g_ResultMenu.fLength = sqrtf(((g_ResultMenu.offset.x * g_ResultMenu.offset.x) + (g_ResultMenu.offset.y * g_ResultMenu.offset.y)) / 2.0f);

		//�Ίp���̊p�x���Z�o
		g_ResultMenu.fAngele = atan2f(g_ResultMenu.offset.x, g_ResultMenu.offset.y);

		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_ResultMenu.pos.x + sinf(g_ResultMenu.rot.z + (D3DX_PI + g_ResultMenu.fAngele)) * g_ResultMenu.fLength;
		pVtx[0].pos.y = g_ResultMenu.pos.y + cosf(g_ResultMenu.rot.z + (D3DX_PI + g_ResultMenu.fAngele)) * g_ResultMenu.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_ResultMenu.pos.x + sinf(g_ResultMenu.rot.z + (D3DX_PI - g_ResultMenu.fAngele)) *  g_ResultMenu.fLength;
		pVtx[1].pos.y = g_ResultMenu.pos.y + cosf(g_ResultMenu.rot.z + (D3DX_PI - g_ResultMenu.fAngele)) *  g_ResultMenu.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_ResultMenu.pos.x + sinf(g_ResultMenu.rot.z - (0 + g_ResultMenu.fAngele)) * g_ResultMenu.fLength;
		pVtx[2].pos.y = g_ResultMenu.pos.y + cosf(g_ResultMenu.rot.z - (0 + g_ResultMenu.fAngele)) * g_ResultMenu.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_ResultMenu.pos.x + sinf(g_ResultMenu.rot.z - (0 - g_ResultMenu.fAngele)) *  g_ResultMenu.fLength;
		pVtx[3].pos.y = g_ResultMenu.pos.y + cosf(g_ResultMenu.rot.z - (0 - g_ResultMenu.fAngele)) *  g_ResultMenu.fLength;
		pVtx[3].pos.z = 0.0f;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_ResultMenu.col;
		pVtx[1].col = g_ResultMenu.col;
		pVtx[2].col = g_ResultMenu.col;
		pVtx[3].col = g_ResultMenu.col;

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffResultMenu->Unlock();
}