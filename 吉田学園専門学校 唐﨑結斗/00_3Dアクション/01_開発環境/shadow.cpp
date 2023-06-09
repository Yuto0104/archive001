//**************************************************************************************************
//
// e`æ(shadow.cpp)
// AutherFú±l
//
//**************************************************************************************************

//***************************************************************************
// CN[h
//***************************************************************************
#include "main.h"
#include "shadow.h"
#include"file.h"
#include"model.h"

//***************************************************************************
// }Nè`
//***************************************************************************
#define MAX_SHADOW_VERTEX		(4)				// eÌ¸_
#define MAX_SHADOW				(12800)			// eÌÅå
#define MAX_SHADOW_SIZE			(10.0f)			// eTCY
#define ATTENUATION_SHADOW		(0.01f)			// eÌ¸W

//***************************************************************************
// O[oÏ
//***************************************************************************
static LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffShadow = NULL;		// ¸_obt@ÖÌ|C^
static LPDIRECT3DTEXTURE9			g_pTextureShadow = NULL;		// eNX`ÖÌ|C^
static Shadow						g_Shadow[MAX_SHADOW];			// eîñÌæ¾

//---------------------------------------------------------------------------
// eú»
//---------------------------------------------------------------------------
void InitShadow(void)
{
	// t@CÏÌé¾Æãü
	char aFile[128] = FILE_TEXTURE_DATA;
	strcat(aFile, "shadow000.jpg");

	// foCXÌæ¾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//¸_obt@Ì¶¬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_SHADOW_VERTEX * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	// eÉ£èt¯éeNX`ÌÇÝÝ
	D3DXCreateTextureFromFile(pDevice, aFile, &g_pTextureShadow);

	// ¸_îñÌæ¾
	VERTEX_3D *pVtx = NULL;

	// ¸_obt@ðbN
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		// eîñÌú»
		g_Shadow[nCntShadow].pos = {};						// Êu
		g_Shadow[nCntShadow].rot = {};						// ü«
		g_Shadow[nCntShadow].size = {};						// ¼a
		g_Shadow[nCntShadow].mtxWorld = {};					// [h}gbNX
		g_Shadow[nCntShadow].bUse = false;					// gpóµ

		// ¸_ÀW
		pVtx[0].pos = D3DXVECTOR3(-g_Shadow[nCntShadow].size.x, 0.0f, g_Shadow[nCntShadow].size.z);
		pVtx[1].pos = D3DXVECTOR3(g_Shadow[nCntShadow].size.x, 0.0f, g_Shadow[nCntShadow].size.z);
		pVtx[2].pos = D3DXVECTOR3(-g_Shadow[nCntShadow].size.x, 0.0f, -g_Shadow[nCntShadow].size.z);
		pVtx[3].pos = D3DXVECTOR3(g_Shadow[nCntShadow].size.x, 0.0f, -g_Shadow[nCntShadow].size.z);

		// e¸_Ì@üÌÝè(*xNgÌå«³Í1É·éKvª é)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ¸_J[ÌÝè
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// eNX`ÀW
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		//¸_f[^Ì|C^ð4Âªißé
	}

	// ¸_obt@ÌAbN
	g_pVtxBuffShadow->Unlock();
}

//---------------------------------------------------------------------------
// eI¹
//---------------------------------------------------------------------------
void UninitShadow(void)
{
	//eNX`Ìjü	  
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();

		g_pTextureShadow = NULL;
	}

	// ¸_obt@Ìjü
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//---------------------------------------------------------------------------
// eXV
//---------------------------------------------------------------------------
void UpdateShadow(void)
{

}

//---------------------------------------------------------------------------
// e`æ
//---------------------------------------------------------------------------
void DrawShadow(void)
{
	// foCXÌæ¾
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// vZp}gbNX

	// ¿ufBOð¸Z¬ÉÝè
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// eNX`ÌÝè
	pDevice->SetTexture(0, g_pTextureShadow);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == true)
		{// eªgp³êÄ¢éÆ«
			// [h}gbNXÌú»
			// sñú»Ö(æêøÌ[sñ]ð[PÊsñ]Éú»)
			D3DXMatrixIdentity(&g_Shadow[nCntShadow].mtxWorld);

			// ü«Ì½f
			// sññ]Ö (æêøÉ[[(y)sb`(x)[(z)]ûüÌñ]sñðì¬)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow[nCntShadow].rot.y, g_Shadow[nCntShadow].rot.x, g_Shadow[nCntShadow].rot.z);

			// sñ|¯ZÖ (æñø * æOøðæêøÉi[)
			D3DXMatrixMultiply(&g_Shadow[nCntShadow].mtxWorld, &g_Shadow[nCntShadow].mtxWorld, &mtxRot);

			// Êuð½f
			// sñÚ®Ö (æêøÉX,Y,ZûüÌÚ®sñðì¬)
			D3DXMatrixTranslation(&mtxTrans, g_Shadow[nCntShadow].pos.x, g_Shadow[nCntShadow].pos.y, g_Shadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_Shadow[nCntShadow].mtxWorld, &g_Shadow[nCntShadow].mtxWorld, &mtxTrans);		// sñ|¯ZÖ

			// [h}gbNXÌÝè
			pDevice->SetTransform(D3DTS_WORLD, &g_Shadow[nCntShadow].mtxWorld);

			// ¸_obt@ðfoCXÌf[^Xg[ÉÝè
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			// ¸_tH[}bg
			pDevice->SetFVF(FVF_VERTEX_3D);

			// e`æ
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, MAX_SHADOW_VERTEX * nCntShadow, 2);
		}
	}

	// eNX`Ìð
	pDevice->SetTexture(0, NULL);

	// ¿ufBOð³Éß·
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//---------------------------------------------------------------------------
// eÝè
//---------------------------------------------------------------------------
int	SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// Ïé¾
	int nCntShadow;

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == false)
		{
			// Ïé¾
			float fDiffPos = pos.y * 0.01f;

			// eîñÌÝè
			g_Shadow[nCntShadow].pos.x = pos.x;																			// Êu(x)
			g_Shadow[nCntShadow].pos.y = 0.1f;																			// Êu(y)
			g_Shadow[nCntShadow].pos.z = pos.z;																			// Êu(z)
			g_Shadow[nCntShadow].rot = rot;																				// ü«
			g_Shadow[nCntShadow].mtxWorld = {};																			// [h}gbNX
			g_Shadow[nCntShadow].size = D3DXVECTOR3(size.x + (size.x * fDiffPos),0.0f, size.z + (size.z * fDiffPos));	// å«³						// ¼a
			g_Shadow[nCntShadow].bUse = true;																			// gpóµ

			break;
		}
	}

	return nCntShadow;		// eÌÔ(index)ðÔ·
}

//---------------------------------------------------------------------------
// eÚ®
//---------------------------------------------------------------------------
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// Ïé¾
	float fDiffPos = pos.y * ATTENUATION_SHADOW;
	float fAlpha = pos.y * ATTENUATION_SHADOW;

	// eîñÌÝè
	g_Shadow[nIdxShadow].pos.x = pos.x;																			// Êu(x)
	g_Shadow[nIdxShadow].pos.y = 0.1f;																			// Êu(y)
	g_Shadow[nIdxShadow].pos.z = pos.z;																			// Êu(z)
	g_Shadow[nIdxShadow].rot.x = 0.0f;																			// ü«(x)
	g_Shadow[nIdxShadow].rot.y = rot.y;																			// ü«(y)
	g_Shadow[nIdxShadow].rot.z = 0.0f;																			// ü«(z)
	g_Shadow[nIdxShadow].size = D3DXVECTOR3(size.x + (size.x * fDiffPos), 0.0f, size.z + (size.z * fDiffPos));	// å«³	

	// ¸_îñÌæ¾
	VERTEX_3D *pVtx = NULL;

	// ¸_obt@ðbN
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdxShadow * 4;		//¸_f[^Ì|C^ð4Âªißé

	// ¸_ÀW
	pVtx[0].pos = D3DXVECTOR3(-g_Shadow[nIdxShadow].size.x, 0.0f, g_Shadow[nIdxShadow].size.z);
	pVtx[1].pos = D3DXVECTOR3(g_Shadow[nIdxShadow].size.x, 0.0f, g_Shadow[nIdxShadow].size.z);
	pVtx[2].pos = D3DXVECTOR3(-g_Shadow[nIdxShadow].size.x, 0.0f, -g_Shadow[nIdxShadow].size.z);
	pVtx[3].pos = D3DXVECTOR3(g_Shadow[nIdxShadow].size.x, 0.0f, -g_Shadow[nIdxShadow].size.z);

	// e¸_Ì@üÌÝè(*xNgÌå«³Í1É·éKvª é)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ¸_J[ÌÝè
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (1.0f * fAlpha));
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (1.0f * fAlpha));
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (1.0f * fAlpha));
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (1.0f * fAlpha));

	// eNX`ÀW
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ¸_obt@ÌAbN
	g_pVtxBuffShadow->Unlock();
}

//---------------------------------------------------------------------------
// eí
//---------------------------------------------------------------------------
void DeleteShadow(int nIdxShadow)
{
	// eîñÌú»
	g_Shadow[nIdxShadow].pos = {};						// Êu
	g_Shadow[nIdxShadow].rot = {};						// ü«
	g_Shadow[nIdxShadow].size = {};						// ¼a
	g_Shadow[nIdxShadow].mtxWorld = {};					// [h}gbNX
	g_Shadow[nIdxShadow].bUse = false;					// gpóµ
}