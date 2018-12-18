/**
* @file STAGESELECTSCENE.h
* @brief �X�e�[�W�Z���N�g�V�[��
* @author Toshiya Matsuoka
*/
#pragma once

#include "SCENE.h"

enum SCENE_NUM;
class Scene;


class StageSelectScene : public Scene
{
public:
	StageSelectScene(DirectX* pDirectX, SoundsManager* pSoundManager);
	~StageSelectScene();
	SCENE_NUM Update();
	void Render();
	void LoadResouce();

private:
	CUSTOMVERTEX  m_SerectBackground[4];
	Scene * m_pScene = NULL;
	int m_timecount = 0;
	CENTRAL_STATE m_StageImage[5];
	CENTRAL_STATE m_StageFrame = { DISPLAY_WIDTH / 2,DISPLAY_HEIGHT / 2,270,270 };

};
