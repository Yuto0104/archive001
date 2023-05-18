//**************************************************************************************************
//
// �t�@�C���ǂݍ��ݏ���(set_file.cpp)
// Auther�F�������l
//
//**************************************************************************************************

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include<stdio.h>
#include "main.h"
#include "set_file.h"
#include"file.h"
#include"model.h"

//***************************************************************************
// �}�N����`
//***************************************************************************
#define LOOD_FILE_NAME_000		"model.txt"

//***************************************************************************
// �O���[�o���ϐ�
//***************************************************************************
static D3DXVECTOR3		g_modelpos;
static D3DXVECTOR3		g_modelrot;
static int				g_modelType;
static char				g_modelFile[128];
static char				g_aString[128];
static char				g_aEqual[128] = {};

//---------------------------------------------------------------------------
// �t�@�C���ǂݍ��ݏ���
//---------------------------------------------------------------------------
void LoodSetFile(void)
{
	// �t�@�C���|�C���^�̐錾
	FILE * pFile;

	char aFile[128] = FILE_3D_STAGE;
	strcat(aFile, LOOD_FILE_NAME_000);

	ModelFile *pModelFile = GetModelFile();

	//�t�@�C�����J��
	pFile = fopen(aFile, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		fscanf(pFile, "%s", &g_aString);

		while (strncmp(&g_aString[0], "SCRIPT", 6) != 0)
		{// �����񂪈�v����܂ŏꍇ
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
				fscanf(pFile, "%s", &pModelFile->aName[0]);
				pModelFile++;
			}
			if (strcmp(&g_aString[0], "MODELSET") == 0)
			{// �����񂪈�v�����ꍇ
				while (strcmp(&g_aString[0], "END_MODELSET") != 0)
				{
					// ������̓ǂݍ���
					fscanf(pFile, "%s", &g_aString[0]);

					if (strcmp(&g_aString[0], "POS") == 0)
					{// �����񂪈�v�����ꍇ
						fscanf(pFile, "%s", &g_aEqual[0]);
						fscanf(pFile, "%f", &g_modelpos.x);
						fscanf(pFile, "%f", &g_modelpos.y);
						fscanf(pFile, "%f", &g_modelpos.z);
					}
					if (strcmp(&g_aString[0], "ROT") == 0)
					{// �����񂪈�v�����ꍇ
						fscanf(pFile, "%s", &g_aEqual[0]);
						fscanf(pFile, "%f", &g_modelrot.x);
						fscanf(pFile, "%f", &g_modelrot.y);
						fscanf(pFile, "%f", &g_modelrot.z);
					}
					if (strcmp(&g_aString[0], "TYPE") == 0)
					{// �����񂪈�v�����ꍇ
						fscanf(pFile, "%s", &g_aEqual[0]);
						fscanf(pFile, "%d", &g_modelType);
					}
				}

				// ���f���̐ݒu
				SetModel(g_modelpos, g_modelrot, g_modelType);
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
// �t�@�C���X�V����
//---------------------------------------------------------------------------
void OutputSetFile(void)
{

}