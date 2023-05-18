//**************************************************************************************************
//
//�|�[�Y�����̐ݒ菈��
//Auther�F�������l
//
//**************************************************************************************************
#include"main.h"
#include"pause.h"
#include"input.h"
#include"sound.h"
#include"fade.h"
#include"pause bg.h"
#include"continue.h"
#include"retry.h"
#include"quit.h"

//********************************************************************************
//�O���[�o���ϐ�
//********************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Pause g_Pause;										//�|�[�Y���̎擾
D3DXCOLOR g_colorPause;								//�|���S���̐F

//********************************************************************************
//�|�[�Y�����̏���������
//********************************************************************************
void InitPause(void)
{
	//�|�[�Y���̏�����
	g_Pause.bDisp = false;					//�\�����Ȃ�
	g_Pause.state = NEXTPROCESS_CONTINUE;	//�Q�[�����(�p��)
	g_Pause.nCountKey = 0;					//�L�[�������ꂽ��

	//�|���S������(�s����)�ɂ��Ă���
	g_colorPause = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									//���_�t�@�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	//���_���ւ̃|�C���^�𐶐�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_colorPause;
	pVtx[1].col = g_colorPause;
	pVtx[2].col = g_colorPause;
	pVtx[3].col = g_colorPause;

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPause->Unlock();

	//�|�[�Y�w�i�̏���������
	InitPauseBG();

	//�R���e�B�j���[�̏���������
	InitContinue();

	//���g���C�̏���������
	InitRetry();

	//�N�C�b�g�̏���������
	InitQuit();
}

//********************************************************************************
//�|�[�Y�����̏I������
//********************************************************************************
void UninitPause(void)
{
	//���_�o�b�t�@��j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();

		g_pVtxBuffPause = NULL;
	}

	//�|�[�Y�w�i�̏I������
	UninitPauseBG();

	//�R���e�B�j���[�̏I������
	UninitContinue();

	//���g���C�̏I������
	UninitRetry();

	//�N�C�b�g�̏I������
	UninitQuit();
}

//********************************************************************************
//�|�[�Y�����̍X�V����
//********************************************************************************
void UpdatePause(void)
{
	//�t�F�[�h���̎擾
	FADE fade;			//�t�F�[�h���ւ̃|�C���^
	fade = GetFade();

	if (g_Pause.bDisp == true)
	{//�\������Ă�
		if (GetKeyboardTrigger(DIK_W) == true || GetJoypadTrigger(JOYKEY_UP) == true)
		{//[W]�L�[�������ꂽ
			g_Pause.nCountKey--;

			//�T�E���h�Đ�
			PlaySound(SOUND_LABEL_SE_SELECT);

			if (g_Pause.nCountKey < 0)
			{//0��菬�����ꍇ
				g_Pause.nCountKey = 2;
			}
		}
		if (GetKeyboardTrigger(DIK_S) == true || GetJoypadTrigger(JOYKEY_DOWN) == true)
		{//[S]�L�[�������ꂽ
			g_Pause.nCountKey++;

			//�T�E���h�Đ�
			PlaySound(SOUND_LABEL_SE_SELECT);

			if (g_Pause.nCountKey >= 3)
			{//3�ȏ�̏ꍇ
				g_Pause.nCountKey = 0;
			}
		}

		//���̏���
		switch (g_Pause.nCountKey)
		{
		case 0:
			g_Pause.state = NEXTPROCESS_CONTINUE;	//�Q�[�����(�p��)
			break;

		case 1:
			g_Pause.state = NEXTPROCESS_RETRY;		//�Q�[�����(�ŏ�����)
			break;

		case 2:
			g_Pause.state = NEXTPROCESS_QUIT;		//�^�C�g�����
			break;
		}

		if (GetKeyboardTrigger(DIK_C) == true)
		{//[C]�L�[�������ꂽ
			g_Pause.state = NEXTPROCESS_CONTINUE;	//�Q�[�����(�p��)

			//�T�E���h�Đ�
			PlaySound(SOUND_LABEL_SE_SELECT);
		}
		else if (GetKeyboardTrigger(DIK_R) == true)
		{//[R]�L�[�������ꂽ
			g_Pause.state = NEXTPROCESS_RETRY;		//�Q�[�����(�ŏ�����)

			//�T�E���h�Đ�
			PlaySound(SOUND_LABEL_SE_SELECT);
		}
		else if (GetKeyboardTrigger(DIK_Q) == true)
		{//[Q]�L�[�������ꂽ
			g_Pause.state = NEXTPROCESS_QUIT;		//�^�C�g�����

			//�T�E���h�Đ�
			PlaySound(SOUND_LABEL_SE_SELECT);
		}
		else if (GetKeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_START) == true)
		{//[P]�L�[�������ꂽ
			//�|�[�Y���̏�����
			g_Pause.state = NEXTPROCESS_CONTINUE;	//�Q�[�����(�p��)
			g_Pause.bDisp = false;					//�\�����Ȃ�
		}

		if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true)
		{//[Enter]�L�[�������ꂽ

			//���̏���
			switch (g_Pause.state)
			{
			case NEXTPROCESS_CONTINUE:

				//�|�[�Y���̏�����
				g_Pause.bDisp = false;					//�\�����Ȃ�
				g_Pause.state = NEXTPROCESS_CONTINUE;	//�Q�[�����(�p��)
				break;

			case NEXTPROCESS_RETRY:
				
				if (fade == FADE_NONE)
				{//�t�F�[�h���s���ĂȂ��Ƃ�
					//�t�F�[�h�ݒ菈��
					SetFade(MODE_GAME);
				}
				break;

			case NEXTPROCESS_QUIT:

				if (fade == FADE_NONE)
				{//�t�F�[�h���s���ĂȂ��Ƃ�
					//�t�F�[�h�ݒ菈��
					SetFade(MODE_TITLE);
				}
				break;
			}
		}

		//�|�[�Y�w�i�̍X�V����
		UpdatePauseBG();

		//�R���e�B�j���[�̍X�V����
		UpdateContinue();

		//���g���C�̍X�V����4
		UpdateRetry();

		//�N�C�b�g�̍X�V����
		UpdateQuit();
	}
}

//********************************************************************************
//�|�[�Y�����̕`�揈��
//********************************************************************************
void DrawPause(void)
{
	if (g_Pause.bDisp == true)
	{//�\������Ă�

		//�f�o�C�X�ւ̃|�C���^
		LPDIRECT3DDEVICE9 pDevice;

		//�f�o�C�X�̎擾
		pDevice = GetDevice();

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//�|�[�Y�w�i�̕`�揈��
		DrawPauseBG();

		//�R���e�B�j���[�̕`�揈��
		DrawContinue();

		//���g���C�̕`�揈��
		DrawRetry();

		//�N�C�b�g�̕`�揈��
		DrawQuit();
	}
}

//********************************************************************************
//�|�[�Y�����̐ݒ菈��
//********************************************************************************
void SetPause(void)
{
	if (g_Pause.bDisp == false)
	{//�\������Ă�
		//�|�[�Y���̐ݒ�
		g_Pause.bDisp = true;					//�\������
		g_Pause.state = NEXTPROCESS_CONTINUE;	//�Q�[�����(�p��)
		g_Pause.nCountKey = 0;					//�L�[�������ꂽ��

		//�|���S������(�s����)�ɂ��Ă���
		g_colorPause = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);

		//�f�o�C�X�ւ̃|�C���^
		LPDIRECT3DDEVICE9 pDevice;

		//�f�o�C�X�̎擾
		pDevice = GetDevice();

		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�T�C�Y
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,									//���_�t�@�[�}�b�g
			D3DPOOL_MANAGED,
			&g_pVtxBuffPause,
			NULL);

		//���_���ւ̃|�C���^�𐶐�
		VERTEX_2D *pVtx;

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDH, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDH, SCREEN_HEIGHT, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_colorPause;
		pVtx[1].col = g_colorPause;
		pVtx[2].col = g_colorPause;
		pVtx[3].col = g_colorPause;

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffPause->Unlock();

		//�|�[�Y�w�i�̐ݒ�
		SetPauseBG();

		//�R���e�B�j���[�̐ݒ�
		SetContinue();

		//���g���C�̐ݒ�
		SetRetry();

		//�N���C�G�b�g�̐ݒ�
		SetQuit();
	}
}

//********************************************************************************
//�|�[�Y���̎擾����
//********************************************************************************
Pause *GetPause(void)
{
	return &g_Pause;
}