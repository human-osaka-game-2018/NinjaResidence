#pragma once

#include "GAMEMANAGER.h"
#include "XinputDevice.h"
#include "SoundsManager.h"

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
	virtual void LoadResouce() = 0;
	virtual void Render() = 0;
	virtual void EndGame();

	void LoadAnimation();
	void CreateSquareVertex(CUSTOMVERTEX* Vertex, CENTRAL_STATE Central, DWORD  color = 0xffffffff, float tu = 0, float tv = 0, float scaleTu = 1, float scaleTv = 1);
	void CreateSquareVertex(CUSTOMVERTEX* Vertex, float x, float y, DWORD  color = 0xffffffff, float tu = 0, float tv = 0, float scaleTu = 1, float scaleTv = 1);
	void GoToOptionScene();
	void RunOptionScene(int BGMvolume, int SEvolume);
	int GetStageNum() {
		return StageNum;
	}
	int GetGameState() {
		return GameState;
	}
protected:
	DirectX* m_pDirectX = NULL;
	XinputDevice* m_pXinputDevice = NULL;
	SoundsManager* m_pSoundManager = NULL;
	int StageNum = 0;
	int GameState = WM_NULL;
private:
	SCENE_NUM	m_NextScene;	//éüÇÃÉVÅ[Éì
	};
