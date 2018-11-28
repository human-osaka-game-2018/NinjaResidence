#include "MapReverse.h"


MapReverse::MapReverse(DirectX* pDirectX, Object* MapChip, GameChara* GameChara) :Object(pDirectX)
{
	m_pMapChip = MapChip;
	m_pGameChara = GameChara;
	MapReverse1 = Surface;
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
	m_pGameChara->GetDisplayCharaCoordinate();
	if (m_pMapChip->getMapChipData((m_pGameChara->GetMapCharaPositionY() - 1),( m_pGameChara->GetMapCharaPositionX() - 1))  != 3 &&
		m_pMapChip->getMapChipData((m_pGameChara->GetMapCharaPositionY() - 1),( m_pGameChara->GetMapCharaPositionX()))  != 3 &&
		m_pMapChip->getMapChipData((m_pGameChara->GetMapCharaPositionY() - 1),( m_pGameChara->GetMapCharaPositionX() + 1)) != 3 &&
		m_pMapChip->getMapChipData((m_pGameChara->GetMapCharaPositionY() - 1),( m_pGameChara->GetMapCharaPositionX() + 2)) != 3)
	{
		return;
	}

	switch (MapReverse1)
	{
		//•\–Ê‚ð— –Ê‚É‚·‚é
	case Surface:
		m_pGameChara->CharaInforSave(true);
		m_SurfaceMapScrollX = m_pMapChip->m_MapScrollX;
		m_SurfaceMapScrollY = m_pMapChip->m_MapScrollY;
		m_pMapChip->m_MapScrollX = m_ReverseMapScrollX;
		m_pMapChip->m_MapScrollY = m_ReverseMapScrollY;
		m_pMapChip->Create("csv/Book2.csv");
		MapReverse1 = Reverse;
		break;
		//— –Ê‚ð•\–Ê‚É‚·‚é
	case Reverse:
		m_pGameChara->CharaInforSave(false);
		m_ReverseMapScrollX = m_pMapChip->m_MapScrollX;
		m_ReverseMapScrollY = m_pMapChip->m_MapScrollY;
		m_pMapChip->m_MapScrollX = m_SurfaceMapScrollX;
		m_pMapChip->m_MapScrollY = m_SurfaceMapScrollY;
		m_pMapChip->Create("csv/Book1.csv");
		MapReverse1 = Surface;
		break;
	}
}
