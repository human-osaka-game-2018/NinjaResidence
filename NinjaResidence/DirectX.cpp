/**
* @file DirectX.cpp
* @brief DirectX�֘A���s��
* @author Toshiya Matsuoka
*/
#include "DirectX.h"
#include "GAMEMANAGER.h"
#include <algorithm>

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define SAFE_RELEASE(p) {if(p){(p)->Release(); (p)=NULL;}}

using std::map;
using std::string;


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
	HRESULT hr = NULL;
	// �uDirect3D�v�I�u�W�F�N�g�̍쐬
	if (!(m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION)))
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
	d3dpp.Windowed = true;

	if (FAILED(hr = m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_MIXED_VERTEXPROCESSING,
		&d3dpp, &m_pD3Device)))
	{
		MessageBox(0, "HAL���[�h��DIRECT3D�f�o�C�X���쐬�ł��܂���\nREF���[�h�ōĎ��s���܂�", NULL, MB_OK);
		if (FAILED(hr = m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
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
		eraseTexture("Test");
		MessageBox(0, "�e�N�X�`���̍쐬�Ɏ��s���܂���", "", MB_OK);
		return E_FAIL;
	}
	eraseTexture("Test");
	return S_OK;
}

//�_�C���N�g�C���v�b�g�̏������֐�
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

HRESULT DirectX::BuildDXDevice(HWND hWnd, bool WinMode, LPCSTR FilePath) {
	//�_�C���N�g�RD�̏������֐����Ă�
	if (FAILED(InitD3d(hWnd, FilePath)))
	{
		return E_FAIL;
	}
	//�_�C���N�g�C���v�b�g�̏������֐����Ă�
	if (FAILED(InitDinput(hWnd)))
	{
		MessageBox(0, "DirectInputDevice�̍쐬�Ɏ��s���܂���", "", MB_OK);
		return E_FAIL;
	}

	//DirectX �I�u�W�F�N�g�̐���
	m_pDirect3D = Direct3DCreate9(
		D3D_SDK_VERSION);
	//�����`�F�b�N
	if (m_pDirect3D == NULL)
	{
		//�����Ɏ��s������I������
		MessageBox(0, "Direct3D�̍쐬�Ɏ��s���܂���", "", MB_OK);
		return E_FAIL;
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
		MessageBox(0, "Direct3D�̍쐬�Ɏ��s���܂���", "", MB_OK);
		return E_FAIL;
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
	return S_OK;
}

void DirectX::InitPresentParameters(HWND hWnd) {
	//Window
	ZeroMemory(&m_d3dppWin, sizeof(D3DPRESENT_PARAMETERS));
	m_d3dppWin.BackBufferWidth = 0;
	m_d3dppWin.BackBufferHeight = 0;
	m_d3dppWin.BackBufferFormat = D3DFMT_UNKNOWN;
	m_d3dppWin.BackBufferCount = 1;
	m_d3dppWin.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_d3dppWin.MultiSampleQuality = 0;
	m_d3dppWin.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dppWin.hDeviceWindow = hWnd;
	m_d3dppWin.Windowed = TRUE;
	m_d3dppWin.EnableAutoDepthStencil = FALSE;
	m_d3dppWin.AutoDepthStencilFormat = D3DFMT_A1R5G5B5;
	m_d3dppWin.Flags = 0;
	m_d3dppWin.FullScreen_RefreshRateInHz = 0;
	m_d3dppWin.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	//Full
	ZeroMemory(&m_d3dppFull, sizeof(D3DPRESENT_PARAMETERS));
	m_d3dppFull.BackBufferWidth = DISPLAY_WIDTH;
	m_d3dppFull.BackBufferHeight = DISPLAY_HEIGHT;
	m_d3dppFull.BackBufferFormat = D3DFMT_X8R8G8B8;
	m_d3dppFull.BackBufferCount = 1;
	m_d3dppFull.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_d3dppFull.MultiSampleQuality = 0;
	m_d3dppFull.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dppFull.hDeviceWindow = hWnd;
	m_d3dppFull.Windowed = FALSE;
	m_d3dppFull.EnableAutoDepthStencil = FALSE;
	m_d3dppFull.AutoDepthStencilFormat = D3DFMT_A1R5G5B5;
	m_d3dppFull.Flags = 0;
	m_d3dppFull.FullScreen_RefreshRateInHz = 0;
	m_d3dppFull.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
}
/*
*DirectInput
*/

void DirectX::CheckKeyStatus() {
	HRESULT hr = m_pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE)) {
		m_pKeyDevice->GetDeviceState(sizeof(m_KeyState), &m_KeyState);
		for (int i = 0; i < MaxKeyNumber; i++) {
			if (m_KeyState[i] & 0x80)
			{
				if (m_KeyOldState[i] == KeyOn)
				{
					m_KeyOldState[i] = KeyOn;
					m_KeyState[i] = KeyOn;
					continue;
				}
				else
				{
					m_KeyOldState[i] = KeyOn;
					m_KeyState[i] = KeyPush;
					continue;
				}
			}
			else
			{
				if (m_KeyOldState[i] == KeyOn)
				{
					m_KeyOldState[i] = KeyOff;
					m_KeyState[i] = KeyRelease;
					continue;
				}
				else
				{
					m_KeyOldState[i] = KeyOff;
					m_KeyState[i] = KeyOff;
					continue;
				}
			}
		}
	}
}

bool DirectX::PushAnykey() {
	BYTE* tmp = std::find_if(std::begin(m_KeyState), std::end(m_KeyState), [](BYTE m_KeyState) {return m_KeyState; });
	return *tmp;
}
/*
*
*/

void DirectX::ClearDisplay() {
	m_pD3Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0, 0);
}
void DirectX::PresentsDevice() {
	DeviceState = m_pD3Device->Present(NULL, NULL, NULL, NULL);
}
void DirectX::DrawSceneBegin() {
	m_pD3Device->BeginScene();
}
void DirectX::DrawSceneEnd() {
	m_pD3Device->EndScene();
}

void DirectX::RenderingBegin() {
	ClearDisplay();
	DrawSceneBegin();
}

void DirectX::RenderingEnd() {
	DrawSceneEnd();
	PresentsDevice();
}

/*
*�摜�`�揈��
*/

void DirectX::LoadTexture(LPCSTR FilePath, string TextureKey) {
	D3DXCreateTextureFromFile(
		m_pD3Device,
		FilePath,
		&m_pTexture[TextureKey]);
}
void DirectX::DrawTexture(string TextureKey, const CUSTOMVERTEX* TextureSize) {
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

void DirectX::DrawWord(RECT rect, LPCSTR text, string FontNumber, int TextFormat, DWORD color) {
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
HRESULT DirectX::ResetDevice(bool isWindowMode, RECT* WinRect, HWND hWnd) {
	if (isWindowMode) {
		m_D3dPresentParameters = m_d3dppWin;
	}
	else {
		m_D3dPresentParameters = m_d3dppFull;
		GetWindowRect(hWnd, WinRect);
	}
	return m_pD3Device->Reset(&m_D3dPresentParameters);
}

HRESULT DirectX::RecoverDevice(HWND hWnd, bool WinMode, LPCSTR FilePath) {

	HRESULT hr = NULL;
	// �uDirect3D�v�I�u�W�F�N�g�̍쐬
	if (!(m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		MessageBox(0, "Direct3D�̍쐬�Ɏ��s���܂���", "", MB_OK);
		return E_FAIL;
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
		MessageBox(0, "Direct3D�̍쐬�Ɏ��s���܂���", "", MB_OK);
		return E_FAIL;
	}


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
		//DirectX �I�u�W�F�N�g�̐���
	m_pDirect3D = Direct3DCreate9(
		D3D_SDK_VERSION);
	//�����`�F�b�N
	if (m_pDirect3D == NULL)
	{
		//�����Ɏ��s������I������
		MessageBox(0, "Direct3D�̍쐬�Ɏ��s���܂���", "", MB_OK);
		return E_FAIL;
	}

	//�u�e�N�X�`���I�u�W�F�N�g�v�̍쐬
	if (FAILED(D3DXCreateTextureFromFileEx(m_pD3Device, FilePath, 100, 100, 0, 0, D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT,
		0xff000000, NULL, NULL, &m_pTexture["Test"])))
	{
		eraseTexture("Test");
		MessageBox(0, "�e�N�X�`���̍쐬�Ɏ��s���܂���", "", MB_OK);
		return E_FAIL;
	}
	eraseTexture("Test");


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
	return S_OK;

}
