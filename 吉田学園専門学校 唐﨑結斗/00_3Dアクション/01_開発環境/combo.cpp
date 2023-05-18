//**************************************************************************************************
//
// �R���{�̏���
// Auther�F�������l
//
//**************************************************************************************************

#include"main.h"
//#include"sound.h"

#include"combo.h"
#include"player.h"
#include"score.h"
#include"fade.h"

//*************************************************************
// �O���[�o���ϐ�
//*************************************************************
static LPDIRECT3DTEXTURE9			g_pTextureCombo = NULL;			// �e�N�X�`���ւ̃|�C���^
static LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffCombo = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
static Combo						g_Combo;						// �R���{���
static int							g_nCombo;						// �R���{�̒l
static int							g_nCntFrame;					// �t���[���̌v�Z

//*************************************************************
// �R���{�̏���������
//*************************************************************
void InitCombo(void)
{
	// �ϐ��錾
	int nCountDigits;	// �������J�E���g����

	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �|���S���ɒ���t����e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureCombo);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * MAX_VERTEX * MAX_COMBO_DIGITS,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,																// ���_�t�@�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffCombo,
		NULL);

	// ���l�̏�����
	g_Combo.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���S�_����̍�
	g_Combo.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
	g_nCombo = 0;										// �R���{�̒l
	g_nCntFrame = 0;									// �t���[���J�E���^��������
	g_Combo.bUse = false;								// �g�p���Ă��Ȃ�

	// �R���{�̈ʒu�̏�����
	for (nCountDigits = 0; nCountDigits < MAX_COMBO_DIGITS; nCountDigits++)
	{
		g_Combo.pos[nCountDigits] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// ���_���ւ̃|�C���^�𐶐�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCombo->Lock(0, 0, (void**)&pVtx, 0);

	// �Ίp���̒������Z�o����
	g_Combo.fLength = sqrtf(((g_Combo.offset.x * g_Combo.offset.x) + (g_Combo.offset.y * g_Combo.offset.y)) / 2.0f);

	// �Ίp���̊p�x���Z�o
	g_Combo.fAngele = atan2f(g_Combo.offset.x, g_Combo.offset.y);

	for (nCountDigits = 0; nCountDigits < MAX_COMBO_DIGITS; nCountDigits++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos.x = g_Combo.pos[nCountDigits].x + sinf(g_Combo.rot.z + (D3DX_PI + g_Combo.fAngele)) * g_Combo.fLength;
		pVtx[0].pos.y = g_Combo.pos[nCountDigits].y + cosf(g_Combo.rot.z + (D3DX_PI + g_Combo.fAngele)) * g_Combo.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Combo.pos[nCountDigits].x + sinf(g_Combo.rot.z + (D3DX_PI - g_Combo.fAngele)) *  g_Combo.fLength;
		pVtx[1].pos.y = g_Combo.pos[nCountDigits].y + cosf(g_Combo.rot.z + (D3DX_PI - g_Combo.fAngele)) *  g_Combo.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Combo.pos[nCountDigits].x + sinf(g_Combo.rot.z - (0 + g_Combo.fAngele)) * g_Combo.fLength;
		pVtx[2].pos.y = g_Combo.pos[nCountDigits].y + cosf(g_Combo.rot.z - (0 + g_Combo.fAngele)) * g_Combo.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Combo.pos[nCountDigits].x + sinf(g_Combo.rot.z - (0 - g_Combo.fAngele)) *  g_Combo.fLength;
		pVtx[3].pos.y = g_Combo.pos[nCountDigits].y + cosf(g_Combo.rot.z - (0 - g_Combo.fAngele)) *  g_Combo.fLength;
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
		pVtx[0].tex = D3DXVECTOR2(0.0f + (g_nCombo * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (g_nCombo * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (g_nCombo * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (g_nCombo * 0.1f), 1.0f);

		pVtx += 4;		// ���_�f�[�^�̃|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffCombo->Unlock();
}

//********************************************************************************
// �R���{�̏I������
//********************************************************************************
void UninitCombo(void)
{
	// �e�N�X�`���̔j��	  
	if (g_pTextureCombo != NULL)
	{
		g_pTextureCombo->Release();

		g_pTextureCombo = NULL;
	}

	// ���_�o�b�t�@��j��
	if (g_pVtxBuffCombo != NULL)
	{
		g_pVtxBuffCombo->Release();

		g_pVtxBuffCombo = NULL;
	}
}

//********************************************************************************
// �R���{�̍X�V����
//********************************************************************************
void UpdateCombo(void)
{
	
}

//********************************************************************************
// �R���{�̕`�揈��
//********************************************************************************
void DrawCombo(void)
{
	if (g_Combo.bUse == true)
	{// �g�p���Ă�
		// �ϐ��錾
		int nCountDigits;		// �������J�E���g����

		// �f�o�C�X�ւ̃|�C���^
		LPDIRECT3DDEVICE9 pDevice;

		// �f�o�C�X�̎擾
		pDevice = GetDevice();

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffCombo, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// ���e�X�g���g�p����
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

		// ���e�X�g�̐ݒ�
		pDevice->SetRenderState(D3DRS_ALPHAREF, 50);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		for (nCountDigits = 0; nCountDigits < MAX_COMBO_DIGITS; nCountDigits++)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureCombo);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCountDigits * 4,
				2);
		}

		// ���e�X�g�̏I��
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}

//********************************************************************************
// �R���{�̐ݒ菈��
//********************************************************************************
void SetCombo(int nCombo, D3DXVECTOR3 pos, D3DXVECTOR3 offset)
{
	if (g_Combo.bUse == false)
	{// �g�p���ĂȂ�
		// �ϐ��錾
		int aPosTexU[MAX_COMBO_DIGITS];		// �e���̐��l���i�[
		int nCountDigits;					// �������J�E���g����

		// �ϐ��Ɉ�������
		g_Combo.offset = offset;
		g_nCombo = nCombo;
		g_Combo.bUse = true;

		// ���l�̕����Ɗi�[
		aPosTexU[0] = g_nCombo % 1000 / 100;
		aPosTexU[1] = g_nCombo % 100 / 10;
		aPosTexU[2] = g_nCombo % 10 / 1;

		// ���_���ւ̃|�C���^�𐶐�
		VERTEX_2D *pVtx;

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffCombo->Lock(0, 0, (void**)&pVtx, 0);

		// �R���{�̈ʒu�̐ݒ�
		for (nCountDigits = 0; nCountDigits < MAX_COMBO_DIGITS; nCountDigits++)
		{
			g_Combo.pos[nCountDigits] = D3DXVECTOR3(pos.x - (g_Combo.offset.x + (g_Combo.offset.x * 2) * nCountDigits), pos.y + g_Combo.offset.y, 0.0f);
		}

		// �Ίp���̒������Z�o����
		g_Combo.fLength = sqrtf(((g_Combo.offset.x * g_Combo.offset.x) + (g_Combo.offset.y * g_Combo.offset.y)) / 2.0f);

		// �Ίp���̊p�x���Z�o
		g_Combo.fAngele = atan2f(g_Combo.offset.x, g_Combo.offset.y);

		for (nCountDigits = 0; nCountDigits < MAX_COMBO_DIGITS; nCountDigits++)
		{
			// ���_���W�̐ݒ�
			pVtx[0].pos.x = g_Combo.pos[nCountDigits].x + sinf(g_Combo.rot.z + (D3DX_PI + g_Combo.fAngele)) * g_Combo.fLength;
			pVtx[0].pos.y = g_Combo.pos[nCountDigits].y + cosf(g_Combo.rot.z + (D3DX_PI + g_Combo.fAngele)) * g_Combo.fLength;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_Combo.pos[nCountDigits].x + sinf(g_Combo.rot.z + (D3DX_PI - g_Combo.fAngele)) *  g_Combo.fLength;
			pVtx[1].pos.y = g_Combo.pos[nCountDigits].y + cosf(g_Combo.rot.z + (D3DX_PI - g_Combo.fAngele)) *  g_Combo.fLength;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_Combo.pos[nCountDigits].x + sinf(g_Combo.rot.z - (0 + g_Combo.fAngele)) * g_Combo.fLength;
			pVtx[2].pos.y = g_Combo.pos[nCountDigits].y + cosf(g_Combo.rot.z - (0 + g_Combo.fAngele)) * g_Combo.fLength;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_Combo.pos[nCountDigits].x + sinf(g_Combo.rot.z - (0 - g_Combo.fAngele)) *  g_Combo.fLength;
			pVtx[3].pos.y = g_Combo.pos[nCountDigits].y + cosf(g_Combo.rot.z - (0 - g_Combo.fAngele)) *  g_Combo.fLength;
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
			pVtx[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[(MAX_COMBO_DIGITS - 1) - nCountDigits] * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (aPosTexU[(MAX_COMBO_DIGITS - 1) - nCountDigits] * 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[(MAX_COMBO_DIGITS - 1) - nCountDigits] * 0.1f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (aPosTexU[(MAX_COMBO_DIGITS - 1) - nCountDigits] * 0.1f), 1.0f);

			pVtx += 4;			// ���_�f�[�^�̃|�C���^��4���i�߂�
		}

		// ���_�o�b�t�@���A�����b�N
		g_pVtxBuffCombo->Unlock();
	}
}

//********************************************************************************
// �R���{�̌v�Z�Z����
//********************************************************************************
void AddCombo(int nCombo)
{
	// �ϐ��錾
	int aPosTexU[MAX_COMBO_DIGITS];		// �e���̐��l���i�[
	int nCountDigits;					// �������J�E���g����
	g_nCombo = nCombo;					// �R���{���̑��
	
	if (g_nCombo < 2)
	{// 0�ȉ��̎�
		g_Combo.bUse = false;
	}

	if (g_Combo.bUse == true)
	{// �g�p���Ă�
		// ���l�̕����Ɗi�[
		aPosTexU[0] = g_nCombo % 1000 / 100;
		aPosTexU[1] = g_nCombo % 100 / 10;
		aPosTexU[2] = g_nCombo % 10 / 1;

		// ���_���ւ̃|�C���^�𐶐�
		VERTEX_2D *pVtx;

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffCombo->Lock(0, 0, (void**)&pVtx, 0);

		// �Ίp���̒������Z�o����
		g_Combo.fLength = sqrtf(((g_Combo.offset.x * g_Combo.offset.x) + (g_Combo.offset.y * g_Combo.offset.y)) / 2.0f);

		// �Ίp���̊p�x���Z�o
		g_Combo.fAngele = atan2f(g_Combo.offset.x, g_Combo.offset.y);

		for (nCountDigits = 0; nCountDigits < MAX_COMBO_DIGITS; nCountDigits++)
		{
			// ���_���W�̐ݒ�
			pVtx[0].pos.x = g_Combo.pos[nCountDigits].x + sinf(g_Combo.rot.z + (D3DX_PI + g_Combo.fAngele)) * g_Combo.fLength;
			pVtx[0].pos.y = g_Combo.pos[nCountDigits].y + cosf(g_Combo.rot.z + (D3DX_PI + g_Combo.fAngele)) * g_Combo.fLength;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_Combo.pos[nCountDigits].x + sinf(g_Combo.rot.z + (D3DX_PI - g_Combo.fAngele)) *  g_Combo.fLength;
			pVtx[1].pos.y = g_Combo.pos[nCountDigits].y + cosf(g_Combo.rot.z + (D3DX_PI - g_Combo.fAngele)) *  g_Combo.fLength;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_Combo.pos[nCountDigits].x + sinf(g_Combo.rot.z - (0 + g_Combo.fAngele)) * g_Combo.fLength;
			pVtx[2].pos.y = g_Combo.pos[nCountDigits].y + cosf(g_Combo.rot.z - (0 + g_Combo.fAngele)) * g_Combo.fLength;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_Combo.pos[nCountDigits].x + sinf(g_Combo.rot.z - (0 - g_Combo.fAngele)) *  g_Combo.fLength;
			pVtx[3].pos.y = g_Combo.pos[nCountDigits].y + cosf(g_Combo.rot.z - (0 - g_Combo.fAngele)) *  g_Combo.fLength;
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
			pVtx[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[(MAX_COMBO_DIGITS - 1) - nCountDigits] * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (aPosTexU[(MAX_COMBO_DIGITS - 1) - nCountDigits] * 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[(MAX_COMBO_DIGITS - 1) - nCountDigits] * 0.1f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (aPosTexU[(MAX_COMBO_DIGITS - 1) - nCountDigits] * 0.1f), 1.0f);

			pVtx += 4;		// ���_�f�[�^�̃|�C���^��4���i�߂�
		}

		// ���_�o�b�t�@���A�����b�N
		g_pVtxBuffCombo->Unlock();
	}
}

//********************************************************************************
// �R���{�̏��̎擾
//********************************************************************************
int GetCombo(void)
{
	return g_nCombo;
}