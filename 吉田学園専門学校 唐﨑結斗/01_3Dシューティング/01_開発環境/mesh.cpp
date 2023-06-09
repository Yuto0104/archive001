//=============================================================================
//
// メッシュクラス(mesh.cpp)
// Author : 唐�ｱ結斗
// 概要 : メッシュ生成を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "mesh.h"
#include "renderer.h"
#include "application.h"

//=============================================================================
// インスタンス生成
// Author : 唐�ｱ結斗
// 概要 : 2Dメッシュを生成する
//=============================================================================
CMesh3D * CMesh3D::Create(void)
{
	// メッシュインスタンス
	CMesh3D *pMesh3D = nullptr;

	// メモリの解放
	pMesh3D = new CMesh3D;

	// メモリの確保ができなかった
	assert(pMesh3D != nullptr);

	// 数値の初期化
	pMesh3D->Init();

	// インスタンスを返す
	return pMesh3D;
}

//=============================================================================
// コンストラクタ
// Author : 唐�ｱ結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CMesh3D::CMesh3D()
{
	m_pVtxBuff = nullptr;								// 頂点バッファ
	m_pIdxBuff = nullptr;								// インデックスバッファへのポインタ
	m_mtxWorld = {};									// ワールドマトリックス
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);				// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 向き
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 大きさ
	m_blockSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ブロックサイズ
	m_tex = D3DXVECTOR2(1.0f, 1.0f);					// テクスチャ座標の基準値
	m_addTex = D3DXVECTOR2(0.0f, 0.0f);					// テクスチャ座標の加算値
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			// カラー
	m_nNumTex = -1;										// テクスチャタイプ
	m_block = DOUBLE_INT(0, 0);							// ブロック数
	m_line = DOUBLE_INT(0, 0);							// 列数
	m_fAngle = 0.0f;									// 対角線の角度
	m_fLength = 0.0f;									// 対角線の長さ
	m_nLineVtxX = 0;									// 列頂点数(X)
	m_nVtx = 0;											// 頂点数
	m_nPolygon = 0;										// ポリゴン数
	m_nIndex = 0;										// インデックス数
	m_bSplitTex = false;								// 分割するかどうか
	m_bScrollTex = false;								// テクスチャがスクロールするかどうか
}

//=============================================================================
// デストラクタ
// Author : 唐�ｱ結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CMesh3D::~CMesh3D()
{

}

//=============================================================================
// 初期化
// Author : 唐�ｱ結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CMesh3D::Init()
{
	// メンバ変数の初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 向き
	m_size = D3DXVECTOR3(100.0f, 0.0f, 100.0f);			// 大きさ
	m_block = DOUBLE_INT(2, 2);							// ブロック数

	// ブロック一つあたりの大きさの算出
	m_blockSize = D3DXVECTOR3(m_size.x / m_block.x, 0.0f, m_size.z / m_block.y);

	// 数値の計算
	SetMeshInfo();

	// 頂点座標などの設定
	SetVtx();

	// 色の設定
	SetCol(m_col);

	// テクスチャの設定
	SetTex();

	// インデックスの設定
	SetIndexBuff();

	return S_OK;
}

//=============================================================================
// 終了
// Author : 唐�ｱ結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CMesh3D::Uninit()
{
	//頂点バッファを破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();

		m_pVtxBuff = nullptr;
	}

	// インデックスバッファの破棄	  
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();

		m_pIdxBuff = nullptr;
	}

	// メッシュ3Dの解放
	Release();
}

//=============================================================================
// 更新
// Author : 唐�ｱ結斗
// 概要 : 2D更新を行う
//=============================================================================
void CMesh3D::Update()
{
	TexScroll();
}

//=============================================================================
// 描画
// Author : 唐�ｱ結斗
// 概要 : 2D描画を行う
//=============================================================================
void CMesh3D::Draw()
{// レンダラーのゲット
	CRenderer *pRenderer = CApplication::GetRenderer();

	// テクスチャポインタの取得
	CTexture *pTexture = CApplication::GetTexture();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ワールドマトリックスの初期化
	// 行列初期化関数(第一引数の[行列]を[単位行列]に初期化)
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きの反映
	// 行列回転関数 (第一引数に[ヨー(y)ピッチ(x)ロール(z)]方向の回転行列を作成)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	// 行列掛け算関数 (第二引数 * 第三引数を第一引数に格納)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	// 行列移動関数 (第一引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);						// 行列掛け算関数

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	// 頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetTexture(m_nNumTex));

	// メッシュフィールド描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVtx, 0, m_nPolygon);

	// テクスチャの解除
	pDevice->SetTexture(0, nullptr);
}

//=============================================================================
// 位置のセッター
// Author : 唐�ｱ結斗
// 概要 : 位置のメンバ変数に引数を代入
//=============================================================================
void CMesh3D::SetPos(const D3DXVECTOR3 &pos)
{
	// 位置の設定
	m_pos = pos;

	// 頂点座標などの設定
	SetVtx();

	// 色の設定
	SetCol(m_col);

	// テクスチャの設定
	SetTex();

	// インデックスの設定
	SetIndexBuff();
}

//=============================================================================
// 向きのセッター
// Author : 唐�ｱ結斗
// 概要 : 向きのメンバ変数に引数を代入
//=============================================================================
void CMesh3D::SetRot(const D3DXVECTOR3 &rot)
{
	// 位置の設定
	m_rot = rot;

	// 頂点座標などの設定
	SetVtx();

	// 色の設定
	SetCol(m_col);

	// テクスチャの設定
	SetTex();

	// インデックスの設定
	SetIndexBuff();
}

//=============================================================================
// 大きさのセッター
// Author : 唐�ｱ結斗
// 概要 : 大きさのメンバ変数に引数を代入
//=============================================================================
void CMesh3D::SetSize(const D3DXVECTOR3 & size)
{
	// 大きさの設定
	m_size = size;

	// 数値の計算
	SetMeshInfo();

	// 頂点座標などの設定
	SetVtx();

	// 色の設定
	SetCol(m_col);

	// テクスチャの設定
	SetTex();

	// インデックスの設定
	SetIndexBuff();
}

//=============================================================================
// ブロック数の設定
// Author : 唐�ｱ結斗
// 概要 : ブロック数の設定
//=============================================================================
void CMesh3D::SetBlock(DOUBLE_INT block)
{
	m_block = block;

	// 数値の計算
	SetMeshInfo();

	// 頂点座標などの設定
	SetVtx();

	// 色の設定
	SetCol(m_col);

	// テクスチャの設定
	SetTex();

	// インデックスの設定
	SetIndexBuff();
}

//=============================================================================
// テクスチャ分割するかのセッター
// Author : 唐�ｱ結斗
// 概要 : テクスチャ分割するかの設定
//=============================================================================
void CMesh3D::SetSplitTex(bool bSplitTex)
{
	m_bSplitTex = bSplitTex;

	// テクスチャの設定
	SetTex();
}

//=============================================================================
// テクスチャスクロールの設定
// Author : 唐�ｱ結斗
// 概要 : テクスチャスクロールの設定
//=============================================================================
void CMesh3D::SetScrollTex(D3DXVECTOR2 addTex, bool bScrollTex)
{
	m_addTex = addTex;
	m_bScrollTex = bScrollTex;
}

//=============================================================================
// 頂点座標などの設定
// Author : 唐�ｱ結斗
// 概要 : 3D頂点座標、rhw、頂点カラーを設定する
//=============================================================================
void CMesh3D::SetVtx()
{
	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < m_line.y; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_line.x; nCntX++)
		{// 変数宣言
			int nCntVtx = nCntX + (nCntZ *  m_line.x);

			// 頂点座標の設定
			pVtx[nCntVtx].pos.x = (nCntVtx % m_line.x * m_blockSize.x) - m_size.x / 2.0f;
			pVtx[nCntVtx].pos.y = 0.0f;
			pVtx[nCntVtx].pos.z = (nCntVtx / m_line.x * -m_blockSize.z) + m_size.z / 2.0f;

			// 法線の設定
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			/*D3DXVec3Cross(&pVtx[nCntVtx].nor, &SetVecLine(pVtx[nCntVtx + 1].pos, pVtx[nCntVtx].pos), &SetVecLine(pVtx[nCntVtx + 1 + m_line.x].pos, pVtx[nCntVtx].pos));
			D3DXVec3Normalize(&pVtx[nCntVtx].nor, &pVtx[nCntVtx].nor);*/
		}
	}

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// テクスチャ座標の設定
// Author : 唐�ｱ結斗
// 概要 : 3Dメッシュのテクスチャ座標を設定する
//=============================================================================
void CMesh3D::SetTex()
{
	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < m_line.y; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_line.x; nCntX++)
		{// 変数宣言
			int nCntVtx = nCntX + (nCntZ *  m_line.x);

			if (m_bSplitTex)
			{// テクスチャ座標の設定
				pVtx[nCntVtx].tex = D3DXVECTOR2(1.0f * nCntX + m_tex.x, 1.0f * nCntZ + m_tex.y);
			}
			else
			{// テクスチャ座標の設定
				pVtx[nCntVtx].tex = D3DXVECTOR2(1.0f / m_block.x * nCntX + m_tex.x, 1.0f / m_block.y * nCntZ + m_tex.y);
			}	
		}
	}

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 色の設定
// Author : 唐�ｱ結斗
// 概要 : 3Dメッシュの色を設定する
//=============================================================================
void CMesh3D::SetCol(const D3DXCOLOR &col)
{
	m_col = col;

	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < m_line.y; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_line.x; nCntX++)
		{// 変数宣言
			int nCntVtx = nCntX + (nCntZ *  m_line.x);

			// 頂点カラーの設定
			pVtx[nCntVtx].col = m_col;
		}
	}

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// インデックスバッファの設定
// Author : 唐�ｱ結斗
// 概要 : インデックスバッファの数値を設定する
//=============================================================================
void CMesh3D::SetIndexBuff()
{
	// インデックスバッファをロック
	WORD *pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// インデックスの設定
	for (int nCntZ = 0; nCntZ < m_block.y; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_line.x; nCntX++)
		{// インデックス数の設定
			pIdx[0] = (WORD)(m_line.x + nCntX + nCntZ * m_line.x);
			pIdx[1] = (WORD)(m_line.x + nCntX + nCntZ * m_line.x - m_line.x);

			pIdx += 2;
		}

		if (nCntZ != m_block.y - 1)
		{// 最大数以下の時
		 // 縮退ポリゴンインデックス数の設定
			pIdx[0] = (WORD)(m_line.x * nCntZ + m_block.x);
			pIdx[1] = (WORD)(m_line.x * (nCntZ + 2));

			pIdx += 2;
		}
	}

	// インデックスバッファのアンロック
	m_pIdxBuff->Unlock();
}

//=============================================================================
// メッシュの数値の計算
// Author : 唐�ｱ結斗
// 概要 : ライン数,1列分の頂点数(X),頂点数,ポリゴン数,インデックス数の計算
//=============================================================================
void CMesh3D::SetMeshInfo()
{// デバイスのゲット
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	m_line = DOUBLE_INT(m_block.x + 1, m_block.y + 1);									// ライン数
	m_nLineVtxX = m_block.x * 2 + 2;													// 1列分の頂点数(X)
	m_nVtx = m_line.x * m_line.y;														// 頂点数
	m_nPolygon = (m_block.x * m_block.y * 2) + (((m_block.y - 1) * 2) * 2);				// ポリゴン数
	m_nIndex = (m_nLineVtxX * m_block.y) + ((m_block.y - 1) * 2);						// インデックス数

	// ブロック一つあたりの大きさの算出
	m_blockSize = D3DXVECTOR3(m_size.x / m_block.x, 0.0f, m_size.z / m_block.y);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);
}

//=============================================================================
// テクスチャスクロール
// Author : 唐�ｱ結斗
// 概要 : テクスチャスクロール
//=============================================================================
void CMesh3D::TexScroll()
{
	if (m_bScrollTex)
	{
		m_tex += m_addTex;
		SetTex();
	}
}

