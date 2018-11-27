#pragma once

#include "SCENE.h"

enum SCENE_NUM;
class Scene;
class TitleCursol;

class TitleScene : public Scene
{
private:
	CUSTOMVERTEX  TitleBackground[4];
	Scene * pScene = NULL;
	int timecount = 0; 
	void ChoseMenu();
	void EndGame();
public:
	TitleScene(DirectX* pDirectX, SoundsManager* pSoundManager);
	~TitleScene();
	SCENE_NUM Update();  
	void Render();       
	void LoadResouce();
	TitleCursol* m_pCursol = NULL;
};
