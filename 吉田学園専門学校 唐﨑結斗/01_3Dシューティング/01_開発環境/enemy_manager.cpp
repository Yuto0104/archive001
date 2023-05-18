//=============================================================================
//
// �G�l�~�[�}�l�[�W���[����(enemy_manager.h)
// Author : �������l
// �T�v : �G�l�~�[�}�l�[�W���[���s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <stdio.h>
#include <assert.h>

#include "enemy_manager.h"
#include "renderer.h"
#include "application.h"
#include "game.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : �X�R�A�𐶐�����
//=============================================================================
CEnemyManager *CEnemyManager::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CEnemyManager *pEnemyManager = nullptr;

	pEnemyManager = new CEnemyManager;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pEnemyManager != nullptr);

	// ������
	pEnemyManager->Init();

	// �C���X�^���X��Ԃ�
	return pEnemyManager;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CEnemyManager::CEnemyManager()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ߋ��̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �傫��
	m_status = nullptr;									// �G�̃X�e�[�^�X
	m_arrangement = nullptr;							// �G�̔z�u
	m_move = nullptr;									// �ړ����
	m_nMaxType = 0;										// ��ނ̍ő吔
	m_nMaxInstall = 0;									// �ő�ݒu��
	m_nMaxMove = 0;										// �ړ����
	m_nCntFrame = 0;									// �t���[���J�E���g
	m_nGameEndFrame = 0;								// �Q�[���̏I������
	m_nCntSetEnemy = 0;									// �G�̐ݒu�J�E���g
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CEnemyManager::~CEnemyManager()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CEnemyManager::Init()
{
	// �t�@�C���̓ǂݍ���
	LoadFile("data/FILE/enemy.txt");

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CEnemyManager::Uninit()
{
	if (m_status != nullptr)
	{// �I������
	 // �������̉��
		delete m_status;
		m_status = nullptr;
	}

	if (m_arrangement != nullptr)
	{// �I������
	 // �������̉��
		delete m_arrangement;
		m_arrangement = nullptr;
	}

	if (m_move != nullptr)
	{// �I������
	 // �������̉��
		delete m_move;
		m_move = nullptr;
	}

	// �X�R�A�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V���s��
//=============================================================================
void CEnemyManager::Update()
{
	if (m_arrangement != nullptr)
	{// �t���[���J�E���g�̃C���N�������g
		m_nCntFrame++;

		// �G�̔z�u
		SetEnemy();

		// �Q�[���I��
		if (m_nCntFrame >= m_nGameEndFrame)
		{
			CGame::SetGame(false);
		}
	}	
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CEnemyManager::Draw()
{

}

//=============================================================================
// �t�@�C���̓ǂݍ���
// Author : �������l
// �T�v : �t�@�C����ǂݍ���
//=============================================================================
void CEnemyManager::LoadFile(char *pFileName)
{
	// �ϐ��錾
	char aStr[128];
	int nCntStatus = 0;
	int nCntArrangement = 0;
	int nCntMove = 0;
	int nCntMoveKey = 0;

	// �t�@�C���̓ǂݍ���
	FILE *pFile = fopen(pFileName, "r");

	if (pFile != nullptr)
	{
		while (fscanf(pFile, "%s", &aStr[0]) != EOF)
		{// "EOF"��ǂݍ��ނ܂� 

			if (strstr(&aStr[0], "MAX_TYPE") != NULL)
			{
				fscanf(pFile, "%s", &aStr[0]);
				fscanf(pFile, "%d", &m_nMaxType);
				m_status = new ENEMY_STATUS[m_nMaxType];
				assert(m_status != nullptr);
				memset(&m_status[0], 0, sizeof(m_status));
			}

			if (strstr(&aStr[0], "GAME_END_FRAME") != NULL)
			{
				fscanf(pFile, "%s", &aStr[0]);
				fscanf(pFile, "%d", &m_nGameEndFrame);
			}

			if (strstr(&aStr[0], "MAX_INSTALL") != NULL)
			{
				fscanf(pFile, "%s", &aStr[0]);
				fscanf(pFile, "%d", &m_nMaxInstall);

				if (m_arrangement != nullptr)
				{// �I������
				 // �������̉��
					delete m_arrangement;
					m_arrangement = nullptr;
				}

				m_arrangement = new ENEMY_ARRANGEMENT[m_nMaxInstall];
				assert(m_arrangement != nullptr);
				memset(&m_arrangement[0], 0, sizeof(m_arrangement));
			}

			if (strstr(&aStr[0], "MAX_MOVE") != NULL)
			{
				fscanf(pFile, "%s", &aStr[0]);
				fscanf(pFile, "%d", &m_nMaxMove);
				m_move = new CEnemy3D::ENEMY_MOVE[m_nMaxMove];
				assert(m_move != nullptr);
				memset(&m_move[0], 0, sizeof(m_move));
			}

			if (strstr(&aStr[0], "STATUS_SET") != NULL)
			{
				while (strstr(&aStr[0], "STATUS_END") == NULL)
				{
					fscanf(pFile, "%s", &aStr[0]);

					if (strstr(&aStr[0], "SCORE") != NULL)
					{// ���f���̃t�@�C�����̐ݒ�
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%d", &m_status[nCntStatus].nScore);
					}

					if (strstr(&aStr[0], "COLLISION_SIZE") != NULL)
					{// ���f���̃t�@�C�����̐ݒ�
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%f", &m_status[nCntStatus].collisionSize.x);
						fscanf(pFile, "%f", &m_status[nCntStatus].collisionSize.y);
						fscanf(pFile, "%f", &m_status[nCntStatus].collisionSize.z);
					}

					if (strstr(&aStr[0], "SIZE") != NULL)
					{// ���f���̃t�@�C�����̐ݒ�
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%f", &m_status[nCntStatus].size.x);
						fscanf(pFile, "%f", &m_status[nCntStatus].size.y);
						fscanf(pFile, "%f", &m_status[nCntStatus].size.z);
					}

					if (strstr(&aStr[0], "COLOR") != NULL)
					{// �J���[�^�C�v�̐ݒ�
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%s", &aStr[0]);

						if (strstr(&aStr[0], "BLACK") != NULL)
						{
							m_status[nCntStatus].colorType = CObject::TYPE_BLACK;
						}
						else if(strstr(&aStr[0], "WHITE") != NULL)
						{
							m_status[nCntStatus].colorType = CObject::TYPE_WHITE;
						}
					}

					if (strstr(&aStr[0], "MODEL_ID") != NULL)
					{// ���f���̃t�@�C�����̐ݒ�
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%d", &m_status[nCntStatus].nModelID);
					}

					if (strstr(&aStr[0], "LIFE") != NULL)
					{// ���f���̃t�@�C�����̐ݒ�
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%d", &m_status[nCntStatus].nLife);
					}

					if (strstr(&aStr[0], "SCORE") != NULL)
					{// ���f���̃t�@�C�����̐ݒ�
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%d", &m_status[nCntStatus].nScore);
					}

					if (strstr(&aStr[0], "CNTSHOT") != NULL)
					{// ���f���̃t�@�C�����̐ݒ�
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%d", &m_status[nCntStatus].nMaxShot);
					}

					if (strstr(&aStr[0], "SHOT_ID") != NULL)
					{// ���f���̃t�@�C�����̐ݒ�
						int nShotID = 0;
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%d", &nShotID);
						m_status[nCntStatus].shotMode = (CEnemy3D::SHOT_MODE)nShotID;
					}

					if (strstr(&aStr[0], "SHOT_SPEED") != NULL)
					{// ���f���̃t�@�C�����̐ݒ�
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%f", &m_status[nCntStatus].fBulletSpeed);
					}

					if (strstr(&aStr[0], "SHOT_ROT") != NULL)
					{// ���f���̃t�@�C�����̐ݒ�
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%f", &m_status[nCntStatus].fBulletRot);
					}

					if (strstr(&aStr[0], "DIFFUSIONWIDTH") != NULL)
					{// ���f���̃t�@�C�����̐ݒ�
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%f", &m_status[nCntStatus].fDiffusionWidth);
					}

					if (strstr(&aStr[0], "MAXBULLET") != NULL)
					{// ���f���̃t�@�C�����̐ݒ�
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%d", &m_status[nCntStatus].nMaxBullet);
					}

					if (strstr(&aStr[0], "COEFFBULLET") != NULL)
					{// ���f���̃t�@�C�����̐ݒ�
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%f", &m_status[nCntStatus].fCoeffBullet);
					}
				}

				nCntStatus++;
			}

			if (strstr(&aStr[0], "ARRANGEMENT_SET") != NULL)
			{
				while (strstr(&aStr[0], "ARRANGEMENT_END") == NULL)
				{
					fscanf(pFile, "%s", &aStr[0]);

					if (strstr(&aStr[0], "POS") != NULL)
					{// �J���[�^�C�v�̐ݒ�
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%f", &m_arrangement[nCntArrangement].pos.x);
						fscanf(pFile, "%f", &m_arrangement[nCntArrangement].pos.y);
						fscanf(pFile, "%f", &m_arrangement[nCntArrangement].pos.z);
					}

					if (strstr(&aStr[0], "MOVE_ID") != NULL)
					{// ���f���̃t�@�C�����̐ݒ�
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%d", &m_arrangement[nCntArrangement].nMoveID);
					}

					if (strstr(&aStr[0], "FRAME") != NULL)
					{// ���f���̃t�@�C�����̐ݒ�
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%d", &m_arrangement[nCntArrangement].nFrame);
					}

					if (strstr(&aStr[0], "ID") != NULL)
					{// ���f���̃t�@�C�����̐ݒ�
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%d", &m_arrangement[nCntArrangement].nID);
					}

					if (strstr(&aStr[0], "DRAW_TYPE") != NULL)
					{// ���f���̃t�@�C�����̐ݒ�
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%d", &m_arrangement[nCntArrangement].nDrawType);
					}
				}

				nCntArrangement++;
			}

			if (strstr(&aStr[0], "MOVE_SET") != NULL)
			{
				while (strstr(&aStr[0], "MOVE_END") == NULL)
				{
					fscanf(pFile, "%s", &aStr[0]);

					if (strstr(&aStr[0], "MAX_KEY") != NULL)
					{// ���f���̃t�@�C�����̐ݒ�
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%d", &m_move[nCntMove].nMaxKey);

						m_move[nCntMove].moveKey = new CEnemy3D::ENEMY_MOVE_KEY[m_move[nCntMove].nMaxKey];
						assert(m_move[nCntMove].moveKey != nullptr);
						memset(&m_move[nCntMove].moveKey[0], 0, sizeof(m_move[nCntMove].moveKey));
					}

					if (strstr(&aStr[0], "LOOP") != NULL)
					{// ���f���̃t�@�C�����̐ݒ�
						int nBool = 0;
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%d", &nBool);

						if (nBool == 0)
						{
							m_move[nCntMove].bLoop = false;
						}
						else
						{
							m_move[nCntMove].bLoop = true;
						}
					}
					
					if (strstr(&aStr[0], "KEY_SET") != NULL)
					{
						while (strstr(&aStr[0], "KEY_END") == NULL)
						{
							fscanf(pFile, "%s", &aStr[0]);

							if (strstr(&aStr[0], "FRAME") != NULL)
							{// ���f���̃t�@�C�����̐ݒ�
								fscanf(pFile, "%s", &aStr[0]);
								fscanf(pFile, "%d", &m_move[nCntMove].moveKey[nCntMoveKey].nFrame);
							}

							if (strstr(&aStr[0], "MOVE_MODE") != NULL)
							{// ���f���̃t�@�C�����̐ݒ�
								fscanf(pFile, "%s", &aStr[0]);
								fscanf(pFile, "%d", &m_move[nCntMove].moveKey[nCntMoveKey].moveMode);
							}
							
							if (strcmp(&aStr[0], "MOVE_VEC") == 0)
							{// �L�[���̓ǂݍ���
								fscanf(pFile, "%s", &aStr[0]);
								fscanf(pFile, "%f", &m_move[nCntMove].moveKey[nCntMoveKey].fMoveVec);
							}

							if (strstr(&aStr[0], "SPEED") != NULL)
							{// ���f���̃t�@�C�����̐ݒ�
								fscanf(pFile, "%s", &aStr[0]);
								fscanf(pFile, "%f", &m_move[nCntMove].moveKey[nCntMoveKey].fSpeed);
							}

							if (strstr(&aStr[0], "WAVE_LENGTH") != NULL)
							{// ���f���̃t�@�C�����̐ݒ�
								fscanf(pFile, "%s", &aStr[0]);
								fscanf(pFile, "%f", &m_move[nCntMove].moveKey[nCntMoveKey].fWaveLength);
							}

							if (strstr(&aStr[0], "WAVE_SIZE") != NULL)
							{// ���f���̃t�@�C�����̐ݒ�
								fscanf(pFile, "%s", &aStr[0]);
								fscanf(pFile, "%f", &m_move[nCntMove].moveKey[nCntMoveKey].fWaveSize);
							}

							if (strcmp(&aStr[0], "ADD_MOVE_VEC") == 0)
							{// �L�[���̓ǂݍ���
								fscanf(pFile, "%s", &aStr[0]);
								fscanf(pFile, "%f", &m_move[nCntMove].moveKey[nCntMoveKey].fAddMoveVec);
							}
						}

						nCntMoveKey++;
					}
				}

				nCntMove++;
				nCntMoveKey = 0;
			}
		}
	}
	else
	{
		assert(false);
	}
}

//=============================================================================
// �G�̐ݒu
// Author : �������l
// �T�v : �G�̐ݒu���s��
//=============================================================================
void CEnemyManager::SetEnemy()
{
	CEnemy3D* pEnemy = nullptr;

	for (int nCntEnemy = 0; nCntEnemy < m_nMaxInstall; nCntEnemy++)
	{
		if (m_arrangement[nCntEnemy].nFrame == m_nCntFrame)
		{
			int nID = m_arrangement[nCntEnemy].nID;

			pEnemy = CEnemy3D::Create(m_status[nID].nModelID);
			pEnemy->SetColisonSize(m_status[nID].collisionSize);
			pEnemy->SetColorType(m_status[nID].colorType);
			pEnemy->SetSize(m_status[nID].size);
			pEnemy->SetLife(m_status[nID].nLife);
			pEnemy->SetScore(m_status[nID].nScore);
			pEnemy->SetMaxShot(m_status[nID].nMaxShot);
			pEnemy->SetShotMode(m_status[nID].shotMode);
			pEnemy->SetBulletSpeed(m_status[nID].fBulletSpeed);
			pEnemy->SetBulletRot(m_status[nID].fBulletRot);
			pEnemy->SetDiffusionWidth(m_status[nID].fDiffusionWidth);
			pEnemy->SetCoeffBullet(m_status[nID].fCoeffBullet);
			pEnemy->SetMaxBullet(m_status[nID].nMaxBullet);
			pEnemy->SetPos(m_arrangement[nCntEnemy].pos);
			pEnemy->SetObjectDrowType((EObjectDrowType)m_arrangement[nCntEnemy].nDrawType);
			pEnemy->SetMoveData(m_move[m_arrangement[nCntEnemy].nMoveID]);
			m_nCntSetEnemy++;
		}
	}	
}

