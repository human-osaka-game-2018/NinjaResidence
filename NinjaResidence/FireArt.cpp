#include "FireArt.h"


using namespace PlayerAnimation;

FireArt::FireArt(DirectX* pDirectX, SoundOperater* pSoundOperater, Object* MapChip, GameChara* GameChara) :SkillBase(pDirectX, pSoundOperater, MapChip,GameChara)
{
	m_pMapChip = MapChip;
	m_pGameChara = GameChara;
	m_SkillType = FIRE_ART;
}



FireArt::~FireArt()
{

}



void FireArt::KeyOperation(KeyDirection vec)
{
	//KeyëÄçÏÇ≈ÇÃèàóù
	switch (vec)
	{
	case FIRE:
		m_isActive = PermitThrow();
		break;
	case END_ART:
		InitPosition();
		break;
	}
}


bool FireArt::PermitThrow() {
	if (!m_isActive) {
		m_Direction = static_cast<float>(m_pGameChara->GetFacing());
		m_Fire.x = m_pGameChara->GetPositionX() + (m_Direction * m_Fire.scale_x);
		m_Fire.y = m_pGameChara->GetPositionY();
		m_isChoseDeg = false;
		return true;
	}
	if (m_isActive) {
		return true;
	}
	//else return false;


	return false;
}

void FireArt::InitPosition() {
	m_isActive = false;
	m_Fire.x = m_pGameChara->GetPositionX() + m_Direction * (m_Fire.scale_x + 5.f);
	m_Fire.y = m_pGameChara->GetPositionY();
	m_DirectionDeg = 0;
	m_Animation = 0.f;
}

bool FireArt::Update()
{

	if (!m_isActive) {
		return true;
	}
	static int AnimeCount = 0;
	++AnimeCount;
	if (AnimeCount > 10) {
		m_Animation += 1.f;
		AnimeCount = 0;
	}
	if (m_Direction == FACING_RIGHT) {
		m_DirectionBias = ZERO;
	}
	else m_DirectionBias = ONE;
	m_Fire.x = m_pGameChara->GetPositionX() + m_Direction * m_Fire.scale_x;
	m_Fire.y = m_pGameChara->GetPositionY()-10.f;
	m_MapPositionX = static_cast<int>((m_Fire.x - m_MapScrollX) / CELL_SIZE);
	m_MapPositionY = static_cast<int>((m_Fire.y - m_MapScrollY) / CELL_SIZE);
	if (m_Fire.x < 0 || m_Fire.x > DISPLAY_WIDTH) {
		InitPosition();
	}
	if (m_MapPositionY == 0 || m_Fire.y < 0 || m_Fire.y > DISPLAY_HEIGHT) {
		InitPosition();
	}
	int buf = 0;
	if (buf = m_pMapChip->getMapChipData(m_MapPositionY, m_MapPositionX) > 100)
	{
		m_pMapChip->Activate(m_MapPositionX, m_MapPositionY);
		InitPosition();
	}
	return true;
}


void FireArt::Render()
{
	static int rad = 0;
	if (!m_isActive) {
		return;
	}
	if (m_isActive) {
		CUSTOMVERTEX Vertex[4];
		CreateSquareVertex(Vertex, m_Fire, 0xFFFFFFFF, m_DirectionBias * m_CharTu, m_CharTv * 8, m_CharTu * m_Direction, m_CharTv);
		m_pDirectX->DrawTexture("CHARA_TEX", Vertex);
		m_Fire.x += 85 * m_Direction;
		CreateSquareVertex(Vertex, m_Fire, 0xFFFFFFFF,(m_DirectionBias + 1)* m_CharTu, m_CharTv * 8, m_CharTu*m_Direction, m_CharTv);
		m_pDirectX->DrawTexture("CHARA_TEX", Vertex);
		m_Fire.x += 85 * m_Direction;
		CreateSquareVertex(Vertex, m_Fire, 0xFFFFFFFF, (m_DirectionBias +2 ) * m_CharTu, m_CharTv * 8, m_CharTu*m_Direction, m_CharTv);
		m_pDirectX->DrawTexture("CHARA_TEX", Vertex);

	}
}

void FireArt::Reverse(Object* MapChip) {
	m_pMapChip = MapChip;
}
