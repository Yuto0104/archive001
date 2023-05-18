//**************************************************************************************************
//
// �~���`�揈��(cylinder.cpp)
// Auther�F�������l
//
//**************************************************************************************************

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"
#include "cylinder.h"
#include"file.h"

//***************************************************************************
// �}�N����`
//***************************************************************************
#define CYLINDER_X_BLOCK2			(10)						// X�����̃u���b�N��
#define CYLINDER_Z_BLOCK2			(3)						// Z�����̃u���b�N��

// �u���b�N�� + 1
#define MESHBLOCK_X_ADD_ONE		(CYLINDER_X_BLOCK2 + 1)
#define MESHBLOCK_Z_ADD_ONE		(CYLINDER_Z_BLOCK2 + 1)

// 1�񒸓_��
#define CYLINDER_RHINE_VTX_ONE		(CYLINDER_X_BLOCK2 * 2 + 2)

// �~���̒��_��
#define MAX_CYLINDER_VERTEX			(MESHBLOCK_X_ADD_ONE * MESHBLOCK_Z_ADD_ONE)		

// �~���̃|���S����
#define MAX_CYLINDER_POLYGON		((CYLINDER_X_BLOCK2 * CYLINDER_Z_BLOCK2 * 2) + (((CYLINDER_Z_BLOCK2 - 1) * 2) * 2))

// �~���̃C���f�b�N�X��
#define MAX_CYLINDER_INDEX			((CYLINDER_RHINE_VTX_ONE * CYLINDER_Z_BLOCK2) + ((CYLINDER_Z_BLOCK2 - 1) * 2))	

// �~���T�C�Y
#define MAX_CYLINDER_SIZE			(10.0f)

// �~���̔��a�̒���
#define CYLINDER_RADIUS				(50.0f)

//***************************************************************************
// �O���[�o���ϐ�
//***************************************************************************
static LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffCylinder = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
static LPDIRECT3DTEXTURE9			g_pTextureCylinder = NULL;		// �e�N�X�`���ւ̃|�C���^
static LPDIRECT3DINDEXBUFFER9		g_pIdzBuffCylinder = NULL;		// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
static Cylinder						g_Cylinder;						// �~�����̎擾

//---------------------------------------------------------------------------
// �~������������
//---------------------------------------------------------------------------
void InitCylinder(void)
{
	g_Cylinder.pos = D3DXVECTOR3(0.0f, 0.0f, 100.0f);

	// �t�@�C���ϐ��̐錾�Ƒ��
	char aFile[128] = FILE_TEXTURE_DATA;
	strcat(aFile, "sky001.jpg");

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �~���ɒ���t����e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, aFile, &g_pTextureCylinder);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_CYLINDER_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCylinder,
		NULL);

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_CYLINDER_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdzBuffCylinder,
		NULL);

	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffCylinder->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntV = 0; nCntV < CYLINDER_Z_BLOCK2 + 1; nCntV++)
	{
		for (int nCntH = 0; nCntH < CYLINDER_X_BLOCK2 + 1; nCntH++)
		{// �ϐ��錾
			float fRot = ((D3DX_PI * 2.0f) / CYLINDER_X_BLOCK2) * nCntH;		// �p�x�̐ݒ�

			// ���_���W�̐ݒ�
			pVtx[0].pos.x = sinf(fRot) * CYLINDER_RADIUS;
			pVtx[0].pos.z = cosf(fRot) * CYLINDER_RADIUS;
			pVtx[0].pos.y = MAX_CYLINDER_SIZE * nCntV;

			// �e���_�̖@���̐ݒ�(*�x�N�g���̑傫����1�ɂ���K�v������)
			pVtx[0].nor.x = pVtx[0].pos.x;
			pVtx[0].nor.z = pVtx[0].pos.z;
			pVtx[0].nor.y = 0.0f;
			D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(1.0f / CYLINDER_X_BLOCK2 * nCntH, 1.0f / CYLINDER_X_BLOCK2 * nCntV);

			pVtx++;
		}
	}

	// �C���f�b�N�X�o�b�t�@�����b�N
	WORD *pIdx;
	g_pIdzBuffCylinder->Lock(0, 0, (void**)&pIdx, 0);

	// �C���f�b�N�X�̐ݒ�
	for (int nCntZ = 0; nCntZ < CYLINDER_Z_BLOCK2; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESHBLOCK_X_ADD_ONE; nCntX++)
		{// �C���f�b�N�X���̐ݒ�
			pIdx[0] = MESHBLOCK_X_ADD_ONE + nCntX + nCntZ * MESHBLOCK_X_ADD_ONE;
			pIdx[1] = MESHBLOCK_X_ADD_ONE + nCntX + nCntZ * MESHBLOCK_X_ADD_ONE - MESHBLOCK_X_ADD_ONE;

			pIdx += 2;
		}

		if (nCntZ != CYLINDER_Z_BLOCK2)
		{// �ő吔�ȉ��̎�
		 // �k�ރ|���S���C���f�b�N�X���̐ݒ�
			pIdx[0] = MESHBLOCK_X_ADD_ONE * nCntZ + CYLINDER_X_BLOCK2;
			pIdx[1] = MESHBLOCK_X_ADD_ONE * (nCntZ + 2);

			pIdx += 2;
		}
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffCylinder->Unlock();

	// ���_�o�b�t�@�̃A�����b�N
	g_pIdzBuffCylinder->Unlock();
}

//---------------------------------------------------------------------------
// �~���I������
//---------------------------------------------------------------------------
void UninitCylinder(void)
{
	// �e�N�X�`���̔j��	  
	if (g_pTextureCylinder != NULL)
	{
		g_pTextureCylinder->Release();
		g_pTextureCylinder = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffCylinder != NULL)
	{
		g_pVtxBuffCylinder->Release();
		g_pVtxBuffCylinder = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��	  
	if (g_pIdzBuffCylinder != NULL)
	{
		g_pIdzBuffCylinder->Release();
		g_pIdzBuffCylinder = NULL;
	}
}

//---------------------------------------------------------------------------
// �~���X�V����
//---------------------------------------------------------------------------
void UpdateCylinder(void)
{

}

//---------------------------------------------------------------------------
// �~���`�揈��
//---------------------------------------------------------------------------
void DrawCylinder(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��������[�s��]��[�P�ʍs��]�ɏ�����)
	D3DXMatrixIdentity(&g_Cylinder.mtxWorld);

	// �����̔��f
	// �s���]�֐� (��������[���[(y)�s�b�`(x)���[��(z)]�����̉�]�s����쐬)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Cylinder.rot.y, g_Cylinder.rot.x, g_Cylinder.rot.z);

	// �s��|���Z�֐� (������ * ��O������������Ɋi�[)
	D3DXMatrixMultiply(&g_Cylinder.mtxWorld, &g_Cylinder.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, g_Cylinder.pos.x, g_Cylinder.pos.y, g_Cylinder.pos.z);
	D3DXMatrixMultiply(&g_Cylinder.mtxWorld, &g_Cylinder.mtxWorld, &mtxTrans);						// �s��|���Z�֐�

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Cylinder.mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffCylinder, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdzBuffCylinder);

	// ���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureCylinder);

	// �~���`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_CYLINDER_VERTEX, 0, MAX_CYLINDER_POLYGON);

	// �e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);
}