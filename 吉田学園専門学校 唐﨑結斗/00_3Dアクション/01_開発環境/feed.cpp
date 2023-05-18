//**************************************************************************************************
//
// �a�`�揈��(feed.cpp)
// Auther�F�������l
//
//**************************************************************************************************

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"
#include "feed.h"
#include"file.h"
#include"input.h"
#include"camera.h"
#include"shadow.h"
#include"billboard.h"
#include"effect.h"
#include"line.h"
#include"calculation.h"
#include<time.h>
#include"player.h"
#include"score.h"
#include"particle.h"
#include"model.h"
#include"sound.h"

//***************************************************************************
// �}�N����`
//***************************************************************************
#define INIT_NUM_FEED			(10000)							// ���_���W�̍ő�ŏ��̏����l
#define FEED_MOVE_SPEED			(0.5f)							// �ړ����x
#define FEED_ROTATE_SPEED		(0.1f)							// ��]���x
#define SEARCH_RANGE_LENGTH		(100.0f)						// �{���͈͂̋���
#define LEAVE_RANGE_LENGTH		(25.0f)							// �����͈͂̋���
#define SEARCH_PLAYER_LENGTH	(150.0f)						// ���G�͈͂̋���
#define SEARCH_RANGE_ROT		(0.5f)							// �{���͈͂̊p�x
#define LEAVE_RANGE_ROT			(SEARCH_RANGE_ROT * 1.5f)		// �{���͈͂̊p�x
#define SEARCH_PLAYER_SPEED		(0.8f)							// ���G�͈͂̑��x
#define JOINT_TIME				(30)							// �������s���܂ł̎���
#define MOVE_TIME				(600)							// �ړ��ʎZ�o�܂ł̎���
#define MAX_SPEED				(0.5f)							// �ړ����x�̍ő�
#define MAX_MOVE_ROT			(0.15f)							// �ړ������̍ő�
#define MAX_COMBO_TIME_FEED		(120)							// �R���{���Z����
#define MIN_SET_FEED			(30)							// �ŏ��ݒu��
#define MAX_SET_FEED			(60)							// �ő�ݒu��
#define MAX_SET_POS_FEED		(400 * 2)						// �ݒu�͈�

//***************************************************************************
// �O���[�o���ϐ�
//***************************************************************************
static Feed			g_Feed[MAX_FEED];				// �a���
static FeedFile		g_FeedFile;						// �a�t�@�C�������
static int			g_nCntFeed = 0;					// �g�p����Ă�a�̐�

//---------------------------------------------------------------------------
// �a����������
//---------------------------------------------------------------------------
void InitFeed(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nCntFeed = 0;

	//�����̏�����
	srand((unsigned int)time(0));

	// �a�t�@�C�������̏�����
	memset(&g_FeedFile, 0, sizeof(g_FeedFile));

	// �a���̏�����
	memset(&g_Feed[0], 0, sizeof(g_Feed));
}

//---------------------------------------------------------------------------
// �a�I������
//---------------------------------------------------------------------------
void UninitFeed(void)
{
	for (int i = 0; i < MAX_FEED; i++)
	{
		// ���b�V���̔j��
		if (g_Feed[i].pMesh != NULL)
		{
			g_Feed[i].pMesh->Release();
			g_Feed[i].pMesh = NULL;
		}

		// �}�e���A���̔j��
		if (g_Feed[i].pBuffer != NULL)
		{
			g_Feed[i].pBuffer->Release();
			g_Feed[i].pBuffer = NULL;
		}
	}
}

//---------------------------------------------------------------------------
// �a�X�V����
//---------------------------------------------------------------------------
void UpdateFeed(void)
{
	for (int nCnt = 0; nCnt < MAX_FEED; nCnt++)
	{
		if (g_Feed[nCnt].bUse == true)
		{// �g�p���Ă���
			// �ߋ��ʒu�̍X�V
			g_Feed[nCnt].posOld = g_Feed[nCnt].pos;

			// ����p�̕ϐ�
			g_Feed[nCnt].bSearchIn = false;
			bool bOnCollisionPlayer = false;

			// �v���C���[�̎���p���ɂ��邩
			g_Feed[nCnt].bSearchIn = SearchPlayer(&g_Feed[nCnt].pos);

			// �v���C���[�̓����蔻��
			D3DXVECTOR3 aVtxA = WorldCastVtx(D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMax.z), g_Feed[nCnt].pos, g_Feed[nCnt].rot);
			D3DXVECTOR3 aVtxB = WorldCastVtx(D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMax.z), g_Feed[nCnt].pos, g_Feed[nCnt].rot);
			D3DXVECTOR3 aVtxC = WorldCastVtx(D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMin.z), g_Feed[nCnt].pos, g_Feed[nCnt].rot);
			D3DXVECTOR3 aVtxD = WorldCastVtx(D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMin.z), g_Feed[nCnt].pos, g_Feed[nCnt].rot);

			if (g_Feed[nCnt].bSearchIn == false)
			{// ����O�̎�
				CollisionPlayer(&aVtxA);
				CollisionPlayer(&aVtxB);
				CollisionPlayer(&aVtxC);
				CollisionPlayer(&aVtxD);
			}

			bOnCollisionPlayer = EatPlayer(&g_Feed[nCnt].pos, g_Feed[nCnt].vtxMax - g_Feed[nCnt].vtxMin);

			MODE mode = GetMode();

			if (mode == MODE_GAME)
			{// �Q�[���̎�
				if (g_Feed[nCnt].bSearchIn == true && bOnCollisionPlayer == true)
				{// ����p���ɂ��ăv���C���[�ɓ������Ă��鎞
					g_Feed[nCnt].bUse = false;
					DeleteShadow(g_Feed[nCnt].nIdx);
					g_nCntFeed--;

					// �v���C���[���̎擾
					Player *pPlayer = GetPlayer();

					// �R���{���Z
					pPlayer->nCntCombo++;

					// �R���{���Z���Ԃ̍X�V
					pPlayer->nCntComboTime = MAX_COMBO_TIME_FEED;

					// �X�^�~�i���C���N�������g
					pPlayer->nStamina += 3;

					if (pPlayer->nStamina >= pPlayer->nMaxStamina)
					{// �X�^�~�i���ő�l�ɌŒ�
						pPlayer->nStamina = pPlayer->nMaxStamina;
					}

					//�X�R�A�̉��Z
					AddScore(200 + 100 * pPlayer->nCntCombo);

					// �p�[�e�B�N���̐ݒu
					SetParticle(g_Feed[nCnt].pos,
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						D3DXVECTOR3(1.0f, 1.0f, 0.0f),
						D3DXCOLOR(0.01f, 1.0f, 1.0f, 1.0f),
						5.0f,
						2.0f,
						0.0f,
						60,
						0,
						1,
						30,
						20,
						false);

					//�T�E���h�̍Đ�
					PlaySound(SOUND_LABEL_SE_DAMAGE001);
				}

				// �v���C���[���瓦���鏈��
				LeavePlayer(nCnt);
			}

			if (g_Feed[nCnt].bEscape == false)
			{// �����Ă��Ȃ��Ƃ�
				// ���[�_�[�̑{��
				SearchLeader(nCnt);

				// ����
				LeaveFeed(nCnt);
			}

			// ����
			AverageFeed(nCnt);

			// �a�̈ړ�
			MoveFeed(nCnt);

			//�a�̉�]
			RotateFeed(nCnt);

			if (CollisionModel(&g_Feed[nCnt].pos, &g_Feed[nCnt].posOld, &aVtxA, &aVtxA) == true
				|| CollisionModel(&g_Feed[nCnt].pos, &g_Feed[nCnt].posOld, &aVtxB, &aVtxB) == true
				|| CollisionModel(&g_Feed[nCnt].pos, &g_Feed[nCnt].posOld, &aVtxC, &aVtxC) == true
				|| CollisionModel(&g_Feed[nCnt].pos, &g_Feed[nCnt].posOld, &aVtxD, &aVtxD) == true)
			{
				g_Feed[nCnt].bUse = false;
				DeleteShadow(g_Feed[nCnt].nIdx);
			}

			// �e�̈ړ�
			SetPositionShadow(g_Feed[nCnt].nIdx, g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMax.x - g_Feed[nCnt].vtxMin.x, 0.0f, g_Feed[nCnt].vtxMax.z - g_Feed[nCnt].vtxMin.z));
		}
	}
}

//---------------------------------------------------------------------------
// �a�`�揈��
//---------------------------------------------------------------------------
void DrawFeed(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9		matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL		*pMat;						// �}�e���A���f�[�^�ւ̃|�C���^

	for (int nCnt = 0; nCnt < MAX_FEED; nCnt++)
	{
		if (g_Feed[nCnt].bUse == true)
		{// �g�p���Ă���
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Feed[nCnt].mtxWorld);			// �s�񏉊����֐�

			// �����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Feed[nCnt].rot.y, g_Feed[nCnt].rot.x, g_Feed[nCnt].rot.z);		// �s���]�֐�
			D3DXMatrixMultiply(&g_Feed[nCnt].mtxWorld, &g_Feed[nCnt].mtxWorld, &mtxRot);								// �s��|���Z�֐� 

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Feed[nCnt].pos.x, g_Feed[nCnt].pos.y, g_Feed[nCnt].pos.z);				// �s��ړ��֐�
			D3DXMatrixMultiply(&g_Feed[nCnt].mtxWorld, &g_Feed[nCnt].mtxWorld, &mtxTrans);								// �s��|���Z�֐�

			//// �T�C�Y�̔��f
			//D3DXMatrixScaling()

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Feed[nCnt].mtxWorld);

			// ���݂̃}�e���A����ێ�
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Feed[nCnt].pBuffer->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Feed[nCnt].nNumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				/*if (g_Feed[nCnt].bSearchIn == true)
				{
					D3DMATERIAL9  matD3D = pMat[nCntMat].MatD3D;
					matD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					pDevice->SetMaterial(&matD3D);
				}
				else
				{
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				}*/

				// �a�p�[�c�̕`��
				g_Feed[nCnt].pMesh->DrawSubset(nCntMat);
			}

			// �ێ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//---------------------------------------------------------------------------
// �a�ړ�����
//---------------------------------------------------------------------------
void MoveFeed(int nCnt)
{
	// �ړ��ʂ̎Z�o
	if (g_Feed[nCnt].bEscape == false)
	{// �����Ă��Ȃ�
		g_Feed[nCnt].nCntMoveTime++;
		if (g_Feed[nCnt].nCntMoveTime >= MOVE_TIME)
		{// �ړ��ʂƑ��x�̎Z�o
			// �ړ�����
			if (g_Feed[nCnt].nIdxLeader == -1)
			{
				float fRotMove = ((D3DX_PI * MAX_MOVE_ROT)) - (float)(rand() % (int)(((D3DX_PI * MAX_MOVE_ROT) * 2.0f) * 100.0f) / 100.0f);

				// �ړ��ʂ̎Z�o
				g_Feed[nCnt].move.x = sinf(g_Feed[nCnt].rot.y + fRotMove);
				g_Feed[nCnt].move.z = cosf(g_Feed[nCnt].rot.y + fRotMove);
				D3DXVec3Normalize(&g_Feed[nCnt].move, &g_Feed[nCnt].move);
			}

			// �ړ����x
			g_Feed[nCnt].fSpeed = (float)(rand() % (int)(MAX_SPEED * 100.0f) / 100.0f);

			// �J�E���g�̏�����
			g_Feed[nCnt].nCntMoveTime = 0;
		}
	}

	g_Feed[nCnt].move += g_Feed[nCnt].joinVec + g_Feed[nCnt].leaveVec + g_Feed[nCnt].averageVec;
	D3DXVec3Normalize(&g_Feed[nCnt].move, &g_Feed[nCnt].move);		// �x�N�g����傫��1

	// �ړ������̎Z�o
	float fDestRot = atan2f((g_Feed[nCnt].move.x + g_Feed[nCnt].pos.x) - g_Feed[nCnt].pos.x,
		(g_Feed[nCnt].move.z + g_Feed[nCnt].pos.z) - g_Feed[nCnt].pos.z);

	// �ړ������̐��K��
	g_Feed[nCnt].rotDest.y = RotNormalization(fDestRot - D3DX_PI);

	// �ʒu�̍X�V
	g_Feed[nCnt].pos += (g_Feed[nCnt].move * g_Feed[nCnt].fSpeed);
}

//---------------------------------------------------------------------------
// �a��]����
//---------------------------------------------------------------------------
void RotateFeed(int nCnt)
{
	// �����̍X�V
	g_Feed[nCnt].rot.y += (g_Feed[nCnt].rotDest.y - g_Feed[nCnt].rot.y) * FEED_ROTATE_SPEED;

	// ���K��
	g_Feed[nCnt].rot.y = RotNormalization(g_Feed[nCnt].rot.y);
}

//---------------------------------------------------------------------------
// �a�̓����蔻��	
//---------------------------------------------------------------------------
void CollisionFeed(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *vtx, D3DXVECTOR3 *vtxOld)
{
	for (int nCnt = 0; nCnt < MAX_FEED; nCnt++)
	{
		if (g_Feed[nCnt].bUse == true && g_Feed[nCnt].bSearchIn != true)
		{// �g�p���Ă���
			// ���_�̎Z�o
			D3DXVECTOR3 aVecA = D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMax.z);
			D3DXVECTOR3 aVecB = D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMax.z);
			D3DXVECTOR3 aVecC = D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMin.z);
			D3DXVECTOR3 aVecD = D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMin.z);

			// ���_�����[���h���W�փL���X�g
			aVecA = WorldCastVtx(aVecA, g_Feed[nCnt].pos, g_Feed[nCnt].rot);
			aVecB = WorldCastVtx(aVecB, g_Feed[nCnt].pos, g_Feed[nCnt].rot);
			aVecC = WorldCastVtx(aVecC, g_Feed[nCnt].pos, g_Feed[nCnt].rot);
			aVecD = WorldCastVtx(aVecD, g_Feed[nCnt].pos, g_Feed[nCnt].rot);

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
			 /*g_Feed[nCnt].bUse = false;
			 DeleteShadow(g_Feed[nCnt].nIdx);*/

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
			}
		}
	}
}

//---------------------------------------------------------------------------
// ���[�_�[�̑{������
//---------------------------------------------------------------------------
void SearchLeader(int nCnt)
{
	// �p�x�̎Z�o
	float fSearchRot = (D3DX_PI * SEARCH_RANGE_ROT);
	float fDistanceMin = (float)(INIT_NUM_FEED);
	float fJoinRot = 0.0f;
	int nCntSearchIn = 0;

	// �����܂ł̃J�E���g�̃C���N�������g
	g_Feed[nCnt].nCntJoinTime++;

	for (int nCntFeed = 0; nCntFeed < MAX_FEED; nCntFeed++)
	{
		if (nCntFeed != nCnt && g_Feed[nCntFeed].bUse == true)
		{// �����ȊO�̎�
			bool bSearch = false;

			// ���Ԃ̂������
			float fFellowRot = atan2f(g_Feed[nCnt].pos.x - g_Feed[nCntFeed].pos.x, g_Feed[nCnt].pos.z - g_Feed[nCntFeed].pos.z);

			// ��r�p�̌����̎Z�o
			float fSearchRotRight = g_Feed[nCnt].rot.y - fSearchRot;
			float fSRROld = fSearchRotRight;
			fSearchRotRight = RotNormalization(fSearchRotRight);
	
			float fSearchRotLeft = g_Feed[nCnt].rot.y + fSearchRot;
			float fSRLOld = fSearchRotLeft;
			fSearchRotLeft = RotNormalization(fSearchRotLeft);

			if (fSRROld == fSearchRotRight && fSRLOld == fSearchRotLeft)
			{// ���K���O�̐��l�������ꍇ
				if (fSearchRotRight <= fFellowRot
					&& fSearchRotLeft >= fFellowRot)
				{// ���������o
					bSearch = true;
				}
			}
			else
			{// ���K���O�̐��l���Ⴄ
				if (fSearchRotRight <= fFellowRot
					|| fSearchRotLeft >= fFellowRot)
				{// ���������o
					bSearch = true;
				}
			}

			// �ڕW�܂ł̋���
			D3DXVECTOR3 distance = g_Feed[nCntFeed].pos - g_Feed[nCnt].pos;
			float fDistance = sqrtf((distance.x * distance.x) + (distance.z * distance.z));

			if (bSearch == true
				&& fDistance <= SEARCH_RANGE_LENGTH)
			{// �{���͈͓�����������
				// �����̕���
				fFellowRot = atan2f(g_Feed[nCntFeed].pos.x - g_Feed[nCnt].pos.x, g_Feed[nCntFeed].pos.z - g_Feed[nCnt].pos.z);

				// �����܂ł̋���
				float fFeedDistance = sqrtf((g_Feed[nCntFeed].pos.x - g_Feed[nCnt].pos.x) * (g_Feed[nCntFeed].pos.x - g_Feed[nCnt].pos.x)
					+ (g_Feed[nCntFeed].pos.z - g_Feed[nCnt].pos.z) * (g_Feed[nCntFeed].pos.z - g_Feed[nCnt].pos.z));

				// �����ւ̌��������Z
				fJoinRot += fFellowRot;

				// �͈͓��̖����̐������Z
				nCntSearchIn++;

				if (fDistanceMin > fFeedDistance)
				{// �������Z�����
					g_Feed[nCnt].nGroup = g_Feed[nCntFeed].nGroup;						// �O���[�v
					g_Feed[nCnt].nIdxLeader = g_Feed[nCntFeed].nGroup;					// ���[�_�[
					fDistanceMin = fFeedDistance;										// ��ԋ߂��ڕW
				}
			}
		}
	}

	if (nCntSearchIn > 0)
	{// �͈͓��ɖ���������Ƃ�
		// ���������̕��ς��Z�o
		g_Feed[nCnt].fJoinRot = fJoinRot / nCntSearchIn;
		g_Feed[nCnt].fJoinRot = RotNormalization(g_Feed[nCnt].fJoinRot - D3DX_PI);

		// �����x�N�g���̎Z�o
		g_Feed[nCnt].joinVec.x = sinf(g_Feed[nCnt].fJoinRot - D3DX_PI);
		g_Feed[nCnt].joinVec.z = cosf(g_Feed[nCnt].fJoinRot - D3DX_PI);

		// ����
		if (g_Feed[nCnt].nCntJoinTime >= JOINT_TIME)
		{// ���̎��Ԍo�߂���
			// �����x�N�g���̎Z�o
			g_Feed[nCnt].joinVec.x = sinf(g_Feed[nCnt].fJoinRot - D3DX_PI);
			g_Feed[nCnt].joinVec.z = cosf(g_Feed[nCnt].fJoinRot - D3DX_PI);
			g_Feed[nCnt].nCntJoinTime = 0;		// �����܂ł̃J�E���g��������
			D3DXVec3Normalize(&g_Feed[nCnt].joinVec, &g_Feed[nCnt].joinVec);
		}
	}
	else
	{// �͈͓��ɖ��������Ȃ�
		g_Feed[nCnt].nIdxLeader = -1;										// ���[�_�[
		g_Feed[nCnt].nGroup = nCnt;											// �O���[�v
		g_Feed[nCnt].fJoinRot = 0.0f;										// ��������

		// �����x�N�g���̎Z�o
		g_Feed[nCnt].joinVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVec3Normalize(&g_Feed[nCnt].joinVec, &g_Feed[nCnt].joinVec);
	}
}

//---------------------------------------------------------------------------
// ��������
//---------------------------------------------------------------------------
void LeaveFeed(int nCnt)
{
	// �p�x�̎Z�o
	float fSearchRot = (D3DX_PI * LEAVE_RANGE_ROT);
	float fDistanceMin = (float)(INIT_NUM_FEED);
	int nCntSearchIn = 0;

	for (int nCntFeed = 0; nCntFeed < MAX_FEED; nCntFeed++)
	{
		if (nCntFeed != nCnt && g_Feed[nCntFeed].bUse == true)
		{// �����ȊO�̎�
			bool bSearch = false;

			// ���Ԃ̂������
			float fFellowRot = atan2f(g_Feed[nCnt].pos.x - g_Feed[nCntFeed].pos.x, g_Feed[nCnt].pos.z - g_Feed[nCntFeed].pos.z);

			// ��r�p�̌����̎Z�o
			float fSearchRotRight = g_Feed[nCnt].rot.y - fSearchRot;
			float fSRROld = fSearchRotRight;
			fSearchRotRight = RotNormalization(fSearchRotRight);

			float fSearchRotLeft = g_Feed[nCnt].rot.y + fSearchRot;
			float fSRLOld = fSearchRotLeft;
			fSearchRotLeft = RotNormalization(fSearchRotLeft);

			if (fSRROld == fSearchRotRight && fSRLOld == fSearchRotLeft)
			{// ���K���O�̐��l�������ꍇ
				if (fSearchRotRight <= fFellowRot
					&& fSearchRotLeft >= fFellowRot)
				{// ���������o
					bSearch = true;
				}
			}
			else
			{// ���K���O�̐��l���Ⴄ
				if (fSearchRotRight <= fFellowRot
					|| fSearchRotLeft >= fFellowRot)
				{// ���������o
					bSearch = true;
				}
			}

			// �ڕW�܂ł̋���
			D3DXVECTOR3 distance = g_Feed[nCntFeed].pos - g_Feed[nCnt].pos;
			float fDistance = sqrtf((distance.x * distance.x) + (distance.z * distance.z));

			if (bSearch == true
				&& fDistance <= LEAVE_RANGE_LENGTH)
			{// �{���͈͓�����������
				float fFeedDistance = sqrtf((g_Feed[nCntFeed].pos.x - g_Feed[nCnt].pos.x) * (g_Feed[nCntFeed].pos.x - g_Feed[nCnt].pos.x)
					+ (g_Feed[nCntFeed].pos.z - g_Feed[nCnt].pos.z) * (g_Feed[nCntFeed].pos.z - g_Feed[nCnt].pos.z));

				// �͈͓��Ɍ���������ꍇ
				nCntSearchIn++;

				if (fDistanceMin > fFeedDistance)
				{// �������Z�����
					fDistanceMin = fFeedDistance;
					g_Feed[nCnt].fLeaveRot = fFellowRot;
					g_Feed[nCnt].fLeaveRot = RotNormalization(g_Feed[nCnt].fLeaveRot - D3DX_PI);
					g_Feed[nCnt].leaveVec.x = sinf(g_Feed[nCnt].fLeaveRot - D3DX_PI);
					g_Feed[nCnt].leaveVec.z = cosf(g_Feed[nCnt].fLeaveRot - D3DX_PI);
					D3DXVec3Normalize(&g_Feed[nCnt].leaveVec, &g_Feed[nCnt].leaveVec);
				}
			}
		}
	}

	if(nCntSearchIn == 0)
	{// �{���͈͂ɖ��������Ȃ�
		g_Feed[nCnt].leaveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Feed[nCnt].fLeaveRot = 0.0f;
	}
}

//---------------------------------------------------------------------------
// ��������
//---------------------------------------------------------------------------
void AverageFeed(int nCnt)
{
	float fSearchRot = (D3DX_PI * SEARCH_RANGE_ROT);
	D3DXVECTOR3 average = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int nCntSearchIn = 0;

	for (int nCntFeed = 0; nCntFeed < MAX_FEED; nCntFeed++)
	{
		if (nCntFeed != nCnt && g_Feed[nCntFeed].bUse == true)
		{// �����ȊO�̎�
			bool bSearch = false;

			// ���Ԃ̂������
			float fFellowRot = atan2f(g_Feed[nCnt].pos.x - g_Feed[nCntFeed].pos.x, g_Feed[nCnt].pos.z - g_Feed[nCntFeed].pos.z);

			// ��r�p�̌����̎Z�o
			float fSearchRotRight = g_Feed[nCnt].rot.y - fSearchRot;
			float fSRROld = fSearchRotRight;
			fSearchRotRight = RotNormalization(fSearchRotRight);
			float fSearchRotLeft = g_Feed[nCnt].rot.y + fSearchRot;
			float fSRLOld = fSearchRotLeft;
			fSearchRotLeft = RotNormalization(fSearchRotLeft);

			if (fSRROld == fSearchRotRight && fSRLOld == fSearchRotLeft)
			{// ���K���O�̐��l�������ꍇ
				if (fSearchRotRight <= fFellowRot
					&& fSearchRotLeft >= fFellowRot)
				{// ���������o
					bSearch = true;
				}
			}
			else
			{// ���K���O�̐��l���Ⴄ
				if (fSearchRotRight <= fFellowRot
					|| fSearchRotLeft >= fFellowRot)
				{// ���������o
					bSearch = true;
				}
			}

			// �ڕW�܂ł̋���
			D3DXVECTOR3 distance = g_Feed[nCntFeed].pos - g_Feed[nCnt].pos;
			float fDistance = sqrtf((distance.x * distance.x) + (distance.z * distance.z));

			if (bSearch == true
				&& fDistance <= LEAVE_RANGE_LENGTH)
			{// �{���͈͓�����������
				float fFeedDistance = sqrtf((g_Feed[nCntFeed].pos.x - g_Feed[nCnt].pos.x) * (g_Feed[nCntFeed].pos.x - g_Feed[nCnt].pos.x)
					+ (g_Feed[nCntFeed].pos.z - g_Feed[nCnt].pos.z) * (g_Feed[nCntFeed].pos.z - g_Feed[nCnt].pos.z));

				// �͈͓��Ɍ���������ꍇ
				nCntSearchIn++;

				// ���ςɉ��Z
				average += g_Feed[nCntFeed].move + g_Feed[nCntFeed].joinVec + g_Feed[nCntFeed].leaveVec;
			}
		}
	}

	if (nCntSearchIn > 0 && g_Feed[nCnt].nIdxLeader != -1)
	{// �͈͓��ɖ���������
		// ���ϕ����̎Z�o
		g_Feed[nCnt].averageVec = average / (float)(nCntSearchIn);
		D3DXVec3Normalize(&g_Feed[nCnt].averageVec, &g_Feed[nCnt].averageVec);
	}
	else
	{// �͈͓��ɖ��������Ȃ�
		// ���ϕ�����������
		g_Feed[nCnt].averageVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//---------------------------------------------------------------------------
// �v���C���[���瓦���鏈��
//---------------------------------------------------------------------------
void LeavePlayer(int nCnt)
{
	// �v���C���[���̎擾
	Player *pPlayer = GetPlayer();

	// �ڕW�܂ł̋���
	D3DXVECTOR3 distance = pPlayer->pos - g_Feed[nCnt].pos;
	float fDistance = sqrtf((distance.x * distance.x) + (distance.z * distance.z));

	if (fDistance <= SEARCH_PLAYER_LENGTH)
	{// ���G�͈͂ɓG������
		// ���Ԃ̂������
		D3DXVECTOR3 distance = g_Feed[nCnt].pos - pPlayer->pos;
		float fFellowRot = atan2f(distance.x, distance.z);

		// �ړ������̎Z�o
		g_Feed[nCnt].move.x = sinf(fFellowRot);
		g_Feed[nCnt].move.z = cosf(fFellowRot);

		// �����ƕ�����������
		g_Feed[nCnt].joinVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Feed[nCnt].leaveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �ړ��ʂ̉��Z
		g_Feed[nCnt].pos += g_Feed[nCnt].move * SEARCH_PLAYER_SPEED;

		// ������
		g_Feed[nCnt].bEscape = true;
	}
	else
	{
		g_Feed[nCnt].bEscape = false;
	}
}

//---------------------------------------------------------------------------
// �a�ݒ菈��
//---------------------------------------------------------------------------
void SetFeed(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_FEED; nCnt++)
	{
		if (g_Feed[nCnt].bUse == false)
		{
			// �t�@�C���ϐ��̐錾�Ƒ��
			char aFile[128] = FILE_MODEL_DATA;
			strcat(aFile, "��.x");

			// �a���̏�����
			g_Feed[nCnt].pos = pos;																// �ʒu�̏�����
			g_Feed[nCnt].posOld = g_Feed[nCnt].pos;												// �ߋ��ʒu�̏�����
			g_Feed[nCnt].rot = rot;																// �����̏�����
			g_Feed[nCnt].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// �ړI�̌����̏�����
			g_Feed[nCnt].joinVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// �����̃x�N�g���̏�����
			g_Feed[nCnt].leaveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// �����x�N�g���̏�����
			g_Feed[nCnt].averageVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// ���σx�N�g���̏�����
			g_Feed[nCnt].nGroup = -1;															// �O���[�v�ԍ�
			g_Feed[nCnt].nIdxLeader = -1;														// ���[�_�[�ԍ�
			g_Feed[nCnt].vtxMin = D3DXVECTOR3(INIT_NUM_FEED, INIT_NUM_FEED, INIT_NUM_FEED);		// ���_���W�̍ŏ��l�̏�����
			g_Feed[nCnt].vtxMax = D3DXVECTOR3(-INIT_NUM_FEED, -INIT_NUM_FEED, -INIT_NUM_FEED);	// ���_���W�̍ő�l�̏�����
			g_Feed[nCnt].mtxWorld = {};															// ���[���h�}�g���b�N�X	
			g_Feed[nCnt].fSpeed = 0.5f;															// �ړ����x
			g_Feed[nCnt].fJoinRot = 0.0f;														// ��������
			g_Feed[nCnt].fLeaveRot = 0.0f;														// ��������
			g_Feed[nCnt].nCntJoinTime = 0;														// �����܂ł̎���
			g_Feed[nCnt].nCntMoveTime = 0;														// �ړ��ʎZ�o�܂ł̃J�E���g
			g_Feed[nCnt].bUse = true;															// �g�p��
			g_Feed[nCnt].bEscape = false;														// �����Ă��Ȃ�

			// �ړ��ʂ̎Z�o
			g_Feed[nCnt].move.x = sinf(g_Feed[nCnt].rot.y);
			g_Feed[nCnt].move.z = cosf(g_Feed[nCnt].rot.y);
			D3DXVec3Normalize(&g_Feed[nCnt].move, &g_Feed[nCnt].move);

			// X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(&aFile[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Feed[nCnt].pBuffer,
				NULL,
				&g_Feed[nCnt].nNumMat,
				&g_Feed[nCnt].pMesh);

			// ���_���W�̍ŏ��l�E�ő�l�̎Z�o
			int		nNumVtx;	// ���_��
			DWORD	sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y
			BYTE	*pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^

			// ���_���̎擾
			nNumVtx = g_Feed[nCnt].pMesh->GetNumVertices();

			// ���_�t�H�[�}�b�g�̃T�C�Y�̎擾
			sizeFVF = D3DXGetFVFVertexSize(g_Feed[nCnt].pMesh->GetFVF());

			// ���_�o�b�t�@�̃��b�N
			g_Feed[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				// ���_���W�̑��
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				if (vtx.x < g_Feed[nCnt].vtxMin.x)
				{// ��r�Ώۂ����݂̒��_���W(X)�̍ŏ��l��菬����
					g_Feed[nCnt].vtxMin.x = vtx.x;
				}
				if (vtx.y < g_Feed[nCnt].vtxMin.y)
				{// ��r�Ώۂ����݂̒��_���W(Y)�̍ŏ��l��菬����
					g_Feed[nCnt].vtxMin.y = vtx.y;
				}
				if (vtx.z < g_Feed[nCnt].vtxMin.z)
				{// ��r�Ώۂ����݂̒��_���W(Z)�̍ŏ��l��菬����
					g_Feed[nCnt].vtxMin.z = vtx.z;
				}

				if (vtx.x > g_Feed[nCnt].vtxMax.x)
				{// ��r�Ώۂ����݂̒��_���W(X)�̍ő�l���傫��
					g_Feed[nCnt].vtxMax.x = vtx.x;
				}
				if (vtx.y > g_Feed[nCnt].vtxMax.y)
				{// ��r�Ώۂ����݂̒��_���W(Y)�̍ő�l���傫��
					g_Feed[nCnt].vtxMax.y = vtx.y;
				}
				if (vtx.z > g_Feed[nCnt].vtxMax.z)
				{// ��r�Ώۂ����݂̒��_���W(Z)�̍ő�l���傫��
					g_Feed[nCnt].vtxMax.z = vtx.z;
				}

				// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
				pVtxBuff += sizeFVF;
			}

			// ���_�o�b�t�@�̃A�����b�N
			g_Feed[nCnt].pMesh->UnlockVertexBuffer();

			// ���C���̐ݒ�
			//SetLine(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMax.z), D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//SetLine(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMin.z), D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//SetLine(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMin.z), D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMin.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//SetLine(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMin.z), D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//SetLine(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMax.y, g_Feed[nCnt].vtxMax.z), D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMax.y, g_Feed[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//SetLine(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMax.y, g_Feed[nCnt].vtxMin.z), D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMax.y, g_Feed[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//SetLine(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMax.y, g_Feed[nCnt].vtxMin.z), D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMax.y, g_Feed[nCnt].vtxMin.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//SetLine(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMax.y, g_Feed[nCnt].vtxMin.z), D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMax.y, g_Feed[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//SetLine(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMax.z), D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMax.y, g_Feed[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//SetLine(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMin.z), D3DXVECTOR3(g_Feed[nCnt].vtxMin.x, g_Feed[nCnt].vtxMax.y, g_Feed[nCnt].vtxMin.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//SetLine(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMin.z), D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMax.y, g_Feed[nCnt].vtxMin.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			//SetLine(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMin.y, g_Feed[nCnt].vtxMax.z), D3DXVECTOR3(g_Feed[nCnt].vtxMax.x, g_Feed[nCnt].vtxMax.y, g_Feed[nCnt].vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

			// �e�̐ݒ�
			g_Feed[nCnt].nIdx = SetShadow(g_Feed[nCnt].pos, g_Feed[nCnt].rot, D3DXVECTOR3(g_Feed[nCnt].vtxMax.x - g_Feed[nCnt].vtxMin.x, 0.0f, g_Feed[nCnt].vtxMax.z - g_Feed[nCnt].vtxMin.z));

			g_nCntFeed++;

			break;
		}
	}
}

//---------------------------------------------------------------------------
// �a�͈̔͐ݒu����
//---------------------------------------------------------------------------
void RandSetFeed(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSetRot, float fSetLength, int nNumSet)
{
	// �擪�̔z�u
	SetFeed(pos, rot);

	for (int nCntFeed = 0; nCntFeed < nNumSet - 1; nCntFeed++)
	{
		// �ϐ��錾
		float fSetRandRot = ((D3DX_PI * fSetRot) / 2.0f) - (float)(rand() % (int)(((D3DX_PI * fSetRot)) * 100.0f) / 100.0f);		// �Q��̒��S����̊p�x
		float fSetRandLength = (float)(rand() % (int)(fSetLength * 100.0f) / 100.0f);												// �Q��̒��S����̋���
		
		// �ʒu�̎Z�o
		D3DXVECTOR3 setPos = D3DXVECTOR3(pos.x + sinf(rot.y + fSetRandRot) * fSetRandLength,
			0.0f,
			pos.z + cosf(rot.y + fSetRandRot) * fSetRandLength);

		// �z�u
		SetFeed(setPos, rot);
	}
}

//---------------------------------------------------------------------------
// �a�̎����͈͐ݒu����
//---------------------------------------------------------------------------
void SetControllerFeed(void)
{
	if (g_nCntFeed <= MIN_SET_FEED)
	{// �ݒu�����ŏ�������������ꍇ
		while (g_nCntFeed < MAX_SET_FEED)
		{
			// �ʒu�̎Z�o
			D3DXVECTOR3 pos = D3DXVECTOR3((float)(-(int)(MAX_SET_POS_FEED / 2.0f) + rand() % ((int)(MAX_SET_POS_FEED)+1)),
				0.0f,
				(float)(-(int)(MAX_SET_POS_FEED / 2.0f) + rand() % ((int)(MAX_SET_POS_FEED)+1)));

			// �����̎Z�o
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, (D3DX_PI * 2 / 2.0f) - (float)(rand() % (int)((D3DX_PI * 2) * 100.0f) / 100.0f), 0.0f);

			// �ݒu�͈�(����)�̎Z�o
			float fRot = (D3DX_PI * 2 / 2.0f) - (float)(rand() % (int)((D3DX_PI * 2 + 1) * 100.0f) / 100.0f);

			// �ݒu�͈�(����)�̎Z�o
			float fLength = (float)(rand() % (int)((200.0f) * 100.0f) / 100.0f);

			// �ݒu���̎Z�o
			int nNumSet = rand() % (MAX_SET_FEED - g_nCntFeed);

			// �ݒu
			RandSetFeed(pos, rot, fRot, fLength, nNumSet);
		}
	}
}

//---------------------------------------------------------------------------
// �a�擾����
//---------------------------------------------------------------------------
Feed *GetFeed(void)
{
	return &g_Feed[0];
}

//---------------------------------------------------------------------------
// �a�t�@�C���擾����
//---------------------------------------------------------------------------
FeedFile *GetFeedFile(void)
{
	return &g_FeedFile;
}