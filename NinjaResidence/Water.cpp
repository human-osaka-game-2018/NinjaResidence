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

}

void Water::Render(int MapScrollY, int MapScrollX, bool MapDataReverse)
{
	m_GimmickPosX = m_GimmickInfo.PositionX;
	m_GimmickPosY = m_GimmickInfo.PositionY;

	if (m_isActive == false)
	{
		WorldPosLeft = (CELL_SIZE * m_GimmickPosX);
		WorldPosTop = (CELL_SIZE * m_GimmickPosY);
		WorldPosRight = (CELL_SIZE * (m_GimmickPosX + 1));
		WorldPosBottom = (CELL_SIZE * (m_GimmickPosY + 1));
		m_isActive = true;
	}

	GimmickVertex[0].x = WorldPosLeft + MapScrollX;
	GimmickVertex[0].y = WorldPosTop + MapScrollY;
	GimmickVertex[1].x = WorldPosRight + MapScrollX;
	GimmickVertex[1].y = WorldPosTop + MapScrollY;
	GimmickVertex[2].x = WorldPosRight + MapScrollX;
	GimmickVertex[2].y = WorldPosBottom + MapScrollY;
	GimmickVertex[3].x = WorldPosLeft + MapScrollX;
	GimmickVertex[3].y = WorldPosBottom + MapScrollY;

	GimmickVertex[0].tu = 240.0f / 512.0f;
	GimmickVertex[1].tu = 320.0f / 512.0f;
	GimmickVertex[2].tu = 320.0f / 512.0f;
	GimmickVertex[3].tu = 240.0f / 512.0f;

	GimmickVertex[0].tv = 80.0f / 512.0f;
	GimmickVertex[1].tv = 80.0f / 512.0f;
	GimmickVertex[2].tv = 160.0f / 512.0f;
	GimmickVertex[3].tv = 160.0f / 512.0f;
	m_pDirectX->DrawTexture("BLOCK_INTEGRATION_A_TEX", GimmickVertex);
}
