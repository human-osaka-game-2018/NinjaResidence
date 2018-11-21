#pragma once

#include "SCENE.h"

enum SCENE_NUM;
class Scene;

class TitleScene : public Scene
{
private:
	CUSTOMVERTEX  TitleBackground[4];
	Scene * pScene = NULL;
	int timecount = 0; 
public:
	TitleScene(DirectX* pDirectX);
	~TitleScene();
	SCENE_NUM Update();     //ゲームシーン（でプレイヤーや敵の移動とか）の更新関数
	void Render();       //ゲームシーン（でプレイヤーや敵の描画したりとか）の描画関数
	void ReadTexture();

};
