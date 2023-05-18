//**************************************************************************************************
//
// �e�`�揈��(shadow.cpp)
// Auther�F�������l
//
//**************************************************************************************************

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"
#include "shadow.h"
#include"file.h"
#include"model.h"

//***************************************************************************
// �}�N����`
//***************************************************************************
#define MAX_SHADOW_VERTEX		(4)				// �e�̒��_��
#define MAX_SHADOW				(12800)			// �e�̍ő吔
#define MAX_SHADOW_SIZE			(10.0f)			// �e�T�C�Y
#define ATTENUATION_SHADOW		(0.01f)			// �e�̌����W��

//***************************************************************************
// �O���[�o���ϐ�
//***************************************************************************
static LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffShadow = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
static LPDIRECT3DTEXTURE9			g_pTextureShadow = NULL;		// �e�N�X�`���ւ̃|�C���^
static Shadow						g_Shadow[MAX_SHADOW];			// �e���̎擾

//---------------------------------------------------------------------------
// �e����������
//---------------------------------------------------------------------------
void InitShadow(void)
{
	// �t�@�C���ϐ��̐錾�Ƒ��
	char aFile[128] = FILE_TEXTURE_DATA;
	strcat(aFile, "shadow000.jpg");

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_SHADOW_VERTEX * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	// �e�ɒ���t����e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, aFile, &g_pTextureShadow);

	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		// �e���̏�����
		g_Shadow[nCntShadow].pos = {};						// �ʒu
		g_Shadow[nCntShadow].rot = {};						// ����
		g_Shadow[nCntShadow].size = {};						// ���a
		g_Shadow[nCntShadow].mtxWorld = {};					// ���[���h�}�g���b�N�X
		g_Shadow[nCntShadow].bUse = false;					// �g�p��

		// ���_���W
		pVtx[0].pos = D3DXVECTOR3(-g_Shadow[nCntShadow].size.x, 0.0f, g_Shadow[nCntShadow].size.z);
		pVtx[1].pos = D3DXVECTOR3(g_Shadow[nCntShadow].size.x, 0.0f, g_Shadow[nCntShadow].size.z);
		pVtx[2].pos = D3DXVECTOR3(-g_Shadow[nCntShadow].size.x, 0.0f, -g_Shadow[nCntShadow].size.z);
		pVtx[3].pos = D3DXVECTOR3(g_Shadow[nCntShadow].size.x, 0.0f, -g_Shadow[nCntShadow].size.z);

		// �e���_�̖@���̐ݒ�(*�x�N�g���̑傫����1�ɂ���K�v������)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffShadow->Unlock();
}

//---------------------------------------------------------------------------
// �e�I������
//---------------------------------------------------------------------------
void UninitShadow(void)
{
	//�e�N�X�`���̔j��	  
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();

		g_pTextureShadow = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//---------------------------------------------------------------------------
// �e�X�V����
//---------------------------------------------------------------------------
void UpdateShadow(void)
{

}

//---------------------------------------------------------------------------
// �e�`�揈��
//---------------------------------------------------------------------------
void DrawShadow(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureShadow);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == true)
		{// �e���g�p����Ă���Ƃ�
			// ���[���h�}�g���b�N�X�̏�����
			// �s�񏉊����֐�(��������[�s��]��[�P�ʍs��]�ɏ�����)
			D3DXMatrixIdentity(&g_Shadow[nCntShadow].mtxWorld);

			// �����̔��f
			// �s���]�֐� (��������[���[(y)�s�b�`(x)���[��(z)]�����̉�]�s����쐬)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow[nCntShadow].rot.y, g_Shadow[nCntShadow].rot.x, g_Shadow[nCntShadow].rot.z);

			// �s��|���Z�֐� (������ * ��O������������Ɋi�[)
			D3DXMatrixMultiply(&g_Shadow[nCntShadow].mtxWorld, &g_Shadow[nCntShadow].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
			D3DXMatrixTranslation(&mtxTrans, g_Shadow[nCntShadow].pos.x, g_Shadow[nCntShadow].pos.y, g_Shadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_Shadow[nCntShadow].mtxWorld, &g_Shadow[nCntShadow].mtxWorld, &mtxTrans);		// �s��|���Z�֐�

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Shadow[nCntShadow].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, MAX_SHADOW_VERTEX * nCntShadow, 2);
		}
	}

	// �e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//---------------------------------------------------------------------------
// �e�ݒ菈��
//---------------------------------------------------------------------------
int	SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// �ϐ��錾
	int nCntShadow;

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == false)
		{
			// �ϐ��錾
			float fDiffPos = pos.y * 0.01f;

			// �e���̐ݒ�
			g_Shadow[nCntShadow].pos.x = pos.x;																			// �ʒu(x)
			g_Shadow[nCntShadow].pos.y = 0.1f;																			// �ʒu(y)
			g_Shadow[nCntShadow].pos.z = pos.z;																			// �ʒu(z)
			g_Shadow[nCntShadow].rot = rot;																				// ����
			g_Shadow[nCntShadow].mtxWorld = {};																			// ���[���h�}�g���b�N�X
			g_Shadow[nCntShadow].size = D3DXVECTOR3(size.x + (size.x * fDiffPos),0.0f, size.z + (size.z * fDiffPos));	// �傫��						// ���a
			g_Shadow[nCntShadow].bUse = true;																			// �g�p��

			break;
		}
	}

	return nCntShadow;		// �e�̔ԍ�(index)��Ԃ�
}

//---------------------------------------------------------------------------
// �e�ړ�����
//---------------------------------------------------------------------------
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// �ϐ��錾
	float fDiffPos = pos.y * ATTENUATION_SHADOW;
	float fAlpha = pos.y * ATTENUATION_SHADOW;

	// �e���̐ݒ�
	g_Shadow[nIdxShadow].pos.x = pos.x;																			// �ʒu(x)
	g_Shadow[nIdxShadow].pos.y = 0.1f;																			// �ʒu(y)
	g_Shadow[nIdxShadow].pos.z = pos.z;																			// �ʒu(z)
	g_Shadow[nIdxShadow].rot.x = 0.0f;																			// ����(x)
	g_Shadow[nIdxShadow].rot.y = rot.y;																			// ����(y)
	g_Shadow[nIdxShadow].rot.z = 0.0f;																			// ����(z)
	g_Shadow[nIdxShadow].size = D3DXVECTOR3(size.x + (size.x * fDiffPos), 0.0f, size.z + (size.z * fDiffPos));	// �傫��	

	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdxShadow * 4;		//���_�f�[�^�̃|�C���^��4���i�߂�

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(-g_Shadow[nIdxShadow].size.x, 0.0f, g_Shadow[nIdxShadow].size.z);
	pVtx[1].pos = D3DXVECTOR3(g_Shadow[nIdxShadow].size.x, 0.0f, g_Shadow[nIdxShadow].size.z);
	pVtx[2].pos = D3DXVECTOR3(-g_Shadow[nIdxShadow].size.x, 0.0f, -g_Shadow[nIdxShadow].size.z);
	pVtx[3].pos = D3DXVECTOR3(g_Shadow[nIdxShadow].size.x, 0.0f, -g_Shadow[nIdxShadow].size.z);

	// �e���_�̖@���̐ݒ�(*�x�N�g���̑傫����1�ɂ���K�v������)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (1.0f * fAlpha));
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (1.0f * fAlpha));
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (1.0f * fAlpha));
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (1.0f * fAlpha));

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffShadow->Unlock();
}

//---------------------------------------------------------------------------
// �e�폜����
//---------------------------------------------------------------------------
void DeleteShadow(int nIdxShadow)
{
	// �e���̏�����
	g_Shadow[nIdxShadow].pos = {};						// �ʒu
	g_Shadow[nIdxShadow].rot = {};						// ����
	g_Shadow[nIdxShadow].size = {};						// ���a
	g_Shadow[nIdxShadow].mtxWorld = {};					// ���[���h�}�g���b�N�X
	g_Shadow[nIdxShadow].bUse = false;					// �g�p��
}