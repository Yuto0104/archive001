//**************************************************************************************************
//
// プレイヤー処理(Player.h)
// Auther：唐﨑結斗
//
//**************************************************************************************************
#ifndef _Player_H_			// このマクロ定義がされてなかったら
#define _Player_H_			// 二重インクルード防止のマクロ定義

//***************************************************************************
// インクルード
//***************************************************************************
#include"main.h"

//***************************************************************************
// マクロ定義
//***************************************************************************
#define	MAX_MODEL_PARTS				(128)				// モデル数の最大数
#define MAX_KEY						(64)				// キーの最大数
#define MAX_KEYSET					(64)				// キー設定の最大数
#define DASH_STAMINA				(20)				// ダッシュの消費スタミナ

//**********************************************************
// モーションモードの列挙型
//**********************************************************
typedef enum
{
	NEUTRAL_MOTION = 0,			// ニュートラルモーション
	MOVE_MOTION,				// 移動モーション
	MAX_MOTION_STATE			// モーションステイトの最大数
}MotionState;

//**********************************************************
// プレイヤー状態の列挙型
//**********************************************************
typedef enum
{
	NORMAL_STATE = 0,			// 通常状態
	DASH_STATE,					// ダッシュ状態
	MAX_PLAYER_STATE			// モーションステイトの最大数
}PlayerState;

//***************************************************************
// プレイヤーファイル構造体を定義
//***************************************************************
typedef struct
{
	char	aName[MAX_MODEL_PARTS];		// 名前
}PlayerFile;

//***************************************************************
// キー構造体を定義
//***************************************************************
typedef struct
{
	D3DXVECTOR3		pos;	// 現在位置
	D3DXVECTOR3		rot;	// 現在の向き
}Key;

//***************************************************************
// キー設定構造体を定義
//***************************************************************
typedef struct
{
	int		nFrame;				// フレーム数
	Key		key[MAX_KEY];		// キー情報
}KeySet;

//***************************************************************
// モーション設定構造体を定義
//***************************************************************
typedef struct
{
	int			nNumKey;				// キー数
	int			nCntKeySet;				// キーセットカウント
	int			nCntFrame;				// フレームカウント
	bool		bLoop;					// ループ使用状況
	KeySet		keySet[MAX_KEYSET];		// キー設定情報
}MotionSet;

//***************************************************************
// モデルパーツ構造体を定義
//***************************************************************
typedef struct
{
	LPD3DXMESH		pMesh;					// メッシュ情報へのポインタ
	LPD3DXBUFFER	pBuffer;				// マテリアル情報へのポインタ
	DWORD			nNumMat;				// マテリアル情報の数
	D3DXMATRIX		mtxWorld;				// ワールドマトリックス
	D3DXVECTOR3		posOrigin;				// 元の位置
	D3DXVECTOR3		rotOrigin;				// 元の向き
	D3DXVECTOR3		pos;					// 現在の位置
	D3DXVECTOR3		rot;					// 現在の向き
	D3DXVECTOR3		posDest;				// 目的の位置
	D3DXVECTOR3		rotDest;				// 目的の向き
	D3DXVECTOR3		vtxMin;					// 頂点座標の最小値
	D3DXVECTOR3		vtxMax;					// 頂点座標の最大値
	int				nIdxModelParent;		// 親モデルのインデックス数
	int				nType;					// パーツのタイプ
}ModelParts;

//***************************************************************
// プレイヤー構造体を定義
//***************************************************************
typedef struct
{
	D3DXVECTOR3		pos;							// 現在位置
	D3DXVECTOR3		posOld;							// 過去位置
	D3DXVECTOR3		rot;							// 現在の向き
	D3DXVECTOR3		rotDest;						// 目的の向き
	D3DXVECTOR3		vtxMin;							// 頂点座標の最小値
	D3DXVECTOR3		vtxMax;							// 頂点座標の最大値
	D3DXVECTOR3		size;							// 大きさ
	D3DXVECTOR3		attackPos;						// 攻撃判定の位置
	D3DXMATRIX		mtxWorld;						// ワールドマトリックス
	ModelParts		modeParts[MAX_MODEL_PARTS];		// モデルパーツ
	MotionState		MotionState;					// モーションステイト
	PlayerState		PlayerState;					// プレイヤーの状態
	int				nMaxModelType;					// モデルのタイプ数
	int				nMaxModelParts;					// 扱うモデルパーツ数
	int				nMaxMotion;						// モーション数
	int				nIdx;							// インデックス
	int				nCntNotMove;					// 動かなった時間
	int				nCntComboTime;					// コンボ加算時間
	int				nCntCombo;						// コンボカウント
	int				nMaxCombo;						// コンボの最大数
	int				nCntState;						// 状態カウント
	int				nStamina;						// スタミナ
	int				nMaxStamina;					// スタミナの最大値
	float			fAttackRadius;					// 攻撃判定の半径
	float			fSpeed;							// 移動速度
	float			fMoveDistance;					// 移動距離
	bool			bUse;							// 使用状況
}Player;

//***************************************************************
// プロトタイプ宣言
//***************************************************************
// 制御関数
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

// 入力関数
void MovePlayer(void);
void RotatePlayer(void);
void SetPlayer(D3DXVECTOR3 pos, 
	D3DXVECTOR3 rot,
	int	nMaxModelType,
	int	nMaxMotion);
void MotionPlayer(int nCntMotionSet);
void MotionBlend(int nCntMotionSet);
bool SearchPlayer(D3DXVECTOR3 *pos);
bool EatPlayer(D3DXVECTOR3 *pos, D3DXVECTOR3 size);
bool CollisionPlayer(D3DXVECTOR3 *vtx);
void DashPlayer(void);

// 出力関数
Player *GetPlayer(void);
PlayerFile *GetPlayerFile(void);
MotionSet *GetMotionSet(void);

#endif

