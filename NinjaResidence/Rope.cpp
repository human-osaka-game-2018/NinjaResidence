#include "Rope.h"



Rope::Rope(BlockInfo Target, BlockInfo Gimmick, DirectX* pDirectX) :BaseTarget(Target, Gimmick, pDirectX)
{
}


Rope::~Rope()
{
}

void Rope::ActivateTarget()
{
	m_pBaseGimmick->Activate();
}

void Rope::Update()
{
	m_pBaseGimmick->Update();
}


void Rope::Render(int MapScrollY, int MapScrollX, MapDataState MapDataReverse)
{
	if (MapDataReverse != m_TargetInfo.MapDataState)
	{
		return;
	}
	m_TargetPosX = m_TargetInfo.PositionX;
	m_TargetPosY = m_TargetInfo.PositionY;
	//TODO:的のオンオフ切り替え
	if (MapDataReverse == m_TargetInfo.MapDataState)
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

		m_TargetVertex[0].tv = 480.f/512.f;
		m_TargetVertex[1].tv = 480.f/512.f;
		m_TargetVertex[2].tv = 1;
		m_TargetVertex[3].tv = 1;

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
