#pragma once

#include "SCENE.h"

enum SCENE_NUM;
class Scene;

class TitleScene : public Scene
{
private:
	CUSTOMVERTEX  TitleBackground[4];
	Scene * pScene;
	int timecount = 0; 
public:
	TitleScene(DirectX* pDirectX);
	~TitleScene();
	SCENE_NUM Update();     //�Q�[���V�[���i�Ńv���C���[��G�̈ړ��Ƃ��j�̍X�V�֐�
	void Render();       //�Q�[���V�[���i�Ńv���C���[��G�̕`�悵����Ƃ��j�̕`��֐�
	void ReadTexture();
	void TextureRender(std::string TextureKey, CUSTOMVERTEX* TextureSize);

};
