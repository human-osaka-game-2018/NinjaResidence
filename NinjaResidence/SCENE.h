#pragma once

#include "GAMEMANAGER.h"
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

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
	virtual void TextureRender(std::string TextureKey, CUSTOMVERTEX* TextureSize);
	SCENE_NUM Getm_NextScene()
	{
		return m_NextScene;
	}
	void Setm_NextScene(SCENE_NUM NextScene)
	{
		m_NextScene = NextScene;
	}
	Scene(DirectX* pDirectX);
	virtual ~Scene();
	virtual SCENE_NUM Update() = 0;
	virtual void ReadTexture() = 0;
	virtual void Render() = 0;
protected:
	DirectX* m_pDirectX;

};