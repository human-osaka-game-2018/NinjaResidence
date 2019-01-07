#include "PartitionBoard.h"
#include <string>

PartitionBoard::PartitionBoard(BlockInf Gimmick, DirectX* pDirectX) :BaseGimmick(Gimmick, pDirectX)
{
	m_pDirectX = pDirectX;
}

PartitionBoard::~PartitionBoard()
{

}

void PartitionBoard::Activate()
{
	//ŽdØ‚è”Â‚Ì“®‚«
	while (PartitionY2 >= 0.f)
	{
		PartitionY2 -= 10.f;
		break;
	}
	if (PartitionY2 >= 0.f)
	{

	}
}


void PartitionBoard::Render(int MapScrollY, int MapScrollX, bool MapDataReverse, float CELL_SIZE, std::string TextureKey, CUSTOMVERTEX* TextureSize)
{
	int x = GimmickInfo.m_x;
	int y = GimmickInfo.m_y;
	if (flag == false)
	{
		PartitionX1 = (CELL_SIZE * x);
		PartitionY1 = (CELL_SIZE * y);
		PartitionX2 = (CELL_SIZE * (x + 3));
		PartitionY2 = (CELL_SIZE * (y + 15));
		flag = true;
	}
	if (MapDataReverse == true && GimmickInfo.MapDataState == SURFACE)
	{
		PartitionSIZE[0] = TextureSize[0];
		PartitionSIZE[1] = TextureSize[1];
		PartitionSIZE[2] = TextureSize[2];
		PartitionSIZE[3] = TextureSize[3];


		TextureSize[0].x = PartitionX1 + MapScrollX;
		TextureSize[0].y = PartitionY1 + MapScrollY;
		TextureSize[1].x = PartitionX2 + MapScrollX;
		TextureSize[1].y = PartitionY1 + MapScrollY;
		TextureSize[2].x = PartitionX2 + MapScrollX;
		TextureSize[2].y = PartitionY2 + MapScrollY;
		TextureSize[3].x = PartitionX1 + MapScrollX;
		TextureSize[3].y = PartitionY2 + MapScrollY;

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

	if (MapDataReverse == false && GimmickInfo.MapDataState == REVERSE)
	{
		PartitionSIZE[0] = TextureSize[0];
		PartitionSIZE[1] = TextureSize[1];
		PartitionSIZE[2] = TextureSize[2];
		PartitionSIZE[3] = TextureSize[3];

		
		TextureSize[0].x = PartitionX1 + MapScrollX;
		TextureSize[0].y = PartitionY1 + MapScrollY;
		TextureSize[1].x = PartitionX2 + MapScrollX;
		TextureSize[1].y = PartitionY1 + MapScrollY;
		TextureSize[2].x = PartitionX2 + MapScrollX;
		TextureSize[2].y = PartitionY2 + MapScrollY;
		TextureSize[3].x = PartitionX1 + MapScrollX;
		TextureSize[3].y = PartitionY2 + MapScrollY;

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
