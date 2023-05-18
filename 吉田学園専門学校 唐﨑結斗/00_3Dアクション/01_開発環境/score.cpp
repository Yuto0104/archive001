//**************************************************************************************************
//
// �X�R�A�̏���
// Auther�F�������l
//
//**************************************************************************************************
#include"main.h"
#include"score.h"

//*************************************************************
// �O���[�o���ϐ�
//*************************************************************
LPDIRECT3DTEXTURE9			g_pTextureScore = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffScore = NULL;			//���_�o�b�t�@�ւ̃|�C���^
Score						g_Score;						//�X�R�A���
int							g_nScore;						//�X�R�A�̒l

//*************************************************************
// �X�R�A�̏���������
//*************************************************************
void InitScore(void)
{
	// �ϐ��錾
	int nCountDigits;	// �������J�E���g����

	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �|���S���ɒ���t����e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureScore);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * MAX_VERTEX * MAX_DIGITS,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,															// ���_�t�@�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	// ���l�̏�����
	g_Score.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���S�_����̍�
	g_Score.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
	g_nScore = 0;										// �X�R�A�̒l
	
	// �X�R�A�̈ʒu�̏�����
	for (nCountDigits = 0; nCountDigits < MAX_DIGITS; nCountDigits++)
	{
		g_Score.pos[nCountDigits] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// ���_���ւ̃|�C���^�𐶐�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	// �Ίp���̒������Z�o����
	g_Score.fLength = sqrtf(((g_Score.offset.x * g_Score.offset.x) + (g_Score.offset.y * g_Score.offset.y)) / 2.0f);

	// �Ίp���̊p�x���Z�o
	g_Score.fAngele = atan2f(g_Score.offset.x, g_Score.offset.y);

	for (nCountDigits = 0; nCountDigits < MAX_DIGITS; nCountDigits++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos.x = g_Score.pos[nCountDigits].x + sinf(g_Score.rot.z + (D3DX_PI + g_Score.fAngele)) * g_Score.fLength;
		pVtx[0].pos.y = g_Score.pos[nCountDigits].y + cosf(g_Score.rot.z + (D3DX_PI + g_Score.fAngele)) * g_Score.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Score.pos[nCountDigits].x + sinf(g_Score.rot.z + (D3DX_PI - g_Score.fAngele)) *  g_Score.fLength;
		pVtx[1].pos.y = g_Score.pos[nCountDigits].y + cosf(g_Score.rot.z + (D3DX_PI - g_Score.fAngele)) *  g_Score.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Score.pos[nCountDigits].x + sinf(g_Score.rot.z - (0 + g_Score.fAngele)) * g_Score.fLength;
		pVtx[2].pos.y = g_Score.pos[nCountDigits].y + cosf(g_Score.rot.z - (0 + g_Score.fAngele)) * g_Score.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Score.pos[nCountDigits].x + sinf(g_Score.rot.z - (0 - g_Score.fAngele)) *  g_Score.fLength;
		pVtx[3].pos.y = g_Score.pos[nCountDigits].y + cosf(g_Score.rot.z - (0 - g_Score.fAngele)) *  g_Score.fLength;
		pVtx[3].pos.z = 0.0f;

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f + (g_nScore * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (g_nScore * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (g_nScore * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (g_nScore * 0.1f), 1.0f);

		pVtx += 4;		// ���_�f�[�^�̃|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffScore->Unlock();
}

//********************************************************************************
// �X�R�A�̏I������
//********************************************************************************
void UninitScore(void)
{
	// �e�N�X�`���̔j��	  
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();

		g_pTextureScore = NULL;
	}

	// ���_�o�b�t�@��j��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();

		g_pVtxBuffScore = NULL;
	}
}

//********************************************************************************
// �X�R�A�̍X�V����
//********************************************************************************
void UpdateScore(void)
{

}

//********************************************************************************
// �X�R�A�̕`�揈��
//********************************************************************************
void DrawScore(void)
{
	// �ϐ��錾
	int nCountDigits;		// �������J�E���g����

	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ���e�X�g���g�p����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// ���e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 50);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (nCountDigits = 0; nCountDigits < MAX_DIGITS; nCountDigits++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureScore);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCountDigits * 4,
			2);
	}
	
	// ���e�X�g�̏I��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//********************************************************************************
// �X�R�A�̐ݒ菈��
//********************************************************************************
void SetScore(int nScore, D3DXVECTOR3 pos, D3DXVECTOR3 offset)
{
	// �ϐ��錾
	int aPosTexU[8];		// �e���̐��l���i�[
	int nCountDigits;		// �������J�E���g����

	// �ϐ��Ɉ�������
	g_Score.offset = offset;
	g_nScore = nScore;

	// ���l�̕����Ɗi�[
	aPosTexU[0] = g_nScore % 100000000 / 10000000;
	aPosTexU[1] = g_nScore % 10000000 / 1000000;
	aPosTexU[2] = g_nScore % 1000000 / 100000;
	aPosTexU[3] = g_nScore % 100000 / 10000;
	aPosTexU[4] = g_nScore % 10000 / 1000;
	aPosTexU[5] = g_nScore % 1000 / 100;
	aPosTexU[6] = g_nScore % 100 / 10;
	aPosTexU[7] = g_nScore % 10 / 1;

	// ���_���ւ̃|�C���^�𐶐�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	// �X�R�A�̈ʒu�̐ݒ�
	for (nCountDigits = 0; nCountDigits < MAX_DIGITS; nCountDigits++)
	{
		g_Score.pos[nCountDigits] = D3DXVECTOR3(pos.x - (g_Score.offset.x + (g_Score.offset.x * 2) * nCountDigits), pos.y + g_Score.offset.y, 0.0f);
	}

	// �Ίp���̒������Z�o����
	g_Score.fLength = sqrtf(((g_Score.offset.x * g_Score.offset.x) + (g_Score.offset.y * g_Score.offset.y)) / 2.0f);

	// �Ίp���̊p�x���Z�o
	g_Score.fAngele = atan2f(g_Score.offset.x, g_Score.offset.y);

	for (nCountDigits = 0; nCountDigits < MAX_DIGITS; nCountDigits++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos.x = g_Score.pos[nCountDigits].x + sinf(g_Score.rot.z + (D3DX_PI + g_Score.fAngele)) * g_Score.fLength;
		pVtx[0].pos.y = g_Score.pos[nCountDigits].y + cosf(g_Score.rot.z + (D3DX_PI + g_Score.fAngele)) * g_Score.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Score.pos[nCountDigits].x + sinf(g_Score.rot.z + (D3DX_PI - g_Score.fAngele)) *  g_Score.fLength;
		pVtx[1].pos.y = g_Score.pos[nCountDigits].y + cosf(g_Score.rot.z + (D3DX_PI - g_Score.fAngele)) *  g_Score.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Score.pos[nCountDigits].x + sinf(g_Score.rot.z - (0 + g_Score.fAngele)) * g_Score.fLength;
		pVtx[2].pos.y = g_Score.pos[nCountDigits].y + cosf(g_Score.rot.z - (0 + g_Score.fAngele)) * g_Score.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Score.pos[nCountDigits].x + sinf(g_Score.rot.z - (0 - g_Score.fAngele)) *  g_Score.fLength;
		pVtx[3].pos.y = g_Score.pos[nCountDigits].y + cosf(g_Score.rot.z - (0 - g_Score.fAngele)) *  g_Score.fLength;
		pVtx[3].pos.z = 0.0f;

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[(MAX_DIGITS - 1) - nCountDigits] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aPosTexU[(MAX_DIGITS - 1) - nCountDigits] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[(MAX_DIGITS - 1) - nCountDigits] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aPosTexU[(MAX_DIGITS - 1) - nCountDigits] * 0.1f), 1.0f);

		pVtx += 4;			// ���_�f�[�^�̃|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffScore->Unlock();
}

//********************************************************************************
// �X�R�A�̉��Z����
//********************************************************************************
void AddScore(int nValue)
{
	// �ϐ��錾
	int aPosTexU[8];		// �e���̐��l���i�[
	int nCountDigits;		// �������J�E���g����

	// �ϐ��Ɉ�������
	g_nScore += nValue;

	// ���l�̕����Ɗi�[
	aPosTexU[0] = g_nScore % 100000000 / 10000000;
	aPosTexU[1] = g_nScore % 10000000 / 1000000;
	aPosTexU[2] = g_nScore % 1000000 / 100000;
	aPosTexU[3] = g_nScore % 100000 / 10000;
	aPosTexU[4] = g_nScore % 10000 / 1000;
	aPosTexU[5] = g_nScore % 1000 / 100;
	aPosTexU[6] = g_nScore % 100 / 10;
	aPosTexU[7] = g_nScore % 10 / 1;

	// ���_���ւ̃|�C���^�𐶐�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	// �Ίp���̒������Z�o����
	g_Score.fLength = sqrtf(((g_Score.offset.x * g_Score.offset.x) + (g_Score.offset.y * g_Score.offset.y)) / 2.0f);

	// �Ίp���̊p�x���Z�o
	g_Score.fAngele = atan2f(g_Score.offset.x, g_Score.offset.y);

	for (nCountDigits = 0; nCountDigits < MAX_DIGITS; nCountDigits++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos.x = g_Score.pos[nCountDigits].x + sinf(g_Score.rot.z + (D3DX_PI + g_Score.fAngele)) * g_Score.fLength;
		pVtx[0].pos.y = g_Score.pos[nCountDigits].y + cosf(g_Score.rot.z + (D3DX_PI + g_Score.fAngele)) * g_Score.fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Score.pos[nCountDigits].x + sinf(g_Score.rot.z + (D3DX_PI - g_Score.fAngele)) *  g_Score.fLength;
		pVtx[1].pos.y = g_Score.pos[nCountDigits].y + cosf(g_Score.rot.z + (D3DX_PI - g_Score.fAngele)) *  g_Score.fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Score.pos[nCountDigits].x + sinf(g_Score.rot.z - (0 + g_Score.fAngele)) * g_Score.fLength;
		pVtx[2].pos.y = g_Score.pos[nCountDigits].y + cosf(g_Score.rot.z - (0 + g_Score.fAngele)) * g_Score.fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Score.pos[nCountDigits].x + sinf(g_Score.rot.z - (0 - g_Score.fAngele)) *  g_Score.fLength;
		pVtx[3].pos.y = g_Score.pos[nCountDigits].y + cosf(g_Score.rot.z - (0 - g_Score.fAngele)) *  g_Score.fLength;
		pVtx[3].pos.z = 0.0f;

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[(MAX_DIGITS - 1) - nCountDigits] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aPosTexU[(MAX_DIGITS - 1) - nCountDigits] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[(MAX_DIGITS - 1) - nCountDigits] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aPosTexU[(MAX_DIGITS - 1) - nCountDigits] * 0.1f), 1.0f);

		pVtx += 4;		// ���_�f�[�^�̃|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffScore->Unlock();
}

//********************************************************************************
// �X�R�A�̏��̎擾
//********************************************************************************
int GetScore(void)
{
	return g_nScore;
}