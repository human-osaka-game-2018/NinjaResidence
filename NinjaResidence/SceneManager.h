#pragma once

#include "SCENE.h"
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

enum SCENE_NUM;
class Scene;

class SceneManager
{
private:
	SCENE_NUM	m_CurrentScene;	//今のシーン
	Scene*	m_pScene;
	SCENE_NUM m_NextScene;
	DirectX * m_pDirectX;

public:
	SceneManager(DirectX* pDirectX);
	~SceneManager();
	void Update();
	void Render();
	void ReadTexture();
};