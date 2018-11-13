#pragma once

#include <windows.h>
#include <d3dx9.h>
#include <mmsystem.h>
#include <dinput.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cstdio>
#include <cstdlib>
#include <map>

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dx9.lib")
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

struct CUSTOMVERTEX
{
	FLOAT	x, y, z, rhw;
	DWORD	color;
	FLOAT	tu, tv;
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

#define DISPLAY_WIDTH 1280
#define DISPLAY_HIGHT 720
/*
* @brief 画像読み込み
* @param FilePath 画像ファイルパス
* @param TextureKey 画像の格納キー
*/
void LoadTexture(LPCSTR FilePath, std::string TextureKey);
/*
* @brief 画像表示
*/
void ClearDisplay();
/*
* @brief 画像表示
*/
void PresentsDevice();
/*
* @brief 画像表示
* @param TextureKey 画像の格納キー
* @param TextureSize 頂点情報
*/
void DrowTexture(std::string TextureKey, const CUSTOMVERTEX* TextureSize);
/**
*@brief 描画開始関数
* @sa DrowSceneEnd()
* @detail 上記関数とセットで使うこと
*/
void DrowSceneBegin();
/**
* @brief 描画終了関数
* @sa DrowSceneBegin()
* @detail 上記関数とセットで使うこと
*/
void DrowSceneEnd();
/**
* @brief キーボード情報の読み取り
*/
void CheckKeyStatus();
/**
* @brief 画像読み込み
* @param pTextureName 読み込む画像ファイル名
* @param TexKey 画像の格納キー
*/
int GetKeyStatus(int KeyName);
void FreeDx();


//Directx関係
//extern std::map<std::string, LPDIRECT3DTEXTURE9> g_pTexture; //画像の情報を入れておく為のポインタ配列
//extern LPDIRECTINPUTDEVICE8 g_pKeyDevice; //step4(キー入力の取得)に必要
//extern LPDIRECTINPUT8 g_pDinput;			//step4(キー入力の取得)に必要
//extern IDirect3DDevice9*  g_pD3Device; //Direct3Dのデバイス
//extern IDirect3D9*    g_pDirect3D; //DIrect3Dのインターフェース
//extern D3DPRESENT_PARAMETERS g_D3dPresentParameters;		//	パラメータ
//extern D3DDISPLAYMODE		  g_D3DdisplayMode;
//extern void FreeDx();

