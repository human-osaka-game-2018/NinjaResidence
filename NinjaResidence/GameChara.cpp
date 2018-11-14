#include "GameChara.h"


GameChara::GameChara(Scene * pScene)
{
	m_pScene = pScene;
	m_pMapChip = new MapChip(pScene);
	m_DisplayCharaCoordinate[0] = { m_Player.x,						m_Player.y,						1.f, 1.f, 0xFFFFFFFF, 0.f,   0.f };
	m_DisplayCharaCoordinate[1] = { m_Player.x + m_Player.scale_x,	m_Player.y,						1.f, 1.f, 0xFFFFFFFF, 80 / 512.f, 0.f };
	m_DisplayCharaCoordinate[2] = { m_Player.x + m_Player.scale_x,	m_Player.y + m_Player.scale_y,  1.f, 1.f, 0xFFFFFFFF, 80 / 512.f,  160 / 512.f };
	m_DisplayCharaCoordinate[3] = { m_Player.x,						m_Player.y + m_Player.scale_y,  1.f, 1.f, 0xFFFFFFFF, 0.f,   160 / 512.f };
}

GameChara::~GameChara()
{
	delete m_pMapChip;
	m_pMapChip = NULL;
}

void GameChara::GameCharaUpdate()
{
	if (0)//��UP
	{
		//�W�����v
	}
	if (0)//��DOWN
	{
		//���̂Ƃ��떳��
	}
	switch (abc)
	{
	case UP:
		//�E�Ɉړ�
		if (m_DisplayCharaCoordinate[3].y <= 400)
		{
			m_DisplayCharaCoordinate[0].y -= 10.f;
			m_DisplayCharaCoordinate[1].y -= 10.f;
			m_DisplayCharaCoordinate[2].y -= 10.f;
			m_DisplayCharaCoordinate[3].y -= 10.f;
		}
		if (m_DisplayCharaCoordinate[3].y >= 400)
		{
			m_pMapChip->MapScrolly += 32;
		}
		break;
	case DOWN:
		//�E�Ɉړ�
		if (m_DisplayCharaCoordinate[3].y <= 500)
		{
			m_DisplayCharaCoordinate[0].y += 10.f;
			m_DisplayCharaCoordinate[1].y += 10.f;
			m_DisplayCharaCoordinate[2].y += 10.f;
			m_DisplayCharaCoordinate[3].y += 10.f;
		}
		if (m_DisplayCharaCoordinate[3].y >= 500)
		{
			m_pMapChip->MapScrolly -= 32;
		}
		break;

	case RIGHT:
		//�E�Ɉړ�
		if (m_DisplayCharaCoordinate[1].x <= 900)
		{
			m_DisplayCharaCoordinate[0].x += 10.f;
			m_DisplayCharaCoordinate[1].x += 10.f;
			m_DisplayCharaCoordinate[2].x += 10.f;
			m_DisplayCharaCoordinate[3].x += 10.f;
		}
		if (m_DisplayCharaCoordinate[1].x >= 900)
		{
			m_pMapChip->MapScrollx -= 32;
		}
		break;
	case LEFT:
		//���Ɉړ�
		if (m_DisplayCharaCoordinate[0].x >= 300)
		{
			m_DisplayCharaCoordinate[0].x -= 10.f;
			m_DisplayCharaCoordinate[1].x -= 10.f;
			m_DisplayCharaCoordinate[2].x -= 10.f;
			m_DisplayCharaCoordinate[3].x -= 10.f;
		}
		if (m_DisplayCharaCoordinate[0].x <= 300)
		{
			m_pMapChip->MapScrollx += 32;
		}
		break;
	}
}

void GameChara::GameCharaRender()
{
	m_pScene->TextureRender("CHARA_INTEGRATION_TEX", m_DisplayCharaCoordinate);
}