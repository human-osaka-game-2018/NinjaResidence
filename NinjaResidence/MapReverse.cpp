#include "MapReverse.h"


MapReverse::MapReverse(DirectX* pDirectX, Object* MapChip, GameChara* GameChara) :Object(pDirectX)
{
	m_pMapChip = MapChip;
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


void MapReverse::GoMapReverse()
{
	int MapPosiinonX = m_pGameChara->GetMapCharaPositionX();
	int MapPosiinonY = m_pGameChara->GetMapCharaPositionY();
	m_pGameChara->GetDisplayCharaCoordinate();
	if (m_pMapChip->getMapChipData((MapPosiinonY),(MapPosiinonX - 1))  < 5 &&
		m_pMapChip->getMapChipData((MapPosiinonY),( MapPosiinonX)) < 5 &&
		m_pMapChip->getMapChipData((MapPosiinonY),( MapPosiinonX+ 1)) < 5 &&
		m_pMapChip->getMapChipData((MapPosiinonY),( MapPosiinonX+ 2)) < 5)
	{
		return;
	}

	switch (MapReverseState)
	{
		//•\–Ê‚ð— –Ê‚É‚·‚é
	case Surface:
		m_pGameChara->CharaInforSave(true);
		m_SurfaceMapScrollX = m_pMapChip->m_MapScrollX;
		m_SurfaceMapScrollY = m_pMapChip->m_MapScrollY;
		m_pMapChip->m_MapScrollX = m_ReverseMapScrollX;
		m_pMapChip->m_MapScrollY = m_ReverseMapScrollY;
		m_pMapChip->Create("csv/Book2.csv");
		MapReverseState = Reverse;
		break;
		//— –Ê‚ð•\–Ê‚É‚·‚é
	case Reverse:
		m_pGameChara->CharaInforSave(false);
		m_ReverseMapScrollX = m_pMapChip->m_MapScrollX;
		m_ReverseMapScrollY = m_pMapChip->m_MapScrollY;
		m_pMapChip->m_MapScrollX = m_SurfaceMapScrollX;
		m_pMapChip->m_MapScrollY = m_SurfaceMapScrollY;
		m_pMapChip->Create("csv/Book1.csv");
		MapReverseState = Surface;
		break;
	}
}
