#pragma once

#include "SCENE.h"

enum SCENE_NUM;
class Scene;


class StageSerectScene : public Scene
{
private:
	CUSTOMVERTEX  TitleBackground[4];
	Scene * pScene;
	int timecount = 0;
	CENTRAL_STATE m_StageImage[5];
	CENTRAL_STATE m_StageFrame = { DISPLAY_WIDTH / 2,DISPLAY_HEIGHT / 2,270,270 };

public:
	StageSerectScene(DirectX* pDirectX);
	~StageSerectScene();
	SCENE_NUM Update();     //ゲームシーン（でプレイヤーや敵の移動とか）の更新関数
	void Render();       //ゲームシーン（でプレイヤーや敵の描画したりとか）の描画関数
	void ReadTexture();

};
