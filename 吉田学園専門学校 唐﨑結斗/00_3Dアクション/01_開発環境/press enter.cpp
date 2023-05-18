//**************************************************************************************************
//
// �v���X�G���^�[�̐ݒ菈��
// Auther�F�������l
//
//**************************************************************************************************
#include"main.h"
#include"press enter.h"
#include"input.h"
#include"fade.h"
#include"sound.h"
#include"calculation.h"

//*******************************************************************************
// �}�N����`
//*******************************************************************************
#define		MAX_ANIMPATTEN_PRESS_ENTER			(2)		// �A�j���[�V�����p�^�[���̍ő�l 

//*******************************************************************************
// �O���[�o���ϐ�
//*******************************************************************************
static LPDIRECT3DTEXTURE9		g_pTexturePressEnter = NULL;		//�e�N�X�`���ւ̃|�C���^
static LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPressEnter = NULL;		//���_�o�b�t�@�ւ̃|�C���^
static PressEnter				g_PE;								//�v���X�G���^�[�̏��
static float					g_nMaxAnimU;						// �e�N�X�`����X���̍ő�l 

//********************************************************************************
// �v���X�G���^�[�̏���������
//********************************************************************************
void InitPressEnter(void)
{
	// �O���[�o���ϐ��̐ݒ�
	g_nMaxAnimU = 1.0f / MAX_ANIMPATTEN_PRESS_ENTER;

	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �|���S���ɒ���t����e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/press_enter.png",
		&g_pTexturePressEnter);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// ���_�t�@�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffPressEnter,
		NULL);

	// �^�C�g�����S���̏�����
	g_PE.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���S�_
	g_PE.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���S�_����̍�
	g_PE.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����
	g_PE.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);		// �J���[
	g_PE.state = PRESSENTERSTATE_NORMAL;				// �ʏ���
	g_PE.nCountState = 0;								// ��ԃJ�E���^�[
	g_PE.nCountFlashing = 0;							// �_�ŉ񐔂̃J�E���^�[
	g_PE.nDecision = 0;									// �_�ŏ�Ԏ��̔���
	g_PE.bUse = false;									// �g�p���ĂȂ�
														
	//���_���ւ̃|�C���^�𐶐�						
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPressEnter->Lock(0, 0, (void**)&pVtx, 0);

	// �Ίp���̒������Z�o����
	g_PE.fLength = sqrtf(((g_PE.offset.x * g_PE.offset.x) + (g_PE.offset.y * g_PE.offset.y)) / 2.0f);

	// �Ίp���̊p�x���Z�o
	g_PE.fAngele = atan2f(g_PE.offset.x, g_PE.offset.y);

	// ���_���W�̐ݒ�
	pVtx[0].pos.x = g_PE.pos.x + sinf(g_PE.rot.z + (D3DX_PI + g_PE.fAngele)) * g_PE.fLength;
	pVtx[0].pos.y = g_PE.pos.y + cosf(g_PE.rot.z + (D3DX_PI + g_PE.fAngele)) * g_PE.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_PE.pos.x + sinf(g_PE.rot.z + (D3DX_PI - g_PE.fAngele)) *  g_PE.fLength;
	pVtx[1].pos.y = g_PE.pos.y + cosf(g_PE.rot.z + (D3DX_PI - g_PE.fAngele)) *  g_PE.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_PE.pos.x + sinf(g_PE.rot.z - (0 + g_PE.fAngele)) * g_PE.fLength;
	pVtx[2].pos.y = g_PE.pos.y + cosf(g_PE.rot.z - (0 + g_PE.fAngele)) * g_PE.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_PE.pos.x + sinf(g_PE.rot.z - (0 - g_PE.fAngele)) *  g_PE.fLength;
	pVtx[3].pos.y = g_PE.pos.y + cosf(g_PE.rot.z - (0 - g_PE.fAngele)) *  g_PE.fLength;
	pVtx[3].pos.z = 0.0f;

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = g_PE.col;
	pVtx[1].col = g_PE.col;
	pVtx[2].col = g_PE.col;
	pVtx[3].col = g_PE.col;

	// �e�N�X�`�����W
	SetVtxTexture(pVtx, g_nMaxAnimU, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffPressEnter->Unlock();
}

//********************************************************************************
// �v���X�G���^�[�̏I������
//********************************************************************************
void UninitPressEnter(void)
{
	// �e�N�X�`���̔j��	  
	if (g_pTexturePressEnter != NULL)
	{
		g_pTexturePressEnter->Release();

		g_pTexturePressEnter = NULL;
	}

	// ���_�o�b�t�@��j��
	if (g_pVtxBuffPressEnter != NULL)
	{
		g_pVtxBuffPressEnter->Release();

		g_pVtxBuffPressEnter = NULL;
	}
}

//********************************************************************************
// �v���X�G���^�[�̍X�V����
//********************************************************************************
void UpdatePressEnter(void)
{
	// �ϐ��錾
	int nPage = 0;

	// ���_���ւ̃|�C���^�𐶐�						
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPressEnter->Lock(0, 0, (void**)&pVtx, 0);

	// �t�F�[�h���̎擾
	FADE fade;			// �t�F�[�h���ւ̃|�C���^
	fade = GetFade();

	if (g_PE.bUse == true)
	{// �v���X�G���^�[���g�p����Ă�

		if (g_PE.state != PRESSENTERSTATE_FLASHING)
		{// �_�ŏ�ԂłȂ��Ƃ�
			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{// [Enter]�L�[�������ꂽ
			 // �_�ŏ�Ԃɂ��e�l�̐ݒ�
				g_PE.state = PRESSENTERSTATE_FLASHING;
				g_PE.nCountState = FLASHING_COUNT_STATE_PE;
				g_PE.nDecision = 1;

				//�T�E���h�Đ�
				PlaySound(SOUND_LABEL_SE_DECIDE);
			}
		}

		switch (g_PE.state)
		{
		case PRESSENTERSTATE_NORMAL:
			g_PE.nCountState--;

			if (g_PE.nCountState == 0)
			{// ��ԃJ�E���^�[�̐ݒ�
				g_PE.nCountState = 0;

				// ��Ԃ̐ݒ�
				g_PE.state = PRESSENTERSTATE_TRANSPARENCY;

				// �����ɐݒ�
				g_PE.col.a = 0.0f;
			}
			break;

		case PRESSENTERSTATE_TRANSPARENCY:
			g_PE.nCountState++;

			if (g_PE.nCountState == MAX_COUNT_STATE_PE)
			{// ��ԃJ�E���^�[�̐ݒ�
				g_PE.nCountState = MAX_COUNT_STATE_PE;

				// ��Ԃ̐ݒ�
				g_PE.state = PRESSENTERSTATE_NORMAL;

				// �s�����ɐݒ�
				g_PE.col.a = 1.0f;
			}
			break;

		case PRESSENTERSTATE_FLASHING:
			if (g_PE.nCountFlashing != 0)
			{
				g_PE.nCountState--;

				if (g_PE.nCountState <= 0)
				{
					if (g_PE.nDecision == 1)
					{// �s�����ɐݒ�
						g_PE.col.a = 1.0f;

						g_PE.nDecision ^= 1;
						g_PE.nCountFlashing--;
						g_PE.nCountState = FLASHING_COUNT_STATE_PE;
					}
					else
					{// �����ɐݒ�
						g_PE.col.a = 0.0f;

						g_PE.nDecision ^= 1;
						g_PE.nCountFlashing--;
						g_PE.nCountState = FLASHING_COUNT_STATE_PE;
					}
				}
			}
			else
			{
				if (fade == FADE_NONE)
				{// �t�F�[�h���s���ĂȂ��Ƃ�

					MODE mode = GetMode();

					if (mode == MODE_TITLE)
					{// �t�F�[�h�ݒ菈��
						SetFade(MODE_TUTORIAL);
					}
					if (mode == MODE_TUTORIAL)
					{// �t�F�[�h�ݒ菈��
						SetFade(MODE_GAME);
					}
				}
			}
			break;
		}
	}

	// ���_�J���[�̐ݒ�
	pVtx[0].col = g_PE.col;
	pVtx[1].col = g_PE.col;
	pVtx[2].col = g_PE.col;
	pVtx[3].col = g_PE.col;

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f , 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f , 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f , 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f , 1.0f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffPressEnter->Unlock();
}

//********************************************************************************
// �v���X�G���^�[�̕`�揈��
//********************************************************************************
void DrawPressEnter(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPressEnter, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ���e�X�g���g�p����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// ���e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	if (g_PE.bUse == true)
	{// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePressEnter);

		// �|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	// ���e�X�g�̏I��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//********************************************************************************
// �v���X�G���^�[�̐ݒ菈��
//********************************************************************************
void SetPressEnter(D3DXVECTOR3 pos, D3DXVECTOR3 offset)
{
	// ���_���ւ̃|�C���^�𐶐�						
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPressEnter->Lock(0, 0, (void**)&pVtx, 0);

	if (g_PE.bUse == false)
	{// �g�p����ĂȂ��ꍇ
		// �^�C�g�����S���̐ݒ�
		g_PE.offset = offset;														// ���S�_����̍�
		g_PE.pos = pos;																// ���S�_
		g_PE.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									// ����
		g_PE.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);								// �J���[
		g_PE.state = PRESSENTERSTATE_TRANSPARENCY;									// �ʏ���
		g_PE.nCountState = 0;														// ��ԃJ�E���^�[
		g_PE.nCountFlashing = MAX_FLASHING;											// �_�ŉ񐔂̃J�E���^�[
		g_PE.bUse = true;															// �g�p���Ă�

		// �Ίp���̒������Z�o����
		g_PE.fLength = sqrtf(((g_PE.offset.x * g_PE.offset.x) + (g_PE.offset.y * g_PE.offset.y)) / 2.0f);

		// �Ίp���̊p�x���Z�o
		g_PE.fAngele = atan2f(g_PE.offset.x, g_PE.offset.y);

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = g_PE.pos.x + sinf(g_PE.rot.z + (D3DX_PI + g_PE.fAngele)) * g_PE.fLength;
		pVtx[0].pos.y = g_PE.pos.y + cosf(g_PE.rot.z + (D3DX_PI + g_PE.fAngele)) * g_PE.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_PE.pos.x + sinf(g_PE.rot.z + (D3DX_PI - g_PE.fAngele)) *  g_PE.fLength;
		pVtx[1].pos.y = g_PE.pos.y + cosf(g_PE.rot.z + (D3DX_PI - g_PE.fAngele)) *  g_PE.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_PE.pos.x + sinf(g_PE.rot.z - (0 + g_PE.fAngele)) * g_PE.fLength;
		pVtx[2].pos.y = g_PE.pos.y + cosf(g_PE.rot.z - (0 + g_PE.fAngele)) * g_PE.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_PE.pos.x + sinf(g_PE.rot.z - (0 - g_PE.fAngele)) *  g_PE.fLength;
		pVtx[3].pos.y = g_PE.pos.y + cosf(g_PE.rot.z - (0 - g_PE.fAngele)) *  g_PE.fLength;
		pVtx[3].pos.z = 0.0f;

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = g_PE.col;
		pVtx[1].col = g_PE.col;
		pVtx[2].col = g_PE.col;
		pVtx[3].col = g_PE.col;

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffPressEnter->Unlock();
}