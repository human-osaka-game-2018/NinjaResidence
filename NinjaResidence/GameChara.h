#pragma once

#include <vector>
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
	PLAYER_STATE m_Player = { 400.f,100.f,(40.f * 2),(40.f * 4) };
	CUSTOMVERTEX m_DisplayCharaCoordinate[4];
	CUSTOMVERTEX m_WorldCharaCoordinate[4];
	int MapCharaPositionX;
	int MapCharaPositionY;
	int MapChara[5];
	//int MapChara[200][200];
public:
	koujirou abc;
	Scene * pScene;
	MapChip * m_pMapChip;
	void GameCharaKeyOperation();
	void GameCharaUpdate();
	bool RectToRectCollisionCheak(CUSTOMVERTEX* pObjA, CUSTOMVERTEX* pObjB);
	void GameCharaRender();
	GameChara();
	~GameChara();
};