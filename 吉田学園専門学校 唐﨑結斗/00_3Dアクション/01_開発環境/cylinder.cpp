//**************************************************************************************************
//
// ~`æ(cylinder.cpp)
// AutherFú±l
//
//**************************************************************************************************

//***************************************************************************
// CN[h
//***************************************************************************
#include "main.h"
#include "cylinder.h"
#include"file.h"

//***************************************************************************
// }Nè`
//***************************************************************************
#define CYLINDER_X_BLOCK2			(10)						// XûüÌubN
#define CYLINDER_Z_BLOCK2			(3)						// ZûüÌubN

// ubN + 1
#define MESHBLOCK_X_ADD_ONE		(CYLINDER_X_BLOCK2 + 1)
#define MESHBLOCK_Z_ADD_ONE		(CYLINDER_Z_BLOCK2 + 1)

// 1ñ¸_
#define CYLINDER_RHINE_VTX_ONE		(CYLINDER_X_BLOCK2 * 2 + 2)

// ~Ì¸_
#define MAX_CYLINDER_VERTEX			(MESHBLOCK_X_ADD_ONE * MESHBLOCK_Z_ADD_ONE)		

// ~Ì|S
#define MAX_CYLINDER_POLYGON		((CYLINDER_X_BLOCK2 * CYLINDER_Z_BLOCK2 * 2) + (((CYLINDER_Z_BLOCK2 - 1) * 2) * 2))

// ~ÌCfbNX
#define MAX_CYLINDER_INDEX			((CYLINDER_RHINE_VTX_ONE * CYLINDER_Z_BLOCK2) + ((CYLINDER_Z_BLOCK2 - 1) * 2))	

// ~TCY
#define MAX_CYLINDER_SIZE			(10.0f)

// ~Ì¼aÌ·³
#define CYLINDER_RADIUS				(50.0f)

//***************************************************************************
// O[oÏ
//***************************************************************************
static LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffCylinder = NULL;		// ¸_obt@ÖÌ|C^
static LPDIRECT3DTEXTURE9			g_pTextureCylinder = NULL;		// eNX`ÖÌ|C^
static LPDIRECT3DINDEXBUFFER9		g_pIdzBuffCylinder = NULL;		// CfbNXobt@ÖÌ|C^
static Cylinder						g_Cylinder;						// ~îñÌæ¾

//---------------------------------------------------------------------------
// ~ú»
//---------------------------------------------------------------------------
void InitCylinder(void)
{
	g_Cylinder.pos = D3DXVECTOR3(0.0f, 0.0f, 100.0f);

	// t@CÏÌé¾Æãü
	char aFile[128] = FILE_TEXTURE_DATA;
	strcat(aFile, "sky001.jpg");

	// foCXÌæ¾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ~É£èt¯éeNX`ÌÇÝÝ
	D3DXCreateTextureFromFile(pDevice, aFile, &g_pTextureCylinder);

	// ¸_obt@Ì¶¬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_CYLINDER_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCylinder,
		NULL);

	// CfbNXobt@Ì¶¬
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_CYLINDER_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdzBuffCylinder,
		NULL);

	// ¸_îñÌæ¾
	VERTEX_3D *pVtx = NULL;

	// ¸_obt@ðbN
	g_pVtxBuffCylinder->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntV = 0; nCntV < CYLINDER_Z_BLOCK2 + 1; nCntV++)
	{
		for (int nCntH = 0; nCntH < CYLINDER_X_BLOCK2 + 1; nCntH++)
		{// Ïé¾
			float fRot = ((D3DX_PI * 2.0f) / CYLINDER_X_BLOCK2) * nCntH;		// pxÌÝè

			// ¸_ÀWÌÝè
			pVtx[0].pos.x = sinf(fRot) * CYLINDER_RADIUS;
			pVtx[0].pos.z = cosf(fRot) * CYLINDER_RADIUS;
			pVtx[0].pos.y = MAX_CYLINDER_SIZE * nCntV;

			// e¸_Ì@üÌÝè(*xNgÌå«³Í1É·éKvª é)
			pVtx[0].nor.x = pVtx[0].pos.x;
			pVtx[0].nor.z = pVtx[0].pos.z;
			pVtx[0].nor.y = 0.0f;
			D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);

			// ¸_J[ÌÝè
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// eNX`ÀWÌÝè
			pVtx[0].tex = D3DXVECTOR2(1.0f / CYLINDER_X_BLOCK2 * nCntH, 1.0f / CYLINDER_X_BLOCK2 * nCntV);

			pVtx++;
		}
	}

	// CfbNXobt@ðbN
	WORD *pIdx;
	g_pIdzBuffCylinder->Lock(0, 0, (void**)&pIdx, 0);

	// CfbNXÌÝè
	for (int nCntZ = 0; nCntZ < CYLINDER_Z_BLOCK2; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESHBLOCK_X_ADD_ONE; nCntX++)
		{// CfbNXÌÝè
			pIdx[0] = MESHBLOCK_X_ADD_ONE + nCntX + nCntZ * MESHBLOCK_X_ADD_ONE;
			pIdx[1] = MESHBLOCK_X_ADD_ONE + nCntX + nCntZ * MESHBLOCK_X_ADD_ONE - MESHBLOCK_X_ADD_ONE;

			pIdx += 2;
		}

		if (nCntZ != CYLINDER_Z_BLOCK2)
		{// ÅåÈºÌ
		 // kÞ|SCfbNXÌÝè
			pIdx[0] = MESHBLOCK_X_ADD_ONE * nCntZ + CYLINDER_X_BLOCK2;
			pIdx[1] = MESHBLOCK_X_ADD_ONE * (nCntZ + 2);

			pIdx += 2;
		}
	}

	// ¸_obt@ÌAbN
	g_pVtxBuffCylinder->Unlock();

	// ¸_obt@ÌAbN
	g_pIdzBuffCylinder->Unlock();
}

//---------------------------------------------------------------------------
// ~I¹
//---------------------------------------------------------------------------
void UninitCylinder(void)
{
	// eNX`Ìjü	  
	if (g_pTextureCylinder != NULL)
	{
		g_pTextureCylinder->Release();
		g_pTextureCylinder = NULL;
	}

	// ¸_obt@Ìjü
	if (g_pVtxBuffCylinder != NULL)
	{
		g_pVtxBuffCylinder->Release();
		g_pVtxBuffCylinder = NULL;
	}

	// CfbNXobt@Ìjü	  
	if (g_pIdzBuffCylinder != NULL)
	{
		g_pIdzBuffCylinder->Release();
		g_pIdzBuffCylinder = NULL;
	}
}

//---------------------------------------------------------------------------
// ~XV
//---------------------------------------------------------------------------
void UpdateCylinder(void)
{

}

//---------------------------------------------------------------------------
// ~`æ
//---------------------------------------------------------------------------
void DrawCylinder(void)
{
	// foCXÌæ¾
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// vZp}gbNX

	// [h}gbNXÌú»
	// sñú»Ö(æêøÌ[sñ]ð[PÊsñ]Éú»)
	D3DXMatrixIdentity(&g_Cylinder.mtxWorld);

	// ü«Ì½f
	// sññ]Ö (æêøÉ[[(y)sb`(x)[(z)]ûüÌñ]sñðì¬)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Cylinder.rot.y, g_Cylinder.rot.x, g_Cylinder.rot.z);

	// sñ|¯ZÖ (æñø * æOøðæêøÉi[)
	D3DXMatrixMultiply(&g_Cylinder.mtxWorld, &g_Cylinder.mtxWorld, &mtxRot);

	// Êuð½f
	// sñÚ®Ö (æêøÉX,Y,ZûüÌÚ®sñðì¬)
	D3DXMatrixTranslation(&mtxTrans, g_Cylinder.pos.x, g_Cylinder.pos.y, g_Cylinder.pos.z);
	D3DXMatrixMultiply(&g_Cylinder.mtxWorld, &g_Cylinder.mtxWorld, &mtxTrans);						// sñ|¯ZÖ

	// [h}gbNXÌÝè
	pDevice->SetTransform(D3DTS_WORLD, &g_Cylinder.mtxWorld);

	// ¸_obt@ðfoCXÌf[^Xg[ÉÝè
	pDevice->SetStreamSource(0, g_pVtxBuffCylinder, 0, sizeof(VERTEX_3D));

	// CfbNXobt@ðf[^Xg[ÉÝè
	pDevice->SetIndices(g_pIdzBuffCylinder);

	// ¸_tH[}bg
	pDevice->SetFVF(FVF_VERTEX_3D);

	//eNX`ÌÝè
	pDevice->SetTexture(0, g_pTextureCylinder);

	// ~`æ
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_CYLINDER_VERTEX, 0, MAX_CYLINDER_POLYGON);

	// eNX`Ìð
	pDevice->SetTexture(0, NULL);
}