//**************************************************************************************************
//
// ���`�揈��(sphere.cpp)
// Auther�F�������l
//
//**************************************************************************************************

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"
#include "sphere.h"
#include"file.h"

//***************************************************************************
// �}�N����`
//***************************************************************************
#define SPHERE_X_BLOCK2				(100)						// X�����̃u���b�N��
#define SPHERE_Z_BLOCK2				(10)						// Z�����̃u���b�N��

// �u���b�N�� + 1
#define MESHBLOCK_X_ADD_ONE			(SPHERE_X_BLOCK2 + 1)
#define MESHBLOCK_Z_ADD_ONE			(SPHERE_Z_BLOCK2 + 1)

// 1�񒸓_��
#define SPHERE_RHINE_VTX_ONE		(SPHERE_X_BLOCK2 * 2 + 2)

// ���̒��_��
#define MAX_SPHERE_VERTEX			(MESHBLOCK_X_ADD_ONE * MESHBLOCK_Z_ADD_ONE)		

// ���̃|���S����
#define MAX_SPHERE_POLYGON			((SPHERE_X_BLOCK2 * SPHERE_Z_BLOCK2 * 2) + (((SPHERE_Z_BLOCK2 - 1) * 2) * 2))

// ���̃C���f�b�N�X��
#define MAX_SPHERE_INDEX			((SPHERE_RHINE_VTX_ONE * SPHERE_Z_BLOCK2) + ((SPHERE_Z_BLOCK2 - 1) * 2))	

// ���T�C�Y
#define MAX_SPHERE_SIZE				(10.0f)

// ���̔��a�̒���
#define SPHERE_RADIUS				(50.0f)


//***************************************************************************
// �O���[�o���ϐ�
//***************************************************************************
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffSphere = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9			g_pTextureSphere = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9		g_pIdzBuffSphere = NULL;		// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
Sphere						g_Sphere;						// �����̎擾

//---------------------------------------------------------------------------
// ������������
//---------------------------------------------------------------------------
void InitSphere(void)
{
	// �t�@�C���ϐ��̐錾�Ƒ��
	char aFile[128] = FILE_TEXTURE_DATA;
	strcat(aFile, "sky001.jpg");

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���ɒ���t����e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, aFile, &g_pTextureSphere);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_SPHERE_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSphere,
		NULL);

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_SPHERE_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdzBuffSphere,
		NULL);

	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffSphere->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntV = 0; nCntV < SPHERE_Z_BLOCK2 + 1; nCntV++)
	{
		for (int nCntH = 0; nCntH < SPHERE_X_BLOCK2 + 1; nCntH++)
		{// �ϐ��錾
			float fRot = ((-D3DX_PI * 2.0f) / SPHERE_X_BLOCK2) * nCntH;			// Y���̊p�x�̐ݒ�
			float fHalfRot = (-D3DX_PI / SPHERE_Z_BLOCK2) * nCntV;				// ������Z���̊p�x�̔���

			// �����Ɣ��a�̐ݒ�
			D3DXVECTOR2 radius = D3DXVECTOR2(sinf(fHalfRot) * SPHERE_RADIUS, cosf(fHalfRot) * SPHERE_RADIUS);

			//// ���_���W�̐ݒ�
			//pVtx[0].pos.x = sinf(fRot) * radius.y;
			//pVtx[0].pos.z = cosf(fRot) * radius.y;
			//pVtx[0].pos.y = radius.x;

			// �����_�̎Z�o
			pVtx[0].pos.z = sinf(fHalfRot) * cosf(fRot) * SPHERE_RADIUS;
			pVtx[0].pos.x = sinf(fHalfRot) * sinf(fRot) * SPHERE_RADIUS;
			pVtx[0].pos.y = cosf(fHalfRot) * SPHERE_RADIUS;

			// �e���_�̖@���̐ݒ�(*�x�N�g���̑傫����1�ɂ���K�v������)
			pVtx[0].nor.x = pVtx[0].pos.x;
			pVtx[0].nor.z = pVtx[0].pos.z;
			pVtx[0].nor.y = 0.0f;
			D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(1.0f / SPHERE_X_BLOCK2 * nCntH, 1.0f / SPHERE_Z_BLOCK2 * nCntV);

			pVtx++;
		}
	}

	// �C���f�b�N�X�o�b�t�@�����b�N
	WORD *pIdx;
	g_pIdzBuffSphere->Lock(0, 0, (void**)&pIdx, 0);

	// �C���f�b�N�X�̐ݒ�
	for (int nCntZ = 0; nCntZ < SPHERE_Z_BLOCK2; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESHBLOCK_X_ADD_ONE; nCntX++)
		{// �C���f�b�N�X���̐ݒ�
			pIdx[0] = MESHBLOCK_X_ADD_ONE + nCntX + nCntZ * MESHBLOCK_X_ADD_ONE;
			pIdx[1] = MESHBLOCK_X_ADD_ONE + nCntX + nCntZ * MESHBLOCK_X_ADD_ONE - MESHBLOCK_X_ADD_ONE;

			pIdx += 2;
		}

		if (nCntZ != SPHERE_Z_BLOCK2)
		{// �ő吔�ȉ��̎�
		 // �k�ރ|���S���C���f�b�N�X���̐ݒ�
			pIdx[0] = MESHBLOCK_X_ADD_ONE * nCntZ + SPHERE_X_BLOCK2;
			pIdx[1] = MESHBLOCK_X_ADD_ONE * (nCntZ + 2);

			pIdx += 2;
		}
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffSphere->Unlock();

	// ���_�o�b�t�@�̃A�����b�N
	g_pIdzBuffSphere->Unlock();
}

//---------------------------------------------------------------------------
// ���I������
//---------------------------------------------------------------------------
void UninitSphere(void)
{
	// �e�N�X�`���̔j��	  
	if (g_pTextureSphere != NULL)
	{
		g_pTextureSphere->Release();
		g_pTextureSphere = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffSphere != NULL)
	{
		g_pVtxBuffSphere->Release();
		g_pVtxBuffSphere = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��	  
	if (g_pIdzBuffSphere != NULL)
	{
		g_pIdzBuffSphere->Release();
		g_pIdzBuffSphere = NULL;
	}
}

//---------------------------------------------------------------------------
// ���X�V����
//---------------------------------------------------------------------------
void UpdateSphere(void)
{

}

//---------------------------------------------------------------------------
// ���`�揈��
//---------------------------------------------------------------------------
void DrawSphere(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��������[�s��]��[�P�ʍs��]�ɏ�����)
	D3DXMatrixIdentity(&g_Sphere.mtxWorld);

	// �����̔��f
	// �s���]�֐� (��������[���[(y)�s�b�`(x)���[��(z)]�����̉�]�s����쐬)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Sphere.rot.y, g_Sphere.rot.x, g_Sphere.rot.z);

	// �s��|���Z�֐� (������ * ��O������������Ɋi�[)
	D3DXMatrixMultiply(&g_Sphere.mtxWorld, &g_Sphere.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, g_Sphere.pos.x, g_Sphere.pos.y, g_Sphere.pos.z);
	D3DXMatrixMultiply(&g_Sphere.mtxWorld, &g_Sphere.mtxWorld, &mtxTrans);						// �s��|���Z�֐�

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Sphere.mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSphere, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdzBuffSphere);

	// ���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureSphere);

	// ���`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_SPHERE_VERTEX, 0, MAX_SPHERE_POLYGON);

	// �e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);
}