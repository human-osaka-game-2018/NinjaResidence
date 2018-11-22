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
	CENTRAL_STATE m_Player = { 400,10,(CELL_SIZE * 2),(CELL_SIZE * 4) };
	CUSTOMVERTEX m_DisplayCharaCoordinate[4];
	CUSTOMVERTEX m_WorldCharaCoordinate[4];
	int MapCharaPositionX;
	int MapCharaPositionX2;
	int MapCharaPositionY;
	int m_prevMapCharaPositionX;
	int m_prevMapCharaPositionX2;
	int m_prevMapCharaPositionY;
	Object* m_pMapChip = NULL;
	float CharTu = 80 / 512.f;
	float CharTv = 160 / 512.f;
public:

	void prevSaveMapCharaPos();
	void KeyOperation(KeyDirection vec);
	void MapScroolCheck();
	void Update();
	void Render();
	GameChara(DirectX* pDirectX, Object* MapChip);
	~GameChara();
};