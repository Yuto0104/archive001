////=============================================================================
////
//// 3D~|SNX(object.h)
//// Author : ú±l
//// Tv : 3D~|S¶¬ðs¤
////
////=============================================================================
//
////*****************************************************************************
//// CN[h
////*****************************************************************************
//#include <assert.h>
//
//#include "circle_polygon3D.h"
//#include "renderer.h"
//#include "application.h"
//
////=============================================================================
//// CX^X¶¬
//// Author : ú±l
//// Tv : 2D3D~|Sð¶¬·é
////=============================================================================
//CCirclePolygon3D * CCirclePolygon3D::Create(void)
//{
//	// 3D~|SCX^X
//	CCirclePolygon3D *pCirclePolygon3D = nullptr;
//
//	// Ìðú
//	pCirclePolygon3D = new CCirclePolygon3D;
//
//	// ÌmÛªÅ«È©Á½
//	assert(pCirclePolygon3D != nullptr);
//
//	// lÌú»
//	pCirclePolygon3D->Init();
//
//	// CX^XðÔ·
//	return pCirclePolygon3D;
//}
//
////=============================================================================
//// RXgN^
//// Author : ú±l
//// Tv : CX^X¶¬És¤
////=============================================================================
//CCirclePolygon3D::CCirclePolygon3D()
//{
//	m_pVtxBuff = nullptr;								// ¸_obt@
//	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// Êu
//	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ü«
//	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// å«³
//	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);			// J[
//	m_fRot = 0.0f;										// px
//	m_fRadius = 0.0f;									// ¼a
//	m_nVtx = 0;											// ¸_
//}
//
////=============================================================================
//// fXgN^
//// Author : ú±l
//// Tv : CX^XI¹És¤
////=============================================================================
//CCirclePolygon3D::~CCirclePolygon3D()
//{
//
//}
//
////=============================================================================
//// ú»
//// Author : ú±l
//// Tv : ¸_obt@ð¶¬µAoÏÌúlðÝè
////=============================================================================
//HRESULT CCirclePolygon3D::Init()
//{// _[ÌQbg
//	CRenderer *pRenderer = CApplication::GetRenderer();
//
//	//¸_obt@Ì¶¬
//	pRenderer->GetDevice()->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,		// mÛ·éobt@TCY
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_3D,														// ¸_t@[}bg
//		D3DPOOL_MANAGED,
//		&m_pVtxBuff,
//		NULL);
//
//	// |SîñÌÝè
//	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// Êu
//	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ü«
//	m_size = D3DXVECTOR3(100.0f, 0.0f, 100.0f);		// å«³
//	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// J[
//	m_fRot = D3DX_PI * 2.0f;						// px
//	m_fRadius = 0.0f;								// ¼a
//	m_nVtx = 10;									// ¸_
//
//	// ¸_ÀWÈÇÌÝè
//	SetVtx();
//
//	return S_OK;
//}
//
////=============================================================================
//// I¹
//// Author : ú±l
//// Tv : eNX`Ì|C^Æ¸_obt@Ìðú
////=============================================================================
//void CCirclePolygon3D::Uninit()
//{//¸_obt@ðjü
//	if (m_pVtxBuff != nullptr)
//	{
//		m_pVtxBuff->Release();
//
//		m_pVtxBuff = nullptr;
//	}
//
//	// IuWFNg3DÌðú
//	Release();
//}
//
////=============================================================================
//// XV
//// Author : ú±l
//// Tv : 2DXVðs¤
////=============================================================================
//void CCirclePolygon3D::Update()
//{
//
//}
//
////=============================================================================
//// `æ
//// Author : ú±l
//// Tv : 2D`æðs¤
////=============================================================================
//void CCirclePolygon3D::Draw()
//{// foCXÌæ¾
//	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
//
//	// îñÌæ¾
//	D3DXMATRIX mtxWorld = GetMtxWorld();
//	D3DXVECTOR3 pos = GetPos();
//	D3DXVECTOR3 rot = GetRot();
//
//	// vZp}gbNX
//	D3DXMATRIX mtxRot, mtxTrans, mtxView;
//
//	// [h}gbNXÌú»
//	// sñú»Ö(æêøÌ[sñ]ð[PÊsñ]Éú»)
//	D3DXMatrixIdentity(&mtxWorld);
//
//	// ü«Ì½f
//	// sññ]Ö (æêøÉ[[(y)sb`(x)[(z)]ûüÌñ]sñðì¬)
//	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
//
//	// sñ|¯ZÖ (æñø * æOøðæêøÉi[)
//	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
//
//	// Êuð½f
//	// sñÚ®Ö (æêøÉX,Y,ZûüÌÚ®sñðì¬)
//	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
//	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);						// sñ|¯ZÖ
//
//	// [h}gbNXÌÝè
//	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
//
//	// ¸_obt@ðfoCXÌf[^Xg[ÉÝè
//	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
//
//	// ¸_tH[}bg
//	pDevice->SetFVF(FVF_VERTEX_3D);
//
//	// ZeXgðgp·é
//	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
//	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
//
//	// ZeXgÌÝè
//	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
//
//	// ¿eXgðgp·é
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
//
//	// ¿eXgÌÝè
//	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
//	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
//
//	// |S`æ
//	pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, m_nVtx - 2);
//
//	// CgðLø	
//	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
//
//	// ZeXgÌI¹
//	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
//
//	// ¿eXgÌI¹
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
//
//	// eNX`Ìð
//	pDevice->SetTexture(0, nullptr);
//}
//
////=============================================================================
//// ÊuÌZb^[
//// Author : ú±l
//// Tv : ÊuÌoÏÉøðãü
////=============================================================================
//void CCirclePolygon3D::SetPos(const D3DXVECTOR3 &pos)
//{
//	// ÊuÌÝè
//	m_pos = pos;
//
//	// ¸_ÀWÈÇÌÝè
//	SetVtx();
//}
//
////=============================================================================
//// ü«ÌZb^[
//// Author : ú±l
//// Tv : ü«ÌoÏÉøðãü
////=============================================================================
//void CCirclePolygon3D::SetRot(const D3DXVECTOR3 &rot)
//{
//	// ÊuÌÝè
//	m_rot = rot;
//
//	// ¸_ÀWÈÇÌÝè
//	SetVtx();
//}
//
////=============================================================================
//// å«³ÌZb^[
//// Author : ú±l
//// Tv : å«³ÌoÏÉøðãü
////=============================================================================
//void CCirclePolygon3D::SetSize(const D3DXVECTOR3 & size)
//{
//	// å«³ÌÝè
//	m_size = size;
//
//	m_fRadius = sqrtf((size.x * size.x) + (size.z * size.z));
//
//	// ¸_ÀWÈÇÌÝè
//	SetVtx();
//}
//
////=============================================================================
//// ¸_ÀWÈÇÌÝè
//// Author : ú±l
//// Tv : 3D¸_ÀWArhwA¸_J[ðÝè·é
////=============================================================================
//void CCirclePolygon3D::SetVtx()
//{// ¸_îñÌæ¾
//	VERTEX_3D *pVtx = NULL;
//
//	// ¸_obt@ðbN
//	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//	float addRot = m_fRot / (m_nVtx - 1);
//
//	pVtx[0].pos = m_pos;
//
//	for (int nCntVtx = 1; nCntVtx < m_nVtx; nCntVtx++)
//	{// ¸_ÀWÌÝè
//		pVtx[nCntVtx].pos.x = pVtx[0].pos.x + sinf(addRot * nCntVtx) * m_fRadius;
//		pVtx[nCntVtx].pos.y = 0.0f;
//		pVtx[nCntVtx].pos.z = pVtx[0].pos.z + cosf(addRot * nCntVtx) * m_fRadius;
//
//		// @üÌÝè
//		pVtx[nCntVtx].nor = D3DXVECTOR3(pVtx[nCntVtx].pos.x, 0.0f, pVtx[nCntVtx].pos.z);
//
//		// ¸_J[ÌÝè
//		pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	}
//
//	// ¸_obt@ÌAbN
//	m_pVtxBuff->Unlock();
//}
