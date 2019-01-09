#pragma once

#include "BaseTarget.h"
#include "BlockInf.h"
#include "Object.h"

class MapReverse;

class Torch :public BaseTarget
{
private:

public:
	void ActivateTarget();
	void Render(int MapScrollY, int MapScrollX, bool MapDataReverse, float CELL_SIZE, std::string TextureKey, CUSTOMVERTEX* TextureSize);
	Torch(BlockInf Target, BlockInf Gimmick, DirectX* pDirectX);
	~Torch();
};
