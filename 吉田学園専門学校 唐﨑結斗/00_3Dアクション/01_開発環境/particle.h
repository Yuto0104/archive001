//**************************************************************************************************
//
// パーティクル描画処理(particle.h)
// Auther：唐﨑結斗
//
//**************************************************************************************************
#ifndef _PARTICLE_H_			// このマクロ定義がされてなかったら
#define _PARTICLE_H_			// 二重インクルード防止のマクロ定義

//***************************************************************************
// インクルード
//***************************************************************************
#include "main.h"

//**********************************************************
// パーティクルのタイプの列挙型
//**********************************************************
typedef enum
{
	PARTICLETYPE_NORMAL = 0,		// 通常パーティクル
	MAX_PARTICLETYPE				// エフェクトタイプの最大数
}PARTICLETYPE;

//***************************************************************
// パーティクル構造体を定義
//***************************************************************
typedef struct
{
	D3DXVECTOR3		pos;					// 位置
	D3DXVECTOR3		posPop;					// 発生位置
	D3DXVECTOR3		rot;					// 向き
	D3DXCOLOR		col;					// カラー
	float			fRadius;				// 半径
	float			fSpeed;					// 移動速度
	float			fGravity;				// 重力
	int				nLife;					// 寿命
	int				nTexture;				// テクスチャ
	int				nAlphaBlend;			// αブレンド
	int				nTime;					// 発生時間
	int				nNumParticle;			// 発生数
	bool			bShadow;				// 影を使用状況
	bool			bUse;					// 使用状況
}Particle;

//***************************************************************
// プロトタイプ宣言
//***************************************************************
// 制御関数
void InitParticle(void);
void UpdateParticle(void);
void SetParticle(D3DXVECTOR3 pos, 
	D3DXVECTOR3	posPop,
	D3DXVECTOR3 rot, 
	D3DXCOLOR col,
	float fRadius,
	float fSpeed,
	float fGravity,
	int	nLife,
	int	nTexture,
	int nAlphaBlend,
	int	nTime,
	int nNumParticle,
	bool bShadow);

#endif
