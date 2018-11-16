#pragma once

#include <vector>
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
	CUSTOMVERTEX m_WorldCharaCoordinate[4];
	int MapCharaPositionX;
	int MapCharaPositionY;
	int MapChara[5];
	//int MapChara[200][200];
public:
	koujirou abc;
	Scene * m_pScene;
	MapChip * m_pMapChip;
	void GameCharaKeyOperation();
	void GameCharaUpdate();
	bool RectToRectCollisionCheak(CUSTOMVERTEX* pObjA, CUSTOMVERTEX* pObjB);
	void GameCharaRender();
	GameChara(Scene * pScene);
	~GameChara();
};