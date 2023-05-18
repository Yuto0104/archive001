//=============================================================================
//
// 3D���f���N���X(model3D.h)
// Author : �������l
// �T�v : 3D���f���������s��
//
//=============================================================================
#ifndef _MODEL_H_			// ���̃}�N����`������ĂȂ�������
#define _MODEL_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"
#include "main.h"

//=============================================================================
// 3D���f���N���X
// Author : �������l
// �T�v : 3D���f���������s���N���X
//=============================================================================
class CModel3D : public CObject
{
public:
	//--------------------------------------------------------------------
	// ���f���̃}�e���A�����
	// Author : �������l
	// �T�v : ���f���̃}�e���A�����̐ݒ�
	//--------------------------------------------------------------------
	struct MODEL_MATERIAL
	{
		LPD3DXMESH		pMesh;				// ���b�V�����ւ̃|�C���^
		LPD3DXBUFFER	pBuffer;			// �}�e���A�����ւ̃|�C���^
		DWORD			nNumMat;			// �}�e���A�����̐�
		int				*pNumTex;			// �e�N�X�`���^�C�v
		char			aFileName[0xff];	// X�t�@�C���̃p�X
	};

	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CModel3D *Create(const int nModelNam);			// 3D���f���̐���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CModel3D();
	~CModel3D();

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	HRESULT Init() override;																		// ������
	HRESULT Init(const int nModelNam);																// ������
	void Uninit() override;																			// �I��
	void Update() override;																			// �X�V
	void Draw() override;																			// �`��
	void SetPos(const D3DXVECTOR3 &pos) override;													// �ʒu�̃Z�b�^�[
	void SetPosOld(const D3DXVECTOR3 &posOld) override { m_posOld = posOld; }						// �ߋ��ʒu�̃Z�b�^�[
	void SetRot(const D3DXVECTOR3 &rot) override;													// �����̃Z�b�^�[
	void SetSize(const D3DXVECTOR3 &size) override;													// �傫���̃Z�b�^�[
	void SetMtxWorld(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }								// ���[���h�}�g���b�N�X�̐ݒ�
	D3DXVECTOR3 GetPos() override { return m_pos; }													// �ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetPosOld()  override { return m_posOld; }											// �ߋ��ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetRot()  override { return m_rot; }												// �����̃Q�b�^�[
	D3DXVECTOR3 GetSize()  override { return m_size; }												// �傫���̃Q�b�^�[
	D3DXMATRIX GetMtxWorld() { return m_mtxWorld; }													// ���[���h�}�g���b�N�X�̎擾
	D3DXVECTOR3	WorldCastVtx(D3DXVECTOR3 vtx, D3DXVECTOR3 FormerPos, D3DXVECTOR3 FormerRot);		// ���[�J�����W�����[���h���W�ɕϊ�����

private:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	MODEL_MATERIAL		m_material;			// �}�e���A�����
	D3DXMATRIX			m_mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3			m_pos;				// �ʒu
	D3DXVECTOR3			m_posOld;			// �ߋ��ʒu
	D3DXVECTOR3			m_rot;				// ����
	D3DXVECTOR3			m_size;				// �傫��
};

#endif