//**************************************************************************************************
//
//�N���C�G�b�g�̐ݒ菈��
//Auther�F�������l
//
//**************************************************************************************************
#include"main.h"
#include"quit.h"
#include"input.h"
#include"pause.h"

//*******************************************************************************
//�O���[�o���ϐ�
//*******************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureQuit = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffQuit = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Quit g_Quit;

//********************************************************************************
//�N���C�G�b�g�̏���������
//********************************************************************************
void InitQuit(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�|���S���ɒ���t����e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/pause002.png",
		&g_pTextureQuit);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									//���_�t�@�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffQuit,
		NULL);

	//�^�C�g�����S���̏�����
	g_Quit.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���S�_
	g_Quit.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���S�_����̍�
	g_Quit.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����
	g_Quit.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//�J���[
	g_Quit.bUse = false;								//�g�p���ĂȂ�

														//���_���ւ̃|�C���^�𐶐�						
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffQuit->Lock(0, 0, (void**)&pVtx, 0);

	//�Ίp���̒������Z�o����
	g_Quit.fLength = sqrtf(((g_Quit.offset.x * g_Quit.offset.x) + (g_Quit.offset.y * g_Quit.offset.y)) / 2.0f);

	//�Ίp���̊p�x���Z�o
	g_Quit.fAngele = atan2f(g_Quit.offset.x, g_Quit.offset.y);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_Quit.pos.x + sinf(g_Quit.rot.z + (D3DX_PI + g_Quit.fAngele)) * g_Quit.fLength;
	pVtx[0].pos.y = g_Quit.pos.y + cosf(g_Quit.rot.z + (D3DX_PI + g_Quit.fAngele)) * g_Quit.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Quit.pos.x + sinf(g_Quit.rot.z + (D3DX_PI - g_Quit.fAngele)) *  g_Quit.fLength;
	pVtx[1].pos.y = g_Quit.pos.y + cosf(g_Quit.rot.z + (D3DX_PI - g_Quit.fAngele)) *  g_Quit.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Quit.pos.x + sinf(g_Quit.rot.z - (0 + g_Quit.fAngele)) * g_Quit.fLength;
	pVtx[2].pos.y = g_Quit.pos.y + cosf(g_Quit.rot.z - (0 + g_Quit.fAngele)) * g_Quit.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Quit.pos.x + sinf(g_Quit.rot.z - (0 - g_Quit.fAngele)) *  g_Quit.fLength;
	pVtx[3].pos.y = g_Quit.pos.y + cosf(g_Quit.rot.z - (0 - g_Quit.fAngele)) *  g_Quit.fLength;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_Quit.col;
	pVtx[1].col = g_Quit.col;
	pVtx[2].col = g_Quit.col;
	pVtx[3].col = g_Quit.col;

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffQuit->Unlock();
}

//********************************************************************************
//�N���C�G�b�g�̏I������
//********************************************************************************
void UninitQuit(void)
{
	//�e�N�X�`���̔j��	  
	if (g_pTextureQuit != NULL)
	{
		g_pTextureQuit->Release();

		g_pTextureQuit = NULL;
	}

	//���_�o�b�t�@��j��
	if (g_pVtxBuffQuit != NULL)
	{
		g_pVtxBuffQuit->Release();

		g_pVtxBuffQuit = NULL;
	}
}

//********************************************************************************
//�N���C�G�b�g�̍X�V����
//********************************************************************************
void UpdateQuit(void)
{
	if (g_Quit.bUse == true)
	{//�g�p����Ă�ꍇ
	 //�|�[�Y���̎擾
		Pause *pPause;				//�|�[�Y���ւ̃|�C���^
		pPause = GetPause();

		if (pPause->state == NEXTPROCESS_QUIT)
		{//���ɍs���鏈�����Q�[�����(�p��)�̎�
			g_Quit.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//���_���ւ̃|�C���^�𐶐�						
			VERTEX_2D *pVtx;

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffQuit->Lock(0, 0, (void**)&pVtx, 0);

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_Quit.col;
			pVtx[1].col = g_Quit.col;
			pVtx[2].col = g_Quit.col;
			pVtx[3].col = g_Quit.col;

			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffQuit->Unlock();
		}
		else if (pPause->state != NEXTPROCESS_QUIT)
		{//���ɍs���鏈�����Q�[�����(�p��)�ȊO�̎�
			g_Quit.col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

			//���_���ւ̃|�C���^�𐶐�						
			VERTEX_2D *pVtx;

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffQuit->Lock(0, 0, (void**)&pVtx, 0);

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_Quit.col;
			pVtx[1].col = g_Quit.col;
			pVtx[2].col = g_Quit.col;
			pVtx[3].col = g_Quit.col;

			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffQuit->Unlock();
		}
	}
}

//********************************************************************************
//�N���C�G�b�g�̕`�揈��
//********************************************************************************
void DrawQuit(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffQuit, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_Quit.bUse == true)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureQuit);

		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//********************************************************************************
//�N���C�G�b�g�̐ݒ菈��
//********************************************************************************
void SetQuit(void)
{
	//���_���ւ̃|�C���^�𐶐�						
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffQuit->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Quit.bUse == false)
	{//�g�p����ĂȂ��ꍇ
	 //�^�C�g�����S���̐ݒ�
		g_Quit.offset = D3DXVECTOR3(MAX_OFFSET_QUIT_X, MAX_OFFSET_QUIT_Y, 0.0f);		//���S�_����̍�
		g_Quit.pos = D3DXVECTOR3(POS_QUIT_X, POS_QUIT_Y, 0.0f);						//���S�_
		g_Quit.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//����
		g_Quit.col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);								//�J���[
		g_Quit.bUse = true;															//�g�p���Ă�

																						//�Ίp���̒������Z�o����
		g_Quit.fLength = sqrtf(((g_Quit.offset.x * g_Quit.offset.x) + (g_Quit.offset.y * g_Quit.offset.y)) / 2.0f);

		//�Ίp���̊p�x���Z�o
		g_Quit.fAngele = atan2f(g_Quit.offset.x, g_Quit.offset.y);

		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_Quit.pos.x + sinf(g_Quit.rot.z + (D3DX_PI + g_Quit.fAngele)) * g_Quit.fLength;
		pVtx[0].pos.y = g_Quit.pos.y + cosf(g_Quit.rot.z + (D3DX_PI + g_Quit.fAngele)) * g_Quit.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Quit.pos.x + sinf(g_Quit.rot.z + (D3DX_PI - g_Quit.fAngele)) *  g_Quit.fLength;
		pVtx[1].pos.y = g_Quit.pos.y + cosf(g_Quit.rot.z + (D3DX_PI - g_Quit.fAngele)) *  g_Quit.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Quit.pos.x + sinf(g_Quit.rot.z - (0 + g_Quit.fAngele)) * g_Quit.fLength;
		pVtx[2].pos.y = g_Quit.pos.y + cosf(g_Quit.rot.z - (0 + g_Quit.fAngele)) * g_Quit.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Quit.pos.x + sinf(g_Quit.rot.z - (0 - g_Quit.fAngele)) *  g_Quit.fLength;
		pVtx[3].pos.y = g_Quit.pos.y + cosf(g_Quit.rot.z - (0 - g_Quit.fAngele)) *  g_Quit.fLength;
		pVtx[3].pos.z = 0.0f;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_Quit.col;
		pVtx[1].col = g_Quit.col;
		pVtx[2].col = g_Quit.col;
		pVtx[3].col = g_Quit.col;

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffQuit->Unlock();
}