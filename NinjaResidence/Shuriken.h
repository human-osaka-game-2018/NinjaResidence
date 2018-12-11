/**
* @file Shuriken.h
* @brief 手裏剣クラス
* @author Toshiya Matsuoka
*/

#pragma once
#include "GAMESCENE.h"
#include "Object.h"
#include "MapChip.h"

class Object;

class Shuriken :public Object
{
public:
	/*
	*キー入力時の内部処理関数
	*/
	void KeyOperation(KeyInput vec);


	bool PermitThrow();


	void Update();
	void Render();
	void Reverse(Object* MapChip);


	Shuriken(DirectX* pDirectX, SoundsManager* pSoundManager, Object* MapChip, GameChara* GameChara);
	~Shuriken();
	bool GetActive() { return isActive; };
private:
	CENTRAL_STATE m_Shuriken = { 500,0,20,20 };
	CENTRAL_STATE m_DirectionArrow = { 500,0,100,20 };
	CUSTOMVERTEX m_DisplayCoordinate[4];
	CUSTOMVERTEX m_WorldCoordinate[4];
	Object* m_pMapChip = NULL;
	GameChara * m_pGameChara = NULL;
	bool isActive = false;
	bool isChoseDeg = false;

	float DirectionDeg = 0;
	//! キャラの向きの判別の為
	float Direction = PlayerAnimation::FACING_NOTHING;

	float MoveSpeed = 10.f;
	void InitPosition();

};
