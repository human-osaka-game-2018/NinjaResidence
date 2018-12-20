/**
* @file MapReverse.cpp
* @brief MapReverse�N���X
* @author Kojiro Kawahara
*/
#include "MapReverse.h"

using namespace MapBlock;
bool MapReverse::MapDataReverseState = true;

<<<<<<< HEAD
MapReverse::MapReverse(DirectX* pDirectX, SoundOperater* pSoundOperater, GameChara* GameChara) :Object(pDirectX, pSoundOperater)
{
	m_pGameChara = GameChara;
=======
bool MapReverse::MapDataReverseState = true;

MapReverse::MapReverse(DirectX* pDirectX, SoundsManager* pSoundManager, GameChara * GameChara) :Object(pDirectX, pSoundManager)
{
	pGameChara = GameChara;
>>>>>>> ターゲットとギミックを裏と表のどこに置いてもいける様にした
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
<<<<<<< HEAD
	int MapPosiinonX = m_pGameChara->GetMapLeftDirectionPosition();
	int MapPosiinonY = m_pGameChara->GetMapPositionY();
=======
	int MapPosiinonX = pGameChara->GetMapLeftDirectionPosition();
	int MapPosiinonY = pGameChara->GetMapCharaPositionY();
>>>>>>> ターゲットとギミックを裏と表のどこに置いてもいける様にした
	if ((*pBusyMapChip)->getMapChipData((MapPosiinonY), (MapPosiinonX - 1)) == WOOD_REVERSE_ZONE ||
		(*pBusyMapChip)->getMapChipData((MapPosiinonY), (MapPosiinonX)) == WOOD_REVERSE_ZONE ||
		(*pBusyMapChip)->getMapChipData((MapPosiinonY), (MapPosiinonX + 1)) == WOOD_REVERSE_ZONE ||
		(*pBusyMapChip)->getMapChipData((MapPosiinonY), (MapPosiinonX + 2)) == WOOD_REVERSE_ZONE)
	{
<<<<<<< HEAD

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
=======
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

		pGameChara->CharaInforSave(*pBusyMapChip, WOOD_REVERSE_ZONE);
>>>>>>> ターゲットとギミックを裏と表のどこに置いてもいける様にした
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
<<<<<<< HEAD


		m_pGameChara->CharaInfoSave(*pBusyMapChip, ROCK_REVERSE_ZONE);
=======
		

		pGameChara->CharaInforSave(*pBusyMapChip, ROCK_REVERSE_ZONE);
>>>>>>> ターゲットとギミックを裏と表のどこに置いてもいける様にした
	}
}
