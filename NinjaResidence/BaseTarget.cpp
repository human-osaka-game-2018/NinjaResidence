#include "BaseTarget.h"
#include "TargetandGimmickType.h"

BaseTarget::BaseTarget(BlockInf Target, BlockInf Gimmick, DirectX* pDirectX)
	:TargetIfno(Target), GimmickInfo(Gimmick), m_pDirectX(pDirectX)
{
	switch (GimmickInfo.m_type)
	{
	case BT_PARTITIONBOARD:
		m_pBaseGimmick = new PartitionBoard(Gimmick, pDirectX);
		break;
	case BT_WATER:
		m_pBaseGimmick = new Water(Gimmick, pDirectX);
		break;
	case BT_FALLROCK:
		m_pBaseGimmick = new FallRock(Gimmick, pDirectX);
		break;
	}
}

BaseTarget::~BaseTarget()
{
	delete m_pBaseGimmick;
	m_pBaseGimmick = NULL;
}

void BaseTarget::Activate()
{
	ActivateTarget();
}

void BaseTarget::ActivateGimmick()
{
	m_pBaseGimmick->Activate();
}
