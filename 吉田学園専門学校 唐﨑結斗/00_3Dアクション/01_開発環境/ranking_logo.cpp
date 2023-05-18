//**************************************************************************************************
//
//�����L���O���S�̐ݒ菈��
//Auther�F�������l
//
//**************************************************************************************************
#include"main.h"
#include"ranking_logo.h"

//*******************************************************************************
//�O���[�o���ϐ�
//*******************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureRankingLogo = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingLogo = NULL;		//���_�o�b�t�@�ւ̃|�C���^
RankingLogo g_RankingLogo;									//�����L���O���S���

//********************************************************************************
//�����L���O���S�̏���������
//********************************************************************************
void InitRankingLogo(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�|���S���ɒ���t����e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ranking_logo.png",
		&g_pTextureRankingLogo);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									//���_�t�@�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingLogo,
		NULL);

	//�����L���O���S���̏�����
	g_RankingLogo.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���S�_
	g_RankingLogo.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���S�_����̍�
	g_RankingLogo.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����
	g_RankingLogo.bUse = false;									//�g�p���ĂȂ�
														
	//���_���ւ̃|�C���^�𐶐�						
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRankingLogo->Lock(0, 0, (void**)&pVtx, 0);

	//�Ίp���̒������Z�o����
	g_RankingLogo.fLength = sqrtf(((g_RankingLogo.offset.x * g_RankingLogo.offset.x) + (g_RankingLogo.offset.y * g_RankingLogo.offset.y)) / 2.0f);

	//�Ίp���̊p�x���Z�o
	g_RankingLogo.fAngele = atan2f(g_RankingLogo.offset.x, g_RankingLogo.offset.y);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_RankingLogo.pos.x + sinf(g_RankingLogo.rot.z + (D3DX_PI + g_RankingLogo.fAngele)) * g_RankingLogo.fLength;
	pVtx[0].pos.y = g_RankingLogo.pos.y + cosf(g_RankingLogo.rot.z + (D3DX_PI + g_RankingLogo.fAngele)) * g_RankingLogo.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_RankingLogo.pos.x + sinf(g_RankingLogo.rot.z + (D3DX_PI - g_RankingLogo.fAngele)) *  g_RankingLogo.fLength;
	pVtx[1].pos.y = g_RankingLogo.pos.y + cosf(g_RankingLogo.rot.z + (D3DX_PI - g_RankingLogo.fAngele)) *  g_RankingLogo.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_RankingLogo.pos.x + sinf(g_RankingLogo.rot.z - (0 + g_RankingLogo.fAngele)) * g_RankingLogo.fLength;
	pVtx[2].pos.y = g_RankingLogo.pos.y + cosf(g_RankingLogo.rot.z - (0 + g_RankingLogo.fAngele)) * g_RankingLogo.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_RankingLogo.pos.x + sinf(g_RankingLogo.rot.z - (0 - g_RankingLogo.fAngele)) *  g_RankingLogo.fLength;
	pVtx[3].pos.y = g_RankingLogo.pos.y + cosf(g_RankingLogo.rot.z - (0 - g_RankingLogo.fAngele)) *  g_RankingLogo.fLength;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRankingLogo->Unlock();
}

//********************************************************************************
//�����L���O���S�̏I������
//********************************************************************************
void UninitRankingLogo(void)
{
	//�e�N�X�`���̔j��	  
	if (g_pTextureRankingLogo != NULL)
	{
		g_pTextureRankingLogo->Release();

		g_pTextureRankingLogo = NULL;
	}

	//���_�o�b�t�@��j��
	if (g_pVtxBuffRankingLogo != NULL)
	{
		g_pVtxBuffRankingLogo->Release();

		g_pVtxBuffRankingLogo = NULL;
	}
}

//********************************************************************************
//�����L���O���S�̍X�V����
//********************************************************************************
void UpdateRankingLogo(void)
{

}

//********************************************************************************
//�����L���O���S�̕`�揈��
//********************************************************************************
void DrawRankingLogo(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankingLogo, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_RankingLogo.bUse == true)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRankingLogo);

		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//********************************************************************************
//�����L���O���S�̐ݒ菈��
//********************************************************************************
void SetRankingLogo(void)
{
	//���_���ւ̃|�C���^�𐶐�						
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRankingLogo->Lock(0, 0, (void**)&pVtx, 0);

	if (g_RankingLogo.bUse == false)
	{//�g�p����ĂȂ��ꍇ
		//�����L���O���S���̐ݒ�
		g_RankingLogo.offset = D3DXVECTOR3(MAX_OFFSET_RL_X, MAX_OFFSET_RL_Y, 0.0f);				//���S�_����̍�
		g_RankingLogo.pos = D3DXVECTOR3(SCREEN_WIDH / 2, 0.0f + g_RankingLogo.offset.y, 0.0f);	//���S�_
		g_RankingLogo.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										//����
		g_RankingLogo.bUse = true;																//�g�p���Ă�

		//�Ίp���̒������Z�o����
		g_RankingLogo.fLength = sqrtf(((g_RankingLogo.offset.x * g_RankingLogo.offset.x) + (g_RankingLogo.offset.y * g_RankingLogo.offset.y)) / 2.0f);

		//�Ίp���̊p�x���Z�o
		g_RankingLogo.fAngele = atan2f(g_RankingLogo.offset.x, g_RankingLogo.offset.y);

		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_RankingLogo.pos.x + sinf(g_RankingLogo.rot.z + (D3DX_PI + g_RankingLogo.fAngele)) * g_RankingLogo.fLength;
		pVtx[0].pos.y = g_RankingLogo.pos.y + cosf(g_RankingLogo.rot.z + (D3DX_PI + g_RankingLogo.fAngele)) * g_RankingLogo.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_RankingLogo.pos.x + sinf(g_RankingLogo.rot.z + (D3DX_PI - g_RankingLogo.fAngele)) *  g_RankingLogo.fLength;
		pVtx[1].pos.y = g_RankingLogo.pos.y + cosf(g_RankingLogo.rot.z + (D3DX_PI - g_RankingLogo.fAngele)) *  g_RankingLogo.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_RankingLogo.pos.x + sinf(g_RankingLogo.rot.z - (0 + g_RankingLogo.fAngele)) * g_RankingLogo.fLength;
		pVtx[2].pos.y = g_RankingLogo.pos.y + cosf(g_RankingLogo.rot.z - (0 + g_RankingLogo.fAngele)) * g_RankingLogo.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_RankingLogo.pos.x + sinf(g_RankingLogo.rot.z - (0 - g_RankingLogo.fAngele)) *  g_RankingLogo.fLength;
		pVtx[3].pos.y = g_RankingLogo.pos.y + cosf(g_RankingLogo.rot.z - (0 - g_RankingLogo.fAngele)) *  g_RankingLogo.fLength;
		pVtx[3].pos.z = 0.0f;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRankingLogo->Unlock();
}