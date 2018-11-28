#include "GameChara.h"
#include "MapChip.h"


GameChara::GameChara(DirectX* pDirectX, Object* MapChip) :Object(pDirectX)
{
	//MapChipの情報を取得するために必要
	m_pMapChip = MapChip;
	row = m_pMapChip->getRow();
	colunm = m_pMapChip->getColunm();
	CreateSquareVertex(m_Player, m_DisplayCharaCoordinate, 0xFFFFFFFF, 0, 0, CharTu, CharTv);
	CreateSquareVertex(m_Player, m_WorldCharaCoordinate, 0xFFFFFFFF, 0, 0, CharTu, CharTv);
	CreateSquareVertex(m_Player, m_WorldCharaCoordinate, 0xFFFFFFFF, 0, 0, CharTu, CharTv);
	CreateSquareVertex(m_Player, m_ReverseDisplayCharaCoordinate, 0xFFFFFFFF, 0, 0, CharTu, CharTv);
	CreateSquareVertex(m_Player, m_ReverseWorldCharaCoordinate, 0xFFFFFFFF, 0, 0, CharTu, CharTv);
	CreateSquareVertex(m_Player, m_SurfaceDisplayCharaCoordinate, 0xFFFFFFFF, 0, 0, CharTu, CharTv);
	CreateSquareVertex(m_Player, m_SurfaceWorldCharaCoordinate, 0xFFFFFFFF, 0, 0, CharTu, CharTv);
}



GameChara::~GameChara()
{
}

void GameChara::CharaMoveOperation(KeyDirection vec, CUSTOMVERTEX* pWorldCharaCoordinate, CUSTOMVERTEX* pDisplayCharaCoordinate,float MoveQuantity)
{
	switch (vec)
	{
		//上に移動
	case UP:
		for (int i = 0;i < 4;i++)
		{
			pWorldCharaCoordinate[i].y -= MoveQuantity;
		}
		if (pDisplayCharaCoordinate[0].y > 200)
		{
			for (int j = 0;j < 4;j++)
			{
				pDisplayCharaCoordinate[j].y -= MoveQuantity;
			}
		}
		break;
	case DOWN:
		//今のところなし

		break;
	case RIGHT:
		//右に移動
		for (int i = 0;i < 4;i++)
		{
			pWorldCharaCoordinate[i].x += MoveQuantity;
		}
		if (pDisplayCharaCoordinate[1].x <= 900)
		{
			for (int j = 0;j < 4;j++)
			{
				pDisplayCharaCoordinate[j].x += MoveQuantity;
			}
		}
		break;
	case LEFT:
		//左に移動
		for (int i = 0;i < 4;i++)
		{
			pWorldCharaCoordinate[i].x -= MoveQuantity;
		}
		if (pDisplayCharaCoordinate[0].x >= 300)
		{
			for (int j = 0;j < 4;j++)
			{
				pDisplayCharaCoordinate[j].x -= MoveQuantity;
			}
		}
		break;
	}
}



void GameChara::ValueAllSetCUSTOMVERTEX(CUSTOMVERTEX* Receive, CUSTOMVERTEX* Give)
{
	Receive[0] = Give[0];
	Receive[1] = Give[1];
	Receive[2] = Give[2];
	Receive[3] = Give[3];
}


void GameChara::prevSaveMapCharaPos()
{
	m_PrevMapCharaPositionX = (int)m_WorldCharaCoordinate[3].x;
	m_PrevMapCharaPositionX2 = (int)m_WorldCharaCoordinate[2].x;
	m_PrevMapCharaPositionY = (int)m_WorldCharaCoordinate[3].y + 10;
}




void GameChara::KeyOperation(KeyDirection vec)
{
	//Key操作での処理
	switch (vec)
	{
	case UP:
		CharaMoveOperation(UP, m_WorldCharaCoordinate, m_DisplayCharaCoordinate, 30.0f);
		break;
	case DOWN:
		////今のところ無し
		CharaMoveOperation(DOWN, m_WorldCharaCoordinate, m_DisplayCharaCoordinate, CharaMoveSpeed);
		break;
	case RIGHT:
		//右に移動
		CharaMoveOperation(RIGHT, m_WorldCharaCoordinate, m_DisplayCharaCoordinate, CharaMoveSpeed);
		break;
	case LEFT:
		//左に移動
		CharaMoveOperation(LEFT, m_WorldCharaCoordinate, m_DisplayCharaCoordinate, CharaMoveSpeed);
		break;

	}
}


void GameChara::CharaInforSave(bool MapReverseSelect)
{
	if (MapReverseSelect)
	{
		ValueAllSetCUSTOMVERTEX(m_SurfaceDisplayCharaCoordinate, m_DisplayCharaCoordinate);
		ValueAllSetCUSTOMVERTEX(m_SurfaceWorldCharaCoordinate, m_WorldCharaCoordinate);
		ValueAllSetCUSTOMVERTEX(m_DisplayCharaCoordinate, m_ReverseDisplayCharaCoordinate);
		ValueAllSetCUSTOMVERTEX(m_WorldCharaCoordinate, m_ReverseWorldCharaCoordinate);
	}
	else 
	{
		ValueAllSetCUSTOMVERTEX(m_ReverseDisplayCharaCoordinate, m_DisplayCharaCoordinate);
		ValueAllSetCUSTOMVERTEX(m_ReverseWorldCharaCoordinate, m_WorldCharaCoordinate);
		ValueAllSetCUSTOMVERTEX(m_DisplayCharaCoordinate, m_SurfaceDisplayCharaCoordinate);
		ValueAllSetCUSTOMVERTEX(m_WorldCharaCoordinate, m_SurfaceWorldCharaCoordinate);
	}
}



void GameChara::MapScroolCheck()
{
	//上にスクロール移動
	if (m_DisplayCharaCoordinate[1].y < 200)
	{
		m_DisplayCharaCoordinate[0].y = 200;
		m_DisplayCharaCoordinate[1].y = 200;
		m_DisplayCharaCoordinate[2].y = 360;
		m_DisplayCharaCoordinate[3].y = 360;
		m_pMapChip->m_MapScrollY += CharaMoveSpeed;
	}
	//下にスクロール移動
	if (m_DisplayCharaCoordinate[3].y > 600)
	{
		m_DisplayCharaCoordinate[0].y = 440;
		m_DisplayCharaCoordinate[1].y = 440;
		m_DisplayCharaCoordinate[2].y = 600;
		m_DisplayCharaCoordinate[3].y = 600;
		m_pMapChip->m_MapScrollY -= CharaMoveSpeed;
	}
	//右にスクロール移動
	if (m_DisplayCharaCoordinate[1].x > 900)
	{
		m_DisplayCharaCoordinate[0].x = 820;
		m_DisplayCharaCoordinate[1].x = 900;
		m_DisplayCharaCoordinate[2].x = 900;
		m_DisplayCharaCoordinate[3].x = 820;
		m_pMapChip->m_MapScrollX -= CharaMoveSpeed;
	}
	//左にスクロール移動
	if (m_DisplayCharaCoordinate[0].x < 300)
	{
		m_DisplayCharaCoordinate[0].x = 300;
		m_DisplayCharaCoordinate[1].x = 380;
		m_DisplayCharaCoordinate[2].x = 380;
		m_DisplayCharaCoordinate[3].x = 300;
		m_pMapChip->m_MapScrollX += CharaMoveSpeed;
	}
}

void GameChara::Update()
{
		MapScroolCheck();
		MapCharaPositionX = (int)m_WorldCharaCoordinate[3].x / CELL_SIZE;
		MapCharaPositionX2 = (int)(m_WorldCharaCoordinate[2].x) / CELL_SIZE;
		MapCharaPositionY = (int)(m_WorldCharaCoordinate[3].y + 10) / CELL_SIZE;
		//重力を毎フレームかける
		m_WorldCharaCoordinate[0].y += 15.f;
		m_WorldCharaCoordinate[1].y += 15.f;
		m_WorldCharaCoordinate[2].y += 15.f;
		m_WorldCharaCoordinate[3].y += 15.f;
		m_DisplayCharaCoordinate[0].y += 15.f;
		m_DisplayCharaCoordinate[1].y += 15.f;
		m_DisplayCharaCoordinate[2].y += 15.f;
 		m_DisplayCharaCoordinate[3].y += 15.f;
		//下の方向を確かめる
		if ((m_pMapChip->getMapChipData(MapCharaPositionY, MapCharaPositionX) != 0 && m_pMapChip->getMapChipData(MapCharaPositionY, MapCharaPositionX) < 3) ||
			(m_pMapChip->getMapChipData(MapCharaPositionY, MapCharaPositionX + 1) != 0 && m_pMapChip->getMapChipData(MapCharaPositionY, MapCharaPositionX + 1) < 3) ||
			(m_pMapChip->getMapChipData(MapCharaPositionY, MapCharaPositionX + 2) != 0 && m_pMapChip->getMapChipData(MapCharaPositionY, MapCharaPositionX + 2) < 3))
		{
				m_WorldCharaCoordinate[0].y = ((MapCharaPositionY - 4) * CELL_SIZE);
				m_WorldCharaCoordinate[1].y = ((MapCharaPositionY - 4) * CELL_SIZE);
				m_WorldCharaCoordinate[2].y = ((MapCharaPositionY)* CELL_SIZE);
				m_WorldCharaCoordinate[3].y = ((MapCharaPositionY)* CELL_SIZE);
				for (int i = 0;i < 4;i++)
				{
					m_DisplayCharaCoordinate[i].y = m_WorldCharaCoordinate[i].y + m_pMapChip->m_MapScrollY;
				}
		}
		//上のブロックを確かめる
		if (m_PrevMapCharaPositionY > m_WorldCharaCoordinate[3].y + 10)
		{
			if ((m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapCharaPositionX) != 0 && m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapCharaPositionX) < 3)||
				(m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapCharaPositionX + 1) != 0 && m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapCharaPositionX + 1) < 3)||
				(m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapCharaPositionX + 2) != 0 && m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapCharaPositionX + 2) < 3))
			{
				m_WorldCharaCoordinate[0].y = ((MapCharaPositionY - 3) * CELL_SIZE);
				m_WorldCharaCoordinate[1].y = ((MapCharaPositionY - 3) * CELL_SIZE);
				m_WorldCharaCoordinate[2].y = ((MapCharaPositionY + 1) * CELL_SIZE);
				m_WorldCharaCoordinate[3].y = ((MapCharaPositionY + 1) * CELL_SIZE);
				for (int i = 0;i < 4;i++)
				{
					m_DisplayCharaCoordinate[i].y = m_WorldCharaCoordinate[i].y + m_pMapChip->m_MapScrollY;
				}
			}
		}
		if (m_PrevMapCharaPositionX >= m_WorldCharaCoordinate[3].x)
		{
			//左の方向のブロックを確かめる
			if ((m_pMapChip->getMapChipData(MapCharaPositionY - 1, MapCharaPositionX) != 0 &&m_pMapChip->getMapChipData(MapCharaPositionY - 1, MapCharaPositionX) < 3) ||
				(m_pMapChip->getMapChipData(MapCharaPositionY - 2, MapCharaPositionX) != 0 &&m_pMapChip->getMapChipData(MapCharaPositionY - 2, MapCharaPositionX) < 3) ||
				(m_pMapChip->getMapChipData(MapCharaPositionY - 3, MapCharaPositionX) != 0 &&m_pMapChip->getMapChipData(MapCharaPositionY - 3, MapCharaPositionX) < 3) ||
				(m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapCharaPositionX) != 0 &&m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapCharaPositionX) < 3))
			{
				if (m_PrevMapCharaPositionX != m_WorldCharaCoordinate[3].x)
				{
						m_WorldCharaCoordinate[0].x = ((MapCharaPositionX + 1) * CELL_SIZE);
						m_WorldCharaCoordinate[1].x = ((MapCharaPositionX + 3) * CELL_SIZE);
						m_WorldCharaCoordinate[2].x = ((MapCharaPositionX + 3) * CELL_SIZE);
						m_WorldCharaCoordinate[3].x = ((MapCharaPositionX + 1) * CELL_SIZE);
						for (int i = 0;i < 4;i++)
						{
							m_DisplayCharaCoordinate[i].x = m_WorldCharaCoordinate[i].x + m_pMapChip->m_MapScrollX;
						}
				}
			}
		}
		if (m_PrevMapCharaPositionX2 <= m_WorldCharaCoordinate[2].x)
		{
			//右方向のブロックを確かめる
			if ((m_pMapChip->getMapChipData(MapCharaPositionY - 1, MapCharaPositionX2) != 0 &&m_pMapChip->getMapChipData(MapCharaPositionY - 1, MapCharaPositionX2) < 3) ||
				(m_pMapChip->getMapChipData(MapCharaPositionY - 2, MapCharaPositionX2) != 0 &&m_pMapChip->getMapChipData(MapCharaPositionY - 2, MapCharaPositionX2) < 3) ||
				(m_pMapChip->getMapChipData(MapCharaPositionY - 3, MapCharaPositionX2) != 0 &&m_pMapChip->getMapChipData(MapCharaPositionY - 3, MapCharaPositionX2) < 3) ||
				(m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapCharaPositionX2) != 0 &&m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapCharaPositionX2) < 3))
			{
				if (m_PrevMapCharaPositionX2 != m_WorldCharaCoordinate[2].x)
				{
					m_WorldCharaCoordinate[0].x = ((MapCharaPositionX2 - 2) * CELL_SIZE) - 1;
					m_WorldCharaCoordinate[1].x = ((MapCharaPositionX2) * CELL_SIZE) - 1;
					m_WorldCharaCoordinate[2].x = ((MapCharaPositionX2) * CELL_SIZE) - 1;
					m_WorldCharaCoordinate[3].x = ((MapCharaPositionX2 - 2) * CELL_SIZE) - 1;
					for (int i = 0;i < 4;i++)
					{
						m_DisplayCharaCoordinate[i].x = m_WorldCharaCoordinate[i].x + m_pMapChip->m_MapScrollX - 1;
					}
				}
			}
		}
}



void GameChara::Render()
{
	TextureRender("CHARA_INTEGRATION_TEX", m_DisplayCharaCoordinate);
}
