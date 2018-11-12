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

struct PLAYER_STATE//プレイヤー（キャラ）にしか使わない
{
	float x, y, scale_x, scale_y;
};

class Scene {
private:
	SCENE_NUM	m_NextScene;	//次のシーン
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
	virtual SCENE_NUM Update() = 0;
	virtual void ReadTexture() = 0;
	virtual void Render() = 0;
};