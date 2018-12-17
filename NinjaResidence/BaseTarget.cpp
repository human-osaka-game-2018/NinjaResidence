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
		//m_pBaseGimmick = new Water();
		break;
	case BT_FALLROCK:
		//m_pBaseGimmick = new FallRock();
		break;
	}
}

BaseTarget::~BaseTarget()
{
	delete m_pBaseGimmick;
}

void BaseTarget::Activate()
{
	ActivateTarget();
}

void BaseTarget::ActivateGimmick()
{
	m_pBaseGimmick->Activate();
}
