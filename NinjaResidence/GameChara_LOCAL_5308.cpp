#include "GameChara.h"
#include "MapChip.h"


GameChara::GameChara(DirectX* pDirectX, Object* MapChip) :Object(pDirectX) 
{
	//MapChipの情報を取得するために必要
	m_pMapChip = MapChip;
	row = m_pMapChip->getRow();
	colunm = m_pMapChip->getColunm();
	CreateSquareVertex(m_Player, m_DisplayCharaCoordinate, 0xFFFFFFFF,0,0, CharTu, CharTv);
	//m_DisplayCharaCoordinate[0] = { m_Player.x,						m_Player.y,						1.f, 1.f, 0xFFFFFFFF, 0.f,   0.f };
	//m_DisplayCharaCoordinate[1] = { m_Player.x + m_Player.scale_x,	m_Player.y,						1.f, 1.f, 0xFFFFFFFF, CharTu, 0.f };
	//m_DisplayCharaCoordinate[2] = { m_Player.x + m_Player.scale_x,	m_Player.y + m_Player.scale_y,  1.f, 1.f, 0xFFFFFFFF, CharTu,  CharTv };
	//m_DisplayCharaCoordinate[3] = { m_Player.x,						m_Player.y + m_Player.scale_y,  1.f, 1.f, 0xFFFFFFFF, 0.f,   CharTv };

	CreateSquareVertex(m_Player, m_WorldCharaCoordinate, 0xFFFFFFFF, 0, 0, CharTu, CharTv);
	//m_WorldCharaCoordinate[0] = { m_Player.x,						m_Player.y,						1.f, 1.f, 0xFFFFFFFF, 0.f,   0.f };
	//m_WorldCharaCoordinate[1] = { m_Player.x + m_Player.scale_x,	m_Player.y,						1.f, 1.f, 0xFFFFFFFF, CharTu, 0.f };
	//m_WorldCharaCoordinate[2] = { m_Player.x + m_Player.scale_x,	m_Player.y + m_Player.scale_y,  1.f, 1.f, 0xFFFFFFFF, CharTu,  CharTv };
	//m_WorldCharaCoordinate[3] = { m_Player.x,						m_Player.y + m_Player.scale_y,  1.f, 1.f, 0xFFFFFFFF, 0.f,   CharTv };
}



GameChara::~GameChara()
{
}



int GameChara::KeyOperation(KeyDirection vec)
{
	//Key操作での処理
	switch (vec)
	{
	case UP:
		m_WorldCharaCoordinate[0].y -= 20.f;
		m_WorldCharaCoordinate[1].y -= 20.f;
		m_WorldCharaCoordinate[2].y -= 20.f;
		m_WorldCharaCoordinate[3].y -= 20.f;
		if (m_DisplayCharaCoordinate[0].y > 200)
		{
			m_DisplayCharaCoordinate[0].y -= 20.f;
			m_DisplayCharaCoordinate[1].y -= 20.f;
			m_DisplayCharaCoordinate[2].y -= 20.f;
			m_DisplayCharaCoordinate[3].y -= 20.f;
		}
		//return MapScrollY;
		break;
	case DOWN:
		////今のところ無し
		//m_WorldCharaCoordinate[0].y += 10.f;
		//m_WorldCharaCoordinate[1].y += 10.f;
		//m_WorldCharaCoordinate[2].y += 10.f;
		//m_WorldCharaCoordinate[3].y += 10.f;
		//if (m_DisplayCharaCoordinate[1].y > 600)
		//{
		//	m_DisplayCharaCoordinate[0].y += 10.f;
		//	m_DisplayCharaCoordinate[1].y += 10.f;
		//	m_DisplayCharaCoordinate[2].y += 10.f;
		//	m_DisplayCharaCoordinate[3].y += 10.f;
		//}
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
		return MapScrollX;
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
		return MapScrollX;
		break;
		//m_pMapChip->MapScrollX = 0;
		//m_pMapChip->MapScrollY = 0;
	}
}



void GameChara::MapScroolCheck()
{
	//上に移動
	if (m_DisplayCharaCoordinate[1].y < 200)
	{
		m_DisplayCharaCoordinate[0].y = 200;
		m_DisplayCharaCoordinate[1].y = 200;
		m_DisplayCharaCoordinate[2].y = 360;
		m_DisplayCharaCoordinate[3].y = 360;
		m_pMapChip->m_MapScrollY += 10;
	}
	//下に移動
	if (m_DisplayCharaCoordinate[3].y > 600)
	{
		m_DisplayCharaCoordinate[0].y = 440;
		m_DisplayCharaCoordinate[1].y = 440;
		m_DisplayCharaCoordinate[2].y = 600;
		m_DisplayCharaCoordinate[3].y = 600;
		m_pMapChip->m_MapScrollY -= 10;
	}
	//右に移動
	if (m_DisplayCharaCoordinate[1].x > 900)
	{
		m_DisplayCharaCoordinate[0].x = 820;
		m_DisplayCharaCoordinate[1].x = 900;
		m_DisplayCharaCoordinate[2].x = 900;
		m_DisplayCharaCoordinate[3].x = 820;
		m_pMapChip->m_MapScrollX -= 10;
	}
	//左に移動
	if (m_DisplayCharaCoordinate[0].x < 300)
	{
		m_DisplayCharaCoordinate[0].x = 300;
		m_DisplayCharaCoordinate[1].x = 380;
		m_DisplayCharaCoordinate[2].x = 380;
		m_DisplayCharaCoordinate[3].x = 300;
		m_pMapChip->m_MapScrollX += 10;
	}
}



void GameChara::GameCharaUpdate()
{
	GameChara::MapScroolCheck();
	MapCharaPositionX = (int)m_WorldCharaCoordinate[3].x / 40;
	MapCharaPositionX2 = (int)(m_WorldCharaCoordinate[2].x) / 40;
	MapCharaPositionY = (int)m_WorldCharaCoordinate[3].y / 40;
	if (m_pMapChip->getMapChipData(MapCharaPosition.Y,MapCharaPosition.X) == 0 && m_pMapChip->getMapChipData(MapCharaPositionY,MapCharaPositionX + 1) == 0)
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
	//左の方向のブロックを確かめる
	if (m_pMapChip->MapData[MapCharaPositionY - 1][MapCharaPositionX] != 0 || m_pMapChip->getMapChipData(MapCharaPositionY - 2,MapCharaPositionX) != 0 || m_pMapChip->getMapChipData(MapCharaPositionY - 3,MapCharaPositionX) != 0 || m_pMapChip->getMapChipData(MapCharaPositionY - 4,MapCharaPositionX) != 0)
	{
		m_WorldCharaCoordinate[0].x = ((MapCharaPositionX + 1) * 40);
		m_WorldCharaCoordinate[1].x = ((MapCharaPositionX + 3) * 40);
		m_WorldCharaCoordinate[2].x = ((MapCharaPositionX + 3) * 40);
		m_WorldCharaCoordinate[3].x = ((MapCharaPositionX + 1) * 40);
		m_DisplayCharaCoordinate[0].x = m_WorldCharaCoordinate[0].x + m_pMapChip->m_MapScrollX;
		m_DisplayCharaCoordinate[1].x = m_WorldCharaCoordinate[1].x + m_pMapChip->m_MapScrollX;
		m_DisplayCharaCoordinate[2].x = m_WorldCharaCoordinate[2].x + m_pMapChip->m_MapScrollX;
		m_DisplayCharaCoordinate[3].x = m_WorldCharaCoordinate[3].x + m_pMapChip->m_MapScrollX;

	
	}
	//右方向のブロックを確かめる
	else if (m_pMapChip->getMapChipData(MapCharaPositionY - 1,MapCharaPositionX2) != 0 || m_pMapChip->getMapChipData(MapCharaPositionY - 2,MapCharaPositionX2) != 0 || m_pMapChip->getMapChipData(MapCharaPositionY - 3,MapCharaPositionX2) != 0 || m_pMapChip->getMapChipData(MapCharaPositionY - 4,MapCharaPositionX2) != 0)
	{
		m_WorldCharaCoordinate[0].x = ((MapCharaPositionX2 -2) * 40);
		m_WorldCharaCoordinate[1].x = ((MapCharaPositionX2 ) * 40);
		m_WorldCharaCoordinate[2].x = ((MapCharaPositionX2 ) * 40);
		m_WorldCharaCoordinate[3].x = ((MapCharaPositionX2 -2) * 40);
		m_DisplayCharaCoordinate[0].x = m_WorldCharaCoordinate[0].x + m_pMapChip->m_MapScrollX;
		m_DisplayCharaCoordinate[1].x = m_WorldCharaCoordinate[1].x + m_pMapChip->m_MapScrollX;
		m_DisplayCharaCoordinate[2].x = m_WorldCharaCoordinate[2].x + m_pMapChip->m_MapScrollX;
		m_DisplayCharaCoordinate[3].x = m_WorldCharaCoordinate[3].x + m_pMapChip->m_MapScrollX;
	}
}


void GameChara::Render()
{
	TextureRender("CHARA_INTEGRATION_TEX", m_DisplayCharaCoordinate);
}