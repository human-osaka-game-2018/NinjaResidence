/**
* @file BaseTarget.h
* @brief BaseTargetクラス
* @author Kojiro Kawahara
*/
#pragma once

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
	virtual void Update() = 0;
	void ActivateGimmick();
	virtual void Render(int MapScrollY, int MapScrollX, MapDataState MapDataReverse) = 0;
	BaseTarget(BlockInfo Target, BlockInfo Gimmick, DirectX* pDirectX);
	virtual ~BaseTarget();
	virtual float GetGimmickPosition(bool isAxisX, MapDataState MapDataReverse) { return m_pBaseGimmick->GetGimmickPosition(isAxisX, MapDataReverse); };
	int GetGimmickYPos() { return m_GimmickInfo.PositionY; };
	int GetGimmickXPos() { return m_GimmickInfo.PositionX; };
	bool GetGimmickActive(int PosX); 
protected:
	BaseGimmick * m_pBaseGimmick = NULL;
	DirectX* m_pDirectX = NULL;
	BlockInfo m_TargetInfo;
	BlockInfo m_GimmickInfo;
	CUSTOMVERTEX m_TargetVertex[4];

	int m_TargetPosX;
	int m_TargetPosY;
	bool m_isSwitchedOn = false;

};
