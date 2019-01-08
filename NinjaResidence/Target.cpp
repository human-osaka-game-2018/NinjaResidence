#include "Target.h"
#include "DirectX.h"
#include "TargetandGimmickType.h"

Target::Target(BlockInfo Target, BlockInfo Gimmick, DirectX* pDirectX) :BaseTarget(Target, Gimmick, pDirectX)
{

}

Target::~Target()
{
	delete m_pBaseGimmick;
	m_pBaseGimmick = NULL;
}


void Target::ActivateTarget()
{
	m_pBaseGimmick->Activate();
}


void Target::Render(int MapScrollY, int MapScrollX, bool MapDataReverse)
{
	m_TargetPosX = m_TargetInfo.PositionX;
	m_TargetPosY = m_TargetInfo.PositionY;
	//TODO:的のオンオフ切り替え
	if (MapDataReverse == true && m_TargetInfo.MapDataState == SURFACE)
	{
		TargetVertex[0].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + 5;
		TargetVertex[0].y = (CELL_SIZE * (m_TargetPosY - 1)) + MapScrollY;
		TargetVertex[1].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + CELL_SIZE + 5;
		TargetVertex[1].y = (CELL_SIZE * (m_TargetPosY - 1)) + MapScrollY;
		TargetVertex[2].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + CELL_SIZE + 5;
		TargetVertex[2].y = (CELL_SIZE * m_TargetPosY) + MapScrollY + CELL_SIZE;
		TargetVertex[3].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + 5;
		TargetVertex[3].y = (CELL_SIZE * m_TargetPosY) + MapScrollY + CELL_SIZE;

		TargetVertex[0].tu = 0;
		TargetVertex[1].tu = BLOCK_INTEGRATION_WIDTH;
		TargetVertex[2].tu = BLOCK_INTEGRATION_WIDTH;
		TargetVertex[3].tu = 0;
		
		TargetVertex[0].tv = BLOCK_INTEGRATION_WIDTH * 2;
		TargetVertex[1].tv = BLOCK_INTEGRATION_WIDTH * 2;
		TargetVertex[2].tv = BLOCK_INTEGRATION_WIDTH * 3;
		TargetVertex[3].tv = BLOCK_INTEGRATION_WIDTH * 3;

		m_pDirectX->DrawTexture("BLOCK_INTEGRATION_A_TEX", TargetVertex);
	}
	if (MapDataReverse == false && m_TargetInfo.MapDataState == REVERSE)
	{
		TargetVertex[0].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + 5;
		TargetVertex[0].y = (CELL_SIZE * (m_TargetPosY - 1)) + MapScrollY;
		TargetVertex[1].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + CELL_SIZE + 5;
		TargetVertex[1].y = (CELL_SIZE * (m_TargetPosY - 1)) + MapScrollY;
		TargetVertex[2].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + CELL_SIZE + 5;
		TargetVertex[2].y = (CELL_SIZE * m_TargetPosY) + MapScrollY + CELL_SIZE;
		TargetVertex[3].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + 5;
		TargetVertex[3].y = (CELL_SIZE * m_TargetPosY) + MapScrollY + CELL_SIZE;

		TargetVertex[0].tu = 0;
		TargetVertex[1].tu = BLOCK_INTEGRATION_WIDTH;
		TargetVertex[2].tu = BLOCK_INTEGRATION_WIDTH;
		TargetVertex[3].tu = 0;

		TargetVertex[0].tv = BLOCK_INTEGRATION_WIDTH * 2;
		TargetVertex[1].tv = BLOCK_INTEGRATION_WIDTH * 2;
		TargetVertex[2].tv = BLOCK_INTEGRATION_WIDTH * 3;
		TargetVertex[3].tv = BLOCK_INTEGRATION_WIDTH * 3;


		m_pDirectX->DrawTexture("BLOCK_INTEGRATION_A_TEX", TargetVertex);
	}

	if (m_GimmickInfo.Type == BT_WATER)
	{
		m_pBaseGimmick->Render(MapScrollY, MapScrollX, MapDataReverse);
	}
	if (m_GimmickInfo.Type == BT_PARTITIONBOARD)
	{
		m_pBaseGimmick->Render(MapScrollY, MapScrollX, MapDataReverse);
	}
	if (m_GimmickInfo.Type == BT_FALLROCK)
	{
		m_pBaseGimmick->Render(MapScrollY, MapScrollX, MapDataReverse);
	}
}
