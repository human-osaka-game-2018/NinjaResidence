#pragma once

#include "DirectX.h"
#include "BaseGimmick.h"
#include "TargetandGimmickType.h"

class FallRock : public BaseGimmick
{
public:
	void Activate();
	void Render(int MapScrollY, int MapScrollX, bool MapDataReverse);
	FallRock(BlockInfo Gimmick, DirectX* pDirectX);
	virtual ~FallRock();
private:
};
