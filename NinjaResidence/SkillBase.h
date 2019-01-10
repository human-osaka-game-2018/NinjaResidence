#pragma once
#include "GameChara.h"
#include "SkillSelect.h"



class SkillBase :	public Object
{
public:
	/*
	* @brief ƒL[“ü—Í‚Ì“à•”ˆ—ŠÖ”
	*/
	virtual void KeyOperation(KeyDirection vec) {};
	virtual bool Update() { return true; };
	virtual void Render() {};
	virtual void Reverse(Object* MapChip) {};


	SkillBase(DirectX* pDirectX, SoundOperater* pSoundOperater, Object* MapChip, GameChara* GameChara) ;
	virtual ~SkillBase();
	bool GetActive() { return m_isActive; };
protected:
	Object * m_pMapChip = NULL;
	GameChara * m_pGameChara = NULL;
	bool m_isActive = false;
	bool m_isChoseDeg = false;

	int m_MapPositionX;
	int m_MapPositionY;

	float m_DirectionDeg = 0;
	//! ƒLƒƒƒ‰‚ÌŒü‚«‚Ì”»•Ê‚Ìˆ×
	float m_Direction = PlayerAnimation::FACING_NOTHING;

	void InitPosition() {};
	SkillType m_SkillType;
};

