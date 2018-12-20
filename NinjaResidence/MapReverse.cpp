/**
* @file MapReverse.cpp
* @brief MapReverseƒNƒ‰ƒX
* @author Kojiro Kawahara
*/
#include "MapReverse.h"

using namespace MapBlock;
bool MapReverse::MapDataReverseState = true;

MapReverse::MapReverse(DirectX* pDirectX, SoundOperater* pSoundOperater, GameChara* GameChara) :Object(pDirectX, pSoundOperater)
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


void MapReverse::GoMapReverse(Object** pBusyMapChip, Object** pIdleMapChip)
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
		if (MapDataReverseState == true)
		{
			MapDataReverseState = false;
		}
		else
		{
			MapDataReverseState = true;
		}
 
		m_pGameChara->CharaInforSave(*m_pBusyMapChip, WOOD_REVERSE_ZONE);
	}
	if ((*pBusyMapChip)->getMapChipData((MapPosiinonY), (MapPosiinonX - 1)) == ROCK_REVERSE_ZONE ||
		(*pBusyMapChip)->getMapChipData((MapPosiinonY), (MapPosiinonX)) == ROCK_REVERSE_ZONE ||
		(*pBusyMapChip)->getMapChipData((MapPosiinonY), (MapPosiinonX + 1)) == ROCK_REVERSE_ZONE ||
		(*pBusyMapChip)->getMapChipData((MapPosiinonY), (MapPosiinonX + 2)) == ROCK_REVERSE_ZONE)
	{
		Object* Mapbuf;
		Mapbuf = (*m_pBusyMapChip);
		*m_pBusyMapChip = *m_pIdleMapChip;
		*m_pIdleMapChip = Mapbuf;
		if (MapDataReverseState == true)
		{
			MapDataReverseState = false;
		}
		else
		{
			MapDataReverseState = true;
		}


		m_pGameChara->CharaInforSave(*m_pBusyMapChip, ROCK_REVERSE_ZONE);
	}
}
