//**************************************************************************************************
//
// 餌処理(feed.h)
// Auther：唐﨑結斗
//
//**************************************************************************************************
#ifndef _FEED_H_			// このマクロ定義がされてなかったら
#define _FEED_H_			// 二重インクルード防止のマクロ定義

//***************************************************************************
// インクルード
//***************************************************************************
#include"main.h"

//***************************************************************************
// マクロ定義
//***************************************************************************
#define	MAX_FEED			(1280)		// 餌数の最大数
#define	MAX_FEED_NAME		(128)		// 餌数の最大数

//***************************************************************
// 餌ファイル構造体を定義
//***************************************************************
typedef struct
{
	char	aName[MAX_FEED_NAME];		// 名前
}FeedFile;

//***************************************************************
// 餌構造体を定義
//***************************************************************
typedef struct
{
	LPD3DXMESH		pMesh;			// メッシュ情報へのポインタ
	LPD3DXBUFFER	pBuffer;		// マテリアル情報へのポインタ
	DWORD			nNumMat;		// マテリアル情報の数
	D3DXMATRIX		mtxWorld;		// ワールドマトリックス
	D3DXVECTOR3		pos;			// 位置
	D3DXVECTOR3		posOld;			// 過去位置
	D3DXVECTOR3		rot;			// 現在の向き
	D3DXVECTOR3		rotDest;		// 目的の向き
	D3DXVECTOR3		move;			// 移動量
	D3DXVECTOR3		joinVec;		// 結合ベクトル
	D3DXVECTOR3		leaveVec;		// 離れるベクトル
	D3DXVECTOR3		averageVec;		// 平均ベクトル
	D3DXVECTOR3		vtxMin;			// 頂点座標の最小値
	D3DXVECTOR3		vtxMax;			// 頂点座標の最大値
	int				nIdx;			// インデックス
	int				nGroup;			// グループ番号
	int				nIdxLeader;		// リーダーの番号(リーダがいない場合-1)
	int				nCntJoinTime;	// リーダー捜索までの時間
	int				nCntMoveTime;	// 移動量算出までの時間
	float			fJoinRot;		// 結合方向
	float			fLeaveRot;		// 結合方向
	float			fSpeed;			// 移動速度
	bool			bUse;			// 使用状況
	bool			bSearchIn;		// 視野角内にいるかどうか
	bool			bEscape;		// 逃げているかどうか
}Feed;

//***************************************************************
// プロトタイプ宣言
//***************************************************************
// 制御関数
void InitFeed(void);
void UninitFeed(void);
void UpdateFeed(void);
void DrawFeed(void);

// 入力関数
void MoveFeed(int nCnt);
void RotateFeed(int nCnt);
void CollisionFeed(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *vtx, D3DXVECTOR3 *vtxOld);
void SearchLeader(int nCnt);
void LeaveFeed(int nCnt);
void AverageFeed(int nCnt);
void SetFeed(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void RandSetFeed(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSetRot, float fSetLength, int nNumSet);
void LeavePlayer(int nCnt);
void SetControllerFeed(void);

// 出力関数
Feed *GetFeed(void);
FeedFile *GetFeedFile(void);
int GetCntFeed(void);

#endif

