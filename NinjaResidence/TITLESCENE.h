/**
* @file TITLESCENE.h
* @brief タイトルシーン
* @author Toshiya Matsuoka
*/
#pragma once

#include "SCENE.h"

enum SCENE_NUM;
class Scene;
class TitleCursol;

class TitleScene : public Scene
{
public:
	TitleScene(DirectX* pDirectX, SoundsManager* pSoundManager);
	~TitleScene();
	SCENE_NUM Update();
	void Render();
	void LoadResouce();

private:
	CUSTOMVERTEX  m_TitleBackground[4];
	Scene* m_pScene = NULL;
	int m_timecount = 0; 
	TitleCursol* m_pCursol = NULL;
	void ChoseMenu();
	void EndGame();
};
