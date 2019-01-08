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
	//—Ž‚¿‚éŠâ‚Ì“®‚«

}

void FallRock::Render(int MapScrollY, int MapScrollX, bool MapDataReverse)
{
	m_GimmickPosX = m_GimmickInfo.PositionX;
	m_GimmickPosY = m_GimmickInfo.PositionY;

	GimmickVertex[0].x = (CELL_SIZE * m_GimmickPosX) + MapScrollX;
	GimmickVertex[0].y = (CELL_SIZE * m_GimmickPosY) + MapScrollY;
	GimmickVertex[1].x = (CELL_SIZE * (m_GimmickPosX + 2)) + MapScrollX;
	GimmickVertex[1].y = (CELL_SIZE * m_GimmickPosY) + MapScrollY;
	GimmickVertex[2].x = (CELL_SIZE * (m_GimmickPosX + 2)) + MapScrollX;
	GimmickVertex[2].y = (CELL_SIZE * (m_GimmickPosY + 2)) + MapScrollY;
	GimmickVertex[3].x = (CELL_SIZE * m_GimmickPosX) + MapScrollX;
	GimmickVertex[3].y = (CELL_SIZE * (m_GimmickPosY + 2)) + MapScrollY;

	GimmickVertex[0].tu = 240.0f / 512.0f;
	GimmickVertex[1].tu = 400.0f / 512.0f;
	GimmickVertex[2].tu = 400.0f / 512.0f;
	GimmickVertex[3].tu = 240.0f / 512.0f;

	GimmickVertex[0].tv = 0;
	GimmickVertex[1].tv = 0;
	GimmickVertex[2].tv = 400.0f / 512.0f;
	GimmickVertex[3].tv = 400.0f / 512.0f;
	m_pDirectX->DrawTexture("BLOCK_INTEGRATION_B_TEX", GimmickVertex);
}
