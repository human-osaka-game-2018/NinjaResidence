#pragma once

#include "SCENE.h"

enum SCENE_NUM;
class Scene;

class SceneManager
{
private:
	SCENE_NUM	m_CurrentScene;	//ç°ÇÃÉVÅ[Éì
	Scene*	m_pScene;
	SCENE_NUM m_NextScene;
public:
	SceneManager();
	~SceneManager();
	void Update();
	void Render();
};