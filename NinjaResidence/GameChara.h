#pragma once

#include "GAMESCENE.h"
class GameScene;
class MapChip;

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
	PLAYER_STATE m_Player = { 400,10,(40 * 2),(40 * 4) };
	CUSTOMVERTEX m_DisplayCharaCoordinate[4];
public:
	koujirou abc;
	Scene * pScene;
	MapChip * m_pMapChip;
	void GameCharaUpdate();
	void GameCharaRender();
	GameChara();
	~GameChara();
};