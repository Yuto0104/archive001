//**************************************************************************************************
//
// �r���{�[�h�`�揈��(billboard.cpp)
// Auther�F�������l
//
//**************************************************************************************************

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"
#include "billboard.h"
#include"file.h"
#include"model.h"
#include"shadow.h"
#include"effect.h"
#include"wall.h"

//***************************************************************************
// �}�N����`
//***************************************************************************
#define MAX_BILLBOARD_VERTEX			(4)					// �r���{�[�h�̒��_��
#define MAX_BILLBOARD					(128)				// �r���{�[�h�̍ő吔
#define MAX_BILLBOARD_SIZE				(10.0f)				// �r���{�[�h�̑傫��

//***************************************************************************
// �O���[�o���ϐ�
//***************************************************************************
static LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffBillboard = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
static LPDIRECT3DTEXTURE9			g_pTextureBillboard = NULL;			// �e�N�X�`���ւ̃|�C���^
static Billboard					g_Billboard[MAX_BILLBOARD];			// �r���{�[�h���̎擾

//---------------------------------------------------------------------------
// �r���{�[�h����������
//---------------------------------------------------------------------------
void InitBillboard(void)
{
	// �t�@�C���ϐ��̐錾�Ƒ��
	char aFile[128] = FILE_TEXTURE_DATA;
	strcat(aFile, "bullet000.png");

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_BILLBOARD_VERTEX * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	// �r���{�[�h�ɒ���t����e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, aFile, &g_pTextureBillboard);

	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		// �r���{�[�h���̏�����
		g_Billboard[nCntBillboard].pos = {};											// �ʒu
		g_Billboard[nCntBillboard].posOld = {};											// �ߋ��ʒu
		g_Billboard[nCntBillboard].move = {};											// �ړ���
		g_Billboard[nCntBillboard].rot = {};											// ����
		g_Billboard[nCntBillboard].mtxWorld = {};										// ���[���h�}�g���b�N�X
		g_Billboard[nCntBillboard].fRadius = MAX_BILLBOARD_SIZE;						// ���a
		g_Billboard[nCntBillboard].bUse = false;										// �g�p��

		// ���_���W
		pVtx[0].pos = D3DXVECTOR3(-g_Billboard[nCntBillboard].fRadius, g_Billboard[nCntBillboard].fRadius, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Billboard[nCntBillboard].fRadius, g_Billboard[nCntBillboard].fRadius, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_Billboard[nCntBillboard].fRadius, -g_Billboard[nCntBillboard].fRadius, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Billboard[nCntBillboard].fRadius, -g_Billboard[nCntBillboard].fRadius, 0.0f);

		// �e���_�̖@���̐ݒ�(*�x�N�g���̑傫����1�ɂ���K�v������)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
	g_pVtxBuffBillboard->Unlock();
}

//---------------------------------------------------------------------------
// �r���{�[�h�I������
//---------------------------------------------------------------------------
void UninitBillboard(void)
{
	//�e�N�X�`���̔j��	  
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();

		g_pTextureBillboard = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//---------------------------------------------------------------------------
// �r���{�[�h�X�V����
//---------------------------------------------------------------------------
void UpdateBillboard(void)
{
	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_Billboard[nCntBillboard].bUse == true)
		{// �r���{�[�h���g�p����Ă���Ƃ�
			// �ߋ��ʒu�̎Z�o
			g_Billboard[nCntBillboard].posOld = g_Billboard[nCntBillboard].pos;

			// �ʒu�̍X�V
			g_Billboard[nCntBillboard].pos -= g_Billboard[nCntBillboard].move;

			if (CollisionWallBillBoard(&g_Billboard[nCntBillboard].pos, &g_Billboard[nCntBillboard].posOld, nCntBillboard))
			{
				/*g_Billboard[nCntBillboard].bUse = false;
				DeleteShadow(g_Billboard[nCntBillboard].nIdx);*/

				// �G�t�F�N�g�̐���
				SetEffect(g_Billboard[nCntBillboard].pos,
					g_Billboard[nCntBillboard].rot,
					D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f),
					D3DCMP_ALWAYS,
					EFFECTTYPE_WALL,
					EFFECTALPHABLEND_ADDITIVE,
					g_Billboard[nCntBillboard].fRadius,
					0.0f,
					0.0f,
					60,
					1,
					false);
			}

			// �e�̈ړ�
			SetPositionShadow(g_Billboard[nCntBillboard].nIdx, g_Billboard[nCntBillboard].pos, g_Billboard[nCntBillboard].rot,D3DXVECTOR3(g_Billboard[nCntBillboard].fRadius, 0.0f, g_Billboard[nCntBillboard].fRadius));

			// ���f���̈ړ�����
			//if (g_Billboard[nCntBillboard].pos.x > 190.0f
			//	|| g_Billboard[nCntBillboard].pos.x < -190.0f
			//	|| g_Billboard[nCntBillboard].pos.z > 190.0f
			//	|| g_Billboard[nCntBillboard].pos.z < -190.0f)
			//{
			//	g_Billboard[nCntBillboard].bUse = false;
			//	DeleteShadow(g_Billboard[nCntBillboard].nIdx);

			//	// �G�t�F�N�g�̐���
			//	SetEffect(g_Billboard[nCntBillboard].pos,
			//		g_Billboard[nCntBillboard].rot,
			//		D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f),
			//		D3DCMP_ALWAYS,
			//		EFFECTTYPE_WALL,
			//		g_Billboard[nCntBillboard].fRadius,
			//		0.0f,
			//		0.0f,
			//		60,
			//		1,
			//		false);
			//}

			// �G�t�F�N�g�̐���
			SetEffect(g_Billboard[nCntBillboard].pos,
				g_Billboard[nCntBillboard].rot,
				D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f),
				D3DCMP_ALWAYS,
				EFFECTTYPE_NORMAL,
				EFFECTALPHABLEND_ADDITIVE,
				g_Billboard[nCntBillboard].fRadius,
				0.0f,
				0.0f,
				60,
				0,
				false);
		}
	}
}

//---------------------------------------------------------------------------
// �r���{�[�h�`�揈��
//---------------------------------------------------------------------------
void DrawBillboard(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans,mtxView;		// �v�Z�p�}�g���b�N�X

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBillboard);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_Billboard[nCntBillboard].bUse == true)
		{// �r���{�[�h���g�p����Ă���Ƃ�
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
			D3DXMatrixIdentity(&g_Billboard[nCntBillboard].mtxWorld);
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// �J�����t�s���ݒ�
			g_Billboard[nCntBillboard].mtxWorld._11 = mtxView._11;
			g_Billboard[nCntBillboard].mtxWorld._12 = mtxView._21;
			g_Billboard[nCntBillboard].mtxWorld._13 = mtxView._31;
			g_Billboard[nCntBillboard].mtxWorld._21 = mtxView._12;
			g_Billboard[nCntBillboard].mtxWorld._22 = mtxView._22;
			g_Billboard[nCntBillboard].mtxWorld._23 = mtxView._32;
			g_Billboard[nCntBillboard].mtxWorld._31 = mtxView._13;
			g_Billboard[nCntBillboard].mtxWorld._32 = mtxView._23;
			g_Billboard[nCntBillboard].mtxWorld._33 = mtxView._33;

			// �ʒu�𔽉f
			// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
			D3DXMatrixTranslation(&mtxTrans, g_Billboard[nCntBillboard].pos.x, g_Billboard[nCntBillboard].pos.y, g_Billboard[nCntBillboard].pos.z);
			D3DXMatrixMultiply(&g_Billboard[nCntBillboard].mtxWorld, &g_Billboard[nCntBillboard].mtxWorld, &mtxTrans);		// �s��|���Z�֐�

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Billboard[nCntBillboard].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �r���{�[�h�`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, MAX_BILLBOARD_VERTEX * nCntBillboard, 2);

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
// �r���{�[�h�ݒ菈��
//---------------------------------------------------------------------------
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSpeed)
{
	// �ϐ��錾
	int nCntBillboard;

	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_Billboard[nCntBillboard].bUse == false)
		{
			// �r���{�[�h���̐ݒ�
			g_Billboard[nCntBillboard].pos = pos;								// �ʒu
			g_Billboard[nCntBillboard].rot = rot;								// ����
			g_Billboard[nCntBillboard].mtxWorld = {};							// ���[���h�}�g���b�N�X
			g_Billboard[nCntBillboard].fRadius = MAX_BILLBOARD_SIZE;			// ���a
			g_Billboard[nCntBillboard].bUse = true;								// �g�p��

			// ���_���W
			pVtx[0].pos = D3DXVECTOR3(-g_Billboard[nCntBillboard].fRadius, g_Billboard[nCntBillboard].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Billboard[nCntBillboard].fRadius, g_Billboard[nCntBillboard].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_Billboard[nCntBillboard].fRadius, -g_Billboard[nCntBillboard].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Billboard[nCntBillboard].fRadius, -g_Billboard[nCntBillboard].fRadius, 0.0f);

			// �ړ���
			g_Billboard[nCntBillboard].move.x = sinf(g_Billboard[nCntBillboard].rot.y) * fSpeed;
			g_Billboard[nCntBillboard].move.z = cosf(g_Billboard[nCntBillboard].rot.y) * fSpeed;
			g_Billboard[nCntBillboard].move.y = 0.0f;

			// �e�̐ݒ�
			g_Billboard[nCntBillboard].nIdx = SetShadow(g_Billboard[nCntBillboard].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(g_Billboard[nCntBillboard].fRadius, 0.0f, g_Billboard[nCntBillboard].fRadius));

			break;
		}

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBillboard->Unlock();
}

//---------------------------------------------------------------------------
// �r���{�[�h���̎擾
//---------------------------------------------------------------------------
Billboard *GetBillboard(void)
{
	return &g_Billboard[0];
}