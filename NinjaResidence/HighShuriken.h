/**
* @file HighShuriken.h
* @brief �藠���N���X
* @author Toshiya Matsuoka
*/

#pragma once
#include "SkillBase.h"
#include "MapChip.h"

class SkillBase;

class HighShuriken :public SkillBase
{
public:
	/*
	* @brief �L�[���͎��̓��������֐�
	*/
	void KeyOperation(KeyDirection vec);



	bool Update();
	void Render();
	void Reverse(Object* MapChip);


	HighShuriken(DirectX* pDirectX, SoundOperater* pSoundOperater, Object* MapChip, GameChara* GameChara);
	~HighShuriken();
	bool GetActive() { return m_isActive; };
private:
	CENTRAL_STATE m_DirectionArrow = { 500,0,100,20 };
	CUSTOMVERTEX m_DisplayCoordinate[4];
	CUSTOMVERTEX m_WorldCoordinate[4];

	bool CollisionRope();
	float PrevMapScrollX = 0;
	float PrevMapScrollY = 0;
	const float MoveSpeed = 10.f;
	void InitPosition();
	/*
	* @brief �����N������
	* @return ������ꂽ��true
	* @details �����O�Ɋp�x�w��t�F�C�Y������
	*/
	bool PermitActive();
	int m_ropeX;
	int m_ropeY;
	bool isOperation = false;
};

