#include "PartitionBoard.h"
#include <string>

PartitionBoard::PartitionBoard(BlockInfo Gimmick, DirectX* pDirectX) :BaseGimmick(Gimmick, pDirectX)
{
	m_pDirectX = pDirectX;
	PartitionBoardStateFlag = true;
}

PartitionBoard::~PartitionBoard()
{

}

void PartitionBoard::Activate()
{
	m_isActive = true;
}

void PartitionBoard::Update()
{
	if (!m_isActive) return;
	//ŽdØ‚è”Â‚Ì“®‚«
	while (m_WorldPosBottom >= 0.f)
	{
		m_WorldPosBottom -= 10.f;
		break;
	}
	if (m_WorldPosBottom <= 0.f)
	{
		m_isActive = false;
	}

}


void PartitionBoard::Render(int MapScrollY, int MapScrollX, MapDataState MapDataReverse)
{
	if (MapDataReverse != m_GimmickInfo.MapDataState)
	{
		return;
	}
	m_GimmickPosX = m_GimmickInfo.PositionX;
	m_GimmickPosY = m_GimmickInfo.PositionY;
	if (m_isFirstTime == false)
	{
		m_WorldPosLeft = (CELL_SIZE * m_GimmickPosX);
		m_WorldPosTop = (CELL_SIZE * m_GimmickPosY);
		m_WorldPosRight = (CELL_SIZE * (m_GimmickPosX + 3));
		m_WorldPosBottom = (CELL_SIZE * (m_GimmickPosY + 15));
		m_isFirstTime = true;
	}
	if (MapDataReverse == m_GimmickInfo.MapDataState)
	{
		m_GimmickVertex[0].x = m_WorldPosLeft + MapScrollX;
		m_GimmickVertex[0].y = m_WorldPosTop + MapScrollY;
		m_GimmickVertex[1].x = m_WorldPosRight + MapScrollX;
		m_GimmickVertex[1].y = m_WorldPosTop + MapScrollY;
		m_GimmickVertex[2].x = m_WorldPosRight + MapScrollX;
		m_GimmickVertex[2].y = m_WorldPosBottom + MapScrollY;
		m_GimmickVertex[3].x = m_WorldPosLeft + MapScrollX;
		m_GimmickVertex[3].y = m_WorldPosBottom + MapScrollY;

		m_GimmickVertex[0].tu = BLOCK_INTEGRATION_WIDTH * 3;
		m_GimmickVertex[1].tu = BLOCK_INTEGRATION_WIDTH * 5;
		m_GimmickVertex[2].tu = BLOCK_INTEGRATION_WIDTH * 5;
		m_GimmickVertex[3].tu = BLOCK_INTEGRATION_WIDTH * 3;

		m_GimmickVertex[0].tv = 0;
		m_GimmickVertex[1].tv = 0;
		m_GimmickVertex[2].tv = BLOCK_INTEGRATION_WIDTH * 5;
		m_GimmickVertex[3].tv = BLOCK_INTEGRATION_WIDTH * 5;

		m_pDirectX->DrawTexture("BLOCK_INTEGRATION_B_TEX", m_GimmickVertex);
	}

}
