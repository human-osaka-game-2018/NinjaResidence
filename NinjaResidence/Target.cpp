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

void Target::Update()
{
	m_pBaseGimmick->Update();
}


void Target::Render(int MapScrollY, int MapScrollX, MapDataState MapDataReverse)
{
	if (MapDataReverse != m_TargetInfo.MapDataState)
	{
		return;
	}
	m_TargetPosX = m_TargetInfo.PositionX;
	m_TargetPosY = m_TargetInfo.PositionY;
	//TODO:的のオンオフ切り替え
	if (MapDataReverse ==m_TargetInfo.MapDataState)
	{
		m_TargetVertex[0].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + 5;
		m_TargetVertex[0].y = (CELL_SIZE * (m_TargetPosY - 1)) + MapScrollY;
		m_TargetVertex[1].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + CELL_SIZE + 5;
		m_TargetVertex[1].y = (CELL_SIZE * (m_TargetPosY - 1)) + MapScrollY;
		m_TargetVertex[2].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + CELL_SIZE + 5;
		m_TargetVertex[2].y = (CELL_SIZE * m_TargetPosY) + MapScrollY + CELL_SIZE;
		m_TargetVertex[3].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + 5;
		m_TargetVertex[3].y = (CELL_SIZE * m_TargetPosY) + MapScrollY + CELL_SIZE;

		m_TargetVertex[0].tu = 0;
		m_TargetVertex[1].tu = BLOCK_INTEGRATION_WIDTH;
		m_TargetVertex[2].tu = BLOCK_INTEGRATION_WIDTH;
		m_TargetVertex[3].tu = 0;
		
		m_TargetVertex[0].tv = BLOCK_INTEGRATION_HEIGHT * 2;
		m_TargetVertex[1].tv = BLOCK_INTEGRATION_HEIGHT * 2;
		m_TargetVertex[2].tv = BLOCK_INTEGRATION_HEIGHT * 3;
		m_TargetVertex[3].tv = BLOCK_INTEGRATION_HEIGHT * 3;

		m_pDirectX->DrawTexture("BLOCK_INTEGRATION_A_TEX", m_TargetVertex);
	}

	if (m_GimmickInfo.GimmickType == BT_WATER)
	{
		m_pBaseGimmick->Render(MapScrollY, MapScrollX, MapDataReverse);
	}
	if (m_GimmickInfo.GimmickType == BT_PARTITIONBOARD)
	{
		m_pBaseGimmick->Render(MapScrollY, MapScrollX, MapDataReverse);
	}
	if (m_GimmickInfo.GimmickType == BT_FALLROCK)
	{
		m_pBaseGimmick->Render(MapScrollY, MapScrollX, MapDataReverse);
	}
}
