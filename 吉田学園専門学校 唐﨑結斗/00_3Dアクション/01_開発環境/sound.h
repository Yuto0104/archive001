//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_BGM003,			// BGM3
	SOUND_LABEL_BGM004,			// BGM4
	SOUND_LABEL_BGM005,			// BGM5
	SOUND_LABEL_BGM006,			// BGM6
	SOUND_LABEL_BGM007,			// BGM7
	SOUND_LABEL_SE_DECIDE,		// 次へ音
	SOUND_LABEL_SE_SELECT,		// 選択音
	SOUND_LABEL_SE_PAUSE,		// ポーズ音
	SOUND_LABEL_SE_COIN000,		// コイン音
	SOUND_LABEL_SE_DAMAGE000,	// ダメージ音
	SOUND_LABEL_SE_DEATH,		// 死ぬ音
	SOUND_LABEL_SE_JUMP,		// ジャンプ音
	SOUND_LABEL_SE_BGM_CLER,	// クリア音
	SOUND_LABEL_SE_POWER,		// パワー音
	SOUND_LABEL_SE_DESTROY,		// 破壊音
	SOUND_LABEL_SE_COUNT,		// カウンター音
	SOUND_LABEL_SE_DAMAGE001,	// ダメージ音1
	SOUND_LABEL_SE_APPEAR,		// キノコ音
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
