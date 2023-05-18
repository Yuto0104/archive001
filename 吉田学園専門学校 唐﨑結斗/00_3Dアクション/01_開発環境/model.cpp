//**************************************************************************************************
//
// ���f���`�揈��(model.cpp)
// Auther�F�������l
//
//**************************************************************************************************

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"
#include "model.h"
#include"file.h"
#include"input.h"
#include"camera.h"
#include"shadow.h"
#include"billboard.h"
#include"effect.h"
#include"line.h"
#include"calculation.h"
#include"player.h"
#include"feed.h"

//***************************************************************************
// �}�N����`
//***************************************************************************
#define INIT_NUM_MODEL			(10000)				// ���_���W�̍ő�ŏ��̏����l
#define MODEL_MOVE_SPEED		(0.5f)				// �ړ����x
#define MODEL_ROTATE_SPEED		(0.1f)				// ��]���x

//***************************************************************************
// �O���[�o���ϐ�
//***************************************************************************
static Model			g_model[MAX_MODEL];				// ���f�����
static ModelFile		g_ModelFile[MAX_MODEL_NAME];	// ���f���t�@�C�������

//---------------------------------------------------------------------------
// ���f������������
//---------------------------------------------------------------------------
void InitModel(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���f���t�@�C�������̏�����
	memset(&g_ModelFile[0], 0, sizeof(g_ModelFile));

	// ���f�����̏�����
	memset(&g_model[0], 0, sizeof(g_model));
}

//---------------------------------------------------------------------------
// ���f���I������
//---------------------------------------------------------------------------
void UninitModel(void)
{
	for (int i = 0; i < MAX_MODEL; i++)
	{
		// ���b�V���̔j��
		if (g_model[i].pMesh != NULL)
		{
			g_model[i].pMesh->Release();
			g_model[i].pMesh = NULL;
		}

		// �}�e���A���̔j��
		if (g_model[i].pBuffer != NULL)
		{
			g_model[i].pBuffer->Release();
			g_model[i].pBuffer = NULL;
		}
	}
}

//---------------------------------------------------------------------------
// ���f���X�V����
//---------------------------------------------------------------------------
void UpdateModel(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_model[nCnt].bUse == true)
		{// �g�p���Ă���
			bool bSearchIn = false;
			bool bOnCollisionPlayer = false;

			// ���f���̈ړ�
			//MoveModel();

			//���f���̉�]
			//RotateModel();

			// �v���C���[�̎���p���ɂ��邩
			bSearchIn = SearchPlayer(&g_model[nCnt].pos);

			// �v���C���[�̓����蔻��
			D3DXVECTOR3 aVtxA = WorldCastVtx(D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMax.z), g_model[nCnt].pos, g_model[nCnt].rot);
			D3DXVECTOR3 aVtxB = WorldCastVtx(D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMax.z), g_model[nCnt].pos, g_model[nCnt].rot);
			D3DXVECTOR3 aVtxC = WorldCastVtx(D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMin.z), g_model[nCnt].pos, g_model[nCnt].rot);
			D3DXVECTOR3 aVtxD = WorldCastVtx(D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMin.z), g_model[nCnt].pos, g_model[nCnt].rot);
			CollisionPlayer(&aVtxA);
			CollisionPlayer(&aVtxB);
			CollisionPlayer(&aVtxC);
			CollisionPlayer(&aVtxD);
			CollisionFeed(&g_model[nCnt].pos, &g_model[nCnt].pos, &aVtxA, &aVtxA);
			CollisionFeed(&g_model[nCnt].pos, &g_model[nCnt].pos, &aVtxB, &aVtxB);
			CollisionFeed(&g_model[nCnt].pos, &g_model[nCnt].pos, &aVtxC, &aVtxC);
			CollisionFeed(&g_model[nCnt].pos, &g_model[nCnt].pos, &aVtxD, &aVtxD);

			if (bSearchIn == true && bOnCollisionPlayer == true)
			{// ����p���ɂ��ăv���C���[�ɓ������Ă��鎞
				g_model[nCnt].bUse = false;
			}
			
			// �e�̈ړ�
			SetPositionShadow(g_model[nCnt].nIdx, g_model[nCnt].pos, g_model[nCnt].rot,D3DXVECTOR3(g_model[nCnt].vtxMax.x - g_model[nCnt].vtxMin.x, 0.0f, g_model[nCnt].vtxMax.z - g_model[nCnt].vtxMin.z));
		}
	}
}

//---------------------------------------------------------------------------
// ���f���`�揈��
//---------------------------------------------------------------------------
void DrawModel(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans, mtxScaling;			// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9		matDef;									// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL		*pMat;									// �}�e���A���f�[�^�ւ̃|�C���^

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_model[nCnt].bUse == true)
		{// �g�p���Ă���
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_model[nCnt].mtxWorld);			// �s�񏉊����֐�

			// �����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_model[nCnt].rot.y, g_model[nCnt].rot.x, g_model[nCnt].rot.z);		// �s���]�֐�
			D3DXMatrixMultiply(&g_model[nCnt].mtxWorld, &g_model[nCnt].mtxWorld, &mtxRot);								// �s��|���Z�֐� 

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_model[nCnt].pos.x, g_model[nCnt].pos.y, g_model[nCnt].pos.z);				// �s��ړ��֐�
			D3DXMatrixMultiply(&g_model[nCnt].mtxWorld, &g_model[nCnt].mtxWorld, &mtxTrans);								// �s��|���Z�֐�

			//// �T�C�Y�̔��f
			//D3DXMatrixScaling(&mtxScaling, 0.1f, 0.1f, 0.1f);
			//D3DXMatrixMultiply(&g_model[nCnt].mtxWorld, &g_model[nCnt].mtxWorld, &mtxScaling);						// �s��|���Z�֐�

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_model[nCnt].mtxWorld);

			// ���݂̃}�e���A����ێ�
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_model[nCnt].pBuffer->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_model[nCnt].nNumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// ���f���p�[�c�̕`��
				g_model[nCnt].pMesh->DrawSubset(nCntMat);
			}

			// �ێ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//---------------------------------------------------------------------------
// ���f���ړ�����
//---------------------------------------------------------------------------
void MoveModel(int nCnt)
{
	if (GetKeyboardPress(DIK_UP)
		|| GetKeyboardPress(DIK_LEFT)
		|| GetKeyboardPress(DIK_RIGHT)
		|| GetKeyboardPress(DIK_DOWN))
	{// �ړ��L�[�������ꂽ
		if (GetKeyboardPress(DIK_UP))
		{// [��]�L�[�������ꂽ��
			if (GetKeyboardPress(DIK_LEFT))
			{// [��]�L�[�������ꂽ��
				// �ړ������̍X�V
				g_model[nCnt].rotDest.y = D3DX_PI * -0.25f;
			}
			else if (GetKeyboardPress(DIK_RIGHT))
			{// [��]�L�[�������ꂽ��
				// �ړ������̍X�V
				g_model[nCnt].rotDest.y = D3DX_PI * 0.25f;
			}
			else
			{// �ړ������̍X�V
				g_model[nCnt].rotDest.y = D3DX_PI * 0.0f;
			}
		}
		else if (GetKeyboardPress(DIK_DOWN))
		{// [��]�L�[�������ꂽ��
			if (GetKeyboardPress(DIK_LEFT))
			{// [��]�L�[�������ꂽ��
				// �ړ������̍X�V
				g_model[nCnt].rotDest.y = D3DX_PI * -0.75f;
			}
			else if (GetKeyboardPress(DIK_RIGHT))
			{// [��]�L�[�������ꂽ��
				// �ړ������̍X�V
				g_model[nCnt].rotDest.y = D3DX_PI * 0.75f;
			}
			else
			{// �ړ������̍X�V
				g_model[nCnt].rotDest.y = D3DX_PI;
			}
		}
		else if (GetKeyboardPress(DIK_LEFT))
		{// [��]�L�[�������ꂽ��
			// �ړ������̍X�V
			g_model[nCnt].rotDest.y = D3DX_PI * -0.5f;
		}
		else if (GetKeyboardPress(DIK_RIGHT))
		{// [��]�L�[�������ꂽ��
			// �ړ������̍X�V
			g_model[nCnt].rotDest.y = D3DX_PI * 0.5f;
		}

		// �J�������̎擾
		Camera *pCamera = GetCamera();

		// �ړ������̎Z�o
		g_model[nCnt].rotDest.y += pCamera->rot.y;
		if (g_model[nCnt].rotDest.y > D3DX_PI)
		{// �ړ������̐��K��
			g_model[nCnt].rotDest.y -= D3DX_PI * 2;
		}
		else if (g_model[nCnt].rotDest.y < -D3DX_PI)
		{// �ړ������̐��K��
			g_model[nCnt].rotDest.y += D3DX_PI * 2;
		}

		// ���_�ʒu�ƌ����̍X�V
		g_model[nCnt].pos.x += sinf(g_model[nCnt].rotDest.y) * MODEL_MOVE_SPEED;
		g_model[nCnt].pos.z += cosf(g_model[nCnt].rotDest.y) * MODEL_MOVE_SPEED;
		g_model[nCnt].rotDest.y -= D3DX_PI;
	}

	if (GetKeyboardPress(DIK_I))
	{// [I]�L�[�������ꂽ��
		// �ړ������̍X�V
		g_model[nCnt].pos.y += MODEL_MOVE_SPEED;
	}
	else if (GetKeyboardPress(DIK_K))
	{// [K]�L�[�������ꂽ��
		// �ړ������̍X�V
		g_model[nCnt].pos.y -= MODEL_MOVE_SPEED;
	}

	// �ړI�̌����̕␳
	if (g_model[nCnt].rotDest.y - g_model[nCnt].rot.y >= D3DX_PI)
	{// �ړ������̐��K��
		g_model[nCnt].rotDest.y -= D3DX_PI * 2;
	}
	else if (g_model[nCnt].rotDest.y - g_model[nCnt].rot.y <= -D3DX_PI)
	{// �ړ������̐��K��
		g_model[nCnt].rotDest.y += D3DX_PI * 2;
	}
}

//---------------------------------------------------------------------------
// ���f����]����
//---------------------------------------------------------------------------
void RotateModel(int nCnt)
{
	// �����̍X�V
	g_model[nCnt].rot.y += (g_model[nCnt].rotDest.y - g_model[nCnt].rot.y) * MODEL_ROTATE_SPEED;

	if (g_model[nCnt].rot.y >= D3DX_PI)
	{// �ړ������̐��K��
		g_model[nCnt].rot.y -= D3DX_PI * 2;
	}
	else if (g_model[nCnt].rot.y <= -D3DX_PI)
	{// �ړ������̐��K��
		g_model[nCnt].rot.y += D3DX_PI * 2;
	}
}

//---------------------------------------------------------------------------
// ���f���̓����蔻��	
//---------------------------------------------------------------------------
bool CollisionModel(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *vtx, D3DXVECTOR3 *vtxOld)
{
	bool bIsLanding = false;

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_model[nCnt].bUse == true)
		{// �g�p���Ă���
			//if ((int)(pos->z - size.z / 2) < (int)(g_model[nCnt].pos.z + g_model[nCnt].vtxMax.z)
			//	&& (int)(pos->z + size.z / 2) > (int)(g_model[nCnt].pos.z + g_model[nCnt].vtxMin.z)
			//	&& (int)(pos->x - size.x / 2) < (int)(g_model[nCnt].pos.x + g_model[nCnt].vtxMax.x)
			//	&& (int)(pos->x + size.x / 2) > (int)(g_model[nCnt].pos.x + g_model[nCnt].vtxMin.x))
			//{// ���f�����ɂ���(XZ��)
			//	if ((int)(posOld->y + size.y) <= (int)(g_model[nCnt].pos.y + g_model[nCnt].vtxMin.y)
			//		&& (int)(pos->y + size.y) >(int)(g_model[nCnt].pos.y + g_model[nCnt].vtxMin.y))
			//	{
			//		pos->y = g_model[nCnt].pos.y + g_model[nCnt].vtxMin.y - size.y;
			//	}
			//	if ((int)(posOld->y) >= (int)(g_model[nCnt].pos.y + g_model[nCnt].vtxMax.y)
			//		&& (int)(pos->y) < (int)(g_model[nCnt].pos.y + g_model[nCnt].vtxMax.y))
			//	{
			//		pos->y = g_model[nCnt].pos.y + g_model[nCnt].vtxMax.y;
			//	}
			//}
			//if ((int)(pos->y) < (int)(g_model[nCnt].pos.y + g_model[nCnt].vtxMax.y)
			//	&& (int)(pos->y + size.y) > (int)(g_model[nCnt].pos.y + g_model[nCnt].vtxMin.y))
			//{// ���f�����ɂ���(Y��)
			//	if ((int)(pos->z - size.z / 2) < (int)(g_model[nCnt].pos.z + g_model[nCnt].vtxMax.z)
			//		&& (int)(pos->z + size.z / 2) > (int)(g_model[nCnt].pos.z + g_model[nCnt].vtxMin.z))
			//	{// ���f�����ɂ���(Z��)
			//		if ((int)(posOld->x + size.z / 2) <= (int)(g_model[nCnt].pos.x + g_model[nCnt].vtxMin.x)
			//			&& (int)(pos->x + size.z / 2) > (int)(g_model[nCnt].pos.x + g_model[nCnt].vtxMin.x))
			//		{
			//			pos->x = g_model[nCnt].pos.x + g_model[nCnt].vtxMin.x - size.z / 2;
			//		}
			//		if ((int)(posOld->x - size.z / 2) >= (int)(g_model[nCnt].pos.x + g_model[nCnt].vtxMax.x)
			//			&& (int)(pos->x - size.z / 2) < (int)(g_model[nCnt].pos.x + g_model[nCnt].vtxMax.x))
			//		{
			//			pos->x = g_model[nCnt].pos.x + g_model[nCnt].vtxMax.x + size.z / 2;
			//		}
			//	}
			//	if ((int)(pos->x - size.x / 2) < (int)(g_model[nCnt].pos.x + g_model[nCnt].vtxMax.x)
			//		&& (int)(pos->x + size.x / 2) > (int)(g_model[nCnt].pos.x + g_model[nCnt].vtxMin.x))
			//	{// ���f�����ɂ���(X��)
			//		if ((int)(posOld->z + size.z / 2) <= (int)(g_model[nCnt].pos.z + g_model[nCnt].vtxMin.z)
			//			&& (int)(pos->z + size.z / 2) > (int)(g_model[nCnt].pos.z + g_model[nCnt].vtxMin.z))
			//		{
			//			pos->z = g_model[nCnt].pos.z + g_model[nCnt].vtxMin.z - size.z / 2;
			//		}
			//		if ((int)(posOld->z - size.z / 2) >= (int)(g_model[nCnt].pos.z + g_model[nCnt].vtxMax.z)
			//			&& (int)(pos->z - size.z / 2) < (int)(g_model[nCnt].pos.z + g_model[nCnt].vtxMax.z))
			//		{
			//			pos->z = g_model[nCnt].pos.z + g_model[nCnt].vtxMax.z + size.z / 2;
			//		}
			//	}
			//}

			// ���_�̎Z�o
			D3DXVECTOR3 aVecA = D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMax.z);
			D3DXVECTOR3 aVecB = D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMax.z);
			D3DXVECTOR3 aVecC = D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMin.z);
			D3DXVECTOR3 aVecD = D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMin.z);

			// ���_�����[���h���W�փL���X�g
			aVecA = WorldCastVtx(aVecA, g_model[nCnt].pos, g_model[nCnt].rot);
			aVecB = WorldCastVtx(aVecB, g_model[nCnt].pos, g_model[nCnt].rot);
			aVecC = WorldCastVtx(aVecC, g_model[nCnt].pos, g_model[nCnt].rot);
			aVecD = WorldCastVtx(aVecD, g_model[nCnt].pos, g_model[nCnt].rot);

			// �x�N�g���̎Z�o
			D3DXVECTOR3 aVecLineA = aVecB - aVecA;
			D3DXVECTOR3 aVecLineB = aVecC - aVecB;
			D3DXVECTOR3 aVecLineC = aVecD - aVecC;
			D3DXVECTOR3 aVecLineD = aVecA - aVecD;
			D3DXVECTOR3 aVecPosA = *vtx - aVecA;
			D3DXVECTOR3 aVecPosB = *vtx - aVecB;
			D3DXVECTOR3 aVecPosC = *vtx - aVecC;
			D3DXVECTOR3 aVecPosD = *vtx - aVecD;

			// ��r���Z�p�̕ϐ��̒�`�Ƒ��
			float fA = (aVecLineA.z * aVecPosA.x) - (aVecLineA.x * aVecPosA.z);
			float fB = (aVecLineB.z * aVecPosB.x) - (aVecLineB.x * aVecPosB.z);
			float fC = (aVecLineC.z * aVecPosC.x) - (aVecLineC.x * aVecPosC.z);
			float fD = (aVecLineD.z * aVecPosD.x) - (aVecLineD.x * aVecPosD.z);

			if (0.0f < fA
				&& 0.0f < fB
				&& 0.0f < fC
				&& 0.0f < fD)
			{// ���f���̂����ɂ���
				/*g_model[nCnt].bUse = false;
				DeleteShadow(g_model[nCnt].nIdx);*/

				// �x�N�g���̎Z�o
				aVecPosA = *vtxOld - aVecA;
				aVecPosB = *vtxOld - aVecB;
				aVecPosC = *vtxOld - aVecC;
				aVecPosD = *vtxOld - aVecD;
				
				// ��r���Z�p�̕ϐ��ɑ��
				fA = (aVecLineA.z * aVecPosA.x) - (aVecLineA.x * aVecPosA.z);
				fB = (aVecLineB.z * aVecPosB.x) - (aVecLineB.x * aVecPosB.z);
				fC = (aVecLineC.z * aVecPosC.x) - (aVecLineC.x * aVecPosC.z);
				fD = (aVecLineD.z * aVecPosD.x) - (aVecLineD.x * aVecPosD.z);

				// ����p�̕ϐ�
				D3DXVECTOR3 aJudgeVec;
				D3DXVECTOR3 aJudgeVecLine;

				if (0.0f >= fA)
				{
					aJudgeVec = aVecA;
					aJudgeVecLine = aVecLineA;
				}
				else if (0.0f >= fB)
				{
					aJudgeVec = aVecB;
					aJudgeVecLine = aVecLineB;
				}
				else if (0.0f >= fC)
				{
					aJudgeVec = aVecC;
					aJudgeVecLine = aVecLineC;
				}
				else if (0.0f >= fD)
				{
					aJudgeVec = aVecD;
					aJudgeVecLine = aVecLineD;
				}

				//D3DXVECTOR3 aVecPosOld = aJudgeVec - *posOld;
				//D3DXVECTOR3 aVecMove = *pos - *posOld;

				//// ��_�̈ʒu�̊���
				//float fIntersection = ((aVecPosOld.z * aVecMove.x) - (aVecPosOld.x * aVecMove.z))
				//	/ ((aVecMove.z * aJudgeVecLine.x) - (aVecMove.x * aJudgeVecLine.z));

				//// ��_�̎Z�o
				//pos->x = aJudgeVec.x + fIntersection * aJudgeVecLine.x;
				//pos->z = aJudgeVec.z + fIntersection * aJudgeVecLine.z;

				// ��_�̎Z�o
				pos->x = posOld->x;
				pos->z = posOld->z;

				bIsLanding = true;
			}
		}
	}

	return bIsLanding;
}

//---------------------------------------------------------------------------
// ���f���ݒ菈��
//---------------------------------------------------------------------------
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_model[nCnt].bUse == false)
		{
			// ���f�����̏�����
			g_model[nCnt].pos = pos;																// �ʒu�̏�����
			g_model[nCnt].rot = rot;																// �����̏�����
			g_model[nCnt].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									// �ړI�̌����̏�����
			g_model[nCnt].vtxMin = D3DXVECTOR3(INIT_NUM_MODEL, INIT_NUM_MODEL, INIT_NUM_MODEL);		// ���_���W�̍ŏ��l�̏�����
			g_model[nCnt].vtxMax = D3DXVECTOR3(-INIT_NUM_MODEL, -INIT_NUM_MODEL, -INIT_NUM_MODEL);	// ���_���W�̍ő�l�̏�����
			g_model[nCnt].mtxWorld = {};															// ���[���h�}�g���b�N�X
			g_model[nCnt].rotDest = {};																// �ړI�̌���
			g_model[nCnt].nType = nType;															// �^�C�v				
			g_model[nCnt].bUse = true;																// �g�p��

			// X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(&g_ModelFile[g_model[nCnt].nType].aName[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_model[nCnt].pBuffer,
				NULL,
				&g_model[nCnt].nNumMat,
				&g_model[nCnt].pMesh);

			// ���_���W�̍ŏ��l�E�ő�l�̎Z�o
			int		nNumVtx;	// ���_��
			DWORD	sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y
			BYTE	*pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^

			// ���_���̎擾
			nNumVtx = g_model[nCnt].pMesh->GetNumVertices();

			// ���_�t�H�[�}�b�g�̃T�C�Y�̎擾
			sizeFVF = D3DXGetFVFVertexSize(g_model[nCnt].pMesh->GetFVF());

			// ���_�o�b�t�@�̃��b�N
			g_model[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				// ���_���W�̑��
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				if (vtx.x < g_model[nCnt].vtxMin.x)
				{// ��r�Ώۂ����݂̒��_���W(X)�̍ŏ��l��菬����
					g_model[nCnt].vtxMin.x = vtx.x;
				}
				if (vtx.y < g_model[nCnt].vtxMin.y)
				{// ��r�Ώۂ����݂̒��_���W(Y)�̍ŏ��l��菬����
					g_model[nCnt].vtxMin.y = vtx.y;
				}
				if (vtx.z < g_model[nCnt].vtxMin.z)
				{// ��r�Ώۂ����݂̒��_���W(Z)�̍ŏ��l��菬����
					g_model[nCnt].vtxMin.z = vtx.z;
				}

				if (vtx.x > g_model[nCnt].vtxMax.x)
				{// ��r�Ώۂ����݂̒��_���W(X)�̍ő�l���傫��
					g_model[nCnt].vtxMax.x = vtx.x;
				}
				if (vtx.y > g_model[nCnt].vtxMax.y)
				{// ��r�Ώۂ����݂̒��_���W(Y)�̍ő�l���傫��
					g_model[nCnt].vtxMax.y = vtx.y;
				}
				if (vtx.z > g_model[nCnt].vtxMax.z)
				{// ��r�Ώۂ����݂̒��_���W(Z)�̍ő�l���傫��
					g_model[nCnt].vtxMax.z = vtx.z;
				}

				// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
				pVtxBuff += sizeFVF;
			}

			// ���_�o�b�t�@�̃A�����b�N
			g_model[nCnt].pMesh->UnlockVertexBuffer();

			// ���C���̐ݒ�
			SetLine(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMax.z), D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			SetLine(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMin.z), D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			SetLine(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMin.z), D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMin.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			SetLine(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMin.z), D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			
			SetLine(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMax.y, g_model[nCnt].vtxMax.z), D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMax.y, g_model[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			SetLine(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMax.y, g_model[nCnt].vtxMin.z), D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMax.y, g_model[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			SetLine(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMax.y, g_model[nCnt].vtxMin.z), D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMax.y, g_model[nCnt].vtxMin.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			SetLine(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMax.y, g_model[nCnt].vtxMin.z), D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMax.y, g_model[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			
			SetLine(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMax.z), D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMax.y, g_model[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			SetLine(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMin.z), D3DXVECTOR3(g_model[nCnt].vtxMin.x, g_model[nCnt].vtxMax.y, g_model[nCnt].vtxMin.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			SetLine(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMin.z), D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMax.y, g_model[nCnt].vtxMin.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			SetLine(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMin.y, g_model[nCnt].vtxMax.z), D3DXVECTOR3(g_model[nCnt].vtxMax.x, g_model[nCnt].vtxMax.y, g_model[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

			// �e�̐ݒ�
			g_model[nCnt].nIdx = SetShadow(g_model[nCnt].pos, g_model[nCnt].rot, D3DXVECTOR3(g_model[nCnt].vtxMax.x - g_model[nCnt].vtxMin.x, 0.0f, g_model[nCnt].vtxMax.z - g_model[nCnt].vtxMin.z));

			break;
		}
	}
}

//---------------------------------------------------------------------------
// ���f���擾����
//---------------------------------------------------------------------------
Model *GetModel(void)
{
	return &g_model[0];
}

//---------------------------------------------------------------------------
// ���f���t�@�C���擾����
//---------------------------------------------------------------------------
ModelFile *GetModelFile(void)
{
	return &g_ModelFile[0];
}