#pragma once

#include "GAMEMANAGER.h"
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

#define CENTRAL_Y (DISPLAY_HEIGHT / 2)
#define CENTRAL_X (DISPLAY_WIDTH / 2)

enum SCENE_NUM
{
	SCENE_NONE,

	TITLE_SCENE,

	STAGESELECT_SCENE,
	
	GAME_SCENE,

	RESULT_SCENE,

	MAX_SCENE,

};

struct CENTRAL_STATE
{
	float x, y, scale_x, scale_y;
};

class Scene {
private:
	SCENE_NUM	m_NextScene;	//éüÇÃÉVÅ[Éì
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

	void CreateSquareVertex(CUSTOMVERTEX* Vertex, CENTRAL_STATE Central, DWORD  color = 0xffffffff, float tu = 0, float tv = 0, float scaleTu = 1, float scaleTv = 1);
	void CreateSquareVertex(CUSTOMVERTEX* Vertex, float x, float y, DWORD  color = 0xffffffff, float tu = 0, float tv = 0, float scaleTu = 1, float scaleTv = 1);

	int GetStageNum() {
		return StageNum;
	}
protected:
	DirectX* m_pDirectX;
	int StageNum = 0;
};