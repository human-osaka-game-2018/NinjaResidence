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

void Water::Render(int MapScrollY, int MapScrollX, bool MapDataReverse, float CELL_SIZE, std::string TextureKey, CUSTOMVERTEX* TextureSize)
{
	m_GimmickPosX = m_GimmickInfo.PositionX;
	m_GimmickPosY = m_GimmickInfo.PositionY;
	WaterSIZE[0] = TextureSize[0];
	WaterSIZE[1] = TextureSize[1];
	WaterSIZE[2] = TextureSize[2];
	WaterSIZE[3] = TextureSize[3];

	if (flag == false)
	{
		WorldPosLeft = (CELL_SIZE * m_GimmickPosX);
		WorldPosTop = (CELL_SIZE * m_GimmickPosY);
		WorldPosRight = (CELL_SIZE * (m_GimmickPosX + 1));
		WorldPosBottom = (CELL_SIZE * (m_GimmickPosY + 1));
		flag = true;
	}

	TextureSize[0].x = WorldPosLeft + MapScrollX;
	TextureSize[0].y = WorldPosTop + MapScrollY;
	TextureSize[1].x = WorldPosRight + MapScrollX;
	TextureSize[1].y = WorldPosTop + MapScrollY;
	TextureSize[2].x = WorldPosRight + MapScrollX;
	TextureSize[2].y = WorldPosBottom + MapScrollY;
	TextureSize[3].x = WorldPosLeft + MapScrollX;
	TextureSize[3].y = WorldPosBottom + MapScrollY;

	TextureSize[0].tu = 240.0f / 512.0f;
	TextureSize[1].tu = 320.0f / 512.0f;
	TextureSize[2].tu = 320.0f / 512.0f;
	TextureSize[3].tu = 240.0f / 512.0f;

	TextureSize[0].tv = 80.0f / 512.0f;
	TextureSize[1].tv = 80.0f / 512.0f;
	TextureSize[2].tv = 160.0f / 512.0f;
	TextureSize[3].tv = 160.0f / 512.0f;
	m_pDirectX->DrawTexture(TextureKey, TextureSize);
}
