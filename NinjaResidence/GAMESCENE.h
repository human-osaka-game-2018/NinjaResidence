#pragma once

#include "MapChip.h"
#include "SCENE.h"
#include "GameChara.h"

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

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
	GameScene(DirectX* pDirectX, int ChosedStage);
	~GameScene();
	SCENE_NUM Update();     //ゲームシーン（でプレイヤーや敵の移動とか）の更新関数
	void Render();       //ゲームシーン（でプレイヤーや敵の描画したりとか）の描画関数
	void ReadTexture();
	void TextureRender(std::string TextureKey, CUSTOMVERTEX* TextureSize);

};
