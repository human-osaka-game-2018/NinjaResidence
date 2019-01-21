/**
* @file HighShuriken.h
* @brief 高等手裏剣クラス
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
	* @brief キー入力時の内部処理関数
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
	const float MoveSpeed = 10.f;
	void InitPosition();
	/*
	* @brief 投擲起動処理
	* @return 投げられたらtrue
	* @details 投擲前に角度指定フェイズを挟む
	*/
	bool PermitActive();
	int m_ropeX;
	int m_ropeY;
	bool isOperation = false;
};

