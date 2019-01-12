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
}


void Torch::Render(int MapScrollY, int MapScrollX, MapDataState MapDataReverse)
{
	m_TargetPosX = m_TargetInfo.PositionX;
	m_TargetPosY = m_TargetInfo.PositionY;
	if (MapDataReverse == true && m_TargetInfo.MapDataState == SURFACE)
	{
		m_TargetVertex[0].x = (CELL_SIZE * m_TargetPosX) + MapScrollX;
		m_TargetVertex[0].y = (CELL_SIZE * m_TargetPosY) + MapScrollY;
		m_TargetVertex[1].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + CELL_SIZE;
		m_TargetVertex[1].y = (CELL_SIZE * m_TargetPosY) + MapScrollY;
		m_TargetVertex[2].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + CELL_SIZE;
		m_TargetVertex[2].y = (CELL_SIZE * m_TargetPosY) + MapScrollY + CELL_SIZE;
		m_TargetVertex[3].x = (CELL_SIZE * m_TargetPosX) + MapScrollX;
		m_TargetVertex[3].y = (CELL_SIZE * m_TargetPosY) + MapScrollY + CELL_SIZE;

		m_TargetVertex[0].tu = 400.0f / 512.0f;
		m_TargetVertex[1].tu = 480.0f / 512.0f;
		m_TargetVertex[2].tu = 480.0f / 512.0f;
		m_TargetVertex[3].tu = 400.0f / 512.0f;

		m_TargetVertex[0].tv = 0;
		m_TargetVertex[1].tv = 0;
		m_TargetVertex[2].tv = 80.0f / 512.0f;
		m_TargetVertex[3].tv = 80.0f / 512.0f;

		m_pDirectX->DrawTexture("BLOCK_INTEGRATION_A_TEX", m_TargetVertex);
	}
	if (MapDataReverse == false && m_TargetInfo.MapDataState == REVERSE)
	{
		m_TargetVertex[0].x = (CELL_SIZE * m_TargetPosX) + MapScrollX;
		m_TargetVertex[0].y = (CELL_SIZE * m_TargetPosY) + MapScrollY;
		m_TargetVertex[1].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + CELL_SIZE;
		m_TargetVertex[1].y = (CELL_SIZE * m_TargetPosY) + MapScrollY;
		m_TargetVertex[2].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + CELL_SIZE;
		m_TargetVertex[2].y = (CELL_SIZE * m_TargetPosY) + MapScrollY + CELL_SIZE;
		m_TargetVertex[3].x = (CELL_SIZE * m_TargetPosX) + MapScrollX;
		m_TargetVertex[3].y = (CELL_SIZE * m_TargetPosY) + MapScrollY + CELL_SIZE;

		m_TargetVertex[0].tu = 400.0f / 512.0f;;
		m_TargetVertex[1].tu = 480.0f / 512.0f;;
		m_TargetVertex[2].tu = 480.0f / 512.0f;;
		m_TargetVertex[3].tu = 400.0f / 512.0f;;

		m_TargetVertex[0].tv = 0;
		m_TargetVertex[1].tv = 0;
		m_TargetVertex[2].tv = 80.0f / 512.0f;
		m_TargetVertex[3].tv = 80.0f / 512.0f;

		m_pDirectX->DrawTexture("BLOCK_INTEGRATION_A_TEX", m_TargetVertex);
	}

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
}
