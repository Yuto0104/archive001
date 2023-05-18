//**************************************************************************************************
//
// �v���X�G���^�[�̐ݒ菈��
// Auther�F�������l
//
//**************************************************************************************************
#ifndef _PRESS_ENTER_H_		// ���̃}�N����`������ĂȂ�������
#define _PRESS_ENTER_H_		// ��d�C���N�\���[�h�h�~�̃}�N����`

#include"main.h"

//*************************************************************
// �}�N����`
//*************************************************************
#define		MAX_OFFSET_PE_X					(320.0f)		// �傫��(��)
#define		MAX_OFFSET_PE_Y					(50.0f)			// �傫��(����)
#define		PRESS_ENTER_POS_Y				(560.0f)		// �ʒu
#define		MAX_COUNT_STATE_PE				(30)			// ��ԃJ�E���^�[�̍ő�l
#define		MAX_FLASHING					(5 * 2)			// �_�ŉ񐔂̍ő�l
#define		FLASHING_COUNT_STATE_PE			(3)				// �_�Ŏ��؂�ւ��̃J�E���^�[

//************************************************************
// �v���X�G���^�[�̏�Ԃ̗񋓌^
//************************************************************
typedef enum
{
	PRESSENTERSTATE_NORMAL = 0,			// �ʏ���
	PRESSENTERSTATE_TRANSPARENCY,		// �������
	PRESSENTERSTATE_FLASHING,			// �_�ŏ��
	PRESSENTERSTATE_MAX					// ��Ԃ̎�ނ̍ő吔
}PRESSENTERSTATE;

//************************************************************
// �v���X�G���^�[�̍\���̂��`
//************************************************************
typedef struct
{
	D3DXVECTOR3			pos;							// ���S�_
	D3DXVECTOR3			offset;							// ���S�_����̍�
	D3DXVECTOR3			rot;							// ����
	D3DXCOLOR			col;							// �J���[
	PRESSENTERSTATE		state;							// ���
	float				fLength;						// �Ίp���̒���
	float				fAngele;						// �Ίp���̊p�x
	int					nCountState;					// ��ԃJ�E���^�[
	int					nCountFlashing;					// �_�ŉ񐔂̃J�E���^�[
	int					nDecision;						// �_�ŏ�Ԃ̔���p
	bool				bUse;							// �g�p���Ă邩�ǂ���
}PressEnter;

//****************************************
// �v���X�G���^�[�錾
//****************************************
void	InitPressEnter		(void);
void	UninitPressEnter	(void);
void	UpdatePressEnter	(void);
void	DrawPressEnter		(void);
void	SetPressEnter		(D3DXVECTOR3 pos, D3DXVECTOR3 offset);

#endif
