/**
* @file MapReverse.h
* @brief MapReverseƒNƒ‰ƒX
* @author Kojiro Kawahara
*/
#pragma once

#include "Object.h"
#include "GameChara.h"


class GameScene;
class GameChara;
class MapChip;

class MapReverse :public Object
{
public:
	void GoMapReverse(Object** m_pBusyMapChip, Object** m_pIdleMapChip);
	MapReverse(DirectX* pDirectX, SoundsManager* pSoundManager, GameChara * GameChara);
	~MapReverse();

private:
	CENTRAL_STATE m_Player = { 400,10,(CELL_SIZE * 2),(CELL_SIZE * 4) };
	int m_SurfaceMapScrollX;
	int m_SurfaceMapScrollY;
	int m_ReverseMapScrollX;
	int m_ReverseMapScrollY;
	enum MapReverseState
	{
		Surface,//•\
		Reverse,//— 
	};
	MapReverseState MapReverseState;
	GameChara* m_pGameChara = NULL;
};
