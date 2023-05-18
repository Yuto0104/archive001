//**************************************************************************************************
//
// ���b�V���t�B�[���h�`�揈��(meshmield.cpp)
// Auther�F�������l
//
//**************************************************************************************************

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"
#include "meshfield.h"
#include"file.h"

//***************************************************************************
// �}�N����`
//***************************************************************************
#define MESHFIELD_X_BLOCK2			(20)						// X�����̃u���b�N��
#define MESHFIELD_Z_BLOCK2			(20)						// Z�����̃u���b�N��

// �u���b�N�� + 1
#define MESHBLOCK_X_ADD_ONE		(MESHFIELD_X_BLOCK2 + 1)
#define MESHBLOCK_Z_ADD_ONE		(MESHFIELD_Z_BLOCK2 + 1)

// 1�񒸓_��
#define MESH_RHINE_VTX_ONE		(MESHFIELD_X_BLOCK2 * 2 + 2)

// ���b�V���t�B�[���h�̒��_��
#define MAX_MESHFIELD_VERTEX		(MESHBLOCK_X_ADD_ONE * MESHBLOCK_Z_ADD_ONE)		

// ���b�V���t�B�[���h�̃|���S����
#define MAX_MESHFIELD_POLYGON		((MESHFIELD_X_BLOCK2 * MESHFIELD_Z_BLOCK2 * 2) + (((MESHFIELD_Z_BLOCK2 - 1) * 2) * 2))

// ���b�V���t�B�[���h�̃C���f�b�N�X��
#define MAX_MESHFIELD_INDEX			((MESH_RHINE_VTX_ONE * MESHFIELD_Z_BLOCK2) + ((MESHFIELD_Z_BLOCK2 - 1) * 2))	

// ���b�V���t�B�[���h�T�C�Y
#define MAX_MESHFIELD_SIZE			(150.0f)															

//***************************************************************************
// �O���[�o���ϐ�
//***************************************************************************
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffMeshField = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9			g_pTextureMeshField = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9		g_pIdzBuffMeshField = NULL;		// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
MeshField					g_MeshField;					// ���b�V���t�B�[���h���̎擾

//---------------------------------------------------------------------------
// ���b�V���t�B�[���h����������
//---------------------------------------------------------------------------
void InitMeshField(void)
{
	// �t�@�C���ϐ��̐錾�Ƒ��
	char aFile[128] = FILE_TEXTURE_DATA;
	strcat(aFile, "��.jpg");

	// �����ʒu�ݒ�
	g_MeshField.pos = D3DXVECTOR3(-(MAX_MESHFIELD_SIZE * MESHFIELD_X_BLOCK2) / 2, 
		0.0f, 
		(MAX_MESHFIELD_SIZE * MESHFIELD_Z_BLOCK2) / 2);

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���b�V���t�B�[���h�ɒ���t����e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, aFile, &g_pTextureMeshField);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_MESHFIELD_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_MESHFIELD_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdzBuffMeshField,
		NULL);

	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < MESHFIELD_Z_BLOCK2 + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESHFIELD_X_BLOCK2 + 1; nCntX++)
		{// �ϐ��錾
			int nCntVtx = nCntX + (nCntZ * (MESHFIELD_X_BLOCK2 + 1));

			// ���_���W�̐ݒ�
			pVtx[nCntVtx].pos.x = (nCntVtx % (MESHFIELD_X_BLOCK2 + 1) - 1) * MAX_MESHFIELD_SIZE;
			pVtx[nCntVtx].pos.y = 0.0f;
			pVtx[nCntVtx].pos.z = (nCntVtx / (MESHFIELD_X_BLOCK2 + 1) - 1) * -MAX_MESHFIELD_SIZE;

			// �e���_�̖@���̐ݒ�(*�x�N�g���̑傫����1�ɂ���K�v������)
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[nCntVtx].tex = D3DXVECTOR2(1.0f * nCntX, 1.0f * nCntZ);
		}
	}

	// �C���f�b�N�X�o�b�t�@�����b�N
	WORD *pIdx;
	g_pIdzBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	// �C���f�b�N�X�̐ݒ�
	for (int nCntZ = 0; nCntZ < MESHFIELD_Z_BLOCK2; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESHBLOCK_X_ADD_ONE; nCntX++)
		{// �C���f�b�N�X���̐ݒ�
			pIdx[0] = MESHBLOCK_X_ADD_ONE + nCntX + nCntZ * MESHBLOCK_X_ADD_ONE;
			pIdx[1] = MESHBLOCK_X_ADD_ONE + nCntX + nCntZ * MESHBLOCK_X_ADD_ONE - MESHBLOCK_X_ADD_ONE;

			pIdx += 2;
		}

		if (nCntZ != MESHFIELD_Z_BLOCK2)
		{// �ő吔�ȉ��̎�
			// �k�ރ|���S���C���f�b�N�X���̐ݒ�
			pIdx[0] = MESHBLOCK_X_ADD_ONE * nCntZ + MESHFIELD_X_BLOCK2;
			pIdx[1] = MESHBLOCK_X_ADD_ONE * (nCntZ + 2);

			pIdx += 2;
		}
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMeshField->Unlock();

	// ���_�o�b�t�@�̃A�����b�N
	g_pIdzBuffMeshField->Unlock();
}

//---------------------------------------------------------------------------
// ���b�V���t�B�[���h�I������
//---------------------------------------------------------------------------
void UninitMeshField(void)
{
	// �e�N�X�`���̔j��	  
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��	  
	if (g_pIdzBuffMeshField != NULL)
	{
		g_pIdzBuffMeshField->Release();
		g_pIdzBuffMeshField = NULL;
	}
}

//---------------------------------------------------------------------------
// ���b�V���t�B�[���h�X�V����
//---------------------------------------------------------------------------
void UpdateMeshField(void)
{

}

//---------------------------------------------------------------------------
// ���b�V���t�B�[���h�`�揈��
//---------------------------------------------------------------------------
void DrawMeshField(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��������[�s��]��[�P�ʍs��]�ɏ�����)
	D3DXMatrixIdentity(&g_MeshField.mtxWorld);

	// �����̔��f
	// �s���]�֐� (��������[���[(y)�s�b�`(x)���[��(z)]�����̉�]�s����쐬)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshField.rot.y, g_MeshField.rot.x, g_MeshField.rot.z);

	// �s��|���Z�֐� (������ * ��O������������Ɋi�[)
	D3DXMatrixMultiply(&g_MeshField.mtxWorld, &g_MeshField.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, g_MeshField.pos.x, g_MeshField.pos.y, g_MeshField.pos.z);
	D3DXMatrixMultiply(&g_MeshField.mtxWorld, &g_MeshField.mtxWorld, &mtxTrans);						// �s��|���Z�֐�

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshField.mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdzBuffMeshField);

	// ���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshField);

	// ���b�V���t�B�[���h�`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_MESHFIELD_VERTEX, 0, MAX_MESHFIELD_POLYGON);

	// �e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);
}