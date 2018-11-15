#include "DirectXlib.h"
#include "GAMEMANAGER.h"


LPDIRECT3DTEXTURE9 g_pTexture[TEXMAX]; //画像の情報を入れておく為のポインタ配列
LPDIRECTINPUTDEVICE8 g_pKeyDevice = NULL; //step4(キー入力の取得)に必要
LPDIRECTINPUT8 g_pDinput = NULL;			//step4(キー入力の取得)に必要
IDirect3DDevice9*  g_pD3Device; //Direct3Dのデバイス
IDirect3D9*    g_pDirect3D; //DIrect3Dのインターフェース
D3DPRESENT_PARAMETERS g_D3dPresentParameters;		//	パラメータ
D3DDISPLAYMODE		  g_D3DdisplayMode;

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
	for (int i = 0; i <= TEXMAX; i++)
	{
		SAFE_RELEASE(g_pTexture[i]);
	}
	if (g_pKeyDevice)
	{
		g_pKeyDevice->Unacquire();
	}
	SAFE_RELEASE(g_pD3Device);
	SAFE_RELEASE(g_pDirect3D);
	SAFE_RELEASE(g_pKeyDevice);
	SAFE_RELEASE(g_pDinput);
}

//メインルーチン
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{

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