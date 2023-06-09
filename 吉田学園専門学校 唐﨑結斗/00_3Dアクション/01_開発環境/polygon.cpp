//**************************************************************************************************
//
// |S`æ(polygon.cpp)
// AutherFú±l
//
//**************************************************************************************************

//***************************************************************************
// CN[h
//***************************************************************************
#include "main.h"
#include "polygon.h"
#include"file.h"

//***************************************************************************
// }Nè`
//***************************************************************************
#define MAX_POLYGON_VERTEX		(4)				// |SÌ¸_
#define MAX_POLYGON_SIZE		(200.0f)		// |STCY

//***************************************************************************
// O[oÏ
//***************************************************************************
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffPolygon = NULL;		// ¸_obt@ÖÌ|C^
LPDIRECT3DTEXTURE9			g_pTexturePolygon = NULL;		// eNX`ÖÌ|C^
POLYGON						g_polygon;						// |SîñÌæ¾

//---------------------------------------------------------------------------
// |Sú»
//---------------------------------------------------------------------------
void InitPolygon(void)
{
	// t@CÏÌé¾Æãü
	char aFile[128] = FILE_TEXTURE_DATA;
	strcat(aFile, "field000.jpg");

	// foCXÌæ¾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//¸_obt@Ì¶¬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_POLYGON_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	// ¸_îñÌæ¾
	VERTEX_3D *pVtx = NULL;

	// ¸_obt@ðbN
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	// |SÉ£èt¯éeNX`ÌÇÝÝ
	D3DXCreateTextureFromFile(pDevice, aFile, &g_pTexturePolygon);

	// ¸_ÀW
	pVtx[0].pos = D3DXVECTOR3(-MAX_POLYGON_SIZE, 0.0f, MAX_POLYGON_SIZE);
	pVtx[1].pos = D3DXVECTOR3(MAX_POLYGON_SIZE, 0.0f, MAX_POLYGON_SIZE);
	pVtx[2].pos = D3DXVECTOR3(-MAX_POLYGON_SIZE, 0.0f, -MAX_POLYGON_SIZE);
	pVtx[3].pos = D3DXVECTOR3(MAX_POLYGON_SIZE, 0.0f, -MAX_POLYGON_SIZE);

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

	// ¸_obt@ÌAbN
	g_pVtxBuffPolygon->Unlock();
}

//---------------------------------------------------------------------------
// |SI¹
//---------------------------------------------------------------------------
void UninitPolygon(void)
{
	//eNX`Ìjü	  
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon->Release();

		g_pTexturePolygon = NULL;
	}

	// ¸_obt@Ìjü
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}

//---------------------------------------------------------------------------
// |SXV
//---------------------------------------------------------------------------
void UpdatePolygon(void)
{

}

//---------------------------------------------------------------------------
// |S`æ
//---------------------------------------------------------------------------
void DrawPolygon(void)
{
	// foCXÌæ¾
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// vZp}gbNX

	// [h}gbNXÌú»
	// sñú»Ö(æêøÌ[sñ]ð[PÊsñ]Éú»)
	D3DXMatrixIdentity(&g_polygon.mtxWorld);

	// ü«Ì½f
	// sññ]Ö (æêøÉ[[(y)sb`(x)[(z)]ûüÌñ]sñðì¬)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_polygon.rot.y, g_polygon.rot.x, g_polygon.rot.z);

	// sñ|¯ZÖ (æñø * æOøðæêøÉi[)
	D3DXMatrixMultiply(&g_polygon.mtxWorld, &g_polygon.mtxWorld, &mtxRot);

	// Êuð½f
	// sñÚ®Ö (æêøÉX,Y,ZûüÌÚ®sñðì¬)
	D3DXMatrixTranslation(&mtxTrans, g_polygon.pos.x, g_polygon.pos.y, g_polygon.pos.z);
	D3DXMatrixMultiply(&g_polygon.mtxWorld, &g_polygon.mtxWorld, &mtxTrans);						// sñ|¯ZÖ

	// [h}gbNXÌÝè
	pDevice->SetTransform(D3DTS_WORLD, &g_polygon.mtxWorld);

	// ¸_obt@ðfoCXÌf[^Xg[ÉÝè
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	// ¸_tH[}bg
	pDevice->SetFVF(FVF_VERTEX_3D);

	//eNX`ÌÝè
	pDevice->SetTexture(0, g_pTexturePolygon);

	// |S`æ
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// eNX`Ìð
	pDevice->SetTexture(0, NULL);
}