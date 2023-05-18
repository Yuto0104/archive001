//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
// ライブラリーリンク
//*****************************************************************************
#pragma comment(lib,"dxguid.lib")		// DirectXのコンポネート(部品)の使用に必要

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "xaudio2.h"			// サウンド処理に必要

//=============================================================================
// テクスチャクラス
// Author : 唐�ｱ結斗
// 概要 : テクスチャ設定を行うクラス
//=============================================================================
class CSound
{
public:
	//*****************************************************************************
	// パラメータ構造体定義
	// Author : 唐�ｱ結斗
	// 概要 : ファイル名とループの使用状況を格納
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDPARAM;

	//*****************************************************************************
	// サウンドファイルの列挙型
	// Author : 唐�ｱ結斗
	// 概要 : サウンドファイルの種別
	//*****************************************************************************
	enum SOUND_LABEL
	{
		SOUND_LABEL_BGM000 = 0,		// BGM0
		SOUND_LABEL_BGM001,			// BGM1
		SOUND_LABEL_BGM002,			// BGM2
		SOUND_LABEL_BGM003,			// BGM3
		SOUND_LABEL_SE_DECIDE,		// 次へ音
		SOUND_LABEL_SE_SELECT,		// 選択音
		SOUND_LABEL_SE_PAUSE,		// ポーズ音
		SOUND_LABEL_SE_SHOT,		// 発射音
		SOUND_LABEL_SE_HIT,			// ヒット音
		SOUND_LABEL_SE_EXPLOSION,	// 爆発音
		SOUND_LABEL_SE_TRANCEFARM,	// 変身音
		SOUND_LABEL_SE_HEEL,		// 回復音
		SOUND_LABEL_MAX,
	};

	//--------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------------
	CSound();
	~CSound();

	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------
	HRESULT Init(HWND hWnd);																			// 初期化
	void Uninit(void);																					// 終了
	HRESULT PlaySound(SOUND_LABEL label);																// セグメント再生(再生中なら停止)
	void StopSound(SOUND_LABEL label);																	// セグメント停止(ラベル指定)
	void StopSound(void);																				// セグメント停止(全て)
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);		// チャンクのチェック
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);		// チャンクデータの読み込み

private:
	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------
	SOUNDPARAM SetSoundParam(char *pFileName, int nCntLoop);			// サウンドパラメータの登録

	//--------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------
	IXAudio2					*m_pXAudio2;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice		*m_pMasteringVoice;							// マスターボイス
	IXAudio2SourceVoice			*m_apSourceVoice[SOUND_LABEL_MAX];			// ソースボイス
	BYTE						*m_apDataAudio[SOUND_LABEL_MAX];			// オーディオデータ
	DWORD						m_aSizeAudio[SOUND_LABEL_MAX];				// オーディオデータサイズ
	SOUNDPARAM					m_aParam[SOUND_LABEL_MAX];					// 各音素材のパラメータ
};

#endif
