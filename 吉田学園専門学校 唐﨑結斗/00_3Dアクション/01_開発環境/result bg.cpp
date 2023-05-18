//**************************************************************************************************
//
//�|�[�Y�w�i�̐ݒ菈��
//Auther�F�������l
//
//**************************************************************************************************
#include"main.h"
#include"result bg.h"
#include"input.h"

//*******************************************************************************
//�O���[�o���ϐ�
//*******************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureResultBG = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultBG = NULL;		//���_�o�b�t�@�ւ̃|�C���^
ResultBG g_ResultBG;

//********************************************************************************
//�|�[�Y�w�i�̏���������
//********************************************************************************
void InitResultBG(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�|���S���ɒ���t����e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RESULT.png",
		&g_pTextureResultBG);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									//���_�t�@�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultBG,
		NULL);

	//�^�C�g�����S���̏�����
	g_ResultBG.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���S�_
	g_ResultBG.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���S�_����̍�
	g_ResultBG.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����
	g_ResultBG.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//�J���[
	g_ResultBG.bUse = false;								//�g�p���ĂȂ�

	//���_���ւ̃|�C���^�𐶐�						
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResultBG->Lock(0, 0, (void**)&pVtx, 0);

	//�Ίp���̒������Z�o����
	g_ResultBG.fLength = sqrtf(((g_ResultBG.offset.x * g_ResultBG.offset.x) + (g_ResultBG.offset.y * g_ResultBG.offset.y)) / 2.0f);

	//�Ίp���̊p�x���Z�o
	g_ResultBG.fAngele = atan2f(g_ResultBG.offset.x, g_ResultBG.offset.y);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_ResultBG.pos.x + sinf(g_ResultBG.rot.z + (D3DX_PI + g_ResultBG.fAngele)) * g_ResultBG.fLength;
	pVtx[0].pos.y = g_ResultBG.pos.y + cosf(g_ResultBG.rot.z + (D3DX_PI + g_ResultBG.fAngele)) * g_ResultBG.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_ResultBG.pos.x + sinf(g_ResultBG.rot.z + (D3DX_PI - g_ResultBG.fAngele)) *  g_ResultBG.fLength;
	pVtx[1].pos.y = g_ResultBG.pos.y + cosf(g_ResultBG.rot.z + (D3DX_PI - g_ResultBG.fAngele)) *  g_ResultBG.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_ResultBG.pos.x + sinf(g_ResultBG.rot.z - (0 + g_ResultBG.fAngele)) * g_ResultBG.fLength;
	pVtx[2].pos.y = g_ResultBG.pos.y + cosf(g_ResultBG.rot.z - (0 + g_ResultBG.fAngele)) * g_ResultBG.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_ResultBG.pos.x + sinf(g_ResultBG.rot.z - (0 - g_ResultBG.fAngele)) *  g_ResultBG.fLength;
	pVtx[3].pos.y = g_ResultBG.pos.y + cosf(g_ResultBG.rot.z - (0 - g_ResultBG.fAngele)) *  g_ResultBG.fLength;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_ResultBG.col;
	pVtx[1].col = g_ResultBG.col;
	pVtx[2].col = g_ResultBG.col;
	pVtx[3].col = g_ResultBG.col;

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffResultBG->Unlock();
}

//********************************************************************************
//�|�[�Y�w�i�̏I������
//********************************************************************************
void UninitResultBG(void)
{
	//�e�N�X�`���̔j��	  
	if (g_pTextureResultBG != NULL)
	{
		g_pTextureResultBG->Release();

		g_pTextureResultBG = NULL;
	}

	//���_�o�b�t�@��j��
	if (g_pVtxBuffResultBG != NULL)
	{
		g_pVtxBuffResultBG->Release();

		g_pVtxBuffResultBG = NULL;
	}
}

//********************************************************************************
//�|�[�Y�w�i�̍X�V����
//********************************************************************************
void UpdateResultBG(void)
{

}

//********************************************************************************
//�|�[�Y�w�i�̕`�揈��
//********************************************************************************
void DrawResultBG(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResultBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ���e�X�g���g�p����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// ���e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	if (g_ResultBG.bUse == true)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureResultBG);

		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	// ���e�X�g�̏I��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//********************************************************************************
//�|�[�Y�w�i�̐ݒ菈��
//********************************************************************************
void SetResultBG(void)
{
	//���_���ւ̃|�C���^�𐶐�						
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResultBG->Lock(0, 0, (void**)&pVtx, 0);

	if (g_ResultBG.bUse == false)
	{//�g�p����ĂȂ��ꍇ
	 //�^�C�g�����S���̐ݒ�
		g_ResultBG.offset = D3DXVECTOR3(MAX_OFFSET_RBG_X, MAX_OFFSET_RBG_Y, 0.0f);		//���S�_����̍�
		g_ResultBG.pos = D3DXVECTOR3(SCREEN_WIDH / 2, 120.0f, 0.0f);					//���S�_
		g_ResultBG.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//����
		g_ResultBG.col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);								//�J���[
		g_ResultBG.bUse = true;															//�g�p���Ă�

		//�Ίp���̒������Z�o����
		g_ResultBG.fLength = sqrtf(((g_ResultBG.offset.x * g_ResultBG.offset.x) + (g_ResultBG.offset.y * g_ResultBG.offset.y)) / 2.0f);

		//�Ίp���̊p�x���Z�o
		g_ResultBG.fAngele = atan2f(g_ResultBG.offset.x, g_ResultBG.offset.y);

		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_ResultBG.pos.x + sinf(g_ResultBG.rot.z + (D3DX_PI + g_ResultBG.fAngele)) * g_ResultBG.fLength;
		pVtx[0].pos.y = g_ResultBG.pos.y + cosf(g_ResultBG.rot.z + (D3DX_PI + g_ResultBG.fAngele)) * g_ResultBG.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_ResultBG.pos.x + sinf(g_ResultBG.rot.z + (D3DX_PI - g_ResultBG.fAngele)) *  g_ResultBG.fLength;
		pVtx[1].pos.y = g_ResultBG.pos.y + cosf(g_ResultBG.rot.z + (D3DX_PI - g_ResultBG.fAngele)) *  g_ResultBG.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_ResultBG.pos.x + sinf(g_ResultBG.rot.z - (0 + g_ResultBG.fAngele)) * g_ResultBG.fLength;
		pVtx[2].pos.y = g_ResultBG.pos.y + cosf(g_ResultBG.rot.z - (0 + g_ResultBG.fAngele)) * g_ResultBG.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_ResultBG.pos.x + sinf(g_ResultBG.rot.z - (0 - g_ResultBG.fAngele)) *  g_ResultBG.fLength;
		pVtx[3].pos.y = g_ResultBG.pos.y + cosf(g_ResultBG.rot.z - (0 - g_ResultBG.fAngele)) *  g_ResultBG.fLength;
		pVtx[3].pos.z = 0.0f;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_ResultBG.col;
		pVtx[1].col = g_ResultBG.col;
		pVtx[2].col = g_ResultBG.col;
		pVtx[3].col = g_ResultBG.col;

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffResultBG->Unlock();
}