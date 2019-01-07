/**
* @file Shuriken.h
* @brief 手裏剣クラス
* @author Toshiya Matsuoka
*/

#pragma once
#include "GAMESCENE.h"
#include "MapChip.h"

class Object;

class Shuriken :public Object
{
public:
	/*
	* @brief キー入力時の内部処理関数
	*/
	void KeyOperation(KeyDirection vec);

	/*
	* @brief 投擲起動処理
	* @return 投げられたらtrue
	* @details 投擲前に角度指定フェイズを挟む
	*/
	bool PermitThrow();


	void Update();
	void Render();
	void Reverse(Object* MapChip);


	Shuriken(DirectX* pDirectX, SoundOperater* pSoundOperater, Object* MapChip, GameChara* GameChara);
	~Shuriken();
	bool GetActive() { return m_isActive; };
private:
	CENTRAL_STATE m_Shuriken = { 500,0,20,20 };
	CENTRAL_STATE m_DirectionArrow = { 500,0,100,20 };
	CUSTOMVERTEX m_DisplayCoordinate[4];
	CUSTOMVERTEX m_WorldCoordinate[4];
	Object* m_pMapChip = NULL;
	GameChara * m_pGameChara = NULL;
	bool m_isActive = false;
	bool m_isChoseDeg = false;

	int m_MapPositionX;
	int m_MapPositionY;

	float m_DirectionDeg = 0;
	//! キャラの向きの判別の為
	float m_Direction = PlayerAnimation::FACING_NOTHING;

	const float MoveSpeed = 10.f;
	void InitPosition();

};
