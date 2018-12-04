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


void MapReverse::GoMapReverse(Object** m_pBusyMapChip, Object** m_pIdleMapChip)
{
	int MapPosiinonX = m_pGameChara->GetMapLeftDirectionPosition();
	int MapPosiinonY = m_pGameChara->GetMapCharaPositionY();
	if ((*m_pBusyMapChip)->getMapChipData((MapPosiinonY), (MapPosiinonX - 1)) == WOOD_REVERSE_ZONE ||
		(*m_pBusyMapChip)->getMapChipData((MapPosiinonY), (MapPosiinonX)) == WOOD_REVERSE_ZONE ||
		(*m_pBusyMapChip)->getMapChipData((MapPosiinonY), (MapPosiinonX + 1)) == WOOD_REVERSE_ZONE ||
		(*m_pBusyMapChip)->getMapChipData((MapPosiinonY), (MapPosiinonX + 2)) == WOOD_REVERSE_ZONE)
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
 
		m_pGameChara->CharaInforSave(*m_pBusyMapChip, WOOD_REVERSE_ZONE);
	}
	if ((*m_pBusyMapChip)->getMapChipData((MapPosiinonY), (MapPosiinonX - 1)) == ROCK_REVERSE_ZONE ||
		(*m_pBusyMapChip)->getMapChipData((MapPosiinonY), (MapPosiinonX)) == ROCK_REVERSE_ZONE ||
		(*m_pBusyMapChip)->getMapChipData((MapPosiinonY), (MapPosiinonX + 1)) == ROCK_REVERSE_ZONE ||
		(*m_pBusyMapChip)->getMapChipData((MapPosiinonY), (MapPosiinonX + 2)) == ROCK_REVERSE_ZONE)
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
