/**
* @file MapReverse.cpp
* @brief MapReverseクラス
* @author Kojiro Kawahara
*/
#include "MapReverse.h"

using namespace MapBlock;

MapReverse::MapReverse(DirectX* pDirectX, SoundsManager* pSoundManager, GameChara * GameChara) :Object(pDirectX, pSoundManager)
{
	m_pGameChara = GameChara;
	MapReverseState = Surface;
	m_SurfaceMapScrollX = 0;
	m_SurfaceMapScrollY = 0;
	m_ReverseMapScrollX = 0;
	m_ReverseMapScrollY = 0;
}


MapReverse::~MapReverse()
{

}


void MapReverse::GoMapReverse(Object** m_pBusyMapChip, Object** m_pIdleMapChip)
{
	int MapPosiinonX = m_pGameChara->GetMapCharaPositionX();
	int MapPosiinonY = m_pGameChara->GetMapCharaPositionY();
	if ((*m_pBusyMapChip)->getMapChipData((MapPosiinonY),(MapPosiinonX - 1))  < WOOD_REVERSE_ZONE &&
		(*m_pBusyMapChip)->getMapChipData((MapPosiinonY),( MapPosiinonX)) < WOOD_REVERSE_ZONE &&
		(*m_pBusyMapChip)->getMapChipData((MapPosiinonY),( MapPosiinonX+ 1)) < WOOD_REVERSE_ZONE &&
		(*m_pBusyMapChip)->getMapChipData((MapPosiinonY),( MapPosiinonX+ 2)) < WOOD_REVERSE_ZONE)
	{
		return;
	}

	Object* Mapbuf;
	Mapbuf = (*m_pBusyMapChip);
	*m_pBusyMapChip = *m_pIdleMapChip;
	*m_pIdleMapChip = Mapbuf;
	(*m_pBusyMapChip)->m_MapScrollX = (*m_pIdleMapChip)->m_MapScrollX;
	(*m_pBusyMapChip)->m_MapScrollY = (*m_pIdleMapChip)->m_MapScrollY;
	switch (MapReverseState)
	{
		//表面を裏面にする
	case Surface:
		m_pGameChara->CharaInforSave(MapReverseState, *m_pBusyMapChip);
		//m_SurfaceMapScrollX = m_pMapChipA->m_MapScrollX;
		//m_SurfaceMapScrollY = m_pMapChipA->m_MapScrollY;
		//m_pMapChipA->m_MapScrollX = m_ReverseMapScrollX;
		//m_pMapChipA->m_MapScrollY = m_ReverseMapScrollY;
		//m_pMapChipA->Create("csv/Book2.csv");
		MapReverseState = Reverse;
		break;
		//裏面を表面にする
	case Reverse:
		m_pGameChara->CharaInforSave(MapReverseState, *m_pBusyMapChip);
		//m_ReverseMapScrollX = m_pMapChipA->m_MapScrollX;
		//m_ReverseMapScrollY = m_pMapChipA->m_MapScrollY;
		//m_pMapChipA->m_MapScrollX = m_SurfaceMapScrollX;
		//m_pMapChipA->m_MapScrollY = m_SurfaceMapScrollY;
		//m_pMapChipA->Create("csv/Book1.csv");
		MapReverseState = Surface;
		break;
	}
}
