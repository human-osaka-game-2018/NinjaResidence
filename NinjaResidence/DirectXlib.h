#pragma once

#include <windows.h>
#include <d3dx9.h>
#include <mmsystem.h>
#include <dinput.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dx9.lib")

struct CUSTOMVERTEX
{
	FLOAT	x, y, z, rhw;
	DWORD	color;
	FLOAT	tu, tv;
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define DISPLAY_WIDTH 1280
#define DISPLAY_HIGHT 720
#define SAFE_RELEASE(p) {if(p){(p)->Release(); (p)=NULL;}}

enum TEXTURE_NUM
{
	BLOCK_INTEGRATION_TEX,
	CHARA_INTEGRATION_TEX,
	BACKGROUND_TEX,
	TEXMAX,
};

//Directx�֌W
extern LPDIRECT3DTEXTURE9 g_pTexture[TEXMAX]; //�摜�̏������Ă����ׂ̃|�C���^�z��
extern LPDIRECTINPUTDEVICE8 g_pKeyDevice; //step4(�L�[���͂̎擾)�ɕK�v
extern LPDIRECTINPUT8 g_pDinput;			//step4(�L�[���͂̎擾)�ɕK�v
extern IDirect3DDevice9*  g_pD3Device; //Direct3D�̃f�o�C�X
extern IDirect3D9*    g_pDirect3D; //DIrect3D�̃C���^�[�t�F�[�X
extern D3DPRESENT_PARAMETERS g_D3dPresentParameters;		//	�p�����[�^
extern D3DDISPLAYMODE		  g_D3DdisplayMode;
extern void FreeDx();

