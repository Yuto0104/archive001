//**************************************************************************************************
//
//�R���e�B�j���[�̐ݒ菈��
//Auther�F�������l
//
//**************************************************************************************************
#include"main.h"
#include"continue.h"
#include"input.h"
#include"pause.h"

//*******************************************************************************
//�O���[�o���ϐ�
//*******************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureContinue = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffContinue = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Continue g_Continue;

//********************************************************************************
//�R���e�B�j���[�̏���������
//********************************************************************************
void InitContinue(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�|���S���ɒ���t����e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/pause000.png",
		&g_pTextureContinue);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									//���_�t�@�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffContinue,
		NULL);

	//�^�C�g�����S���̏�����
	g_Continue.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���S�_
	g_Continue.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���S�_����̍�
	g_Continue.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����
	g_Continue.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//�J���[
	g_Continue.bUse = false;								//�g�p���ĂȂ�

	//���_���ւ̃|�C���^�𐶐�						
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffContinue->Lock(0, 0, (void**)&pVtx, 0);

	//�Ίp���̒������Z�o����
	g_Continue.fLength = sqrtf(((g_Continue.offset.x * g_Continue.offset.x) + (g_Continue.offset.y * g_Continue.offset.y)) / 2.0f);

	//�Ίp���̊p�x���Z�o
	g_Continue.fAngele = atan2f(g_Continue.offset.x, g_Continue.offset.y);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_Continue.pos.x + sinf(g_Continue.rot.z + (D3DX_PI + g_Continue.fAngele)) * g_Continue.fLength;
	pVtx[0].pos.y = g_Continue.pos.y + cosf(g_Continue.rot.z + (D3DX_PI + g_Continue.fAngele)) * g_Continue.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Continue.pos.x + sinf(g_Continue.rot.z + (D3DX_PI - g_Continue.fAngele)) *  g_Continue.fLength;
	pVtx[1].pos.y = g_Continue.pos.y + cosf(g_Continue.rot.z + (D3DX_PI - g_Continue.fAngele)) *  g_Continue.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Continue.pos.x + sinf(g_Continue.rot.z - (0 + g_Continue.fAngele)) * g_Continue.fLength;
	pVtx[2].pos.y = g_Continue.pos.y + cosf(g_Continue.rot.z - (0 + g_Continue.fAngele)) * g_Continue.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Continue.pos.x + sinf(g_Continue.rot.z - (0 - g_Continue.fAngele)) *  g_Continue.fLength;
	pVtx[3].pos.y = g_Continue.pos.y + cosf(g_Continue.rot.z - (0 - g_Continue.fAngele)) *  g_Continue.fLength;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_Continue.col;
	pVtx[1].col = g_Continue.col;
	pVtx[2].col = g_Continue.col;
	pVtx[3].col = g_Continue.col;

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffContinue->Unlock();
}

//********************************************************************************
//�R���e�B�j���[�̏I������
//********************************************************************************
void UninitContinue(void)
{
	//�e�N�X�`���̔j��	  
	if (g_pTextureContinue != NULL)
	{
		g_pTextureContinue->Release();

		g_pTextureContinue = NULL;
	}

	//���_�o�b�t�@��j��
	if (g_pVtxBuffContinue != NULL)
	{
		g_pVtxBuffContinue->Release();

		g_pVtxBuffContinue = NULL;
	}
}

//********************************************************************************
//�R���e�B�j���[�̍X�V����
//********************************************************************************
void UpdateContinue(void)
{
	if (g_Continue.bUse == true)
	{//�g�p����Ă�ꍇ
		//�|�[�Y���̎擾
		Pause *pPause;				//�|�[�Y���ւ̃|�C���^
		pPause = GetPause();

		if (pPause->state == NEXTPROCESS_CONTINUE)
		{//���ɍs���鏈�����Q�[�����(�p��)�̎�
			g_Continue.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//���_���ւ̃|�C���^�𐶐�						
			VERTEX_2D *pVtx;

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffContinue->Lock(0, 0, (void**)&pVtx, 0);

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_Continue.col;
			pVtx[1].col = g_Continue.col;
			pVtx[2].col = g_Continue.col;
			pVtx[3].col = g_Continue.col;

			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffContinue->Unlock();
		}
		else if (pPause->state != NEXTPROCESS_CONTINUE)
		{//���ɍs���鏈�����Q�[�����(�p��)�ȊO�̎�
			g_Continue.col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

			//���_���ւ̃|�C���^�𐶐�						
			VERTEX_2D *pVtx;

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffContinue->Lock(0, 0, (void**)&pVtx, 0);

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_Continue.col;
			pVtx[1].col = g_Continue.col;
			pVtx[2].col = g_Continue.col;
			pVtx[3].col = g_Continue.col;

			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffContinue->Unlock();
		}
	}
}

//********************************************************************************
//�R���e�B�j���[�̕`�揈��
//********************************************************************************
void DrawContinue(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffContinue, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_Continue.bUse == true)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureContinue);

		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//********************************************************************************
//�R���e�B�j���[�̐ݒ菈��
//********************************************************************************
void SetContinue(void)
{
	//���_���ւ̃|�C���^�𐶐�						
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffContinue->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Continue.bUse == false)
	{//�g�p����ĂȂ��ꍇ
		//�^�C�g�����S���̐ݒ�
		g_Continue.offset = D3DXVECTOR3(MAX_OFFSET_CONTINUE_X, MAX_OFFSET_CONTINUE_Y, 0.0f);		//���S�_����̍�
		g_Continue.pos = D3DXVECTOR3(POS_CONTINUE_X, POS_CONTINUE_Y, 0.0f);							//���S�_
		g_Continue.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);												//����
		g_Continue.col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);											//�J���[
		g_Continue.bUse = true;																		//�g�p���Ă�

		//�Ίp���̒������Z�o����
		g_Continue.fLength = sqrtf(((g_Continue.offset.x * g_Continue.offset.x) + (g_Continue.offset.y * g_Continue.offset.y)) / 2.0f);

		//�Ίp���̊p�x���Z�o
		g_Continue.fAngele = atan2f(g_Continue.offset.x, g_Continue.offset.y);

		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_Continue.pos.x + sinf(g_Continue.rot.z + (D3DX_PI + g_Continue.fAngele)) * g_Continue.fLength;
		pVtx[0].pos.y = g_Continue.pos.y + cosf(g_Continue.rot.z + (D3DX_PI + g_Continue.fAngele)) * g_Continue.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Continue.pos.x + sinf(g_Continue.rot.z + (D3DX_PI - g_Continue.fAngele)) *  g_Continue.fLength;
		pVtx[1].pos.y = g_Continue.pos.y + cosf(g_Continue.rot.z + (D3DX_PI - g_Continue.fAngele)) *  g_Continue.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Continue.pos.x + sinf(g_Continue.rot.z - (0 + g_Continue.fAngele)) * g_Continue.fLength;
		pVtx[2].pos.y = g_Continue.pos.y + cosf(g_Continue.rot.z - (0 + g_Continue.fAngele)) * g_Continue.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Continue.pos.x + sinf(g_Continue.rot.z - (0 - g_Continue.fAngele)) *  g_Continue.fLength;
		pVtx[3].pos.y = g_Continue.pos.y + cosf(g_Continue.rot.z - (0 - g_Continue.fAngele)) *  g_Continue.fLength;
		pVtx[3].pos.z = 0.0f;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_Continue.col;
		pVtx[1].col = g_Continue.col;
		pVtx[2].col = g_Continue.col;
		pVtx[3].col = g_Continue.col;

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffContinue->Unlock();
}