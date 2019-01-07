#pragma once

#include "DirectX.h"
#include "BlockInf.h"
#include "BaseGimmick.h"

class PartitionBoard : public BaseGimmick
{
private:
	CUSTOMVERTEX PartitionSIZE[4];
	float PartitionX1;
	float PartitionY1;
	float PartitionX2;
	float PartitionY2;
	bool flag = false;
public:
	void Activate();
	void Render(int MapScrollY, int MapScrollX, bool MapDataReverse, float CELL_SIZE, std::string TextureKey, CUSTOMVERTEX* TextureSize);
	PartitionBoard(BlockInf Gimmick, DirectX* pDirectX);
	virtual ~PartitionBoard();
};
