#include "PartitionBoard.h"
#include <string>

PartitionBoard::PartitionBoard(BlockInfo Gimmick, DirectX* pDirectX) :BaseGimmick(Gimmick, pDirectX)
{
	m_pDirectX = pDirectX;
}

PartitionBoard::~PartitionBoard()
{

}

void PartitionBoard::Activate()
{
	//ŽdØ‚è”Â‚Ì“®‚«
	while (WorldPosBottom >= 0.f)
	{
		WorldPosBottom -= 10.f;
		break;
	}
	if (WorldPosBottom >= 0.f)
	{

	}
}


void PartitionBoard::Render(int MapScrollY, int MapScrollX, bool MapDataReverse)
{
	m_GimmickPosX = m_GimmickInfo.PositionX;
	m_GimmickPosY = m_GimmickInfo.PositionY;
	if (m_isActive == false)
	{
		WorldPosLeft = (CELL_SIZE * m_GimmickPosX);
		WorldPosTop = (CELL_SIZE * m_GimmickPosY);
		WorldPosRight = (CELL_SIZE * (m_GimmickPosX + 3));
		WorldPosBottom = (CELL_SIZE * (m_GimmickPosY + 15));
		m_isActive = true;
	}
	if (MapDataReverse == true && m_GimmickInfo.MapDataState == SURFACE)
	{


		GimmickVertex[0].x = WorldPosLeft + MapScrollX;
		GimmickVertex[0].y = WorldPosTop + MapScrollY;
		GimmickVertex[1].x = WorldPosRight + MapScrollX;
		GimmickVertex[1].y = WorldPosTop + MapScrollY;
		GimmickVertex[2].x = WorldPosRight + MapScrollX;
		GimmickVertex[2].y = WorldPosBottom + MapScrollY;
		GimmickVertex[3].x = WorldPosLeft + MapScrollX;
		GimmickVertex[3].y = WorldPosBottom + MapScrollY;

		GimmickVertex[0].tu = 240.0f / 512.0f;
		GimmickVertex[1].tu = 400.0f / 512.0f;
		GimmickVertex[2].tu = 400.0f / 512.0f;
		GimmickVertex[3].tu = 240.0f / 512.0f;

		GimmickVertex[0].tv = 0;
		GimmickVertex[1].tv = 0;
		GimmickVertex[2].tv = 400.0f / 512.0f;
		GimmickVertex[3].tv = 400.0f / 512.0f;

		m_pDirectX->DrawTexture("BLOCK_INTEGRATION_B_TEX", GimmickVertex);
	}

	if (MapDataReverse == false && m_GimmickInfo.MapDataState == REVERSE)
	{
		
		GimmickVertex[0].x = WorldPosLeft + MapScrollX;
		GimmickVertex[0].y = WorldPosTop + MapScrollY;
		GimmickVertex[1].x = WorldPosRight + MapScrollX;
		GimmickVertex[1].y = WorldPosTop + MapScrollY;
		GimmickVertex[2].x = WorldPosRight + MapScrollX;
		GimmickVertex[2].y = WorldPosBottom + MapScrollY;
		GimmickVertex[3].x = WorldPosLeft + MapScrollX;
		GimmickVertex[3].y = WorldPosBottom + MapScrollY;

		GimmickVertex[0].tu = 240.0f / 512.0f;
		GimmickVertex[1].tu = 400.0f / 512.0f;
		GimmickVertex[2].tu = 400.0f / 512.0f;
		GimmickVertex[3].tu = 240.0f / 512.0f;

		GimmickVertex[0].tv = 0;
		GimmickVertex[1].tv = 0;
		GimmickVertex[2].tv = 400.0f / 512.0f;
		GimmickVertex[3].tv = 400.0f / 512.0f;
		m_pDirectX->DrawTexture("BLOCK_INTEGRATION_B_TEX", GimmickVertex);
	}
}
