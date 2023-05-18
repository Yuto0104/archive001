//**************************************************************************************************
//
// �X�J�C�{�b�N�X�`�揈��(skybox.cpp)
// Auther�F�������l
//
//**************************************************************************************************

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"
#include "skybox.h"
#include"file.h"

//***************************************************************************
// �}�N����`
//***************************************************************************
#define HEMISPHERE_X_BLOCK2				(10)						// X�����̃u���b�N��
#define HEMISPHERE_Z_BLOCK2				(10)						// Z�����̃u���b�N��

// �u���b�N�� + 1
#define MESHBLOCK_X_ADD_ONE			(HEMISPHERE_X_BLOCK2 + 1)
#define MESHBLOCK_Z_ADD_ONE			(HEMISPHERE_Z_BLOCK2 + 1)

// 1�񒸓_��
#define HEMISPHERE_RHINE_VTX_ONE		(HEMISPHERE_X_BLOCK2 * 2 + 2)

// �����̒��_��
#define MAX_HEMISPHERE_VERTEX			(MESHBLOCK_X_ADD_ONE * MESHBLOCK_Z_ADD_ONE)		

// �����̃|���S����
#define MAX_HEMISPHERE_POLYGON			((HEMISPHERE_X_BLOCK2 * HEMISPHERE_Z_BLOCK2 * 2) + (((HEMISPHERE_Z_BLOCK2 - 1) * 2) * 2))

// �����̃C���f�b�N�X��
#define MAX_HEMISPHERE_INDEX			((HEMISPHERE_RHINE_VTX_ONE * HEMISPHERE_Z_BLOCK2) + ((HEMISPHERE_Z_BLOCK2 - 1) * 2))

// �X�J�C���u�̒��_��
#define MAX_SKYLID_VERTEX				(MESHBLOCK_X_ADD_ONE + 1)

// �X�J�C���u�̃|���S����
#define MAX_SKYLID_POLYGON				(HEMISPHERE_X_BLOCK2)

// �X�J�C���u�̃C���f�b�N�X��
#define MAX_SKYLID_INDEX				((HEMISPHERE_X_BLOCK2 * 2) + 1)

// �X�J�C�{�b�N�X�T�C�Y
#define MAX_HEMISPHERE_SIZE				(10.0f)

// �X�J�C�{�b�N�X�̔��a�̒���
#define HEMISPHERE_RADIUS				(1000.0f)

//***************************************************************************
// �O���[�o���ϐ�
//***************************************************************************
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffSkybox = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9			g_pTextureSkybox = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9		g_pIdzBuffSkybox = NULL;		// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffSkyLid = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9			g_pTextureSkyLid = NULL;		// �X�J�C���u�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9		g_pIdzBuffSkyLid = NULL;		// �X�J�C���u�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
SkyBox						g_Skybox;						// �X�J�C���u�X�J�C�{�b�N�X���̎擾

//---------------------------------------------------------------------------
// �X�J�C�{�b�N�X����������
//---------------------------------------------------------------------------
void InitSkyBox(void)
{
	// �t�@�C���ϐ��̐錾�Ƒ��
	char aFile[128] = FILE_TEXTURE_DATA;
	strcat(aFile, "�C�w�i.png");

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �X�J�C�{�b�N�X�ɒ���t����e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, aFile, &g_pTextureSkybox);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_HEMISPHERE_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSkybox,
		NULL);

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_HEMISPHERE_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdzBuffSkybox,
		NULL);

	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffSkybox->Lock(0, 0, (void**)&pVtx, 0);

	// �C���f�b�N�X�o�b�t�@�����b�N
	WORD *pIdx;
	g_pIdzBuffSkybox->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntV = 0; nCntV < HEMISPHERE_Z_BLOCK2 + 1; nCntV++)
	{
		for (int nCntH = 0; nCntH < HEMISPHERE_X_BLOCK2 + 1; nCntH++)
		{// �ϐ��錾
			float fRot = ((-D3DX_PI * 2.0f) / HEMISPHERE_X_BLOCK2) * nCntH;				// Y���̊p�x�̐ݒ�
			float fHalfRot = (D3DX_PI / HEMISPHERE_Z_BLOCK2) * nCntV;			// ���X�J�C�{�b�N�X��Z���̊p�x�̔���

			// �����Ɣ��a�̐ݒ�
			D3DXVECTOR2 radius = D3DXVECTOR2(sinf(fHalfRot) * HEMISPHERE_RADIUS, cosf(fHalfRot) * HEMISPHERE_RADIUS);

			// ���_���W�̐ݒ�
			pVtx[0].pos.x = sinf(fRot) * radius.y;
			pVtx[0].pos.z = cosf(fRot) * radius.y;
			pVtx[0].pos.y = radius.x;

			// �e���_�̖@���̐ݒ�(*�x�N�g���̑傫����1�ɂ���K�v������)
			pVtx[0].nor.x = pVtx[0].pos.x;
			pVtx[0].nor.z = pVtx[0].pos.z;
			pVtx[0].nor.y = 0.0f;
			D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(1.0f / HEMISPHERE_X_BLOCK2 * (HEMISPHERE_X_BLOCK2 - nCntH),
				1.0f / HEMISPHERE_Z_BLOCK2 * (HEMISPHERE_Z_BLOCK2 - nCntV));

			// ���_���ւ̃|�C���^��i�߂�
			pVtx++;
		}
	}

	// �C���f�b�N�X�̐ݒ�
	for (int nCntZ = 0; nCntZ < HEMISPHERE_Z_BLOCK2; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESHBLOCK_X_ADD_ONE; nCntX++)
		{// �C���f�b�N�X���̐ݒ�
			pIdx[0] = MESHBLOCK_X_ADD_ONE + nCntX + nCntZ * MESHBLOCK_X_ADD_ONE;
			pIdx[1] = MESHBLOCK_X_ADD_ONE + nCntX + nCntZ * MESHBLOCK_X_ADD_ONE - MESHBLOCK_X_ADD_ONE;

			pIdx += 2;
		}

		if (nCntZ != HEMISPHERE_Z_BLOCK2)
		{// �ő吔�ȉ��̎�
		 // �k�ރ|���S���C���f�b�N�X���̐ݒ�
			pIdx[0] = MESHBLOCK_X_ADD_ONE * nCntZ + HEMISPHERE_X_BLOCK2;
			pIdx[1] = MESHBLOCK_X_ADD_ONE * (nCntZ + 2);

			pIdx += 2;
		}
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffSkybox->Unlock();

	// ���_�o�b�t�@�̃A�����b�N
	g_pIdzBuffSkybox->Unlock();

	/*InitSkyLid();*/
}

//---------------------------------------------------------------------------
// �X�J�C�{�b�N�X�I������
//---------------------------------------------------------------------------
void UninitSkyBox(void)
{
	// �e�N�X�`���̔j��	  
	if (g_pTextureSkybox != NULL)
	{
		g_pTextureSkybox->Release();
		g_pTextureSkybox = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffSkybox != NULL)
	{
		g_pVtxBuffSkybox->Release();
		g_pVtxBuffSkybox = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��	  
	if (g_pIdzBuffSkybox != NULL)
	{
		g_pIdzBuffSkybox->Release();
		g_pIdzBuffSkybox = NULL;
	}
}

//---------------------------------------------------------------------------
// �X�J�C�{�b�N�X�X�V����
//---------------------------------------------------------------------------
void UpdateSkyBox(void)
{

}

//---------------------------------------------------------------------------
// �X�J�C�{�b�N�X�`�揈��
//---------------------------------------------------------------------------
void DrawSkyBox(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X

	// ���C�g�𖳌�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��������[�s��]��[�P�ʍs��]�ɏ�����)
	D3DXMatrixIdentity(&g_Skybox.mtxWorld);

	// �����̔��f
	// �s���]�֐� (��������[���[(y)�s�b�`(x)���[��(z)]�����̉�]�s����쐬)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Skybox.rot.y, g_Skybox.rot.x, g_Skybox.rot.z);

	// �s��|���Z�֐� (������ * ��O������������Ɋi�[)
	D3DXMatrixMultiply(&g_Skybox.mtxWorld, &g_Skybox.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, g_Skybox.pos.x, g_Skybox.pos.y, g_Skybox.pos.z);
	D3DXMatrixMultiply(&g_Skybox.mtxWorld, &g_Skybox.mtxWorld, &mtxTrans);						// �s��|���Z�֐�

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Skybox.mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSkybox, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdzBuffSkybox);

	// ���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureSkybox);

	// �X�J�C�{�b�N�X�`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_HEMISPHERE_VERTEX, 0, MAX_HEMISPHERE_POLYGON);

	// �e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);

	// ���C�g��L��	
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	/*DrawSkyLid();*/
}

//---------------------------------------------------------------------------
// �X�J�C���u����������
//---------------------------------------------------------------------------
void InitSkyLid(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_HEMISPHERE_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSkyLid,
		NULL);

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_HEMISPHERE_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdzBuffSkyLid,
		NULL);

	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffSkyLid->Lock(0, 0, (void**)&pVtx, 0);

	// �C���f�b�N�X�o�b�t�@�����b�N
	WORD *pIdx;
	g_pIdzBuffSkyLid->Lock(0, 0, (void**)&pIdx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, HEMISPHERE_RADIUS, 0.0f);

	// �e���_�̖@���̐ݒ�(*�x�N�g���̑傫����1�ɂ���K�v������)
	pVtx[0].nor = pVtx[0].pos;
	D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���_���ւ̃|�C���^��i�߂�
	pVtx++;

	for (int nCnt = 1; nCnt < MAX_SKYLID_VERTEX - 1; nCnt++)
	{
		// �ϐ��錾
		float fRot = ((-D3DX_PI * 2.0f) / HEMISPHERE_X_BLOCK2) * nCnt;				// Y���̊p�x�̐ݒ�

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = sinf(fRot) * HEMISPHERE_RADIUS;
		pVtx[0].pos.z = cosf(fRot) * HEMISPHERE_RADIUS;
		pVtx[0].pos.y = HEMISPHERE_RADIUS;

		// �e���_�̖@���̐ݒ�(*�x�N�g���̑傫����1�ɂ���K�v������)
		pVtx[0].nor = pVtx[0].pos;
		D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���_���ւ̃|�C���^��i�߂�
		pVtx++;
	}

	pIdx[0] = 0;
	pIdx++;

	// �C���f�b�N�X�̐ݒ�
	for (int nCnt = 1; nCnt < MAX_SKYLID_INDEX - 1; nCnt += 3)
	{
		pIdx[0] = nCnt;
		pIdx[1] = nCnt + 1;
		pIdx[2] = 0;

		pIdx += 3;
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffSkyLid->Unlock();

	// ���_�o�b�t�@�̃A�����b�N
	g_pIdzBuffSkyLid->Unlock();
}

//---------------------------------------------------------------------------
// �X�J�C���u�`�揈��
//---------------------------------------------------------------------------
void DrawSkyLid(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X

	// ���C�g�𖳌�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��������[�s��]��[�P�ʍs��]�ɏ�����)
	D3DXMatrixIdentity(&g_Skybox.mtxWorld);

	// �����̔��f
	// �s���]�֐� (��������[���[(y)�s�b�`(x)���[��(z)]�����̉�]�s����쐬)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Skybox.rot.y, g_Skybox.rot.x, g_Skybox.rot.z);

	// �s��|���Z�֐� (������ * ��O������������Ɋi�[)
	D3DXMatrixMultiply(&g_Skybox.mtxWorld, &g_Skybox.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, g_Skybox.pos.x, g_Skybox.pos.y, g_Skybox.pos.z);
	D3DXMatrixMultiply(&g_Skybox.mtxWorld, &g_Skybox.mtxWorld, &mtxTrans);						// �s��|���Z�֐�

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Skybox.mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSkybox, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdzBuffSkybox);

	// ���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �X�J�C�{�b�N�X�`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN, 0, 0, MAX_SKYLID_VERTEX, 0, MAX_SKYLID_POLYGON);

	// �e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);

	// ���C�g��L��	
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}