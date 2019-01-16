#pragma once

#include "DirectX.h"
#include "BaseGimmick.h"
#include "TargetandGimmickType.h"


class ClingBoard : public BaseGimmick
{
public:
	void Activate();
	void Update();
	void Render(int MapScrollY, int MapScrollX, MapDataState MapDataReverse);
	ClingBoard(BlockInfo Gimmick, DirectX* pDirectX, MapChip* pMapChip);
	virtual ~ClingBoard();
private:
	MapChip * m_pMapChip = NULL;
};
