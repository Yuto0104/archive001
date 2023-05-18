//**************************************************************************************************
//
// �v�Z����(calculation.h)
// Auther�F�������l
//
//**************************************************************************************************
#ifndef _CALCULATION_H_			// ���̃}�N����`������ĂȂ�������
#define _CALCULATION_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//***************************************************************
// �v���g�^�C�v�錾
//***************************************************************
// ����֐�
D3DXVECTOR3	WorldCastVtx(D3DXVECTOR3 vtx, D3DXVECTOR3 FormerPos, D3DXVECTOR3 FormerRot);				// ���[���h���W�ɃL���X�g
D3DXVECTOR3	WorldCastVtx(D3DXVECTOR3 vtx, D3DXVECTOR3 FormerPos, D3DXQUATERNION FormeQuaternion);		// ���[���h���W�ɃL���X�g
float RotNormalization(float fRot);																		// �p�x�̐��K��
D3DXVECTOR3 WorldCastScreen(D3DXVECTOR3 *screenPos,														// �X�N���[�����W
	D3DXVECTOR3 screenSize,																				// �X�N���[���T�C�Y
	D3DXMATRIX* mtxView,																				// �r���[�}�g���b�N�X
	D3DXMATRIX* mtxProjection);																			// �v���W�F�N�V�����}�g���b�N�X
D3DXVECTOR3 ScreenCastWorld(D3DXVECTOR3 *screenPos,														// �X�N���[�����W
	D3DXVECTOR3 screenSize,																				// �X�N���[���T�C�Y
	D3DXMATRIX* mtxView,																				// �r���[�}�g���b�N�X
	D3DXMATRIX* mtxProjection,																			// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX *mtxWorld);																				// ���[���h���W				

#endif
