/**
* @file STAGESELECTSCENE.h
* @brief ステージセレクトシーン
* @author Toshiya Matsuoka
*/
#pragma once

#include "SCENE.h"

enum SCENE_NUM;
class Scene;


class StageSelectScene : public Scene
{
public:
	StageSelectScene(DirectX* pDirectX, SoundOperater* pSoundOperater);
	~StageSelectScene();
	SCENE_NUM Update();
	void Render();
	void LoadResouce();

	void TurnUpStageImage();

	void TurnDownStageImage();

private:
	
	Scene* m_pScene = NULL;
	
	int m_timecount = 0;
	
	CENTRAL_STATE m_SelectCursol[1];
	CENTRAL_STATE m_StageImage[5];
	CENTRAL_STATE m_StageFrame = { DISPLAY_WIDTH / 2,DISPLAY_HEIGHT / 2,270,270 };
	std::string m_StageImagekey[6];
};
