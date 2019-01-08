#pragma once

#include "DirectX.h"
#include "BaseGimmick.h"

class Water : public BaseGimmick
{
public:
	void Activate();
	void Render(int MapScrollY, int MapScrollX, bool MapDataReverse );
	Water(BlockInfo Gimmick, DirectX* pDirectX);
	~Water();
private:
};