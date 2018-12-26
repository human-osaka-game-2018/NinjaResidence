/**
* @file SceneManager.h
* @brief SceneManager�N���X
* @author Kojiro Kawahara
*/
#pragma once

#include "SCENE.h"
#include "SoundOperater.h"


enum SCENE_NUM;
class Scene;
class VOLUMESELECTSCENE;


class SceneManager
{
public:
	SceneManager(DirectX* pDirectX, SoundOperater* pSoundOperater);
	~SceneManager();
	int Update();
	void Render();
	static void LoadResouce();
	static DWORD WINAPI Thread(LPVOID *data);

private:
	void LoadAnimation();

	SCENE_NUM m_CurrentScene;	//���̃V�[��
	//! ���������[�N���m��ł͌��o����Ȃ��Ǝv����B
	static Scene*	m_pScene;
	SCENE_NUM m_NextScene;
	DirectX* m_pDirectX = NULL;
	SoundOperater* m_pSoundManager = NULL;
	VOLUMESELECTSCENE* m_pVolumeSettingScene = NULL;

	HANDLE m_threadHandle;
	DWORD m_threadResult;
	void LoadAction();
	bool isRunOnce = false;
	bool isThreadActive = false;
	int LoadTime = 0;
	int TestTime = 0;
};
