/**
* @file SceneManager.h
* @brief SceneManagerクラス
* @author Kojiro Kawahara
*/
#pragma once

#include "SCENE.h"
#include "SoundsManager.h"

using SoundLib::SoundsManager;

enum SCENE_NUM;
class Scene;

class SceneManager
{
public:
	SceneManager(DirectX* pDirectX, SoundsManager* pSoundManager);
	~SceneManager();
	int Update();
	void Render();
	static void LoadResouce();
	static DWORD WINAPI Thread(LPVOID *data);

private:
	void LoadAnimation();

	SCENE_NUM	m_CurrentScene;	//今のシーン
	//! メモリリーク検知器では検出されないと思われる。
	static Scene*	m_pScene;
	SCENE_NUM m_NextScene;
	DirectX * m_pDirectX = NULL;
	SoundsManager* m_pSoundManager = NULL;
	int BGMvolume = 100;
	int SEvolume = 100;
	HANDLE threadHandle;
	DWORD threadResult;
	void LoadAction();
	bool isRunOnce = false;
	bool isThreadActive = false;
	int LoadTime = 0;
};
