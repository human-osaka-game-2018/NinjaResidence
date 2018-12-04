#include "GameChara.h"
#include "MapChip.h"

using  namespace MapBlock;

GameChara::GameChara(DirectX* pDirectX, Object* MapChip) :Object(pDirectX)
{
	Gravity = 15.f;
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
			pDisplayCharaCoordinate[i].y -= MoveQuantity;
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
			pDisplayCharaCoordinate[i].x += MoveQuantity;
		}
		break;
	case LEFT:
		//左に移動
		for (int i = 0;i < 4;i++)
		{
			pWorldCharaCoordinate[i].x -= MoveQuantity;
			pDisplayCharaCoordinate[i].x -= MoveQuantity;
		}
		break;
	}
}




void GameChara::ValueAllSetCUSTOMVERTEX(CUSTOMVERTEX* Receive, CUSTOMVERTEX* Give)
{
	//Receive[0] = Give[0];
	//Receive[1] = Give[1];
	//Receive[2] = Give[2];
	//Receive[3] = Give[3];
}


void GameChara::prevSaveMapCharaPos()
{
	m_PrevMapLeftDirectionPosition = (int)m_WorldCharaCoordinate[3].x;
	m_PrevMapRightDirectionPosition = (int)m_WorldCharaCoordinate[2].x;
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


void GameChara::MapReversePointSearch(int BlockNumber)
{
	for (int i = 0;i < colunm;i++)
	{
		for (int j = 0;j < row;j++)
		{
			if (m_pMapChip->getMapChipData(i, j) == BlockNumber)
			{
				m_WorldCharaCoordinate[0].x = (j * CELL_SIZE);
				m_WorldCharaCoordinate[1].x = (j * CELL_SIZE) + m_Player.scale_x;
				m_WorldCharaCoordinate[2].x = (j * CELL_SIZE) + m_Player.scale_x;
				m_WorldCharaCoordinate[3].x = (j * CELL_SIZE);
				m_WorldCharaCoordinate[0].y = (i * CELL_SIZE) - m_Player.scale_y;
				m_WorldCharaCoordinate[1].y = (i * CELL_SIZE) - m_Player.scale_y;
				m_WorldCharaCoordinate[2].y = (i * CELL_SIZE);
				m_WorldCharaCoordinate[3].y = (i * CELL_SIZE);
				for (int i = 0;i < 4;i++)
				{
					m_DisplayCharaCoordinate[i].y = m_WorldCharaCoordinate[i].y + m_pMapChip->m_MapScrollY;
				}
				for (int i = 0;i < 4;i++)
				{
					m_DisplayCharaCoordinate[i].x = m_WorldCharaCoordinate[i].x + m_pMapChip->m_MapScrollX;
				}
			}
		}
	}
}


void GameChara::CharaInforSave(Object* MapChip,int BlockNumber)
{
	m_pMapChip = MapChip;
	switch (BlockNumber)
	{
	case WOOD_REVERSE_ZONE:
		MapReversePointSearch(BlockNumber);
		break;
	case ROCK_REVERSE_ZONE:
		MapReversePointSearch(BlockNumber);
		break;
	}
}


void GameChara::MapScroolCheck()
{
	//上にスクロール移動
	if (m_DisplayCharaCoordinate[1].y < DisplayCharMoveScopeUp)
	{
		if (m_WorldCharaCoordinate[0].y >= DisplayCharMoveScopeUp)
		{
			m_DisplayCharaCoordinate[0].y =( DisplayCharMoveScopeUp);
			m_DisplayCharaCoordinate[1].y =( DisplayCharMoveScopeUp);
			m_DisplayCharaCoordinate[2].y =( DisplayCharMoveScopeUp + m_Player.scale_y);
			m_DisplayCharaCoordinate[3].y =( DisplayCharMoveScopeUp + m_Player.scale_y);
			m_pMapChip->m_MapScrollY += CharaMoveSpeed;
		}
	}
	//下にスクロール移動
	if (m_DisplayCharaCoordinate[3].y > DisplayCharMoveScopeDown)
	{
		m_DisplayCharaCoordinate[0].y = (DisplayCharMoveScopeDown - m_Player.scale_y);
		m_DisplayCharaCoordinate[1].y = (DisplayCharMoveScopeDown - m_Player.scale_y);
		m_DisplayCharaCoordinate[2].y = (DisplayCharMoveScopeDown);
		m_DisplayCharaCoordinate[3].y = (DisplayCharMoveScopeDown);
		m_pMapChip->m_MapScrollY -= CharaMoveSpeed;
	}
	//右にスクロール移動
	if (m_DisplayCharaCoordinate[1].x > DisplayCharMoveScopeRight)
	{
		if (m_WorldCharaCoordinate[1].x <= ((row * CELL_SIZE)- DisplayCharMoveScopeX))
		{
			m_DisplayCharaCoordinate[0].x = (DisplayCharMoveScopeRight - m_Player.scale_x);
			m_DisplayCharaCoordinate[1].x = (DisplayCharMoveScopeRight);
			m_DisplayCharaCoordinate[2].x = (DisplayCharMoveScopeRight);
			m_DisplayCharaCoordinate[3].x = (DisplayCharMoveScopeRight - m_Player.scale_x);
			m_pMapChip->m_MapScrollX -= CharaMoveSpeed;
		}
	}
	//左にスクロール移動
	if (m_DisplayCharaCoordinate[0].x < DisplayCharMoveScopeLeft)
	{
		if(m_WorldCharaCoordinate[0].x >= DisplayCharMoveScopeX)
		{
		m_DisplayCharaCoordinate[0].x = (DisplayCharMoveScopeLeft);
		m_DisplayCharaCoordinate[1].x = (DisplayCharMoveScopeLeft + m_Player.scale_x);
		m_DisplayCharaCoordinate[2].x = (DisplayCharMoveScopeLeft + m_Player.scale_x);
		m_DisplayCharaCoordinate[3].x = (DisplayCharMoveScopeLeft);
		m_pMapChip->m_MapScrollX += CharaMoveSpeed;
		}
	}
}

void GameChara::Update()
{
		MapScroolCheck();
		MapLeftDirectionPosition = (int)m_WorldCharaCoordinate[3].x / CELL_SIZE;
		MapRightDirectionPosition = (int)(m_WorldCharaCoordinate[2].x) / CELL_SIZE;
		MapCharaPositionY = (int)(m_WorldCharaCoordinate[3].y + 10) / CELL_SIZE;
		//重力を毎フレームかける
		for (int i = 0; i < 4; i++)
		{
			m_WorldCharaCoordinate[i].y += Gravity;
			m_DisplayCharaCoordinate[i].y += Gravity;
		}
		//下の方向を確かめる
		if ((m_pMapChip->getMapChipData(MapCharaPositionY,MapLeftDirectionPosition) != NONE) ||
			(m_pMapChip->getMapChipData(MapCharaPositionY,MapLeftDirectionPosition + 1) != NONE) ||
			(m_pMapChip->getMapChipData(MapCharaPositionY,MapLeftDirectionPosition + 2) != NONE))
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
			if ((    m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapLeftDirectionPosition) != NONE)||
				(m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapLeftDirectionPosition + 1) != NONE)||
				(m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapLeftDirectionPosition + 2) != NONE))
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
		if (m_PrevMapLeftDirectionPosition >= m_WorldCharaCoordinate[3].x)
		{
			//左の方向のブロックを確かめる
			if ((m_pMapChip->getMapChipData(MapCharaPositionY - 1, MapLeftDirectionPosition) != NONE )||
				(m_pMapChip->getMapChipData(MapCharaPositionY - 2, MapLeftDirectionPosition) != NONE )||
				(m_pMapChip->getMapChipData(MapCharaPositionY - 3, MapLeftDirectionPosition) != NONE )||
				(m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapLeftDirectionPosition) != NONE ))
			{
				if (m_PrevMapLeftDirectionPosition != m_WorldCharaCoordinate[3].x)
				{
						m_WorldCharaCoordinate[0].x = ((MapLeftDirectionPosition + 1) * CELL_SIZE);
						m_WorldCharaCoordinate[1].x = ((MapLeftDirectionPosition + 3) * CELL_SIZE);
						m_WorldCharaCoordinate[2].x = ((MapLeftDirectionPosition + 3) * CELL_SIZE);
						m_WorldCharaCoordinate[3].x = ((MapLeftDirectionPosition + 1) * CELL_SIZE);
						for (int i = 0;i < 4;i++)
						{
							m_DisplayCharaCoordinate[i].x = m_WorldCharaCoordinate[i].x + m_pMapChip->m_MapScrollX;
						}
				}
			}
		}
		if (m_PrevMapRightDirectionPosition <= m_WorldCharaCoordinate[2].x)
		{
			//右方向のブロックを確かめる
			if ((m_pMapChip->getMapChipData(MapCharaPositionY - 1, MapRightDirectionPosition) != NONE )||
				(m_pMapChip->getMapChipData(MapCharaPositionY - 2, MapRightDirectionPosition) != NONE )||
				(m_pMapChip->getMapChipData(MapCharaPositionY - 3, MapRightDirectionPosition) != NONE )||
				(m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapRightDirectionPosition) != NONE ))
			{
				if (m_PrevMapRightDirectionPosition != m_WorldCharaCoordinate[2].x)
				{
					m_WorldCharaCoordinate[0].x = ((MapRightDirectionPosition - 2) * CELL_SIZE) - 1;
					m_WorldCharaCoordinate[1].x = ((MapRightDirectionPosition) * CELL_SIZE) - 1;
					m_WorldCharaCoordinate[2].x = ((MapRightDirectionPosition) * CELL_SIZE) - 1;
					m_WorldCharaCoordinate[3].x = ((MapRightDirectionPosition - 2) * CELL_SIZE) - 1;
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
