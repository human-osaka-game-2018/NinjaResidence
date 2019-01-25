﻿/**
* @file HighShuriken.cpp
* @brief 高等手裏剣クラス
* @author Toshiya Matsuoka
*/
#include "HighShuriken.h"
#include "XinputDevice.h"



using namespace PlayerAnimation;

HighShuriken::HighShuriken(DirectX* pDirectX, SoundOperater* pSoundOperater, Object* MapChip, GameChara* GameChara, XinputDevice* pXinputDevice) :SkillBase(pDirectX, pSoundOperater, MapChip, GameChara)
{
	m_Central = { 500,0,20,20 };
	m_pMapChip = MapChip;
	m_pGameChara = GameChara;
	m_row = m_pMapChip->GetRow();
	m_colunm = m_pMapChip->GetColunm();
	m_pXinputDevice = pXinputDevice;
	m_SkillType = HIGH_SHURIKEN_ART;
}



HighShuriken::~HighShuriken()
{

}



void HighShuriken::KeyOperation(KeyDirection vec)
{
	//Key操作での処理
	switch (vec)
	{
	case THROW:
		m_isActive = PermitActive();
		break;
	case UP:
		if (m_isActive || !m_isChoseDeg) {
			return;
		}
		m_DirectionDeg += m_Direction;
		if (m_DirectionDeg > 45) {
			m_DirectionDeg = 45;
		}
		if (m_DirectionDeg < -45) {
			m_DirectionDeg = -45;
		}
		break;
	case DOWN:
		if (m_isActive || !m_isChoseDeg) {
			return;
		}
		m_DirectionDeg -= m_Direction;
		if (m_DirectionDeg > 45) {
			m_DirectionDeg = 45;
		}
		if (m_DirectionDeg < -45) {
			m_DirectionDeg = -45;
		}
		break;

	case BIT_X_UP:
		m_DirectionDeg = InputRightStickDeg();
		break;
	case BIT_X_DOWN:
		m_DirectionDeg = InputRightStickDeg();
		break;
	case BIT_X_LEFT:
		m_DirectionDeg = InputRightStickDeg();
		break;
	case BIT_X_RIGHT:
		m_DirectionDeg = InputRightStickDeg();
		break;
	case BIT_D_UP:
		m_DirectionDeg = 90.f;
		break;
	case BIT_D_DOWN:
		m_DirectionDeg = 270.f;
		break;
	case BIT_D_LEFT:
		m_DirectionDeg = 180.f;
		break;
	case BIT_D_RIGHT:
		m_DirectionDeg = 0.f;
		break;
	case END_ART:
		InitPosition();
		break;
	}
}


bool HighShuriken::PermitActive() {
	if (!m_isChoseDeg && !m_isActive) {
		m_isChoseDeg = true;
		m_DirectionDeg = 0;
		m_Direction = static_cast<float>(m_pGameChara->GetFacing());
		return false;
	}
	if (m_isChoseDeg && !m_isActive) {
		m_Central.x = m_pGameChara->GetPositionX() + (m_Direction * m_Central.scale_x);
		m_Central.y = m_pGameChara->GetPositionY();
		PrevMapScrollX = m_MapScrollX;
		PrevMapScrollY = m_MapScrollY;
		isOperation = false;
		m_isChoseDeg = false;
		return true;
	}
	if (m_isActive) {
		return true;
	}
	return false;
}


void HighShuriken::InitPosition() {
	m_isActive = false;
	m_DirectionDeg = 0;

	m_Central.x = m_pGameChara->GetPositionX() + m_Direction * m_Central.scale_x;
	m_Central.y = m_pGameChara->GetPositionY();
}

bool HighShuriken::Update()
{
	if (m_isChoseDeg) {
		m_DirectionArrow.x = m_pGameChara->GetPositionX() + m_Direction * CELL_SIZE * 2;
		m_DirectionArrow.y = m_pGameChara->GetPositionY();
	}

	if (!m_isActive) {
		return true;
	}
	PrevMapScrollX -= m_MapScrollX;
	PrevMapScrollY -= m_MapScrollY;
	m_Central.x += (MoveSpeed * m_Direction) * std::cos(DegToRad(m_DirectionDeg)) - PrevMapScrollX;
	m_Central.y -= (MoveSpeed * m_Direction) * std::sin(DegToRad(m_DirectionDeg)) + PrevMapScrollY;
	m_MapPositionX = static_cast<int>((m_Central.x - m_MapScrollX) / CELL_SIZE);
	m_MapPositionY = static_cast<int>((m_Central.y - m_MapScrollY) / CELL_SIZE);

	if (m_Central.x < 0 || m_Central.x > DISPLAY_WIDTH || m_MapPositionX >= m_row - 1) {
		InitPosition();
	}
	if (m_MapPositionY == 0 || m_Central.y < 0 || m_Central.y > DISPLAY_HEIGHT || m_MapPositionY >= m_colunm - 1) {
		InitPosition();
	}
	int buf = m_pMapChip->GetMapChipData(m_MapPositionY, m_MapPositionX);
	if (buf > 100)
	{
		m_pMapChip->Activate(m_MapPositionX, m_MapPositionY);
		InitPosition();
	}
	else if (buf < 100 && buf > MapBlock::NONE && buf != MapBlock::START_ZONE)
	{
		m_pSoundOperater->Start("CLAWSHOT", false);
		InitPosition();
	}

	if (CollisionRope()) {
		m_pMapChip->Activate(m_ropeX, m_ropeY);

		InitPosition();
	}
	PrevMapScrollX = m_MapScrollX;
	PrevMapScrollY = m_MapScrollY;

	return true;
}


void HighShuriken::Render()
{
#ifdef _DEBUG
	RECT testName = { 0, 100, 1250, 720 };
	char TestName[ARRAY_LONG];
	sprintf_s(TestName, ARRAY_LONG, "\nDirectionDeg::%.2f", m_DirectionDeg);
	m_pDirectX->DrawWord(testName, TestName, "DEBUG_FONT", DT_RIGHT, 0xffffffff);
#endif

	static int rad = 0;
	if (!m_isChoseDeg && !m_isActive) {
		return;
	}
	if (m_isChoseDeg) {
		CUSTOMVERTEX DirectionArrowVertex[4];
		RevolveZEX(DirectionArrowVertex, DegToRad(m_DirectionDeg), m_DirectionArrow, m_DirectionArrow.x - (m_DirectionArrow.scale_x * m_Direction), m_DirectionArrow.y, 0xFFFFFFFF, 0, 0, m_Direction);
		TextureRender("ARROW_TEX", DirectionArrowVertex);
		rad = 0;
		return;
	}
	if (m_isActive) {
		CUSTOMVERTEX ShurikenVertex[4];
		static float rad = 0.f;
		rad += 10.f;
		RevolveZ(ShurikenVertex, static_cast<float>(rad), m_Central, 0xFFFFFFFF, 0.f, BLOCK_INTEGRATION_HEIGHT * 3.f, BLOCK_INTEGRATION_WIDTH, BLOCK_INTEGRATION_HEIGHT);
		m_pDirectX->DrawTexture("BLOCK_INTEGRATION_A_TEX", ShurikenVertex);
	}

}

void HighShuriken::Reverse(Object* MapChip) {
	m_pMapChip = MapChip;
	m_row = m_pMapChip->GetRow();
	m_colunm = m_pMapChip->GetColunm();
	InitPosition();
}

float HighShuriken::InputRightStickDeg() {
	int XaxisValue = m_pXinputDevice->GetAnalogRValue(ANALOG_X);
	int YaxisValue = m_pXinputDevice->GetAnalogRValue(ANALOG_Y);
	if (XaxisValue == 0 && YaxisValue == 0) { 
		return 0.f;
	}
	float Rad = static_cast<float>(std::atan2(YaxisValue, XaxisValue));
	static float Deg = 0;
	return Deg = RadToDeg(Rad);
}
