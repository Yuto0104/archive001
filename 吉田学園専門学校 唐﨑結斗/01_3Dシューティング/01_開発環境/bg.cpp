//=============================================================================
//
// wiNX(object.h)
// Author : ϊ±l
// Tv : wiΆ¬πs€
//
//=============================================================================

//*****************************************************************************
// CN[h
//*****************************************************************************
#include <assert.h>

#include "bg.h"
#include "renderer.h"
#include "application.h"

//=============================================================================
// CX^XΆ¬
// Author : ϊ±l
// Tv : 3DfπΆ¬·ι
//=============================================================================
CBG * CBG::Create(void)
{
	// IuWFNgCX^X
	CBG *pBG = nullptr;

	// Μπϊ
	pBG = new CBG;

	// ΜmΫͺΕ«Θ©Α½
	assert(pBG != nullptr);

	// lΜϊ»
	pBG->Init();

	// CX^XπΤ·
	return pBG;
}

//=============================================================================
// RXgN^
// Author : ϊ±l
// Tv : CX^XΆ¬Ιs€
//=============================================================================
CBG::CBG(int nPriority/* = PRIORITY_LEVEL0*/) : CObject(nPriority)
{
	m_pVtxBuff = nullptr;								// Έ_obt@
	m_col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);				// J[
	m_nNumTex = -1;										// eNX`ΜνΚ
}

//=============================================================================
// fXgN^
// Author : ϊ±l
// Tv : CX^XIΉΙs€
//=============================================================================
CBG::~CBG()
{

}

//=============================================================================
// ϊ»
// Author : ϊ±l
// Tv : Έ_obt@πΆ¬΅AoΟΜϊlπέθ
//=============================================================================
HRESULT CBG::Init()
{// _[ΜQbg
	CRenderer *pRenderer = CApplication::GetRenderer();

	//Έ_obt@ΜΆ¬
	pRenderer->GetDevice()->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,		// mΫ·ιobt@TCY
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,														// Έ_t@[}bg
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// |SξρΜέθ
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// J[
	m_nNumTex = 9;									// eNX`^Cv

	// Έ_ΐWΜέθ
	SetVtx();

	// Έ_J[Μέθ
	SetCol(m_col);

	// eNX`ΐWΜέθ
	SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// IΉ
// Author : ϊ±l
// Tv : eNX`Μ|C^ΖΈ_obt@Μπϊ
//=============================================================================
void CBG::Uninit()
{
	//Έ_obt@πjό
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();

		m_pVtxBuff = nullptr;
	}

	// wi3DΜπϊ
	Release();
}

//=============================================================================
// XV
// Author : ϊ±l
// Tv : 2DXVπs€
//=============================================================================
void CBG::Update()
{

}

//=============================================================================
// `ζ
// Author : ϊ±l
// Tv : 2D`ζπs€
//=============================================================================
void CBG::Draw()
{// _[ΜQbg
	CRenderer *pRenderer = CApplication::GetRenderer();

	// eNX`|C^ΜζΎ
	CTexture *pTexture = CApplication::GetTexture();

	//eNX`Μέθ
	pRenderer->GetDevice()->SetTexture(0, nullptr);

	//eNX`Μέθ
	pRenderer->GetDevice()->SetTexture(0, pTexture->GetTexture(m_nNumTex));

	//Έ_obt@πf[^Xg[Ιέθ
	pRenderer->GetDevice()->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// Έ_tH[}bgΜέθ
	pRenderer->GetDevice()->SetFVF(FVF_VERTEX_2D);

	//|S`ζ
	pRenderer->GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//eNX`Μέθ
	pRenderer->GetDevice()->SetTexture(0, nullptr);
}

//=============================================================================
// Έ_J[Μέθ
// Author : ϊ±l
// Tv : 2D|SΜΈ_J[πέθ·ι
//=============================================================================
void CBG::SetCol(const D3DXCOLOR color)
{
	// J[Μέθ
	m_col = color;

	//Έ_ξρΦΜ|C^πΆ¬
	VERTEX_2D *pVtx;

	//Έ_obt@πbN΅AΈ_ξρΦΜ|C^πζΎ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// Έ_J[Μέθ
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//Έ_obt@πAbN
	m_pVtxBuff->Unlock();
}

//=============================================================================
// Έ_ΐWΘΗΜέθ
// Author : ϊ±l
// Tv : 2D|SΜΈ_ΐWArhwAΈ_J[πέθ·ι
//=============================================================================
void CBG::SetVtx()
{
	//Έ_ξρΦΜ|C^πΆ¬
	VERTEX_2D *pVtx;

	//Έ_obt@πbN΅AΈ_ξρΦΜ|C^πζΎ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// Έ_ξρπέθ
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, (float)CRenderer::SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT, 0.0f);

	// rhwΜέθ
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//Έ_obt@πAbN
	m_pVtxBuff->Unlock();
}

//=============================================================================
// eNX`ΐWΜέθ
// Author : ϊ±l
// Tv : 2DIuWFNgΜeNX`ΐWπέθ·ι
//=============================================================================
void CBG::SetTex(const D3DXVECTOR2 &minTex, const D3DXVECTOR2 &maxTex)
{
	//Έ_ξρΦΜ|C^πΆ¬
	VERTEX_2D *pVtx;

	//Έ_obt@πbN΅AΈ_ξρΦΜ|C^πζΎ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// eNX`ΐWΜέθ
	pVtx[0].tex = D3DXVECTOR2(minTex.x, minTex.y);
	pVtx[1].tex = D3DXVECTOR2(maxTex.x, minTex.y);
	pVtx[2].tex = D3DXVECTOR2(minTex.x, maxTex.y);
	pVtx[3].tex = D3DXVECTOR2(maxTex.x, maxTex.y);

	//Έ_obt@πAbN
	m_pVtxBuff->Unlock();
}