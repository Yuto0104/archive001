//=============================================================================
//
// 3D���f���N���X(model3D.h)
// Author : �������l
// �T�v : 3D���f���������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "model3D.h"
#include "renderer.h"
#include "application.h"
#include "model_manager.h"
#include "texture.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : 3D���f���𐶐�����
//=============================================================================
CModel3D * CModel3D::Create(const int nModelNam)
{
	// �I�u�W�F�N�g�C���X�^���X
	CModel3D *pModel3D = nullptr;

	// �������̉��
	pModel3D = new CModel3D;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pModel3D != nullptr);

	// ���l�̏�����
	pModel3D->Init(nModelNam);

	// �C���X�^���X��Ԃ�
	return pModel3D;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CModel3D::CModel3D()
{
	memset(&m_material, 0, sizeof(MODEL_MATERIAL));				// �}�e���A�����
	m_mtxWorld = {};											// ���[���h�}�g���b�N�X
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ߋ��ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �傫��
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CModel3D::~CModel3D()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CModel3D::Init()
{
	// �����o�ϐ��̏�����
	memset(&m_material, 0, sizeof(MODEL_MATERIAL));				// �}�e���A�����
	m_mtxWorld = {};											// ���[���h�}�g���b�N�X
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ߋ��ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ����
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);						// �傫��

	return S_OK;
}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CModel3D::Init(const int nModelNam)
{
	// ���f���}�l�[�W���[�N���X�̐ݒ�
	CModelManager *pModelManager = CApplication::GetModelManager();

	// �����o�ϐ��̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ߋ��ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ����
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);					// �傫��

	// ���f���̃}�e���A�����̐ݒ�
	m_material = pModelManager->GetModelMateria(nModelNam);
	
	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CModel3D::Uninit()
{
	// �I�u�W�F�N�g3D�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : 2D�X�V���s��
//=============================================================================
void CModel3D::Update()
{

}

//=============================================================================
// �`��
// Author : �������l
// �T�v : 2D�`����s��
//=============================================================================
void CModel3D::Draw()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// �e�N�X�`���|�C���^�̎擾
	CTexture *pTexture = CApplication::GetTexture();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxScaling;

	// ���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);											// �s�񏉊����֐�

	// �T�C�Y�̔��f
	D3DXMatrixScaling(&mtxScaling, m_size.x, m_size.y, m_size.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScaling);					// �s��|���Z�֐�

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);			// �s���]�֐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);						// �s��|���Z�֐� 

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);				// �s��ړ��֐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);					// �s��|���Z�֐�

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	if (m_material.pBuffer != nullptr)
	{// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_material.pBuffer->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_material.nNumMat; nCntMat++)
		{// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pTexture->GetTexture(m_material.pNumTex[nCntMat]));

			// ���f���p�[�c�̕`��
			m_material.pMesh->DrawSubset(nCntMat);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, nullptr);
		}
	}

	// �ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �ʒu�̃Z�b�^�[
// Author : �������l
// �T�v : �ʒu�̃����o�ϐ��Ɉ�������
//=============================================================================
void CModel3D::SetPos(const D3DXVECTOR3 &pos)
{
	// �ʒu�̐ݒ�
	m_pos = pos;
}

//=============================================================================
// �����̃Z�b�^�[
// Author : �������l
// �T�v : �����̃����o�ϐ��Ɉ�������
//=============================================================================
void CModel3D::SetRot(const D3DXVECTOR3 &rot)
{
	// �ʒu�̐ݒ�
	m_rot = rot;
}

//=============================================================================
// �傫���̃Z�b�^�[
// Author : �������l
// �T�v : �傫���̃����o�ϐ��Ɉ�������
//=============================================================================
void CModel3D::SetSize(const D3DXVECTOR3 & size)
{
	// �傫���̐ݒ�
	m_size = size;
}

//=============================================================================
// ���[���h���W�ւ̃L���X�g����
// Author : �������l
// �T�v : pos,rot�̍s��v�Z���s���A���[�J�����W�����[���h���W�ɕϊ�����
//=============================================================================
D3DXVECTOR3 CModel3D::WorldCastVtx(D3DXVECTOR3 vtx, D3DXVECTOR3 FormerPos, D3DXVECTOR3 FormerRot)
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
	D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxTrans);					// �s��|���Z�֐�

	return D3DXVECTOR3(mtxWorldVtx._41, mtxWorldVtx._42, mtxWorldVtx._43);
}
