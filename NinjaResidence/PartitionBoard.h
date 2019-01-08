#pragma once

#include "DirectX.h"
#include "BaseGimmick.h"

class PartitionBoard : public BaseGimmick
{
public:
	void Activate();
	void Update();
	void Render(int MapScrollY, int MapScrollX, MapDataState MapDataReverse);
	PartitionBoard(BlockInfo Gimmick, DirectX* pDirectX);
	virtual ~PartitionBoard();
private:
};
