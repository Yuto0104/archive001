//**************************************************************************************************
//
// �^�C�g�����S�̐ݒ菈��
// Auther�F�������l
//
//**************************************************************************************************
#include"main.h"
#include"titlelogo.h"
#include"input.h"
#include"press enter.h"

//*******************************************************************************
// �O���[�o���ϐ�
//*******************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTitleLogo = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleLogo = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Logo g_Logo;											//�^�C�g�����S���

//********************************************************************************
// �^�C�g�����S�̏���������
//********************************************************************************
void InitTitleLogo(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �|���S���ɒ���t����e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/�^�C�g��.png",
		&g_pTextureTitleLogo);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// ���_�t�@�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitleLogo,
		NULL);

	// �^�C�g�����S���̏�����
	g_Logo.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���S�_
	g_Logo.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���S�_����̍�
	g_Logo.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����
	g_Logo.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ�����
	g_Logo.fSpeed = 0.0f;								// �ړ����x
	g_Logo.bUse = false;								// �g�p���ĂȂ�
														
	// ���_���ւ̃|�C���^�𐶐�						
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

	// �Ίp���̒������Z�o����
	g_Logo.fLength = sqrtf(((g_Logo.offset.x * g_Logo.offset.x) + (g_Logo.offset.y * g_Logo.offset.y)) / 2.0f);

	// �Ίp���̊p�x���Z�o
	g_Logo.fAngele = atan2f(g_Logo.offset.x, g_Logo.offset.y);

	// ���_���W�̐ݒ�
	pVtx[0].pos.x = g_Logo.pos.x + sinf(g_Logo.rot.z + (D3DX_PI + g_Logo.fAngele)) * g_Logo.fLength;
	pVtx[0].pos.y = g_Logo.pos.y + cosf(g_Logo.rot.z + (D3DX_PI + g_Logo.fAngele)) * g_Logo.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Logo.pos.x + sinf(g_Logo.rot.z + (D3DX_PI - g_Logo.fAngele)) *  g_Logo.fLength;
	pVtx[1].pos.y = g_Logo.pos.y + cosf(g_Logo.rot.z + (D3DX_PI - g_Logo.fAngele)) *  g_Logo.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Logo.pos.x + sinf(g_Logo.rot.z - (0 + g_Logo.fAngele)) * g_Logo.fLength;
	pVtx[2].pos.y = g_Logo.pos.y + cosf(g_Logo.rot.z - (0 + g_Logo.fAngele)) * g_Logo.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Logo.pos.x + sinf(g_Logo.rot.z - (0 - g_Logo.fAngele)) *  g_Logo.fLength;
	pVtx[3].pos.y = g_Logo.pos.y + cosf(g_Logo.rot.z - (0 - g_Logo.fAngele)) *  g_Logo.fLength;
	pVtx[3].pos.z = 0.0f;

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitleLogo->Unlock();
}

//********************************************************************************
// �^�C�g�����S�̏I������
//********************************************************************************
void UninitTitleLogo(void)
{
	// �e�N�X�`���̔j��	  
	if (g_pTextureTitleLogo != NULL)
	{
		g_pTextureTitleLogo->Release();

		g_pTextureTitleLogo = NULL;
	}

	// ���_�o�b�t�@��j��
	if (g_pVtxBuffTitleLogo != NULL)
	{
		g_pVtxBuffTitleLogo->Release();

		g_pVtxBuffTitleLogo = NULL;
	}
}

//********************************************************************************
// �^�C�g�����S�̍X�V����
//********************************************************************************
void UpdateTitleLogo(void)
{
	// ���_���ւ̃|�C���^�𐶐�						
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Logo.bUse == true)
	{// �^�C�g�����S���g�p����Ă�
		if (g_Logo.pos.y < MAX_MOVED)
		{// ����̈ʒu�܂ňړ�����
			// �ʒu�̍X�V
			g_Logo.pos.x += g_Logo.move.x;
			g_Logo.pos.y += g_Logo.move.y;

			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{// [Enter]�L�[�������ꂽ
				g_Logo.pos.y = MAX_MOVED;
			}
		}
		else if (g_Logo.pos.y >= MAX_MOVED)
		{// ���l���Œ�
			g_Logo.pos.y = MAX_MOVED;
			
			// �v���X�G���^�[�̐ݒ菈��
			SetPressEnter(D3DXVECTOR3(SCREEN_WIDH / 2, PRESS_ENTER_POS_Y, 0.0f), D3DXVECTOR3(MAX_OFFSET_PE_X, MAX_OFFSET_PE_Y, 0.0f));
		}

		// �Ίp���̒������Z�o����
		g_Logo.fLength = sqrtf(((g_Logo.offset.x * g_Logo.offset.x) + (g_Logo.offset.y * g_Logo.offset.y)) / 2.0f);

		// �Ίp���̊p�x���Z�o
		g_Logo.fAngele = atan2f(g_Logo.offset.x, g_Logo.offset.y);

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = g_Logo.pos.x + sinf(g_Logo.rot.z + (D3DX_PI + g_Logo.fAngele)) * g_Logo.fLength;
		pVtx[0].pos.y = g_Logo.pos.y + cosf(g_Logo.rot.z + (D3DX_PI + g_Logo.fAngele)) * g_Logo.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Logo.pos.x + sinf(g_Logo.rot.z + (D3DX_PI - g_Logo.fAngele)) *  g_Logo.fLength;
		pVtx[1].pos.y = g_Logo.pos.y + cosf(g_Logo.rot.z + (D3DX_PI - g_Logo.fAngele)) *  g_Logo.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Logo.pos.x + sinf(g_Logo.rot.z - (0 + g_Logo.fAngele)) * g_Logo.fLength;
		pVtx[2].pos.y = g_Logo.pos.y + cosf(g_Logo.rot.z - (0 + g_Logo.fAngele)) * g_Logo.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Logo.pos.x + sinf(g_Logo.rot.z - (0 - g_Logo.fAngele)) *  g_Logo.fLength;
		pVtx[3].pos.y = g_Logo.pos.y + cosf(g_Logo.rot.z - (0 - g_Logo.fAngele)) *  g_Logo.fLength;
		pVtx[3].pos.z = 0.0f;

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitleLogo->Unlock();
}

//********************************************************************************
// �^�C�g�����S�̕`�揈��
//********************************************************************************
void DrawTitleLogo(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitleLogo, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ���e�X�g���g�p����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// ���e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	if (g_Logo.bUse == true)
	{// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitleLogo);

		// �|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	// ���e�X�g�̏I��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//********************************************************************************
// �^�C�g�����S�̐ݒ菈��
//********************************************************************************
void SetTitleLogo(void)
{
	// ���_���ւ̃|�C���^�𐶐�						
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Logo.bUse == false)
	{// �g�p����ĂȂ��ꍇ
		// �^�C�g�����S���̐ݒ�
		g_Logo.offset = D3DXVECTOR3(MAX_OFFSET_TL_X, MAX_OFFSET_TL_Y, 0.0f);		// ���S�_����̍�
		g_Logo.pos = D3DXVECTOR3(SCREEN_WIDH / 2, 0.0f - g_Logo.offset.y, 0.0f);	// ���S�_
		g_Logo.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									// ����
		g_Logo.fSpeed = MAX_MOVE_SPEED;												// �ړ����x
		g_Logo.bUse = true;															// �g�p���Ă�

		// �ړ��ʂ̐ݒ�
		g_Logo.move.x += sinf(D3DX_PI - D3DX_PI) * g_Logo.fSpeed;
		g_Logo.move.y += cosf(D3DX_PI - D3DX_PI) * g_Logo.fSpeed;

		// �Ίp���̒������Z�o����
		g_Logo.fLength = sqrtf(((g_Logo.offset.x * g_Logo.offset.x) + (g_Logo.offset.y * g_Logo.offset.y)) / 2.0f);

		// �Ίp���̊p�x���Z�o
		g_Logo.fAngele = atan2f(g_Logo.offset.x, g_Logo.offset.y);

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = g_Logo.pos.x + sinf(g_Logo.rot.z + (D3DX_PI + g_Logo.fAngele)) * g_Logo.fLength;
		pVtx[0].pos.y = g_Logo.pos.y + cosf(g_Logo.rot.z + (D3DX_PI + g_Logo.fAngele)) * g_Logo.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Logo.pos.x + sinf(g_Logo.rot.z + (D3DX_PI - g_Logo.fAngele)) *  g_Logo.fLength;
		pVtx[1].pos.y = g_Logo.pos.y + cosf(g_Logo.rot.z + (D3DX_PI - g_Logo.fAngele)) *  g_Logo.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Logo.pos.x + sinf(g_Logo.rot.z - (0 + g_Logo.fAngele)) * g_Logo.fLength;
		pVtx[2].pos.y = g_Logo.pos.y + cosf(g_Logo.rot.z - (0 + g_Logo.fAngele)) * g_Logo.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Logo.pos.x + sinf(g_Logo.rot.z - (0 - g_Logo.fAngele)) *  g_Logo.fLength;
		pVtx[3].pos.y = g_Logo.pos.y + cosf(g_Logo.rot.z - (0 - g_Logo.fAngele)) *  g_Logo.fLength;
		pVtx[3].pos.z = 0.0f;

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitleLogo->Unlock();
}