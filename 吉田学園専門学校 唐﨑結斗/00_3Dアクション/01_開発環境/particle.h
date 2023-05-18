//**************************************************************************************************
//
// �p�[�e�B�N���`�揈��(particle.h)
// Auther�F�������l
//
//**************************************************************************************************
#ifndef _PARTICLE_H_			// ���̃}�N����`������ĂȂ�������
#define _PARTICLE_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"

//**********************************************************
// �p�[�e�B�N���̃^�C�v�̗񋓌^
//**********************************************************
typedef enum
{
	PARTICLETYPE_NORMAL = 0,		// �ʏ�p�[�e�B�N��
	MAX_PARTICLETYPE				// �G�t�F�N�g�^�C�v�̍ő吔
}PARTICLETYPE;

//***************************************************************
// �p�[�e�B�N���\���̂��`
//***************************************************************
typedef struct
{
	D3DXVECTOR3		pos;					// �ʒu
	D3DXVECTOR3		posPop;					// �����ʒu
	D3DXVECTOR3		rot;					// ����
	D3DXCOLOR		col;					// �J���[
	float			fRadius;				// ���a
	float			fSpeed;					// �ړ����x
	float			fGravity;				// �d��
	int				nLife;					// ����
	int				nTexture;				// �e�N�X�`��
	int				nAlphaBlend;			// ���u�����h
	int				nTime;					// ��������
	int				nNumParticle;			// ������
	bool			bShadow;				// �e���g�p��
	bool			bUse;					// �g�p��
}Particle;

//***************************************************************
// �v���g�^�C�v�錾
//***************************************************************
// ����֐�
void InitParticle(void);
void UpdateParticle(void);
void SetParticle(D3DXVECTOR3 pos, 
	D3DXVECTOR3	posPop,
	D3DXVECTOR3 rot, 
	D3DXCOLOR col,
	float fRadius,
	float fSpeed,
	float fGravity,
	int	nLife,
	int	nTexture,
	int nAlphaBlend,
	int	nTime,
	int nNumParticle,
	bool bShadow);

#endif
