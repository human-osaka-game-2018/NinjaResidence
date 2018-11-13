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
#define DISPLAY_HIGHT 720
/*
* @brief �摜�ǂݍ���
* @param FilePath �摜�t�@�C���p�X
* @param TextureKey �摜�̊i�[�L�[
*/
void LoadTexture(LPCSTR FilePath, std::string TextureKey);
/*
* @brief �摜�\��
*/
void ClearDisplay();
/*
* @brief �摜�\��
*/
void PresentsDevice();
/*
* @brief �摜�\��
* @param TextureKey �摜�̊i�[�L�[
* @param TextureSize ���_���
*/
void DrowTexture(std::string TextureKey, const CUSTOMVERTEX* TextureSize);
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
void FreeDx();


//Directx�֌W
//extern std::map<std::string, LPDIRECT3DTEXTURE9> g_pTexture; //�摜�̏������Ă����ׂ̃|�C���^�z��
//extern LPDIRECTINPUTDEVICE8 g_pKeyDevice; //step4(�L�[���͂̎擾)�ɕK�v
//extern LPDIRECTINPUT8 g_pDinput;			//step4(�L�[���͂̎擾)�ɕK�v
//extern IDirect3DDevice9*  g_pD3Device; //Direct3D�̃f�o�C�X
//extern IDirect3D9*    g_pDirect3D; //DIrect3D�̃C���^�[�t�F�[�X
//extern D3DPRESENT_PARAMETERS g_D3dPresentParameters;		//	�p�����[�^
//extern D3DDISPLAYMODE		  g_D3DdisplayMode;
//extern void FreeDx();

