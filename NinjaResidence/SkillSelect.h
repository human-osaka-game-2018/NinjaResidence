/**
* @file SkillSelect.h
* @brief 忍術選択UI
* @author Toshiya Matsuoka
*/
#pragma once
#include "Object.h"

enum Skill {
	SHURIKEN,
	CLAWSHOT,
	FIRE_ART,
	HIGH_SHURIKEN_ART,
	MAX_ITEM,
};

class SkillSelect :public Object
{
public:
	void KeyOperation(KeyDirection vec);
	void Update();
	void Render();
	SkillSelect(DirectX* pDirectX, SoundOperater* pSoundOperater, bool* m_EnableSkill);
	~SkillSelect();
	int GetSkillNum() {
		return m_SkillNum;
	}
private:
	CENTRAL_STATE m_SelectUI = { 100,50,75,30 };
	CENTRAL_STATE m_SkillUI = { 100,50,30,30 };

	std::string m_SkillTexKey = "CROSS_TEX";
	int m_SkillNum = SHURIKEN;
	DWORD m_Color = 0xFFFFFFFF;
	bool* m_EnableSkill = NULL;

	void SkillTransUp();
	void SkillTransDown();

};
