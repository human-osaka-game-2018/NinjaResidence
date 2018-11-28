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
	int m_SurfaceMapScrollX;
	int m_SurfaceMapScrollY;
	int m_ReverseMapScrollX;
	int m_ReverseMapScrollY;
	enum MapReverse1
	{
		Surface,//•\
		Reverse,//— 
	};
	MapReverse1 MapReverse1;
	GameChara* m_pGameChara = NULL;
	Object* m_pMapChip = NULL;
public:
	void GoMapReverse();
	MapReverse(DirectX* pDirectX, Object* MapChip, GameChara * GameChara);
	~MapReverse();
};
