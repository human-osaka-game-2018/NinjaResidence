#pragma once

#include "GAMESCENE.h"
class GameScene;
class MapChip;
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

extern enum koujirou
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

class GameChara
{
private:
	CENTRAL_STATE m_Player = { 400,10,(40 * 2),(40 * 4) };
	CUSTOMVERTEX m_DisplayCharaCoordinate[4];
public:
	koujirou abc;
	Scene * m_pScene;
	MapChip * m_pMapChip;
	void GameCharaUpdate();
	void GameCharaRender();
	GameChara(Scene * pScene);
	~GameChara();
};