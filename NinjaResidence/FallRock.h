#pragma once

#include "DirectX.h"
#include "BaseGimmick.h"
#include "TargetandGimmickType.h"


class FallRock : public BaseGimmick
{
public:
	void Activate();
	void Update();
	void Render(int MapScrollY, int MapScrollX, MapDataState MapDataReverse);
	FallRock(BlockInfo Gimmick, DirectX* pDirectX, MapChip* pMapChip);
	virtual ~FallRock();
private:
	MapChip * m_pMapChip = NULL;
};
