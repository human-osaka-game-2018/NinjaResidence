#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <dinput.h>
#include <D3dx9core.h>
#include <dinput.h>
#include <time.h>
#include <stdio.h>
#include <crtdbg.h>
#include <map>

//画面サイズ
#define WIDTH 1280
#define HEIGHT 720
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

using std::map;
using std::string;

struct CUSTOMVERTEX
{
	FLOAT	x, y, z, rhw;
	DWORD	color;
	FLOAT	tu, tv;
};
struct CENTRAL_STATE
{
	float x, y, scaleX, scaleY;
};

enum KEYSTATE
{
	//! 押されていない
	KeyOff,
	//! 押されている
	KeyOn,
	//! 押し続けている
	KeyPush,
	//! 離された
	KeyRelease
};

HRESULT InitD3d(HWND hWnd);
HRESULT InitDinput(HWND hWnd);
void Render(HWND* hWnd, D3DPRESENT_PARAMETERS* g_D3dPresentParameters, HINSTANCE hInstance);
void Control(int* isRight);
int EndGame();
void LoadTexture();
void BuildDXDevice();
void AcquireKeyBoardState();
int GetSpecificKeyState(int KeyName);
void SetUpFont(int WordHeight, int WordWidth, string FontKey, LPCSTR FontName, int CharSet = DEFAULT_CHARSET);
void RevolveY(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, float tu = 0, float tv = 0, float scaleTu = 1, float scaleTv = 1);

extern string NinjaTexture;
extern LPDIRECT3D9			  g_pDirect3D;		//	Direct3Dのインターフェイス
extern map<string, LPDIRECT3DTEXTURE9>	  g_pTexture;	//	画像の情報を入れておく為のポインタ配列
extern IDirect3DDevice9*	  g_pD3Device;		//	Direct3Dのデバイス
extern D3DDISPLAYMODE		  g_D3DdisplayMode;
extern LPDIRECTINPUT8		  g_pDinput ;
extern LPDIRECTINPUTDEVICE8  g_pKeyDevice ;
extern D3DPRESENT_PARAMETERS g_D3dPresentParameters;
extern map<string, LPD3DXFONT> g_pFont;
extern CENTRAL_STATE ninja;
extern CENTRAL_STATE water;
extern CENTRAL_STATE stoneWall;
extern HWND hWnd;
//フルスクリーン関連
extern D3DPRESENT_PARAMETERS d3dppWin, d3dppFull;
extern bool WinMode;	//true:Window　false:Full
extern int isRight;
extern bool isBackStage;
extern bool DONDENGAESHI;