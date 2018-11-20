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
		if (MapCharaPosition.Y > 1) {
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
				return MapScrollY += 10;
			}
		}
		//return MapScrollY;
		break;
	case DOWN:
		//今のところ無し
		if (MapCharaPosition.Y < colunm) {

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
				return MapScrollY -= 10;
			}
		}
		return MapScrollY;
		break;
	case RIGHT:
		//右に移動
		if (MapCharaPosition.X < row) {

			m_WorldCharaCoordinate[0].x += 10.f;
			m_WorldCharaCoordinate[1].x += 10.f;
			m_WorldCharaCoordinate[2].x += 10.f;
			m_WorldCharaCoordinate[3].x += 10.f;
			if (m_DisplayCharaCoordinate[1].x <= 1100)
			{
				m_DisplayCharaCoordinate[0].x += 10.f;
				m_DisplayCharaCoordinate[1].x += 10.f;
				m_DisplayCharaCoordinate[2].x += 10.f;
				m_DisplayCharaCoordinate[3].x += 10.f;
			}
			if (m_DisplayCharaCoordinate[1].x >= 900 && MapScrollX > (-30 * row))
			{
				return MapScrollX -= 10;
			}
		}
		return MapScrollX;
		break;
	case LEFT:
		//左に移動
		if (MapCharaPosition.X > 1) {

			m_WorldCharaCoordinate[0].x -= 10.f;
			m_WorldCharaCoordinate[1].x -= 10.f;
			m_WorldCharaCoordinate[2].x -= 10.f;
			m_WorldCharaCoordinate[3].x -= 10.f;
			if (m_DisplayCharaCoordinate[0].x >= 0)
			{
				m_DisplayCharaCoordinate[0].x -= 10.f;
				m_DisplayCharaCoordinate[1].x -= 10.f;
				m_DisplayCharaCoordinate[2].x -= 10.f;
				m_DisplayCharaCoordinate[3].x -= 10.f;
			}
			if (m_DisplayCharaCoordinate[0].x <= 200 && MapScrollX <= 0)
			{
				return MapScrollX += 10;
			}
		}
		return MapScrollX;
		break;
		//m_pMapChip->MapScrollX = 0;
		//m_pMapChip->MapScrollY = 0;
	}
}


void GameChara::Update()
{
	//マップチップの当たり判定
	if (m_WorldCharaCoordinate[3].x >= 440)
	{
		m_WorldCharaCoordinate[0].y += 10.f;
	}
	//static_castを使用する
	MapCharaPosition.X = (int)m_WorldCharaCoordinate[3].x / CELL_SIZE;
	int MapCharaPositionX2 = (int)(m_WorldCharaCoordinate[2].x - 10) / CELL_SIZE;
	MapCharaPosition.Y = (int)m_WorldCharaCoordinate[3].y / CELL_SIZE;
	if (m_pMapChip->getMapChipData(MapCharaPosition.Y,MapCharaPosition.X) == 0 && m_pMapChip->getMapChipData(MapCharaPosition.Y,MapCharaPosition.X + 1) == 0)
	{
		m_WorldCharaCoordinate[0].y += 10.f;
		m_WorldCharaCoordinate[1].y += 10.f;
		m_WorldCharaCoordinate[2].y += 10.f;
		m_WorldCharaCoordinate[3].y += 10.f;
		m_DisplayCharaCoordinate[0].y += 10.f;
		m_DisplayCharaCoordinate[1].y += 10.f;
		m_DisplayCharaCoordinate[2].y += 10.f;
		m_DisplayCharaCoordinate[3].y += 10.f;
		if (m_DisplayCharaCoordinate[3].y > 700) {
			m_DisplayCharaCoordinate[0].y -= 20.f;
			m_DisplayCharaCoordinate[1].y -= 20.f;
			m_DisplayCharaCoordinate[2].y -= 20.f;
			m_DisplayCharaCoordinate[3].y -= 20.f;
		}
		MapScrollY -= 10;
		setMapScrollY(MapScrollY);
	}
	if (m_pMapChip->getMapChipData(MapCharaPosition.Y - 1,MapCharaPosition.X) != 0 || m_pMapChip->getMapChipData(MapCharaPosition.Y - 2,MapCharaPosition.X) != 0 || m_pMapChip->getMapChipData(MapCharaPosition.Y - 3,MapCharaPosition.X) != 0 || m_pMapChip->getMapChipData(MapCharaPosition.Y - 4,MapCharaPosition.X) != 0)
	{
		m_WorldCharaCoordinate[0].x += 10.f;
		m_WorldCharaCoordinate[1].x += 10.f;
		m_WorldCharaCoordinate[2].x += 10.f;
		m_WorldCharaCoordinate[3].x += 10.f;
		m_DisplayCharaCoordinate[0].x += 10.f;
		m_DisplayCharaCoordinate[1].x += 10.f;
		m_DisplayCharaCoordinate[2].x += 10.f;
		m_DisplayCharaCoordinate[3].x += 10.f;
		if (MapScrollX < 0) {
			MapScrollX += 10;
			setMapScrollX(MapScrollX);
		}
	}

	if (m_pMapChip->getMapChipData(MapCharaPosition.Y - 1,MapCharaPositionX2) != 0 || m_pMapChip->getMapChipData(MapCharaPosition.Y - 2,MapCharaPositionX2) != 0 || m_pMapChip->getMapChipData(MapCharaPosition.Y - 3,MapCharaPositionX2) != 0 || m_pMapChip->getMapChipData(MapCharaPosition.Y - 4,MapCharaPositionX2) != 0)
	{
		m_WorldCharaCoordinate[0].x -= 10.f;
		m_WorldCharaCoordinate[1].x -= 10.f;
		m_WorldCharaCoordinate[2].x -= 10.f;
		m_WorldCharaCoordinate[3].x -= 10.f;
		m_DisplayCharaCoordinate[0].x -= 10.f;
		m_DisplayCharaCoordinate[1].x -= 10.f;
		m_DisplayCharaCoordinate[2].x -= 10.f;
		m_DisplayCharaCoordinate[3].x -= 10.f;
		if (MapScrollX >(-30 * row)) {
			MapScrollX -= 10;
			setMapScrollX(MapScrollX);
		}
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



void GameChara::Render()
{
	TextureRender("CHARA_INTEGRATION_TEX", m_DisplayCharaCoordinate);
}