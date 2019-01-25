/**
* @file SkillBase.cpp
* @brief SkillBaseクラス
* @author Toshiya Matsuoka
*/
#include "SkillBase.h"



SkillBase::SkillBase(DirectX* pDirectX, SoundOperater* pSoundOperater, Object* MapChip, GameChara* GameChara) :Object(pDirectX, pSoundOperater)
{
	m_pMapChip = MapChip;
	m_pGameChara = GameChara;
}


SkillBase::~SkillBase()
{
}


bool SkillBase::CollisionRope()
{
	CENTRAL_STATE RopeCentral = { 0 };
	TranslateCentral_State(m_pMapChip->GetTargetPosition(BT_ROPE), &RopeCentral);

	m_ropeX = static_cast<int>((RopeCentral.x - m_MapScrollX) / CELL_SIZE);
	m_ropeY = static_cast<int>((RopeCentral.y - m_MapScrollY) / CELL_SIZE);

	return ContactSpecifyObject(&RopeCentral);
}


