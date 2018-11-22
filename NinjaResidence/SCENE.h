#pragma once

#include "GAMEMANAGER.h"
#include "SoundsManager.h"

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

#define CENTRAL_Y (DISPLAY_HEIGHT / 2)
#define CENTRAL_X (DISPLAY_WIDTH / 2)

using SoundLib::SoundsManager;

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
	SCENE_NUM	m_NextScene;	//次のシーン
public:
	SCENE_NUM GetNextScene()
	{
		return m_NextScene;
	}
	void SetNextScene(SCENE_NUM NextScene)
	{
		m_NextScene = NextScene;
	}
	Scene(DirectX* pDirectX, SoundsManager* pSoundManager);
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
	DirectX* m_pDirectX = NULL;
	SoundsManager* m_pSoundManager = NULL;
	int StageNum = 0;
};
