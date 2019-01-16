/**
* @file MapReverse.cpp
* @brief MapReverseクラス
* @author Kojiro Kawahara
*/
#include "MapReverse.h"

using namespace MapBlock;
bool MapReverse::MapDataReverseState = true;


MapReverse::MapReverse(DirectX* pDirectX, SoundOperater* pSoundOperater, GameChara* GameChara) :Object(pDirectX, pSoundOperater)
{
	m_pGameChara = GameChara;
}


MapReverse::~MapReverse()
{

}

bool MapReverse::collisonReversePoint(int x, int y) {
	for (int i = 0; i < m_ReverseCount; ++i) {
		if (ReversePointVector[i].PositionX == x && ReversePointVector[i].PositionY == y) {
			m_ReversePair = ReversePointVector[i].PairNumber;
			return true;
		}
	}
}

void MapReverse::GoMapReverse(Object** pBusyMapChip, Object** pIdleMapChip)
{

	int MapPosiinonX = m_pGameChara->GetMapLeftDirectionPosition();
	int MapPosiinonY = m_pGameChara->GetMapPositionY();

	bool CollLeft = collisonReversePoint(MapPosiinonX, MapPosiinonY);
	bool CollRight = collisonReversePoint(MapPosiinonX + 2, MapPosiinonY);
	bool CollCenter = collisonReversePoint(MapPosiinonX + 1, MapPosiinonY);
	if ((CollLeft|| CollCenter|| CollRight)&& m_ReversePair)
	{
		int Bufx = MapScrollXBuf;
		int Bufy = MapScrollYBuf;
		MapScrollXBuf = m_MapScrollX;
		MapScrollYBuf = m_MapScrollY;
		MapScrollXBuf = Bufx;
		MapScrollYBuf = Bufy;

		Object* Mapbuf;
		Mapbuf = (*pBusyMapChip);
		*pBusyMapChip = *pIdleMapChip;
		*pIdleMapChip = Mapbuf;

		m_pGameChara->CharaInfoSave(*pBusyMapChip, m_ReversePair);
	}
}
