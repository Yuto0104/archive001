//**************************************************************************************************
//
// �v�Z����(calculation.h)
// Auther�F�������l
//
//**************************************************************************************************
#ifndef _CALCULATION_H_			// ���̃}�N����`������ĂȂ�������
#define _CALCULATION_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"

//***************************************************************
// �v���g�^�C�v�錾
//***************************************************************
// ����֐�
D3DXVECTOR3	WorldCastVtx(D3DXVECTOR3 vtx, D3DXVECTOR3 FormerPos, D3DXVECTOR3 FormerRot);
float RotNormalization(float fRot);
void SetVertex(VERTEX_2D *pVtx, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fAngele, float fLength, float SizeX, int nType);
void SetRhw(VERTEX_2D *pVtx);
void SetVtxColor(VERTEX_2D *pVtx, float fRed, float fGreen, float fBlue, float fAlpha);
void SetVtxTexture(VERTEX_2D *pVtx, float fTexU, float fTexV);

#endif
