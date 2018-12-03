#pragma once

#include "SCENE.h"

enum SCENE_NUM;
class Scene;


class StageSerectScene : public Scene
{
private:
	CUSTOMVERTEX  TitleBackground[4];
	Scene * pScene = NULL;
	int timecount = 0;
	CENTRAL_STATE m_StageImage[5];
	CENTRAL_STATE m_StageFrame = { DISPLAY_WIDTH / 2,DISPLAY_HEIGHT / 2,270,270 };

public:
	StageSerectScene(DirectX* pDirectX, SoundsManager* pSoundManager);
	~StageSerectScene();
	SCENE_NUM Update();     //�Q�[���V�[���i�Ńv���C���[��G�̈ړ��Ƃ��j�̍X�V�֐�
	void Render();       //�Q�[���V�[���i�Ńv���C���[��G�̕`�悵����Ƃ��j�̕`��֐�
	void ReadTexture();

};
