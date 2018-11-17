#pragma once

#include <vector>
#include "GAMESCENE.h"
#include "Object.h"


class GameScene;
class MapChip;
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)


class GameChara :public Object
{
private:
	CENTRAL_STATE m_Player = { 400,10,(40 * 2),(40 * 4) };
	CUSTOMVERTEX m_DisplayCharaCoordinate[4];
	CUSTOMVERTEX m_WorldCharaCoordinate[4];
	//int MapCharaPositionX;
	//int MapCharaPositionY;
	int MapChara[5];
	//int MapChara[200][200];
public:
	koujirou abc;
	Scene * m_pScene;
	Object * m_pMapChip;
	void KeyOperation(koujirou abc);
	void Update();
	bool RectToRectCollisionCheak(CUSTOMVERTEX* pObjA, CUSTOMVERTEX* pObjB);
	void Render();
	GameChara(Scene * pScene, Object* MapChip);
	~GameChara();
	//int getMapCharaPositionX() {
	//	return MapCharaPositionX;
	//};
	//int getMapCharaPositionY() {
	//	return MapCharaPositionY;
	//};
};