////=============================================================================
////
//// 3D�~�|���S���N���X(object.h)
//// Author : �������l
//// �T�v : 3D�~�|���S���������s��
////
////=============================================================================
//
////*****************************************************************************
//// �C���N���[�h
////*****************************************************************************
//#include <assert.h>
//
//#include "circle_polygon3D.h"
//#include "renderer.h"
//#include "application.h"
//
////=============================================================================
//// �C���X�^���X����
//// Author : �������l
//// �T�v : 2D3D�~�|���S���𐶐�����
////=============================================================================
//CCirclePolygon3D * CCirclePolygon3D::Create(void)
//{
//	// 3D�~�|���S���C���X�^���X
//	CCirclePolygon3D *pCirclePolygon3D = nullptr;
//
//	// �������̉��
//	pCirclePolygon3D = new CCirclePolygon3D;
//
//	// �������̊m�ۂ��ł��Ȃ�����
//	assert(pCirclePolygon3D != nullptr);
//
//	// ���l�̏�����
//	pCirclePolygon3D->Init();
//
//	// �C���X�^���X��Ԃ�
//	return pCirclePolygon3D;
//}
//
////=============================================================================
//// �R���X�g���N�^
//// Author : �������l
//// �T�v : �C���X�^���X�������ɍs������
////=============================================================================
//CCirclePolygon3D::CCirclePolygon3D()
//{
//	m_pVtxBuff = nullptr;								// ���_�o�b�t�@
//	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu
//	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
//	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �傫��
//	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);			// �J���[
//	m_fRot = 0.0f;										// �p�x
//	m_fRadius = 0.0f;									// ���a
//	m_nVtx = 0;											// ���_��
//}
//
////=============================================================================
//// �f�X�g���N�^
//// Author : �������l
//// �T�v : �C���X�^���X�I�����ɍs������
////=============================================================================
//CCirclePolygon3D::~CCirclePolygon3D()
//{
//
//}
//
////=============================================================================
//// ������
//// Author : �������l
//// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
////=============================================================================
//HRESULT CCirclePolygon3D::Init()
//{// �����_���[�̃Q�b�g
//	CRenderer *pRenderer = CApplication::GetRenderer();
//
//	//���_�o�b�t�@�̐���
//	pRenderer->GetDevice()->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,		// �m�ۂ���o�b�t�@�T�C�Y
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_3D,														// ���_�t�@�[�}�b�g
//		D3DPOOL_MANAGED,
//		&m_pVtxBuff,
//		NULL);
//
//	// �|���S�����̐ݒ�
//	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu
//	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����
//	m_size = D3DXVECTOR3(100.0f, 0.0f, 100.0f);		// �傫��
//	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �J���[
//	m_fRot = D3DX_PI * 2.0f;						// �p�x
//	m_fRadius = 0.0f;								// ���a
//	m_nVtx = 10;									// ���_��
//
//	// ���_���W�Ȃǂ̐ݒ�
//	SetVtx();
//
//	return S_OK;
//}
//
////=============================================================================
//// �I��
//// Author : �������l
//// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
////=============================================================================
//void CCirclePolygon3D::Uninit()
//{//���_�o�b�t�@��j��
//	if (m_pVtxBuff != nullptr)
//	{
//		m_pVtxBuff->Release();
//
//		m_pVtxBuff = nullptr;
//	}
//
//	// �I�u�W�F�N�g3D�̉��
//	Release();
//}
//
////=============================================================================
//// �X�V
//// Author : �������l
//// �T�v : 2D�X�V���s��
////=============================================================================
//void CCirclePolygon3D::Update()
//{
//
//}
//
////=============================================================================
//// �`��
//// Author : �������l
//// �T�v : 2D�`����s��
////=============================================================================
//void CCirclePolygon3D::Draw()
//{// �f�o�C�X�̎擾
//	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
//
//	// ���̎擾
//	D3DXMATRIX mtxWorld = GetMtxWorld();
//	D3DXVECTOR3 pos = GetPos();
//	D3DXVECTOR3 rot = GetRot();
//
//	// �v�Z�p�}�g���b�N�X
//	D3DXMATRIX mtxRot, mtxTrans, mtxView;
//
//	// ���[���h�}�g���b�N�X�̏�����
//	// �s�񏉊����֐�(��������[�s��]��[�P�ʍs��]�ɏ�����)
//	D3DXMatrixIdentity(&mtxWorld);
//
//	// �����̔��f
//	// �s���]�֐� (��������[���[(y)�s�b�`(x)���[��(z)]�����̉�]�s����쐬)
//	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
//
//	// �s��|���Z�֐� (������ * ��O������������Ɋi�[)
//	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
//
//	// �ʒu�𔽉f
//	// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
//	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
//	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);						// �s��|���Z�֐�
//
//	// ���[���h�}�g���b�N�X�̐ݒ�
//	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
//
//	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
//	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
//
//	// ���_�t�H�[�}�b�g
//	pDevice->SetFVF(FVF_VERTEX_3D);
//
//	// Z�e�X�g���g�p����
//	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
//	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
//
//	// Z�e�X�g�̐ݒ�
//	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
//
//	// ���e�X�g���g�p����
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
//
//	// ���e�X�g�̐ݒ�
//	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
//	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
//
//	// �|���S���`��
//	pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, m_nVtx - 2);
//
//	// ���C�g��L��	
//	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
//
//	// Z�e�X�g�̏I��
//	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
//
//	// ���e�X�g�̏I��
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
//
//	// �e�N�X�`���̉���
//	pDevice->SetTexture(0, nullptr);
//}
//
////=============================================================================
//// �ʒu�̃Z�b�^�[
//// Author : �������l
//// �T�v : �ʒu�̃����o�ϐ��Ɉ�������
////=============================================================================
//void CCirclePolygon3D::SetPos(const D3DXVECTOR3 &pos)
//{
//	// �ʒu�̐ݒ�
//	m_pos = pos;
//
//	// ���_���W�Ȃǂ̐ݒ�
//	SetVtx();
//}
//
////=============================================================================
//// �����̃Z�b�^�[
//// Author : �������l
//// �T�v : �����̃����o�ϐ��Ɉ�������
////=============================================================================
//void CCirclePolygon3D::SetRot(const D3DXVECTOR3 &rot)
//{
//	// �ʒu�̐ݒ�
//	m_rot = rot;
//
//	// ���_���W�Ȃǂ̐ݒ�
//	SetVtx();
//}
//
////=============================================================================
//// �傫���̃Z�b�^�[
//// Author : �������l
//// �T�v : �傫���̃����o�ϐ��Ɉ�������
////=============================================================================
//void CCirclePolygon3D::SetSize(const D3DXVECTOR3 & size)
//{
//	// �傫���̐ݒ�
//	m_size = size;
//
//	m_fRadius = sqrtf((size.x * size.x) + (size.z * size.z));
//
//	// ���_���W�Ȃǂ̐ݒ�
//	SetVtx();
//}
//
////=============================================================================
//// ���_���W�Ȃǂ̐ݒ�
//// Author : �������l
//// �T�v : 3D���_���W�Arhw�A���_�J���[��ݒ肷��
////=============================================================================
//void CCirclePolygon3D::SetVtx()
//{// ���_���̎擾
//	VERTEX_3D *pVtx = NULL;
//
//	// ���_�o�b�t�@�����b�N
//	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//	float addRot = m_fRot / (m_nVtx - 1);
//
//	pVtx[0].pos = m_pos;
//
//	for (int nCntVtx = 1; nCntVtx < m_nVtx; nCntVtx++)
//	{// ���_���W�̐ݒ�
//		pVtx[nCntVtx].pos.x = pVtx[0].pos.x + sinf(addRot * nCntVtx) * m_fRadius;
//		pVtx[nCntVtx].pos.y = 0.0f;
//		pVtx[nCntVtx].pos.z = pVtx[0].pos.z + cosf(addRot * nCntVtx) * m_fRadius;
//
//		// �@���̐ݒ�
//		pVtx[nCntVtx].nor = D3DXVECTOR3(pVtx[nCntVtx].pos.x, 0.0f, pVtx[nCntVtx].pos.z);
//
//		// ���_�J���[�̐ݒ�
//		pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	}
//
//	// ���_�o�b�t�@�̃A�����b�N
//	m_pVtxBuff->Unlock();
//}
