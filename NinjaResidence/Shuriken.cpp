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
		isActive = PermitThrow();
		break;
	case UP:
		if (isActive) {
			return;
		}
		DirectionDeg += Direction;
		if (DirectionDeg>45) {
			DirectionDeg = 45;
		}
		if (DirectionDeg<-45) {
			DirectionDeg = -45;
		}
		break;
	case DOWN:
		if (isActive) {
			return;;
		}
		DirectionDeg -= Direction;
		if (DirectionDeg>45) {
			DirectionDeg = 45;
		}
		if (DirectionDeg<-45) {
			DirectionDeg = -45;
		}
		break;
	}
}


bool Shuriken::PermitThrow() {
	if (!isChoseDeg && !isActive) {
		isChoseDeg = true;
		Direction = static_cast<float>(m_pGameChara->GetFacing());
		return false;
	}
	if (isChoseDeg && !isActive) {
		m_Shuriken.x = m_pGameChara->GetPositionX() +( Direction * m_Shuriken.scale_x);
		m_Shuriken.y = m_pGameChara->GetPositionY();
		isChoseDeg = false;
		return true;
	}
	if (isActive) {
		return true;
	}
	//else return false;


	return false;
}

void Shuriken::InitPosition() {
	isActive = false;
	m_Shuriken.x = m_pGameChara->GetPositionX() + Direction * m_Shuriken.scale_x;
	m_Shuriken.y = m_pGameChara->GetPositionY();
	DirectionDeg = 0;
}

void Shuriken::Update()
{
	if (isChoseDeg) {
		m_DirectionArrow.x = m_pGameChara->GetPositionX() + Direction * CELL_SIZE * 2;
		m_DirectionArrow.y = m_pGameChara->GetPositionY();

	}

	if (!isActive) {
		return;
	}
	m_Shuriken.x += (MoveSpeed * Direction) * std::cos(DegToRad(DirectionDeg));
	m_Shuriken.y -= (MoveSpeed * Direction) * std::sin(DegToRad(DirectionDeg));
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
	if (!isChoseDeg&&!isActive) {
		return;
	}
	if (isChoseDeg) {
		CUSTOMVERTEX DirectionArrowVertex[4];
		RevolveZEX(DirectionArrowVertex, DegToRad(DirectionDeg), m_DirectionArrow, m_DirectionArrow.x - (m_DirectionArrow.scale_x * Direction), m_DirectionArrow.y, 0xFFFFFFFF, 0,0,Direction);
		TextureRender("ARROW_TEX", DirectionArrowVertex);
		rad = 0;
		return;
	}
	if (isActive) {
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
