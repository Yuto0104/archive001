//**************************************************************************************************
//
// カメラ処理(camera.h)
// Auther：唐﨑結斗
//
//**************************************************************************************************
#ifndef _CAMERA_H_			// このマクロ定義がされてなかったら
#define _CAMERA_H_			// 二重インクルード防止のマクロ定義

//***************************************************************************
// インクルード
//***************************************************************************
#include"main.h"

//***************************************************************
// カメラ構造体を定義
//***************************************************************
typedef struct
{
	D3DXVECTOR3			posV;				// 視点
	D3DXVECTOR3			posR;				// 注視点
	D3DXVECTOR3			vecU;				// 上方向ベクトル
	D3DXVECTOR3			posVDest;			// 視点の目的の位置
	D3DXVECTOR3			posRDest;			// 注視点の目的の位置
	D3DXVECTOR3			rot;				// 向き
	D3DXVECTOR3			rotMove;			// 移動方向
	D3DXVECTOR3			rotDest;			// 目的の向き
	D3DXVECTOR3			roll;				// 回転量
	D3DXMATRIX			mtxProjection;		// プロジェクションマトリックス
	D3DXMATRIX			mtxView;			// ビューマトリックス	
	float				fDistance;			// 視点から注視点までの距離
	float				fZoomSpeed;			// ズーム速度
}Camera;

//***************************************************************
// プロトタイプ宣言
//***************************************************************
// 制御関数
void InitCamera(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU, D3DXVECTOR3 rot);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);

// 副関数
Camera *GetCamera(void);
void RotateCamera(void);
void MoveCamera(void);
void FollowCamera(void);
void AutoRotateCamera(void);
void TitleRotateCamera(void);

#endif
