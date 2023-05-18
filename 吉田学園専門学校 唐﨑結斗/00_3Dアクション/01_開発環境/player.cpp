//**************************************************************************************************
//
// �v���C���[�`�揈��(player.cpp)
// Auther�F�������l
//
//**************************************************************************************************

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"
#include "player.h"
#include"file.h"
#include"input.h"
#include"camera.h"
#include"shadow.h"
#include"billboard.h"
#include"effect.h"
#include"line.h"
#include"model.h"
#include"camera.h"
#include"feed.h"
#include"calculation.h"
#include"combo.h"
#include"mouse.h"
#include"fade.h"
#include"sound.h"

//***************************************************************************
// �}�N����`
//***************************************************************************
#define INIT_NUM_PLAYER				(10000)				// ���_���W�̍ő�ŏ��̏����l
#define PLAYER_MOVE_SPEED			(2.0f)				// �ړ����x
#define PLAYER_MAX_SPEED			(5.0f)				// �ړ����x
#define PLAYER_ROTATE_SPEED			(0.1f)				// ��]���x
#define CAMERA_ROTATE_INTERVAL		(60)				// �J�����̎�����]�܂ł̃^�C�~���O
#define	MAX_MOTION					(64)				// ���[�V�����ő吔
#define MAX_VIEW_ROT				(0.25f)				// ����p
#define MAX_COUNT_STATE				(60)				// ��ԃJ�E���^�̍ő�l
#define MAX_STAMINA					(200)				// �X�^�~�i�̍ő�l

//***************************************************************************
// �O���[�o���ϐ�
//***************************************************************************
static int				nCntFrame = 0;					// ���݂̃t���[����
static int				nCntNumKeySet;					// �Đ����̃L�[�ݒ�ԍ�
static int				nNumMotionCnt;					// �Đ����郂�[�V�����ԍ�
static int				nNumMotionCntOld;				// �ЂƂO�̍Đ����郂�[�V�����ԍ�
static Player			g_Player;						// �v���C���[���
static MotionSet		g_MotionSet[MAX_MOTION];		// ���[�V�����ݒ���
static PlayerFile		g_PlayerFile[MAX_MOTION];		// �v���C���[�t�@�C�����

//---------------------------------------------------------------------------
// �v���C���[����������
//---------------------------------------------------------------------------
void InitPlayer(void)
{
	// �v���C���[�t�@�C�����̏�����
	memset(&g_PlayerFile[0], 0, sizeof(g_PlayerFile));

	// �v���C���[���̏�����
	memset(&g_Player, 0, sizeof(g_Player));

	// ���f���p�[�c�̏�����
	memset(&g_Player.modeParts[0], 0, sizeof(g_Player.modeParts));

	// ���[�V�����ݒ�̏�����
	memset(&g_MotionSet[0], 0, sizeof(g_MotionSet));
}

//---------------------------------------------------------------------------
// �v���C���[�I������
//---------------------------------------------------------------------------
void UninitPlayer(void)
{
	for (int i = 0; i < g_Player.nMaxModelParts; i++)
	{
		// ���b�V���̔j��
		if (g_Player.modeParts[i].pMesh != NULL)
		{
			g_Player.modeParts[i].pMesh->Release();
			g_Player.modeParts[i].pMesh = NULL;
		}

		// �}�e���A���̔j��
		if (g_Player.modeParts[i].pBuffer != NULL)
		{
			g_Player.modeParts[i].pBuffer->Release();
			g_Player.modeParts[i].pBuffer = NULL;
		}
	}
}

//---------------------------------------------------------------------------
// �v���C���[�X�V����
//---------------------------------------------------------------------------
void UpdatePlayer(void)
{
	if (g_Player.bUse == true)
	{// �g�p���Ă���
		// �J�E���g���C���N�������g
		g_Player.nCntNotMove++;

		// �ߋ��ʒu�̍X�V
		g_Player.posOld = g_Player.pos;

		nNumMotionCntOld = nNumMotionCnt;

		// �j���[�g�������[�V����
		g_Player.MotionState = NEUTRAL_MOTION;

		// �_�b�V������
		DashPlayer();

		if (g_Player.PlayerState == NORMAL_STATE)
		{// �v���C���[�̈ړ�
			MovePlayer();
		}
		// ���[�V����
		MotionPlayer((int)(g_Player.MotionState));

		//�v���C���[�̉�]
		RotatePlayer();

		// ���f���Ƃ̓����蔻��
		D3DXVECTOR3 aVtxA = WorldCastVtx(D3DXVECTOR3(-(g_Player.size.x / 2.0f), g_Player.pos.y, +(g_Player.size.z / 2.0f)), g_Player.pos, g_Player.rot);
		D3DXVECTOR3 aVtxB = WorldCastVtx(D3DXVECTOR3(+(g_Player.size.x / 2.0f), g_Player.pos.y, +(g_Player.size.z / 2.0f)), g_Player.pos, g_Player.rot);
		D3DXVECTOR3 aVtxC = WorldCastVtx(D3DXVECTOR3(+(g_Player.size.x / 2.0f), g_Player.pos.y, -(g_Player.size.z / 2.0f)), g_Player.pos, g_Player.rot);
		D3DXVECTOR3 aVtxD = WorldCastVtx(D3DXVECTOR3(-(g_Player.size.x / 2.0f), g_Player.pos.y, -(g_Player.size.z / 2.0f)), g_Player.pos, g_Player.rot);
		D3DXVECTOR3 aVtxAOld = WorldCastVtx(D3DXVECTOR3(g_Player.posOld.x - (g_Player.size.x / 2.0f), g_Player.posOld.y, g_Player.posOld.z + (g_Player.size.z / 2.0f)), g_Player.posOld, g_Player.rot);
		D3DXVECTOR3 aVtxBOld = WorldCastVtx(D3DXVECTOR3(g_Player.posOld.x + (g_Player.size.x / 2.0f), g_Player.posOld.y, g_Player.posOld.z + (g_Player.size.z / 2.0f)), g_Player.posOld, g_Player.rot);
		D3DXVECTOR3 aVtxCOld = WorldCastVtx(D3DXVECTOR3(g_Player.posOld.x + (g_Player.size.x / 2.0f), g_Player.posOld.y, g_Player.posOld.z - (g_Player.size.z / 2.0f)), g_Player.posOld, g_Player.rot);
		D3DXVECTOR3 aVtxDOld = WorldCastVtx(D3DXVECTOR3(g_Player.posOld.x - (g_Player.size.x / 2.0f), g_Player.posOld.y, g_Player.posOld.z - (g_Player.size.z / 2.0f)), g_Player.posOld, g_Player.rot);
		CollisionModel(&g_Player.pos, &g_Player.posOld, &aVtxA, &aVtxAOld);
		CollisionModel(&g_Player.pos, &g_Player.posOld, &aVtxB, &aVtxBOld);
		CollisionModel(&g_Player.pos, &g_Player.posOld, &aVtxC, &aVtxCOld);
		CollisionModel(&g_Player.pos, &g_Player.posOld, &aVtxD, &aVtxDOld);

		CollisionFeed(&g_Player.pos, &g_Player.posOld, &aVtxA, &aVtxAOld);
		CollisionFeed(&g_Player.pos, &g_Player.posOld, &aVtxB, &aVtxBOld);
		CollisionFeed(&g_Player.pos, &g_Player.posOld, &aVtxC, &aVtxCOld);
		CollisionFeed(&g_Player.pos, &g_Player.posOld, &aVtxD, &aVtxDOld);

		// �J�����̉�荞��
		if (g_Player.nCntNotMove >= CAMERA_ROTATE_INTERVAL)
		{
			//AutoRotateCamera();
		}

		// �e�̈ړ�
		SetPositionShadow(g_Player.nIdx, g_Player.pos, g_Player.rot, g_Player.size);

		//if (GetKeyboardTrigger(DIK_SPACE))
		//{// [SPACE]�L�[�������ꂽ��
		//	SetBillboard(g_Player.pos, g_Player.rot,1.0f);

		//	// �G�t�F�N�g�̐���
		//	SetEffect(g_Player.pos,
		//		D3DXVECTOR3(0.0f,0.0f,0.0f),
		//		D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f),
		//		D3DCMP_ALWAYS,
		//		EFFECTTYPE_FIELD,
		//		10.0f,
		//		0.0f,
		//		0.0f,
		//		30,
		//		1,
		//		false);
		//}

		if (g_Player.PlayerState == NORMAL_STATE)
		{// �R���{���Ԃ̃f�N�������g
			g_Player.nCntComboTime--;
		}

		if (g_Player.nCntComboTime == 0)
		{// �R���{���Z���Ԃ�0�̎�
			if (g_Player.nMaxCombo < g_Player.nCntCombo)
			{
				g_Player.nMaxCombo = g_Player.nCntCombo;
			}
			g_Player.nCntCombo = 0;
		}

		// �R���{�Z�b�g
		SetCombo(g_Player.nCntCombo, D3DXVECTOR3((30.0f * 2) * 3.0f + 1080.0f, 230.0f, 0.0f), D3DXVECTOR3(30.0f, 60.0f, 0.0f));

		// �R���{�J�E���^�[�̍X�V
		AddCombo(g_Player.nCntCombo);

		// �X�^�~�i�̌���
		if ((int)(g_Player.fMoveDistance) % 20 == 0 
			&& (int)(g_Player.fMoveDistance) > 0
			&& g_Player.PlayerState == NORMAL_STATE)
		{// ���ȏ�ړ�����
			g_Player.nStamina--;

			if (g_Player.nStamina == 0)
			{// 0�ȉ��̎�
				//�t�F�[�h���̎擾
				FADE fade;			//�t�F�[�h���ւ̃|�C���^
				fade = GetFade();

				if (g_Player.nMaxCombo < g_Player.nCntCombo)
				{
					g_Player.nMaxCombo = g_Player.nCntCombo;
				}

				if (fade == FADE_NONE)
				{//�t�F�[�h���s���ĂȂ��Ƃ�
					//���U���g��ʂֈړ�
					SetFade(MODE_RESULT);
				}
			}
		}
	}
}

//---------------------------------------------------------------------------
// �v���C���[�`�揈��
//---------------------------------------------------------------------------
void DrawPlayer(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	D3DXMATRIX			mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9		matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL		*pMat;						// �}�e���A���f�[�^�ւ̃|�C���^

	if (g_Player.bUse == true)
	{// �g�p���Ă���
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player.mtxWorld);			// �s�񏉊����֐�

		// �����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);		// �s���]�֐�
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);							// �s��|���Z�֐� 

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);				// �s��ړ��֐�
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);							// �s��|���Z�֐�

		//// �T�C�Y�̔��f
		//D3DXMatrixScaling()

		for (int i = 0; i < g_Player.nMaxModelParts; i++)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Player.modeParts[i].mtxWorld);			// �s�񏉊����֐�

			// �����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, 
				g_Player.modeParts[i].rot.y, 
				g_Player.modeParts[i].rot.x, 
				g_Player.modeParts[i].rot.z);								// �s���]�֐�
			D3DXMatrixMultiply(&g_Player.modeParts[i].mtxWorld, 
				&g_Player.modeParts[i].mtxWorld,
				&mtxRot);													// �s��|���Z�֐� 

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, 
				g_Player.modeParts[i].pos.x, 
				g_Player.modeParts[i].pos.y,
				g_Player.modeParts[i].pos.z);								// �s��ړ��֐�
			D3DXMatrixMultiply(&g_Player.modeParts[i].mtxWorld, 
				&g_Player.modeParts[i].mtxWorld,
				&mtxTrans);													// �s��|���Z�֐�

			// �e�p�[�c�̃��[���h�}�g���b�N�X��ێ�
			D3DXMATRIX mtxParent;

			if (g_Player.modeParts[i].nIdxModelParent == -1)
			{// �e���f���̃C���f�b�N�X����-1�̎�
				mtxParent = g_Player.mtxWorld;
			}
			else
			{
				mtxParent = g_Player.modeParts[g_Player.modeParts[i].nIdxModelParent].mtxWorld;
			}

			// �����̐e�}�g���b�N�X�Ƃ̊|���Z
			D3DXMatrixMultiply(&g_Player.modeParts[i].mtxWorld, &g_Player.modeParts[i].mtxWorld, &mtxParent);

			//// �T�C�Y�̔��f
			//D3DXMatrixScaling()

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Player.modeParts[i].mtxWorld);

			// ���݂̃}�e���A����ێ�
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Player.modeParts[i].pBuffer->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Player.modeParts[i].nNumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �v���C���[�p�[�c�̕`��
				g_Player.modeParts[i].pMesh->DrawSubset(nCntMat);
			}

			// �ێ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//---------------------------------------------------------------------------
// �v���C���[�ړ�����
//---------------------------------------------------------------------------
void MovePlayer(void)
{
	if (GetKeyboardPress(DIK_W)
		|| GetKeyboardPress(DIK_A)
		|| GetKeyboardPress(DIK_D)
		|| GetKeyboardPress(DIK_S))
	{// �ړ��L�[�������ꂽ
		 // �ړ����[�V����
		g_Player.MotionState = MOVE_MOTION;

		if (GetKeyboardPress(DIK_W))
		{// [��]�L�[�������ꂽ��
			if (GetKeyboardPress(DIK_A))
			{// [��]�L�[�������ꂽ��
				// �ړ������̍X�V
				g_Player.rotDest.y = D3DX_PI * -0.25f;
			}
			else if (GetKeyboardPress(DIK_D))
			{// [��]�L�[�������ꂽ��
				// �ړ������̍X�V
				g_Player.rotDest.y = D3DX_PI * 0.25f;
			}
			else
			{// �ړ������̍X�V
				g_Player.rotDest.y = D3DX_PI * 0.0f;
			}
		}
		else if (GetKeyboardPress(DIK_S))
		{// [��]�L�[�������ꂽ��
			if (GetKeyboardPress(DIK_A))
			{// [��]�L�[�������ꂽ��
				// �ړ������̍X�V
				g_Player.rotDest.y = D3DX_PI * -0.75f;
			}
			else if (GetKeyboardPress(DIK_D))
			{// [��]�L�[�������ꂽ��
				// �ړ������̍X�V
				g_Player.rotDest.y = D3DX_PI * 0.75f;
			}
			else
			{// �ړ������̍X�Vq
				g_Player.rotDest.y = D3DX_PI;
			}
		}
		else if (GetKeyboardPress(DIK_A))
		{// [��]�L�[�������ꂽ��
			// �ړ������̍X�V
			g_Player.rotDest.y = D3DX_PI * -0.5f;
		}
		else if (GetKeyboardPress(DIK_D))
		{// [��]�L�[�������ꂽ��
			// �ړ������̍X�V
			g_Player.rotDest.y = D3DX_PI * 0.5f;
		}

		// �J�������̎擾
		Camera *pCamera = GetCamera();

		// �ړ������̎Z�o
		g_Player.rotDest.y += pCamera->rot.y;

		if (g_Player.rotDest.y > D3DX_PI)
		{// �ړ������̐��K��
			g_Player.rotDest.y -= D3DX_PI * 2;
		}
		else if (g_Player.rotDest.y < -D3DX_PI)
		{// �ړ������̐��K��
			g_Player.rotDest.y += D3DX_PI * 2;
		}

		// ���_�ʒu�ƌ����̍X�V
		g_Player.fSpeed = PLAYER_MOVE_SPEED + (0.1f * g_Player.nCntCombo);

		if (g_Player.fSpeed >= PLAYER_MAX_SPEED)
		{// ���x�����ȏア����
			g_Player.fSpeed = PLAYER_MAX_SPEED;
		}

		// �ړ��ʂ̌v�Z
		D3DXVECTOR3 move = D3DXVECTOR3(sinf(g_Player.rotDest.y), 0.0f, cosf(g_Player.rotDest.y));

		// �ړ�
		g_Player.pos += move * g_Player.fSpeed;

		// �ړ������̉��Z
		g_Player.fMoveDistance += sqrtf((move.x * move.x) + (move.z * move.z));

		g_Player.rotDest.y -= D3DX_PI;

		// �J�E���g��0�ɂ���
		g_Player.nCntNotMove = 0;
	}

	//if (GetKeyboardPress(DIK_I) || GetKeyboardPress(DIK_K))
	//{
	//	if (GetKeyboardPress(DIK_I))
	//	{// [I]�L�[�������ꂽ��
	//	 // �ړ������̍X�V
	//		g_Player.pos.y += PLAYER_MOVE_SPEED;
	//	}
	//	else if (GetKeyboardPress(DIK_K))
	//	{// [K]�L�[�������ꂽ��
	//	 // �ړ������̍X�V
	//		g_Player.pos.y -= PLAYER_MOVE_SPEED;
	//	}

	//	// �J�E���g��0�ɂ���
	//	g_Player.nCntNotMove = 0;
	//}

	// �ړI�̌����̕␳
	if (g_Player.rotDest.y - g_Player.rot.y >= D3DX_PI)
	{// �ړ������̐��K��
		g_Player.rotDest.y -= D3DX_PI * 2;
	}
	else if (g_Player.rotDest.y - g_Player.rot.y <= -D3DX_PI)
	{// �ړ������̐��K��
		g_Player.rotDest.y += D3DX_PI * 2;
	}
}

//---------------------------------------------------------------------------
// �v���C���[��]����
//---------------------------------------------------------------------------
void RotatePlayer(void)
{
	// �����̍X�V
	g_Player.rot.y += (g_Player.rotDest.y - g_Player.rot.y) * PLAYER_ROTATE_SPEED;

	if (g_Player.rot.y >= D3DX_PI)
	{// �ړ������̐��K��
		g_Player.rot.y -= D3DX_PI * 2;
	}
	else if (g_Player.rot.y <= -D3DX_PI)
	{// �ړ������̐��K��
		g_Player.rot.y += D3DX_PI * 2;
	}
}

//---------------------------------------------------------------------------
// �v���C���[�ݒ菈��
//---------------------------------------------------------------------------
void SetPlayer(D3DXVECTOR3 pos,D3DXVECTOR3 rot,int	nMaxModelType,int	nMaxMotion)
{
	// �v���C���[���̏�����
	g_Player.pos = pos;																		// �ʒu�̏�����
	g_Player.posOld = g_Player.pos;															// �ߋ��ʒu�̏�����
	g_Player.rot = rot;																		// �����̏�����
	g_Player.vtxMin = D3DXVECTOR3(INIT_NUM_PLAYER, INIT_NUM_PLAYER, INIT_NUM_PLAYER);		// ���_���W�̍ŏ��l
	g_Player.vtxMax = D3DXVECTOR3(-INIT_NUM_PLAYER, -INIT_NUM_PLAYER, -INIT_NUM_PLAYER);	// ���_���W�̍ő�l
	g_Player.size = D3DXVECTOR3(35.0f, 50.0f, 110.0f);										// �傫��
	g_Player.PlayerState = NORMAL_STATE;													// �ʏ���
	g_Player.attackPos = D3DXVECTOR3(0.0f, 0.0f, -20.0f);									// �����蔻��̃��[�J�����W
	g_Player.fAttackRadius = 20.0f;															// �����蔻��̑傫��
	g_Player.mtxWorld = {};																	// ���[���h�}�g���b�N�X
	g_Player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										// �ړI�̌���
	g_Player.nMaxModelType = nMaxModelType;													// ���f���̃^�C�v��
	g_Player.nMaxMotion = nMaxMotion;														// ���[�V������
	g_Player.nCntCombo = 0;																	// �R���{��
	g_Player.nMaxCombo = 0;																	// �R���{�ő�l
	g_Player.nMaxStamina = MAX_STAMINA;														// �X�^�~�i�̍ő�l
	g_Player.nStamina = g_Player.nMaxStamina;												// �X�^�~�i
	g_Player.nCntState = 0;																	// ��ԃJ�E���^
	g_Player.fSpeed = PLAYER_MOVE_SPEED + (0.1f * g_Player.nCntCombo);						// �ړ����x
	g_Player.fMoveDistance = 0.0f;															// �ړ�����
	g_Player.bUse = true;																	// �g�p��
	g_Player.nCntNotMove = CAMERA_ROTATE_INTERVAL;

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < g_Player.nMaxModelParts; i++)
	{
		// �ʒu�ƌ����̏����l��ۑ�
		g_Player.modeParts[i].posOrigin = g_Player.modeParts[i].pos;
		g_Player.modeParts[i].rotOrigin = g_Player.modeParts[i].rot;

		// �p�[�c���̏�����
		g_Player.modeParts[i].mtxWorld = {};																// ���[���h�}�g���b�N�X
		g_Player.modeParts[i].vtxMin = D3DXVECTOR3(INIT_NUM_PLAYER, INIT_NUM_PLAYER, INIT_NUM_PLAYER);		// ���_���W�̍ŏ��l
		g_Player.modeParts[i].vtxMax = D3DXVECTOR3(-INIT_NUM_PLAYER, -INIT_NUM_PLAYER, -INIT_NUM_PLAYER);	// ���_���W�̍ő�l

		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(&g_PlayerFile[g_Player.modeParts[i].nType].aName[0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Player.modeParts[i].pBuffer,
			NULL,
			&g_Player.modeParts[i].nNumMat,
			&g_Player.modeParts[i].pMesh);

		// ���_���W�̍ŏ��l�E�ő�l�̎Z�o
		int			nNumVtx;		// ���_��
		DWORD		sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
		BYTE		*pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

		// ���_���̎擾
		nNumVtx = g_Player.modeParts[i].pMesh->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y�̎擾
		sizeFVF = D3DXGetFVFVertexSize(g_Player.modeParts[i].pMesh->GetFVF());

		// ���_�o�b�t�@�̃��b�N
		g_Player.modeParts[i].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			// ���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			if (vtx.x < g_Player.modeParts[i].vtxMin.x)
			{// ��r�Ώۂ����݂̒��_���W(X)�̍ŏ��l��菬����
				g_Player.modeParts[i].vtxMin.x = vtx.x;
			}
			if (vtx.y < g_Player.modeParts[i].vtxMin.y)
			{// ��r�Ώۂ����݂̒��_���W(Y)�̍ŏ��l��菬����
				g_Player.modeParts[i].vtxMin.y = vtx.y;
			}
			if (vtx.z < g_Player.modeParts[i].vtxMin.z)
			{// ��r�Ώۂ����݂̒��_���W(Z)�̍ŏ��l��菬����
				g_Player.modeParts[i].vtxMin.z = vtx.z;
			}

			if (vtx.x > g_Player.modeParts[i].vtxMax.x)
			{// ��r�Ώۂ����݂̒��_���W(X)�̍ő�l���傫��
				g_Player.modeParts[i].vtxMax.x = vtx.x;
			}
			if (vtx.y > g_Player.modeParts[i].vtxMax.y)
			{// ��r�Ώۂ����݂̒��_���W(Y)�̍ő�l���傫��
				g_Player.modeParts[i].vtxMax.y = vtx.y;
			}
			if (vtx.z > g_Player.modeParts[i].vtxMax.z)
			{// ��r�Ώۂ����݂̒��_���W(Z)�̍ő�l���傫��
				g_Player.modeParts[i].vtxMax.z = vtx.z;
			}

			// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		// ���_�̎Z�o
		D3DXVECTOR3 aVtxMin = D3DXVECTOR3(g_Player.modeParts[i].vtxMin.x, g_Player.modeParts[i].vtxMin.y, g_Player.modeParts[i].vtxMin.z);
		D3DXVECTOR3 aVtxMax = D3DXVECTOR3(g_Player.modeParts[i].vtxMax.x, g_Player.modeParts[i].vtxMax.y, g_Player.modeParts[i].vtxMax.z);

		// ���_�����[���h���W�փL���X�g
		aVtxMin = WorldCastVtx(aVtxMin, g_Player.modeParts[i].pos, g_Player.modeParts[i].rot);
		aVtxMax = WorldCastVtx(aVtxMax, g_Player.modeParts[i].pos, g_Player.modeParts[i].rot);

		if (aVtxMin.x < g_Player.vtxMin.x)
		{// ��r�Ώۂ����݂̒��_���W(X)�̍ŏ��l��菬����
			g_Player.vtxMin.x = aVtxMin.x;
		}
		if (aVtxMin.y < g_Player.vtxMin.y)
		{// ��r�Ώۂ����݂̒��_���W(Y)�̍ŏ��l��菬����
			g_Player.vtxMin.y = aVtxMin.y;
		}
		if (aVtxMin.z < g_Player.vtxMin.z)
		{// ��r�Ώۂ����݂̒��_���W(Z)�̍ŏ��l��菬����
			g_Player.vtxMin.z = aVtxMin.z;
		}

		if (aVtxMax.x > g_Player.vtxMax.x)
		{// ��r�Ώۂ����݂̒��_���W(X)�̍ő�l���傫��
			g_Player.vtxMax.x = aVtxMax.x;
		}
		if (aVtxMax.y > g_Player.vtxMax.y)
		{// ��r�Ώۂ����݂̒��_���W(Y)�̍ő�l���傫��
			g_Player.vtxMax.y = aVtxMax.y;
		}
		if (aVtxMax.z > g_Player.vtxMax.z)
		{// ��r�Ώۂ����݂̒��_���W(Z)�̍ő�l���傫��
			g_Player.vtxMax.z = aVtxMax.z;
		}

		// ���_�o�b�t�@�̃A�����b�N
		g_Player.modeParts[i].pMesh->UnlockVertexBuffer();
	}

	// ���C���̐ݒ�
#ifndef _DEBUG
	SetLine(g_Player.pos, g_Player.rot, D3DXVECTOR3(-g_Player.size.x / 2.0f, -g_Player.size.y, g_Player.size.z / 2.0f), D3DXVECTOR3(g_Player.size.x / 2.0f, -g_Player.size.y, g_Player.size.z / 2.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	SetLine(g_Player.pos, g_Player.rot, D3DXVECTOR3(-g_Player.size.x / 2.0f, -g_Player.size.y, -g_Player.size.z / 2.0f), D3DXVECTOR3(-g_Player.size.x / 2.0f, -g_Player.size.y, g_Player.size.z / 2.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	SetLine(g_Player.pos, g_Player.rot, D3DXVECTOR3(-g_Player.size.x / 2.0f, -g_Player.size.y, -g_Player.size.z / 2.0f), D3DXVECTOR3(g_Player.size.x / 2.0f, -g_Player.size.y, -g_Player.size.z / 2.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	SetLine(g_Player.pos, g_Player.rot, D3DXVECTOR3(g_Player.size.x / 2.0f, -g_Player.size.y, -g_Player.size.z / 2.0f), D3DXVECTOR3(g_Player.size.x / 2.0f, -g_Player.size.y, g_Player.size.z / 2.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

	SetLine(g_Player.pos, g_Player.rot, D3DXVECTOR3(-g_Player.size.x / 2.0f, g_Player.size.y, g_Player.size.z / 2.0f), D3DXVECTOR3(g_Player.size.x / 2.0f, g_Player.size.y, g_Player.size.z / 2.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	SetLine(g_Player.pos, g_Player.rot, D3DXVECTOR3(-g_Player.size.x / 2.0f, g_Player.size.y, -g_Player.size.z / 2.0f), D3DXVECTOR3(-g_Player.size.x / 2.0f, g_Player.size.y, g_Player.size.z / 2.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	SetLine(g_Player.pos, g_Player.rot, D3DXVECTOR3(-g_Player.size.x / 2.0f, g_Player.size.y, -g_Player.size.z / 2.0f), D3DXVECTOR3(g_Player.size.x / 2.0f, g_Player.size.y, -g_Player.size.z / 2.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	SetLine(g_Player.pos, g_Player.rot, D3DXVECTOR3(g_Player.size.x / 2.0f, g_Player.size.y, -g_Player.size.z / 2.0f), D3DXVECTOR3(g_Player.size.x / 2.0f, g_Player.size.y, g_Player.size.z / 2.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

	SetLine(g_Player.pos, g_Player.rot, D3DXVECTOR3(-g_Player.size.x / 2.0f, -g_Player.size.y, g_Player.size.z / 2.0f), D3DXVECTOR3(-g_Player.size.x / 2.0f, g_Player.size.y, g_Player.size.z / 2.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	SetLine(g_Player.pos, g_Player.rot, D3DXVECTOR3(-g_Player.size.x / 2.0f, -g_Player.size.y, -g_Player.size.z / 2.0f), D3DXVECTOR3(-g_Player.size.x / 2.0f, g_Player.size.y, -g_Player.size.z / 2.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	SetLine(g_Player.pos, g_Player.rot, D3DXVECTOR3(g_Player.size.x / 2.0f, -g_Player.size.y, -g_Player.size.z / 2.0f), D3DXVECTOR3(g_Player.size.x / 2.0f, g_Player.size.y, -g_Player.size.z / 2.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	SetLine(g_Player.pos, g_Player.rot, D3DXVECTOR3(g_Player.size.x / 2.0f, -g_Player.size.y, g_Player.size.z / 2.0f), D3DXVECTOR3(g_Player.size.x / 2.0f, g_Player.size.y, g_Player.size.z / 2.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
#endif // _DEBUG

	// �e�̐ݒ�
	g_Player.nIdx = SetShadow(g_Player.pos, g_Player.rot, g_Player.size);

	AutoRotateCamera();
}

//---------------------------------------------------------------------------
// �v���C���[�̃��[�V��������
//---------------------------------------------------------------------------
void MotionPlayer(int nCntMotionSet)
{
	KeySet* keyset = &g_MotionSet[nCntMotionSet].keySet[g_MotionSet[nCntMotionSet].nCntKeySet];
	MotionSet* motionSet = &g_MotionSet[nCntMotionSet];

	for (int nCntParts = 0; nCntParts < g_Player.nMaxModelParts; nCntParts++)
	{
		ModelParts* modelParts = &g_Player.modeParts[nCntParts];

		if (motionSet->nCntFrame == 0)
		{// �t���[���J�E���g��0�̎�
			// �ړI�̈ʒu�ƌ����̎Z�o
			modelParts->posDest = (modelParts->posOrigin + keyset->key[nCntParts].pos) - modelParts->pos;
			modelParts->rotDest = (modelParts->rotOrigin + keyset->key[nCntParts].rot) - modelParts->rot;

			// �ړ������̐��K��
			RotNormalization(modelParts->rotDest.x);
			RotNormalization(modelParts->rotDest.y);
			RotNormalization(modelParts->rotDest.z);
		}
				
		// �ϐ��錾
		D3DXVECTOR3 addPos = D3DXVECTOR3(modelParts->posDest / (float)(keyset->nFrame));
		D3DXVECTOR3 addRot = D3DXVECTOR3(modelParts->rotDest / (float)(keyset->nFrame));

		// �ʒu�̉��Z
		modelParts->pos += addPos;

		//	�����̉��Z
		modelParts->rot += addRot;

		// �ړ������̐��K��
		RotNormalization(modelParts->rot.x);
		RotNormalization(modelParts->rot.y);
		RotNormalization(modelParts->rot.z);
	}

	// �t���[���J�E���g�̉��Z
	motionSet->nCntFrame++;

	if (motionSet->nCntFrame >= keyset->nFrame)
	{// �t���[���J�E���g���w��̃t���[�����𒴂����ꍇ
		// �t���[�����̏�����
		motionSet->nCntFrame = 0;

		// �Đ����̃L�[�ԍ����̉��Z
		motionSet->nCntKeySet++;

		if ((motionSet->nCntKeySet >= motionSet->nNumKey) && motionSet->bLoop)
		{// �Đ����̃L�[���J�E���g���L�[���̍ő�l�𒴂����Ƃ��A���̃��[�V���������[�v���g�p���Ă���
			// �Đ����̃L�[���J�E���g��������
			motionSet->nCntKeySet = 0;
		}
	}
}

//---------------------------------------------------------------------------
// �v���C���[�̃��[�V�����u�����h����
//---------------------------------------------------------------------------
void MotionBlend(int nCntMotionSet)
{
	for (int nCntParts = 0; nCntParts < g_Player.nMaxModelParts; nCntParts++)
	{
		if (g_MotionSet[nCntMotionSet].nCntFrame == 0)
		{// �t���[���J�E���g��0�̎�
		 // �ړI�̈ʒu�ƌ����̎Z�o
			g_Player.modeParts[nCntParts].posDest = (g_Player.modeParts[nCntParts].posOrigin + g_MotionSet[nCntMotionSet].keySet[g_MotionSet[nCntMotionSet].nCntKeySet].key[nCntParts].pos) - g_Player.modeParts[nCntParts].pos;
			g_Player.modeParts[nCntParts].rotDest = (g_Player.modeParts[nCntParts].rotOrigin + g_MotionSet[nCntMotionSet].keySet[g_MotionSet[nCntMotionSet].nCntKeySet].key[nCntParts].rot) - g_Player.modeParts[nCntParts].rot;

			if (g_Player.modeParts[nCntParts].rotDest.x >= D3DX_PI)
			{// �ړ������̐��K��
				g_Player.modeParts[nCntParts].rotDest.x -= D3DX_PI * 2;
			}
			else if (g_Player.modeParts[nCntParts].rotDest.x <= -D3DX_PI)
			{// �ړ������̐��K��
				g_Player.modeParts[nCntParts].rotDest.x += D3DX_PI * 2;
			}
			if (g_Player.modeParts[nCntParts].rotDest.y >= D3DX_PI)
			{// �ړ������̐��K��
				g_Player.modeParts[nCntParts].rotDest.y -= D3DX_PI * 2;
			}
			else if (g_Player.modeParts[nCntParts].rotDest.y <= -D3DX_PI)
			{// �ړ������̐��K��
				g_Player.modeParts[nCntParts].rotDest.y += D3DX_PI * 2;
			}
			if (g_Player.modeParts[nCntParts].rotDest.z >= D3DX_PI)
			{// �ړ������̐��K��
				g_Player.modeParts[nCntParts].rotDest.z -= D3DX_PI * 2;
			}
			else if (g_Player.modeParts[nCntParts].rotDest.z <= -D3DX_PI)
			{// �ړ������̐��K��
				g_Player.modeParts[nCntParts].rotDest.z += D3DX_PI * 2;
			}
		}

		// �ϐ��錾
		D3DXVECTOR3 addPos = D3DXVECTOR3(g_Player.modeParts[nCntParts].posDest / (float)(g_MotionSet[nCntMotionSet].keySet[g_MotionSet[nCntMotionSet].nCntKeySet].nFrame));
		D3DXVECTOR3 addRot = D3DXVECTOR3(g_Player.modeParts[nCntParts].rotDest / (float)(g_MotionSet[nCntMotionSet].keySet[g_MotionSet[nCntMotionSet].nCntKeySet].nFrame));

		// �ʒu�̉��Z
		g_Player.modeParts[nCntParts].pos += addPos;

		//	�����̉��Z
		g_Player.modeParts[nCntParts].rot += addRot;

		if (g_Player.modeParts[nCntParts].rot.x >= D3DX_PI)
		{// �ړ������̐��K��
			g_Player.modeParts[nCntParts].rot.x -= D3DX_PI * 2;
		}
		else if (g_Player.modeParts[nCntParts].rot.x <= -D3DX_PI)
		{// �ړ������̐��K��
			g_Player.modeParts[nCntParts].rot.x += D3DX_PI * 2;
		}
		if (g_Player.modeParts[nCntParts].rot.y >= D3DX_PI)
		{// �ړ������̐��K��
			g_Player.modeParts[nCntParts].rot.y -= D3DX_PI * 2;
		}
		else if (g_Player.modeParts[nCntParts].rot.y <= -D3DX_PI)
		{// �ړ������̐��K��
			g_Player.modeParts[nCntParts].rot.y += D3DX_PI * 2;
		}
		if (g_Player.modeParts[nCntParts].rot.z >= D3DX_PI)
		{// �ړ������̐��K��
			g_Player.modeParts[nCntParts].rot.z -= D3DX_PI * 2;
		}
		else if (g_Player.modeParts[nCntParts].rot.z <= -D3DX_PI)
		{// �ړ������̐��K��
			g_Player.modeParts[nCntParts].rot.z += D3DX_PI * 2;
		}
	}

	// �t���[���J�E���g�̉��Z
	g_MotionSet[nCntMotionSet].nCntFrame++;

	if (g_MotionSet[nCntMotionSet].nCntFrame >= g_MotionSet[nCntMotionSet].keySet[g_MotionSet[nCntMotionSet].nCntKeySet].nFrame)
	{// �t���[���J�E���g���w��̃t���[�����𒴂����ꍇ
		// �t���[�����̏�����
		g_MotionSet[nCntMotionSet].nCntFrame = 0;

		// �Đ����̃L�[�ԍ����̉��Z
		g_MotionSet[nCntMotionSet].nCntKeySet++;

		if (g_MotionSet[nCntMotionSet].nCntKeySet >= g_MotionSet[nCntMotionSet].nNumKey && g_MotionSet[nCntMotionSet].bLoop == true)
		{// �Đ����̃L�[���J�E���g���L�[���̍ő�l�𒴂����Ƃ��A���̃��[�V���������[�v���g�p���Ă���
			// �Đ����̃L�[���J�E���g��������
			g_MotionSet[nCntMotionSet].nCntKeySet = 0;
		}
	}
}

//---------------------------------------------------------------------------
// �v���C���[����p����
//---------------------------------------------------------------------------
bool SearchPlayer(D3DXVECTOR3 *pos)
{
	// �ϐ��錾
	bool bSearchIn = false;

	// ����p�̔������Z�o
	float fSearchRot = (D3DX_PI * MAX_VIEW_ROT);

	// ���Ԃ̂������
	D3DXVECTOR3 aVtxPos = g_Player.pos;
	float fFellowRot = atan2f(aVtxPos.x - pos->x, aVtxPos.z - pos->z);
	fFellowRot = RotNormalization(fFellowRot);

	// ��r�p�̌����̎Z�o
	D3DXVECTOR3 sen = g_Player.pos;
	float fSearchRotRight = g_Player.rot.y - fSearchRot;
	float fSRROld = fSearchRotRight;
	fSearchRotRight = RotNormalization(fSearchRotRight);

	float fSearchRotLeft = g_Player.rot.y + fSearchRot;
	float fSRLOld = fSearchRotLeft;
	fSearchRotLeft = RotNormalization(fSearchRotLeft);

	if (fSRROld == fSearchRotRight && fSRLOld == fSearchRotLeft)
	{// ���K���O�̐��l�������ꍇ
		if (fSearchRotRight <= fFellowRot
			&& fSearchRotLeft >= fFellowRot)
		{// ����p���ɖڕW������
			bSearchIn = true;
		}
	}
	else
	{// ���K���O�̐��l���Ⴄ�ꍇ
		if (fSearchRotRight <= fFellowRot
			|| fSearchRotLeft >= fFellowRot)
		{// ����p���ɖڕW������
			bSearchIn = true;
		}
	}

	return bSearchIn;
}

//---------------------------------------------------------------------------
// �v���C���[�U�����菈��
//---------------------------------------------------------------------------
bool EatPlayer(D3DXVECTOR3 *pos, D3DXVECTOR3 size)
{
	// �ϐ��錾
	bool bOnCollison = false;
	D3DXVECTOR3 distance;

	// ���a�̎Z�o
	float fRadius = sqrtf((size.x * size.x) + (size.z * size.z)) / 2.0f;
	fRadius += g_Player.fAttackRadius / 2.0f;

	// �����蔻��̈ʒu�����[���h���W�ɃL���X�g
	distance = WorldCastVtx(g_Player.attackPos, g_Player.pos, g_Player.rot);

	// �ڕW�ƍ���
	distance = *pos - distance;
	float fDistance = sqrtf((distance.x * distance.x) + (distance.z * distance.z));
	
	if (fDistance <= fRadius)
	{// �����蔻��I��
		bOnCollison = true;
	}

	return bOnCollison;
}

//---------------------------------------------------------------------------
// �v���C���[�����蔻�菈��
//---------------------------------------------------------------------------
bool CollisionPlayer(D3DXVECTOR3 *vtx)
{
	// �ϐ��錾
	bool OnCollision = false;

	// ���_�̎Z�o
	D3DXVECTOR3 aVecA = D3DXVECTOR3(-(g_Player.size.x / 2.0f), g_Player.pos.y, +(g_Player.size.z / 2.0f));
	D3DXVECTOR3 aVecB = D3DXVECTOR3(+(g_Player.size.x / 2.0f), g_Player.pos.y, +(g_Player.size.z / 2.0f));
	D3DXVECTOR3 aVecC = D3DXVECTOR3(+(g_Player.size.x / 2.0f), g_Player.pos.y, -(g_Player.size.z / 2.0f));
	D3DXVECTOR3 aVecD = D3DXVECTOR3(-(g_Player.size.x / 2.0f), g_Player.pos.y, -(g_Player.size.z / 2.0f));

	// ���_�����[���h���W�փL���X�g
	aVecA = WorldCastVtx(aVecA, g_Player.pos, g_Player.rot);
	aVecB = WorldCastVtx(aVecB, g_Player.pos, g_Player.rot);
	aVecC = WorldCastVtx(aVecC, g_Player.pos, g_Player.rot);
	aVecD = WorldCastVtx(aVecD, g_Player.pos, g_Player.rot);

	if (g_Player.pos.x < g_Player.pos.x)g_Player.pos.x = g_Player.pos.x;

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
		// ��_�̎Z�o
		g_Player.pos.x = g_Player.posOld.x;
		g_Player.pos.z = g_Player.posOld.z;
		OnCollision = true;
	}

	return OnCollision;
}

//---------------------------------------------------------------------------
// �v���C���[�̃_�b�V������
//---------------------------------------------------------------------------
void DashPlayer(void)
{
	if(GetKeyboardTrigger(DIK_LSHIFT))
	{// ���V�t�g�{�^���������ꂽ
		if (g_Player.nStamina > DASH_STAMINA)
		{// �_�b�V���Ɏg���X�^�~�i�ȏ゠��
			if (g_Player.PlayerState == NORMAL_STATE)
			{// �ʏ��Ԃ̎�
				g_Player.PlayerState = DASH_STATE;
				g_Player.nCntState = MAX_COUNT_STATE;
				g_Player.nStamina -= DASH_STAMINA;
				g_Player.fSpeed = PLAYER_MOVE_SPEED + (0.1f * g_Player.nCntCombo);

				if (g_Player.fSpeed >= PLAYER_MAX_SPEED)
				{// ���x�����ȏア����
					g_Player.fSpeed = PLAYER_MAX_SPEED;
				}

				//�T�E���h�̍Đ�
				PlaySound(SOUND_LABEL_SE_APPEAR);
			}
		}
	}

	if (g_Player.PlayerState == DASH_STATE)
	{// �_�b�V�����
		// �ړ����[�V����
		g_Player.MotionState = MOVE_MOTION;
		float fMaxSpeed = 3.0f;
		g_Player.fSpeed += fMaxSpeed / (float)(g_Player.nCntState);

		// �ړ�����
		g_Player.pos.x += sinf(g_Player.rot.y - D3DX_PI) * g_Player.fSpeed;
		g_Player.pos.z += cosf(g_Player.rot.y - D3DX_PI) * g_Player.fSpeed;

		g_Player.nCntState--;

		if (g_Player.nCntState <= 0)
		{
			g_Player.PlayerState = NORMAL_STATE;
		}
	}
}

//---------------------------------------------------------------------------
// �v���C���[�擾����
//---------------------------------------------------------------------------
Player *GetPlayer(void)
{
	return &g_Player;
}

//---------------------------------------------------------------------------
// �v���C���[�t�@�C���擾����
//---------------------------------------------------------------------------
PlayerFile	*GetPlayerFile(void)
{
	return &g_PlayerFile[0];
}

//---------------------------------------------------------------------------
// ���[�V�����擾����
//---------------------------------------------------------------------------
MotionSet	*GetMotionSet(void)
{
	return &g_MotionSet[0];
}