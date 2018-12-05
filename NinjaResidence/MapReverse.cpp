#include "MapReverse.h"

using namespace MapBlock;

MapReverse::MapReverse(DirectX* pDirectX, GameChara * GameChara) :Object(pDirectX)
{
	m_pGameChara = GameChara;
}


MapReverse::~MapReverse()
{

}


void MapReverse::GoMapReverse(Object** m_pBusyMapChip, Object** m_pIdleMapChip)
{
	int MapPosiinonX = m_pGameChara->GetMapCharaPositionX();
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

		m_pGameChara->CharaInforSave(*m_pBusyMapChip, ROCK_REVERSE_ZONE);

	}
}
