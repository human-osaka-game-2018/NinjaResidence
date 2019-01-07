#include "Target.h"
#include "DirectX.h"
#include "TargetandGimmickType.h"

Target::Target(BlockInfo Target, BlockInfo Gimmick, DirectX* pDirectX) :BaseTarget(Target, Gimmick, pDirectX)
{

}

Target::~Target()
{
	delete m_pBaseGimmick;
	m_pBaseGimmick = NULL;
}


void Target::ActivateTarget()
{
	m_pBaseGimmick->Activate();
}


void Target::Render(int MapScrollY, int MapScrollX, bool MapDataReverse, float CELL_SIZE, std::string TextureKey, CUSTOMVERTEX* TextureSize)
{
	m_TargetPosX = m_TargetInfo.PositionX;
	m_TargetPosY = m_TargetInfo.PositionY;
	if (MapDataReverse == true && m_TargetInfo.MapDataState == SURFACE)
	{
		float WIDTH = 80.0f / 512.0f;
		float HEIGHT = 80.0f / 512.0f;
		TextureSize[0].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + 5;
		TextureSize[0].y = (CELL_SIZE * (m_TargetPosY - 1)) + MapScrollY;
		TextureSize[1].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + CELL_SIZE + 5;
		TextureSize[1].y = (CELL_SIZE * (m_TargetPosY - 1)) + MapScrollY;
		TextureSize[2].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + CELL_SIZE + 5;
		TextureSize[2].y = (CELL_SIZE * m_TargetPosY) + MapScrollY + CELL_SIZE;
		TextureSize[3].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + 5;
		TextureSize[3].y = (CELL_SIZE * m_TargetPosY) + MapScrollY + CELL_SIZE;

		TextureSize[0].tu = 0;
		TextureSize[1].tu = WIDTH;
		TextureSize[2].tu = WIDTH;
		TextureSize[3].tu = 0;

		TextureSize[0].tv = HEIGHT*2;
		TextureSize[1].tv = HEIGHT*2;
		TextureSize[2].tv = HEIGHT*3;
		TextureSize[3].tv = HEIGHT*3;

		m_pDirectX->DrawTexture(TextureKey, TextureSize);
	}
	if (MapDataReverse == false && m_TargetInfo.MapDataState == REVERSE)
	{
		float WIDTH = 80.0f / 512.0f;
		float HEIGHT = 80.0f / 512.0f;
		TextureSize[0].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + 5;
		TextureSize[0].y = (CELL_SIZE * (m_TargetPosY - 1)) + MapScrollY;
		TextureSize[1].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + CELL_SIZE + 5;
		TextureSize[1].y = (CELL_SIZE * (m_TargetPosY - 1)) + MapScrollY;
		TextureSize[2].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + CELL_SIZE + 5;
		TextureSize[2].y = (CELL_SIZE * m_TargetPosY) + MapScrollY + CELL_SIZE;
		TextureSize[3].x = (CELL_SIZE * m_TargetPosX) + MapScrollX + 5;
		TextureSize[3].y = (CELL_SIZE * m_TargetPosY) + MapScrollY + CELL_SIZE;

		TextureSize[0].tu = 0;
		TextureSize[1].tu = WIDTH;
		TextureSize[2].tu = WIDTH;
		TextureSize[3].tu = 0;

		TextureSize[0].tv = HEIGHT * 2;
		TextureSize[1].tv = HEIGHT * 2;
		TextureSize[2].tv = HEIGHT * 3;
		TextureSize[3].tv = HEIGHT * 3;


		m_pDirectX->DrawTexture(TextureKey, TextureSize);
	}

	if (m_GimmickInfo.Type == BT_WATER)
	{
		m_pBaseGimmick->Render(MapScrollY, MapScrollX, MapDataReverse, CELL_SIZE, "BLOCK_INTEGRATION_A_TEX", TextureSize);
	}
	if (m_GimmickInfo.Type == BT_PARTITIONBOARD)
	{
		m_pBaseGimmick->Render(MapScrollY, MapScrollX, MapDataReverse, CELL_SIZE, "BLOCK_INTEGRATION_B_TEX", TextureSize);
	}
	if (m_GimmickInfo.Type == BT_FALLROCK)
	{
		m_pBaseGimmick->Render(MapScrollY, MapScrollX, MapDataReverse, CELL_SIZE, "BLOCK_INTEGRATION_B_TEX", TextureSize);
	}
}
