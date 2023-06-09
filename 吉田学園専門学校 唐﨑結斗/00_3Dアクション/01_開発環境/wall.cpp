//**************************************************************************************************
//
// Ç`æ(wall.cpp)
// AutherFú±l
//
//**************************************************************************************************

//***************************************************************************
// CN[h
//***************************************************************************
#include "main.h"
#include "wall.h"
#include"file.h"
#include"model.h"
#include"billboard.h"
#include"shadow.h"
#include"effect.h"
#include "calculation.h"

//***************************************************************************
// }Nè`
//***************************************************************************
#define MAX_WALL_VERTEX			(4)					// ÇÌ¸_
#define MAX_WALL				(128)				// ÇÌÅå
#define MAX_WALL_WIDH			(200.0f)			// ÇÌ
#define MAX_WALL_HEIGHT			(100.0f)			// ÇÌ³

//***************************************************************************
// O[oÏ
//***************************************************************************
static LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffWall = NULL;		// ¸_obt@ÖÌ|C^
static LPDIRECT3DTEXTURE9			g_pTextureWall = NULL;		// eNX`ÖÌ|C^
static Wall							g_Wall[MAX_WALL];			// ÇîñÌæ¾

//---------------------------------------------------------------------------
// Çú»
//---------------------------------------------------------------------------
void InitWall(void)
{
	// t@CÏÌé¾Æãü
	char aFile[128] = FILE_TEXTURE_DATA;
	strcat(aFile, "wall000.jpg");

	// foCXÌæ¾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//¸_obt@Ì¶¬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_WALL_VERTEX * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	// ÇÉ£èt¯éeNX`ÌÇÝÝ
	D3DXCreateTextureFromFile(pDevice, aFile, &g_pTextureWall);

	// ¸_îñÌæ¾
	VERTEX_3D *pVtx = NULL;

	// ¸_obt@ðbN
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		// ÇîñÌú»
		g_Wall[nCntWall].pos = {};											// Êu
		g_Wall[nCntWall].rot = {};											// ü«
		g_Wall[nCntWall].mtxWorld = {};										// [h}gbNX
		g_Wall[nCntWall].col = {};											// J[
		g_Wall[nCntWall].bUse = false;										// gpóµ

		// ¸_ÀW
		pVtx[0].pos = D3DXVECTOR3(-MAX_WALL_WIDH, MAX_WALL_HEIGHT,0.0f);
		pVtx[1].pos = D3DXVECTOR3(MAX_WALL_WIDH, MAX_WALL_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-MAX_WALL_WIDH, -MAX_WALL_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(MAX_WALL_WIDH, -MAX_WALL_HEIGHT, 0.0f);

		// e¸_Ì@üÌÝè(*xNgÌå«³Í1É·éKvª é)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		// ¸_J[ÌÝè
		pVtx[0].col = g_Wall[nCntWall].col;
		pVtx[1].col = g_Wall[nCntWall].col;
		pVtx[2].col = g_Wall[nCntWall].col;
		pVtx[3].col = g_Wall[nCntWall].col;

		// eNX`ÀW
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		//¸_f[^Ì|C^ð4Âªißé
	}

	// ¸_obt@ÌAbN
	g_pVtxBuffWall->Unlock();
}

//---------------------------------------------------------------------------
// ÇI¹
//---------------------------------------------------------------------------
void UninitWall(void)
{
	//eNX`Ìjü	  
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();

		g_pTextureWall = NULL;
	}

	// ¸_obt@Ìjü
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//---------------------------------------------------------------------------
// ÇXV
//---------------------------------------------------------------------------
void UpdateWall(void)
{
	
}

//---------------------------------------------------------------------------
// Ç`æ
//---------------------------------------------------------------------------
void DrawWall(void)
{
	// foCXÌæ¾
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// vZp}gbNX

	// eNX`ÌÝè
	pDevice->SetTexture(0, g_pTextureWall);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == true)
		{// Çªgp³êÄ¢éÆ«
			// [h}gbNXÌú»
			// sñú»Ö(æêøÌ[sñ]ð[PÊsñ]Éú»)
			D3DXMatrixIdentity(&g_Wall[nCntWall].mtxWorld);

			// ü«Ì½f
			// sññ]Ö (æêøÉ[[(y)sb`(x)[(z)]ûüÌñ]sñðì¬)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[nCntWall].rot.y, g_Wall[nCntWall].rot.x, g_Wall[nCntWall].rot.z);

			// sñ|¯ZÖ (æñø * æOøðæêøÉi[)
			D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorld, &g_Wall[nCntWall].mtxWorld, &mtxRot);

			// Êuð½f
			// sñÚ®Ö (æêøÉX,Y,ZûüÌÚ®sñðì¬)
			D3DXMatrixTranslation(&mtxTrans, g_Wall[nCntWall].pos.x, g_Wall[nCntWall].pos.y, g_Wall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorld, &g_Wall[nCntWall].mtxWorld, &mtxTrans);		// sñ|¯ZÖ

			// [h}gbNXÌÝè
			pDevice->SetTransform(D3DTS_WORLD, &g_Wall[nCntWall].mtxWorld);

			// ¸_obt@ðfoCXÌf[^Xg[ÉÝè
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			// ¸_tH[}bg
			pDevice->SetFVF(FVF_VERTEX_3D);

			// Ç`æ
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, MAX_WALL_VERTEX * nCntWall, 2);
		}
	}

	// eNX`Ìð
	pDevice->SetTexture(0, NULL);
}

//---------------------------------------------------------------------------
// ÇÝè
//---------------------------------------------------------------------------
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	// Ïé¾
	int nCntWall;

	// ¸_îñÌæ¾
	VERTEX_3D *pVtx = NULL;

	// ¸_obt@ðbN
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == false)
		{
			// ÇîñÌÝè
			g_Wall[nCntWall].pos = pos;																		// Êu
			g_Wall[nCntWall].rot = D3DXVECTOR3((D3DX_PI * rot.x),(D3DX_PI * rot.y),(D3DX_PI * rot.z));		// ü«
			g_Wall[nCntWall].mtxWorld = {};																	// [h}gbNX
			g_Wall[nCntWall].col = col;																		// J[
			g_Wall[nCntWall].bUse = true;																	// gpóµ

			// ¸_J[ÌÝè
			pVtx[0].col = g_Wall[nCntWall].col;
			pVtx[1].col = g_Wall[nCntWall].col;
			pVtx[2].col = g_Wall[nCntWall].col;
			pVtx[3].col = g_Wall[nCntWall].col;
			break;
		}

		pVtx += 4;		//¸_f[^Ì|C^ð4Âªißé
	}

	// ¸_obt@ÌAbN
	g_pVtxBuffWall->Unlock();
}

//---------------------------------------------------------------------------
// ÇÆr{[hÌ½è»è
//---------------------------------------------------------------------------
bool	CollisionWallBillBoard(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, int nIdx)
{
	// Ïé¾
	int		nCntWall;
	bool	bIsLanding = false;

	// ¸_îñÌæ¾
	VERTEX_3D *pVtx = NULL;

	// ¸_obt@ðbN
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == true)
		{
			// Ïé¾
			D3DXVECTOR3 aVtx0 = WorldCastVtx(pVtx[0].pos, g_Wall[nCntWall].pos, g_Wall[nCntWall].rot);
			D3DXVECTOR3 aVtx1 = WorldCastVtx(pVtx[1].pos, g_Wall[nCntWall].pos, g_Wall[nCntWall].rot);
			D3DXVECTOR3 aVecLine = aVtx1 - aVtx0;															// ÇÌxNg
			D3DXVECTOR3 aVecPos = D3DXVECTOR3(pos->x - aVtx0.x, pos->y - aVtx0.y, pos->z - aVtx0.z);		// ÊuÌxNg
			// OÏðgpµ½½è»è
			if (0.0f > (aVecLine.z * aVecPos.x) - (aVecLine.x * aVecPos.z))
			{
				/*bIsLanding = true;*/
				Billboard *pBillboard = GetBillboard();
				pBillboard += nIdx;

				D3DXVECTOR3 VecC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				D3DXVECTOR3 aVtx0 = WorldCastVtx(pVtx[0].pos, g_Wall[nCntWall].pos, g_Wall[nCntWall].rot);
				D3DXVECTOR3 aVtx1 = WorldCastVtx(pVtx[1].pos, g_Wall[nCntWall].pos, g_Wall[nCntWall].rot);
				D3DXVECTOR3 aVtx2 = WorldCastVtx(pVtx[2].pos, g_Wall[nCntWall].pos, g_Wall[nCntWall].rot);
				D3DXVECTOR3 aVecA = aVtx1 - aVtx0;		// ÇÌxNg
				D3DXVECTOR3 aVecB = aVtx2 - aVtx0;		// ÇÌxNg

				// OÏðgpµÄ@üÌZo
				D3DXVec3Cross(&VecC, &aVecA, &aVecB);
				D3DXVec3Normalize(&VecC, &VecC);

				VecC *= (-pBillboard->move.x * VecC.x) + (-pBillboard->move.z * VecC.z);

				// ½Ë
				pBillboard->move += VecC * 2.0f;

				break;
			}
		}
	}

	return bIsLanding;

	// ¸_obt@ÌAbN
	g_pVtxBuffWall->Unlock();
}