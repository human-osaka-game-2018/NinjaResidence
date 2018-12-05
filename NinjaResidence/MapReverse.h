#pragma once

#include "Object.h"
#include "GameChara.h"


class GameScene;
class GameChara;
class MapChip;

class MapReverse :public Object
{
private:
	CENTRAL_STATE m_Player = { 400,10,(CELL_SIZE * 2),(CELL_SIZE * 4) };
	GameChara* m_pGameChara = NULL;
public:
	void GoMapReverse(Object** m_pBusyMapChip, Object** m_pIdleMapChip);
	MapReverse(DirectX* pDirectX,GameChara * GameChara);
	~MapReverse();
};
