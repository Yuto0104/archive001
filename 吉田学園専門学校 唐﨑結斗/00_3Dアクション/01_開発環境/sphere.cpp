//**************************************************************************************************
//
// `æ(sphere.cpp)
// AutherFú±l
//
//**************************************************************************************************

//***************************************************************************
// CN[h
//***************************************************************************
#include "main.h"
#include "sphere.h"
#include"file.h"

//***************************************************************************
// }Nè`
//***************************************************************************
#define SPHERE_X_BLOCK2				(100)						// XûüÌubN
#define SPHERE_Z_BLOCK2				(10)						// ZûüÌubN

// ubN + 1
#define MESHBLOCK_X_ADD_ONE			(SPHERE_X_BLOCK2 + 1)
#define MESHBLOCK_Z_ADD_ONE			(SPHERE_Z_BLOCK2 + 1)

// 1ñ¸_
#define SPHERE_RHINE_VTX_ONE		(SPHERE_X_BLOCK2 * 2 + 2)

// Ì¸_
#define MAX_SPHERE_VERTEX			(MESHBLOCK_X_ADD_ONE * MESHBLOCK_Z_ADD_ONE)		

// Ì|S
#define MAX_SPHERE_POLYGON			((SPHERE_X_BLOCK2 * SPHERE_Z_BLOCK2 * 2) + (((SPHERE_Z_BLOCK2 - 1) * 2) * 2))

// ÌCfbNX
#define MAX_SPHERE_INDEX			((SPHERE_RHINE_VTX_ONE * SPHERE_Z_BLOCK2) + ((SPHERE_Z_BLOCK2 - 1) * 2))	

// TCY
#define MAX_SPHERE_SIZE				(10.0f)

// Ì¼aÌ·³
#define SPHERE_RADIUS				(50.0f)


//***************************************************************************
// O[oÏ
//***************************************************************************
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffSphere = NULL;		// ¸_obt@ÖÌ|C^
LPDIRECT3DTEXTURE9			g_pTextureSphere = NULL;		// eNX`ÖÌ|C^
LPDIRECT3DINDEXBUFFER9		g_pIdzBuffSphere = NULL;		// CfbNXobt@ÖÌ|C^
Sphere						g_Sphere;						// îñÌæ¾

//---------------------------------------------------------------------------
// ú»
//---------------------------------------------------------------------------
void InitSphere(void)
{
	// t@CÏÌé¾Æãü
	char aFile[128] = FILE_TEXTURE_DATA;
	strcat(aFile, "sky001.jpg");

	// foCXÌæ¾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// É£èt¯éeNX`ÌÇÝÝ
	D3DXCreateTextureFromFile(pDevice, aFile, &g_pTextureSphere);

	// ¸_obt@Ì¶¬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_SPHERE_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSphere,
		NULL);

	// CfbNXobt@Ì¶¬
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_SPHERE_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdzBuffSphere,
		NULL);

	// ¸_îñÌæ¾
	VERTEX_3D *pVtx = NULL;

	// ¸_obt@ðbN
	g_pVtxBuffSphere->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntV = 0; nCntV < SPHERE_Z_BLOCK2 + 1; nCntV++)
	{
		for (int nCntH = 0; nCntH < SPHERE_X_BLOCK2 + 1; nCntH++)
		{// Ïé¾
			float fRot = ((-D3DX_PI * 2.0f) / SPHERE_X_BLOCK2) * nCntH;			// Y²ÌpxÌÝè
			float fHalfRot = (-D3DX_PI / SPHERE_Z_BLOCK2) * nCntV;				// ¼ÌZ²ÌpxÌ¼ª

			// ³Æ¼aÌÝè
			D3DXVECTOR2 radius = D3DXVECTOR2(sinf(fHalfRot) * SPHERE_RADIUS, cosf(fHalfRot) * SPHERE_RADIUS);

			//// ¸_ÀWÌÝè
			//pVtx[0].pos.x = sinf(fRot) * radius.y;
			//pVtx[0].pos.z = cosf(fRot) * radius.y;
			//pVtx[0].pos.y = radius.x;

			// _ÌZo
			pVtx[0].pos.z = sinf(fHalfRot) * cosf(fRot) * SPHERE_RADIUS;
			pVtx[0].pos.x = sinf(fHalfRot) * sinf(fRot) * SPHERE_RADIUS;
			pVtx[0].pos.y = cosf(fHalfRot) * SPHERE_RADIUS;

			// e¸_Ì@üÌÝè(*xNgÌå«³Í1É·éKvª é)
			pVtx[0].nor.x = pVtx[0].pos.x;
			pVtx[0].nor.z = pVtx[0].pos.z;
			pVtx[0].nor.y = 0.0f;
			D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);

			// ¸_J[ÌÝè
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// eNX`ÀWÌÝè
			pVtx[0].tex = D3DXVECTOR2(1.0f / SPHERE_X_BLOCK2 * nCntH, 1.0f / SPHERE_Z_BLOCK2 * nCntV);

			pVtx++;
		}
	}

	// CfbNXobt@ðbN
	WORD *pIdx;
	g_pIdzBuffSphere->Lock(0, 0, (void**)&pIdx, 0);

	// CfbNXÌÝè
	for (int nCntZ = 0; nCntZ < SPHERE_Z_BLOCK2; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESHBLOCK_X_ADD_ONE; nCntX++)
		{// CfbNXÌÝè
			pIdx[0] = MESHBLOCK_X_ADD_ONE + nCntX + nCntZ * MESHBLOCK_X_ADD_ONE;
			pIdx[1] = MESHBLOCK_X_ADD_ONE + nCntX + nCntZ * MESHBLOCK_X_ADD_ONE - MESHBLOCK_X_ADD_ONE;

			pIdx += 2;
		}

		if (nCntZ != SPHERE_Z_BLOCK2)
		{// ÅåÈºÌ
		 // kÞ|SCfbNXÌÝè
			pIdx[0] = MESHBLOCK_X_ADD_ONE * nCntZ + SPHERE_X_BLOCK2;
			pIdx[1] = MESHBLOCK_X_ADD_ONE * (nCntZ + 2);

			pIdx += 2;
		}
	}

	// ¸_obt@ÌAbN
	g_pVtxBuffSphere->Unlock();

	// ¸_obt@ÌAbN
	g_pIdzBuffSphere->Unlock();
}

//---------------------------------------------------------------------------
// I¹
//---------------------------------------------------------------------------
void UninitSphere(void)
{
	// eNX`Ìjü	  
	if (g_pTextureSphere != NULL)
	{
		g_pTextureSphere->Release();
		g_pTextureSphere = NULL;
	}

	// ¸_obt@Ìjü
	if (g_pVtxBuffSphere != NULL)
	{
		g_pVtxBuffSphere->Release();
		g_pVtxBuffSphere = NULL;
	}

	// CfbNXobt@Ìjü	  
	if (g_pIdzBuffSphere != NULL)
	{
		g_pIdzBuffSphere->Release();
		g_pIdzBuffSphere = NULL;
	}
}

//---------------------------------------------------------------------------
// XV
//---------------------------------------------------------------------------
void UpdateSphere(void)
{

}

//---------------------------------------------------------------------------
// `æ
//---------------------------------------------------------------------------
void DrawSphere(void)
{
	// foCXÌæ¾
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// vZp}gbNX

	// [h}gbNXÌú»
	// sñú»Ö(æêøÌ[sñ]ð[PÊsñ]Éú»)
	D3DXMatrixIdentity(&g_Sphere.mtxWorld);

	// ü«Ì½f
	// sññ]Ö (æêøÉ[[(y)sb`(x)[(z)]ûüÌñ]sñðì¬)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Sphere.rot.y, g_Sphere.rot.x, g_Sphere.rot.z);

	// sñ|¯ZÖ (æñø * æOøðæêøÉi[)
	D3DXMatrixMultiply(&g_Sphere.mtxWorld, &g_Sphere.mtxWorld, &mtxRot);

	// Êuð½f
	// sñÚ®Ö (æêøÉX,Y,ZûüÌÚ®sñðì¬)
	D3DXMatrixTranslation(&mtxTrans, g_Sphere.pos.x, g_Sphere.pos.y, g_Sphere.pos.z);
	D3DXMatrixMultiply(&g_Sphere.mtxWorld, &g_Sphere.mtxWorld, &mtxTrans);						// sñ|¯ZÖ

	// [h}gbNXÌÝè
	pDevice->SetTransform(D3DTS_WORLD, &g_Sphere.mtxWorld);

	// ¸_obt@ðfoCXÌf[^Xg[ÉÝè
	pDevice->SetStreamSource(0, g_pVtxBuffSphere, 0, sizeof(VERTEX_3D));

	// CfbNXobt@ðf[^Xg[ÉÝè
	pDevice->SetIndices(g_pIdzBuffSphere);

	// ¸_tH[}bg
	pDevice->SetFVF(FVF_VERTEX_3D);

	//eNX`ÌÝè
	pDevice->SetTexture(0, g_pTextureSphere);

	// `æ
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_SPHERE_VERTEX, 0, MAX_SPHERE_POLYGON);

	// eNX`Ìð
	pDevice->SetTexture(0, NULL);
}