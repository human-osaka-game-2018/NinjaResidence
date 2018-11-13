#include "DirectXlib.h"
#include "GAMEMANAGER.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define SAFE_RELEASE(p) {if(p){(p)->Release(); (p)=NULL;}}

using std::map;
using std::string;
DirectX* pDirectX;


//���b�Z�[�W�����@�E�B���h�E�v���V�[�W��WndProc�̐ݒ�
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wp, lp);
}


//���C�����[�`��
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	pDirectX = new DirectX;
	WNDCLASS Wndclass;
	HWND hWnd = NULL;
	//Windows���������̐ݒ�
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc = WndProc;
	Wndclass.cbClsExtra = Wndclass.cbWndExtra = 0;
	Wndclass.hInstance = hInstance;
	Wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	Wndclass.lpszMenuName = NULL;
	Wndclass.lpszClassName = TEXT("�E�҉��~");	//�N���X��
											//Window�̓o�^
	RegisterClass(&Wndclass);
	//Window�̐���
	hWnd = CreateWindow(
		TEXT("�E�҉��~"),								//�E�B���h�E�̃N���X��
		TEXT("�E�҉��~"), 							//�E�B���h�E�̃^�C�g��
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,	//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,						// �E�B���h�E�̉������̈ʒux
		CW_USEDEFAULT,						// �E�B���h�E�̏c�����̈ʒuy
		DISPLAY_WIDTH,							// Width�i���j
		DISPLAY_HEIGHT,							// Height�i�����j
		NULL,
		NULL,
		hInstance,							// �A�v���P�[�V�����C���X�^���X�̃n���h��
		NULL
	);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	bool WinMode = true;	//true:Window�@false:Full
	pDirectX->InitPresentParameters(hWnd);
	pDirectX->BuildDXDevice(hWnd, WinMode, "texture/Block_Integration.png");

	MessageLoop();
	delete pDirectX;
}



DirectX::DirectX() {

}
DirectX::~DirectX() {
	ReleaseDx();
}
//�������J��
void DirectX::ReleaseDx()
{
	m_pTexture.clear();
	map<string, LPDIRECT3DTEXTURE9>().swap(m_pTexture);
	m_pFont.clear();
	map<string, LPD3DXFONT>().swap(m_pFont);
	if (m_pKeyDevice)
	{
		m_pKeyDevice->Unacquire();
	}
	SAFE_RELEASE(m_pKeyDevice);
	SAFE_RELEASE(m_pDinput);
	SAFE_RELEASE(m_pD3Device);
	SAFE_RELEASE(m_pDirect3D);
}

//�_�C���N�g3D�̏������֐�
HRESULT DirectX::InitD3d(HWND hWnd, LPCSTR FilePath)
{
	// �uDirect3D�v�I�u�W�F�N�g�̍쐬
	if (NULL == (m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		MessageBox(0, "Direct3D�̍쐬�Ɏ��s���܂���", "", MB_OK);
		return E_FAIL;
	}
	// �uDIRECT3D�f�o�C�X�v�I�u�W�F�N�g�̍쐬
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;

	if (FAILED(m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_MIXED_VERTEXPROCESSING,
		&d3dpp, &m_pD3Device)))
	{
		MessageBox(0, "HAL���[�h��DIRECT3D�f�o�C�X���쐬�ł��܂���\nREF���[�h�ōĎ��s���܂�", NULL, MB_OK);
		if (FAILED(m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
			D3DCREATE_MIXED_VERTEXPROCESSING,
			&d3dpp, &m_pD3Device)))
		{
			MessageBox(0, "DIRECT3D�f�o�C�X�̍쐬�Ɏ��s���܂���", NULL, MB_OK);
			return E_FAIL;
		}
	}
	//�u�e�N�X�`���I�u�W�F�N�g�v�̍쐬
	if (FAILED(D3DXCreateTextureFromFileEx(m_pD3Device, FilePath, 100, 100, 0, 0, D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT,
		0xff000000, NULL, NULL, &m_pTexture["Test"])))
	{
		MessageBox(0, "�e�N�X�`���̍쐬�Ɏ��s���܂���", "", MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

//�_�C���N�g�C���v�b�g�̏�������
HRESULT DirectX::InitDinput(HWND hWnd)
{
	HRESULT hr;

	//�_�C���N�g�C���v�b�g�̃I�u�W�F�̍쐬
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_pDinput, NULL)))
	{
		return hr;
	}
	//�_�C���N�g�C���v�b�g�̃f�o�C�X�̍쐬
	if (FAILED(hr = m_pDinput->CreateDevice(GUID_SysKeyboard,
		&m_pKeyDevice, NULL)))
	{
		return hr;
	}
	//�f�o�C�X���L�[�{�[�h�̐ݒ�
	if (FAILED(hr = m_pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}
	//�������x��
	if (FAILED(hr = m_pKeyDevice->SetCooperativeLevel(
		hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return hr;
	}
	return S_OK;
}

void DirectX::BuildDXDevice(HWND hWnd,bool WinMode, LPCSTR FilePath) {
	//�_�C���N�g�RD�̏������֐����Ă�
	if (FAILED(InitD3d(hWnd,FilePath)))
	{
		return;
	}
	//�_�C���N�g�C���v�b�g�̏������֐����Ă�
	if (FAILED(InitDinput(hWnd)))
	{
		return;
	}

	//DirectX �I�u�W�F�N�g�̐���
	m_pDirect3D = Direct3DCreate9(
		D3D_SDK_VERSION);

	//�����`�F�b�N
	if (m_pDirect3D == NULL)
	{
		//�����Ɏ��s������I������
		return;
	}
	m_D3dPresentParameters = (WinMode) ? m_d3dppWin : m_d3dppFull;
	m_pDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&m_D3dPresentParameters, &m_pD3Device);
	//�����`�F�b�N
	if (m_pD3Device == NULL)
	{
		//�����Ɏ��s������DirectX�I�u�W�F�N�g���J�����ďI������
		m_pDirect3D->Release();
		return;
	}
	//�`��ݒ�
	m_pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRC�̐ݒ�
	m_pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//m_pD3Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//���_�ɓ����f�[�^��ݒ�
	m_pD3Device->SetFVF(D3DFVF_CUSTOMVERTEX);
}

void DirectX::InitPresentParameters(HWND hWnd) {
	//Window
	ZeroMemory(&pDirectX->m_d3dppWin, sizeof(D3DPRESENT_PARAMETERS));
	pDirectX->m_d3dppWin.BackBufferWidth = 0;
	pDirectX->m_d3dppWin.BackBufferHeight = 0;
	pDirectX->m_d3dppWin.BackBufferFormat = D3DFMT_UNKNOWN;
	pDirectX->m_d3dppWin.BackBufferCount = 1;
	pDirectX->m_d3dppWin.MultiSampleType = D3DMULTISAMPLE_NONE;
	pDirectX->m_d3dppWin.MultiSampleQuality = 0;
	pDirectX->m_d3dppWin.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pDirectX->m_d3dppWin.hDeviceWindow = hWnd;
	pDirectX->m_d3dppWin.Windowed = TRUE;
	pDirectX->m_d3dppWin.EnableAutoDepthStencil = FALSE;
	pDirectX->m_d3dppWin.AutoDepthStencilFormat = D3DFMT_A1R5G5B5;
	pDirectX->m_d3dppWin.Flags = 0;
	pDirectX->m_d3dppWin.FullScreen_RefreshRateInHz = 0;
	pDirectX->m_d3dppWin.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	//Full
	ZeroMemory(&pDirectX->m_d3dppFull, sizeof(D3DPRESENT_PARAMETERS));
	pDirectX->m_d3dppFull.BackBufferWidth = DISPLAY_WIDTH;
	pDirectX->m_d3dppFull.BackBufferHeight = DISPLAY_HEIGHT;
	pDirectX->m_d3dppFull.BackBufferFormat = D3DFMT_X8R8G8B8;
	pDirectX->m_d3dppFull.BackBufferCount = 1;
	pDirectX->m_d3dppFull.MultiSampleType = D3DMULTISAMPLE_NONE;
	pDirectX->m_d3dppFull.MultiSampleQuality = 0;
	pDirectX->m_d3dppFull.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pDirectX->m_d3dppFull.hDeviceWindow = hWnd;
	pDirectX->m_d3dppFull.Windowed = FALSE;
	pDirectX->m_d3dppFull.EnableAutoDepthStencil = FALSE;
	pDirectX->m_d3dppFull.AutoDepthStencilFormat = D3DFMT_A1R5G5B5;
	pDirectX->m_d3dppFull.Flags = 0;
	pDirectX->m_d3dppFull.FullScreen_RefreshRateInHz = 0;
	pDirectX->m_d3dppFull.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;


}
/*
*DirectInput
*/
void DirectX::CheckKeyStatus() {
	HRESULT hr = m_pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE)) {
		m_pKeyDevice->GetDeviceState(sizeof(m_KeyState), &m_KeyState);
		for (int i = 0; i < 0xED; i++) {
			if (m_KeyState[i] & 0x80)
			{
				if (m_KeyOldState[i] == KeyOn)
				{
					m_KeyOldState[i] = KeyOn;
					m_KeyState[i] = KeyOn;
				}
				else
				{
					m_KeyOldState[i] = KeyOn;
					m_KeyState[i] = KeyPush;
				}
			}
			else
			{
				if (m_KeyOldState[i] == KeyOn)
				{
					m_KeyOldState[i] = KeyOff;
					m_KeyState[i] = KeyRelease;
				}
				else
				{
					m_KeyOldState[i] = KeyOff;
					m_KeyState[i] = KeyOff;
				}
			}
		}
	}
}

int DirectX::GetKeyStatus(int KeyName) {
	return m_KeyState[KeyName];
}

/*
*�摜�`�揈��
*/
void DirectX::ClearDisplay() {
	m_pD3Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0, 0);
}
void DirectX::PresentsDevice() {
	m_pD3Device->Present(NULL, NULL, NULL, NULL);
}
void DirectX::DrowSceneBegin() {
	m_pD3Device->BeginScene();
}
void DirectX::DrowSceneEnd() {
	m_pD3Device->EndScene();
}

void DirectX::LoadTexture(LPCSTR FilePath, string TextureKey) {
	D3DXCreateTextureFromFile(
		m_pD3Device,
		FilePath,
		&m_pTexture[TextureKey]);
}
void DirectX::DrowTexture(string TextureKey, const CUSTOMVERTEX* TextureSize) {
	m_pD3Device->SetTexture(0, m_pTexture[TextureKey]);
	m_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, TextureSize, sizeof(CUSTOMVERTEX));
}
void DirectX::eraseTexture(string TexKey) {
	m_pTexture.erase(TexKey);
}
void DirectX::ClearTexture() {
	m_pTexture.clear();
	map<string, LPDIRECT3DTEXTURE9>().swap(m_pTexture);

}
/*
*DxFont
*/
void DirectX::DrowWord(RECT rect, LPCSTR text, string FontNumber, int TextFormat, DWORD color) {
	m_pFont[FontNumber]->DrawText(
		NULL,		// NULL
		text,		// �`��e�L�X�g
		-1,			// �S�ĕ\��
		&rect,		// �\���͈�
		TextFormat,	// ����
		color		// color
	);
}
void DirectX::SetFont(int height, int width, string FontKey, LPCSTR FontType, int CharSet) {
	D3DXCreateFont(
		m_pD3Device,
		height,
		width,
		FW_DEMIBOLD,
		NULL,
		FALSE,
		CharSet,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		FIXED_PITCH | FF_SCRIPT,
		FontType,
		&m_pFont[FontKey]);
}
void DirectX::eraseFont(string FontKey) {
	m_pFont.erase(FontKey);
}
void DirectX::ClearFont() {
	m_pFont.clear();
	map<string, LPD3DXFONT>().swap(m_pFont);

}
