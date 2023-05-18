//**************************************************************************************************
//
//���g���C�̐ݒ菈��
//Auther�F�������l
//
//**************************************************************************************************
#include"main.h"
#include"retry.h"
#include"input.h"
#include"pause.h"

//*******************************************************************************
//�O���[�o���ϐ�
//*******************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureRetry = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRetry = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Retry g_Retry;

//********************************************************************************
//���g���C�̏���������
//********************************************************************************
void InitRetry(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�|���S���ɒ���t����e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/pause001.png",
		&g_pTextureRetry);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									//���_�t�@�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffRetry,
		NULL);

	//�^�C�g�����S���̏�����
	g_Retry.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���S�_
	g_Retry.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���S�_����̍�
	g_Retry.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����
	g_Retry.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//�J���[
	g_Retry.bUse = false;									//�g�p���ĂȂ�

	//���_���ւ̃|�C���^�𐶐�						
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRetry->Lock(0, 0, (void**)&pVtx, 0);

	//�Ίp���̒������Z�o����
	g_Retry.fLength = sqrtf(((g_Retry.offset.x * g_Retry.offset.x) + (g_Retry.offset.y * g_Retry.offset.y)) / 2.0f);

	//�Ίp���̊p�x���Z�o
	g_Retry.fAngele = atan2f(g_Retry.offset.x, g_Retry.offset.y);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_Retry.pos.x + sinf(g_Retry.rot.z + (D3DX_PI + g_Retry.fAngele)) * g_Retry.fLength;
	pVtx[0].pos.y = g_Retry.pos.y + cosf(g_Retry.rot.z + (D3DX_PI + g_Retry.fAngele)) * g_Retry.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Retry.pos.x + sinf(g_Retry.rot.z + (D3DX_PI - g_Retry.fAngele)) *  g_Retry.fLength;
	pVtx[1].pos.y = g_Retry.pos.y + cosf(g_Retry.rot.z + (D3DX_PI - g_Retry.fAngele)) *  g_Retry.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Retry.pos.x + sinf(g_Retry.rot.z - (0 + g_Retry.fAngele)) * g_Retry.fLength;
	pVtx[2].pos.y = g_Retry.pos.y + cosf(g_Retry.rot.z - (0 + g_Retry.fAngele)) * g_Retry.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Retry.pos.x + sinf(g_Retry.rot.z - (0 - g_Retry.fAngele)) *  g_Retry.fLength;
	pVtx[3].pos.y = g_Retry.pos.y + cosf(g_Retry.rot.z - (0 - g_Retry.fAngele)) *  g_Retry.fLength;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_Retry.col;
	pVtx[1].col = g_Retry.col;
	pVtx[2].col = g_Retry.col;
	pVtx[3].col = g_Retry.col;

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRetry->Unlock();
}

//********************************************************************************
//���g���C�̏I������
//********************************************************************************
void UninitRetry(void)
{
	//�e�N�X�`���̔j��	  
	if (g_pTextureRetry != NULL)
	{
		g_pTextureRetry->Release();

		g_pTextureRetry = NULL;
	}

	//���_�o�b�t�@��j��
	if (g_pVtxBuffRetry != NULL)
	{
		g_pVtxBuffRetry->Release();

		g_pVtxBuffRetry = NULL;
	}
}

//********************************************************************************
//���g���C�̍X�V����
//********************************************************************************
void UpdateRetry(void)
{
	if (g_Retry.bUse == true)
	{//�g�p����Ă�ꍇ
		//�|�[�Y���̎擾
		Pause *pPause;				//�|�[�Y���ւ̃|�C���^
		pPause = GetPause();

		if (pPause->state == NEXTPROCESS_RETRY)
		{//���ɍs���鏈�����Q�[�����(�p��)�̎�
			g_Retry.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//���_���ւ̃|�C���^�𐶐�						
			VERTEX_2D *pVtx;

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffRetry->Lock(0, 0, (void**)&pVtx, 0);

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_Retry.col;
			pVtx[1].col = g_Retry.col;
			pVtx[2].col = g_Retry.col;
			pVtx[3].col = g_Retry.col;

			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffRetry->Unlock();
		}
		else if (pPause->state != NEXTPROCESS_RETRY)
		{//���ɍs���鏈�����Q�[�����(�p��)�ȊO�̎�
			g_Retry.col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

			//���_���ւ̃|�C���^�𐶐�						
			VERTEX_2D *pVtx;

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffRetry->Lock(0, 0, (void**)&pVtx, 0);

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_Retry.col;
			pVtx[1].col = g_Retry.col;
			pVtx[2].col = g_Retry.col;
			pVtx[3].col = g_Retry.col;

			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffRetry->Unlock();
		}
	}
}

//********************************************************************************
//���g���C�̕`�揈��
//********************************************************************************
void DrawRetry(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRetry, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_Retry.bUse == true)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRetry);

		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//********************************************************************************
//���g���C�̐ݒ菈��
//********************************************************************************
void SetRetry(void)
{
	//���_���ւ̃|�C���^�𐶐�						
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRetry->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Retry.bUse == false)
	{//�g�p����ĂȂ��ꍇ
	 //�^�C�g�����S���̐ݒ�
		g_Retry.offset = D3DXVECTOR3(MAX_OFFSET_RETRY_X, MAX_OFFSET_RETRY_Y, 0.0f);		//���S�_����̍�
		g_Retry.pos = D3DXVECTOR3(POS_RETRY_X, POS_RETRY_Y, 0.0f);						//���S�_
		g_Retry.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//����
		g_Retry.col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);								//�J���[
		g_Retry.bUse = true;															//�g�p���Ă�

		//�Ίp���̒������Z�o����
		g_Retry.fLength = sqrtf(((g_Retry.offset.x * g_Retry.offset.x) + (g_Retry.offset.y * g_Retry.offset.y)) / 2.0f);

		//�Ίp���̊p�x���Z�o
		g_Retry.fAngele = atan2f(g_Retry.offset.x, g_Retry.offset.y);

		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_Retry.pos.x + sinf(g_Retry.rot.z + (D3DX_PI + g_Retry.fAngele)) * g_Retry.fLength;
		pVtx[0].pos.y = g_Retry.pos.y + cosf(g_Retry.rot.z + (D3DX_PI + g_Retry.fAngele)) * g_Retry.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Retry.pos.x + sinf(g_Retry.rot.z + (D3DX_PI - g_Retry.fAngele)) *  g_Retry.fLength;
		pVtx[1].pos.y = g_Retry.pos.y + cosf(g_Retry.rot.z + (D3DX_PI - g_Retry.fAngele)) *  g_Retry.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Retry.pos.x + sinf(g_Retry.rot.z - (0 + g_Retry.fAngele)) * g_Retry.fLength;
		pVtx[2].pos.y = g_Retry.pos.y + cosf(g_Retry.rot.z - (0 + g_Retry.fAngele)) * g_Retry.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Retry.pos.x + sinf(g_Retry.rot.z - (0 - g_Retry.fAngele)) *  g_Retry.fLength;
		pVtx[3].pos.y = g_Retry.pos.y + cosf(g_Retry.rot.z - (0 - g_Retry.fAngele)) *  g_Retry.fLength;
		pVtx[3].pos.z = 0.0f;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_Retry.col;
		pVtx[1].col = g_Retry.col;
		pVtx[2].col = g_Retry.col;
		pVtx[3].col = g_Retry.col;

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRetry->Unlock();
}