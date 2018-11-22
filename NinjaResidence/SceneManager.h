#pragma once

#include "SCENE.h"
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

enum SCENE_NUM;
class Scene;

class SceneManager
{
private:
	SCENE_NUM	m_CurrentScene;	//ç°ÇÃÉVÅ[Éì
	Scene*	m_pScene = NULL;
	SCENE_NUM m_NextScene;
	DirectX * m_pDirectX = NULL;

public:
	SceneManager(DirectX* pDirectX);
	~SceneManager();
	void Update();
	void Render();
	void ReadTexture();
};