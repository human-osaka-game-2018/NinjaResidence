﻿/**
* @file BaseTarget.cpp
* @brief BaseTargetクラス
* @author Kojiro Kawahara
*/
#include "BaseTarget.h"
#include "TargetandGimmickType.h"

BaseTarget::BaseTarget(BlockInfo Target, BlockInfo Gimmick, DirectX* pDirectX)
	:m_TargetInfo(Target), m_GimmickInfo(Gimmick), m_pDirectX(pDirectX)
{
	for (int i = 0; i < 4; ++i) {
		m_TargetVertex[i].color = 0xFFFFFFFF;
		m_TargetVertex[i].rhw = 1;
	}

	switch (m_GimmickInfo.GimmickType)
	{
	case BT_PARTITIONBOARD:
		m_pBaseGimmick = new PartitionBoard(Gimmick, pDirectX, m_GimmickInfo.pMapChip);
		break;
	case BT_FALLROCK:
		m_pBaseGimmick = new FallRock(Gimmick, pDirectX, m_GimmickInfo.pMapChip);
		break;
	case BT_WATER:
		m_pBaseGimmick = new Water(Gimmick, pDirectX);
		break;
	case BT_CLINGBOARD:
		m_pBaseGimmick = new ClingBoard(Gimmick, pDirectX, m_GimmickInfo.pMapChip);
		break;
	}
}

BaseTarget::~BaseTarget()
{
	delete m_pBaseGimmick;
	m_pBaseGimmick = NULL;
}

bool BaseTarget::GetGimmickActive(int PosX)
{
	if (PosX != m_GimmickInfo.PositionX) {
		return false;
	}
	return m_pBaseGimmick->GetActive();
}
void BaseTarget::Activate()
{
	ActivateTarget();
}

void BaseTarget::ActivateGimmick()
{
	m_pBaseGimmick->Activate();
}
