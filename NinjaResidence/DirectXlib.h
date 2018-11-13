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
#define DISPLAY_HEIGHT 720

class DirectX {
public:
	DirectX();
	~DirectX();

	/*
	* @brief 画像表示
	*/
	void ClearDisplay();
	/*
	* @brief 画像表示
	*/
	void PresentsDevice();

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
	/*
	* @brief 画像読み込み
	* @param FilePath 画像ファイルパス
	* @param TextureKey 画像の格納キー
	*/
	void LoadTexture(LPCSTR FilePath, std::string TextureKey);
	/*
	* @brief 画像表示
	* @param TextureKey 画像の格納キー
	* @param TextureSize 頂点情報
	*/
	void DrowTexture(std::string TextureKey, const CUSTOMVERTEX* TextureSize);
	/*
	* @brief 画像消去
	* @param TextureKey 画像の格納キー
	*/
	void eraseTexture(std::string TexKey);
	/*
	* @brief 画像全消去
	*/
	void ClearTexture();
	/**
	* @brief DXフォント描画設定
	* @param Texts 表示内容
	* @param Vertex 表示範囲
	* @param FontNum 表示文字設定の格納キー
	* @param TextFormat フォーマット
	* @param color 色
	*/
	void DrowWord(RECT rect, LPCSTR text, std::string FontNumber, int TextFormat = DT_LEFT, DWORD color = 0xff000000);
	/**
	* @brief DXフォント文字設定
	* @param WordHeight 文字の高さ
	* @param WordWidth 文字の幅
	* @param FontKey 表示文字設定の格納先配列番号
	* @param FontName 使用するフォント名
	* @param CharSet キャラセット（英字ならDEFAULT_CHARSET，シフトJISならSHIFTJIS_CHARSET）
	*/
	void SetFont(int height, int width, std::string FontKey, LPCSTR FontType = "ＭＳ　ゴシック", int CharSet = DEFAULT_CHARSET);
	/**
	* @brief DXフォント消去
	* @param FontKey 表示文字設定の格納先配列番号
	*/
	void eraseFont(std::string FontKey);
	/**
	* @brief DXフォント全消去
	*/
	void ClearFont();


	void BuildDXDevice(HWND hWnd, bool WinMode, LPCSTR FilePath);
	void InitPresentParameters(HWND hWnd);
private:
	std::map<std::string, LPDIRECT3DTEXTURE9> m_pTexture; //画像の情報を入れておく為のポインタ配列
	LPDIRECTINPUTDEVICE8 m_pKeyDevice = NULL; 
	LPDIRECTINPUT8 m_pDinput = NULL;			
	IDirect3DDevice9*  m_pD3Device; //Direct3Dのデバイス
	IDirect3D9*    m_pDirect3D; //DIrect3Dのインターフェース
	D3DPRESENT_PARAMETERS m_D3dPresentParameters;		//	パラメータ
	D3DDISPLAYMODE		  m_D3DdisplayMode;
	std::map<std::string, LPD3DXFONT> m_pFont;
	D3DPRESENT_PARAMETERS m_d3dppWin, m_d3dppFull;

	BYTE m_KeyOldState[256];
	BYTE m_KeyState[256];

	HRESULT InitD3d(HWND hWnd, LPCSTR FilePath);
	HRESULT InitDinput(HWND hWnd);
	void ReleaseDx();
};

extern DirectX* pDirectX;
