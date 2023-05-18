//**************************************************************************************************
//
// ファイル読み込み処理(set_file.cpp)
// Auther：唐﨑結斗
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include<stdio.h>
#include "main.h"
#include "set_file.h"
#include"file.h"
#include"model.h"

//***************************************************************************
// マクロ定義
//***************************************************************************
#define LOOD_FILE_NAME_000		"model.txt"

//***************************************************************************
// グローバル変数
//***************************************************************************
static D3DXVECTOR3		g_modelpos;
static D3DXVECTOR3		g_modelrot;
static int				g_modelType;
static char				g_modelFile[128];
static char				g_aString[128];
static char				g_aEqual[128] = {};

//---------------------------------------------------------------------------
// ファイル読み込み処理
//---------------------------------------------------------------------------
void LoodSetFile(void)
{
	// ファイルポインタの宣言
	FILE * pFile;

	char aFile[128] = FILE_3D_STAGE;
	strcat(aFile, LOOD_FILE_NAME_000);

	ModelFile *pModelFile = GetModelFile();

	//ファイルを開く
	pFile = fopen(aFile, "r");

	if (pFile != NULL)
	{//ファイルが開いた場合
		fscanf(pFile, "%s", &g_aString);

		while (strncmp(&g_aString[0], "SCRIPT", 6) != 0)
		{// 文字列が一致するまで場合
			g_aString[0] = {};
			// 文字列の読み込み
			fscanf(pFile, "%s", &g_aString[0]);
		}
		while (strncmp(&g_aString[0], "END_SCRIPT", 10) != 0)
		{
			fscanf(pFile, "%s", &g_aString[0]);

			if (strncmp(&g_aString[0], "#", 1) == 0)
			{// 一列読み込む
				fgets(&g_aString[0], sizeof(g_aString), pFile);
			}

			if (strcmp(&g_aString[0], "MODEL_FILENAME") == 0)
			{// ファイル名の読み込み
				fscanf(pFile, "%s", &g_aEqual[0]);
				fscanf(pFile, "%s", &pModelFile->aName[0]);
				pModelFile++;
			}
			if (strcmp(&g_aString[0], "MODELSET") == 0)
			{// 文字列が一致した場合
				while (strcmp(&g_aString[0], "END_MODELSET") != 0)
				{
					// 文字列の読み込み
					fscanf(pFile, "%s", &g_aString[0]);

					if (strcmp(&g_aString[0], "POS") == 0)
					{// 文字列が一致した場合
						fscanf(pFile, "%s", &g_aEqual[0]);
						fscanf(pFile, "%f", &g_modelpos.x);
						fscanf(pFile, "%f", &g_modelpos.y);
						fscanf(pFile, "%f", &g_modelpos.z);
					}
					if (strcmp(&g_aString[0], "ROT") == 0)
					{// 文字列が一致した場合
						fscanf(pFile, "%s", &g_aEqual[0]);
						fscanf(pFile, "%f", &g_modelrot.x);
						fscanf(pFile, "%f", &g_modelrot.y);
						fscanf(pFile, "%f", &g_modelrot.z);
					}
					if (strcmp(&g_aString[0], "TYPE") == 0)
					{// 文字列が一致した場合
						fscanf(pFile, "%s", &g_aEqual[0]);
						fscanf(pFile, "%d", &g_modelType);
					}
				}

				// モデルの設置
				SetModel(g_modelpos, g_modelrot, g_modelType);
			}
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けない場合
		printf("\n * * * ファイルが開けません * * * \n");
	}
}

//---------------------------------------------------------------------------
// ファイル更新処理
//---------------------------------------------------------------------------
void OutputSetFile(void)
{

}