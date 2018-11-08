#pragma once

#include "MapChip.h"
#include "SCENE.h"
enum SCENE_NUM;
class Scene;
class MapChip;


class GameScene : public Scene
{
private:
	OBJECT_STATE m_Player = { 0,0,CELL_SIZE,(CELL_SIZE * 2)};
	CUSTOMVERTEX VertexPlayer[4];
	CUSTOMVERTEX  GameBackground[4];
	MapChip*	pMapChip;
	Scene*	pScene;
public:
	GameScene();
	~GameScene();
	SCENE_NUM Update();     //ゲームシーン（でプレイヤーや敵の移動とか）の更新関数
	void Render();       //ゲームシーン（でプレイヤーや敵の描画したりとか）の描画関数
};
