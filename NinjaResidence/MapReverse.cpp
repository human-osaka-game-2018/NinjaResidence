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


void MapReverse::GoMapReverse(Object** pBusyMapChip, Object** pIdleMapChip)
{

	int MapPosiinonX = m_pGameChara->GetMapLeftDirectionPosition();
	int MapPosiinonY = m_pGameChara->GetMapPositionY();
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
 
		m_pGameChara->CharaInfoSave(*pBusyMapChip, WOOD_REVERSE_ZONE);
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
		if (MapDataReverseState == true)
		{
			MapDataReverseState = false;
		}
		else
		{
			MapDataReverseState = true;
		}



		m_pGameChara->CharaInfoSave(*pBusyMapChip, ROCK_REVERSE_ZONE);
	}
}
