//**************************************************************************************************
//
// ���[�V�����ǂݍ��ݏ���(set_file.cpp)
// Auther�F�������l
//
//**************************************************************************************************

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include<stdio.h>
#include "main.h"
#include "set_motion.h"
#include"file.h"
#include"model.h"
#include"camera.h"

//***************************************************************************
// �}�N����`
//***************************************************************************
#define LOOD_FILE_NAME_000		"model.txt"

//***************************************************************************
// �O���[�o���ϐ�
//***************************************************************************
static char				g_aString[128];
static char				g_aEqual[128] = {};
static PlayerSet		g_PlayerSet;

//---------------------------------------------------------------------------
// ���[�V�����ǂݍ��ݏ���
//---------------------------------------------------------------------------
void LoodSetMotion(char *pFileName)
{
	// ���[�V�����ǂݍ��ݏ��̏�����
	memset(&g_PlayerSet, 0, sizeof(g_PlayerSet));

	Player *pPlayer = GetPlayer();
	PlayerFile *pPlayerFile = GetPlayerFile();
	MotionSet *pMotionSet = GetMotionSet();

	// �t�@�C���|�C���^�̐錾
	FILE * pFile;

	char aFile[128] = FILE_MOTION_DATA;
	strcat(aFile, pFileName);

	//�t�@�C�����J��
	pFile = fopen(aFile, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		fscanf(pFile, "%s", &g_aString);

		while (strncmp(&g_aString[0], "SCRIPT",6) != 0)
		{// �����񂪈�v�����ꍇ
			g_aString[0] = {};
			// ������̓ǂݍ���
			fscanf(pFile, "%s", &g_aString[0]);
		}
		while (strncmp(&g_aString[0], "END_SCRIPT", 10) != 0)
		{
			fscanf(pFile, "%s", &g_aString[0]);

			if (strncmp(&g_aString[0], "#", 1) == 0)
			{// ���ǂݍ���
				fgets(&g_aString[0], sizeof(g_aString), pFile);
			}

			if (strcmp(&g_aString[0], "MODEL_FILENAME") == 0)
			{// �t�@�C�����̓ǂݍ���
				fscanf(pFile, "%s", &g_aEqual[0]);
				fscanf(pFile, "%s", &pPlayerFile->aName[0]);
				pPlayerFile++;
			}

			if (strcmp(&g_aString[0], "CHARACTERSET") == 0)
			{// �L�����N�^�[�̓ǂݍ���
				while (strcmp(&g_aString[0], "END_CHARACTERSET") != 0)
				{
					fscanf(pFile, "%s", &g_aString[0]);

					if (strncmp(&g_aString[0], "#", 1) == 0)
					{// ���ǂݍ���
						fgets(&g_aString[0], sizeof(g_aString), pFile);
					}

					if (strcmp(&g_aString[0], "NUM_PARTS") == 0)
					{// �ǂݍ��ރp�[�c��
						fscanf(pFile, "%s", &g_aEqual[0]);
						fscanf(pFile, "%d", &pPlayer->nMaxModelParts);//���������ɂ��Ȃ�����߂�
					}

					if (strcmp(&g_aString[0], "PARTSSET") == 0)
					{// �p�[�c�̓ǂݍ���
						while (strcmp(&g_aString[0], "END_PARTSSET") != 0)
						{
							fscanf(pFile, "%s", &g_aString[0]);

							if (strncmp(&g_aString[0], "#", 1) == 0)
							{// ���ǂݍ���
								fgets(&g_aString[0], sizeof(g_aString), pFile);
							}

							if (strcmp(&g_aString[0], "INDEX") == 0)
							{// �^�C�v�̓ǂݍ���
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &pPlayer->modeParts[g_PlayerSet.nCntModelParts].nType);
							}
							if (strcmp(&g_aString[0], "PARENT") == 0)
							{// �e�̓ǂݍ���
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &pPlayer->modeParts[g_PlayerSet.nCntModelParts].nIdxModelParent);
							}
							if (strcmp(&g_aString[0], "POS") == 0)
							{// �ʒu�̓ǂݍ���
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &pPlayer->modeParts[g_PlayerSet.nCntModelParts].pos.x);
								fscanf(pFile, "%f", &pPlayer->modeParts[g_PlayerSet.nCntModelParts].pos.y);
								fscanf(pFile, "%f", &pPlayer->modeParts[g_PlayerSet.nCntModelParts].pos.z);
							}
							if (strcmp(&g_aString[0], "ROT") == 0)
							{// �����̓ǂݍ���
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &pPlayer->modeParts[g_PlayerSet.nCntModelParts].rot.x);
								fscanf(pFile, "%f", &pPlayer->modeParts[g_PlayerSet.nCntModelParts].rot.y);
								fscanf(pFile, "%f", &pPlayer->modeParts[g_PlayerSet.nCntModelParts].rot.z);
							}
						}

						// �p�[�c�J�E���g�̃C���N�������g
						g_PlayerSet.nCntModelParts++;
					}
				}

				// �v���C���[�̐ݒu
				SetPlayer(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					g_PlayerSet.nCntModelType,
					1);
			}
			if (strcmp(&g_aString[0], "MOTIONSET") == 0)
			{// ���[�V�����̓ǂݍ���
				while (strcmp(&g_aString[0], "END_MOTIONSET") != 0)
				{
					fscanf(pFile, "%s", &g_aString[0]);

					if (strncmp(&g_aString[0], "#", 1) == 0)
					{// ���ǂݍ���
						fgets(&g_aString[0], sizeof(g_aString), pFile);
					}

					if (strcmp(&g_aString[0], "LOOP") == 0)
					{// ���[�v�L���̓ǂݍ���
						fscanf(pFile, "%s", &g_aEqual[0]);
						fscanf(pFile, "%d", (int*)(&pMotionSet->bLoop));
					}
					if (strcmp(&g_aString[0], "NUM_KEY") == 0)
					{// �L�[���̓ǂݍ���
						fscanf(pFile, "%s", &g_aEqual[0]);
						fscanf(pFile, "%d", &pMotionSet->nNumKey);
					}
					if (strcmp(&g_aString[0], "KEYSET") == 0)
					{// �L�[�Z�b�g�̓ǂݍ���
						while (strcmp(&g_aString[0], "END_KEYSET") != 0)
						{
							fscanf(pFile, "%s", &g_aString[0]);

							if (strncmp(&g_aString[0], "#", 1) == 0)
							{// ���ǂݍ���
								fgets(&g_aString[0], sizeof(g_aString), pFile);
							}

							if (strcmp(&g_aString[0], "FRAME") == 0)
							{// �t���[�����̓ǂݍ���
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &pMotionSet->keySet[g_PlayerSet.nCntKeySet].nFrame);
							}
							if (strcmp(&g_aString[0], "KEY") == 0)
							{// �L�[�̓ǂݍ���
								while (strcmp(&g_aString[0], "END_KEY") != 0)
								{
									fscanf(pFile, "%s", &g_aString[0]);

									if (strncmp(&g_aString[0], "#", 1) == 0)
									{// ���ǂݍ���
										fgets(&g_aString[0], sizeof(g_aString), pFile);
									}

									if (strcmp(&g_aString[0], "POS") == 0)
									{// �ʒu�̓ǂݍ���
										fscanf(pFile, "%s", &g_aEqual[0]);
										fscanf(pFile, "%f", &pMotionSet->keySet[g_PlayerSet.nCntKeySet].key[g_PlayerSet.nCntKey].pos.x);
										fscanf(pFile, "%f", &pMotionSet->keySet[g_PlayerSet.nCntKeySet].key[g_PlayerSet.nCntKey].pos.y);
										fscanf(pFile, "%f", &pMotionSet->keySet[g_PlayerSet.nCntKeySet].key[g_PlayerSet.nCntKey].pos.z);
									}
									if (strcmp(&g_aString[0], "ROT") == 0)
									{// �����̓ǂݍ���
										fscanf(pFile, "%s", &g_aEqual[0]);
										fscanf(pFile, "%f", &pMotionSet->keySet[g_PlayerSet.nCntKeySet].key[g_PlayerSet.nCntKey].rot.x);
										fscanf(pFile, "%f", &pMotionSet->keySet[g_PlayerSet.nCntKeySet].key[g_PlayerSet.nCntKey].rot.y);
										fscanf(pFile, "%f", &pMotionSet->keySet[g_PlayerSet.nCntKeySet].key[g_PlayerSet.nCntKey].rot.z);
									}
								}

								// �L�[�J�E���g�̃C���N�������g
								g_PlayerSet.nCntKey++;
							}
						}

						// �L�[�J�E���g�̏�����
						g_PlayerSet.nCntKey = 0;

						// �L�[�Z�b�g�J�E���g�̃C���N�������g
						g_PlayerSet.nCntKeySet++;
					}
				}
				// �L�[�Z�b�g�J�E���g�̏�����
				g_PlayerSet.nCntKeySet = 0;

				// �p�[�c���̃C���N�������g
				pMotionSet++;
			}

		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ��ꍇ
		printf("\n * * * �t�@�C�����J���܂��� * * * \n");
	}
}

//---------------------------------------------------------------------------
// ���[�V�����X�V����
//---------------------------------------------------------------------------
void OutputSetMotion(void)
{

}