//**************************************************************************************************
//
// エフェクト描画処理(effect.h)
// Auther：唐﨑結斗
//
//**************************************************************************************************
#ifndef _EFFECT_H_			// このマクロ定義がされてなかったら
#define _EFFECT_H_			// 二重インクルード防止のマクロ定義

//***************************************************************************
// インクルード
//***************************************************************************
#include "main.h"

//**********************************************************
// エフェクトのテクスチャの列挙型
//**********************************************************
typedef enum
{
	EFFECTTEXTURE_000 = 0,		// テクスチャ000
	EFFECTTEXTURE_001,			// テクスチャ001
	EFFECTTEXTURE_002,			// テクスチャ002
	EFFECTTEXTURE_003,			// テクスチャ003
	EFFECTTEXTURE_004,			// テクスチャ004
	EFFECTTEXTURE_005,			// テクスチャ005
	MAX_EFFECTTEXTURE			// エフェクトテクスチャの最大数
}EFFECTTEXTURE;

//**********************************************************
// エフェクトの状態の列挙型
//**********************************************************
typedef enum
{
	EFFECTTYPE_NORMAL = 0,		// 通常エフェクト
	EFFECTTYPE_FIELD,			// 地面エフェクト
	EFFECTTYPE_WALL,			// 壁エフェクト
	MAX_EFFECTTYPE				// エフェクトタイプの最大数
}EFFECTTYPE;

//**********************************************************
// エフェクトのαブレンディングの列挙型
//**********************************************************
typedef enum
{
	EFFECTALPHABLEND_ADDITIVE = 0,		// 加算合成
	EFFECTALPHABLEND_SUBTRACTIVE,		// 減算合成
	MAX_EFFECTALPHABLEND				// αブレンディングの最大数
}EFFECTALPHABLEND;

//***************************************************************
// エフェクト構造体を定義
//***************************************************************
typedef struct
{
	D3DXVECTOR3			pos;					// 位置
	D3DXVECTOR3			move;					// 移動量
	D3DXVECTOR3			rot;					// 向き
	D3DXMATRIX			mtxWorld;				// ワールドマトリックス
	D3DXCOLOR			col;					// カラー
	D3DCMPFUNC			zFuncType;				// Zバッファの比較タイプ
	EFFECTTYPE			EffectType;				// エフェクトタイプ
	EFFECTTEXTURE		EffectTexture;			// エフェクトテクスチャ
	EFFECTALPHABLEND	EffectAlphaBlend;		// エフェクトのαブレンドモード
	float				fRadius;				// 半径
	float				fAttenuationRadius;		// 半径の減衰量
	float				fAttenuationAlpha;		// α値の減衰量
	float				fSpeed;					// 移動速度
	float				fGravity;				// 重力
	int					nIdx;					// インデックス
	int					nLife;					// 寿命
	bool				bShadow;				// 影を使用状況
	bool				bUse;					// 使用状況
}Effect;

//***************************************************************
// プロトタイプ宣言
//***************************************************************
// 制御関数
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

// 副制御関数
void SetEffect(D3DXVECTOR3 pos, 
	D3DXVECTOR3 rot, 
	D3DXCOLOR col, 
	D3DCMPFUNC zFuncType,
	EFFECTTYPE EffectType,
	EFFECTALPHABLEND EffectAlphaBlend,
	float fRadius,
	float fSpeed,
	float fGravity,
	int nLife,
	int nTexture,
	bool bShadow);

#endif
