//**************************************************************************************************
//
// �J��������(camera.h)
// Auther�F�������l
//
//**************************************************************************************************
#ifndef _CAMERA_H_			// ���̃}�N����`������ĂȂ�������
#define _CAMERA_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include"main.h"

//***************************************************************
// �J�����\���̂��`
//***************************************************************
typedef struct
{
	D3DXVECTOR3			posV;				// ���_
	D3DXVECTOR3			posR;				// �����_
	D3DXVECTOR3			vecU;				// ������x�N�g��
	D3DXVECTOR3			posVDest;			// ���_�̖ړI�̈ʒu
	D3DXVECTOR3			posRDest;			// �����_�̖ړI�̈ʒu
	D3DXVECTOR3			rot;				// ����
	D3DXVECTOR3			rotMove;			// �ړ�����
	D3DXVECTOR3			rotDest;			// �ړI�̌���
	D3DXVECTOR3			roll;				// ��]��
	D3DXMATRIX			mtxProjection;		// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX			mtxView;			// �r���[�}�g���b�N�X	
	float				fDistance;			// ���_���璍���_�܂ł̋���
	float				fZoomSpeed;			// �Y�[�����x
}Camera;

//***************************************************************
// �v���g�^�C�v�錾
//***************************************************************
// ����֐�
void InitCamera(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU, D3DXVECTOR3 rot);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);

// ���֐�
Camera *GetCamera(void);
void RotateCamera(void);
void MoveCamera(void);
void FollowCamera(void);
void AutoRotateCamera(void);
void TitleRotateCamera(void);

#endif
