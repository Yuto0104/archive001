//**************************************************************************************************
//
// ���[�V��������(motion.cpp)
// Auther�F�������l
//
//**************************************************************************************************

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include <stdio.h>
#include <assert.h>

#include "application.h"
#include "motion.h"	
#include "model_manager.h"
#include "calculation.h"
#include "texture.h"

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CMotion::CMotion(const char * pFileName)
{
	// �p�[�c���̏�����
	memset(&m_partsFile, 0, sizeof(m_partsFile));

	// ���[�V�����̏�����
	memset(&m_motion, 0, sizeof(m_motion));

	// �p�[�c�̏�����
	memset(&m_parts, 0, sizeof(m_parts));

	// �p�[�c���̏�����
	m_nMaxParts = 0;

	// ���[�V�����̓ǂݍ���
	LoodSetMotion(pFileName);
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CMotion::~CMotion()
{
}

//=============================================================================
// ������
// Author : �������l
// �T�v : �p�[�c����X�t�@�C���ǂݍ���
//=============================================================================
void CMotion::Init(void)
{
	// ���f���}�l�[�W���[�N���X�̐ݒ�
	CModelManager *pModelManager = CApplication::GetModelManager();

	for (int nCntMotion = 0; nCntMotion < MAX_MOTION; nCntMotion++)
	{// �J�E���g�̃��Z�b�g
		CntReset(nCntMotion);
	}

	for (int nCntParts = 0; nCntParts < m_nMaxParts; nCntParts++)
	{
		CMotion::Parts* parts = (m_parts + nCntParts);

		// �ʒu�ƌ����̏����l��ۑ�
		parts->posOrigin = parts->pos;
		parts->rotOrigin = parts->rot;

		// �p�[�c���̏�����
		parts->mtxWorld = {};		// ���[���h�}�g���b�N�X

		// �}�e���A�����̑��
		parts->material = pModelManager->GetModelMateria(parts->nType);
	}
}

//=============================================================================
// ���[�V�����̐ݒ�
// Author : �������l
// �T�v : ���[�V�����̏����ʒu�ɐݒ�
//=============================================================================
void CMotion::SetMotion(const int nCntMotionSet)
{
	CMotion::MyMotion *motion = (m_motion + nCntMotionSet);

	for (int nCntParts = 0; nCntParts < m_nMaxParts; nCntParts++)
	{
		CMotion::Parts* parts = (m_parts + nCntParts);

		// �ʒu�̐ݒ�
		parts->pos = (parts->posOrigin + motion->keySet[motion->nCntKeySet].key[nCntParts].pos);

		//	�����̐ݒ�
		parts->rot = (parts->rotOrigin + motion->keySet[motion->nCntKeySet].key[nCntParts].rot);

		// �p�x�̐��K��
		parts->rot.x = RotNormalization(parts->rot.x);
		parts->rot.y = RotNormalization(parts->rot.y);
		parts->rot.z = RotNormalization(parts->rot.z);
	}
}

//=============================================================================
// �p�[�c�̐ݒ�
// Author : �������l
// �T�v : �s��𗘗p���āA�p�[�c�̐e�q�֌W�ƕ`��ݒ���s��
//=============================================================================
void CMotion::SetParts(D3DXMATRIX mtxWorld)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// �e�N�X�`���|�C���^�̎擾
	CTexture *pTexture = CApplication::GetTexture();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat = {};

	for (int nCntParts = 0; nCntParts < m_nMaxParts; nCntParts++)
	{// ���[���h�}�g���b�N�X�̏�����
		CMotion::Parts* parts = (m_parts + nCntParts);

		D3DXMatrixIdentity(&parts->mtxWorld);			// �s�񏉊����֐�

		// �����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			parts->rot.y,
			parts->rot.x,
			parts->rot.z);								// �s���]�֐�

		D3DXMatrixMultiply(&parts->mtxWorld,
			&parts->mtxWorld,
			&mtxRot);									// �s��|���Z�֐� 

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans,
			parts->pos.x,
			parts->pos.y,
			parts->pos.z);								// �s��ړ��֐�

		D3DXMatrixMultiply(&parts->mtxWorld,
			&parts->mtxWorld,
			&mtxTrans);									// �s��|���Z�֐�

		// �e�p�[�c�̃��[���h�}�g���b�N�X��ێ�
		D3DXMATRIX mtxParent;

		if (parts->nIdxModelParent == -1)
		{// �e���f���̃C���f�b�N�X����-1�̎�
		 // �V�K�[�x�l��Z�o�b�t�@�̐[�x�l�������l�Ȃ�e�X�g�����ɂ���
			mtxParent = mtxWorld;
		}
		else
		{// �V�K�[�x�l��Z�o�b�t�@�̐[�x�l�������l�Ȃ�e�X�g�����ɂ���
			mtxParent = (m_parts + parts->nIdxModelParent)->mtxWorld;
		}

		// �����̐e�}�g���b�N�X�Ƃ̊|���Z
		D3DXMatrixMultiply(&parts->mtxWorld, &parts->mtxWorld, &mtxParent);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &parts->mtxWorld);

		// ���݂̃}�e���A����ێ�
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)parts->material.pBuffer->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)parts->material.nNumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pTexture->GetTexture(parts->material.pNumTex[nCntMat]));

			// �v���C���[�p�[�c�̕`��
			parts->material.pMesh->DrawSubset(nCntMat);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, nullptr);
		}

		// �ۂ��Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}

	// �V�K�[�x�l��Z�o�b�t�@�̐[�x�l�������l�Ȃ�e�X�g�����ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}

//=============================================================================
// �p�[�c�̐ݒ�
// Author : �������l
// �T�v : �s��𗘗p���āA�p�[�c�̐e�q�֌W�ƕ`��ݒ�A�F�ݒ���s��
//=============================================================================
void CMotion::SetParts(D3DXMATRIX mtxWorld, const D3DXCOLOR col)
{// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// �e�N�X�`���|�C���^�̎擾
	CTexture *pTexture = CApplication::GetTexture();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat = {};

	for (int nCntParts = 0; nCntParts < m_nMaxParts; nCntParts++)
	{// ���[���h�}�g���b�N�X�̏�����
		CMotion::Parts* parts = (m_parts + nCntParts);

		D3DXMatrixIdentity(&parts->mtxWorld);			// �s�񏉊����֐�

		// �����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			parts->rot.y,
			parts->rot.x,
			parts->rot.z);								// �s���]�֐�

		D3DXMatrixMultiply(&parts->mtxWorld,
			&parts->mtxWorld,
			&mtxRot);									// �s��|���Z�֐� 

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans,
			parts->pos.x,
			parts->pos.y,
			parts->pos.z);								// �s��ړ��֐�

		D3DXMatrixMultiply(&parts->mtxWorld,
			&parts->mtxWorld,
			&mtxTrans);									// �s��|���Z�֐�

		// �e�p�[�c�̃��[���h�}�g���b�N�X��ێ�
		D3DXMATRIX mtxParent;

		if (parts->nIdxModelParent == -1)
		{// �e���f���̃C���f�b�N�X����-1�̎�
		 // �V�K�[�x�l��Z�o�b�t�@�̐[�x�l�������l�Ȃ�e�X�g�����ɂ���
			mtxParent = mtxWorld;
		}
		else
		{// �V�K�[�x�l��Z�o�b�t�@�̐[�x�l�������l�Ȃ�e�X�g�����ɂ���
			mtxParent = (m_parts + parts->nIdxModelParent)->mtxWorld;
		}

		// �����̐e�}�g���b�N�X�Ƃ̊|���Z
		D3DXMatrixMultiply(&parts->mtxWorld, &parts->mtxWorld, &mtxParent);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &parts->mtxWorld);

		// ���݂̃}�e���A����ێ�
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)parts->material.pBuffer->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)parts->material.nNumMat; nCntMat++)
		{// �}�e���A�����̐ݒ�
			D3DMATERIAL9  matD3D = pMat[nCntMat].MatD3D;

			// ������F�ɐݒ�
			matD3D.Diffuse = col;

			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&matD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pTexture->GetTexture(parts->material.pNumTex[nCntMat]));

			// �v���C���[�p�[�c�̕`��
			parts->material.pMesh->DrawSubset(nCntMat);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, nullptr);
		}

		// �ۂ��Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}

	// �V�K�[�x�l��Z�o�b�t�@�̐[�x�l�������l�Ȃ�e�X�g�����ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}

//=============================================================================
// ���[�V�����̍Đ�
// Author : �������l
// �T�v : �ړI�̈ʒu�܂œ���̃t���[�����œ������鏈�����p�[�c���Ƃɍs��
//=============================================================================
bool CMotion::PlayMotion(const int nCntMotionSet)
{
	CMotion::MyMotion *motion = (m_motion + nCntMotionSet);

	for (int nCntParts = 0; nCntParts < m_nMaxParts; nCntParts++)
	{
		CMotion::Parts* parts = (m_parts + nCntParts);

		if (motion->nCntFrame == 0)
		{// �t���[���J�E���g��0�̎�
			// �ړI�̈ʒu�ƌ����̎Z�o
			parts->posDest = (parts->posOrigin + motion->keySet[motion->nCntKeySet].key[nCntParts].pos) - parts->pos;
			parts->rotDest = (parts->rotOrigin + motion->keySet[motion->nCntKeySet].key[nCntParts].rot) - parts->rot;

			// �p�x�̐��K��
			parts->rotDest.x = RotNormalization(parts->rotDest.x);
			parts->rotDest.y = RotNormalization(parts->rotDest.y);
			parts->rotDest.z = RotNormalization(parts->rotDest.z);
		}

		// �ϐ��錾
		D3DXVECTOR3 addPos = D3DXVECTOR3(parts->posDest / (float)(motion->keySet[motion->nCntKeySet].nFrame));
		D3DXVECTOR3 addRot = D3DXVECTOR3(parts->rotDest / (float)(motion->keySet[motion->nCntKeySet].nFrame));

		// �ʒu�̉��Z
		parts->pos += addPos;

		//	�����̉��Z
		parts->rot += addRot;

		// �p�x�̐��K��
		parts->rot.x = RotNormalization(parts->rot.x);
		parts->rot.y = RotNormalization(parts->rot.y);
		parts->rot.z = RotNormalization(parts->rot.z);
	}

	// �t���[���J�E���g�̉��Z
	motion->nCntFrame++;

	if (motion->nCntFrame >= motion->keySet[motion->nCntKeySet].nFrame)
	{// �t���[���J�E���g���w��̃t���[�����𒴂����ꍇ
		// �t���[�����̏�����
		motion->nCntFrame = 0;

		// �Đ����̃L�[�ԍ����̉��Z
		motion->nCntKeySet++;

		if (motion->nCntKeySet >= motion->nNumKey && motion->bLoop)
		{// �Đ����̃L�[���J�E���g���L�[���̍ő�l�𒴂����Ƃ��A���̃��[�V���������[�v���g�p���Ă���
			// �Đ����̃L�[���J�E���g��������
			motion->nCntKeySet = 0;

		}
		else if (motion->nCntKeySet >= motion->nNumKey)
		{
			motion->nCntKeySet = 0;
			return false;
		}
	}

	return true;
}

//=============================================================================
// ���[�V�����u�����h
// Author : �������l
// �T�v : ���[�V�����ƃ��[�V�����̂Ȃ��ڂ𒲐�����
// �Ԃ�l : ���[�V�����u�����h�g�p�̉�
//=============================================================================
bool CMotion::MotionBlend(const int nCntMotionSet)
{
	CMotion::MyMotion* motion = (m_motion + nCntMotionSet);

	for (int nCntParts = 0; nCntParts < m_nMaxParts; nCntParts++)
	{
		CMotion::Parts* parts = (m_parts + nCntParts);

		if (motion->nCntFrame == 0)
		{// �t���[���J�E���g��0�̎�
			// �ړI�̈ʒu�ƌ����̎Z�o
			CMotion::MyKey myKey = motion->keySet[motion->nCntKeySet].key[nCntParts];
			parts->posDest = parts->posOrigin + myKey.pos - parts->pos;
			parts->rotDest = parts->rotOrigin + myKey.rot - parts->rot;

			// �p�x�̐��K��
			parts->rotDest.x = RotNormalization(parts->rotDest.x);
			parts->rotDest.y = RotNormalization(parts->rotDest.y);
			parts->rotDest.z = RotNormalization(parts->rotDest.z);
		}

		// �ϐ��錾
		D3DXVECTOR3 addPos = D3DXVECTOR3(parts->posDest / (float)(MOTION_BLEND_FRAM));
		D3DXVECTOR3 addRot = D3DXVECTOR3(parts->rotDest / (float)(MOTION_BLEND_FRAM));

		// �ʒu�̉��Z
		parts->pos += addPos;

		//	�����̉��Z
		parts->rot += addRot;

		// �p�x�̐��K��
		parts->rotDest.x = RotNormalization(parts->rotDest.x);
		parts->rotDest.y = RotNormalization(parts->rotDest.y);
		parts->rotDest.z = RotNormalization(parts->rotDest.z);
	}

	// �t���[���J�E���g�̉��Z
	motion->nCntFrame++;

	if (motion->nCntFrame >= MOTION_BLEND_FRAM)
	{// �t���[���J�E���g���w��̃t���[�����𒴂����ꍇ

		motion->nCntFrame = 0;	// �t���[�����̏�����
		motion->nCntKeySet++;	// �Đ����̃L�[�ԍ����̉��Z

		return false;
	}

	return true;
}

//=============================================================================
// �p�[�c�ƃ��[�V�����̓ǂݍ���
// Author : �������l
// �T�v : �p�[�c�ƃ��[�V�����̓ǂݍ��݁A���������Ăяo��
//=============================================================================
void CMotion::LoodSetMotion(const char * pFileName)
{
	// ���f���}�l�[�W���[�N���X�̐ݒ�
	CModelManager *pModelManager = CApplication::GetModelManager();

	// �ϐ��錾
	char aString[128] = {};			// �������r�p�̕ϐ�
	char g_aEqual[128] = {};		// ���ǂݍ��ݗp�ϐ�
	int	nCntKeySet = 0;				// KeySet�J�E���g
	int	nCntKey = 0;				// Key�J�E���g
	int nCntFileName = 0;			// �t�@�C����
	int nCntParts = 0;				// �p�[�c���̃J�E���g
	int nCntMotion = 0;				// ���[�V�������̃J�E���g

	// �t�@�C���|�C���^�̐錾
	FILE * pFile;

	//�t�@�C�����J��
	pFile = fopen(pFileName, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		fscanf(pFile, "%s", &aString);

		while (strncmp(&aString[0], "SCRIPT", 6) != 0)
		{// �����񂪈�v�����ꍇ
			aString[0] = {};
			// ������̓ǂݍ���
			fscanf(pFile, "%s", &aString[0]);
		}
		while (strncmp(&aString[0], "END_SCRIPT", 10) != 0)
		{
			fscanf(pFile, "%s", &aString[0]);

			if (strncmp(&aString[0], "#", 1) == 0)
			{// ���ǂݍ���
				fgets(&aString[0], sizeof(aString), pFile);
			}

			if (strcmp(&aString[0], "MODEL_FILENAME") == 0)
			{// �t�@�C�����̓ǂݍ���
				fscanf(pFile, "%s", &g_aEqual[0]);
				fscanf(pFile, "%s", &m_partsFile[nCntFileName].aName[0]);
				nCntFileName++;
			}

			if (strcmp(&aString[0], "CHARACTERSET") == 0)
			{// �L�����N�^�[�̓ǂݍ���
				while (strcmp(&aString[0], "END_CHARACTERSET") != 0)
				{
					fscanf(pFile, "%s", &aString[0]);

					if (strncmp(&aString[0], "#", 1) == 0)
					{// ���ǂݍ���
						fgets(&aString[0], sizeof(aString), pFile);
					}

					if (strcmp(&aString[0], "NUM_PARTS") == 0)
					{// �ǂݍ��ރp�[�c��
						fscanf(pFile, "%s", &g_aEqual[0]);
						fscanf(pFile, "%d", &m_nMaxParts);

						// �������̉��
						m_parts = new Parts[m_nMaxParts];
						m_motion = new MyMotion[MAX_MOTION];
						assert(m_parts != nullptr && m_motion != nullptr);
					}

					if (strcmp(&aString[0], "PARTSSET") == 0)
					{// �p�[�c�̓ǂݍ���
						while (strcmp(&aString[0], "END_PARTSSET") != 0)
						{
							fscanf(pFile, "%s", &aString[0]);

							if (strncmp(&aString[0], "#", 1) == 0)
							{// ���ǂݍ���
								fgets(&aString[0], sizeof(aString), pFile);
							}

							if (strcmp(&aString[0], "INDEX") == 0)
							{// �^�C�v�̓ǂݍ���
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &m_parts[nCntParts].nType);

								for (int nCntModel = 0; nCntModel < pModelManager->GetMaxModelMaterial(); nCntModel++)
								{
									if (strcmp(&m_partsFile[m_parts[nCntParts].nType].aName[0], pModelManager->GetFileName(nCntModel)) == 0)
									{
										m_parts[nCntParts].nType = nCntModel;
										break;
									}
								}
							}
							if (strcmp(&aString[0], "PARENT") == 0)
							{// �e�̓ǂݍ���
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &m_parts[nCntParts].nIdxModelParent);
							}
							if (strcmp(&aString[0], "POS") == 0)
							{// �ʒu�̓ǂݍ���
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &m_parts[nCntParts].pos.x);
								fscanf(pFile, "%f", &m_parts[nCntParts].pos.y);
								fscanf(pFile, "%f", &m_parts[nCntParts].pos.z);
							}
							if (strcmp(&aString[0], "ROT") == 0)
							{// �����̓ǂݍ���
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &m_parts[nCntParts].rot.x);
								fscanf(pFile, "%f", &m_parts[nCntParts].rot.y);
								fscanf(pFile, "%f", &m_parts[nCntParts].rot.z);
							}
						}

						// �p�[�c�J�E���g�̃C���N�������g
						nCntParts++;
					}
				}
			}
			if (strcmp(&aString[0], "MOTIONSET") == 0)
			{// ���[�V�����̓ǂݍ���
				while (strcmp(&aString[0], "END_MOTIONSET") != 0)
				{
					fscanf(pFile, "%s", &aString[0]);

					if (strncmp(&aString[0], "#", 1) == 0)
					{// ���ǂݍ���
						fgets(&aString[0], sizeof(aString), pFile);
					}

					if (strcmp(&aString[0], "LOOP") == 0)
					{// ���[�v�L���̓ǂݍ���
						fscanf(pFile, "%s", &g_aEqual[0]);
						fscanf(pFile, "%d", (int*)(&m_motion[nCntMotion].bLoop));
					}
					if (strcmp(&aString[0], "NUM_KEY") == 0)
					{// �L�[���̓ǂݍ���
						fscanf(pFile, "%s", &g_aEqual[0]);
						fscanf(pFile, "%d", &m_motion[nCntMotion].nNumKey);
					}
					if (strcmp(&aString[0], "KEYSET") == 0)
					{// �L�[�Z�b�g�̓ǂݍ���
						while (strcmp(&aString[0], "END_KEYSET") != 0)
						{
							fscanf(pFile, "%s", &aString[0]);

							if (strncmp(&aString[0], "#", 1) == 0)
							{// ���ǂݍ���
								fgets(&aString[0], sizeof(aString), pFile);
							}

							if (strcmp(&aString[0], "FRAME") == 0)
							{// �t���[�����̓ǂݍ���
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &m_motion[nCntMotion].keySet[nCntKeySet].nFrame);
							}
							if (strcmp(&aString[0], "KEY") == 0)
							{// �L�[�̓ǂݍ���
								while (strcmp(&aString[0], "END_KEY") != 0)
								{
									fscanf(pFile, "%s", &aString[0]);

									if (strncmp(&aString[0], "#", 1) == 0)
									{// ���ǂݍ���
										fgets(&aString[0], sizeof(aString), pFile);
									}

									if (strcmp(&aString[0], "POS") == 0)
									{// �ʒu�̓ǂݍ���
										fscanf(pFile, "%s", &g_aEqual[0]);
										fscanf(pFile, "%f", &m_motion[nCntMotion].keySet[nCntKeySet].key[nCntKey].pos.x);
										fscanf(pFile, "%f", &m_motion[nCntMotion].keySet[nCntKeySet].key[nCntKey].pos.y);
										fscanf(pFile, "%f", &m_motion[nCntMotion].keySet[nCntKeySet].key[nCntKey].pos.z);
									}
									if (strcmp(&aString[0], "ROT") == 0)
									{// �����̓ǂݍ���
										fscanf(pFile, "%s", &g_aEqual[0]);
										fscanf(pFile, "%f", &m_motion[nCntMotion].keySet[nCntKeySet].key[nCntKey].rot.x);
										fscanf(pFile, "%f", &m_motion[nCntMotion].keySet[nCntKeySet].key[nCntKey].rot.y);
										fscanf(pFile, "%f", &m_motion[nCntMotion].keySet[nCntKeySet].key[nCntKey].rot.z);
									}
								}

								// �L�[�J�E���g�̃C���N�������g
								nCntKey++;
							}
						}

						// �L�[�J�E���g�̏�����
						nCntKey = 0;

						// �L�[�Z�b�g�J�E���g�̃C���N�������g
						nCntKeySet++;
					}
				}
				// �L�[�Z�b�g�J�E���g�̏�����
				nCntKeySet = 0;

				// �p�[�c���̃C���N�������g
				nCntMotion++;
			}
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ��ꍇ
		assert(false);
	}

	// ������
	Init();
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �������̉��
//=============================================================================
void CMotion::Uninit(void)
{
	if (m_parts != nullptr
		&& m_motion != nullptr)
	{// �������̉��
		delete[] m_parts;
		delete[] m_motion;
		m_parts = nullptr;
	}
}

//=============================================================================
// �J�E���g�̃��Z�b�g
// Author : �������l
// �T�v : �J�E���g�̃��Z�b�g
//=============================================================================
void CMotion::CntReset(const int nNumMotionOld)
{
	m_motion[nNumMotionOld].nCntFrame = 0;
	m_motion[nNumMotionOld].nCntKeySet = 0;
}

//=============================================================================
// ���[�V�����̍ēǂݍ���
// Author : �������l
// �T�v : ���݂̃��[�V������j�����āA�ʂ̃��[�V������ǂݍ���
//=============================================================================
void CMotion::ReloadMotion(const char * pFileName)
{// �I��
	Uninit();

	// �p�[�c���̏�����
	memset(&m_partsFile, 0, sizeof(m_partsFile));

	// ���[�V�����̏�����
	memset(&m_motion, 0, sizeof(m_motion));

	// �p�[�c�̏�����
	memset(&m_parts, 0, sizeof(m_parts));

	// �p�[�c���̏�����
	m_nMaxParts = 0;

	// ���[�V�����̓ǂݍ���
	LoodSetMotion(pFileName);
}


