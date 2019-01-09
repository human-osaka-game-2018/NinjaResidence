#include "Torch.h"
#include "DirectX.h"
#include "TargetandGimmickType.h"

Torch::Torch(BlockInf Target, BlockInf Gimmick, DirectX* pDirectX) :BaseTarget(Target, Gimmick, pDirectX)
{

}

Torch::~Torch()
{

}


void Torch::ActivateTarget()
{
		m_pBaseGimmick->Activate();
}


void Torch::Render(int MapScrollY, int MapScrollX, bool MapDataReverse, float CELL_SIZE, std::string TextureKey, CUSTOMVERTEX* TextureSize)
{
	int x = TargetIfno.m_x;
	int y = TargetIfno.m_y;
	if (MapDataReverse == true && TargetIfno.MapDataState == Surface)
	{
		TextureSize[0].x = (CELL_SIZE * x) + MapScrollX;
		TextureSize[0].y = (CELL_SIZE * y) + MapScrollY;
		TextureSize[1].x = (CELL_SIZE * x) + MapScrollX + CELL_SIZE;
		TextureSize[1].y = (CELL_SIZE * y) + MapScrollY;
		TextureSize[2].x = (CELL_SIZE * x) + MapScrollX + CELL_SIZE;
		TextureSize[2].y = (CELL_SIZE * y) + MapScrollY + CELL_SIZE;
		TextureSize[3].x = (CELL_SIZE * x) + MapScrollX;
		TextureSize[3].y = (CELL_SIZE * y) + MapScrollY + CELL_SIZE;

		TextureSize[0].tu = 400.0f / 512.0f;
		TextureSize[1].tu = 480.0f / 512.0f;
		TextureSize[2].tu = 480.0f / 512.0f;
		TextureSize[3].tu = 400.0f / 512.0f;

		TextureSize[0].tv = 0;
		TextureSize[1].tv = 0;
		TextureSize[2].tv = 80.0f / 512.0f;
		TextureSize[3].tv = 80.0f / 512.0f;

		m_pDirectX->DrawTexture(TextureKey, TextureSize);
	}
	if (MapDataReverse == false && TargetIfno.MapDataState == Reverse)
	{
		TextureSize[0].x = (CELL_SIZE * x) + MapScrollX;
		TextureSize[0].y = (CELL_SIZE * y) + MapScrollY;
		TextureSize[1].x = (CELL_SIZE * x) + MapScrollX + CELL_SIZE;
		TextureSize[1].y = (CELL_SIZE * y) + MapScrollY;
		TextureSize[2].x = (CELL_SIZE * x) + MapScrollX + CELL_SIZE;
		TextureSize[2].y = (CELL_SIZE * y) + MapScrollY + CELL_SIZE;
		TextureSize[3].x = (CELL_SIZE * x) + MapScrollX;
		TextureSize[3].y = (CELL_SIZE * y) + MapScrollY + CELL_SIZE;

		TextureSize[0].tu = 400.0f / 512.0f;;
		TextureSize[1].tu = 480.0f / 512.0f;;
		TextureSize[2].tu = 480.0f / 512.0f;;
		TextureSize[3].tu = 400.0f / 512.0f;;

		TextureSize[0].tv = 0;
		TextureSize[1].tv = 0;
		TextureSize[2].tv = 80.0f / 512.0f;
		TextureSize[3].tv = 80.0f / 512.0f;

		m_pDirectX->DrawTexture(TextureKey, TextureSize);
	}

	if (GimmickIfno.m_type == BT_PARTITIONBOARD)
	{
		m_pBaseGimmick->Render(MapScrollY, MapScrollX, MapDataReverse, CELL_SIZE, "BLOCK_INTEGRATION_B_TEX", TextureSize);
	}
	if (GimmickIfno.m_type == BT_FALLROCK)
	{
		m_pBaseGimmick->Render(MapScrollY, MapScrollX, MapDataReverse, CELL_SIZE, "BLOCK_INTEGRATION_B_TEX", TextureSize);
	}
	if (GimmickIfno.m_type == BT_WATER)
	{
		m_pBaseGimmick->Render(MapScrollY, MapScrollX, MapDataReverse, CELL_SIZE, "BLOCK_INTEGRATION_A_TEX", TextureSize);
	}
}
