/**
* @file GameChara.cpp
* @brief GameCharaクラス
* @author Kojiro Kawahara
*/
#include "GameChara.h"
#include "MapChip.h"

using  namespace MapBlock;

GameChara::GameChara(DirectX* pDirectX, SoundsManager* pSoundManager, Object* MapChip) :Object(pDirectX,pSoundManager)
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



void GameChara::CharaMoveOperation(KeyDirection vec, CUSTOMVERTEX* pWorldCharaCoordinate, CUSTOMVERTEX* pDisplayCharaCoordinate, float MoveQuantity)
{
	switch (vec)
	{
		//上に移動
	case UP:
		//for (int i = 0;i < 4;i++)
		//{
		//	pWorldCharaCoordinate[i].y -= MoveQuantity;
		//	pDisplayCharaCoordinate[i].y -= MoveQuantity;
		//}
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
		//今のところ無し
		break;
	case RIGHT:
		//右に移動
		CharaMoveOperation(RIGHT, m_WorldCharaCoordinate, m_DisplayCharaCoordinate, CharaMoveSpeed);
		break;
	case LEFT:
		//左に移動
		CharaMoveOperation(LEFT, m_WorldCharaCoordinate, m_DisplayCharaCoordinate, CharaMoveSpeed);
		break;
	case SoundOn:
		m_pSoundManager->Start("DECISION");
		break;
	}
}


void GameChara::CharaInforSave(int MapReverseSelect,Object* MapChip)
{
	m_pMapChip = MapChip;
	if (!MapReverseSelect)
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
	if ((m_pMapChip->getMapChipData(MapCharaPositionY, MapLeftDirectionPosition) != NONE) ||
		(m_pMapChip->getMapChipData(MapCharaPositionY, MapLeftDirectionPosition + 1) != NONE) ||
		(m_pMapChip->getMapChipData(MapCharaPositionY, MapLeftDirectionPosition + 2) != NONE))
	{
		m_WorldCharaCoordinate[0].y = ((MapCharaPositionY - 4) * CELL_SIZE);
		m_WorldCharaCoordinate[1].y = ((MapCharaPositionY - 4) * CELL_SIZE);
		m_WorldCharaCoordinate[2].y = ((MapCharaPositionY)* CELL_SIZE);
		m_WorldCharaCoordinate[3].y = ((MapCharaPositionY)* CELL_SIZE);
		for (int i = 0; i < 4; i++)
		{
			m_DisplayCharaCoordinate[i].y = m_WorldCharaCoordinate[i].y + m_pMapChip->m_MapScrollY;
		}
	}
	//上のブロックを確かめる
	if (m_PrevMapCharaPositionY > m_WorldCharaCoordinate[3].y + 10)
	{
		if ((m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapLeftDirectionPosition) != NONE) ||
			(m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapLeftDirectionPosition + 1) != NONE) ||
			(m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapLeftDirectionPosition + 2) != NONE))
		{
			m_WorldCharaCoordinate[0].y = ((MapCharaPositionY - 3) * CELL_SIZE);
			m_WorldCharaCoordinate[1].y = ((MapCharaPositionY - 3) * CELL_SIZE);
			m_WorldCharaCoordinate[2].y = ((MapCharaPositionY + 1) * CELL_SIZE);
			m_WorldCharaCoordinate[3].y = ((MapCharaPositionY + 1) * CELL_SIZE);
			for (int i = 0; i < 4; i++)
			{
				m_DisplayCharaCoordinate[i].y = m_WorldCharaCoordinate[i].y + m_pMapChip->m_MapScrollY;
			}
		}
	}
	if (m_PrevMapLeftDirectionPosition >= m_WorldCharaCoordinate[3].x)
	{
		//左の方向のブロックを確かめる
		if ((m_pMapChip->getMapChipData(MapCharaPositionY - 1, MapLeftDirectionPosition) != NONE) ||
			(m_pMapChip->getMapChipData(MapCharaPositionY - 2, MapLeftDirectionPosition) != NONE) ||
			(m_pMapChip->getMapChipData(MapCharaPositionY - 3, MapLeftDirectionPosition) != NONE) ||
			(m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapLeftDirectionPosition) != NONE))
		{
			if (m_PrevMapLeftDirectionPosition != m_WorldCharaCoordinate[3].x)
			{
				m_WorldCharaCoordinate[0].x = ((MapLeftDirectionPosition + 1) * CELL_SIZE);
				m_WorldCharaCoordinate[1].x = ((MapLeftDirectionPosition + 3) * CELL_SIZE);
				m_WorldCharaCoordinate[2].x = ((MapLeftDirectionPosition + 3) * CELL_SIZE);
				m_WorldCharaCoordinate[3].x = ((MapLeftDirectionPosition + 1) * CELL_SIZE);
				for (int i = 0; i < 4; i++)
				{
					m_DisplayCharaCoordinate[i].x = m_WorldCharaCoordinate[i].x + m_pMapChip->m_MapScrollX;
				}
			}
		}
	}
	if (m_PrevMapRightDirectionPosition <= m_WorldCharaCoordinate[2].x)
	{
		//右方向のブロックを確かめる
		if ((m_pMapChip->getMapChipData(MapCharaPositionY - 1, MapRightDirectionPosition) != NONE) ||
			(m_pMapChip->getMapChipData(MapCharaPositionY - 2, MapRightDirectionPosition) != NONE) ||
			(m_pMapChip->getMapChipData(MapCharaPositionY - 3, MapRightDirectionPosition) != NONE) ||
			(m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapRightDirectionPosition) != NONE))
		{
			if (m_PrevMapRightDirectionPosition != m_WorldCharaCoordinate[2].x)
			{
				m_WorldCharaCoordinate[0].x = ((MapRightDirectionPosition - 2) * CELL_SIZE) - 1;
				m_WorldCharaCoordinate[1].x = ((MapRightDirectionPosition)* CELL_SIZE) - 1;
				m_WorldCharaCoordinate[2].x = ((MapRightDirectionPosition)* CELL_SIZE) - 1;
				m_WorldCharaCoordinate[3].x = ((MapRightDirectionPosition - 2) * CELL_SIZE) - 1;
				for (int i = 0; i < 4; i++)
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

	RECT test = { 0,0,1200,500 };
	char TestText[ArrayLong];
	sprintf_s(TestText, ArrayLong, "\nPrevMapChara::X-L:%d,X-R:%d,Y:%d", m_PrevMapLeftDirectionPosition, m_PrevMapRightDirectionPosition, m_PrevMapCharaPositionY);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_LEFT, 0xffffffff);
	sprintf_s(TestText, ArrayLong, "\n\nWorldChara::X-L:%.2f,X-R:%.2f,Y:%.2f", m_WorldCharaCoordinate[3].x, m_WorldCharaCoordinate[2].x, m_WorldCharaCoordinate[3].y);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_LEFT, 0xffffffff);
	sprintf_s(TestText, ArrayLong, "\n\n\nDisplayChara::X-L:%.2f,X-R:%.2f,Y:%.2f", m_DisplayCharaCoordinate[3].x, m_DisplayCharaCoordinate[2].x, m_DisplayCharaCoordinate[3].y);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_LEFT, 0xffffffff);

}
