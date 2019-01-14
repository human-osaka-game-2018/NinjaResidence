/**
* @file Torch.cpp
* @brief Torchクラス
* @author Kojiro Kawahara
*/
#include "Torch.h"
#include "DirectX.h"
#include "TargetandGimmickType.h"

Torch::Torch(BlockInfo Target, BlockInfo Gimmick, DirectX* pDirectX) :BaseTarget(Target, Gimmick, pDirectX)
{

}

Torch::~Torch()
{

}


void Torch::ActivateTarget()
{
	m_pBaseGimmick->Activate();
}

void Torch::Update()
{
	m_pBaseGimmick->Update();
}


void Torch::Render(int MapScrollY, int MapScrollX, MapDataState MapDataReverse)
{
	if (m_GimmickInfo.GimmickType == BT_PARTITIONBOARD)
	{
		m_pBaseGimmick->Render(MapScrollY, MapScrollX, MapDataReverse);
	}
	if (m_GimmickInfo.GimmickType == BT_FALLROCK)
	{
		m_pBaseGimmick->Render(MapScrollY, MapScrollX, MapDataReverse);
	}
	if (m_GimmickInfo.GimmickType == BT_WATER)
	{
		m_pBaseGimmick->Render(MapScrollY, MapScrollX, MapDataReverse);
	}
	if (MapDataReverse != m_TargetInfo.MapDataState)
	{
		return;
	}
	m_TargetPosX = m_TargetInfo.PositionX;
	m_TargetPosY = m_TargetInfo.PositionY;

	m_TargetVertex[0].x = (CELL_SIZE * m_TargetPosX) + MapScrollX;
	m_TargetVertex[0].y = (CELL_SIZE * m_TargetPosY) + MapScrollY;
	m_TargetVertex[1].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + CELL_SIZE;
	m_TargetVertex[1].y = (CELL_SIZE * m_TargetPosY) + MapScrollY;
	m_TargetVertex[2].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + CELL_SIZE;
	m_TargetVertex[2].y = (CELL_SIZE * m_TargetPosY) + MapScrollY + CELL_SIZE * 3;
	m_TargetVertex[3].x = (CELL_SIZE * m_TargetPosX) + MapScrollX;
	m_TargetVertex[3].y = (CELL_SIZE * m_TargetPosY) + MapScrollY + CELL_SIZE * 3;

	m_TargetVertex[0].tu = BLOCK_INTEGRATION_WIDTH * 3;
	m_TargetVertex[1].tu = BLOCK_INTEGRATION_WIDTH * 4;
	m_TargetVertex[2].tu = BLOCK_INTEGRATION_WIDTH * 4;
	m_TargetVertex[3].tu = BLOCK_INTEGRATION_WIDTH * 3;

	m_TargetVertex[0].tv = BLOCK_INTEGRATION_HEIGHT * 3;
	m_TargetVertex[1].tv = BLOCK_INTEGRATION_HEIGHT * 3;
	m_TargetVertex[2].tv = BLOCK_INTEGRATION_HEIGHT * 5;
	m_TargetVertex[3].tv = BLOCK_INTEGRATION_HEIGHT * 5;

	m_pDirectX->DrawTexture("BLOCK_INTEGRATION_A_TEX", m_TargetVertex);

}
