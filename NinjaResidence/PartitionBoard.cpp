﻿/**
* @file PartitionBoard.cpp
* @brief PartitionBoardクラス
* @author Kojiro Kawahara
*/
#include "PartitionBoard.h"
#include <string>
#include "MapChip.h"

PartitionBoard::PartitionBoard(BlockInfo Gimmick, DirectX* pDirectX, MapChip* pMapChip, SoundOperater* pSoundOperater) :BaseGimmick(Gimmick, pDirectX,pSoundOperater)
{
	m_pDirectX = pDirectX;
	m_pMapChip = pMapChip;
	m_pMapChip->MapDataVectorHitSet(m_GimmickInfo.PositionY, m_GimmickInfo.PositionX, 13, 3);
}

PartitionBoard::~PartitionBoard()
{

}


void PartitionBoard::Activate()
{
	m_isActive = true;
	m_pSoundOperater->Start("DOOR",false);
}


void PartitionBoard::Update()
{
	if (!m_isActive) return;
	//仕切り板の動き
	while (m_WorldPosBottom >= 0.f)
	{
		m_WorldPosBottom -= 20.f;
		break;
	}
	if (m_WorldPosBottom <= 0.f)
	{
		m_isActive = false;
		m_pSoundOperater->Stop("DOOR");
		m_pMapChip->MapDataVectorZeroSet(m_GimmickInfo.PositionY, m_GimmickInfo.PositionX, 13, 3);
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
		m_GimmickVertex[0].x = static_cast<float>(m_WorldPosLeft + MapScrollX);
		m_GimmickVertex[0].y = static_cast<float>(m_WorldPosTop + MapScrollY);
		m_GimmickVertex[1].x = static_cast<float>(m_WorldPosRight + MapScrollX);
		m_GimmickVertex[1].y = static_cast<float>(m_WorldPosTop + MapScrollY);
		m_GimmickVertex[2].x = static_cast<float>(m_WorldPosRight + MapScrollX);
		m_GimmickVertex[2].y = static_cast<float>(m_WorldPosBottom + MapScrollY);
		m_GimmickVertex[3].x = static_cast<float>(m_WorldPosLeft + MapScrollX);
		m_GimmickVertex[3].y = static_cast<float>(m_WorldPosBottom + MapScrollY);

		m_GimmickVertex[0].tu = BLOCK_INTEGRATION_WIDTH * 3.f;
		m_GimmickVertex[1].tu = BLOCK_INTEGRATION_WIDTH * 5.f;
		m_GimmickVertex[2].tu = BLOCK_INTEGRATION_WIDTH * 5.f;
		m_GimmickVertex[3].tu = BLOCK_INTEGRATION_WIDTH * 3.f;

		m_GimmickVertex[0].tv = 0.f;
		m_GimmickVertex[1].tv = 0.f;
		m_GimmickVertex[2].tv = BLOCK_INTEGRATION_WIDTH * 5.f;
		m_GimmickVertex[3].tv = BLOCK_INTEGRATION_WIDTH * 5.f;

		m_pDirectX->DrawTexture("BLOCK_INTEGRATION_B_TEX", m_GimmickVertex);
	}

}
