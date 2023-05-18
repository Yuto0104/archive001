//**************************************************************************************************
//
// �p�[�e�B�N���`�揈��(particle.cpp)
// Auther�F�������l
//
//**************************************************************************************************

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"
#include "particle.h"
#include "file.h"
#include"effect.h"

//***************************************************************************
// �}�N����`
//***************************************************************************
#define MAX_PARTICLE_VERTEX		(4)				// �p�[�e�B�N���̒��_��
#define MAX_PARTICLE			(128)			// �p�[�e�B�N���̍ő吔

//***************************************************************************
// �O���[�o���ϐ�
//***************************************************************************
static Particle						g_Particle[MAX_PARTICLE];			// �p�[�e�B�N�����̎擾

//---------------------------------------------------------------------------
// �p�[�e�B�N������������
//---------------------------------------------------------------------------
void InitParticle(void)
{
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		// �p�[�e�B�N�����̏�����
		g_Particle[nCntParticle].pos = {};											// �ʒu
		g_Particle[nCntParticle].posPop = {};										// �����ʒu
		g_Particle[nCntParticle].rot = {};											// ����
		g_Particle[nCntParticle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			// �J���[
		g_Particle[nCntParticle].fRadius = 0.0f;									// ���a
		g_Particle[nCntParticle].fSpeed = 0.0f;										// �ړ����x
		g_Particle[nCntParticle].fGravity = 0.0f;									// �d��
		g_Particle[nCntParticle].nLife = 0;											// ����
		g_Particle[nCntParticle].nTexture = 0;										// �e�N�X�`��
		g_Particle[nCntParticle].nAlphaBlend = 0;									// ���u�����h
		g_Particle[nCntParticle].nTime = 0;											// ��������
		g_Particle[nCntParticle].nNumParticle = 0;									// ������
		g_Particle[nCntParticle].bShadow = false;									// �e�̎g�p��
		g_Particle[nCntParticle].bUse = false;										// �g�p��
	}
}

//---------------------------------------------------------------------------
// �p�[�e�B�N���X�V����
//---------------------------------------------------------------------------
void UpdateParticle(void)
{
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_Particle[nCntParticle].bUse == true)
		{// �g�p����Ă��Ȃ�
			for (int nCntNum = 0; nCntNum < g_Particle[nCntParticle].nNumParticle; nCntNum++)
			{
				// �p�[�e�B�N�����̌v�Z
				Particle particle;

				// �ʒu�̎Z�o
				particle.pos.x = g_Particle[nCntParticle].pos.x + (float)(-(int)(g_Particle[nCntParticle].posPop.x / 2.0f) + rand() % ((int)(g_Particle[nCntParticle].posPop.x) + 1));
				particle.pos.y = g_Particle[nCntParticle].pos.y + (float)(-(int)(g_Particle[nCntParticle].posPop.y / 2.0f) + rand() % ((int)(g_Particle[nCntParticle].posPop.y) + 1));
				particle.pos.z = g_Particle[nCntParticle].pos.z + (float)(-(int)(g_Particle[nCntParticle].posPop.z / 2.0f) + rand() % ((int)(g_Particle[nCntParticle].posPop.z) + 1));

				// ���a�̎Z�o
				particle.fRadius = (float)(rand() % ((int)(g_Particle[nCntParticle].fRadius * 100.0f) + 1)) / 100.0f;

				// �����̎Z�o
				particle.nLife = rand() % (g_Particle[nCntParticle].nLife + 1) + 1;

				// �ړ����x�̎Z�o
				particle.fSpeed = (float)(rand() % ((int)(g_Particle[nCntParticle].fSpeed * 100.0f) + 1)) / 100.0f;

				// �ړ������̎Z�o
				particle.rot.x = (((int)((D3DX_PI * 2) * g_Particle[nCntParticle].rot.x * 100.0f) / 2) - (rand() % ((int)((D3DX_PI * 2) * g_Particle[nCntParticle].rot.x * 100.0f) + 1))) / 100.0f;
				particle.rot.y = (((int)((D3DX_PI * 2) * g_Particle[nCntParticle].rot.y * 100.0f) / 2) - (rand() % ((int)((D3DX_PI * 2) * g_Particle[nCntParticle].rot.y * 100.0f) + 1))) / 100.0f;
				particle.rot.z = 0.0f;

				// �G�t�F�N�g�̐���
				SetEffect(particle.pos,
					particle.rot,
					g_Particle[nCntParticle].col,
					D3DCMP_ALWAYS,
					EFFECTTYPE_NORMAL,
					(EFFECTALPHABLEND)(g_Particle[nCntParticle].nAlphaBlend),
					particle.fRadius,
					particle.fSpeed,
					g_Particle[nCntParticle].fGravity,
					particle.nLife,
					g_Particle[nCntParticle].nTexture,
					g_Particle[nCntParticle].bShadow);
			}

			if (g_Particle[nCntParticle].nTime != 0)
			{// �������Ԃ�0�̎�
				g_Particle[nCntParticle].nTime--;
			}

			if (g_Particle[nCntParticle].nTime <= 1 && g_Particle[nCntParticle].nTime != 0)
			{// 0�ȊO��1�ȉ��̎�
				g_Particle[nCntParticle].bUse = false;
			}
		}
	}
}

//---------------------------------------------------------------------------
// �p�[�e�B�N���ݒ菈��
//---------------------------------------------------------------------------
void SetParticle(D3DXVECTOR3 pos,		// �ʒu
	D3DXVECTOR3	posPop,					// �����ʒu
	D3DXVECTOR3 rot,					// ����(X���W->��,Y���W->��,360��->1.0f)
	D3DXCOLOR col,						// �J���[
	float fRadius,						// ���a
	float fSpeed,						// �ړ����x
	float fGravity,						// �d��
	int	nLife,							// ����
	int	nTexture,						// �e�N�X�`���^�C�v
	int nAlphaBlend,					// ���u�����h(0 = ���Z���� | 1 = ���Z����)
	int	nTime,							// ��������(0 == ��)
	int nNumParticle,					// ������
	bool bShadow)						// �e�̎g�p��
{
	// �ϐ��錾
	int nCntParticle;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_Particle[nCntParticle].bUse == false)
		{// �g�p����Ă��Ȃ�
			// �p�[�e�B�N�����̏�����
			g_Particle[nCntParticle].pos = pos;							// �ʒu
			g_Particle[nCntParticle].posPop = posPop;					// �����ʒu
			g_Particle[nCntParticle].rot = rot;							// ����
			g_Particle[nCntParticle].col = col;							// �J���[
			g_Particle[nCntParticle].fRadius = fRadius;					// ���a
			g_Particle[nCntParticle].fSpeed = fSpeed;					// �ړ����x
			g_Particle[nCntParticle].fGravity = fGravity;				// �d��
			g_Particle[nCntParticle].nLife = nLife;						// ����
			g_Particle[nCntParticle].nTexture = nTexture;				// �e�N�X�`��
			g_Particle[nCntParticle].nAlphaBlend = nAlphaBlend;			// ���u�����h
			g_Particle[nCntParticle].nTime = nTime;						// ��������
			g_Particle[nCntParticle].nNumParticle = nNumParticle + 1;	// ������
			g_Particle[nCntParticle].bShadow = bShadow;					// �e�̎g�p��
			g_Particle[nCntParticle].bUse = true;						// �g�p��

			if (g_Particle[nCntParticle].nTime != 0)
			{// �������Ԃ�0�̎�
				g_Particle[nCntParticle].nTime++;
			}

			break;
		}
	}
}