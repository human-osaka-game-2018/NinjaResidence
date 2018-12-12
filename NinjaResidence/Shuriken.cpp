/**
* @file Shuriken.cpp
* @brief Žè— Œ•ƒNƒ‰ƒX
* @author Toshiya Matsuoka
*/
#include "Shuriken.h"
using SoundLib::SoundsManager;
using namespace PlayerAnimation;

Shuriken::Shuriken(DirectX* pDirectX, SoundsManager* pSoundManager, Object* MapChip, GameChara* GameChara) :Object(pDirectX, pSoundManager)
{
	m_pMapChip = MapChip;
	m_pGameChara = GameChara;
}



Shuriken::~Shuriken()
{

}



void Shuriken::KeyOperation(KeyInput vec)
{
	//Key‘€ì‚Å‚Ìˆ—
	switch (vec)
	{
	case THROW:
		m_isActive = PermitThrow();
		break;
	case UP:
		if (m_isActive) {
			return;
		}
		m_DirectionDeg += m_Direction;
		if (m_DirectionDeg>45) {
			m_DirectionDeg = 45;
		}
		if (m_DirectionDeg<-45) {
			m_DirectionDeg = -45;
		}
		break;
	case DOWN:
		if (m_isActive) {
			return;;
		}
		m_DirectionDeg -= m_Direction;
		if (m_DirectionDeg>45) {
			m_DirectionDeg = 45;
		}
		if (m_DirectionDeg<-45) {
			m_DirectionDeg = -45;
		}
		break;
	}
}


bool Shuriken::PermitThrow() {
	if (!m_isChoseDeg && !m_isActive) {
		m_isChoseDeg = true;
		m_Direction = static_cast<float>(m_pGameChara->GetFacing());
		return false;
	}
	if (m_isChoseDeg && !m_isActive) {
		m_Shuriken.x = m_pGameChara->GetPositionX() +( m_Direction * m_Shuriken.scale_x);
		m_Shuriken.y = m_pGameChara->GetPositionY();
		m_isChoseDeg = false;
		return true;
	}
	if (m_isActive) {
		return true;
	}
	//else return false;


	return false;
}

void Shuriken::InitPosition() {
	m_isActive = false;
	m_Shuriken.x = m_pGameChara->GetPositionX() + m_Direction * m_Shuriken.scale_x;
	m_Shuriken.y = m_pGameChara->GetPositionY();
	m_DirectionDeg = 0;
}

void Shuriken::Update()
{
	if (m_isChoseDeg) {
		m_DirectionArrow.x = m_pGameChara->GetPositionX() + m_Direction * CELL_SIZE * 2;
		m_DirectionArrow.y = m_pGameChara->GetPositionY();

	}

	if (!m_isActive) {
		return;
	}
	m_Shuriken.x += (MoveSpeed * m_Direction) * std::cos(DegToRad(m_DirectionDeg));
	m_Shuriken.y -= (MoveSpeed * m_Direction) * std::sin(DegToRad(m_DirectionDeg));
	if (m_Shuriken.x < 0 || m_Shuriken.x > DISPLAY_WIDTH) {
		InitPosition();
	}
	if (m_Shuriken.y < 0 || m_Shuriken.y > DISPLAY_HEIGHT) {
		InitPosition();
	}

}


void Shuriken::Render()
{
	static int rad = 0;
	if (!m_isChoseDeg&&!m_isActive) {
		return;
	}
	if (m_isChoseDeg) {
		CUSTOMVERTEX DirectionArrowVertex[4];
		RevolveZEX(DirectionArrowVertex, DegToRad(m_DirectionDeg), m_DirectionArrow, m_DirectionArrow.x - (m_DirectionArrow.scale_x * m_Direction), m_DirectionArrow.y, 0xFFFFFFFF, 0,0,m_Direction);
		TextureRender("ARROW_TEX", DirectionArrowVertex);
		rad = 0;
		return;
	}
	if (m_isActive) {
		CUSTOMVERTEX ShurikenVertex[4];
		static int rad = 0;
		rad += 3;
		RevolveZ(ShurikenVertex, rad, m_Shuriken);
		m_pDirectX->DrawTexture("CROSS_TEX", ShurikenVertex);
	}
}

void Shuriken::Reverse(Object* MapChip) {
	m_pMapChip = MapChip;
}
