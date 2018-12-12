/**
* @file Shuriken.h
* @brief �藠���N���X
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
	* @brief �L�[���͎��̓��������֐�
	*/
	void KeyOperation(KeyInput vec);

	/*
	* @brief �����N������
	* @return ������ꂽ��true
	* @details �����O�Ɋp�x�w��t�F�C�Y������
	*/
	bool PermitThrow();


	void Update();
	void Render();
	void Reverse(Object* MapChip);


	Shuriken(DirectX* pDirectX, SoundsManager* pSoundManager, Object* MapChip, GameChara* GameChara);
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

	float m_DirectionDeg = 0;
	//! �L�����̌����̔��ʂ̈�
	float m_Direction = PlayerAnimation::FACING_NOTHING;

	const float MoveSpeed = 10.f;
	void InitPosition();

};
