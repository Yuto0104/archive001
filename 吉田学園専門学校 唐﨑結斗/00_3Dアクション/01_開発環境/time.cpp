//**************************************************************************************************
//
// ���Ԃ̏���
// Auther�F�������l
//
//**************************************************************************************************

#include"main.h"
//#include"sound.h"

#include"time.h"
#include"player.h"
#include"score.h"
#include"fade.h"

//*************************************************************
// �O���[�o���ϐ�
//*************************************************************
static LPDIRECT3DTEXTURE9			g_pTextureTime = NULL;			// �e�N�X�`���ւ̃|�C���^
static LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffTime = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
static Time							g_Time;							// ���ԏ��

//---------------------------------------------------------------------------
// ���Ԃ̏���������
//---------------------------------------------------------------------------
void InitTime(void)
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
		&g_pTextureTime);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * MAX_VERTEX * MAX_TIME_DIGITS * MAX_TIME_SEPARATION,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,																					// ���_�t�@�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	// ���l�̏�����
	g_Time.size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���S�_����̍�
	g_Time.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����
	g_Time.nTime = 0;
	g_Time.nMinutes = 0;
	g_Time.nSeconds = 0;
	g_Time.nMillisecond = 0;	

	// ���Ԃ̈ʒu�̏�����
	for (nCountDigits = 0; nCountDigits < MAX_TIME_DIGITS * MAX_TIME_SEPARATION; nCountDigits++)
	{
		g_Time.pos[nCountDigits] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// ���_���ւ̃|�C���^�𐶐�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	// �Ίp���̒������Z�o����
	g_Time.fLength = sqrtf(((g_Time.size.x * g_Time.size.x) + (g_Time.size.y * g_Time.size.y)) / 2.0f);

	// �Ίp���̊p�x���Z�o
	g_Time.fAngele = atan2f(g_Time.size.x, g_Time.size.y);

	for (nCountDigits = 0; nCountDigits < MAX_TIME_DIGITS * MAX_TIME_SEPARATION; nCountDigits++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos.x = g_Time.pos[nCountDigits].x + sinf(g_Time.rot.z + (D3DX_PI + g_Time.fAngele)) * g_Time.fLength;
		pVtx[0].pos.y = g_Time.pos[nCountDigits].y + cosf(g_Time.rot.z + (D3DX_PI + g_Time.fAngele)) * g_Time.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Time.pos[nCountDigits].x + sinf(g_Time.rot.z + (D3DX_PI - g_Time.fAngele)) *  g_Time.fLength;
		pVtx[1].pos.y = g_Time.pos[nCountDigits].y + cosf(g_Time.rot.z + (D3DX_PI - g_Time.fAngele)) *  g_Time.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Time.pos[nCountDigits].x + sinf(g_Time.rot.z - (0 + g_Time.fAngele)) * g_Time.fLength;
		pVtx[2].pos.y = g_Time.pos[nCountDigits].y + cosf(g_Time.rot.z - (0 + g_Time.fAngele)) * g_Time.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Time.pos[nCountDigits].x + sinf(g_Time.rot.z - (0 - g_Time.fAngele)) *  g_Time.fLength;
		pVtx[3].pos.y = g_Time.pos[nCountDigits].y + cosf(g_Time.rot.z - (0 - g_Time.fAngele)) *  g_Time.fLength;
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
		float fDivision = 1.0f / 10.0f;
		pVtx[0].tex = D3DXVECTOR2(0.0f + (g_Time.nTime * fDivision), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(fDivision + (g_Time.nTime * fDivision), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (g_Time.nTime * fDivision), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(fDivision + (g_Time.nTime * fDivision), 1.0f);

		pVtx += 4;		// ���_�f�[�^�̃|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffTime->Unlock();
}

//---------------------------------------------------------------------------
// ���Ԃ̏I������
//---------------------------------------------------------------------------
void UninitTime(void)
{
	// �e�N�X�`���̔j��	  
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();

		g_pTextureTime = NULL;
	}

	// ���_�o�b�t�@��j��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();

		g_pVtxBuffTime = NULL;
	}
}

//---------------------------------------------------------------------------
// ���Ԃ̍X�V����
//---------------------------------------------------------------------------
void UpdateTime(void)
{
	// ���Ԃ̍X�V
	SubTime();

	if (g_Time.nTime == 0 && g_Time.nMillisecond == 0)
	{
		//�t�F�[�h���̎擾
		FADE fade;			//�t�F�[�h���ւ̃|�C���^
		fade = GetFade();

		//�v���C���[���̎擾
		Player *pPlayer;
		pPlayer = GetPlayer();

		if (pPlayer->nMaxCombo < pPlayer->nCntCombo)
		{
			pPlayer->nMaxCombo = pPlayer->nCntCombo;
		}

		if (fade == FADE_NONE)
		{//�t�F�[�h���s���ĂȂ��Ƃ�
			//���U���g��ʂֈړ�
			SetFade(MODE_RESULT);
		}
	}
	
}

//---------------------------------------------------------------------------
// ���Ԃ̕`�揈��
//---------------------------------------------------------------------------
void DrawTime(void)
{
	// �ϐ��錾
	int nCountDigits;		// �������J�E���g����

	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0,sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCountDigits = 0; nCountDigits < MAX_TIME_DIGITS * MAX_TIME_SEPARATION; nCountDigits++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTime);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCountDigits * 4,
			2);
	}
}

//---------------------------------------------------------------------------
// ���Ԃ̐ݒ菈��
//---------------------------------------------------------------------------
void SetTime(int nTime, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �ϐ��錾
	int aPosTexU[MAX_TIME_DIGITS];		// �e���̐��l���i�[
	int nCountDigits;					// �������J�E���g����

	// �ϐ��Ɉ�������
	g_Time.size = size;
	g_Time.nTime = nTime;

	// ���̎Z�o
	g_Time.nMinutes = g_Time.nTime / 60;

	if (g_Time.nTime >= 60)
	{// ���Ԃ�60�𒴂����Ƃ�
		g_Time.nSeconds = g_Time.nTime - (60 * g_Time.nMinutes);
	}
	else
	{// 60�ȊO�̎�
		g_Time.nSeconds = g_Time.nTime;
	}
	
	// �~���b��0����
	g_Time.nMillisecond = 0;

	// ���_���ւ̃|�C���^�𐶐�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTime = 0; nCntTime < MAX_TIME_SEPARATION; nCntTime++)
	{
		// �ϐ��錾
		int nNumTime;

		if (nCntTime == 0)
		{// ������
			nNumTime = g_Time.nMinutes;
		}
		else if (nCntTime == 1)
		{// �b�̑��
			nNumTime = g_Time.nSeconds;
		}
		else
		{// �~���b�̑��
			nNumTime = g_Time.nMillisecond;
		}

		// ���l�̕����Ɗi�[
		aPosTexU[0] = nNumTime % 100 / 10;
		aPosTexU[1] = nNumTime % 10 / 1;

		// ���Ԃ̈ʒu�̐ݒ�
		for (nCountDigits = nCntTime * MAX_TIME_DIGITS; nCountDigits < MAX_TIME_DIGITS + nCntTime * MAX_TIME_DIGITS; nCountDigits++)
		{
			g_Time.pos[nCountDigits] = D3DXVECTOR3(pos.x + (g_Time.size.x * nCntTime) + (g_Time.size.x + (g_Time.size.x * 2) * nCountDigits), pos.y + g_Time.size.y, 0.0f);
		}

		// �Ίp���̒������Z�o����
		g_Time.fLength = sqrtf(((g_Time.size.x * g_Time.size.x) + (g_Time.size.y * g_Time.size.y)) / 2.0f);

		// �Ίp���̊p�x���Z�o
		g_Time.fAngele = atan2f(g_Time.size.x, g_Time.size.y);

		for (nCountDigits = nCntTime * MAX_TIME_DIGITS; nCountDigits < MAX_TIME_DIGITS + nCntTime * MAX_TIME_DIGITS; nCountDigits++)
		{
			// ���_���W�̐ݒ�
			pVtx[0].pos.x = g_Time.pos[nCountDigits].x + sinf(g_Time.rot.z + (D3DX_PI + g_Time.fAngele)) * g_Time.fLength;
			pVtx[0].pos.y = g_Time.pos[nCountDigits].y + cosf(g_Time.rot.z + (D3DX_PI + g_Time.fAngele)) * g_Time.fLength;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_Time.pos[nCountDigits].x + sinf(g_Time.rot.z + (D3DX_PI - g_Time.fAngele)) *  g_Time.fLength;
			pVtx[1].pos.y = g_Time.pos[nCountDigits].y + cosf(g_Time.rot.z + (D3DX_PI - g_Time.fAngele)) *  g_Time.fLength;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_Time.pos[nCountDigits].x + sinf(g_Time.rot.z - (0 + g_Time.fAngele)) * g_Time.fLength;
			pVtx[2].pos.y = g_Time.pos[nCountDigits].y + cosf(g_Time.rot.z - (0 + g_Time.fAngele)) * g_Time.fLength;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_Time.pos[nCountDigits].x + sinf(g_Time.rot.z - (0 - g_Time.fAngele)) *  g_Time.fLength;
			pVtx[3].pos.y = g_Time.pos[nCountDigits].y + cosf(g_Time.rot.z - (0 - g_Time.fAngele)) *  g_Time.fLength;
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

			int nNumTex = (nCountDigits - (nCntTime * MAX_TIME_DIGITS));

			// �e�N�X�`�����W
			float fDivision = 1.0f / 10.0f;
			pVtx[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[nNumTex] * fDivision), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(fDivision + (aPosTexU[nNumTex] * fDivision), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[nNumTex] * fDivision), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(fDivision + (aPosTexU[nNumTex] * fDivision), 1.0f);

			pVtx += 4;			// ���_�f�[�^�̃|�C���^��4���i�߂�
		}
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffTime->Unlock();
}

//---------------------------------------------------------------------------
// ���Ԃ̌��Z����
//---------------------------------------------------------------------------
void SubTime(void)
{
	// �ϐ��錾
	int aPosTexU[MAX_TIME_DIGITS];		// �e���̐��l���i�[
	int nCountDigits;					// �������J�E���g����

	g_Time.nTime = (g_Time.nMinutes * 60) + g_Time.nSeconds;

	if (g_Time.nTime >= 0)
	{
		g_Time.nMillisecond--;

		if (g_Time.nMillisecond < 0)
		{
			g_Time.nMillisecond = 59;
			g_Time.nTime--;

			if (g_Time.nTime <= 0)
			{
				g_Time.nTime = 0;
				g_Time.nMillisecond = 0;
			}
		}
	}
	
	g_Time.nMinutes = g_Time.nTime / 60;

	if (g_Time.nTime >= 60)
	{
		g_Time.nSeconds = g_Time.nTime - (60 * g_Time.nMinutes);
	}
	else
	{
		g_Time.nSeconds = g_Time.nTime;
	}

	// ���_���ւ̃|�C���^�𐶐�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTime = 0; nCntTime < MAX_TIME_SEPARATION; nCntTime++)
	{
		int nNumTime;

		if (nCntTime == 0)
		{
			nNumTime = g_Time.nMinutes;
		}
		else if (nCntTime == 1)
		{
			nNumTime = g_Time.nSeconds;
		}
		else
		{
			nNumTime = g_Time.nMillisecond;
		}

		// ���l�̕����Ɗi�[
		aPosTexU[0] = nNumTime % 100 / 10;
		aPosTexU[1] = nNumTime % 10 / 1;

		// �Ίp���̒������Z�o����
		g_Time.fLength = sqrtf(((g_Time.size.x * g_Time.size.x) + (g_Time.size.y * g_Time.size.y)) / 2.0f);

		// �Ίp���̊p�x���Z�o
		g_Time.fAngele = atan2f(g_Time.size.x, g_Time.size.y);

		for (nCountDigits = nCntTime * MAX_TIME_DIGITS; nCountDigits < MAX_TIME_DIGITS + nCntTime * MAX_TIME_DIGITS; nCountDigits++)
		{
			// ���_���W�̐ݒ�
			pVtx[0].pos.x = g_Time.pos[nCountDigits].x + sinf(g_Time.rot.z + (D3DX_PI + g_Time.fAngele)) * g_Time.fLength;
			pVtx[0].pos.y = g_Time.pos[nCountDigits].y + cosf(g_Time.rot.z + (D3DX_PI + g_Time.fAngele)) * g_Time.fLength;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_Time.pos[nCountDigits].x + sinf(g_Time.rot.z + (D3DX_PI - g_Time.fAngele)) *  g_Time.fLength;
			pVtx[1].pos.y = g_Time.pos[nCountDigits].y + cosf(g_Time.rot.z + (D3DX_PI - g_Time.fAngele)) *  g_Time.fLength;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_Time.pos[nCountDigits].x + sinf(g_Time.rot.z - (0 + g_Time.fAngele)) * g_Time.fLength;
			pVtx[2].pos.y = g_Time.pos[nCountDigits].y + cosf(g_Time.rot.z - (0 + g_Time.fAngele)) * g_Time.fLength;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_Time.pos[nCountDigits].x + sinf(g_Time.rot.z - (0 - g_Time.fAngele)) *  g_Time.fLength;
			pVtx[3].pos.y = g_Time.pos[nCountDigits].y + cosf(g_Time.rot.z - (0 - g_Time.fAngele)) *  g_Time.fLength;
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

			int nNumTex = (nCountDigits - (nCntTime * MAX_TIME_DIGITS));

			// �e�N�X�`�����W
			float fDivision = 1.0f / 10.0f;
			pVtx[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[nNumTex] * fDivision), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(fDivision + (aPosTexU[nNumTex] * fDivision), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[nNumTex] * fDivision), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(fDivision + (aPosTexU[nNumTex] * fDivision), 1.0f);

			pVtx += 4;		// ���_�f�[�^�̃|�C���^��4���i�߂�
		}
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffTime->Unlock();
}

//---------------------------------------------------------------------------
// ���Ԃ̏��̎擾
//---------------------------------------------------------------------------
int GetTime(void)
{
	return g_Time.nTime;
}