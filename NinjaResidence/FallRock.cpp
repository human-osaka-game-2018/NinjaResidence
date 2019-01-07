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

void FallRock::Render(int MapScrollY, int MapScrollX, bool MapDataReverse, float CELL_SIZE, std::string TextureKey, CUSTOMVERTEX* TextureSize)
{
	m_GimmickPosX = m_GimmickInfo.PositionX;
	m_GimmickPosY = m_GimmickInfo.PositionY;
	FallRockSIZE[0] = TextureSize[0];
	FallRockSIZE[1] = TextureSize[1];
	FallRockSIZE[2] = TextureSize[2];
	FallRockSIZE[3] = TextureSize[3];

	TextureSize[0].x = (CELL_SIZE * m_GimmickPosX) + MapScrollX;
	TextureSize[0].y = (CELL_SIZE * m_GimmickPosY) + MapScrollY;
	TextureSize[1].x = (CELL_SIZE * (m_GimmickPosX + 2)) + MapScrollX;
	TextureSize[1].y = (CELL_SIZE * m_GimmickPosY) + MapScrollY;
	TextureSize[2].x = (CELL_SIZE * (m_GimmickPosX + 2)) + MapScrollX;
	TextureSize[2].y = (CELL_SIZE * (m_GimmickPosY + 2)) + MapScrollY;
	TextureSize[3].x = (CELL_SIZE * m_GimmickPosX) + MapScrollX;
	TextureSize[3].y = (CELL_SIZE * (m_GimmickPosY + 2)) + MapScrollY;

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
