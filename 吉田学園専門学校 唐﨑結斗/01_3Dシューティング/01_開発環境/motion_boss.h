//=============================================================================
//
// モーションボスクラス(motion_boss.h)
// Author : 唐�ｱ結斗
// 概要 : モーションボス生成を行う
//
//=============================================================================
#ifndef _MOTION_BOSS_H_			// このマクロ定義がされてなかったら
#define _MOTION_BOSS_H_			// 二重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "model3D.h"
#include "main.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CMotion;
class CMove;

//=============================================================================
// モーションボスクラス
// Author : 唐�ｱ結斗
// 概要 : モーションボス生成を行うクラス
//=============================================================================
class CMotionBoss : public CModel3D
{
public:
	//--------------------------------------------------------------------
	// 定数定義
	//--------------------------------------------------------------------
	//static const float				ROTATE_SPEED;
	//static const unsigned int		MAX_CNT_SHOT = 15;			// 弾発射までのカウント
	//static const unsigned int		MAX_MOTION = 2;				// モーションのカウント
	//static const unsigned int		MAX_LIFE = 5;				// ライフの最大値
	//static const unsigned int		MAX_ENERGY = 100;			// エネルギーの最大
	//static const unsigned int		MAX_CNT_RECOVERY = 60;		// 回復までのカウント
	//static const unsigned int		ENERGY_RECOVERY = 20;		// 回復に消費するエネルギー
	//static const unsigned int		ENERGY_FOLLOW_SHOT = 10;	// 追従弾発射に消費するエネルギー
	//static const unsigned int		INVINCIBLE_TIME = 20;		// 無敵時間

	//=============================================================================
	// モーションのタイプ列挙型
	// Author : 唐�ｱ結斗
	// 概要 : モーションの種別
	//=============================================================================
	enum MOTION_TYPE
	{
		TYPE_NEUTRAL = 0,			// ニュートラルモーション
		TYPE_MOVE,					// 移動モーション
		TYPE_ATTACK1,				// 攻撃モーション(1)
		TYPE_ATTACK2,				// 攻撃モーション(2)
		MAX_MOTION_TYPE,			// タイプの最大数
	};

	//=============================================================================
	// 行動種類の列挙型
	// Author : 唐�ｱ結斗
	// 概要 : 行動種類の種別
	//=============================================================================
	enum ACTION_TYPE
	{
		ACTION_NONE = 0,					// アクション無し
		ACTION_DIFFUSIONSHOT,				// 拡散弾
		ACTION_RUSH,						// 突進
		MAX_ACTION_TYPE,					// タイプの最大数
	};

	//--------------------------------------------------------------------
	// 静的メンバ関数
	//--------------------------------------------------------------------
	static CMotionBoss *Create();			// モーションボスの生成

	//--------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------------
	CMotionBoss();
	~CMotionBoss();

	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------
	HRESULT Init() override;								// 初期化
	void Uninit() override;									// 終了
	void Update() override;									// 更新
	void Draw() override;									// 描画
	void Hit(COLOR_TYPE colorType, int nAttack);			// ダメージ
	
private:
	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------
	void MotionSet();				// モーションの設定
	void Shot();					// 弾の発射
	void Move();					// 移動情報の管理
	bool CollisionScreen();			// スクリーンの当たり判定

	//--------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------
	CMotion				*m_pMotion;						// モーションインスタンス
	ACTION_TYPE			m_actionType;					// アクションタイプ
	D3DXVECTOR3			m_move;							// 移動量
	float				m_fMoveVec;						// 移動方向
	float				m_fWave;						// 波
	float				m_fSpeed;						// 移動速度
	float				m_fAddRot;						// 角度の加算
	int					m_nNumMotion;					// 現在のモーション番号
	int					m_nNumMotionOld;				// 過去のモーション番号
	int					m_nLife;						// 寿命
	int					m_nScore;						// スコア
	int					m_nCntShot;						// 弾発射までのカウント
	int					m_nMaxShot;						// 弾発射するカウント
	int					m_nCntFrame;					// フレームカウント
	bool				m_bMotion;						// モーションの使用状況
	bool				m_bMotionBlend;					// モーションブレンドの使用状況
	bool				m_bUse;							// 使用状況
};

#endif
