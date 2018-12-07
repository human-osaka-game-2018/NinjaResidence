#pragma once

#include "MapChip.h"
#include "SCENE.h"
#include "GameChara.h"
#include "MapReverse.h"
#include "DescriptionBoard.h"

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)


enum SCENE_NUM;
class Scene;
class MapChip;
class GameChara;
class MapReverse;
class DescriptionBoard;

class GameScene : public Scene
{
private:
	CUSTOMVERTEX  GameBackground[4];
	DirectX* m_pDirectX = NULL;
	GameChara* m_pGameChara = NULL;
	Object* m_pBusyMapChip = NULL;//使用中のMapChip
	Object* m_pIdleMapChip = NULL;//停止中のMapChip
	MapReverse * m_pMapReverse = NULL;
	DescriptionBoard * m_pDescriptionBoard = NULL;
	Scene* pScene = NULL;
public:
	GameScene(DirectX* pDirectX, int ChosedStage);
	~GameScene();
	SCENE_NUM Update();     //ゲームシーン（でプレイヤーや敵の移動とか）の更新関数
	void Render();       //ゲームシーン（でプレイヤーや敵の描画したりとか）の描画関数
	void ReadTexture();
	void TextureRender(std::string TextureKey, CUSTOMVERTEX* TextureSize);

};
