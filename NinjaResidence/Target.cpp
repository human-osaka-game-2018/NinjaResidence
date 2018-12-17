#include "Target.h"
#include "DirectX.h"


Target::Target(BlockInf Target, BlockInf Gimmick, DirectX* pDirectX) :BaseTarget(Target, Gimmick, pDirectX)
{

}

Target::~Target()
{

}


void Target::ActivateTarget()
{
	m_pBaseGimmick->Activate();
}


void Target::Render(int MapScrollY, int MapScrollX, float CELL_SIZE, std::string TextureKey, CUSTOMVERTEX* TextureSize)
{
	int x = TargetIfno.m_x;
	int y = TargetIfno.m_y;
	float WIDTH = 80.0f / 512.0f;
	float HEIGHT = 80.0f / 512.0f;
	TextureSize[0].x = (CELL_SIZE * x) + MapScrollX + 5;
	TextureSize[0].y = (CELL_SIZE * (y - 1)) + MapScrollY;
	TextureSize[1].x = (CELL_SIZE * x) + MapScrollX + CELL_SIZE + 5;
	TextureSize[1].y = (CELL_SIZE * (y - 1)) + MapScrollY;
	TextureSize[2].x = (CELL_SIZE * x) + MapScrollX + CELL_SIZE + 5;
	TextureSize[2].y = (CELL_SIZE * y) + MapScrollY + CELL_SIZE;
	TextureSize[3].x = (CELL_SIZE * x) + MapScrollX + 5;
	TextureSize[3].y = (CELL_SIZE * y) + MapScrollY + CELL_SIZE;

	TextureSize[0].tu = 0;
	TextureSize[1].tu = WIDTH;
	TextureSize[2].tu = WIDTH;
	TextureSize[3].tu = 0;

	TextureSize[0].tv = 0.32f;
	TextureSize[1].tv = 0.32f;
	TextureSize[2].tv = HEIGHT + 0.32f;
	TextureSize[3].tv = HEIGHT + 0.32f;
	m_pDirectX->DrawTexture(TextureKey, TextureSize);
	m_pBaseGimmick->Render(MapScrollY, MapScrollX, CELL_SIZE, "BLOCK_INTEGRATION_B_TEX", TextureSize);
}
