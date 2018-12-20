#pragma once

#include "DirectX.h"
#include "BaseGimmick.h"

class Water : public BaseGimmick
{
public:
	void Activate();
	void Update();
	void Render(int MapScrollY, int MapScrollX, MapDataState MapDataReverse );
	Water(BlockInfo Gimmick, DirectX* pDirectX);
	~Water();
private:

};
