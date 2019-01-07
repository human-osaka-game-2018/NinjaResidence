#pragma once

#include "DirectX.h"
#include "BlockInf.h"
#include "BaseGimmick.h"

class Water : public BaseGimmick
{
public:
	void Activate();
	void Render(int MapScrollY, int MapScrollX, bool MapDataReverse ,float CELL_SIZE, std::string TextureKey, CUSTOMVERTEX* TextureSize);
	Water(BlockInfo Gimmick, DirectX* pDirectX);
	~Water();
private:
	CUSTOMVERTEX WaterSIZE[4];
	bool flag = false;
};