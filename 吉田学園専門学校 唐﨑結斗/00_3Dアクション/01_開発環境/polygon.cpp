//**************************************************************************************************
//
// �|���S���`�揈��(polygon.cpp)
// Auther�F�������l
//
//**************************************************************************************************

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"
#include "polygon.h"
#include"file.h"

//***************************************************************************
// �}�N����`
//***************************************************************************
#define MAX_POLYGON_VERTEX		(4)				// �|���S���̒��_��
#define MAX_POLYGON_SIZE		(200.0f)		// �|���S���T�C�Y

//***************************************************************************
// �O���[�o���ϐ�
//***************************************************************************
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffPolygon = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9			g_pTexturePolygon = NULL;		// �e�N�X�`���ւ̃|�C���^
POLYGON						g_polygon;						// �|���S�����̎擾

//---------------------------------------------------------------------------
// �|���S������������
//---------------------------------------------------------------------------
void InitPolygon(void)
{
	// �t�@�C���ϐ��̐錾�Ƒ��
	char aFile[128] = FILE_TEXTURE_DATA;
	strcat(aFile, "field000.jpg");

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_POLYGON_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	// �|���S���ɒ���t����e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, aFile, &g_pTexturePolygon);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(-MAX_POLYGON_SIZE, 0.0f, MAX_POLYGON_SIZE);
	pVtx[1].pos = D3DXVECTOR3(MAX_POLYGON_SIZE, 0.0f, MAX_POLYGON_SIZE);
	pVtx[2].pos = D3DXVECTOR3(-MAX_POLYGON_SIZE, 0.0f, -MAX_POLYGON_SIZE);
	pVtx[3].pos = D3DXVECTOR3(MAX_POLYGON_SIZE, 0.0f, -MAX_POLYGON_SIZE);

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

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffPolygon->Unlock();
}

//---------------------------------------------------------------------------
// �|���S���I������
//---------------------------------------------------------------------------
void UninitPolygon(void)
{
	//�e�N�X�`���̔j��	  
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon->Release();

		g_pTexturePolygon = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}

//---------------------------------------------------------------------------
// �|���S���X�V����
//---------------------------------------------------------------------------
void UpdatePolygon(void)
{

}

//---------------------------------------------------------------------------
// �|���S���`�揈��
//---------------------------------------------------------------------------
void DrawPolygon(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��������[�s��]��[�P�ʍs��]�ɏ�����)
	D3DXMatrixIdentity(&g_polygon.mtxWorld);

	// �����̔��f
	// �s���]�֐� (��������[���[(y)�s�b�`(x)���[��(z)]�����̉�]�s����쐬)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_polygon.rot.y, g_polygon.rot.x, g_polygon.rot.z);

	// �s��|���Z�֐� (������ * ��O������������Ɋi�[)
	D3DXMatrixMultiply(&g_polygon.mtxWorld, &g_polygon.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, g_polygon.pos.x, g_polygon.pos.y, g_polygon.pos.z);
	D3DXMatrixMultiply(&g_polygon.mtxWorld, &g_polygon.mtxWorld, &mtxTrans);						// �s��|���Z�֐�

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_polygon.mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePolygon);

	// �|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// �e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);
}