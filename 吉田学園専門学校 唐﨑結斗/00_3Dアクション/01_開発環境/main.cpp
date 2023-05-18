//**************************************************************************************************
//
// ���C������(main.cpp)
// Auther�F�������l
//
//**************************************************************************************************

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include<stdio.h>
#include"main.h"

#include"input.h"
#include"mouse.h"
#include"fade.h"
#include"title.h"
#include"tutorial.h"
#include"game.h"
#include"result.h"
#include"ranking.h"

#include"player.h"
#include"camera.h"
#include"sound.h"

//***************************************************************************
// �O���[�o���ϐ�
//***************************************************************************
LPDIRECT3D9					g_pD3D = NULL;							// Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9			g_pD3DDevice = NULL;					// Direct3D�f�o�C�X�ւ̃|�C���^
LPD3DXFONT					g_pFont = NULL;							// �t�H���g�ւ̃|�C���^
MODE						g_mode = MODE_TITLE;					// ���݂̃��[�h
HWND						g_hWnd;									// �E�B���h�E�n���h��(���ʎq)
int							g_nCountFPS = 0;						// FPS�J�E���^
int							g_nJudgDebagText = 0;					// �f�o�b�N�\�������̔���p�ϐ�
int							g_nUseWireFrame = 0;					// ���C���[�t���[���̔���p�ϐ�

//---------------------------------------------------------------------------
// ���C���֐�
//---------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdline, int nCmdshow)
{
	// �E�B���h�E�N���X�̍\����
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),						// WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,								// �E�B���h�E�̃X�^�C��
		WindowProc,								// �E�B���h�E�v���V�[�W��
		0,										// 0�ɂ���(�ʏ�͎g�p���Ȃ�)
		0,										// 0�ɂ���(�ʏ�͎g�p���Ȃ�)
		hInstance,								// �C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),			// �^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),				// �}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),				// �N���C�A���g�̈�̔w�i�F
		NULL,									// ���j���[�o�[
		CLASS_NAME,								// �E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)			// �t�@�C���̃A�C�R��
	};

	// �ϐ��錾
	MSG			msg;												// ���b�Z�[�W���i�[����ϐ�
	RECT		rect = { 0,0,SCREEN_WIDH,SCREEN_HEIGHT };			// ��ʃT�C�Y�\����
	DWORD		dwCurrentTime;										// ���ݎ���
	DWORD		dwExecLastTime;										// �Ō�ɏ�����������
	DWORD		dwFrameCount;										// �t���[���J�E���g
	DWORD		dwFPSLastTime;										// �Ō��FPS���v����������

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// �E�B���h�E�𐶐�
	g_hWnd = CreateWindowEx(0,				// �g���E�B���h�E�X�^�C��
		CLASS_NAME,							// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,						// �E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,				// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,						// �E�B���h�E�̍���X���W
		CW_USEDEFAULT,						// �E�B���h�E�̍���Y���W
		(rect.right - rect.left),			// �E�B���h�E�̕�
		(rect.bottom - rect.top),			// �E�B���h�E�̍���
		NULL,								// �e�E�B���h�E�̃n���h��
		NULL,								// ���j���[�n���h�����͎q�E�B���h�EID
		hInstance,							// �C���X�^���X�n���h��
		NULL);								// �E�B���h�E�쐬�f�[�^

	// ����������
#ifdef _DEBUG
	if (FAILED(Init(hInstance, g_hWnd, TRUE)) != 0)
	{// ���������������s�����ꍇ
		return-1;
	}
#else
	if (FAILED(Init(hInstance, g_hWnd, FALSE)) != 0)
	{// ���������������s�����ꍇ
		return-1;
	}
#endif
	// ����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;						// ������
	dwExecLastTime = timeGetTime();			// ���ݎ������擾(�ۑ�)
	dwFrameCount = 0;						// �t���[���J�E���g��������
	dwFPSLastTime = timeGetTime();			// ���ݎ�������(�ۑ�)

	// �E�B���h�E�̕\��
	ShowWindow(g_hWnd, nCmdshow);		// �E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(g_hWnd);				// �N���C�A���g�̈���X�V

	// ���b�Z�[�W���[�v
	while (1)
	{
		// ���������^�̏ꍇ���s
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// Windows�̏���
			if (msg.message == WM_QUIT)
			{// WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				// ���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);			// ���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);			// �E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{// DirectX�̏���
			dwCurrentTime = timeGetTime();		// ���ݎ������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5�b�o��
				// FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;		// FPS���v������������ۑ�
				dwFrameCount = 0;					// �t���[���J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 60����1�b�o��
				dwExecLastTime = dwCurrentTime;		// �����J�n����[���ݎ���]��ۑ�

				// �X�V����
				Update();
				
				// �`�揈��
				Draw();

				dwFrameCount++;			// �t���[���J�E���g�����Z
			}
		}
	}

	// �I������
	Uninit();

	// ����\��߂�
	timeEndPeriod(1);

	// �E�B���h�E�N���X�̓o�^����
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �Ԃ�l�𑗂�
	return (int)msg.wParam;
}

//---------------------------------------------------------------------------
// �E�B���h�E�v���V�[�W��
//---------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// �ϐ��錾
	int nID;	// �Ԃ�l���i�[����

   //��������
	switch (uMsg)
	{
	case WM_DESTROY:		// �E�B���h�E�j���̃��b�Z�[�W
		// WM_QUIT�փ��b�Z�[�W�𑗂�
		PostQuitMessage(0);

		// �����I��
		break;

	case WM_KEYDOWN:		// �L�[�������̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:		 // [ESC]�������ꂽ
#ifdef _DEBUG
			DestroyWindow(hWnd);
#else
			// �f�[�^����
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

			// ���������^�̏ꍇ���s
			if (nID == IDYES)
			{
				// �E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);
			}
#endif

			//�����I��
			break;
		}

		// �����I��
		break;

	case WM_CLOSE: //����{�^�������������b�Z�[�W

		// �f�[�^����
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

		// ���������^�̏ꍇ���s
		if (nID == IDYES)
		{
			// �E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;		// 0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}

		// �����I��
		break;

	case WM_LBUTTONDOWN:	// �}�E�X���N���b�N�̃��b�Z�[�W
		// �E�B���h�E�Ƀt�H�[�J�X�����킹��
		SetFocus(hWnd);

		// �����I��
		break;

	}

	// �Ԃ�l�𑗂�
	return DefWindowProc(hWnd, uMsg, wParam, lParam); //�����̏�����Ԃ�
}

//---------------------------------------------------------------------------
// ����������
//---------------------------------------------------------------------------
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �ϐ��錾
	D3DDISPLAYMODE				d3ddm;			// �f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS		d3dpp;			// �v���[���e�[�V�����p�����[�^

	// Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	// ���������^�̏ꍇ���s
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h�̎擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));		// �p�����[�^�̃[���N���A

	// �A�h���X�̑��
	d3dpp.BackBufferWidth = SCREEN_WIDH;							// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;							// �o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;										// �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// �_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;							// �f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;										// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��

	// Direct3D�f�o�C�X�̐���
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		// Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_������CPU�ōs��)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{// Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_������CPU�ōs��)
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	// �����_�\�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �T���v���[�X�e�\�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//�e�N�X�`�������j�A�⊮����
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//�e�N�X�`�������j�A�⊮����
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// �f�o�b�N�\���p�̃t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH, "Terminal", &g_pFont);

	// �}�E�X�J�[�\���̔�\��
	ShowCursor(FALSE);

	// �L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// �W���C�p�b�h�̏���������
	InitJoypad();

	// �}�E�X�̏�����
	InitMouse(hInstance, hWnd);

	//�T�E���h����������
	InitSound(hWnd);

	//�t�F�[�h����������
	InitFade(g_mode);

	//�����L���O���Z�b�g
	ResetRanking();

	return S_OK;
}

//---------------------------------------------------------------------------
// �I������
//---------------------------------------------------------------------------
void Uninit(void)
{
	// �L�[�{�[�h�̏I������
	UninitKeyboard();

	// �W���C�p�b�h�̏I������
	UninitJoypad();

	// �}�E�X�̏I������
	UninitMouse();

	//�T�E���h�̏I������
	UninitSound();

	//�^�C�g����ʂ̏I������
	UninitTitle();

	//�`���[�g���A����ʂ̏I������
	UninitTutorial();

	//�Q�[����ʂ̏I������
	UninitGame();

	//���U���g��ʂ̏I������
	UninitResult();

	//�����L���O��ʂ̏I������
	UninitRanking();

	//�t�F�[�h�I������
	UninitFade();

	// �f�o�b�N�\���p�t�H���g�̔j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();

		g_pFont = NULL;
	}

	// Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();

		g_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();

		g_pD3D = NULL;
	}
}

//---------------------------------------------------------------------------
// �X�V����
//---------------------------------------------------------------------------
void Update(void)
{
	// �L�[�{�[�h�̍X�V����
	UpdateKeyboard();

	// �W���C�p�b�h�̍X�V����
	UpdateJoypad();

	// �}�E�X�̍X�V����
	UpdateMouse();

	//��ʂ̍X�V
	switch (g_mode)
	{
	case MODE_TITLE:		//�^�C�g�����
		UpdateTitle();
		break;

	case MODE_TUTORIAL:		//�`���[�g���A�����
		UpdateTutorial();
		break;

	case MODE_GAME:			//�Q�[�����
		UpdateGame();
		break;

	case MODE_RESULT:		//���U���g���
		UpdateResult();
		break;

	case MODE_RANKING:		//�����L���O���
		UpdateRanking();
		break;
	}

	//�t�F�[�h�X�V����
	UpdateFade();

	if (GetKeyboardTrigger(DIK_F1) == true || GetJoypadTrigger(JOYKEY_BACK) == true)
	{// [F1]�L�[�������ꂽ���A�W���C�p�b�h��[Back]�������ꂽ
		g_nJudgDebagText ^= 1;
	}

	if (GetKeyboardTrigger(DIK_F2) == true)
	{// [F2]�L�[�������ꂽ���A�W���C�p�b�h��[Back]�������ꂽ
		g_nUseWireFrame ^= 1;
	}

	if (g_nUseWireFrame == 1)
	{// ���C���[�t���[�����g�p���Ă���
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}

//---------------------------------------------------------------------------
// �`�揈��
//---------------------------------------------------------------------------
void Draw(void)
{// ��ʂ̃N���A(�o�b�N�o�b�t�@&Z�o�b�t�@�̃N���A)
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{// �`��J�n�����������ꍇ
		// ��ʂ̕`��

		switch (g_mode)
		{
		case MODE_TITLE:		//�^�C�g�����
			DrawTitle();
			break;

		case MODE_TUTORIAL:		//�`���[�g���A�����
			DrawTutorial();
			break;

		case MODE_GAME:			//�Q�[�����
			DrawGame();
			break;

		case MODE_RESULT:		//���U���g���
			DrawResult();
			break;

		case MODE_RANKING:		//�����L���O���
			DrawRanking();
			break;
		}

		//�t�F�[�h�`�揈��
		DrawFade();
#ifdef _DEBUG
		if (g_nJudgDebagText == 0)
		{// �f�o�b�N�\�������̔���p�̕ϐ���0�̎�
			// FPS�̕`��
			DrawFPS();
		}
#endif

		// �`��I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//*********************************************************************************
//���[�h�ݒ�
//*********************************************************************************
void SetMode(MODE mode)
{
	//���݂̉��(���[�h)�̏I������
	switch (g_mode)
	{
	case MODE_TITLE:		//�^�C�g�����
		UninitTitle();
		break;

	case MODE_TUTORIAL:		//�`���[�g���A�����
		UninitTutorial();
		break;

	case MODE_GAME:			//�Q�[�����
		UninitGame();
		break;

	case MODE_RESULT:		//���U���g���
		UninitResult();
		break;

	case MODE_RANKING:		//�����L���O���
		UninitRanking();
		break;
	}

	//�V�������(���[�h)�̏���������
	switch (mode)
	{
	case MODE_TITLE:		//�^�C�g�����
		InitTitle();
		break;

	case MODE_TUTORIAL:		//�`���[�g���A�����
		InitTutorial();
		break;

	case MODE_GAME:			//�Q�[�����
		InitGame();
		break;

	case MODE_RESULT:		//���U���g���
		InitResult();
		break;

	case MODE_RANKING:		//�����L���O���
		InitRanking();
		break;
	}

	g_mode = mode;			//���݂̉�ʃ��[�h��؂�ւ���
}

//*********************************************************************************
//���[�h�̎擾
//*********************************************************************************
MODE GetMode(void)
{
	return g_mode;
}

//---------------------------------------------------------------------------
// �f�o�C�X�̎擾
//---------------------------------------------------------------------------
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//---------------------------------------------------------------------------
// FPS�̕\��
//---------------------------------------------------------------------------
void DrawFPS(void)
{
	// �ϐ��錾
	RECT rect = { 0,0,SCREEN_WIDH,SCREEN_HEIGHT };
	char aStr[1256];
	char aSrrCopy[256];

	// �J�������̎擾
	Camera *pCamera = GetCamera();

	// ���f�����̎擾
	Player *pPlayer = GetPlayer();

	// ������̑��
	wsprintf(&aStr[0], "FPS %d\n", g_nCountFPS);

	// �J�����̎��_
	strcat(&aStr[0], "*-----�J�����̈ړ� [ W / A / S / D ]-----*\n");
	sprintf(&aSrrCopy[0], "  �J�����̎��_ | %0.1f | %0.1f | %0.1f |\n", pCamera->posV.x, pCamera->posV.y, pCamera->posV.z);
	strcat(&aStr[0], &aSrrCopy[0]);

	// �J�����̒����_
	sprintf(&aSrrCopy[0], "  �J�����̒����_ | %0.1f | %0.1f | %0.1f |\n", pCamera->posR.x, pCamera->posR.y, pCamera->posR.z);
	strcat(&aStr[0], &aSrrCopy[0]);

	// �J�����̒����_�܂ł̌���
	sprintf(&aSrrCopy[0], "  �����_�܂ł̌���(��) [Q / E | Z / C] | %0.3f\n", pCamera->rot.y);
	strcat(&aStr[0], &aSrrCopy[0]);
	sprintf(&aSrrCopy[0], "  �����_�܂ł̌���(��) [Y / H | U / J] | %0.3f\n\n", pCamera->rot.x);
	strcat(&aStr[0], &aSrrCopy[0]);

	// ���f���̈ʒu
	strcat(&aStr[0], "*-----���f���̈ړ�(�O�㍶�E) [ �� / �� / �� / �� ]-----*\n");
	strcat(&aStr[0], "*-----���f���̈ړ�(�㉺) [ I / K ]-----*\n");
	sprintf(&aSrrCopy[0], "  ���f���̈ʒu | %0.1f | %0.1f | %0.1f |\n", pPlayer->pos.x, pPlayer->pos.y, pPlayer->pos.z);
	strcat(&aStr[0], &aSrrCopy[0]);
	sprintf(&aSrrCopy[0], "  ���f���̌��� | %0.2f | %0.2f | %0.2f |\n", pPlayer->rot.x, pPlayer->rot.y, pPlayer->rot.z);
	strcat(&aStr[0], &aSrrCopy[0]);
	strcat(&aStr[0], "�e�̔��ˁ@[ SPACE ]\n");

	// �e�L�X�g�`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//---------------------------------------------------------------------------
// �E�B���h�E�n���h���̎擾
//---------------------------------------------------------------------------
HWND GetWnd(void)
{
	return g_hWnd;
}