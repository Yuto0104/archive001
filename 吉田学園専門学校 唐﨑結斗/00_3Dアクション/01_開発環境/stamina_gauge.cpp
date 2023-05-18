//**************************************************************************************************
//
//�_�f�Q�[�W�̐ݒ菈��
//Auther�F�������l
//
//**************************************************************************************************
#include"main.h"
#include"input.h"
#include"pause.h"
#include"fade.h"
#include"stamina_gauge.h"
#include"player.h"

//*******************************************************************************
// �O���[�o���ϐ�
//*******************************************************************************
//LPDIRECT3DTEXTURE9 g_pTextureStaminaGauge = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStaminaGauge = NULL;		//���_�o�b�t�@�ւ̃|�C���^
StaminaGauge g_StaminaGauge[MAX_STAMINA_GAUGE];				// �X�^�~�i�Q�[�W

//---------------------------------------------------------------------------
// �X�^�~�i�Q�[�W�̏���������
//---------------------------------------------------------------------------
void InitStaminaGauge(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	////�|���S���ɒ���t����e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	"data/TEXTURE/�_�f�{���x.png",
	//	&g_pTextureStaminaGauge);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_STAMINA_GAUGE,		// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,															// ���_�t�@�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffStaminaGauge,
		NULL);

	for (int nCnt = 0; nCnt < MAX_STAMINA_GAUGE; nCnt++)
	{
		// �X�^�~�i�Q�[�W���̏�����
		g_StaminaGauge[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);												// ���S�_
		g_StaminaGauge[nCnt].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);												// �傫��
		g_StaminaGauge[nCnt].maxSize = g_StaminaGauge[nCnt].size;												// �傫���̍ő�l
		D3DXVECTOR3 sizePos = D3DXVECTOR3(g_StaminaGauge[nCnt].size.x, 0.0f, 0.0f);								// �������̑傫��
		g_StaminaGauge[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);												// ����
		g_StaminaGauge[nCnt].type = TYPE_GAUGE;																	// �^�C�v
		g_StaminaGauge[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);											// �J���[
		g_StaminaGauge[nCnt].bUse = false;																		// �g�p���Ă�

		// ���_���ւ̃|�C���^�𐶐�						
		VERTEX_2D *pVtx;

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffStaminaGauge->Lock(0, 0, (void**)&pVtx, 0);

		// �Ίp���̒���[0]���Z�o����
		g_StaminaGauge[nCnt].fLength = sqrtf(((g_StaminaGauge[nCnt].size.x * g_StaminaGauge[nCnt].size.x) + (g_StaminaGauge[nCnt].size.y * g_StaminaGauge[nCnt].size.y)) / 2.0f);
		float fLengthPos = sqrtf(((sizePos.x * sizePos.x) + (sizePos.y * sizePos.y)) / 2.0f);

		// �Ίp���̊p�x[0]���Z�o
		g_StaminaGauge[nCnt].fAngele = atan2f(g_StaminaGauge[nCnt].size.x, g_StaminaGauge[nCnt].size.y);
		float fAngelePos = atan2f(sizePos.x, sizePos.y);

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = g_StaminaGauge[nCnt].pos.x + sinf(g_StaminaGauge[nCnt].rot.z + (D3DX_PI + g_StaminaGauge[nCnt].fAngele)) * g_StaminaGauge[nCnt].fLength;
		pVtx[0].pos.y = g_StaminaGauge[nCnt].pos.y + cosf(g_StaminaGauge[nCnt].rot.z + (D3DX_PI + g_StaminaGauge[nCnt].fAngele)) * g_StaminaGauge[nCnt].fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_StaminaGauge[nCnt].pos.x + sinf(g_StaminaGauge[nCnt].rot.z + (D3DX_PI - g_StaminaGauge[nCnt].fAngele)) *  g_StaminaGauge[nCnt].fLength;
		pVtx[1].pos.y = g_StaminaGauge[nCnt].pos.y + cosf(g_StaminaGauge[nCnt].rot.z + (D3DX_PI - g_StaminaGauge[nCnt].fAngele)) *  g_StaminaGauge[nCnt].fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_StaminaGauge[nCnt].pos.x + sinf(g_StaminaGauge[nCnt].rot.z - (0 + fAngelePos)) * fLengthPos;
		pVtx[2].pos.y = g_StaminaGauge[nCnt].pos.y + cosf(g_StaminaGauge[nCnt].rot.z - (0 + fAngelePos)) * fLengthPos;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_StaminaGauge[nCnt].pos.x + sinf(g_StaminaGauge[nCnt].rot.z - (0 - fAngelePos)) * fLengthPos;
		pVtx[3].pos.y = g_StaminaGauge[nCnt].pos.y + cosf(g_StaminaGauge[nCnt].rot.z - (0 - fAngelePos)) * fLengthPos;
		pVtx[3].pos.z = 0.0f;

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = g_StaminaGauge[nCnt].col;
		pVtx[1].col = g_StaminaGauge[nCnt].col;
		pVtx[2].col = g_StaminaGauge[nCnt].col;
		pVtx[3].col = g_StaminaGauge[nCnt].col;

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffStaminaGauge->Unlock();
}

//---------------------------------------------------------------------------
// �X�^�~�i�Q�[�W�̏I������
//---------------------------------------------------------------------------
void UninitStaminaGauge(void)
{
	//// �e�N�X�`���̔j��	  
	//if (g_pTextureStaminaGauge != NULL)
	//{
	//	g_pTextureStaminaGauge->Release();

	//	g_pTextureStaminaGauge = NULL;
	//}

	// ���_�o�b�t�@��j��
	if (g_pVtxBuffStaminaGauge != NULL)
	{
		g_pVtxBuffStaminaGauge->Release();

		g_pVtxBuffStaminaGauge = NULL;
	}
}

//---------------------------------------------------------------------------
// �X�^�~�i�Q�[�W�̍X�V����
//---------------------------------------------------------------------------
void UpdateStaminaGauge(void)
{
	for (int nCnt = 0; nCnt < MAX_STAMINA_GAUGE; nCnt++)
	{
		if (g_StaminaGauge[nCnt].bUse)
		{
			SubStaminaGauge(nCnt);
		}
	}
}

//---------------------------------------------------------------------------
// �X�^�~�i�Q�[�W�̕`�揈��
//---------------------------------------------------------------------------
void DrawStaminaGauge(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffStaminaGauge, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_STAMINA_GAUGE; nCnt++)
	{
		if (g_StaminaGauge[nCnt].bUse)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			// �|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 
				nCnt * 4,
				2);
		}
	}
}

//---------------------------------------------------------------------------
// �X�^�~�i�Q�[�W�̐ݒ菈��
//---------------------------------------------------------------------------
void SetStaminaGauge(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nType)
{
	for (int nCntType = 0; nCntType < MAX_STAMINA_GAUGE; nCntType++)
	{
		if (g_StaminaGauge[nCntType].bUse == false)
		{
			// �X�^�~�i�Q�[�W���̏�����
			g_StaminaGauge[nCntType].pos = pos;																			// ���S�_
			g_StaminaGauge[nCntType].size = D3DXVECTOR3(size.x, size.y * 2.0f, size.z);									// �傫��
			g_StaminaGauge[nCntType].maxSize = g_StaminaGauge[nCntType].size;											// �傫���̍ő�l
			g_StaminaGauge[nCntType].type = (STAMINA_GAUGE_TYPE)(nType);												// �^�C�v
			D3DXVECTOR3 sizePos = D3DXVECTOR3(g_StaminaGauge[nCntType].size.x, 0.0f, 0.0f);								// �������̑傫��
			g_StaminaGauge[nCntType].rot = rot;																			// ����
			g_StaminaGauge[nCntType].bUse = true;																		// �g�p���Ă�

			switch (g_StaminaGauge[nCntType].type)
			{
			case TYPE_GAUGE:
				g_StaminaGauge[nCntType].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);					// �J���[
				break;

			case TYPE_BG:
				g_StaminaGauge[nCntType].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);					// �J���[
				break;
			}
			

			//���_���ւ̃|�C���^�𐶐�						
			VERTEX_2D *pVtx;

			// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffStaminaGauge->Lock(0, 0, (void**)&pVtx, 0);

			// �Ίp���̒������Z�o����
			g_StaminaGauge[nCntType].fLength = sqrtf(((g_StaminaGauge[nCntType].size.x * g_StaminaGauge[nCntType].size.x) + (g_StaminaGauge[nCntType].size.y * g_StaminaGauge[nCntType].size.y)) / 2.0f);
			float fLengthPos = sqrtf(((sizePos.x * sizePos.x) + (sizePos.y * sizePos.y)) / 2.0f);

			// �Ίp���̊p�x���Z�o
			g_StaminaGauge[nCntType].fAngele = atan2f(g_StaminaGauge[nCntType].size.x, g_StaminaGauge[nCntType].size.y);
			float fAngelePos = atan2f(sizePos.x, sizePos.y);

			// ���_���W�̐ݒ�
			pVtx[0].pos.x = g_StaminaGauge[nCntType].pos.x + sinf(g_StaminaGauge[nCntType].rot.z + (D3DX_PI + g_StaminaGauge[nCntType].fAngele)) * g_StaminaGauge[nCntType].fLength;
			pVtx[0].pos.y = g_StaminaGauge[nCntType].pos.y + cosf(g_StaminaGauge[nCntType].rot.z + (D3DX_PI + g_StaminaGauge[nCntType].fAngele)) * g_StaminaGauge[nCntType].fLength;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_StaminaGauge[nCntType].pos.x + sinf(g_StaminaGauge[nCntType].rot.z + (D3DX_PI - g_StaminaGauge[nCntType].fAngele)) *  g_StaminaGauge[nCntType].fLength;
			pVtx[1].pos.y = g_StaminaGauge[nCntType].pos.y + cosf(g_StaminaGauge[nCntType].rot.z + (D3DX_PI - g_StaminaGauge[nCntType].fAngele)) *  g_StaminaGauge[nCntType].fLength;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_StaminaGauge[nCntType].pos.x + sinf(g_StaminaGauge[nCntType].rot.z - (0 + fAngelePos)) * fLengthPos;
			pVtx[2].pos.y = g_StaminaGauge[nCntType].pos.y + cosf(g_StaminaGauge[nCntType].rot.z - (0 + fAngelePos)) * fLengthPos;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_StaminaGauge[nCntType].pos.x + sinf(g_StaminaGauge[nCntType].rot.z - (0 - fAngelePos)) * fLengthPos;
			pVtx[3].pos.y = g_StaminaGauge[nCntType].pos.y + cosf(g_StaminaGauge[nCntType].rot.z - (0 - fAngelePos)) * fLengthPos;
			pVtx[3].pos.z = 0.0f;

			// rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_StaminaGauge[nCntType].col;
			pVtx[1].col = g_StaminaGauge[nCntType].col;
			pVtx[2].col = g_StaminaGauge[nCntType].col;
			pVtx[3].col = g_StaminaGauge[nCntType].col;

			// �e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			// ���_�o�b�t�@���A�����b�N
			g_pVtxBuffStaminaGauge->Unlock();

			break;
		}
	}
}

//---------------------------------------------------------------------------
// �X�^�~�i�Q�[�W�̌�������
//---------------------------------------------------------------------------
void SubStaminaGauge(int nCnt)
{
	if (g_StaminaGauge[nCnt].bUse)
	{
		//�v���C���[���̎擾
		Player *pPlayer = GetPlayer();

		switch (g_StaminaGauge[nCnt].type)
		{
		case TYPE_GAUGE:
			// �傫���ɐ��l����
			g_StaminaGauge[nCnt].size.y = (g_StaminaGauge[nCnt].maxSize.y / (float)(pPlayer->nMaxStamina)) * (float)(pPlayer->nStamina);

			if (pPlayer->nStamina <= pPlayer->nMaxStamina)
			{// �X�^�~�i�������ȉ��̎�
				g_StaminaGauge[nCnt].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);			// �J���[
				if (pPlayer->nStamina <= pPlayer->nMaxStamina / 2)
				{// �X�^�~�i�������ȉ��̎�
					g_StaminaGauge[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);			// �J���[

					if (pPlayer->nStamina <= DASH_STAMINA)
					{// �X�^�~�i���_�b�V������ʈȉ�
						g_StaminaGauge[nCnt].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);			// �J���[
					}
				}
			}
			break;

		case TYPE_BG:
			break;
		}

		// �������̑傫��
		D3DXVECTOR3 sizePos = D3DXVECTOR3(g_StaminaGauge[nCnt].size.x, 0.0f, 0.0f);

		//���_���ւ̃|�C���^�𐶐�						
		VERTEX_2D *pVtx;

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffStaminaGauge->Lock(0, 0, (void**)&pVtx, 0);

		// �Ίp���̒������Z�o����
		g_StaminaGauge[nCnt].fLength = sqrtf(((g_StaminaGauge[nCnt].size.x * g_StaminaGauge[nCnt].size.x) + (g_StaminaGauge[nCnt].size.y * g_StaminaGauge[nCnt].size.y)) / 2.0f);
		float fLengthPos = sqrtf(((sizePos.x * sizePos.x) + (sizePos.y * sizePos.y)) / 2.0f);

		// �Ίp���̊p�x���Z�o
		g_StaminaGauge[nCnt].fAngele = atan2f(g_StaminaGauge[nCnt].size.x, g_StaminaGauge[nCnt].size.y);
		float fAngelePos = atan2f(sizePos.x, sizePos.y);

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = g_StaminaGauge[nCnt].pos.x + sinf(g_StaminaGauge[nCnt].rot.z + (D3DX_PI + g_StaminaGauge[nCnt].fAngele)) * g_StaminaGauge[nCnt].fLength;
		pVtx[0].pos.y = g_StaminaGauge[nCnt].pos.y + cosf(g_StaminaGauge[nCnt].rot.z + (D3DX_PI + g_StaminaGauge[nCnt].fAngele)) * g_StaminaGauge[nCnt].fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_StaminaGauge[nCnt].pos.x + sinf(g_StaminaGauge[nCnt].rot.z + (D3DX_PI - g_StaminaGauge[nCnt].fAngele)) *  g_StaminaGauge[nCnt].fLength;
		pVtx[1].pos.y = g_StaminaGauge[nCnt].pos.y + cosf(g_StaminaGauge[nCnt].rot.z + (D3DX_PI - g_StaminaGauge[nCnt].fAngele)) *  g_StaminaGauge[nCnt].fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_StaminaGauge[nCnt].pos.x + sinf(g_StaminaGauge[nCnt].rot.z - (0 + fAngelePos)) * fLengthPos;
		pVtx[2].pos.y = g_StaminaGauge[nCnt].pos.y + cosf(g_StaminaGauge[nCnt].rot.z - (0 + fAngelePos)) * fLengthPos;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_StaminaGauge[nCnt].pos.x + sinf(g_StaminaGauge[nCnt].rot.z - (0 - fAngelePos)) * fLengthPos;
		pVtx[3].pos.y = g_StaminaGauge[nCnt].pos.y + cosf(g_StaminaGauge[nCnt].rot.z - (0 - fAngelePos)) * fLengthPos;
		pVtx[3].pos.z = 0.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = g_StaminaGauge[nCnt].col;
		pVtx[1].col = g_StaminaGauge[nCnt].col;
		pVtx[2].col = g_StaminaGauge[nCnt].col;
		pVtx[3].col = g_StaminaGauge[nCnt].col;

		// ���_�o�b�t�@���A�����b�N
		g_pVtxBuffStaminaGauge->Unlock();
	}
}

//---------------------------------------------------------------------------
// �X�^�~�i�Q�[�W�̏��擾
//---------------------------------------------------------------------------
StaminaGauge *GetStaminaGauge(void)
{
	return &g_StaminaGauge[0];
}