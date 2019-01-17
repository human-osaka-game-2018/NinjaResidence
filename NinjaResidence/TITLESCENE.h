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
	TitleScene(DirectX* pDirectX, SoundOperater* pSoundOperater);
	~TitleScene();
	SCENE_NUM Update();
	void Render();
	void LoadResouce();

private:
	Scene* m_pScene = NULL;
	
	CENTRAL_STATE m_Logo={ 350,200,250,100 };
	CENTRAL_STATE m_Menu = { 350 ,500,80,150 };
	
	int m_timecount = 0;
	
	TitleCursol* m_pCursol = NULL;
	
	void ChoseMenu();
};
