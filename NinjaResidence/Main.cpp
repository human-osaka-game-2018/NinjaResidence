#include "Main.h"
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib,"SoundLib.lib")

SoundLib::SoundsManager soundsManager;
LPDIRECT3D9			  g_pDirect3D;		//	Direct3Dのインターフェイス
map<string,LPDIRECT3DTEXTURE9>	  g_pTexture;	//	画像の情報を入れておく為のポインタ配列
IDirect3DDevice9*	  g_pD3Device;		//	Direct3Dのデバイス
D3DDISPLAYMODE		  g_D3DdisplayMode;
LPDIRECTINPUT8		  g_pDinput = NULL;
LPDIRECTINPUTDEVICE8  g_pKeyDevice = NULL;
D3DPRESENT_PARAMETERS g_D3dPresentParameters;
HWND hWnd = NULL;
map<string, LPD3DXFONT> g_pFont;
void FreeDx();
//フルスクリーン関連
D3DPRESENT_PARAMETERS d3dppWin, d3dppFull;
RECT WinRect;			//Window Mode での位置大きさ
bool WinAct=false;
bool WinMode = true;	//true:Window　false:Full
bool DeviceLost=false;
//-------------------------------------------------------------
//
// 画面モードの変更
// 
//-------------------------------------------------------------
void ChangeDisplayMode(void)
{
	HRESULT hr = NULL;
	WinMode = !WinMode;

	if (WinMode) {
		g_D3dPresentParameters = d3dppWin;
	}
	else {
		g_D3dPresentParameters = d3dppFull;
		GetWindowRect(hWnd, &WinRect);
	}
	hr = g_pD3Device->Reset(&g_D3dPresentParameters);
	FreeDx();
	soundsManager.Initialize();
	BuildDXDevice();
	//画像の引用
	LoadTexture();
	LoadFont();

	if (FAILED(hr)) {
		if (hr == D3DERR_DEVICELOST) {
			DeviceLost = true;
		}
		if (hr == D3DERR_DRIVERINTERNALERROR) {
			DestroyWindow(hWnd);
		}
		return;
	}

	if (WinMode) {
		SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
		SetWindowPos(hWnd, HWND_NOTOPMOST,
			WinRect.left, WinRect.top,
			WinRect.right - WinRect.left,
			WinRect.bottom - WinRect.top,
			SWP_SHOWWINDOW);
	}
	else {
		SetWindowLong(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
	}
}
//-------------------------------------------------------------
//
// ウインドウ・サイズの変更
//
//-------------------------------------------------------------
HRESULT ChangeWindowSize(void)
{
	// ウインドウのクライアント領域に合わせる

	HRESULT hr = g_pD3Device->Reset(&g_D3dPresentParameters);
	if (FAILED(hr)) {
		if (hr == D3DERR_DEVICELOST) {
			DeviceLost = true;
		}
	}
	else {
		DestroyWindow(hWnd);
	}

	// ビューポートの設定
	D3DVIEWPORT9 vp;
	vp.X = 0;
	vp.Y = 0;
	vp.Width = g_D3dPresentParameters.BackBufferWidth;
	vp.Height = g_D3dPresentParameters.BackBufferHeight;
	vp.MinZ = 0.0f;
	vp.MaxZ = 1.0f;
	hr = g_pD3Device->SetViewport(&vp);
	if (FAILED(hr)) {
		DestroyWindow(hWnd);
	}
	return hr;
}

void LoadSound() {
	soundsManager.AddFile("Sound/dart1.mp3", "THROW");
	soundsManager.SetVolume("THROW", 75);
	soundsManager.AddFile("Sound/nc62985.wav", "DECISION");
	soundsManager.AddFile("Sound/nc62985.wav", "DECISION2");
	soundsManager.AddFile("Sound/nc52970.wav", "CLEAR");
	soundsManager.AddFile("Sound/nc80935.wav", "SLASH");
	soundsManager.AddFile("Sound/nc100104.wav", "DONDENGAESHI");

}
//ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_SIZE:
		if (g_D3dPresentParameters.Windowed != TRUE)
			break;

		if (g_pD3Device || wp == SIZE_MINIMIZED)
			break;
		g_D3dPresentParameters.BackBufferWidth = LOWORD(lp);
		g_D3dPresentParameters.BackBufferHeight = HIWORD(lp);
		if (DeviceLost)
			break;
		if (wp == SIZE_MAXIMIZED || wp == SIZE_RESTORED)
			ChangeWindowSize();
		break;

	case WM_SETCURSOR:
		if (g_D3dPresentParameters.Windowed != TRUE) {
			SetCursor(NULL);
			return 1;
		}
		break;

	case WM_KEYDOWN:
		 //キー入力の処理
		switch (wp) {
		case VK_ESCAPE: // [ESCAPE]キーでウインドウを閉じる
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		}
		break;
	case WM_SYSKEYDOWN:     // Alt + 特殊キーの処理に使う
		switch (wp) {
		case VK_RETURN:     // Alt + Enterを押すと切り替え
			ChangeDisplayMode();
			break;
		default:
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, msg, wp, lp);
}

/**
*メモリ開放
*/
void FreeDx()
{
	g_pTexture.clear();
	map<string, LPDIRECT3DTEXTURE9>().swap(g_pTexture);
	g_pFont.clear();
	map<string, LPD3DXFONT>().swap(g_pFont);

	if (g_pKeyDevice)
	{
		g_pKeyDevice->Unacquire();
	}
	SAFE_RELEASE(g_pKeyDevice);
	SAFE_RELEASE(g_pDinput);

	SAFE_RELEASE(g_pDirect3D);
	SAFE_RELEASE(g_pD3Device);

}
void BuildDXDevice() {
	//ダイレクト３Dの初期化関数を呼ぶ
	if (FAILED(InitD3d(hWnd)))
	{
		return;
	}
	//ダイレクトインプットの初期化関数を呼ぶ
	if (FAILED(InitDinput(hWnd)))
	{
		return;
	}

	//DirectX オブジェクトの生成
	g_pDirect3D = Direct3DCreate9(
		D3D_SDK_VERSION);

	//成功チェック
	if (g_pDirect3D == NULL)
	{
		//生成に失敗したら終了する
		return;
	}
	g_D3dPresentParameters = (WinMode) ? d3dppWin : d3dppFull;
	g_pDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&g_D3dPresentParameters, &g_pD3Device);
	//生成チェック
	if (g_pD3Device == NULL)
	{
		//生成に失敗したらDirectXオブジェクトを開放して終了する
		g_pDirect3D->Release();
		return;
	}
	//描画設定
	g_pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRCの設定
	g_pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//g_pD3Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//頂点に入れるデータを設定
	g_pD3Device->SetFVF(D3DFVF_CUSTOMVERTEX);
}

HRESULT InitD3d(HWND hWnd)
{
	// 「Direct3D」オブジェクトの作成
	if (NULL == (g_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION)))
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

	if (FAILED(g_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_MIXED_VERTEXPROCESSING,
		&d3dpp, &g_pD3Device)))
	{
		MessageBox(0, "HALモードでDIRECT3Dデバイスを作成できません\nREFモードで再試行します", NULL, MB_OK);
		if (FAILED(g_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
			D3DCREATE_MIXED_VERTEXPROCESSING,
			&d3dpp, &g_pD3Device)))
		{
			MessageBox(0, "DIRECT3Dデバイスの作成に失敗しました", NULL, MB_OK);
			return E_FAIL;
		}
	}
	LPDIRECT3DTEXTURE9	  pTexture;
	//「テクスチャオブジェクト」の作成
	if (FAILED(D3DXCreateTextureFromFileEx(g_pD3Device, "Texture/woodWall.jpg", 100, 100, 0, 0, D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,
		0xff000000, NULL, NULL, &pTexture)))
	{
		MessageBox(0, "テクスチャの作成に失敗しました", "", MB_OK);
		return E_FAIL;
	}
	pTexture->Release();
	return S_OK;
}

//DirectInput
HRESULT InitDinput(HWND hWnd) {
	HRESULT hr;
	// 「DirectInput」オブジェクトの作成
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&g_pDinput, NULL)))
	{
		return hr;
	}
	// 「DirectInputデバイス」オブジェクトの作成
	if (FAILED(hr = g_pDinput->CreateDevice(GUID_SysKeyboard,
		&g_pKeyDevice, NULL)))
	{
		return hr;
	}
	// デバイスをキーボードに設定
	if (FAILED(hr = g_pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}
	// 協調レベルの設定
	if (FAILED(hr = g_pKeyDevice->SetCooperativeLevel(
		hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return hr;
	}
	// デバイスを「取得」する
	g_pKeyDevice->Acquire();
	return S_OK;
}


INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstance, LPSTR szStr, INT iCmdShow)
{
	

	MSG msg;
	WNDCLASS Wndclass;
	static bool GAMEOPEN = true;
	soundsManager.Initialize();
	//Windows情報の設定
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc = WndProc;
	Wndclass.cbClsExtra = Wndclass.cbWndExtra = 0;
	Wndclass.hInstance = hInst;
	Wndclass.hIcon = LoadIcon(hInst, NULL);
	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	Wndclass.lpszMenuName = NULL;
	Wndclass.lpszClassName = TEXT("NINJA");	//クラス名

	RegisterClass(&Wndclass);//Windowの登録

	//Windowの生成
	hWnd = CreateWindow(
		TEXT("NINJA"),						//ウィンドウのクラス名
		TEXT("NINJA"),  				//ウィンドウのタイトル
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,	//ウィンドウスタイル
		CW_USEDEFAULT,						// ウィンドウの横方向の位置x
		CW_USEDEFAULT,						// ウィンドウの縦方向の位置y
		WIDTH,							// Width（幅）
		HEIGHT,							// Height（高さ）
		NULL,
		NULL,
		hInstance,							// アプリケーションインスタンスのハンドル
		NULL
	);
	//Window
	ZeroMemory(&d3dppWin, sizeof(D3DPRESENT_PARAMETERS));
	d3dppWin.BackBufferWidth = 0;
	d3dppWin.BackBufferHeight = 0;
	d3dppWin.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dppWin.BackBufferCount = 1;
	d3dppWin.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dppWin.MultiSampleQuality = 0;
	d3dppWin.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dppWin.hDeviceWindow = hWnd;
	d3dppWin.Windowed = TRUE;
	d3dppWin.EnableAutoDepthStencil = FALSE;
	d3dppWin.AutoDepthStencilFormat = D3DFMT_A1R5G5B5;
	d3dppWin.Flags = 0;
	d3dppWin.FullScreen_RefreshRateInHz = 0;
	d3dppWin.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	//Full
	ZeroMemory(&d3dppFull, sizeof(D3DPRESENT_PARAMETERS));
	d3dppFull.BackBufferWidth = WIDTH;
	d3dppFull.BackBufferHeight = HEIGHT;
	d3dppFull.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dppFull.BackBufferCount = 1;
	d3dppFull.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dppFull.MultiSampleQuality = 0;
	d3dppFull.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dppFull.hDeviceWindow = hWnd;
	d3dppFull.Windowed = FALSE;
	d3dppFull.EnableAutoDepthStencil = FALSE;
	d3dppFull.AutoDepthStencilFormat = D3DFMT_A1R5G5B5;
	d3dppFull.Flags = 0;
	d3dppFull.FullScreen_RefreshRateInHz = 0;
	d3dppFull.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	BuildDXDevice();

	//画像の引用
	LoadTexture();
	LoadFont();
	LoadSound();
	DWORD SyncOld = timeGetTime();	//	システム時間を取得
	DWORD SyncNow;

	timeBeginPeriod(1);
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		Sleep(1);
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			SyncNow = timeGetTime();
			if (SyncNow - SyncOld >= 1000 / 60)
			{//60フレームループしたい処理
				msg.message = EndGame();
				Control(&isRight); 
				Render(&hWnd,&g_D3dPresentParameters, hInstance);
				SyncOld = SyncNow;
			}
		}
	}
	timeEndPeriod(1);

	FreeDx();
	return (int)msg.wParam;
}


int EndGame() {

	if (KeyRelease == GetSpecificKeyState(DIK_ESCAPE)) {
		return WM_QUIT;
	}
	return WM_NULL;

}

