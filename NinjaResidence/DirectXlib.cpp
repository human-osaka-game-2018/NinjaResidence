#include "DirectXlib.h"
#include "GAMEMANAGER.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define SAFE_RELEASE(p) {if(p){(p)->Release(); (p)=NULL;}}

using std::map;
using std::string;
DirectX* pDirectX;


//メッセージ処理　ウィンドウプロシージャWndProcの設定
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


//メインルーチン
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	pDirectX = new DirectX;
	WNDCLASS Wndclass;
	HWND hWnd = NULL;
	//Windows初期化情報の設定
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc = WndProc;
	Wndclass.cbClsExtra = Wndclass.cbWndExtra = 0;
	Wndclass.hInstance = hInstance;
	Wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	Wndclass.lpszMenuName = NULL;
	Wndclass.lpszClassName = TEXT("忍者屋敷");	//クラス名
											//Windowの登録
	RegisterClass(&Wndclass);
	//Windowの生成
	hWnd = CreateWindow(
		TEXT("忍者屋敷"),								//ウィンドウのクラス名
		TEXT("忍者屋敷"), 							//ウィンドウのタイトル
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,	//ウィンドウスタイル
		CW_USEDEFAULT,						// ウィンドウの横方向の位置x
		CW_USEDEFAULT,						// ウィンドウの縦方向の位置y
		DISPLAY_WIDTH,							// Width（幅）
		DISPLAY_HEIGHT,							// Height（高さ）
		NULL,
		NULL,
		hInstance,							// アプリケーションインスタンスのハンドル
		NULL
	);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	bool WinMode = true;	//true:Window　false:Full
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
//メモリ開放
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

//ダイレクト3Dの初期化関数
HRESULT DirectX::InitD3d(HWND hWnd, LPCSTR FilePath)
{
	// 「Direct3D」オブジェクトの作成
	if (NULL == (m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		MessageBox(0, "Direct3Dの作成に失敗しました", "", MB_OK);
		return E_FAIL;
	}
	// 「DIRECT3Dデバイス」オブジェクトの作成
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
		MessageBox(0, "HALモードでDIRECT3Dデバイスを作成できません\nREFモードで再試行します", NULL, MB_OK);
		if (FAILED(m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
			D3DCREATE_MIXED_VERTEXPROCESSING,
			&d3dpp, &m_pD3Device)))
		{
			MessageBox(0, "DIRECT3Dデバイスの作成に失敗しました", NULL, MB_OK);
			return E_FAIL;
		}
	}
	//「テクスチャオブジェクト」の作成
	if (FAILED(D3DXCreateTextureFromFileEx(m_pD3Device, FilePath, 100, 100, 0, 0, D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT,
		0xff000000, NULL, NULL, &m_pTexture["Test"])))
	{
		MessageBox(0, "テクスチャの作成に失敗しました", "", MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

//ダイレクトインプットの初期化関
HRESULT DirectX::InitDinput(HWND hWnd)
{
	HRESULT hr;

	//ダイレクトインプットのオブジェの作成
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_pDinput, NULL)))
	{
		return hr;
	}
	//ダイレクトインプットのデバイスの作成
	if (FAILED(hr = m_pDinput->CreateDevice(GUID_SysKeyboard,
		&m_pKeyDevice, NULL)))
	{
		return hr;
	}
	//デバイスをキーボードの設定
	if (FAILED(hr = m_pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}
	//協調レベル
	if (FAILED(hr = m_pKeyDevice->SetCooperativeLevel(
		hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return hr;
	}
	return S_OK;
}

void DirectX::BuildDXDevice(HWND hWnd,bool WinMode, LPCSTR FilePath) {
	//ダイレクト３Dの初期化関数を呼ぶ
	if (FAILED(InitD3d(hWnd,FilePath)))
	{
		return;
	}
	//ダイレクトインプットの初期化関数を呼ぶ
	if (FAILED(InitDinput(hWnd)))
	{
		return;
	}

	//DirectX オブジェクトの生成
	m_pDirect3D = Direct3DCreate9(
		D3D_SDK_VERSION);

	//成功チェック
	if (m_pDirect3D == NULL)
	{
		//生成に失敗したら終了する
		return;
	}
	m_D3dPresentParameters = (WinMode) ? m_d3dppWin : m_d3dppFull;
	m_pDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&m_D3dPresentParameters, &m_pD3Device);
	//生成チェック
	if (m_pD3Device == NULL)
	{
		//生成に失敗したらDirectXオブジェクトを開放して終了する
		m_pDirect3D->Release();
		return;
	}
	//描画設定
	m_pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRCの設定
	m_pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//m_pD3Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//頂点に入れるデータを設定
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
*画像描画処理
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
		text,		// 描画テキスト
		-1,			// 全て表示
		&rect,		// 表示範囲
		TextFormat,	// 左寄せ
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
