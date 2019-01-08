#pragma once
#include "BaseTarget.h"

class Rope :public BaseTarget
{
public:
	void ActivateTarget();
	void Update();
	void Render(int MapScrollY, int MapScrollX, MapDataState MapDataReverse);

	Rope(BlockInfo Target, BlockInfo Gimmick, DirectX* pDirectX);
	~Rope();
};

