#include "Water.h"
#include <string>

int x ;
int y ;

Water::Water(BlockInf Gimmick, DirectX* pDirectX) :BaseGimmick(Gimmick, pDirectX)
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
	x = GimmickInfo.m_x;
	y = GimmickInfo.m_y;
	WaterSIZE[0] = TextureSize[0];
	WaterSIZE[1] = TextureSize[1];
	WaterSIZE[2] = TextureSize[2];
	WaterSIZE[3] = TextureSize[3];

	if (flag == false)
	{
		WaterX1 = (CELL_SIZE * x);
		WaterY1 = (CELL_SIZE * y);
		WaterX2 = (CELL_SIZE * (x + 1));
		WaterY2 = (CELL_SIZE * (y + 1));
		flag = true;
	}

	TextureSize[0].x = WaterX1 + MapScrollX;
	TextureSize[0].y = WaterY1 + MapScrollY;
	TextureSize[1].x = WaterX2 + MapScrollX;
	TextureSize[1].y = WaterY1 + MapScrollY;
	TextureSize[2].x = WaterX2 + MapScrollX;
	TextureSize[2].y = WaterY2 + MapScrollY;
	TextureSize[3].x = WaterX1 + MapScrollX;
	TextureSize[3].y = WaterY2 + MapScrollY;

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
