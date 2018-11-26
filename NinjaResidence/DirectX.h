/**
* @file DirectX.h
* @brief DirectX関連を行う
* @author Toshiya Matsuoka
*/
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


// TODO:Singletonにする
/**
* @class DirectX
* @brief DirectX
*/
class DirectX {
public:
	DirectX();
	~DirectX();

	/**
	* @brief ディスプレイクリア
	*/
	void ClearDisplay();
	/**
	* @brief デバイスプレゼント
	*/
	void PresentsDevice();

	/**
	*@brief 描画開始関数
	* @sa DrowSceneEnd()
	* @detail 上記関数とセットで使うこと
	*/
	void DrawSceneBegin();
	/**
	* @brief 描画終了関数
	* @sa DrowSceneBegin()
	* @detail 上記関数とセットで使うこと
	*/
	void DrawSceneEnd();


	/**
	*@brief 描画開始関数
	* @sa RenderingEnd()
	* @detail 上記関数とセットで使うこと
	* ClearDisplayとDrowSceneBeginを行う
	*/
	void RenderingBegin();
	/**
	* @brief 描画終了関数
	* @sa RenderingBegin()
	* @detail 上記関数とセットで使うこと
	* DrowSceneEndとPresentsDeviceを行う
	*/
	void RenderingEnd();

	/**
	* @brief キーボード情報の読み取り
	*/
	void CheckKeyStatus();
	/**
	* @brief 指定のキー情報取得
	* @param KeyName DXINPUTキーの名前
	*/
	int GetKeyStatus(int KeyName) {
		return m_KeyState[KeyName];
	};
	/**
	* @brief 画像読み込み
	* @param FilePath 画像ファイルパス
	* @param TextureKey 画像の格納キー
	*/
	void LoadTexture(LPCSTR FilePath, std::string TextureKey);
	/**
	* @brief 画像表示
	* @param TextureKey 画像の格納キー
	* @param TextureSize 頂点情報
	*/
	void DrawTexture(std::string TextureKey, const CUSTOMVERTEX* TextureSize);
	/**
	* @brief 画像消去
	* @param TextureKey 画像の格納キー
	*/
	void eraseTexture(std::string TexKey);
	/**
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
	void DrawWord(RECT rect, LPCSTR text, std::string FontNumber, int TextFormat = DT_LEFT, DWORD color = 0xff000000);
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

	/**
	* @brief DirectXデバイスの作成
	* @param hWnd ウィンドウハンドル
	* @param isWindowMode ウィンドウモード　true:WindowMode　false:FullscreenMode
	* @param FilePath デバイス生成チェック用画像ファイルパス
	*/
	HRESULT BuildDXDevice(HWND hWnd, bool WinMode, LPCSTR FilePath);
	/**
	* @brief 各ウィンドウモードのパラメータセッティング
	* @param hWnd ウィンドウハンドル
	*/
	void InitPresentParameters(HWND hWnd);
	void ReleaseDx();
	HRESULT ResetDevice(bool WinMode, RECT* WinRect, HWND hWnd);
private:
	std::map<std::string, LPDIRECT3DTEXTURE9> m_pTexture; //画像の情報を入れておく為のポインタ配列
	LPDIRECTINPUTDEVICE8 m_pKeyDevice = NULL; 
	LPDIRECTINPUT8 m_pDinput = NULL;			
	IDirect3DDevice9*  m_pD3Device = NULL; //Direct3Dのデバイス
	IDirect3D9*    m_pDirect3D = NULL; //DIrect3Dのインターフェース
	D3DPRESENT_PARAMETERS m_D3dPresentParameters;		//	パラメータ
	//D3DDISPLAYMODE		  m_D3DdisplayMode;
	std::map<std::string, LPD3DXFONT> m_pFont;
	D3DPRESENT_PARAMETERS m_d3dppWin, m_d3dppFull;

	BYTE m_KeyOldState[256];
	BYTE m_KeyState[256];

	HRESULT InitD3d(HWND hWnd, LPCSTR FilePath);
	HRESULT InitDinput(HWND hWnd);
	
};


