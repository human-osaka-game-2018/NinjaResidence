#include "PartitionBoard.h"
#include <string>

PartitionBoard::PartitionBoard(BlockInfo Gimmick, DirectX* pDirectX) :BaseGimmick(Gimmick, pDirectX)
{
	m_pDirectX = pDirectX;
}

PartitionBoard::~PartitionBoard()
{

}

void PartitionBoard::Activate()
{
	//ŽdØ‚è”Â‚Ì“®‚«
	while (WorldPosBottom >= 0.f)
	{
		WorldPosBottom -= 10.f;
		break;
	}
	if (WorldPosBottom >= 0.f)
	{

	}
}


void PartitionBoard::Render(int MapScrollY, int MapScrollX, bool MapDataReverse, float CELL_SIZE, std::string TextureKey, CUSTOMVERTEX* TextureSize)
{
	m_GimmickPosX = m_GimmickInfo.PositionX;
	m_GimmickPosY = m_GimmickInfo.PositionY;
	if (flag == false)
	{
		WorldPosLeft = (CELL_SIZE * m_GimmickPosX);
		WorldPosTop = (CELL_SIZE * m_GimmickPosY);
		WorldPosRight = (CELL_SIZE * (m_GimmickPosX + 3));
		WorldPosBottom = (CELL_SIZE * (m_GimmickPosY + 15));
		flag = true;
	}
	if (MapDataReverse == true && m_GimmickInfo.MapDataState == SURFACE)
	{
		PartitionSIZE[0] = TextureSize[0];
		PartitionSIZE[1] = TextureSize[1];
		PartitionSIZE[2] = TextureSize[2];
		PartitionSIZE[3] = TextureSize[3];


		TextureSize[0].x = WorldPosLeft + MapScrollX;
		TextureSize[0].y = WorldPosTop + MapScrollY;
		TextureSize[1].x = WorldPosRight + MapScrollX;
		TextureSize[1].y = WorldPosTop + MapScrollY;
		TextureSize[2].x = WorldPosRight + MapScrollX;
		TextureSize[2].y = WorldPosBottom + MapScrollY;
		TextureSize[3].x = WorldPosLeft + MapScrollX;
		TextureSize[3].y = WorldPosBottom + MapScrollY;

		TextureSize[0].tu = 240.0f / 512.0f;
		TextureSize[1].tu = 400.0f / 512.0f;
		TextureSize[2].tu = 400.0f / 512.0f;
		TextureSize[3].tu = 240.0f / 512.0f;

		TextureSize[0].tv = 0;
		TextureSize[1].tv = 0;
		TextureSize[2].tv = 400.0f / 512.0f;
		TextureSize[3].tv = 400.0f / 512.0f;

		m_pDirectX->DrawTexture(TextureKey, TextureSize);
	}

	if (MapDataReverse == false && m_GimmickInfo.MapDataState == REVERSE)
	{
		PartitionSIZE[0] = TextureSize[0];
		PartitionSIZE[1] = TextureSize[1];
		PartitionSIZE[2] = TextureSize[2];
		PartitionSIZE[3] = TextureSize[3];

		
		TextureSize[0].x = WorldPosLeft + MapScrollX;
		TextureSize[0].y = WorldPosTop + MapScrollY;
		TextureSize[1].x = WorldPosRight + MapScrollX;
		TextureSize[1].y = WorldPosTop + MapScrollY;
		TextureSize[2].x = WorldPosRight + MapScrollX;
		TextureSize[2].y = WorldPosBottom + MapScrollY;
		TextureSize[3].x = WorldPosLeft + MapScrollX;
		TextureSize[3].y = WorldPosBottom + MapScrollY;

		TextureSize[0].tu = 240.0f / 512.0f;
		TextureSize[1].tu = 400.0f / 512.0f;
		TextureSize[2].tu = 400.0f / 512.0f;
		TextureSize[3].tu = 240.0f / 512.0f;

		TextureSize[0].tv = 0;
		TextureSize[1].tv = 0;
		TextureSize[2].tv = 400.0f / 512.0f;
		TextureSize[3].tv = 400.0f / 512.0f;
		m_pDirectX->DrawTexture(TextureKey, TextureSize);
	}
}
