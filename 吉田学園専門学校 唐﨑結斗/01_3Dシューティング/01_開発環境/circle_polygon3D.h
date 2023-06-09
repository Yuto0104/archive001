//=============================================================================
//
// 3D�~�|���S���N���X(circle_polygon3D.h)
// Author : �������l
// �T�v : �I�u�W�F�N�g�������s��
//
//=============================================================================
#ifndef _CIRCLE_POLYGON3D_H_		// ���̃}�N����`������ĂȂ�������
#define _CIRCLE_POLYGON3D_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object3D.h"
#include "texture.h"

//=============================================================================
// 3D�~�|���S���N���X
// Author : �������l
// �T�v : 3D�~�|���S���������s���N���X
//=============================================================================
class CCirclePolygon3D : public CObject
{
public:
	// ���_�t�H�[�}�b�g
	const unsigned int	FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	//*****************************************************************************
	// �\���̒�`
	//*****************************************************************************
	// ���_�f�[�^
	typedef struct
	{
		D3DXVECTOR3			pos;			// ���_���W
		D3DXVECTOR3			nor;			// �@���x�N�g��
		D3DCOLOR			col;			// ���_�J���[
		D3DXVECTOR2			tex;			// �e�N�X�`�����W
	}VERTEX_3D;

	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CCirclePolygon3D *Create(void);				// 2D�I�u�W�F�N�g�̐���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CCirclePolygon3D();
	~CCirclePolygon3D();

	//--------------------------------------------------------------------
	// �I�[�o�[���C�h�֐�
	//--------------------------------------------------------------------
	HRESULT Init() override;														// ������
	void Uninit() override;															// �I��
	void Update() override;															// �X�V
	void Draw() override;															// �`��
	void SetPos(const D3DXVECTOR3 &pos) override;									// �ʒu�̃Z�b�^�[
	void SetPosOld(const D3DXVECTOR3 &posOld) override { m_posOld = posOld; }		// �ߋ��ʒu�̃Z�b�^�[
	void SetRot(const D3DXVECTOR3 &rot) override;									// �����̃Z�b�^�[
	void SetSize(const D3DXVECTOR3 &size) override;									// �傫���̃Z�b�^�[
	D3DXVECTOR3 GetPos() override { return m_pos; }									// �ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetPosOld()  override { return m_posOld; }							// �ߋ��ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetRot()  override { return m_rot; }								// �����̃Q�b�^�[
	D3DXVECTOR3 GetSize()  override { return m_size; }								// �傫���̃Q�b�^�[

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void SetMtxWorld(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }		// ���[���h�}�g���b�N�X�̃Z�b�^�[
	D3DXMATRIX GetMtxWorld() { return m_mtxWorld; }							// ���[���h�}�g���b�N�X�̃Q�b�^�[
	void SetVtx();															// ���_���W�Ȃǂ̐ݒ�

private:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;			// ���_�o�b�t�@
	D3DXMATRIX						m_mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3						m_pos;				// �ʒu
	D3DXVECTOR3						m_posOld;			// �ߋ��ʒu
	D3DXVECTOR3						m_rot;				// ����
	D3DXVECTOR3						m_size;				// �傫��
	D3DXCOLOR						m_col;				// �J���[
	float							m_fRot;				// �p�x
	float							m_fRadius;			// ���a
	int								m_nVtx;				// ���_��
};

#endif




