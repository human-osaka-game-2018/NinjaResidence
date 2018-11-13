#include "DirectXlib.h"
#include "GAMEMANAGER.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define SAFE_RELEASE(p) {if(p){(p)->Release(); (p)=NULL;}}

using std::map;
using std::string;

static map<string,LPDIRECT3DTEXTURE9> g_pTexture; //画像の情報を入れておく為のポインタ配列
static LPDIRECTINPUTDEVICE8 g_pKeyDevice = NULL; //step4(キー入力の取得)に必要
static LPDIRECTINPUT8 g_pDinput = NULL;			//step4(キー入力の取得)に必要
static IDirect3DDevice9*  g_pD3Device; //Direct3Dのデバイス
static IDirect3D9*    g_pDirect3D; //DIrect3Dのインターフェース
static D3DPRESENT_PARAMETERS g_D3dPresentParameters;		//	パラメータ
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
//ダイレクトインプットの初期化関
HRESULT InitDinput(HWND hWnd)
{
	HRESULT hr;

	//ダイレクトインプットのオブジェの作成
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&g_pDinput, NULL)))
	{
		return hr;
	}
	//ダイレクトインプットのデバイスの作成
	if (FAILED(hr = g_pDinput->CreateDevice(GUID_SysKeyboard,
		&g_pKeyDevice, NULL)))
	{
		return hr;
	}
	//デバイスをキーボードの設定
	if (FAILED(hr = g_pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}
	//協調レベル
	if (FAILED(hr = g_pKeyDevice->SetCooperativeLevel(
		hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return hr;
	}
	return S_OK;
}

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

//メモリ開放
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

//メインルーチン
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

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
		DISPLAY_HIGHT,							// Height（高さ）
		NULL,
		NULL,
		hInstance,							// アプリケーションインスタンスのハンドル
		NULL
	);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	//DirectX オブジェクトの生成
	g_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	//Display Mode の設定
	g_pDirect3D->GetAdapterDisplayMode(
		D3DADAPTER_DEFAULT,
		&g_D3DdisplayMode);
	ZeroMemory(&g_D3dPresentParameters,
		sizeof(D3DPRESENT_PARAMETERS));
	g_D3dPresentParameters.BackBufferFormat = g_D3DdisplayMode.Format;
	g_D3dPresentParameters.BackBufferCount = 1;
	g_D3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_D3dPresentParameters.Windowed = TRUE;

	//デバイスを作る
	g_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &g_D3dPresentParameters, &g_pD3Device);
	//DirectInput関係
	if (FAILED(InitDinput(hWnd)))
	{
		return 0;
	}
	//描画設定
	g_pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);//SRCの設定
	g_pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	//頂点に入れるデータを設定
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