//**************************************************************************************************
//
//�_�f�Q�[�W�̐ݒ菈��
//Auther�F�������l
//
//**************************************************************************************************
#ifndef _OXYGEN_GAUGE_H_		//���̃}�N����`������ĂȂ�������
#define _OXYGEN_GAUGE_H_		//��d�C���N�\���[�h�h�~�̃}�N����`

#include"main.h"

//**********************************************************
// ���[�V�������[�h�̗񋓌^
//**********************************************************
typedef enum
{
	TYPE_GAUGE = 0,					// �Q�[�W
	TYPE_BG,						// �w�i
	MAX_STAMINA_GAUGE_TYPE			// �X�^�~�i�Q�[�W�^�C�v�̍ő吔
}STAMINA_GAUGE_TYPE;

//*************************************************************
//�}�N����`
//*************************************************************
#define MAX_OFFSET_OXYGEN_GAUGE_X0		(40.0f)									// �傫��(��)[0]
#define MAX_OFFSET_OXYGEN_GAUGE_Y0		(370.0f)								// �傫��(����)[0]
#define MAX_OFFSET_OXYGEN_GAUGE_X1		(40.0f)									// �傫��(��)[1]
#define MAX_OFFSET_OXYGEN_GAUGE_Y1		(0.0f)									// �傫��(����)[1]
#define MAX_STAMINA_GAUGE				(1 * MAX_STAMINA_GAUGE_TYPE)			// �ݒu���̍ő�

//************************************************************
//�_�f�Q�[�W�̍\���̂��`
//************************************************************
typedef struct
{
	D3DXVECTOR3				pos;							// ���S�_
	D3DXVECTOR3				size;							// �傫��
	D3DXVECTOR3				maxSize;						// �傫���̍ő�l
	D3DXVECTOR3				rot;							// ����
	D3DXCOLOR				col;							// �J���[
	STAMINA_GAUGE_TYPE		type;							// �^�C�v
	float					fLength;						// �Ίp���̒���
	float					fAngele;						// �Ίp���̊p�x
	bool					bUse;							// �g�p���Ă邩�ǂ���
}StaminaGauge;

//****************************************
//�v���g�^�C�v�錾
//****************************************
void InitStaminaGauge(void);
void UninitStaminaGauge(void);
void UpdateStaminaGauge(void);
void DrawStaminaGauge(void);
void SetStaminaGauge(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nType);
void SubStaminaGauge(int nCnt);
StaminaGauge *GetStaminaGauge(void);

#endif
