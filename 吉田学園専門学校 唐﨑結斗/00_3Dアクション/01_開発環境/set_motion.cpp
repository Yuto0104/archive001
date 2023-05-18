//**************************************************************************************************
//
// モーション読み込み処理(set_file.cpp)
// Auther：唐﨑結斗
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include<stdio.h>
#include "main.h"
#include "set_motion.h"
#include"file.h"
#include"model.h"
#include"camera.h"

//***************************************************************************
// マクロ定義
//***************************************************************************
#define LOOD_FILE_NAME_000		"model.txt"

//***************************************************************************
// グローバル変数
//***************************************************************************
static char				g_aString[128];
static char				g_aEqual[128] = {};
static PlayerSet		g_PlayerSet;

//---------------------------------------------------------------------------
// モーション読み込み処理
//---------------------------------------------------------------------------
void LoodSetMotion(char *pFileName)
{
	// モーション読み込み情報の初期化
	memset(&g_PlayerSet, 0, sizeof(g_PlayerSet));

	Player *pPlayer = GetPlayer();
	PlayerFile *pPlayerFile = GetPlayerFile();
	MotionSet *pMotionSet = GetMotionSet();

	// ファイルポインタの宣言
	FILE * pFile;

	char aFile[128] = FILE_MOTION_DATA;
	strcat(aFile, pFileName);

	//ファイルを開く
	pFile = fopen(aFile, "r");

	if (pFile != NULL)
	{//ファイルが開いた場合
		fscanf(pFile, "%s", &g_aString);

		while (strncmp(&g_aString[0], "SCRIPT",6) != 0)
		{// 文字列が一致した場合
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
				fscanf(pFile, "%s", &pPlayerFile->aName[0]);
				pPlayerFile++;
			}

			if (strcmp(&g_aString[0], "CHARACTERSET") == 0)
			{// キャラクターの読み込み
				while (strcmp(&g_aString[0], "END_CHARACTERSET") != 0)
				{
					fscanf(pFile, "%s", &g_aString[0]);

					if (strncmp(&g_aString[0], "#", 1) == 0)
					{// 一列読み込む
						fgets(&g_aString[0], sizeof(g_aString), pFile);
					}

					if (strcmp(&g_aString[0], "NUM_PARTS") == 0)
					{// 読み込むパーツ数
						fscanf(pFile, "%s", &g_aEqual[0]);
						fscanf(pFile, "%d", &pPlayer->nMaxModelParts);//こいつ引数にしなあきらめな
					}

					if (strcmp(&g_aString[0], "PARTSSET") == 0)
					{// パーツの読み込み
						while (strcmp(&g_aString[0], "END_PARTSSET") != 0)
						{
							fscanf(pFile, "%s", &g_aString[0]);

							if (strncmp(&g_aString[0], "#", 1) == 0)
							{// 一列読み込む
								fgets(&g_aString[0], sizeof(g_aString), pFile);
							}

							if (strcmp(&g_aString[0], "INDEX") == 0)
							{// タイプの読み込み
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &pPlayer->modeParts[g_PlayerSet.nCntModelParts].nType);
							}
							if (strcmp(&g_aString[0], "PARENT") == 0)
							{// 親の読み込み
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &pPlayer->modeParts[g_PlayerSet.nCntModelParts].nIdxModelParent);
							}
							if (strcmp(&g_aString[0], "POS") == 0)
							{// 位置の読み込み
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &pPlayer->modeParts[g_PlayerSet.nCntModelParts].pos.x);
								fscanf(pFile, "%f", &pPlayer->modeParts[g_PlayerSet.nCntModelParts].pos.y);
								fscanf(pFile, "%f", &pPlayer->modeParts[g_PlayerSet.nCntModelParts].pos.z);
							}
							if (strcmp(&g_aString[0], "ROT") == 0)
							{// 向きの読み込み
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &pPlayer->modeParts[g_PlayerSet.nCntModelParts].rot.x);
								fscanf(pFile, "%f", &pPlayer->modeParts[g_PlayerSet.nCntModelParts].rot.y);
								fscanf(pFile, "%f", &pPlayer->modeParts[g_PlayerSet.nCntModelParts].rot.z);
							}
						}

						// パーツカウントのインクリメント
						g_PlayerSet.nCntModelParts++;
					}
				}

				// プレイヤーの設置
				SetPlayer(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					g_PlayerSet.nCntModelType,
					1);
			}
			if (strcmp(&g_aString[0], "MOTIONSET") == 0)
			{// モーションの読み込み
				while (strcmp(&g_aString[0], "END_MOTIONSET") != 0)
				{
					fscanf(pFile, "%s", &g_aString[0]);

					if (strncmp(&g_aString[0], "#", 1) == 0)
					{// 一列読み込む
						fgets(&g_aString[0], sizeof(g_aString), pFile);
					}

					if (strcmp(&g_aString[0], "LOOP") == 0)
					{// ループ有無の読み込み
						fscanf(pFile, "%s", &g_aEqual[0]);
						fscanf(pFile, "%d", (int*)(&pMotionSet->bLoop));
					}
					if (strcmp(&g_aString[0], "NUM_KEY") == 0)
					{// キー数の読み込み
						fscanf(pFile, "%s", &g_aEqual[0]);
						fscanf(pFile, "%d", &pMotionSet->nNumKey);
					}
					if (strcmp(&g_aString[0], "KEYSET") == 0)
					{// キーセットの読み込み
						while (strcmp(&g_aString[0], "END_KEYSET") != 0)
						{
							fscanf(pFile, "%s", &g_aString[0]);

							if (strncmp(&g_aString[0], "#", 1) == 0)
							{// 一列読み込む
								fgets(&g_aString[0], sizeof(g_aString), pFile);
							}

							if (strcmp(&g_aString[0], "FRAME") == 0)
							{// フレーム数の読み込み
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &pMotionSet->keySet[g_PlayerSet.nCntKeySet].nFrame);
							}
							if (strcmp(&g_aString[0], "KEY") == 0)
							{// キーの読み込み
								while (strcmp(&g_aString[0], "END_KEY") != 0)
								{
									fscanf(pFile, "%s", &g_aString[0]);

									if (strncmp(&g_aString[0], "#", 1) == 0)
									{// 一列読み込む
										fgets(&g_aString[0], sizeof(g_aString), pFile);
									}

									if (strcmp(&g_aString[0], "POS") == 0)
									{// 位置の読み込み
										fscanf(pFile, "%s", &g_aEqual[0]);
										fscanf(pFile, "%f", &pMotionSet->keySet[g_PlayerSet.nCntKeySet].key[g_PlayerSet.nCntKey].pos.x);
										fscanf(pFile, "%f", &pMotionSet->keySet[g_PlayerSet.nCntKeySet].key[g_PlayerSet.nCntKey].pos.y);
										fscanf(pFile, "%f", &pMotionSet->keySet[g_PlayerSet.nCntKeySet].key[g_PlayerSet.nCntKey].pos.z);
									}
									if (strcmp(&g_aString[0], "ROT") == 0)
									{// 向きの読み込み
										fscanf(pFile, "%s", &g_aEqual[0]);
										fscanf(pFile, "%f", &pMotionSet->keySet[g_PlayerSet.nCntKeySet].key[g_PlayerSet.nCntKey].rot.x);
										fscanf(pFile, "%f", &pMotionSet->keySet[g_PlayerSet.nCntKeySet].key[g_PlayerSet.nCntKey].rot.y);
										fscanf(pFile, "%f", &pMotionSet->keySet[g_PlayerSet.nCntKeySet].key[g_PlayerSet.nCntKey].rot.z);
									}
								}

								// キーカウントのインクリメント
								g_PlayerSet.nCntKey++;
							}
						}

						// キーカウントの初期化
						g_PlayerSet.nCntKey = 0;

						// キーセットカウントのインクリメント
						g_PlayerSet.nCntKeySet++;
					}
				}
				// キーセットカウントの初期化
				g_PlayerSet.nCntKeySet = 0;

				// パーツ情報のインクリメント
				pMotionSet++;
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
// モーション更新処理
//---------------------------------------------------------------------------
void OutputSetMotion(void)
{

}