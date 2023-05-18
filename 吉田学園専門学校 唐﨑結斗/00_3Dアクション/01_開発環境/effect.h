//**************************************************************************************************
//
// �G�t�F�N�g�`�揈��(effect.h)
// Auther�F�������l
//
//**************************************************************************************************
#ifndef _EFFECT_H_			// ���̃}�N����`������ĂȂ�������
#define _EFFECT_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"

//**********************************************************
// �G�t�F�N�g�̃e�N�X�`���̗񋓌^
//**********************************************************
typedef enum
{
	EFFECTTEXTURE_000 = 0,		// �e�N�X�`��000
	EFFECTTEXTURE_001,			// �e�N�X�`��001
	EFFECTTEXTURE_002,			// �e�N�X�`��002
	EFFECTTEXTURE_003,			// �e�N�X�`��003
	EFFECTTEXTURE_004,			// �e�N�X�`��004
	EFFECTTEXTURE_005,			// �e�N�X�`��005
	MAX_EFFECTTEXTURE			// �G�t�F�N�g�e�N�X�`���̍ő吔
}EFFECTTEXTURE;

//**********************************************************
// �G�t�F�N�g�̏�Ԃ̗񋓌^
//**********************************************************
typedef enum
{
	EFFECTTYPE_NORMAL = 0,		// �ʏ�G�t�F�N�g
	EFFECTTYPE_FIELD,			// �n�ʃG�t�F�N�g
	EFFECTTYPE_WALL,			// �ǃG�t�F�N�g
	MAX_EFFECTTYPE				// �G�t�F�N�g�^�C�v�̍ő吔
}EFFECTTYPE;

//**********************************************************
// �G�t�F�N�g�̃��u�����f�B���O�̗񋓌^
//**********************************************************
typedef enum
{
	EFFECTALPHABLEND_ADDITIVE = 0,		// ���Z����
	EFFECTALPHABLEND_SUBTRACTIVE,		// ���Z����
	MAX_EFFECTALPHABLEND				// ���u�����f�B���O�̍ő吔
}EFFECTALPHABLEND;

//***************************************************************
// �G�t�F�N�g�\���̂��`
//***************************************************************
typedef struct
{
	D3DXVECTOR3			pos;					// �ʒu
	D3DXVECTOR3			move;					// �ړ���
	D3DXVECTOR3			rot;					// ����
	D3DXMATRIX			mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXCOLOR			col;					// �J���[
	D3DCMPFUNC			zFuncType;				// Z�o�b�t�@�̔�r�^�C�v
	EFFECTTYPE			EffectType;				// �G�t�F�N�g�^�C�v
	EFFECTTEXTURE		EffectTexture;			// �G�t�F�N�g�e�N�X�`��
	EFFECTALPHABLEND	EffectAlphaBlend;		// �G�t�F�N�g�̃��u�����h���[�h
	float				fRadius;				// ���a
	float				fAttenuationRadius;		// ���a�̌�����
	float				fAttenuationAlpha;		// ���l�̌�����
	float				fSpeed;					// �ړ����x
	float				fGravity;				// �d��
	int					nIdx;					// �C���f�b�N�X
	int					nLife;					// ����
	bool				bShadow;				// �e���g�p��
	bool				bUse;					// �g�p��
}Effect;

//***************************************************************
// �v���g�^�C�v�錾
//***************************************************************
// ����֐�
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

// ������֐�
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
