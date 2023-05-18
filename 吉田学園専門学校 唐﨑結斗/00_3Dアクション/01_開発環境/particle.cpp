//**************************************************************************************************
//
// パーティクル描画処理(particle.cpp)
// Auther：唐﨑結斗
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include "main.h"
#include "particle.h"
#include "file.h"
#include"effect.h"

//***************************************************************************
// マクロ定義
//***************************************************************************
#define MAX_PARTICLE_VERTEX		(4)				// パーティクルの頂点数
#define MAX_PARTICLE			(128)			// パーティクルの最大数

//***************************************************************************
// グローバル変数
//***************************************************************************
static Particle						g_Particle[MAX_PARTICLE];			// パーティクル情報の取得

//---------------------------------------------------------------------------
// パーティクル初期化処理
//---------------------------------------------------------------------------
void InitParticle(void)
{
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		// パーティクル情報の初期化
		g_Particle[nCntParticle].pos = {};											// 位置
		g_Particle[nCntParticle].posPop = {};										// 発生位置
		g_Particle[nCntParticle].rot = {};											// 向き
		g_Particle[nCntParticle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			// カラー
		g_Particle[nCntParticle].fRadius = 0.0f;									// 半径
		g_Particle[nCntParticle].fSpeed = 0.0f;										// 移動速度
		g_Particle[nCntParticle].fGravity = 0.0f;									// 重力
		g_Particle[nCntParticle].nLife = 0;											// 寿命
		g_Particle[nCntParticle].nTexture = 0;										// テクスチャ
		g_Particle[nCntParticle].nAlphaBlend = 0;									// αブレンド
		g_Particle[nCntParticle].nTime = 0;											// 発生時間
		g_Particle[nCntParticle].nNumParticle = 0;									// 発生数
		g_Particle[nCntParticle].bShadow = false;									// 影の使用状況
		g_Particle[nCntParticle].bUse = false;										// 使用状況
	}
}

//---------------------------------------------------------------------------
// パーティクル更新処理
//---------------------------------------------------------------------------
void UpdateParticle(void)
{
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_Particle[nCntParticle].bUse == true)
		{// 使用されていない
			for (int nCntNum = 0; nCntNum < g_Particle[nCntParticle].nNumParticle; nCntNum++)
			{
				// パーティクル情報の計算
				Particle particle;

				// 位置の算出
				particle.pos.x = g_Particle[nCntParticle].pos.x + (float)(-(int)(g_Particle[nCntParticle].posPop.x / 2.0f) + rand() % ((int)(g_Particle[nCntParticle].posPop.x) + 1));
				particle.pos.y = g_Particle[nCntParticle].pos.y + (float)(-(int)(g_Particle[nCntParticle].posPop.y / 2.0f) + rand() % ((int)(g_Particle[nCntParticle].posPop.y) + 1));
				particle.pos.z = g_Particle[nCntParticle].pos.z + (float)(-(int)(g_Particle[nCntParticle].posPop.z / 2.0f) + rand() % ((int)(g_Particle[nCntParticle].posPop.z) + 1));

				// 半径の算出
				particle.fRadius = (float)(rand() % ((int)(g_Particle[nCntParticle].fRadius * 100.0f) + 1)) / 100.0f;

				// 寿命の算出
				particle.nLife = rand() % (g_Particle[nCntParticle].nLife + 1) + 1;

				// 移動速度の算出
				particle.fSpeed = (float)(rand() % ((int)(g_Particle[nCntParticle].fSpeed * 100.0f) + 1)) / 100.0f;

				// 移動方向の算出
				particle.rot.x = (((int)((D3DX_PI * 2) * g_Particle[nCntParticle].rot.x * 100.0f) / 2) - (rand() % ((int)((D3DX_PI * 2) * g_Particle[nCntParticle].rot.x * 100.0f) + 1))) / 100.0f;
				particle.rot.y = (((int)((D3DX_PI * 2) * g_Particle[nCntParticle].rot.y * 100.0f) / 2) - (rand() % ((int)((D3DX_PI * 2) * g_Particle[nCntParticle].rot.y * 100.0f) + 1))) / 100.0f;
				particle.rot.z = 0.0f;

				// エフェクトの生成
				SetEffect(particle.pos,
					particle.rot,
					g_Particle[nCntParticle].col,
					D3DCMP_ALWAYS,
					EFFECTTYPE_NORMAL,
					(EFFECTALPHABLEND)(g_Particle[nCntParticle].nAlphaBlend),
					particle.fRadius,
					particle.fSpeed,
					g_Particle[nCntParticle].fGravity,
					particle.nLife,
					g_Particle[nCntParticle].nTexture,
					g_Particle[nCntParticle].bShadow);
			}

			if (g_Particle[nCntParticle].nTime != 0)
			{// 発生時間が0の時
				g_Particle[nCntParticle].nTime--;
			}

			if (g_Particle[nCntParticle].nTime <= 1 && g_Particle[nCntParticle].nTime != 0)
			{// 0以外で1以下の時
				g_Particle[nCntParticle].bUse = false;
			}
		}
	}
}

//---------------------------------------------------------------------------
// パーティクル設定処理
//---------------------------------------------------------------------------
void SetParticle(D3DXVECTOR3 pos,		// 位置
	D3DXVECTOR3	posPop,					// 発生位置
	D3DXVECTOR3 rot,					// 向き(X座標->θ,Y座標->φ,360°->1.0f)
	D3DXCOLOR col,						// カラー
	float fRadius,						// 半径
	float fSpeed,						// 移動速度
	float fGravity,						// 重力
	int	nLife,							// 寿命
	int	nTexture,						// テクスチャタイプ
	int nAlphaBlend,					// αブレンド(0 = 加算合成 | 1 = 減算合成)
	int	nTime,							// 発生時間(0 == ∞)
	int nNumParticle,					// 発生数
	bool bShadow)						// 影の使用状況
{
	// 変数宣言
	int nCntParticle;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_Particle[nCntParticle].bUse == false)
		{// 使用されていない
			// パーティクル情報の初期化
			g_Particle[nCntParticle].pos = pos;							// 位置
			g_Particle[nCntParticle].posPop = posPop;					// 発生位置
			g_Particle[nCntParticle].rot = rot;							// 向き
			g_Particle[nCntParticle].col = col;							// カラー
			g_Particle[nCntParticle].fRadius = fRadius;					// 半径
			g_Particle[nCntParticle].fSpeed = fSpeed;					// 移動速度
			g_Particle[nCntParticle].fGravity = fGravity;				// 重力
			g_Particle[nCntParticle].nLife = nLife;						// 寿命
			g_Particle[nCntParticle].nTexture = nTexture;				// テクスチャ
			g_Particle[nCntParticle].nAlphaBlend = nAlphaBlend;			// αブレンド
			g_Particle[nCntParticle].nTime = nTime;						// 発生時間
			g_Particle[nCntParticle].nNumParticle = nNumParticle + 1;	// 発生数
			g_Particle[nCntParticle].bShadow = bShadow;					// 影の使用状況
			g_Particle[nCntParticle].bUse = true;						// 使用状況

			if (g_Particle[nCntParticle].nTime != 0)
			{// 発生時間が0の時
				g_Particle[nCntParticle].nTime++;
			}

			break;
		}
	}
}