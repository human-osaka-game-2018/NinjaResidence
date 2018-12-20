/**
* @file MapReverse.cpp
* @brief MapReverseƒNƒ‰ƒX
* @author Kojiro Kawahara
*/
#include "MapReverse.h"

using namespace MapBlock;

MapReverse::MapReverse(DirectX* pDirectX, SoundsManager* pSoundManager, GameChara * GameChara) :Object(pDirectX, pSoundManager)
{
	m_pGameChara = GameChara;
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
	int MapPosiinonX = pGameChara->GetMapLeftDirectionPosition();
	int MapPosiinonY = pGameChara->GetMapCharaPositionY();
	if ((*pBusyMapChip)->getMapChipData((MapPosiinonY), (MapPosiinonX - 1)) == WOOD_REVERSE_ZONE ||
		(*pBusyMapChip)->getMapChipData((MapPosiinonY), (MapPosiinonX)) == WOOD_REVERSE_ZONE ||
		(*pBusyMapChip)->getMapChipData((MapPosiinonY), (MapPosiinonX + 1)) == WOOD_REVERSE_ZONE ||
		(*pBusyMapChip)->getMapChipData((MapPosiinonY), (MapPosiinonX + 2)) == WOOD_REVERSE_ZONE)
	{
		Object* Mapbuf;
		Mapbuf = (*pBusyMapChip);
		*pBusyMapChip = *pIdleMapChip;
		*pIdleMapChip = Mapbuf;
		m_pGameChara->CharaInforSave(*m_pBusyMapChip, WOOD_REVERSE_ZONE);
	}
	
	if ((*pBusyMapChip)->getMapChipData((MapPosiinonY), (MapPosiinonX - 1)) == ROCK_REVERSE_ZONE ||
		(*pBusyMapChip)->getMapChipData((MapPosiinonY), (MapPosiinonX)) == ROCK_REVERSE_ZONE ||
		(*pBusyMapChip)->getMapChipData((MapPosiinonY), (MapPosiinonX + 1)) == ROCK_REVERSE_ZONE ||
		(*pBusyMapChip)->getMapChipData((MapPosiinonY), (MapPosiinonX + 2)) == ROCK_REVERSE_ZONE)
	{
		Object* Mapbuf;
		Mapbuf = (*pBusyMapChip);
		*pBusyMapChip = *pIdleMapChip;
		*pIdleMapChip = Mapbuf;
		pGameChara->CharaInforSave(*pBusyMapChip, ROCK_REVERSE_ZONE);
	}
}
