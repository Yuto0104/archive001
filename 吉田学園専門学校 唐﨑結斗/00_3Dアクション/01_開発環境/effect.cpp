//**************************************************************************************************
//
// �G�t�F�N�g�`�揈��(effect.cpp)
// Auther�F�������l
//
//**************************************************************************************************

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"
#include "effect.h"
#include"file.h"
#include"model.h"
#include"shadow.h"

//***************************************************************************
// �}�N����`
//***************************************************************************
#define MAX_EFFECT_VERTEX		(4)				// �G�t�F�N�g�̒��_��
#define MAX_EFFECT				(12800)			// �G�t�F�N�g�̍ő吔

//***************************************************************************
// �O���[�o���ϐ�
//***************************************************************************
static LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffEffect = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
static LPDIRECT3DTEXTURE9			g_pTextureEffect[MAX_EFFECTTEXTURE] = {};		// �e�N�X�`���ւ̃|�C���^
static Effect						g_Effect[MAX_EFFECT];							// �G�t�F�N�g���̎擾

//---------------------------------------------------------------------------
// �G�t�F�N�g����������
//---------------------------------------------------------------------------
void InitEffect(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �t�@�C���ϐ��̐錾�Ƒ��
	char aFile[MAX_EFFECTTEXTURE][128];
	memset(&aFile[0][0], 0, sizeof(aFile));
	
	for (int i = 0; i < MAX_EFFECTTEXTURE; i++)
	{// ���΃p�X�̎擾
		strcpy(&aFile[i][0], FILE_TEXTURE_DATA);
	}
	
	// �e�N�X�`���̊���U��
	strcat(&aFile[(int)(EFFECTTEXTURE_000)][0], "effect/Particle01.png");
	strcat(&aFile[(int)(EFFECTTEXTURE_001)][0], "effect/Shock_wave003.png");
	strcat(&aFile[(int)(EFFECTTEXTURE_002)][0], "effect/Particle02.png");
	strcat(&aFile[(int)(EFFECTTEXTURE_003)][0], "effect/���}�Z��.jpg");
	strcat(&aFile[(int)(EFFECTTEXTURE_004)][0], "effect/���L�Z��.jpg");
	strcat(&aFile[(int)(EFFECTTEXTURE_005)][0], "effect/�A.jpg");

	for (int nCnt = 0; nCnt < MAX_EFFECTTEXTURE; nCnt++)
	{
		// �G�t�F�N�g�ɒ���t����e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, &aFile[(EFFECTTEXTURE)(nCnt)][0], &g_pTextureEffect[(EFFECTTEXTURE)(nCnt)]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_EFFECT_VERTEX * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		// �G�t�F�N�g���̏�����
		g_Effect[nCntEffect].pos = {};											// �ʒu
		g_Effect[nCntEffect].rot = {};											// ����
		g_Effect[nCntEffect].move = {};											// �ړ���
		g_Effect[nCntEffect].mtxWorld = {};										// ���[���h�}�g���b�N�X
		g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			// �J���[
		g_Effect[nCntEffect].zFuncType = D3DCMP_LESS;							// Z�o�b�t�@�̔�r�^�C�v
		g_Effect[nCntEffect].EffectType = EFFECTTYPE_NORMAL;					// �G�t�F�N�g�^�C�v
		g_Effect[nCntEffect].EffectTexture = EFFECTTEXTURE_000;					// �e�N�X�`���^�C�v
		g_Effect[nCntEffect].EffectAlphaBlend = EFFECTALPHABLEND_ADDITIVE;		// ���u�����h
		g_Effect[nCntEffect].fRadius = 0.0f;									// ���a
		g_Effect[nCntEffect].fSpeed = 0.0f;										// �ړ����x
		g_Effect[nCntEffect].fGravity = 0.0f;									// �d��
		g_Effect[nCntEffect].nIdx = 0;											// �C���f�b�N�X
		g_Effect[nCntEffect].nLife = 0;											// ����
		g_Effect[nCntEffect].bShadow = false;									// �e�̎g�p��
		g_Effect[nCntEffect].bUse = false;										// �g�p��

		// �����ʂ̌v�Z
		g_Effect[nCntEffect].fAttenuationRadius = g_Effect[nCntEffect].fRadius / (float)(g_Effect[nCntEffect].nLife);	// ���a
		g_Effect[nCntEffect].fAttenuationAlpha = g_Effect[nCntEffect].col.a / (float)(g_Effect[nCntEffect].nLife);		// ���l

		// ���_���W
		pVtx[0].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);

		// �e���_�̖@���̐ݒ�(*�x�N�g���̑傫����1�ɂ���K�v������)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = g_Effect[nCntEffect].col;
		pVtx[1].col = g_Effect[nCntEffect].col;
		pVtx[2].col = g_Effect[nCntEffect].col;
		pVtx[3].col = g_Effect[nCntEffect].col;

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//---------------------------------------------------------------------------
// �G�t�F�N�g�I������
//---------------------------------------------------------------------------
void UninitEffect(void)
{
	for (int nCnt = 0; nCnt < MAX_EFFECTTEXTURE; nCnt++)
	{
		//�e�N�X�`���̔j��	  
		if (g_pTextureEffect[nCnt] != NULL)
		{
			g_pTextureEffect[nCnt]->Release();

			g_pTextureEffect[nCnt] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//---------------------------------------------------------------------------
// �G�t�F�N�g�X�V����
//---------------------------------------------------------------------------
void UpdateEffect(void)
{
	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == true)
		{// �g�p����Ă���
			// �ʒu�̍X�V
			g_Effect[nCntEffect].pos += g_Effect[nCntEffect].move;

			// �d�͂̕t�^
			g_Effect[nCntEffect].pos.y -= g_Effect[nCntEffect].fGravity;

			// �����̌���
			g_Effect[nCntEffect].nLife--;

			if (g_Effect[nCntEffect].nLife == 0)
			{// �������Ȃ��Ȃ�����
				g_Effect[nCntEffect].bUse = false;

				if (g_Effect[nCntEffect].bShadow == true)
				{// �e���g�p����
					DeleteShadow(g_Effect[nCntEffect].nIdx);
				}
			}

			if (g_Effect[nCntEffect].bShadow == true)
			{// �e���g�p����
				// �e�̈ړ�
				SetPositionShadow(g_Effect[nCntEffect].nIdx, g_Effect[nCntEffect].pos, g_Effect[nCntEffect].rot,D3DXVECTOR3(g_Effect[nCntEffect].fRadius,0.0f, g_Effect[nCntEffect].fRadius));
			}

			switch (g_Effect[nCntEffect].EffectType)
			{
			case EFFECTTYPE_NORMAL:		// �ʏ�G�t�F�N�g
				// �T�C�Y�̌���
				g_Effect[nCntEffect].fRadius -= g_Effect[nCntEffect].fAttenuationRadius;

				// ���l�̌���
				g_Effect[nCntEffect].col.a -= g_Effect[nCntEffect].fAttenuationAlpha;

				// ���_���W
				pVtx[0].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
				break;

			case EFFECTTYPE_WALL:		// �ǃG�t�F�N�g
				// �T�C�Y�̌���
				g_Effect[nCntEffect].fRadius += g_Effect[nCntEffect].fAttenuationRadius;

				// ���l�̌���
				g_Effect[nCntEffect].col.a -= g_Effect[nCntEffect].fAttenuationAlpha;

				// ���_���W
				pVtx[0].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
				break;

			case EFFECTTYPE_FIELD:		// �n�ʃG�t�F�N�g
				// �T�C�Y�̌���
				g_Effect[nCntEffect].fRadius += g_Effect[nCntEffect].fAttenuationRadius;

				// ���l�̌���
				g_Effect[nCntEffect].col.a -= g_Effect[nCntEffect].fAttenuationAlpha;

				// �����̉��Z
				g_Effect[nCntEffect].rot.y += 0.1f;

				// ���_���W
				pVtx[0].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, 0.0f, g_Effect[nCntEffect].fRadius);
				pVtx[1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, 0.0f, g_Effect[nCntEffect].fRadius);
				pVtx[2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, 0.0f, -g_Effect[nCntEffect].fRadius);
				pVtx[3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, 0.0f, -g_Effect[nCntEffect].fRadius);
				break;
			}

			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_Effect[nCntEffect].col;
			pVtx[1].col = g_Effect[nCntEffect].col;
			pVtx[2].col = g_Effect[nCntEffect].col;
			pVtx[3].col = g_Effect[nCntEffect].col;
		}

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//---------------------------------------------------------------------------
// �G�t�F�N�g�`�揈��
//---------------------------------------------------------------------------
void DrawEffect(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans, mtxView;			// �v�Z�p�}�g���b�N�X

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == true)
		{// �G�t�F�N�g���g�p����Ă���Ƃ�
			
			switch (g_Effect[nCntEffect].EffectAlphaBlend)
			{// ���u�����h�̐ݒ�
			case EFFECTALPHABLEND_ADDITIVE:
				// ���u�����f�B���O�����Z�����ɐݒ�
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
				break;

			case EFFECTALPHABLEND_SUBTRACTIVE:
				// ���u�����f�B���O�����Z�����ɐݒ�
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
				break;
			}

			// ���[���h�}�g���b�N�X�̏�����
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect[(int)(g_Effect[nCntEffect].EffectTexture)]);

			// Z�e�X�g���g�p����
			pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

			// Z�e�X�g�̐ݒ�
			pDevice->SetRenderState(D3DRS_ZFUNC, g_Effect[nCntEffect].zFuncType);

			// ���e�X�g���g�p����
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

			// ���e�X�g�̐ݒ�
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			// ���C�g�𖳌�
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// ���[���h�}�g���b�N�X�̏�����
			// �s�񏉊����֐�(��������[�s��]��[�P�ʍs��]�ɏ�����)
			D3DXMatrixIdentity(&g_Effect[nCntEffect].mtxWorld);

			switch (g_Effect[nCntEffect].EffectType)
			{
			case EFFECTTYPE_NORMAL:		// �ʏ�G�t�F�N�g
				pDevice->GetTransform(D3DTS_VIEW, &mtxView);

				// �J�����t�s���ݒ�
				g_Effect[nCntEffect].mtxWorld._11 = mtxView._11;
				g_Effect[nCntEffect].mtxWorld._12 = mtxView._21;
				g_Effect[nCntEffect].mtxWorld._13 = mtxView._31;
				g_Effect[nCntEffect].mtxWorld._21 = mtxView._12;
				g_Effect[nCntEffect].mtxWorld._22 = mtxView._22;
				g_Effect[nCntEffect].mtxWorld._23 = mtxView._32;
				g_Effect[nCntEffect].mtxWorld._31 = mtxView._13;
				g_Effect[nCntEffect].mtxWorld._32 = mtxView._23;
				g_Effect[nCntEffect].mtxWorld._33 = mtxView._33;
				break;

			case EFFECTTYPE_WALL:		// �ǃG�t�F�N�g
				pDevice->GetTransform(D3DTS_VIEW, &mtxView);

				// �J�����t�s���ݒ�
				g_Effect[nCntEffect].mtxWorld._11 = mtxView._11;
				g_Effect[nCntEffect].mtxWorld._13 = mtxView._31;
				g_Effect[nCntEffect].mtxWorld._31 = mtxView._13;
				g_Effect[nCntEffect].mtxWorld._33 = mtxView._33;
				break;

			case EFFECTTYPE_FIELD:		// �n�ʃG�t�F�N�g
				// �����̔��f
				// �s���]�֐� (��������[���[(y)�s�b�`(x)���[��(z)]�����̉�]�s����쐬)
				D3DXMatrixRotationYawPitchRoll(&mtxRot,
					g_Effect[nCntEffect].rot.y,
					g_Effect[nCntEffect].rot.x,
					g_Effect[nCntEffect].rot.z);

				// �s��|���Z�֐� (������ * ��O������������Ɋi�[)
				D3DXMatrixMultiply(&g_Effect[nCntEffect].mtxWorld, &g_Effect[nCntEffect].mtxWorld, &mtxRot);
				break;
			}		

			// �ʒu�𔽉f
			// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
			D3DXMatrixTranslation(&mtxTrans, g_Effect[nCntEffect].pos.x, g_Effect[nCntEffect].pos.y, g_Effect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_Effect[nCntEffect].mtxWorld, &g_Effect[nCntEffect].mtxWorld, &mtxTrans);		// �s��|���Z�֐�

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Effect[nCntEffect].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �G�t�F�N�g�`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, MAX_EFFECT_VERTEX * nCntEffect, 2);

			// ���C�g��L��	
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// Z�e�X�g�̏I��
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

			// ���e�X�g�̏I��
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

			// �e�N�X�`���̉���
			pDevice->SetTexture(0, NULL);

			// ���u�����f�B���O�����ɖ߂�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
	}
}

//---------------------------------------------------------------------------
// �G�t�F�N�g�ݒ菈��
//---------------------------------------------------------------------------
void SetEffect(D3DXVECTOR3 pos,
	D3DXVECTOR3 rot,
	D3DXCOLOR col,
	D3DCMPFUNC zFuncType,
	EFFECTTYPE EffectType,
	EFFECTALPHABLEND EffectAlphaBlend,
	float fRadius,
	float fSpeed,
	float fGravity,
	int nLife,
	int nTexture,
	bool bShadow)
{
	// �ϐ��錾
	int nCntEffect;

	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == false)
		{// �g�p����Ă��Ȃ�
			// �G�t�F�N�g���̏�����
			g_Effect[nCntEffect].pos = pos;										// �ʒu
			g_Effect[nCntEffect].rot = rot;										// ����
			g_Effect[nCntEffect].mtxWorld = {};									// ���[���h�}�g���b�N�X
			g_Effect[nCntEffect].col = col;										// �J���[
			g_Effect[nCntEffect].zFuncType = zFuncType;							// Z�o�b�t�@�̔�r�^�C�v
			g_Effect[nCntEffect].EffectType = EffectType;						// �G�t�F�N�g�^�C�v
			g_Effect[nCntEffect].EffectTexture = (EFFECTTEXTURE)(nTexture);		// �e�N�X�`���^�C�v
			g_Effect[nCntEffect].EffectAlphaBlend = EffectAlphaBlend;			// ���u�����h
			g_Effect[nCntEffect].fRadius = fRadius;								// ���a
			g_Effect[nCntEffect].fSpeed = fSpeed;								// �ړ����x
			g_Effect[nCntEffect].fGravity = fGravity;							// �d��
			g_Effect[nCntEffect].nLife = nLife;									// ����
			g_Effect[nCntEffect].bShadow = bShadow;								// �e�̎g�p��
			g_Effect[nCntEffect].bUse = true;									// �g�p��

			// �����ʂ̌v�Z
			g_Effect[nCntEffect].fAttenuationRadius = g_Effect[nCntEffect].fRadius / (float)(g_Effect[nCntEffect].nLife);	// ���a
			g_Effect[nCntEffect].fAttenuationAlpha = g_Effect[nCntEffect].col.a / (float)(g_Effect[nCntEffect].nLife);		// ���l

			// �ړ��ʂ̎Z�o
			g_Effect[nCntEffect].move.z = sinf(g_Effect[nCntEffect].rot.x) * cosf(g_Effect[nCntEffect].rot.y) * g_Effect[nCntEffect].fSpeed;
			g_Effect[nCntEffect].move.x = sinf(g_Effect[nCntEffect].rot.x) * sinf(g_Effect[nCntEffect].rot.y) * g_Effect[nCntEffect].fSpeed;
			g_Effect[nCntEffect].move.y = cosf(g_Effect[nCntEffect].rot.x) * g_Effect[nCntEffect].fSpeed;

			switch (g_Effect[nCntEffect].EffectType)
			{
			case EFFECTTYPE_NORMAL:		// �ʏ�G�t�F�N�g
			case EFFECTTYPE_WALL:		// �ǃG�t�F�N�g
				// ���_���W
				pVtx[0].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);

				break;

			case EFFECTTYPE_FIELD:		// �n�ʃG�t�F�N�g
				// �G�t�F�N�g���̏�����
				g_Effect[nCntEffect].pos.y = 0.5f;													// �ʒu
				g_Effect[nCntEffect].rot = rot;														// ����
				g_Effect[nCntEffect].fAttenuationRadius = g_Effect[nCntEffect].fRadius / 10.0f;		// ���a�̌�����

				// ���_���W
				pVtx[0].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, 0.0f, g_Effect[nCntEffect].fRadius);
				pVtx[1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, 0.0f, g_Effect[nCntEffect].fRadius);
				pVtx[2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, 0.0f, -g_Effect[nCntEffect].fRadius);
				pVtx[3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, 0.0f, -g_Effect[nCntEffect].fRadius);
				break;
			}

			if (g_Effect[nCntEffect].bShadow == true)
			{// �e���g�p����
				// �e�̐ݒ�
				g_Effect[nCntEffect].nIdx = SetShadow(g_Effect[nCntEffect].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(g_Effect[nCntEffect].fRadius, 0.0f, g_Effect[nCntEffect].fRadius));
			}

			// �e���_�̖@���̐ݒ�(*�x�N�g���̑傫����1�ɂ���K�v������)
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_Effect[nCntEffect].col;
			pVtx[1].col = g_Effect[nCntEffect].col;
			pVtx[2].col = g_Effect[nCntEffect].col;
			pVtx[3].col = g_Effect[nCntEffect].col;

			// �e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEffect->Unlock();
}