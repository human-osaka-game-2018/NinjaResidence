#include "FallRock.h"
#include <string>


FallRock::FallRock(BlockInfo Gimmick, DirectX* pDirectX) :BaseGimmick(Gimmick, pDirectX)
{
	m_pDirectX = pDirectX;
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

	//—Ž‚¿‚éŠâ‚Ì“®‚«
	m_QuantityOfMovement += 10.f;
}

void FallRock::Render(int MapScrollY, int MapScrollX, MapDataState MapDataReverse)
{
	if (MapDataReverse != m_GimmickInfo.MapDataState)
	{
		return;
	}

	m_GimmickPosX = m_GimmickInfo.PositionX;
	m_GimmickPosY = m_GimmickInfo.PositionY;

	m_GimmickVertex[0].x = (CELL_SIZE * m_GimmickPosX) + MapScrollX;
	m_GimmickVertex[0].y = (CELL_SIZE * m_GimmickPosY) + MapScrollY + m_QuantityOfMovement;
	m_GimmickVertex[1].x = (CELL_SIZE * (m_GimmickPosX + 2)) + MapScrollX;
	m_GimmickVertex[1].y = (CELL_SIZE * m_GimmickPosY) + MapScrollY + m_QuantityOfMovement;
	m_GimmickVertex[2].x = (CELL_SIZE * (m_GimmickPosX + 2)) + MapScrollX;
	m_GimmickVertex[2].y = (CELL_SIZE * (m_GimmickPosY + 2)) + MapScrollY + m_QuantityOfMovement;
	m_GimmickVertex[3].x = (CELL_SIZE * m_GimmickPosX) + MapScrollX;
	m_GimmickVertex[3].y = (CELL_SIZE * (m_GimmickPosY + 2)) + MapScrollY + m_QuantityOfMovement;

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
