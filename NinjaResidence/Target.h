#pragma once

#include "BaseTarget.h"
#include "BlockInf.h"
#include "Object.h"

class Target :public BaseTarget
{
private:

public:
	void ActivateTarget();
	void Render(int MapScrollY, int MapScrollX, float CELL_SIZE, std::string TextureKey, CUSTOMVERTEX* TextureSize);
	Target(BlockInf Target, BlockInf Gimmick, DirectX* pDirectX);
	~Target();
};
