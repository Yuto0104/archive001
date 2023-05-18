//**************************************************************************************************
//
// �Ǖ`�揈��(wall.cpp)
// Auther�F�������l
//
//**************************************************************************************************

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"
#include "wall.h"
#include"file.h"
#include"model.h"
#include"billboard.h"
#include"shadow.h"
#include"effect.h"
#include "calculation.h"

//***************************************************************************
// �}�N����`
//***************************************************************************
#define MAX_WALL_VERTEX			(4)					// �ǂ̒��_��
#define MAX_WALL				(128)				// �ǂ̍ő吔
#define MAX_WALL_WIDH			(200.0f)			// �ǂ̕�
#define MAX_WALL_HEIGHT			(100.0f)			// �ǂ̍���

//***************************************************************************
// �O���[�o���ϐ�
//***************************************************************************
static LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffWall = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
static LPDIRECT3DTEXTURE9			g_pTextureWall = NULL;		// �e�N�X�`���ւ̃|�C���^
static Wall							g_Wall[MAX_WALL];			// �Ǐ��̎擾

//---------------------------------------------------------------------------
// �Ǐ���������
//---------------------------------------------------------------------------
void InitWall(void)
{
	// �t�@�C���ϐ��̐錾�Ƒ��
	char aFile[128] = FILE_TEXTURE_DATA;
	strcat(aFile, "wall000.jpg");

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_WALL_VERTEX * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	// �ǂɒ���t����e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, aFile, &g_pTextureWall);

	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		// �Ǐ��̏�����
		g_Wall[nCntWall].pos = {};											// �ʒu
		g_Wall[nCntWall].rot = {};											// ����
		g_Wall[nCntWall].mtxWorld = {};										// ���[���h�}�g���b�N�X
		g_Wall[nCntWall].col = {};											// �J���[
		g_Wall[nCntWall].bUse = false;										// �g�p��

		// ���_���W
		pVtx[0].pos = D3DXVECTOR3(-MAX_WALL_WIDH, MAX_WALL_HEIGHT,0.0f);
		pVtx[1].pos = D3DXVECTOR3(MAX_WALL_WIDH, MAX_WALL_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-MAX_WALL_WIDH, -MAX_WALL_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(MAX_WALL_WIDH, -MAX_WALL_HEIGHT, 0.0f);

		// �e���_�̖@���̐ݒ�(*�x�N�g���̑傫����1�ɂ���K�v������)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = g_Wall[nCntWall].col;
		pVtx[1].col = g_Wall[nCntWall].col;
		pVtx[2].col = g_Wall[nCntWall].col;
		pVtx[3].col = g_Wall[nCntWall].col;

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffWall->Unlock();
}

//---------------------------------------------------------------------------
// �ǏI������
//---------------------------------------------------------------------------
void UninitWall(void)
{
	//�e�N�X�`���̔j��	  
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();

		g_pTextureWall = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//---------------------------------------------------------------------------
// �ǍX�V����
//---------------------------------------------------------------------------
void UpdateWall(void)
{
	
}

//---------------------------------------------------------------------------
// �Ǖ`�揈��
//---------------------------------------------------------------------------
void DrawWall(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureWall);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == true)
		{// �ǂ��g�p����Ă���Ƃ�
			// ���[���h�}�g���b�N�X�̏�����
			// �s�񏉊����֐�(��������[�s��]��[�P�ʍs��]�ɏ�����)
			D3DXMatrixIdentity(&g_Wall[nCntWall].mtxWorld);

			// �����̔��f
			// �s���]�֐� (��������[���[(y)�s�b�`(x)���[��(z)]�����̉�]�s����쐬)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[nCntWall].rot.y, g_Wall[nCntWall].rot.x, g_Wall[nCntWall].rot.z);

			// �s��|���Z�֐� (������ * ��O������������Ɋi�[)
			D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorld, &g_Wall[nCntWall].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
			D3DXMatrixTranslation(&mtxTrans, g_Wall[nCntWall].pos.x, g_Wall[nCntWall].pos.y, g_Wall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorld, &g_Wall[nCntWall].mtxWorld, &mtxTrans);		// �s��|���Z�֐�

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Wall[nCntWall].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �Ǖ`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, MAX_WALL_VERTEX * nCntWall, 2);
		}
	}

	// �e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);
}

//---------------------------------------------------------------------------
// �ǐݒ菈��
//---------------------------------------------------------------------------
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	// �ϐ��錾
	int nCntWall;

	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == false)
		{
			// �Ǐ��̐ݒ�
			g_Wall[nCntWall].pos = pos;																		// �ʒu
			g_Wall[nCntWall].rot = D3DXVECTOR3((D3DX_PI * rot.x),(D3DX_PI * rot.y),(D3DX_PI * rot.z));		// ����
			g_Wall[nCntWall].mtxWorld = {};																	// ���[���h�}�g���b�N�X
			g_Wall[nCntWall].col = col;																		// �J���[
			g_Wall[nCntWall].bUse = true;																	// �g�p��

			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_Wall[nCntWall].col;
			pVtx[1].col = g_Wall[nCntWall].col;
			pVtx[2].col = g_Wall[nCntWall].col;
			pVtx[3].col = g_Wall[nCntWall].col;
			break;
		}

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffWall->Unlock();
}

//---------------------------------------------------------------------------
// �ǂƃr���{�[�h�̓����蔻�菈��
//---------------------------------------------------------------------------
bool	CollisionWallBillBoard(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, int nIdx)
{
	// �ϐ��錾
	int		nCntWall;
	bool	bIsLanding = false;

	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == true)
		{
			// �ϐ��錾
			D3DXVECTOR3 aVtx0 = WorldCastVtx(pVtx[0].pos, g_Wall[nCntWall].pos, g_Wall[nCntWall].rot);
			D3DXVECTOR3 aVtx1 = WorldCastVtx(pVtx[1].pos, g_Wall[nCntWall].pos, g_Wall[nCntWall].rot);
			D3DXVECTOR3 aVecLine = aVtx1 - aVtx0;															// �ǂ̃x�N�g��
			D3DXVECTOR3 aVecPos = D3DXVECTOR3(pos->x - aVtx0.x, pos->y - aVtx0.y, pos->z - aVtx0.z);		// �ʒu�̃x�N�g��
			// �O�ς��g�p���������蔻��
			if (0.0f > (aVecLine.z * aVecPos.x) - (aVecLine.x * aVecPos.z))
			{
				/*bIsLanding = true;*/
				Billboard *pBillboard = GetBillboard();
				pBillboard += nIdx;

				D3DXVECTOR3 VecC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				D3DXVECTOR3 aVtx0 = WorldCastVtx(pVtx[0].pos, g_Wall[nCntWall].pos, g_Wall[nCntWall].rot);
				D3DXVECTOR3 aVtx1 = WorldCastVtx(pVtx[1].pos, g_Wall[nCntWall].pos, g_Wall[nCntWall].rot);
				D3DXVECTOR3 aVtx2 = WorldCastVtx(pVtx[2].pos, g_Wall[nCntWall].pos, g_Wall[nCntWall].rot);
				D3DXVECTOR3 aVecA = aVtx1 - aVtx0;		// �ǂ̃x�N�g��
				D3DXVECTOR3 aVecB = aVtx2 - aVtx0;		// �ǂ̃x�N�g��

				// �O�ς��g�p���Ė@���̎Z�o
				D3DXVec3Cross(&VecC, &aVecA, &aVecB);
				D3DXVec3Normalize(&VecC, &VecC);

				VecC *= (-pBillboard->move.x * VecC.x) + (-pBillboard->move.z * VecC.z);

				// ����
				pBillboard->move += VecC * 2.0f;

				break;
			}
		}
	}

	return bIsLanding;

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffWall->Unlock();
}