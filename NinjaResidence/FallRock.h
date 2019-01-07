#pragma once

#include "DirectX.h"
#include "BlockInf.h"
#include "BaseGimmick.h"
#include "TargetandGimmickType.h"

class FallRock : public BaseGimmick
{
private:
	CUSTOMVERTEX FallRockSIZE[4];
	bool flag = false;
public:
	void Activate();
	void Render(int MapScrollY, int MapScrollX, bool MapDataReverse, float CELL_SIZE, std::string TextureKey, CUSTOMVERTEX* TextureSize);
	FallRock(BlockInfo Gimmick, DirectX* pDirectX);
	virtual ~FallRock();
};
