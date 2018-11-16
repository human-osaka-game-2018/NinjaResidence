#include "GameChara.h"
#include "MapChip.h"


GameChara::GameChara(Scene * pScene)
{
	m_pScene = pScene;
	m_pMapChip = new MapChip(pScene);
	m_DisplayCharaCoordinate[0] = { m_Player.x,						m_Player.y,						1.f, 1.f, 0xFFFFFFFF, 0.f,   0.f };
	m_DisplayCharaCoordinate[1] = { m_Player.x + m_Player.scale_x,	m_Player.y,						1.f, 1.f, 0xFFFFFFFF, 80 / 512.f, 0.f };
	m_DisplayCharaCoordinate[2] = { m_Player.x + m_Player.scale_x,	m_Player.y + m_Player.scale_y,  1.f, 1.f, 0xFFFFFFFF, 80 / 512.f,  160 / 512.f };
	m_DisplayCharaCoordinate[3] = { m_Player.x,						m_Player.y + m_Player.scale_y,  1.f, 1.f, 0xFFFFFFFF, 0.f,   160 / 512.f };       
	m_WorldCharaCoordinate[0] = { m_Player.x,						m_Player.y,						1.f, 1.f, 0xFFFFFFFF, 0.f,   0.f };
	m_WorldCharaCoordinate[1] = { m_Player.x + m_Player.scale_x,	m_Player.y,						1.f, 1.f, 0xFFFFFFFF, 80 / 512.f, 0.f };
	m_WorldCharaCoordinate[2] = { m_Player.x + m_Player.scale_x,	m_Player.y + m_Player.scale_y,  1.f, 1.f, 0xFFFFFFFF, 80 / 512.f,  160 / 512.f };
	m_WorldCharaCoordinate[3] = { m_Player.x,						m_Player.y + m_Player.scale_y,  1.f, 1.f, 0xFFFFFFFF, 0.f,   160 / 512.f };
}



GameChara::~GameChara()
{
	delete m_pMapChip;
	m_pMapChip = NULL;
}



void GameChara::GameCharaKeyOperation()
{
//Key操作での処理
	switch (abc)
	{
	case UP:
		m_WorldCharaCoordinate[0].y -= 30.f;
		m_WorldCharaCoordinate[1].y -= 30.f;
		m_WorldCharaCoordinate[2].y -= 30.f;
		m_WorldCharaCoordinate[3].y -= 30.f;
		if (m_DisplayCharaCoordinate[0].y >= 100)
		{
			m_DisplayCharaCoordinate[0].y -= 30.f;
			m_DisplayCharaCoordinate[1].y -= 30.f;
			m_DisplayCharaCoordinate[2].y -= 30.f;
			m_DisplayCharaCoordinate[3].y -= 30.f;
		}
		if (m_DisplayCharaCoordinate[0].y <= 100)
		{
			m_pMapChip->m_MapScrollY += 10;
		}
		break;
	case DOWN:
		//今のところ無し
		m_WorldCharaCoordinate[0].y += 10.f;
		m_WorldCharaCoordinate[1].y += 10.f;
		m_WorldCharaCoordinate[2].y += 10.f;
		m_WorldCharaCoordinate[3].y += 10.f;
		if (m_DisplayCharaCoordinate[3].y >= 600)
		{
			m_DisplayCharaCoordinate[0].y += 10.f;
			m_DisplayCharaCoordinate[1].y += 10.f;
			m_DisplayCharaCoordinate[2].y += 10.f;
			m_DisplayCharaCoordinate[3].y += 10.f;
		}
		if (m_DisplayCharaCoordinate[3].y <= 600)
		{
			m_pMapChip->m_MapScrollY -= 10;
		}
		break;
	case RIGHT:
		//右に移動
		m_WorldCharaCoordinate[0].x += 10.f;
		m_WorldCharaCoordinate[1].x += 10.f;
		m_WorldCharaCoordinate[2].x += 10.f;
		m_WorldCharaCoordinate[3].x += 10.f;
		if (m_DisplayCharaCoordinate[1].x <= 900)
		{
			m_DisplayCharaCoordinate[0].x += 10.f;
			m_DisplayCharaCoordinate[1].x += 10.f;
			m_DisplayCharaCoordinate[2].x += 10.f;
			m_DisplayCharaCoordinate[3].x += 10.f;
		}
		if (m_DisplayCharaCoordinate[1].x >= 900)
		{
			m_pMapChip->m_MapScrollX -= 10;
		}
		break;
	case LEFT:
		//左に移動
		m_WorldCharaCoordinate[0].x -= 10.f;
		m_WorldCharaCoordinate[1].x -= 10.f;
		m_WorldCharaCoordinate[2].x -= 10.f;
		m_WorldCharaCoordinate[3].x -= 10.f;
		if (m_DisplayCharaCoordinate[0].x >= 300)
		{
			m_DisplayCharaCoordinate[0].x -= 10.f;
			m_DisplayCharaCoordinate[1].x -= 10.f;
			m_DisplayCharaCoordinate[2].x -= 10.f;
			m_DisplayCharaCoordinate[3].x -= 10.f;
		}
		if (m_DisplayCharaCoordinate[0].x <= 300)
		{
			m_pMapChip->m_MapScrollX += 10;
		}
		break;
	}
}

int MapCharaPositionX2;

void GameChara::GameCharaUpdate()
{
	//マップチップの当たり判定
	if (m_WorldCharaCoordinate[3].x >= 440)
	{
		m_WorldCharaCoordinate[0].y += 0.f;
	}
	MapCharaPositionX = (int)m_WorldCharaCoordinate[3].x / 40;
	MapCharaPositionX2 = (int)(m_WorldCharaCoordinate[2].x - 10) / 40;
	MapCharaPositionY = (int)m_WorldCharaCoordinate[3].y / 40;
	if (m_pMapChip->MapData[MapCharaPositionY][MapCharaPositionX] == 0 || m_pMapChip->MapData[MapCharaPositionY][MapCharaPositionX + 1] == 0)
	{
		m_WorldCharaCoordinate[0].y += 10.f;
		m_WorldCharaCoordinate[1].y += 10.f;
		m_WorldCharaCoordinate[2].y += 10.f;
		m_WorldCharaCoordinate[3].y += 10.f;
		m_DisplayCharaCoordinate[0].y += 10.f;
		m_DisplayCharaCoordinate[1].y += 10.f;
		m_DisplayCharaCoordinate[2].y += 10.f;
		m_DisplayCharaCoordinate[3].y += 10.f;
	}
	if (m_pMapChip->MapData[MapCharaPositionY-1][MapCharaPositionX] != 0 || m_pMapChip->MapData[MapCharaPositionY - 2][MapCharaPositionX] != 0 || m_pMapChip->MapData[MapCharaPositionY - 3][MapCharaPositionX] != 0 || m_pMapChip->MapData[MapCharaPositionY - 4][MapCharaPositionX] != 0)
	{
		m_WorldCharaCoordinate[0].x += 10.f;
		m_WorldCharaCoordinate[1].x += 10.f;
		m_WorldCharaCoordinate[2].x += 10.f;
		m_WorldCharaCoordinate[3].x += 10.f;
		m_DisplayCharaCoordinate[0].x += 10.f;
		m_DisplayCharaCoordinate[1].x += 10.f;
		m_DisplayCharaCoordinate[2].x += 10.f;
		m_DisplayCharaCoordinate[3].x += 10.f;
	}
	if ( m_pMapChip->MapData[MapCharaPositionY - 1][MapCharaPositionX2 ] != 0 || m_pMapChip->MapData[MapCharaPositionY - 2][MapCharaPositionX2] != 0 || m_pMapChip->MapData[MapCharaPositionY - 3][MapCharaPositionX2 ] != 0 || m_pMapChip->MapData[MapCharaPositionY - 4][MapCharaPositionX2] != 0)
	{								   
		m_WorldCharaCoordinate[0].x -= 10.f;
		m_WorldCharaCoordinate[1].x -= 10.f;
		m_WorldCharaCoordinate[2].x -= 10.f;
		m_WorldCharaCoordinate[3].x -= 10.f;
		m_DisplayCharaCoordinate[0].x -= 10.f;
		m_DisplayCharaCoordinate[1].x -= 10.f;
		m_DisplayCharaCoordinate[2].x -= 10.f;
		m_DisplayCharaCoordinate[3].x -= 10.f;
	}
	//if (GameChara::RectToRectCollisionCheak(m_WorldCharaCoordinate, m_pMapChip->CELL))
	//{
	//	int a = 0;
	//}
	//MapChara[MapCharaPositionX][MapCharaPositionY];
}



bool GameChara::RectToRectCollisionCheak(CUSTOMVERTEX* pObjA, CUSTOMVERTEX* pObjB)
{
	//四角形の当たり判定
	if ((pObjA[0].x <= pObjB[0].x && pObjB[0].x <= pObjA[1].x) ||
		(pObjA[0].x <= pObjB[1].x && pObjB[1].x <= pObjA[1].x) ||
		(pObjB[0].x <= pObjA[0].x && pObjA[1].x <= pObjB[1].x))
	{
		if ((pObjA[0].y <= pObjB[0].y && pObjB[0].y <= pObjA[3].y) ||
			(pObjA[0].y <= pObjB[3].y && pObjB[3].y <= pObjA[3].y) ||
			(pObjB[0].y <= pObjA[0].y && pObjA[3].y <= pObjB[3].y))
		{
			return true;
		}
	}

	return false;
}



void GameChara::GameCharaRender()
{
	m_pScene->TextureRender("CHARA_INTEGRATION_TEX", m_DisplayCharaCoordinate);
}