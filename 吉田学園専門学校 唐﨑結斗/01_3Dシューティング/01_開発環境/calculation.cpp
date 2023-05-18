//**************************************************************************************************
//
// �v�Z����(calculation.cpp)
// Auther�F�������l
//
//**************************************************************************************************

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"
#include "calculation.h"

//=============================================================================
// ���[���h���W�ւ̃L���X�g����
// Author : �������l
// �T�v : pos,rot�̍s��v�Z���s���A���[�J�����W�����[���h���W�ɕϊ�����
//=============================================================================
D3DXVECTOR3	WorldCastVtx(D3DXVECTOR3 vtx, D3DXVECTOR3 FormerPos, D3DXVECTOR3 FormerRot)
{
	// �ϐ��錾
	D3DXMATRIX		mtxWorldVtx;				// ���[���h�}�g���b�N�X
	D3DXMATRIX		mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��������[�s��]��[�P�ʍs��]�ɏ�����)
	D3DXMatrixIdentity(&mtxWorldVtx);

	// �ʒu�𔽉f
	// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, vtx.x, vtx.y, vtx.z);
	D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxTrans);		// �s��|���Z�֐�

	// �����̔��f
	// �s���]�֐� (��������[���[(y)�s�b�`(x)���[��(z)]�����̉�]�s����쐬)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, FormerRot.y, FormerRot.x, FormerRot.z);

	// �s��|���Z�֐� (������ * ��O������������Ɋi�[)
	D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxRot);

	// �ʒu�𔽉f
	// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, FormerPos.x, FormerPos.y, FormerPos.z);
	D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxTrans);		// �s��|���Z�֐�

	return D3DXVECTOR3(mtxWorldVtx._41, mtxWorldVtx._42, mtxWorldVtx._43);
}

D3DXVECTOR3 WorldCastVtx(D3DXVECTOR3 vtx, D3DXVECTOR3 FormerPos, D3DXQUATERNION FormeQuaternion)
{
	// �ϐ��錾
	D3DXMATRIX		mtxWorldVtx;				// ���[���h�}�g���b�N�X
	D3DXMATRIX		mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��������[�s��]��[�P�ʍs��]�ɏ�����)
	D3DXMatrixIdentity(&mtxWorldVtx);

	// �ʒu�𔽉f
	// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, vtx.x, vtx.y, vtx.z);
	D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxTrans);		// �s��|���Z�֐�

	 // �N�H�[�^�j�I���̎g�p�����p���̐ݒ�
	D3DXMatrixRotationQuaternion(&mtxRot, &FormeQuaternion);            // �N�I�[�^�j�I���ɂ��s���]

	// �s��|���Z�֐� (������ * ��O������������Ɋi�[)
	D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxRot);

	// �ʒu�𔽉f
	// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, FormerPos.x, FormerPos.y, FormerPos.z);
	D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxTrans);		// �s��|���Z�֐�

	return D3DXVECTOR3(mtxWorldVtx._41, mtxWorldVtx._42, mtxWorldVtx._43);
}

//=============================================================================
// �p�x�̐��K������
// Author : �������l
// �T�v : �p�x���~������2�{�𒴂����Ƃ��ɔ͈͓��ɖ߂�
//=============================================================================
float RotNormalization(float fRot)
{
	if (fRot >= D3DX_PI)
	{// �ړ������̐��K��
		fRot -= D3DX_PI * 2;
	}
	else if (fRot <= -D3DX_PI)
	{// �ړ������̐��K��
		fRot += D3DX_PI * 2;
	}

	return fRot;
}

//---------------------------------------------------------------------------
// �X�N���[�����W�����[���h���W�ւ̃L���X�g
// Author : �������l
// �T�v : 
//---------------------------------------------------------------------------
D3DXVECTOR3 WorldCastScreen(D3DXVECTOR3 *screenPos,			// �X�N���[�����W
	D3DXVECTOR3 screenSize,									// �X�N���[���T�C�Y
	D3DXMATRIX* mtxView,									// �r���[�}�g���b�N�X
	D3DXMATRIX* mtxProjection)								// �v���W�F�N�V�����}�g���b�N�X
{
	// �ϐ��錾
	D3DXVECTOR3 ScreenPos;

	// �v�Z�p�}�g���b�N�X�̐錾
	D3DXMATRIX InvView, InvPrj, VP, InvViewport;

	// �e�s��̋t�s����Z�o
	D3DXMatrixInverse(&InvView, NULL, mtxView);
	D3DXMatrixInverse(&InvPrj, NULL, mtxProjection);
	D3DXMatrixIdentity(&VP);

	VP._11 = screenSize.x / 2.0f; VP._22 = -screenSize.y / 2.0f;
	VP._41 = screenSize.x / 2.0f; VP._42 = screenSize.y / 2.0f;

	D3DXMatrixInverse(&InvViewport, NULL, &VP);

	// ���[���h���W�ւ̃L���X�g
	D3DXMATRIX mtxWorld = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord(&ScreenPos, screenPos, &mtxWorld);

	return ScreenPos;
}

D3DXVECTOR3 ScreenCastWorld(D3DXVECTOR3 * screenPos, D3DXVECTOR3 screenSize, D3DXMATRIX * mtxView, D3DXMATRIX * mtxProjection, D3DXMATRIX *mtxWorld)
{
	// �v�Z�p�}�g���b�N�X�̐錾
	D3DXMATRIX VP, InvViewport;

	// �e�s��̋t�s����Z�o
	VP._11 = screenSize.x / 2.0f; VP._22 = -screenSize.y / 2.0f;
	VP._41 = screenSize.x / 2.0f; VP._42 = screenSize.y / 2.0f;

	// �s��|���Z�֐�
	D3DXMatrixMultiply(&InvViewport, mtxWorld, &VP);
	D3DXMatrixMultiply(&InvViewport, mtxWorld, mtxProjection);
	D3DXMatrixMultiply(&InvViewport, mtxWorld, mtxView);

	return D3DXVECTOR3(InvViewport._41, InvViewport._42, InvViewport._43);
}
