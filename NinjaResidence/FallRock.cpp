/**
* @file FallRock.cpp
* @brief FallRockクラス
* @author Kojiro Kawahara
*/
#include "FallRock.h"
#include <string>
#include "MapChip.h"


FallRock::FallRock(BlockInfo Gimmick, DirectX* pDirectX, MapChip* pMapChip, SoundOperater* pSoundOperater) :BaseGimmick(Gimmick, pDirectX,pSoundOperater)
{
	m_pDirectX = pDirectX;
	m_pMapChip = pMapChip;
	m_GimmickPosX = CELL_SIZE * m_GimmickInfo.PositionX;
	m_GimmickPosY = CELL_SIZE * m_GimmickInfo.PositionY;
	m_pMapChip->MapDataVectorHitSet(m_GimmickInfo.PositionY, m_GimmickInfo.PositionX, 2, 2);
}

FallRock::~FallRock()
{

}

void FallRock::Activate()
{
	m_isActive = true;
}

void FallRock::Update()
{
	if (!m_isActive) return;

	//落ちる岩の動き
	int CheckNumber = m_pMapChip->GimmickMapDataCheck((m_GimmickPosY + (CELL_SIZE * 2) + m_QuantityOfMovement) / CELL_SIZE, m_GimmickPosX / CELL_SIZE);
	if (CheckNumber == MapBlock::NONE)
	{
		m_pMapChip->MapDataVectorZeroSet((m_GimmickPosY + m_QuantityOfMovement) / CELL_SIZE, m_GimmickInfo.PositionX, 2, 2);
		m_QuantityOfMovement += 5.f;
		m_pMapChip->MapDataVectorHitSet((m_GimmickPosY + m_QuantityOfMovement) / CELL_SIZE, m_GimmickInfo.PositionX, 2, 2);
	}
	if (CheckNumber / 100 == BT_SWITCH)
	{
		m_pMapChip->Activate((m_GimmickPosX / CELL_SIZE), (m_GimmickPosY + (CELL_SIZE * 2) + m_QuantityOfMovement) / CELL_SIZE);
	}
}

void FallRock::Render(int MapScrollY, int MapScrollX, MapDataState MapDataReverse)
{
	if (MapDataReverse != m_GimmickInfo.MapDataState)
	{
		return;
	}

	m_GimmickVertex[0].x = static_cast<float>(m_GimmickPosX + MapScrollX);
	m_GimmickVertex[0].y = static_cast<float>(m_GimmickPosY + MapScrollY + m_QuantityOfMovement);
	m_GimmickVertex[1].x = static_cast<float>(m_GimmickPosX + (CELL_SIZE * 2.f) + MapScrollX);
	m_GimmickVertex[1].y = static_cast<float>(m_GimmickPosY + MapScrollY + m_QuantityOfMovement);
	m_GimmickVertex[2].x = static_cast<float>(m_GimmickPosX + (CELL_SIZE * 2.f) + MapScrollX);
	m_GimmickVertex[2].y = static_cast<float>(m_GimmickPosY + (CELL_SIZE * 2.f) + MapScrollY + m_QuantityOfMovement);
	m_GimmickVertex[3].x = static_cast<float>(m_GimmickPosX + MapScrollX);
	m_GimmickVertex[3].y = static_cast<float>(m_GimmickPosY + (CELL_SIZE * 2.f) + MapScrollY + m_QuantityOfMovement);

	m_GimmickVertex[0].tu = BLOCK_INTEGRATION_WIDTH * 4.f;
	m_GimmickVertex[1].tu = BLOCK_INTEGRATION_WIDTH * 6.f;
	m_GimmickVertex[2].tu = BLOCK_INTEGRATION_WIDTH * 6.f;
	m_GimmickVertex[3].tu = BLOCK_INTEGRATION_WIDTH * 4.f;

	m_GimmickVertex[0].tv = BLOCK_INTEGRATION_HEIGHT * 3.f;
	m_GimmickVertex[1].tv = BLOCK_INTEGRATION_HEIGHT * 3.f;
	m_GimmickVertex[2].tv = BLOCK_INTEGRATION_HEIGHT * 5.f;
	m_GimmickVertex[3].tv = BLOCK_INTEGRATION_HEIGHT * 5.f;

	m_pDirectX->DrawTexture("BLOCK_INTEGRATION_A_TEX", m_GimmickVertex);
}
