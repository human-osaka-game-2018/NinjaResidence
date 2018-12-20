#pragma once

#include "DirectX.h"
#include "BlockInf.h"
#include "BaseGimmick.h"

class Water : public BaseGimmick
{
private:
	CUSTOMVERTEX WaterSIZE[4];
	float WaterX1;
	float WaterY1;
	float WaterX2;
	float WaterY2;
	bool flag = false;
public:
	void Activate();
	void Render(int MapScrollY, int MapScrollX, bool MapDataReverse ,float CELL_SIZE, std::string TextureKey, CUSTOMVERTEX* TextureSize);
	Water(BlockInf Gimmick, DirectX* pDirectX);
	~Water();
};