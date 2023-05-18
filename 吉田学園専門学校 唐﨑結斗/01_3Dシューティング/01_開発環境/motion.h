//**************************************************************************************************
//
// ���[�V��������(motion.h)
// Auther�F�������l
// �T�v : ���[�V�����N���X�̐ݒ�
//
//**************************************************************************************************
#ifndef _MOTION_H_			// ���̃}�N����`������ĂȂ�������
#define _MOTION_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"
#include "model3D.h"
#include "renderer.h"

//=============================================================================
// ���[�V�����N���X
// Author : �������l
// �T�v : ���[�V�����ݒ���s���N���X
//=============================================================================
class CMotion
{
public:
	//***************************************************************************
	// �萔��`
	//***************************************************************************
	static const unsigned int MAX_MOTION = (128);					// ���[�V�������̍ő吔
	static const unsigned int MAX_MODEL_PARTS = (128);				// ���f�����̍ő吔
	static const unsigned int MAX_KEY = (64);						// �L�[�̍ő吔
	static const unsigned int MAX_KEYSET = (64);					// �L�[�ݒ�̍ő吔
	static const unsigned int MOTION_BLEND_FRAM = (12);				// ���[�V�����u�����h�̃t���[����	

	//***************************************************************
	// �p�[�c�t�@�C���\���̂��`
	//***************************************************************
	typedef struct
	{
		char	aName[MAX_MODEL_PARTS];		// ���O
	}PartsFile;

	//***************************************************************
	// �L�[�\���̂��`
	//***************************************************************
	typedef struct
	{
		D3DXVECTOR3		pos;	// ���݈ʒu
		D3DXVECTOR3		rot;	// ���݂̌���
	}MyKey;

	//***************************************************************
	// �L�[�ݒ�\���̂��`
	//***************************************************************
	typedef struct
	{
		int		nFrame;			// �t���[����
		MyKey	key[MAX_KEY];	// �L�[���
	}MyKeySet;

	//***************************************************************
	// ���[�V�����ݒ�\���̂��`
	//***************************************************************
	typedef struct
	{
		int				nNumKey;				// �L�[��
		int				nCntKeySet;				// �L�[�Z�b�g�J�E���g
		int				nCntFrame;				// �t���[���J�E���g
		bool			bLoop;					// ���[�v�g�p��
		MyKeySet		keySet[MAX_KEYSET];		// �L�[�ݒ���
	}MyMotion;

	//***************************************************************
	// ���f���p�[�c�\���̂��`
	//***************************************************************
	typedef struct
	{
		CModel3D::MODEL_MATERIAL		material;				// �}�e���A�����
		D3DXMATRIX						mtxWorld;				// ���[���h�}�g���b�N�X
		D3DXVECTOR3						posOrigin;				// ���̈ʒu
		D3DXVECTOR3						rotOrigin;				// ���̌���
		D3DXVECTOR3						pos;					// ���݂̈ʒu
		D3DXVECTOR3						rot;					// ���݂̌���
		D3DXVECTOR3						posDest;				// �ړI�̈ʒu
		D3DXVECTOR3						rotDest;				// �ړI�̌���
		int								nIdxModelParent;		// �e���f���̃C���f�b�N�X��
		int								nType;					// �p�[�c�̃^�C�v
	}Parts;

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CMotion(const char *pFileName);
	~CMotion();

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	// ������
	void Init(void);

	// ���[�V�����̏����ݒ�
	void SetMotion(const int nCntMotionSet);

	// �p�[�c�̐ݒ�
	void SetParts(D3DXMATRIX mtxWorld);

	// �p�[�c�̐F�ݒ�
	void SetParts(D3DXMATRIX mtxWorld, const D3DXCOLOR col);

	// ���[�V�����̍Đ�
	bool PlayMotion(const int nCntMotionSet);

	// ���[�V�����u�����h
	bool MotionBlend(const int nCntMotionSet);	

	// ���[�V�����ǂݍ���
	void LoodSetMotion(const char *pFileName);

	// �I��
	void Uninit(void);

	// �J�E���g���Z�b�g
	void CntReset(const int nNumMotionOld);

	// ���[�V�����̍ēǂݍ���
	void ReloadMotion(const char *pFileName);

private:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	MyMotion	*m_motion;							// ���[�V����
	Parts		*m_parts;							// �p�[�c
	PartsFile	m_partsFile[MAX_MODEL_PARTS];		// �p�[�c��X�t�@�C����
	int			m_nMaxParts;						// �p�[�c��
};

#endif

