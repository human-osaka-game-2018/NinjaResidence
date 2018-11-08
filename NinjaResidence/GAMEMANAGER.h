#pragma once

#include "common.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define DISPLAY_WIDTH 1280
#define DISPLAY_HIGHT 720
#define SAFE_RELEASE(p) {if(p){(p)->Release(); (p)=NULL;}}

enum TEXTURE_NUM
{
	BLOCK_INTEGRATION_TEX,
	BACKGROUND_TEX,
	TEXMAX,
};

//Directx関係
extern LPDIRECT3DTEXTURE9 g_pTexture[TEXMAX]; //画像の情報を入れておく為のポインタ配列
extern LPDIRECTINPUTDEVICE8 pKeyDevice; //step4(キー入力の取得)に必要
extern LPDIRECTINPUT8 pDinput;			//step4(キー入力の取得)に必要
extern IDirect3DDevice9*  g_pD3Device; //Direct3Dのデバイス
extern IDirect3D9*    g_pDirect3D; //DIrect3Dのインターフェース
extern D3DPRESENT_PARAMETERS g_D3dPresentParameters;		//	パラメータ
extern D3DDISPLAYMODE		  g_D3DdisplayMode;

class GAMEMANAGER
{
private:
	
public:
	GAMEMANAGER();
	~GAMEMANAGER();
};