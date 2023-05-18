//**************************************************************************************************
//
// ���C���`�揈��(line.cpp)
// Auther�F�������l
//
//**************************************************************************************************

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"
#include "line.h"
#include "file.h"

//***************************************************************************
// �}�N����`
//***************************************************************************
#define MAX_LINE_VERTEX				(2)					// ���C���̒��_��
#define MAX_LINE					(128)				// ���C���̍ő吔
#define MAX_LINE_SIZE				(10.0f)				// ���C���̑傫��

//***************************************************************************
// �O���[�o���ϐ�
//***************************************************************************
static LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffLine = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
static Line							g_Line[MAX_LINE];				// ���C�����̎擾

//---------------------------------------------------------------------------
// ���C������������
//---------------------------------------------------------------------------
void InitLine(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_LINE_VERTEX * MAX_LINE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLine,
		NULL);

	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		// ���C�����̏�����
		g_Line[nCntLine].pos = {};											// �ʒu
		g_Line[nCntLine].rot = {};											// ����
		g_Line[nCntLine].start = {};										// �n�_
		g_Line[nCntLine].goal = {};											// �I�_
		g_Line[nCntLine].mtxWorld = {};										// ���[���h�}�g���b�N�X
		g_Line[nCntLine].fLength = 0.0f;									// ����
		g_Line[nCntLine].bUse = false;										// �g�p��

		// ���_���W
		pVtx[0].pos = D3DXVECTOR3(g_Line[nCntLine].start.x, g_Line[nCntLine].start.y, g_Line[nCntLine].start.z);
		pVtx[1].pos = D3DXVECTOR3(g_Line[nCntLine].goal.x, g_Line[nCntLine].goal.y, g_Line[nCntLine].goal.z);

		// �e���_�̖@���̐ݒ�(*�x�N�g���̑傫����1�ɂ���K�v������)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 2;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffLine->Unlock();
}

//---------------------------------------------------------------------------
// ���C���I������
//---------------------------------------------------------------------------
void UninitLine(void)
{
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffLine != NULL)
	{
		g_pVtxBuffLine->Release();
		g_pVtxBuffLine = NULL;
	}
}

//---------------------------------------------------------------------------
// ���C���X�V����
//---------------------------------------------------------------------------
void UpdateLine(void)
{
	
}

//---------------------------------------------------------------------------
// ���C���`�揈��
//---------------------------------------------------------------------------
void DrawLine(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans,mtxView;		// �v�Z�p�}�g���b�N�X

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		if (g_Line[nCntLine].bUse == true)
		{// ���C�����g�p����Ă���Ƃ�
			// Z�e�X�g���g�p����
			pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

			// Z�e�X�g�̐ݒ�
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);

			// ���e�X�g���g�p����
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

			// ���e�X�g�̐ݒ�
			pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			// ���C�g�𖳌�
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// ���[���h�}�g���b�N�X�̏�����
			// �s�񏉊����֐�(��������[�s��]��[�P�ʍs��]�ɏ�����)
			D3DXMatrixIdentity(&g_Line[nCntLine].mtxWorld);
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// �����̔��f
			// �s���]�֐� (��������[���[(y)�s�b�`(x)���[��(z)]�����̉�]�s����쐬)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Line[nCntLine].rot.y, g_Line[nCntLine].rot.x, g_Line[nCntLine].rot.z);

			// �s��|���Z�֐� (������ * ��O������������Ɋi�[)
			D3DXMatrixMultiply(&g_Line[nCntLine].mtxWorld, &g_Line[nCntLine].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
			D3DXMatrixTranslation(&mtxTrans, g_Line[nCntLine].pos.x, g_Line[nCntLine].pos.y, g_Line[nCntLine].pos.z);
			D3DXMatrixMultiply(&g_Line[nCntLine].mtxWorld, &g_Line[nCntLine].mtxWorld, &mtxTrans);		// �s��|���Z�֐�

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Line[nCntLine].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffLine, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g
			pDevice->SetFVF(FVF_VERTEX_3D);

			// ���C���`��
			pDevice->DrawPrimitive(D3DPT_LINELIST, MAX_LINE_VERTEX * nCntLine, 1);

			// ���C�g��L��	
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// Z�e�X�g�̏I��
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

			// ���e�X�g�̏I��
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		}
	}

	// �e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);
}

//---------------------------------------------------------------------------
// ���C���ݒ菈��
//---------------------------------------------------------------------------
int SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 start, D3DXVECTOR3 goal, D3DXCOLOR col)
{
	// �ϐ��錾
	int nCntLine = 0;

	//// ���_���̎擾
	//VERTEX_3D *pVtx = NULL;

	//// ���_�o�b�t�@�����b�N
	//g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);

	//for (nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	//{
	//	if (g_Line[nCntLine].bUse == false)
	//	{
	//		// ���C�����̐ݒ�
	//		g_Line[nCntLine].pos = pos;								// �ʒu
	//		g_Line[nCntLine].rot = rot;								// ����
	//		g_Line[nCntLine].start = start;							// �n�_
	//		g_Line[nCntLine].goal = goal;							// �I�_
	//		g_Line[nCntLine].mtxWorld = {};							// ���[���h�}�g���b�N�X
	//		g_Line[nCntLine].bUse = true;							// �g�p��

	//		// ���_���W
	//		pVtx[0].pos = D3DXVECTOR3(g_Line[nCntLine].start.x, g_Line[nCntLine].start.y, g_Line[nCntLine].start.z);
	//		pVtx[1].pos = D3DXVECTOR3(g_Line[nCntLine].goal.x, g_Line[nCntLine].goal.y, g_Line[nCntLine].goal.z);

	//		// ���_�J���[�̐ݒ�
	//		pVtx[0].col = col;
	//		pVtx[1].col = col;


	//		break;
	//	}

	//	pVtx += 2;		//���_�f�[�^�̃|�C���^��4���i�߂�
	//}

	//// ���_�o�b�t�@�̃A�����b�N
	//g_pVtxBuffLine->Unlock();

	return nCntLine;
}

void MoveLine(int nCnt, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���C�����̐ݒ�
	g_Line[nCnt].pos = pos;	// �ʒu
	g_Line[nCnt].rot = rot;	// ����
}

void DeleteLine(int nCnt)
{
	g_Line[nCnt].bUse = false;
}
