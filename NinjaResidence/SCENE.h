#pragma once

#include "GAMEMANAGER.h"
enum TEXTURE_NUM;

enum SCENE_NUM
{
	SCENE_NONE,

	TITLE_SCENE,

	GAME_SCENE,

	RESULT_SCENE,

	MAX_SCENE,

};

class Scene {
private:
	SCENE_NUM	m_NextScene;	//éüÇÃÉVÅ[Éì
protected:
	struct OBJECT_STATE
	{
		float x, y, scale_x, scale_y;
	};
public:
	void TextureRender(TEXTURE_NUM TextureID, CUSTOMVERTEX TextureSize[4]);
	SCENE_NUM Getm_NextScene()
	{
		return m_NextScene;
	}
	void Setm_NextScene(SCENE_NUM NextScene)
	{
		m_NextScene = NextScene;
	}
	Scene();
	 ~Scene();
	 void ReadTexture();
	virtual SCENE_NUM Update() = 0;
	virtual void Render() = 0;
};