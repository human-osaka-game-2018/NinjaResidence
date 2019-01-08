#pragma once

#include <windows.h>
#include "BaseGimmick.h"
#include "PartitionBoard.h"
#include "Water.h"
#include "FallRock.h"
#include "DirectX.h"


class BaseTarget
{
public:
	BlockInfo* GetTargetInfo() { return &m_TargetInfo; }
	void Activate();
	virtual void ActivateTarget() = 0;
	void ActivateGimmick();
	virtual void Render(int MapScrollY, int MapScrollX,bool MapDataReverse) = 0;
	BaseTarget(BlockInfo Target, BlockInfo Gimmick, DirectX* pDirectX);
	virtual ~BaseTarget();
protected:
	BaseGimmick * m_pBaseGimmick = NULL;
	DirectX* m_pDirectX = NULL;
	BlockInfo m_TargetInfo;
	BlockInfo m_GimmickInfo;
	CUSTOMVERTEX TargetVertex[4];

	int m_TargetPosX;
	int m_TargetPosY;
	bool m_isSwitchedOn = false;

};
