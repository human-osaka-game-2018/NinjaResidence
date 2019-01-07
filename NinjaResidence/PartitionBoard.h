#pragma once

#include "DirectX.h"
#include "BlockInf.h"
#include "BaseGimmick.h"

class PartitionBoard : public BaseGimmick
{
public:
	void Activate();
	void Render(int MapScrollY, int MapScrollX, bool MapDataReverse, float CELL_SIZE, std::string TextureKey, CUSTOMVERTEX* TextureSize);
	PartitionBoard(BlockInfo Gimmick, DirectX* pDirectX);
	virtual ~PartitionBoard();
private:
	CUSTOMVERTEX PartitionSIZE[4];
	bool flag = false;
};
