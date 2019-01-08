#include "Water.h"
#include <string>


Water::Water(BlockInfo Gimmick, DirectX* pDirectX) :BaseGimmick(Gimmick, pDirectX)
{
	m_pDirectX = pDirectX;
}

Water::~Water()
{

}

void Water::Activate()
{
	//…‚Ì“®‚«
	m_isActive = true;
}

void Water::Update()
{
	if (!m_isActive) return;
	m_QuantityOfMovement -= 10.f;
}

void Water::Render(int MapScrollY, int MapScrollX, MapDataState MapDataReverse)
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
		m_WorldPosRight = (CELL_SIZE * (m_GimmickPosX + 1));
		m_WorldPosBottom = (CELL_SIZE * (m_GimmickPosY + 1));
		m_isFirstTime = true;
	}

	m_GimmickVertex[0].x = m_WorldPosLeft + MapScrollX;
	m_GimmickVertex[0].y = m_WorldPosTop + MapScrollY + m_QuantityOfMovement;
	m_GimmickVertex[1].x = m_WorldPosRight + MapScrollX;
	m_GimmickVertex[1].y = m_WorldPosTop + MapScrollY + m_QuantityOfMovement;
	m_GimmickVertex[2].x = m_WorldPosRight + MapScrollX;
	m_GimmickVertex[2].y = m_WorldPosBottom + MapScrollY + m_QuantityOfMovement;
	m_GimmickVertex[3].x = m_WorldPosLeft + MapScrollX;
	m_GimmickVertex[3].y = m_WorldPosBottom + MapScrollY + m_QuantityOfMovement;

	m_GimmickVertex[0].tu = BLOCK_INTEGRATION_WIDTH * 3;
	m_GimmickVertex[1].tu = BLOCK_INTEGRATION_WIDTH * 4;
	m_GimmickVertex[2].tu = BLOCK_INTEGRATION_WIDTH * 4;
	m_GimmickVertex[3].tu = BLOCK_INTEGRATION_WIDTH * 3;

	m_GimmickVertex[0].tv = BLOCK_INTEGRATION_WIDTH;
	m_GimmickVertex[1].tv = BLOCK_INTEGRATION_WIDTH;
	m_GimmickVertex[2].tv = BLOCK_INTEGRATION_WIDTH * 2;
	m_GimmickVertex[3].tv = BLOCK_INTEGRATION_WIDTH * 2;

	m_pDirectX->DrawTexture("BLOCK_INTEGRATION_A_TEX", m_GimmickVertex);
}
