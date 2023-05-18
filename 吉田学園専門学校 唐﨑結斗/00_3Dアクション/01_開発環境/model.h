//**************************************************************************************************
//
// モデル処理(model.h)
// Auther：唐﨑結斗
//
//**************************************************************************************************
#ifndef _MODEL_H_			// このマクロ定義がされてなかったら
#define _MODEL_H_			// 二重インクルード防止のマクロ定義

//***************************************************************************
// インクルード
//***************************************************************************
#include"main.h"

//***************************************************************************
// マクロ定義
//***************************************************************************
#define	MAX_MODEL			(128)		// モデル数の最大数
#define	MAX_MODEL_NAME		(128)		// モデル数の最大数

//***************************************************************
// モデルファイル構造体を定義
//***************************************************************
typedef struct
{
	char	aName[MAX_MODEL_NAME];		// 名前
}ModelFile;

//***************************************************************
// モデル構造体を定義
//***************************************************************
typedef struct
{
	LPD3DXMESH		pMesh;			// メッシュ情報へのポインタ
	LPD3DXBUFFER	pBuffer;		// マテリアル情報へのポインタ
	DWORD			nNumMat;		// マテリアル情報の数
	D3DXMATRIX		mtxWorld;		// ワールドマトリックス
	D3DXVECTOR3		pos;			// 位置
	D3DXVECTOR3		rot;			// 現在の向き
	D3DXVECTOR3		rotDest;		// 目的の向き
	D3DXVECTOR3		vtxMin;			// 頂点座標の最小値
	D3DXVECTOR3		vtxMax;			// 頂点座標の最大値
	int				nType;			// タイプ
	int				nIdx;			// インデックス
	bool			bUse;			// 使用状況
}Model;

//***************************************************************
// プロトタイプ宣言
//***************************************************************
// 制御関数
void	InitModel		(void);
void	UninitModel		(void);
void	UpdateModel		(void);
void	DrawModel		(void);

// 入力関数
void	MoveModel		(int nCnt);
void	RotateModel		(int nCnt);
bool	CollisionModel(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *vtx, D3DXVECTOR3 *vtxOld);
void	SetModel		(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);

// 出力関数
Model		*GetModel		(void);
ModelFile	*GetModelFile	(void);

#endif
