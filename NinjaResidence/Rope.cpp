/**
* @file Rope.cpp
* @brief Ropeクラス
* @author Toshiya Matsuoka
*/
#include "Rope.h"



Rope::Rope(BlockInfo Target, BlockInfo Gimmick, DirectX* pDirectX, SoundOperater* pSoundOperater) :BaseTarget(Target, Gimmick, pDirectX,pSoundOperater)
{
}


Rope::~Rope()
{
}

void Rope::ActivateTarget()
{
	m_pBaseGimmick->Activate();
	m_pSoundOperater->Start("CUT_OFF", false);

	m_isActive = true;
}

void Rope::Update()
{
	m_pBaseGimmick->Update();
	if (m_isActive) {
		m_Movement += 1.5f;
		m_CellSize = CELL_SIZE *0.5f;
	}
}


void Rope::Render(int MapScrollY, int MapScrollX, MapDataState MapDataReverse)
{
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

	if (MapDataReverse != m_TargetInfo.MapDataState)
	{
		return;
	}
	m_TargetPosX = m_TargetInfo.PositionX;
	m_TargetPosY = m_TargetInfo.PositionY;
	m_TargetVertex[0].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + 5;
	m_TargetVertex[0].y = (CELL_SIZE * (m_TargetPosY - 1)) + MapScrollY;
	m_TargetVertex[1].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + 5 + CELL_SIZE;
	m_TargetVertex[1].y = (CELL_SIZE * (m_TargetPosY - 1)) + MapScrollY;
	m_TargetVertex[2].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + 5 + CELL_SIZE;
	m_TargetVertex[2].y = (CELL_SIZE * m_TargetPosY) + MapScrollY + m_CellSize;
	m_TargetVertex[3].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + 5;
	m_TargetVertex[3].y = (CELL_SIZE * m_TargetPosY) + MapScrollY + m_CellSize;

	m_TargetVertex[0].tu = BLOCK_INTEGRATION_WIDTH * 6;
	m_TargetVertex[1].tu = 1;
	m_TargetVertex[2].tu = 1;
	m_TargetVertex[3].tu = BLOCK_INTEGRATION_WIDTH * 6;

	m_TargetVertex[0].tv = 0;
	m_TargetVertex[1].tv = 0;
	m_TargetVertex[2].tv = 0.5;
	m_TargetVertex[3].tv = 0.5;

	m_pDirectX->DrawTexture("BLOCK_INTEGRATION_B_TEX", m_TargetVertex);
	if (m_isActive) {
		CUSTOMVERTEX DivededRope[4];
		DivededRope[0].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + 5;
		DivededRope[0].y = (CELL_SIZE * (m_TargetPosY - 1)) + MapScrollY + m_Movement;
		DivededRope[1].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + CELL_SIZE + 5;
		DivededRope[1].y = (CELL_SIZE * (m_TargetPosY - 1)) + MapScrollY + m_Movement;
		DivededRope[2].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + CELL_SIZE + 5;
		DivededRope[2].y = (CELL_SIZE * m_TargetPosY) + MapScrollY + m_CellSize + m_Movement;
		DivededRope[3].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + 5;
		DivededRope[3].y = (CELL_SIZE * m_TargetPosY) + MapScrollY + m_CellSize + m_Movement;

		DivededRope[0].tu = BLOCK_INTEGRATION_WIDTH * 6;
		DivededRope[1].tu = 1;
		DivededRope[2].tu = 1;
		DivededRope[3].tu = BLOCK_INTEGRATION_WIDTH * 6;

		DivededRope[0].tv = 0;
		DivededRope[1].tv = 0;
		DivededRope[2].tv = 0.5;
		DivededRope[3].tv = 0.5;

		m_pDirectX->DrawTexture("BLOCK_INTEGRATION_B_TEX", DivededRope);
	}
}

