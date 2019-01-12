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
	
	CENTRAL_STATE m_Logo={ CENTRAL_X ,200,400,150 };
	CENTRAL_STATE m_Menu = { CENTRAL_X ,500,100,100 };
	
	int m_timecount = 0;
	
	TitleCursol* m_pCursol = NULL;
	
	void ChoseMenu();
};
