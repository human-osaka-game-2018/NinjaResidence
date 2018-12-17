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
	float PartitionX3;
	float PartitionY3;
	bool flag = false;
public:
	void Activate();
	void Render(int MapScrollY, int MapScrollX, float CELL_SIZE, std::string TextureKey, CUSTOMVERTEX* TextureSize);
	PartitionBoard(BlockInf Gimmick, DirectX* pDirectX);
	~PartitionBoard();
};