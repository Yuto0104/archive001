//=============================================================================
//
// �Q�[���N���X(game.h)
// Author : �������l
// �T�v : �Q�[���N���X�̊Ǘ����s��
//
//=============================================================================
#ifndef _GAME_H_		// ���̃}�N����`������ĂȂ�������
#define _GAME_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "scene_mode.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CMotionPlayer3D;
class CScore;
class CLifeManager;
class CEnergyGage;
class CEnemyManager;

//=============================================================================
// �Q�[���N���X
// Author : �������l
// �T�v : �Q�[���������s���N���X
//=============================================================================
class CGame : public CSceneMode
{
public:
	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CMotionPlayer3D *GetMotionPlayer3D() { return m_MotionPlayer3D; }			// ���[�V�����v���C���[�̃Q�b�^�[
	static CScore *GetScore() { return m_pScore; }										// �X�R�A�̎擾
	static CLifeManager *GetLifeManager() { return m_pLifeManager; }					// ���C�t�}�l�[�W���[�̎擾
	static CEnergyGage *GetEnergyGage() { return m_pEnergyGage; }						// �G�l���M�[�Q�[�W�̎擾
	static CEnemyManager *GetEnemyManager() { return m_pEnemyManager; }					// �G�l�~�[�}�l�[�W���[�̎擾
	static bool GetUsePlayer() { return m_bUsePlayer; }									// �v���C���[�̎g�p�󋵂̎擾
	static void SetUsePlayer(const bool bUse) { m_bUsePlayer = bUse; }					// �v���C���[�̎g�p�󋵂̐ݒ�
	static void SetGame(const bool bGame) { m_bGame = bGame; }							// �Q�[���̏󋵂̐ݒ�

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CGame();
	~CGame() override;

	//--------------------------------------------------------------------
	// �ÓI�����o�ϐ�
	//--------------------------------------------------------------------
	static CMotionPlayer3D *m_MotionPlayer3D;										// ���[�V�����v���C���[�N���X
	static CScore *m_pScore;														// �X�R�A�N���X
	static CLifeManager *m_pLifeManager;											// ���C�t�}�l�[�W���[�N���X
	static CEnergyGage *m_pEnergyGage;												// �G�l���M�[�Q�[�W
	static CEnemyManager *m_pEnemyManager;											// �G�l�~�[�}�l�[�W���[�N���X
	static bool m_bUsePlayer;														// �v���C���[���g�p���Ă��邩
	static bool m_bGame;															// �Q�[���̏�

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update() override;		// �X�V
	void Draw() override;		// �`��
};

#endif



