//=============================================================================
//
// モデルオブジェクトクラス(model_obj.cpp)
// Author : 唐�ｱ結斗
// 概要 : モデルオブジェクト生成を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>
#include <stdio.h>

#include "model_obj.h"
#include "model3D.h"
#include "renderer.h"
#include "application.h"
#include "line.h"

//=============================================================================
// インスタンス生成
// Author : 唐�ｱ結斗
// 概要 : モーションキャラクター3Dを生成する
//=============================================================================
CModelObj * CModelObj::Create()
{
	// オブジェクトインスタンス
	CModelObj *pModelObj = nullptr;

	// メモリの解放
	pModelObj = new CModelObj;

	// メモリの確保ができなかった
	assert(pModelObj != nullptr);

	// 数値の初期化
	pModelObj->Init();

	// インスタンスを返す
	return pModelObj;
}

//=============================================================================
// ファイルを読み込み処理
// Author : 唐�ｱ結斗
// 概要 : ファイルを読み込みモデルを生成する
//=============================================================================
void CModelObj::LoadFile(const char *pFileName)
{
	// 変数宣言
	char aStr[128];
	int nCntSetModel = 0;

	// ファイルの読み込み
	FILE *pFile = fopen(pFileName, "r");

	if (pFile != nullptr)
	{
		while (fscanf(pFile, "%s", &aStr[0]) != EOF)
		{// "EOF"を読み込むまで 
			if (strncmp(&aStr[0], "#", 1) == 0)
			{// 一列読み込む
				fgets(&aStr[0], sizeof(aStr), pFile);
			}

			if (strstr(&aStr[0], "MODELSET") != NULL)
			{
				// モデルの設置
				CModelObj *pModelObj = Create();
				assert(pModelObj != nullptr);

				while (strstr(&aStr[0], "END_MODELSET") == NULL)
				{
					fscanf(pFile, "%s", &aStr[0]);

					if (strncmp(&aStr[0], "#", 1) == 0)
					{// 一列読み込む
						fgets(&aStr[0], sizeof(aStr), pFile);
					}

					if (strstr(&aStr[0], "COLISON_POS") != NULL)
					{// モデルのファイル名の設定
						D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%f", &pos.x);
						fscanf(pFile, "%f", &pos.y);
						fscanf(pFile, "%f", &pos.z);
						pModelObj->SetColisonPos(pos);
					}
					else if (strstr(&aStr[0], "POS") != NULL)
					{// モデルのファイル名の設定
						D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%f", &pos.x);
						fscanf(pFile, "%f", &pos.y);
						fscanf(pFile, "%f", &pos.z);
						pModelObj->SetPos(pos);
					}

					if (strstr(&aStr[0], "ROT") != NULL)
					{// モデルのファイル名の設定
						D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%f", &rot.x);
						fscanf(pFile, "%f", &rot.y);
						fscanf(pFile, "%f", &rot.z);
						pModelObj->SetRot(rot);
					}

					if (strcmp(&aStr[0], "COLISON") == 0)
					{// キー数の読み込み
						int nColison = 0;
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%d", &nColison);

						if (nColison != 0)
						{// 大きさの初期値を入力する
							CModel3D::MODEL_MATERIAL *material = pModelObj->GetModel()->GetMaterial();
							D3DXVECTOR3 size = material[pModelObj->GetModel()->GetModelID()].size;
							pModelObj->SetColisonSize(size);
						}
					}

					if (strstr(&aStr[0], "COLISONSIZE") != NULL)
					{// モデルのファイル名の設定
						D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%f", &size.x);
						fscanf(pFile, "%f", &size.y);
						fscanf(pFile, "%f", &size.z);
						pModelObj->SetColisonSize(size);
					}

					if (strcmp(&aStr[0], "TYPE") == 0)
					{// キー数の読み込み
						int nID = 0;
						fscanf(pFile, "%s", &aStr[0]);
						fscanf(pFile, "%d", &nID);
						pModelObj->SetType(nID);
					}
				}

#ifdef _DEBUG
				// ラインの設定
				pModelObj->SetLine();
#endif // _DEBUG

				nCntSetModel++;
			}
		}
	}
	else
	{
		assert(false);
	}
}

//=============================================================================
// コンストラクタ
// Author : 唐�ｱ結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CModelObj::CModelObj() : m_pModel(nullptr),					// モデル情報
m_mtxWorld(D3DXMATRIX()),									// ワールドマトリックス
m_pos(D3DXVECTOR3()),										// 位置
m_posOld(D3DXVECTOR3()),									// 過去位置
m_rot(D3DXVECTOR3()),										// 向き
m_size(D3DXVECTOR3()),										// 大きさ
m_nType(-1)													// モデルのタイプ
{
#ifdef _DEBUG
	// ライン情報
	m_pLine = nullptr;
#endif // _DEBUG
}

//=============================================================================
// デストラクタ
// Author : 唐�ｱ結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CModelObj::~CModelObj()
{

}

//=============================================================================
// 初期化
// Author : 唐�ｱ結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CModelObj::Init()
{
	// 変数の初期化
	m_mtxWorld = {};										// ワールドマトリックス
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 位置
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 過去位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 向き
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);					// 大きさ
	m_nType = -1;											// モデルのタイプ

	// オブジェクトタイプの入力
	SetObjType(OBJTYPE_3DMODEL);

	// モデルクラスのメモリ確保
	m_pModel = CModel3D::Create();
	assert(m_pModel != nullptr);
	m_pModel->SetModelID(m_nType);

#ifdef _DEBUG
	// ライン情報
	m_pLine = new CLine*[12];

	for (int nCntLine = 0; nCntLine < 12; nCntLine++)
	{
		m_pLine[nCntLine] = CLine::Create();
	}

	// ラインの設定
	SetLine();
#endif // _DEBUG

	return E_NOTIMPL;
}

//=============================================================================
// 終了
// Author : 唐�ｱ結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CModelObj::Uninit()
{
	if (m_pModel != nullptr)
	{// 終了処理
		m_pModel->Uninit();

		// メモリの解放
		delete m_pModel;
		m_pModel = nullptr;
	}

#ifdef _DEBUG
	for (int nCntLine = 0; nCntLine < 12; nCntLine++)
	{
		m_pLine[nCntLine]->Uninit();
	}

	delete m_pLine;
#endif // _DEBUG

	// オブジェクトの解放
	Release();
}

//=============================================================================
// 更新
// Author : 唐�ｱ結斗
// 概要 : 更新を行う
//=============================================================================
void CModelObj::Update()
{
	// モデルの更新
	m_pModel->Update();

#ifdef _DEBUG
	// ラインの設定
	SetLine();
#endif // _DEBUG
}

//=============================================================================
// 描画
// Author : 唐�ｱ結斗
// 概要 : 描画を行う
//=============================================================================
void CModelObj::Draw()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);											// 行列初期化関数

	// 向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);			// 行列回転関数
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);						// 行列掛け算関数 

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);				// 行列移動関数
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);					// 行列掛け算関数

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// モデルの描画
	m_pModel->Draw(m_mtxWorld);
}

//=============================================================================
// モデルのタイプの設定
// Author : 唐�ｱ結斗
// 概要 : モデルのタイプの設定
//=============================================================================
void CModelObj::SetType(const int nType)
{
	// モデルのタイプ
	m_nType = nType;

	// モデルクラスのID設定
	m_pModel->SetModelID(m_nType);
}

#ifdef _DEBUG
//=============================================================================
// ラインの設置
// Author : 唐�ｱ結斗
// 概要 : ラインを矩形状に設置
//=============================================================================
void CModelObj::SetLine()
{
	// 変数宣言
	const D3DXVECTOR3 pos = GetPos() + GetColisonPos();
	const D3DXVECTOR3 rot = GetRot();
	const D3DXVECTOR3 size = GetColisonSize() / 2.0f;
	const D3DXCOLOR col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	// ラインの設定
	m_pLine[0]->SetLine(pos, rot, D3DXVECTOR3(-size.x, -size.y, size.z), D3DXVECTOR3(size.x, -size.y, size.z), col);
	m_pLine[1]->SetLine(pos, rot, D3DXVECTOR3(-size.x, -size.y, -size.z), D3DXVECTOR3(-size.x, -size.y, size.z), col);
	m_pLine[2]->SetLine(pos, rot, D3DXVECTOR3(-size.x, -size.y, -size.z), D3DXVECTOR3(size.x, -size.y, -size.z), col);
	m_pLine[3]->SetLine(pos, rot, D3DXVECTOR3(size.x, -size.y, -size.z), D3DXVECTOR3(size.x, -size.y, size.z), col);
	m_pLine[4]->SetLine(pos, rot, D3DXVECTOR3(-size.x, size.y, size.z), D3DXVECTOR3(size.x, size.y, size.z), col);
	m_pLine[5]->SetLine(pos, rot, D3DXVECTOR3(-size.x, size.y, -size.z), D3DXVECTOR3(-size.x, size.y, size.z), col);
	m_pLine[6]->SetLine(pos, rot, D3DXVECTOR3(-size.x, size.y, -size.z), D3DXVECTOR3(size.x, size.y, -size.z), col);
	m_pLine[7]->SetLine(pos, rot, D3DXVECTOR3(size.x, size.y, -size.z), D3DXVECTOR3(size.x, size.y, size.z), col);
	m_pLine[8]->SetLine(pos, rot, D3DXVECTOR3(-size.x, -size.y, size.z), D3DXVECTOR3(-size.x, size.y, size.z), col);
	m_pLine[9]->SetLine(pos, rot, D3DXVECTOR3(-size.x, -size.y, -size.z), D3DXVECTOR3(-size.x, size.y, -size.z), col);
	m_pLine[10]->SetLine(pos, rot, D3DXVECTOR3(size.x, -size.y, -size.z), D3DXVECTOR3(size.x, size.y, -size.z), col);
	m_pLine[11]->SetLine(pos, rot, D3DXVECTOR3(size.x, -size.y, size.z), D3DXVECTOR3(size.x, size.y, size.z), col);
}
#endif // DEBUG

