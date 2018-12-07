#include "DescriptionBoard.h"

using namespace MapBlock;

DescriptionBoard::DescriptionBoard(DirectX* pDirectX,GameChara * GameChara, Object * m_pBusyMapChip) :Object(pDirectX)
{
	m_pGameChara = GameChara;
	m_pMapChip = m_pBusyMapChip;
	DescriptionNumberdecision = NONE;
	DescriptionBoardSIZE[0] = {300,110,1.0f, 1.0f,0xFFFFFFFF, 0.f, 0.f };
	DescriptionBoardSIZE[1] = {980,110,1.0f, 1.0f,0xFFFFFFFF, 1.0f, 0.f };
	DescriptionBoardSIZE[2] = {980,500,1.0f, 1.0f,0xFFFFFFFF, 1.0f, 1.0f};
	DescriptionBoardSIZE[3] = {300,500,1.0f, 1.0f,0xFFFFFFFF, 0.f, 1.0f};
}

DescriptionBoard::~DescriptionBoard()
{

}

void DescriptionBoard::GoDescriptionBoard(Object * m_pBusyMapChip)
{
	m_pMapChip = m_pBusyMapChip;
	int MapPosiinonX = m_pGameChara->GetMapLeftDirectionPosition();
	int MapPosiinonY = m_pGameChara->GetMapCharaPositionY();
	if ((m_pMapChip->getMapChipData(MapPosiinonY - 5, MapPosiinonX) == 7) ||
		(m_pMapChip->getMapChipData(MapPosiinonY - 5, MapPosiinonX + 1) == 7) ||
		(m_pMapChip->getMapChipData(MapPosiinonY - 5, MapPosiinonX + 2) == 7) ||
		(m_pMapChip->getMapChipData(MapPosiinonY - 5, MapPosiinonX - 1) == 7) ||
		(m_pMapChip->getMapChipData(MapPosiinonY - 4, MapPosiinonX ) == 7) || 
		(m_pMapChip->getMapChipData(MapPosiinonY - 4, MapPosiinonX + 1) == 7) || 
		(m_pMapChip->getMapChipData(MapPosiinonY - 4, MapPosiinonX  + 2) == 7) || 
		(m_pMapChip->getMapChipData(MapPosiinonY - 4, MapPosiinonX - 1) == 7))
	{
		DescriptionNumberdecision = Number1;
	}
	if ((m_pMapChip->getMapChipData(MapPosiinonY - 5, MapPosiinonX) == 8) ||
		(m_pMapChip->getMapChipData(MapPosiinonY - 5, MapPosiinonX + 1) == 8) ||
		(m_pMapChip->getMapChipData(MapPosiinonY - 5, MapPosiinonX + 2) == 8) ||
		(m_pMapChip->getMapChipData(MapPosiinonY - 5, MapPosiinonX - 1) == 8) ||
		(m_pMapChip->getMapChipData(MapPosiinonY - 4, MapPosiinonX) == 8)||
		(m_pMapChip->getMapChipData(MapPosiinonY - 4, MapPosiinonX + 1) == 8)||
		(m_pMapChip->getMapChipData(MapPosiinonY - 4, MapPosiinonX + 2) == 8)||
		(m_pMapChip->getMapChipData(MapPosiinonY - 4, MapPosiinonX - 1) == 8))
	{
		DescriptionNumberdecision = Number2;
	}
}
