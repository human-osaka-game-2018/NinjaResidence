#pragma once

#include "MapChip.h"
#include "SCENE.h"
#include "GameChara.h"
enum SCENE_NUM;
class Scene;
class MapChip;
class GameChara;

class GameScene : public Scene
{
private:
	CUSTOMVERTEX  GameBackground[4];
public:
	GameChara * m_pGameChara;
	MapChip * m_pMapChip;
	Scene * pScene;
	int MapScrollx ;
	int MapScrolly ;
	GameScene();
	~GameScene();
	SCENE_NUM Update();     //ゲームシーン（でプレイヤーや敵の移動とか）の更新関数
	void Render();       //ゲームシーン（でプレイヤーや敵の描画したりとか）の描画関数
	void ReadTexture();
};
