#pragma once

#include <windows.h>
#include "BaseGimmick.h"
#include "PartitionBoard.h"
#include "Water.h"
#include "FallRock.h"
#include "BlockInf.h"
#include "DirectX.h"


class BaseTarget
{
protected:
	BaseGimmick* m_pBaseGimmick = NULL;
	DirectX* m_pDirectX = NULL;
	BlockInf TargetIfno;
	BlockInf GimmickInfo;
public:
	BlockInf* GetTargetInfo() { return &TargetIfno; }
	void Activate();
	virtual void ActivateTarget() = 0;
	void ActivateGimmick();
	virtual void Render(int MapScrollY, int MapScrollX,bool MapDataReverse, float CELL_SIZE, std::string TextureKey, CUSTOMVERTEX* TextureSize) = 0;
	BaseTarget(BlockInf Target, BlockInf Gimmick, DirectX* pDirectX);
	~BaseTarget();
};
