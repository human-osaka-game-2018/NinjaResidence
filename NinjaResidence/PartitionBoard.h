#pragma once

#include "DirectX.h"
#include "BaseGimmick.h"

class PartitionBoard : public BaseGimmick
{
public:
	void Activate();
	void Render(int MapScrollY, int MapScrollX, bool MapDataReverse);
	PartitionBoard(BlockInfo Gimmick, DirectX* pDirectX);
	virtual ~PartitionBoard();
private:
};
