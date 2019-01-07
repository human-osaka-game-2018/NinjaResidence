#pragma once

#include "BaseTarget.h"
#include "BlockInf.h"
#include "Object.h"

class MapReverse;

class Target :public BaseTarget
{
private:

public:
	void ActivateTarget();
	void Render(int MapScrollY, int MapScrollX, bool MapDataReverse,float CELL_SIZE, std::string TextureKey, CUSTOMVERTEX* TextureSize);
	Target(BlockInf Target, BlockInf Gimmick, DirectX* pDirectX);
	virtual ~Target();
};
