//=============================================================================
//
// リザルトクラス(result.cpp)
// Author : 唐�ｱ結斗
// 概要 : リザルトクラスの管理を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "result.h"
#include "keyboard.h"
#include "sound.h"
#include "object2D.h"
#include "score.h"
#include "bg.h"
#include "ranking.h"

//=============================================================================
// コンストラクタ
// Author : 唐�ｱ結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CResult::CResult()
{
	m_nextMode = CApplication::MODE_NONE;		// 次に設定するモード
	m_pScoreObj = nullptr;						// スコアオブジェクト
	m_pTitleObj = nullptr;						// タイトルオブジェクト
	m_pGameObj = nullptr;						// ゲームオブジェクト
	m_pRankingObj = nullptr;					// ランキングオブジェクト
	m_pScore = nullptr;							// スコアクラス
	m_pRanking = nullptr;						// ランキングクラス
	m_fAddAlpha = 0.0f;							// アルファの加算値
	m_nCntFrame = 0;							// フレームカウント
	m_bPressEnter = true;						// プレスエンターを使用できるか
}

//=============================================================================
// デストラクタ
// Author : 唐�ｱ結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
// 初期化
// Author : 唐�ｱ結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CResult::Init()
{
	// サウンド情報の取得
	CSound *pSound = CApplication::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM002);

	// 次に行くモードの設定
	m_nextMode = CApplication::MODE_TITLE;

	m_pScoreObj = CObject2D::Create();
	m_pScoreObj->SetPos(D3DXVECTOR3(640.0f, 520.0f, 0.0f));
	m_pScoreObj->SetSize(D3DXVECTOR3(600.0f, 120.0f, 0.0f));
	m_pScoreObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.1f, 1.0f));
	m_pScoreObj->LoadTex(17);

	m_pTitleObj = CObject2D::Create();
	m_pTitleObj->SetPos(D3DXVECTOR3(340.0f, 650.0f, 0.0f));
	m_pTitleObj->SetSize(D3DXVECTOR3(300.0f, 100.0f, 0.0f));
	m_pTitleObj->SetCol(D3DXCOLOR(0.3f, 0.1f, 1.0f, 1.0f));
	m_pTitleObj->LoadTex(18);

	m_pGameObj = CObject2D::Create();
	m_pGameObj->SetPos(D3DXVECTOR3(940.0f, 650.0f, 0.0f));
	m_pGameObj->SetSize(D3DXVECTOR3(320.0f, 100.0f, 0.0f));
	m_pGameObj->SetCol(D3DXCOLOR(0.3f, 0.1f, 1.0f, 1.0f));
	m_pGameObj->LoadTex(19);

	m_pRankingObj = CObject2D::Create();
	m_pRankingObj->SetPos(D3DXVECTOR3(640.0f, 80.0f, 0.0f));
	m_pRankingObj->SetSize(D3DXVECTOR3(320.0f, 100.0f, 0.0f));
	m_pRankingObj->SetCol(D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f));
	m_pRankingObj->LoadTex(21);

	m_pScore = CScore::Create(10, false);
	m_pScore->SetDestScore(CApplication::GetScore());
	m_pScore->SetScore(CApplication::GetScore());
	m_pScore->SetPos(D3DXVECTOR3(900.0f, 530.0, 0.0f));
	m_pScore->SetSize(D3DXVECTOR3(80.0f, 80.0, 0.0f));
	m_pScore->SetWholeSize(D3DXVECTOR3(480.0f, 70.0, 0.0f));

	m_pRanking = CRanking::Create(5, CApplication::GetScore());
	m_pRanking->SetPos(D3DXVECTOR3(660.0f, 280.0f, 0.0f));
	m_pRanking->SetWholeSize(D3DXVECTOR3(500.0f, 300.0f, 0.0f));

	CBG *pBG = CBG::Create();
	pBG->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	return S_OK;
}

//=============================================================================
// 終了
// Author : 唐�ｱ結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CResult::Uninit()
{
	// サウンド情報の取得
	CSound *pSound = CApplication::GetSound();

	// サウンド終了
	pSound->StopSound();

	// スコアの解放
	Release();
}

//=============================================================================
// 更新
// Author : 唐�ｱ結斗
// 概要 : 更新を行う
//=============================================================================
void CResult::Update()
{
	// サウンド情報の取得
	CSound *pSound = CApplication::GetSound();

	AutoTransition();

	if (m_bPressEnter)
	{
		SelectMode();
	}

	FlashObj();

	// 入力情報の取得
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	if (m_bPressEnter
		&& pKeyboard->GetTrigger(DIK_RETURN))
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
		m_bPressEnter = false;
	}

	if (!m_bPressEnter
		&& m_nCntFrame >= 40)
	{
		CApplication::SetNextMode(m_nextMode);
	}
}

//=============================================================================
// 描画
// Author : 唐�ｱ結斗
// 概要 : 描画を行う
//=============================================================================
void CResult::Draw()
{

}

//=============================================================================
// オブジェクトの点滅
// Author : 唐�ｱ結斗
// 概要 : 指定のオブジェクトを点滅させる
//=============================================================================
void CResult::FlashObj()
{
	CObject2D *pObj = nullptr;

	if (m_bPressEnter)
	{
		m_fAddAlpha += 0.07f;
	}
	else if (!m_bPressEnter)
	{
		m_fAddAlpha += 0.5f;
		m_nCntFrame++;
	}

	switch (m_nextMode)
	{
	case CApplication::MODE_TITLE:
		pObj = m_pTitleObj;
		m_pGameObj->SetCol(D3DXCOLOR(0.3f, 0.1f, 1.0f, 1.0f));
		break;

	case CApplication::MODE_GAME:
		pObj = m_pGameObj;
		m_pTitleObj->SetCol(D3DXCOLOR(0.3f, 0.1f, 1.0f, 1.0f));
		break;

	default:
		assert(false);
		break;
	}

	pObj->SetCol(D3DXCOLOR(0.25f, 0.1f, 0.8f, sinf(m_fAddAlpha) * 3.0f));
}

//=============================================================================
// モードの選択
// Author : 唐�ｱ結斗
// 概要 : モードの選択する
//=============================================================================
void CResult::SelectMode()
{
	// サウンド情報の取得
	CSound *pSound = CApplication::GetSound();

	int nMode = (int)m_nextMode;

	// 入力情報の取得
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_A))
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		nMode--;

		if (nMode < 0)
		{
			nMode = 1;
		}
	}
	else if (pKeyboard->GetTrigger(DIK_D))
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		nMode++;

		if (nMode > 1)
		{
			nMode = 0;
		}
	}

	m_nextMode = (CApplication::SCENE_MODE)nMode;
}

//=============================================================================
// 自動遷移
// Author : 唐�ｱ結斗
// 概要 : 自動で画面遷移する
//=============================================================================
void CResult::AutoTransition()
{
	// サウンド情報の取得
	CSound *pSound = CApplication::GetSound();

	m_nCntFrame++;

	if (m_nCntFrame >= 1800)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
		m_bPressEnter = false;
		m_nextMode = CApplication::MODE_TITLE;
		m_nCntFrame = 0;
	}
}

