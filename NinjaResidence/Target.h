#pragma once

#include "BaseTarget.h"
#include "Object.h"

class MapReverse;

class Target :public BaseTarget
{
public:
	void ActivateTarget();
	void Update();
	void Render(int MapScrollY, int MapScrollX, MapDataState MapDataReverse);
	Target(BlockInfo Target, BlockInfo Gimmick, DirectX* pDirectX);
	virtual ~Target();
private:

};
