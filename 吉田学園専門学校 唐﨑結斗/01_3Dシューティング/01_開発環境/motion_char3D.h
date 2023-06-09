//=============================================================================
//
// 3Dモーションキャラクタークラス(motion_char3D.h)
// Author : 唐�ｱ結斗
// 概要 : 3Dプレイヤー生成を行う
//
//=============================================================================
#ifndef _MOTION_CHAR3D_H_			// このマクロ定義がされてなかったら
#define _MOTION_CHAR3D_H_			// 二重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "model3D.h"
#include "main.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CMotion;

//=============================================================================
// 3Dプレイヤークラス
// Author : 唐�ｱ結斗
// 概要 : 3Dプレイヤー生成を行うクラス
//=============================================================================
class CMotionChar3D : public CModel3D
{
public:
	//--------------------------------------------------------------------
	// 静的メンバ関数
	//--------------------------------------------------------------------
	static CMotionChar3D *Create(const char *pName);			// 3Dプレイヤーの生成

	//--------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------------
	CMotionChar3D();
	~CMotionChar3D();

	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------
	virtual HRESULT Init(const char *pName);									// 初期化
	void Uninit() override;														// 終了
	void Update() override;														// 更新
	void Draw() override;														// 描画
	void ReloadMotion(const char *pName);										// モーションの再読み込み
	void SetNumMotion(int nNumMotion) { m_nNumMotion = nNumMotion; }			// モーションナンバーの設定
	int GetNumMotion() { return m_nNumMotion; }									// モーションナンバーの取得
	
private:
	//--------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------
	CMotion		*m_pMotion;				// モーションインスタンス
	int			m_nNumMotion;			// 現在のモーション番号
	int			m_nNumMotionOld;		// 過去のモーション番号
	bool		m_bMotion;				// モーションの使用状況
	bool		m_bMotionBlend;			// モーションブレンドの使用状況
};

#endif