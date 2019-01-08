#include "BaseTarget.h"
#include "TargetandGimmickType.h"

BaseTarget::BaseTarget(BlockInfo Target, BlockInfo Gimmick, DirectX* pDirectX)
	:m_TargetInfo(Target), m_GimmickInfo(Gimmick), m_pDirectX(pDirectX)
{
	for (int i = 0; i < 4; ++i) {
		m_TargetVertex[i].color = 0xFFFFFFFF;
	}

	switch (m_GimmickInfo.GimmickType)
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
