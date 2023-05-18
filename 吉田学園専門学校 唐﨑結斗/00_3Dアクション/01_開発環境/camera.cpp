//**************************************************************************************************
//
// �J��������(camera.cpp)
// Auther�F�������l
//
//**************************************************************************************************

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"
#include "camera.h"
#include "input.h"
#include "mouse.h"
#include "player.h"
#include "calculation.h"

//***************************************************************************
// �}�N����`
//***************************************************************************
#define CAMERA_NEAR					(10.0f)				// �j�A
#define CAMERA_FUR					(2000.0f)			// �t�@�[
#define CAMERA_ROT_MOVE				(D3DX_PI * 10)		// �p�x�̕ϓ��l
#define CAMERA_MOVE_SPEED			(20.0f)				// �J�����̈ړ��Ǔx
#define MIN_MOUSE_MOVED				(5.0f)				// �}�E�X����̍Œ�l
#define ROTATE_MOUSE_MOVED			(0.45f)				// �}�E�X�ł̃J������]�l
#define MAX_ROTATE_MOUSE_MOVED		(50.0f)				// �}�E�X�ł̃J������]�l�̍ő�
#define MIN_ROTATE_MOUSE_MOVED		(0.1f)				// �}�E�X�ł̃J������]�l�̍ŏ�
#define ROTATE_MOUSE_FRICTION		(0.2f)				// �}�E�X�ł̃J������]�l�̖��C�W��
#define FOLLOW_DISTANCE				(10.0f)				// �Ǐ]���̒����_�ƃv���C���[�̋���

//***************************************************************************
// �O���[�o���ϐ�
//***************************************************************************
static Camera		s_camera;				// �J�������
static int			s_nCameraMode = 0;		// �J�����ړ����[�h

//---------------------------------------------------------------------------
// �J��������������
//---------------------------------------------------------------------------
void InitCamera(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU, D3DXVECTOR3 rot)
{
	// ���_�E�����_�E�������ݒ肷��
	s_camera.posV = posV;
	s_camera.posR = posR;
	s_camera.vecU = vecU;

	// ���l�̌v�Z
	float fDistanceX = s_camera.posR.x - s_camera.posV.x;
	float fDistanceY = s_camera.posR.y - s_camera.posV.y;
	float fDistanceZ = s_camera.posR.z - s_camera.posV.z;

	// ���_���璍���_�܂ł̋������Z�o
	s_camera.fDistance = sqrtf((fDistanceY * fDistanceY) + (fDistanceX * fDistanceX) + (fDistanceZ * fDistanceZ));

	// �����_�̌�����ݒ�
	s_camera.rot = rot;

	// �ړ������̏�����
	s_camera.rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//---------------------------------------------------------------------------
// �J�����I������
//---------------------------------------------------------------------------
void UninitCamera(void)
{

}

//---------------------------------------------------------------------------
// �J�����X�V����
//---------------------------------------------------------------------------
void UpdateCamera(void)
{
	if (GetKeyboardTrigger(DIK_F5) == true)
	{// �J�����ړ����[�h�̕ύX
		s_nCameraMode ^= 1;
	}

	MODE mode = GetMode();

	if (mode == MODE_GAME)
	{
		// �J�����̉�]
		RotateCamera();

		// �J�����ړ�
		//MoveCamera();

		// �J�����̒Ǐ]����
		FollowCamera();
	}
	else if (mode == MODE_TITLE)
	{
		TitleRotateCamera();
	}
}

//---------------------------------------------------------------------------
// �J�����ݒ菈��
//---------------------------------------------------------------------------
void SetCamera(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&s_camera.mtxView);			// �s�񏉊����֐�

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&s_camera.mtxView,
		&s_camera.posV,
		&s_camera.posR,
		&s_camera.vecU);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &s_camera.mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&s_camera.mtxProjection);			// �s�񏉊����֐�

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&s_camera.mtxProjection,
		D3DXToRadian(45.0f),								// ����p
		(float)SCREEN_WIDH / (float)SCREEN_HEIGHT,			// �A�X�y�N�g��
		CAMERA_NEAR,										// �j�A
		CAMERA_FUR);										// �t�@�[

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &s_camera.mtxProjection);
}

//---------------------------------------------------------------------------
// �J�����ݒ菈��
//---------------------------------------------------------------------------
Camera *GetCamera(void)
{
	return &s_camera;
}

//---------------------------------------------------------------------------
// �J������]����
//---------------------------------------------------------------------------
void RotateCamera(void)
{
	D3DXVECTOR3 pMouseMove = GetMouseMove();

	if (pMouseMove.x > MIN_MOUSE_MOVED || pMouseMove.x < -MIN_MOUSE_MOVED)
	{// �}�E�X����苗��(X)�ړ������Ƃ�
		if (pMouseMove.x > MIN_MOUSE_MOVED)
		{
			s_camera.roll.y += (D3DX_PI / 180.0f) * ROTATE_MOUSE_MOVED;
		}
		if (pMouseMove.x < -MIN_MOUSE_MOVED)
		{
			s_camera.roll.y += (D3DX_PI / 180.0f) * -ROTATE_MOUSE_MOVED;
		}
	}

	if (pMouseMove.y > MIN_MOUSE_MOVED || pMouseMove.y < -MIN_MOUSE_MOVED)
	{// �}�E�X����苗��(Y)�ړ������Ƃ�
		if (pMouseMove.y > MIN_MOUSE_MOVED)
		{
			s_camera.roll.x += (D3DX_PI / 180.0f) * ROTATE_MOUSE_MOVED / 3.0f;
		}
		if (pMouseMove.y < -MIN_MOUSE_MOVED)
		{
			s_camera.roll.x += (D3DX_PI / 180.0f) * -ROTATE_MOUSE_MOVED / 3.0f;
		}
	}

	// ���x���~�b�^�[
	float speed = D3DXVec3Length(&s_camera.roll);

	if (speed > (D3DX_PI / 180.0f) * MAX_ROTATE_MOUSE_MOVED)
	{
		s_camera.roll = s_camera.roll / speed * (D3DX_PI / 180.0f) * -ROTATE_MOUSE_MOVED;
	}

	// �����C�W����������
	s_camera.roll *= (1.0f - ROTATE_MOUSE_FRICTION);

	// ���x���~�b�^�[
	if (D3DXVec3Length(&s_camera.roll) < (D3DX_PI / 180.0f) * MIN_ROTATE_MOUSE_MOVED)
	{
		s_camera.roll = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// �J�����̌����̐��K��
	RotNormalization(s_camera.roll.x);
	RotNormalization(s_camera.roll.y);
	RotNormalization(s_camera.roll.z);

	s_camera.rot += s_camera.roll;

	if (s_camera.rot.y < -D3DX_PI)
	{// ������-D3DX_PI�����̎�
		s_camera.rot.y += D3DX_PI * 2;
	}
	if (s_camera.rot.y > D3DX_PI)
	{// ������D3DX_PI�ȏ�̎�
		s_camera.rot.y -= D3DX_PI * 2;
	}
	if (s_camera.rot.x < 0.0f + 1.68f)
	{// ������0�ȉ��̎�
		s_camera.rot.x = 0.0f + 1.68f;
	}
	if (s_camera.rot.x > D3DX_PI - 0.1f)
	{// ������D3DX_PI�ȏ�̎�
		s_camera.rot.x = D3DX_PI - 0.1f;
	}

	// �����_�̎Z�o
	s_camera.posR.z = s_camera.posV.z + sinf(s_camera.rot.x) * cosf(s_camera.rot.y) * s_camera.fDistance;
	s_camera.posR.x = s_camera.posV.x + sinf(s_camera.rot.x) * sinf(s_camera.rot.y) * s_camera.fDistance;
	s_camera.posR.y = s_camera.posV.y + cosf(s_camera.rot.x) * s_camera.fDistance;

	//// �����_�̉�]
	//if (GetKeyboardPress(DIK_Q) == true
	//	|| GetKeyboardPress(DIK_E) == true
	//	|| GetKeyboardPress(DIK_Y) == true
	//	|| GetKeyboardPress(DIK_H) == true)
	//{
	//	if (GetKeyboardPress(DIK_Q) == true)
	//	{// [Q]�L�[�������ꂽ��
	//		s_camera.rot.y += 1.0f / -CAMERA_ROT_MOVE;
	//	}
	//	if (GetKeyboardPress(DIK_E) == true)
	//	{// [E]�L�[�������ꂽ��
	//		s_camera.rot.y += 1.0f / CAMERA_ROT_MOVE;
	//	}
	//	if (GetKeyboardPress(DIK_Y) == true)
	//	{// [Y]�L�[�������ꂽ��
	//		s_camera.rot.x += 1.0f / -CAMERA_ROT_MOVE;
	//	}
	//	if (GetKeyboardPress(DIK_H) == true)
	//	{// [H]�L�[�������ꂽ��
	//		s_camera.rot.x += 1.0f / CAMERA_ROT_MOVE;
	//	}

	//	// �J�����̌����̐��K��
	//	if (s_camera.rot.y < -D3DX_PI)
	//	{// ������-D3DX_PI�����̎�
	//		s_camera.rot.y += D3DX_PI * 2;
	//	}
	//	if (s_camera.rot.y > D3DX_PI)
	//	{// ������D3DX_PI�ȏ�̎�
	//		s_camera.rot.y -= D3DX_PI * 2;
	//	}
	//	if (s_camera.rot.x < 0.0f + 0.1f)
	//	{// ������0�ȉ��̎�
	//		s_camera.rot.x = 0.0f + 0.1f;
	//	}
	//	if (s_camera.rot.x > D3DX_PI - 0.1f)
	//	{// ������D3DX_PI�ȏ�̎�
	//		s_camera.rot.x = D3DX_PI - 0.1f;
	//	}

	//	// �����_�̎Z�o
	//	s_camera.posR.z = s_camera.posV.z + sinf(s_camera.rot.x) * cosf(s_camera.rot.y) * s_camera.fDistance;
	//	s_camera.posR.x = s_camera.posV.x + sinf(s_camera.rot.x) * sinf(s_camera.rot.y) * s_camera.fDistance;
	//	s_camera.posR.y = s_camera.posV.y + cosf(s_camera.rot.x) * s_camera.fDistance;
	//}

	//// ���_�̉�]
	//if (GetKeyboardPress(DIK_Z) == true
	//	|| GetKeyboardPress(DIK_C) == true
	//	|| GetKeyboardPress(DIK_U) == true
	//	|| GetKeyboardPress(DIK_J) == true)
	//{
	//	if (GetKeyboardPress(DIK_Z) == true)
	//	{// [Z]�L�[�������ꂽ��
	//		s_camera.rot.y += 1.0f / -CAMERA_ROT_MOVE;
	//	}
	//	if (GetKeyboardPress(DIK_C) == true)
	//	{// [C]�L�[�������ꂽ��
	//		s_camera.rot.y += 1.0f / CAMERA_ROT_MOVE;
	//	}
	//	if (GetKeyboardPress(DIK_U) == true)
	//	{// [U]�L�[�������ꂽ��
	//		s_camera.rot.x += 1.0f / -CAMERA_ROT_MOVE;
	//	}
	//	if (GetKeyboardPress(DIK_J) == true)
	//	{// [J]�L�[�������ꂽ��
	//		s_camera.rot.x += 1.0f / CAMERA_ROT_MOVE;
	//	}

	//	// �J�����̌����̐��K��
	//	if (s_camera.rot.y < -D3DX_PI)
	//	{// ������-D3DX_PI�����̎�
	//		s_camera.rot.y += D3DX_PI * 2;
	//	}
	//	if (s_camera.rot.y > D3DX_PI)
	//	{// ������D3DX_PI�ȏ�̎�
	//		s_camera.rot.y -= D3DX_PI * 2;
	//	}
	//	if (s_camera.rot.x < 0.0f + 0.1f)
	//	{// ������0�ȉ��̎�
	//		s_camera.rot.x = 0.0f + 0.1f;
	//	}
	//	if (s_camera.rot.x > D3DX_PI - 0.1f)
	//	{// ������D3DX_PI�ȏ�̎�
	//		s_camera.rot.x = D3DX_PI - 0.1f;
	//	}

	//	// ���_�̎Z�o
	//	s_camera.posV.z = s_camera.posR.z - sinf(s_camera.rot.x) * cosf(s_camera.rot.y) * s_camera.fDistance;
	//	s_camera.posV.x = s_camera.posR.x - sinf(s_camera.rot.x) * sinf(s_camera.rot.y) * s_camera.fDistance;
	//	s_camera.posV.y = s_camera.posR.y - cosf(s_camera.rot.x) * s_camera.fDistance;
	//}
}

//---------------------------------------------------------------------------
// �J�����ړ�����
//---------------------------------------------------------------------------
void MoveCamera(void)
{
	if (GetKeyboardPress(DIK_W) == true
		|| GetKeyboardPress(DIK_A) == true
		|| GetKeyboardPress(DIK_D) == true
		|| GetKeyboardPress(DIK_S) == true)
	{// �ړ��L�[�������ꂽ
		// �O�㍶�E�ړ�
		if (GetKeyboardPress(DIK_W) == true)
		{// [W]�L�[�������ꂽ��
			if (GetKeyboardPress(DIK_A) == true)
			{// [A]�L�[�������ꂽ��
				// �ړ������̍X�V
				s_camera.rotMove.y = D3DX_PI * -0.25f;
			}
			else if (GetKeyboardPress(DIK_D) == true)
			{// [D]�L�[�������ꂽ��
			 // �ړ������̍X�V
				s_camera.rotMove.y = D3DX_PI * 0.25f;
			}
			else
			{// �ړ������̍X�V
				s_camera.rotMove.y = D3DX_PI * 0.0f;
			}

			// �ړ������̍X�V
			s_camera.rotMove.x = D3DX_PI * 0.0f;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{// [S]�L�[�������ꂽ��
			if (GetKeyboardPress(DIK_A) == true)
			{// [A]�L�[�������ꂽ��
				// �ړ������̍X�V
				s_camera.rotMove.y = D3DX_PI * -0.75f;
			}
			else if (GetKeyboardPress(DIK_D) == true)
			{// [D]�L�[�������ꂽ��
				// �ړ������̍X�V
				s_camera.rotMove.y = D3DX_PI * 0.75f;
			}
			else
			{// �ړ������̍X�V
				s_camera.rotMove.y = D3DX_PI;
			}

			// �ړ������̍X�V
			s_camera.rotMove.x = D3DX_PI * 1.0f;
		}
		else if (GetKeyboardPress(DIK_A) == true)
		{// [A]�L�[�������ꂽ��
			// �ړ������̍X�V
			s_camera.rotMove.y = D3DX_PI * -0.5f;

			// �ړ������̍X�V
			s_camera.rotMove.x = D3DX_PI * 0.5f;
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{// [D]�L�[�������ꂽ��
			// �ړ������̍X�V
			s_camera.rotMove.y = D3DX_PI * 0.5f;

			// �ړ������̍X�V
			s_camera.rotMove.x = D3DX_PI * 0.5f;
		}

		// �ړ������̎Z�o
		s_camera.rotMove.x += s_camera.rot.x;
		if (s_camera.rotMove.x > D3DX_PI)
		{// �ړ������̐��K��
			s_camera.rotMove.x -= D3DX_PI * 2;
		}
		else if (s_camera.rotMove.x < -D3DX_PI)
		{// �ړ������̐��K��
			s_camera.rotMove.x += D3DX_PI * 2;
		}

		s_camera.rotMove.y += s_camera.rot.y;
		if (s_camera.rotMove.y > D3DX_PI)
		{// �ړ������̐��K��
			s_camera.rotMove.y -= D3DX_PI * 2;
		}
		else if (s_camera.rotMove.y < -D3DX_PI)
		{// �ړ������̐��K��
			s_camera.rotMove.y += D3DX_PI * 2;
		}

		// ���_�ʒu�̍X�V
		if (s_nCameraMode == 0)
		{// �J�����ړ����[�h[0]
			s_camera.posV.x += sinf(s_camera.rotMove.y) * CAMERA_MOVE_SPEED;
			s_camera.posV.z += cosf(s_camera.rotMove.y) * CAMERA_MOVE_SPEED;
		}
		else if (s_nCameraMode == 1)
		{// �J�����ړ����[�h[1]
			s_camera.posV.z += sinf(s_camera.rotMove.x) * cosf(s_camera.rotMove.y) * CAMERA_MOVE_SPEED;
			s_camera.posV.x += sinf(s_camera.rotMove.x) * sinf(s_camera.rotMove.y) * CAMERA_MOVE_SPEED;
			s_camera.posV.y += cosf(s_camera.rotMove.x) * CAMERA_MOVE_SPEED;
		}	

		// �����_�̎Z�o
		s_camera.posR.z = s_camera.posV.z + sinf(s_camera.rot.x) * cosf(s_camera.rot.y) * s_camera.fDistance;
		s_camera.posR.x = s_camera.posV.x + sinf(s_camera.rot.x) * sinf(s_camera.rot.y) * s_camera.fDistance;
		s_camera.posR.y = s_camera.posV.y + cosf(s_camera.rot.x) * s_camera.fDistance;
	}
}

//---------------------------------------------------------------------------
// �J�����̒Ǐ]����
//---------------------------------------------------------------------------
void FollowCamera(void)
{
	// �v���C���[���̎擾
	Player *pPlayer = GetPlayer();

	//// �ړI�̒����_�̎Z�o
	//s_camera.posRDest.z = pPlayer->pos.z + sinf(pPlayer->rot.x) * cosf(pPlayer->rot.y) * s_camera.fDistance;
	//s_camera.posRDest.x = pPlayer->pos.x + sinf(pPlayer->rot.x) * sinf(pPlayer->rot.y) * s_camera.fDistance;
	//s_camera.posRDest.y = pPlayer->pos.y + cosf(pPlayer->rot.x) * s_camera.fDistance;

	s_camera.posRDest.z = pPlayer->pos.z + cosf(pPlayer->rot.y) * -10.0f;
	s_camera.posRDest.x = pPlayer->pos.x + sinf(pPlayer->rot.y) * -10.0f;
	s_camera.posRDest.y = pPlayer->pos.y;

	//// �ړI�̎��_�̎Z�o
	//s_camera.posVDest.z = pPlayer->pos.z - sinf(pPlayer->rot.x) * cosf(pPlayer->rot.y) * s_camera.fDistance;
	//s_camera.posVDest.x = pPlayer->pos.x - sinf(pPlayer->rot.x) * sinf(pPlayer->rot.y) * s_camera.fDistance;
	//s_camera.posVDest.y = pPlayer->pos.y - cosf(pPlayer->rot.x) * s_camera.fDistance;

	s_camera.posVDest.z = pPlayer->pos.z - cosf(s_camera.rot.y) * s_camera.fDistance;
	s_camera.posVDest.x = pPlayer->pos.x - sinf(s_camera.rot.y) * s_camera.fDistance;
	s_camera.posVDest.y = 80.0f;

	// �����_�̈ړ�
	s_camera.posR.x += (s_camera.posRDest.x - s_camera.posR.x) * 0.1f;
	s_camera.posR.y += (s_camera.posRDest.y - s_camera.posR.y) * 0.1f;
	s_camera.posR.z += (s_camera.posRDest.z - s_camera.posR.z) * 0.1f;

	// ���_�̈ړ�
	s_camera.posV.x += (s_camera.posVDest.x - s_camera.posV.x) * 0.1f;
	s_camera.posV.y += (s_camera.posVDest.y - s_camera.posV.y) * 0.1f;
	s_camera.posV.z += (s_camera.posVDest.z - s_camera.posV.z) * 0.1f;
}

//---------------------------------------------------------------------------
// �J�����̎�����]����
//---------------------------------------------------------------------------
void AutoRotateCamera(void)
{
	// �v���C���[���̎擾
	Player *pPlayer = GetPlayer();

	// �ړI�̌���
	s_camera.rotDest.x = atan2f(pPlayer->pos.z - s_camera.posV.z, pPlayer->pos.y - s_camera.posV.y);
	s_camera.rotDest.y = pPlayer->rot.y - D3DX_PI;

	// �ړI�̌����̎Z�o
	s_camera.rotDest.x -= s_camera.rot.x;
	s_camera.rotDest.y -= s_camera.rot.y;

	// �J�����̖ړI�̌����̐��K��
	if (s_camera.rotDest.y < -D3DX_PI)
	{// ������-D3DX_PI�����̎�
		s_camera.rotDest.y += D3DX_PI * 2;
	}
	if (s_camera.rotDest.y > D3DX_PI)
	{// ������D3DX_PI�ȏ�̎�
		s_camera.rotDest.y -= D3DX_PI * 2;
	}
	if (s_camera.rotDest.x < 0.0f + 0.1f)
	{// ������0�ȉ��̎�
		s_camera.rotDest.x = 0.0f + 0.1f;
	}
	if (s_camera.rotDest.x > D3DX_PI - 0.1f)
	{// ������D3DX_PI�ȏ�̎�
		s_camera.rotDest.x = D3DX_PI - 0.1f;
	}

	// �J�����̌����̍X�V
	s_camera.rot.x += (s_camera.rotDest.x) * 0.1f;
	s_camera.rot.y += (s_camera.rotDest.y) * 0.1f;

	// �J�����̌����̐��K��
	if (s_camera.rot.y < -D3DX_PI)
	{// ������-D3DX_PI�����̎�
		s_camera.rot.y += D3DX_PI * 2;
	}
	if (s_camera.rot.y > D3DX_PI)
	{// ������D3DX_PI�ȏ�̎�
		s_camera.rot.y -= D3DX_PI * 2;
	}
	if (s_camera.rot.x < 0.0f + 0.1f)
	{// ������0�ȉ��̎�
		s_camera.rot.x = 0.0f + 0.1f;
	}
	if (s_camera.rot.x > D3DX_PI - 0.1f)
	{// ������D3DX_PI�ȏ�̎�
		s_camera.rot.x = D3DX_PI - 0.1f;
	}
}

//---------------------------------------------------------------------------
// �J�����̉�]����
//---------------------------------------------------------------------------
void TitleRotateCamera(void)
{
	// ���_�̉�]
	s_camera.rot.y += (D3DX_PI / 180.0f) * 0.5f;

	// �J�����̌����̐��K��
	if (s_camera.rot.y < -D3DX_PI)
	{// ������-D3DX_PI�����̎�
		s_camera.rot.y += D3DX_PI * 2;
	}
	if (s_camera.rot.y > D3DX_PI)
	{// ������D3DX_PI�ȏ�̎�
		s_camera.rot.y -= D3DX_PI * 2;
	}
	if (s_camera.rot.x < 0.0f + 0.1f)
	{// ������0�ȉ��̎�
		s_camera.rot.x = 0.0f + 0.1f;
	}
	if (s_camera.rot.x > D3DX_PI - 0.1f)
	{// ������D3DX_PI�ȏ�̎�
		s_camera.rot.x = D3DX_PI - 0.1f;
	}

	// ���_�̎Z�o
	s_camera.posV.z = s_camera.posR.z - sinf(s_camera.rot.x) * cosf(s_camera.rot.y) * s_camera.fDistance;
	s_camera.posV.x = s_camera.posR.x - sinf(s_camera.rot.x) * sinf(s_camera.rot.y) * s_camera.fDistance;
	s_camera.posV.y = s_camera.posR.y - cosf(s_camera.rot.x) * s_camera.fDistance;
}