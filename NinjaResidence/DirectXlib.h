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
	//! ������Ă��Ȃ�
	KeyOff,
	//! ������Ă���
	KeyOn,
	//! ���������Ă���
	KeyPush,
	//! �����ꂽ
	KeyRelease
};

#define DISPLAY_WIDTH 1280
#define DISPLAY_HEIGHT 720

class DirectX {
public:
	DirectX();
	~DirectX();

	/*
	* @brief �摜�\��
	*/
	void ClearDisplay();
	/*
	* @brief �摜�\��
	*/
	void PresentsDevice();

	/**
	*@brief �`��J�n�֐�
	* @sa DrowSceneEnd()
	* @detail ��L�֐��ƃZ�b�g�Ŏg������
	*/
	void DrowSceneBegin();
	/**
	* @brief �`��I���֐�
	* @sa DrowSceneBegin()
	* @detail ��L�֐��ƃZ�b�g�Ŏg������
	*/
	void DrowSceneEnd();
	/**
	* @brief �L�[�{�[�h���̓ǂݎ��
	*/
	void CheckKeyStatus();
	/**
	* @brief �摜�ǂݍ���
	* @param pTextureName �ǂݍ��މ摜�t�@�C����
	* @param TexKey �摜�̊i�[�L�[
	*/
	int GetKeyStatus(int KeyName);
	/*
	* @brief �摜�ǂݍ���
	* @param FilePath �摜�t�@�C���p�X
	* @param TextureKey �摜�̊i�[�L�[
	*/
	void LoadTexture(LPCSTR FilePath, std::string TextureKey);
	/*
	* @brief �摜�\��
	* @param TextureKey �摜�̊i�[�L�[
	* @param TextureSize ���_���
	*/
	void DrowTexture(std::string TextureKey, const CUSTOMVERTEX* TextureSize);
	/*
	* @brief �摜����
	* @param TextureKey �摜�̊i�[�L�[
	*/
	void eraseTexture(std::string TexKey);
	/*
	* @brief �摜�S����
	*/
	void ClearTexture();
	/**
	* @brief DX�t�H���g�`��ݒ�
	* @param Texts �\�����e
	* @param Vertex �\���͈�
	* @param FontNum �\�������ݒ�̊i�[�L�[
	* @param TextFormat �t�H�[�}�b�g
	* @param color �F
	*/
	void DrowWord(RECT rect, LPCSTR text, std::string FontNumber, int TextFormat = DT_LEFT, DWORD color = 0xff000000);
	/**
	* @brief DX�t�H���g�����ݒ�
	* @param WordHeight �����̍���
	* @param WordWidth �����̕�
	* @param FontKey �\�������ݒ�̊i�[��z��ԍ�
	* @param FontName �g�p����t�H���g��
	* @param CharSet �L�����Z�b�g�i�p���Ȃ�DEFAULT_CHARSET�C�V�t�gJIS�Ȃ�SHIFTJIS_CHARSET�j
	*/
	void SetFont(int height, int width, std::string FontKey, LPCSTR FontType = "�l�r�@�S�V�b�N", int CharSet = DEFAULT_CHARSET);
	/**
	* @brief DX�t�H���g����
	* @param FontKey �\�������ݒ�̊i�[��z��ԍ�
	*/
	void eraseFont(std::string FontKey);
	/**
	* @brief DX�t�H���g�S����
	*/
	void ClearFont();


	void BuildDXDevice(HWND hWnd, bool WinMode, LPCSTR FilePath);
	void InitPresentParameters(HWND hWnd);
private:
	std::map<std::string, LPDIRECT3DTEXTURE9> m_pTexture; //�摜�̏������Ă����ׂ̃|�C���^�z��
	LPDIRECTINPUTDEVICE8 m_pKeyDevice = NULL; 
	LPDIRECTINPUT8 m_pDinput = NULL;			
	IDirect3DDevice9*  m_pD3Device; //Direct3D�̃f�o�C�X
	IDirect3D9*    m_pDirect3D; //DIrect3D�̃C���^�[�t�F�[�X
	D3DPRESENT_PARAMETERS m_D3dPresentParameters;		//	�p�����[�^
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
