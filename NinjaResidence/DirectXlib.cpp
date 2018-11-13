#include "DirectXlib.h"
#include "GAMEMANAGER.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define SAFE_RELEASE(p) {if(p){(p)->Release(); (p)=NULL;}}

using std::map;
using std::string;

static map<string,LPDIRECT3DTEXTURE9> g_pTexture; //�摜�̏������Ă����ׂ̃|�C���^�z��
static LPDIRECTINPUTDEVICE8 g_pKeyDevice = NULL; //step4(�L�[���͂̎擾)�ɕK�v
static LPDIRECTINPUT8 g_pDinput = NULL;			//step4(�L�[���͂̎擾)�ɕK�v
static IDirect3DDevice9*  g_pD3Device; //Direct3D�̃f�o�C�X
static IDirect3D9*    g_pDirect3D; //DIrect3D�̃C���^�[�t�F�[�X
static D3DPRESENT_PARAMETERS g_D3dPresentParameters;		//	�p�����[�^
static D3DDISPLAYMODE		  g_D3DdisplayMode;
static map<string, LPD3DXFONT> g_Font;

static BYTE KeyOldState[256];
static BYTE KeyState[256];



void LoadTexture(LPCSTR FilePath,string TextureKey){
	D3DXCreateTextureFromFile(
		g_pD3Device,
		FilePath,
		&g_pTexture[TextureKey]);
}
void ClearDisplay() {
	g_pD3Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0, 0);
}
void PresentsDevice() {
	g_pD3Device->Present(NULL, NULL, NULL, NULL);
}
void DrowTexture(string TextureKey,const CUSTOMVERTEX* TextureSize) {
	g_pD3Device->SetTexture(0, g_pTexture[TextureKey]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, TextureSize, sizeof(CUSTOMVERTEX));
}
void DrowSceneBegin() {
	g_pD3Device->BeginScene();
}
void DrowSceneEnd() {
	g_pD3Device->EndScene();
}
//�_�C���N�g�C���v�b�g�̏�������
HRESULT InitDinput(HWND hWnd)
{
	HRESULT hr;

	//�_�C���N�g�C���v�b�g�̃I�u�W�F�̍쐬
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&g_pDinput, NULL)))
	{
		return hr;
	}
	//�_�C���N�g�C���v�b�g�̃f�o�C�X�̍쐬
	if (FAILED(hr = g_pDinput->CreateDevice(GUID_SysKeyboard,
		&g_pKeyDevice, NULL)))
	{
		return hr;
	}
	//�f�o�C�X���L�[�{�[�h�̐ݒ�
	if (FAILED(hr = g_pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}
	//�������x��
	if (FAILED(hr = g_pKeyDevice->SetCooperativeLevel(
		hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return hr;
	}
	return S_OK;
}

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

//�������J��
void FreeDx()
{
	g_pTexture.clear();
	map<string, LPDIRECT3DTEXTURE9>().swap(g_pTexture);
	g_Font.clear();
	map<string, LPD3DXFONT>().swap(g_Font);
	if (g_pKeyDevice)
	{
		g_pKeyDevice->Unacquire();
	}
	SAFE_RELEASE(g_pKeyDevice);
	SAFE_RELEASE(g_pDinput);
	SAFE_RELEASE(g_pD3Device);
	SAFE_RELEASE(g_pDirect3D);
}

//���C�����[�`��
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

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
		DISPLAY_HIGHT,							// Height�i�����j
		NULL,
		NULL,
		hInstance,							// �A�v���P�[�V�����C���X�^���X�̃n���h��
		NULL
	);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	//DirectX �I�u�W�F�N�g�̐���
	g_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	//Display Mode �̐ݒ�
	g_pDirect3D->GetAdapterDisplayMode(
		D3DADAPTER_DEFAULT,
		&g_D3DdisplayMode);
	ZeroMemory(&g_D3dPresentParameters,
		sizeof(D3DPRESENT_PARAMETERS));
	g_D3dPresentParameters.BackBufferFormat = g_D3DdisplayMode.Format;
	g_D3dPresentParameters.BackBufferCount = 1;
	g_D3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_D3dPresentParameters.Windowed = TRUE;

	//�f�o�C�X�����
	g_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &g_D3dPresentParameters, &g_pD3Device);
	//DirectInput�֌W
	if (FAILED(InitDinput(hWnd)))
	{
		return 0;
	}
	//�`��ݒ�
	g_pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);//SRC�̐ݒ�
	g_pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	//���_�ɓ����f�[�^��ݒ�
	g_pD3Device->SetFVF(D3DFVF_CUSTOMVERTEX);

	MessageLoop();
}


/*
*DirectInput
*/
void CheckKeyStatus() {
	HRESULT hr = g_pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE)) {
		g_pKeyDevice->GetDeviceState(sizeof(KeyState), &KeyState);
		for (int i = 0; i < 0xED; i++) {
			if (KeyState[i] & 0x80)
			{
				if (KeyOldState[i] == KeyOn)
				{
					KeyOldState[i] = KeyOn;
					KeyState[i] = KeyOn;
				}
				else
				{
					KeyOldState[i] = KeyOn;
					KeyState[i] = KeyPush;
				}
			}
			else
			{
				if (KeyOldState[i] == KeyOn)
				{
					KeyOldState[i] = KeyOff;
					KeyState[i] = KeyRelease;
				}
				else
				{
					KeyOldState[i] = KeyOff;
					KeyState[i] = KeyOff;
				}
			}
		}
	}
}

int GetKeyStatus(int KeyName) {
	return KeyState[KeyName];
}