/**
* @file HighShuriken.cpp
* @brief 高等手裏剣クラス
* @author Toshiya Matsuoka
*/
#include "HighShuriken.h"



using namespace PlayerAnimation;

HighShuriken::HighShuriken(DirectX* pDirectX, SoundOperater* pSoundOperater, Object* MapChip, GameChara* GameChara) :SkillBase(pDirectX, pSoundOperater, MapChip, GameChara)
{
	m_Central = { 500,0,20,20 };
	m_pMapChip = MapChip;
	m_pGameChara = GameChara;
	m_row = m_pMapChip->getRow();
	m_colunm = m_pMapChip->getColunm();

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

	case BIT_UP:
		isOperation = true;
		m_Central.y -= MoveSpeed;
		break;
	case BIT_DOWN:
		isOperation = true;
		m_Central.y += MoveSpeed;
		break;
	case BIT_LEFT:
		isOperation = true;
		m_Central.x -= MoveSpeed;
		break;
	case BIT_RIGHT:
		isOperation = true;
		m_Central.x += MoveSpeed;
		break;
	case END_ART:
		InitPosition();
		break;
	}
}


bool HighShuriken::PermitActive() {
	if (!m_isChoseDeg && !m_isActive) {
		m_isChoseDeg = true;
		m_Direction = static_cast<float>(m_pGameChara->GetFacing());
		return false;
	}
	if (m_isChoseDeg && !m_isActive) {
		m_Central.x = m_pGameChara->GetPositionX() + (m_Direction * m_Central.scale_x);
		m_Central.y = m_pGameChara->GetPositionY();
		PrevMapScrollX = m_MapScrollX;
		PrevMapScrollY = m_MapScrollY;

		m_isChoseDeg = false;
		return true;
	}
	if (m_isActive) {
		return true;
	}
	return false;
}

bool HighShuriken::CollisionRope()
{
	CENTRAL_STATE RopeCentral = { 0 };
	TranslateCentral_State(m_pMapChip->GetTargetPosition(BT_ROPE), &RopeCentral);

	m_ropeX = static_cast<int>((RopeCentral.x - m_MapScrollX) / CELL_SIZE);
	m_ropeY = static_cast<int>((RopeCentral.y - m_MapScrollY) / CELL_SIZE);

	return ContactSpecifyObject(&RopeCentral);
}

void HighShuriken::InitPosition() {
	m_isActive = false;
	isOperation = false;

	m_Central.x = m_pGameChara->GetPositionX() + m_Direction * m_Central.scale_x;
	m_Central.y = m_pGameChara->GetPositionY();
	m_DirectionDeg = 0;
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
	if (!isOperation) {
		m_Central.x += (MoveSpeed * m_Direction) * std::cos(DegToRad(m_DirectionDeg)) - PrevMapScrollX;
		m_Central.y -= (MoveSpeed * m_Direction) * std::sin(DegToRad(m_DirectionDeg)) + PrevMapScrollY;
	}
	m_MapPositionX = static_cast<int>((m_Central.x - m_MapScrollX) / CELL_SIZE);
	m_MapPositionY = static_cast<int>((m_Central.y - m_MapScrollY) / CELL_SIZE);

	if (m_Central.x < 0 || m_Central.x > DISPLAY_WIDTH || m_MapPositionX >= m_row - 1) {
		InitPosition();
	}
	if (m_MapPositionY == 0 || m_Central.y < 0 || m_Central.y > DISPLAY_HEIGHT || m_MapPositionY >= m_colunm - 1) {
		InitPosition();
	}
	int buf = 0;
	if (buf = m_pMapChip->getMapChipData(m_MapPositionY, m_MapPositionX) > 100)
	{
		m_pMapChip->Activate(m_MapPositionX, m_MapPositionY);
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
		RevolveZ(ShurikenVertex, rad, m_Central);
		m_pDirectX->DrawTexture("CROSS_TEX", ShurikenVertex);
	}
}

void HighShuriken::Reverse(Object* MapChip) {
	m_pMapChip = MapChip;
	InitPosition();
}
