﻿/**
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

bool MapReverse::collisonReversePoint(int x, int y, Object* pBusyMapChip) {
	for (int i = 0; i < m_ReverseCount; ++i) {

		if (ReversePointVector[i].PositionX == x &&
			ReversePointVector[i].PositionY == y &&
			ReversePointVector[i].MapDataState == (*pBusyMapChip).GetMapDataState()) {

			m_ReversePair = ReversePointVector[i].PairNumber;
			m_ReverseBuffer[i].ScrollX = m_MapScrollX;
			m_ReverseBuffer[i].ScrollY = m_MapScrollY;
			m_ActiveReversePointNum = i;
			return true;
		}
	}
	return false;
}

void MapReverse::GoMapReverse(Object** pBusyMapChip, Object** pIdleMapChip)
{

	int MapPosiinonX = m_pGameChara->GetMapLeftDirectionPosition();
	int MapPosiinonY = m_pGameChara->GetMapPositionY();

	bool CollLeft = collisonReversePoint(MapPosiinonX-1, MapPosiinonY, *pBusyMapChip);
	bool CollRight = collisonReversePoint(MapPosiinonX + 1, MapPosiinonY, *pBusyMapChip);
	bool CollCenter = collisonReversePoint(MapPosiinonX + 0, MapPosiinonY, *pBusyMapChip);
	if ((CollLeft|| CollCenter|| CollRight)&& m_ReversePair)
	{
		for (int i = 0; i < m_ReverseCount; ++i) {

			if (ReversePointVector[i].PairNumber== m_ReversePair&&
				ReversePointVector[i].MapDataState != (*pBusyMapChip)->GetMapDataState()) {
				if (i == m_ActiveReversePointNum) {
					continue;
				}
				m_MapScrollX = m_ReverseBuffer[i].ScrollX;
				m_MapScrollY = m_ReverseBuffer[i].ScrollY;
			}
		}

		//int Bufx = m_MapScrollX;
		//int Bufy = m_MapScrollY;
		//m_MapScrollX = MapScrollXBuf;
		//m_MapScrollY = MapScrollYBuf;
		//MapScrollXBuf = Bufx;
		//MapScrollYBuf = Bufy;

		Object* Mapbuf;
		Mapbuf = (*pBusyMapChip);
		*pBusyMapChip = *pIdleMapChip;
		*pIdleMapChip = Mapbuf;

		m_pGameChara->CharaInfoSave(*pBusyMapChip, m_ReversePair);
	}
	CollLeft = CollRight = CollCenter = false;
}
