#pragma once

#include "SCENE.h"
#include "SoundsManager.h"

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

using SoundLib::SoundsManager;

enum SCENE_NUM;
class Scene;

class SceneManager
{
private:
	SCENE_NUM	m_CurrentScene;	//ç°ÇÃÉVÅ[Éì
	Scene*	m_pScene = NULL;
	SCENE_NUM m_NextScene;
	DirectX * m_pDirectX = NULL;
	SoundsManager* m_pSoundManager = NULL;
public:
	SceneManager(DirectX* pDirectX, SoundsManager* pSoundManager);
	~SceneManager();
	void Update();
	void Render();
	void ReadTexture();
};
