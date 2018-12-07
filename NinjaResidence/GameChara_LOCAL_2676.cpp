#include "GameChara.h"
#include "MapChip.h"

using  namespace MapBlock;

GameChara::GameChara(DirectX* pDirectX, Object* MapChip) :Object(pDirectX)
{
	Gravity = 15.f;
	//MapChip‚Ìî•ñ‚ğæ“¾‚·‚é‚½‚ß‚É•K—v
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
<<<<<<< HEAD
		//ã‚ÉˆÚ“®
	case UP:
		for (int i = 0;i < 4;i++)
		{
			pWorldCharaCoordinate[i].y -= MoveQuantity;
			pDisplayCharaCoordinate[i].y -= MoveQuantity;
		}
		break;
	case DOWN:
		//¡‚Ì‚Æ‚±‚ë‚È‚µ

		break;
	case RIGHT:
		//‰E‚ÉˆÚ“®
		for (int i = 0;i < 4;i++)
		{
			pWorldCharaCoordinate[i].x += MoveQuantity;
			pDisplayCharaCoordinate[i].x += MoveQuantity;
=======
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
		break;
	case DOWN:
		////¡‚Ì‚Æ‚±‚ë–³‚µ
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
		//‰E‚ÉˆÚ“®
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
>>>>>>> Xåº§æ¨™ã®å½“ãŸã‚Šåˆ¤å®šã‚’ã‚¹ã‚¯ãƒ­ãƒ¼ãƒ«ã«å¯¾å¿œã€yåº§æ¨™ã®ã‚¹ã‚¯ãƒ­ãƒ¼ãƒ«ï¼ˆå½“ãŸã‚Šåˆ¤å®šéå¯¾å¿œï¼‰
		}
		break;
	case LEFT:
		//¶‚ÉˆÚ“®
<<<<<<< HEAD
		for (int i = 0;i < 4;i++)
		{
			pWorldCharaCoordinate[i].x -= MoveQuantity;
			pDisplayCharaCoordinate[i].x -= MoveQuantity;
=======
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
>>>>>>> Xåº§æ¨™ã®å½“ãŸã‚Šåˆ¤å®šã‚’ã‚¹ã‚¯ãƒ­ãƒ¼ãƒ«ã«å¯¾å¿œã€yåº§æ¨™ã®ã‚¹ã‚¯ãƒ­ãƒ¼ãƒ«ï¼ˆå½“ãŸã‚Šåˆ¤å®šéå¯¾å¿œï¼‰
		}
		break;
	}
}



<<<<<<< HEAD

void GameChara::ValueAllSetCUSTOMVERTEX(CUSTOMVERTEX* Receive, CUSTOMVERTEX* Give)
{
	Receive[0] = Give[0];
	Receive[1] = Give[1];
	Receive[2] = Give[2];
	Receive[3] = Give[3];
}


void GameChara::prevSaveMapCharaPos()
{
	m_PrevMapLeftDirectionPosition = (int)m_WorldCharaCoordinate[3].x;
	m_PrevMapRightDirectionPosition = (int)m_WorldCharaCoordinate[2].x;
	m_PrevMapCharaPositionY = (int)m_WorldCharaCoordinate[3].y + 10;
=======
void GameChara::MapScroolCheck()
{
	//ã‚ÉˆÚ“®
	if (m_DisplayCharaCoordinate[1].y < 200)
	{
		m_DisplayCharaCoordinate[0].y = 200;
		m_DisplayCharaCoordinate[1].y = 200;
		m_DisplayCharaCoordinate[2].y = 360;
		m_DisplayCharaCoordinate[3].y = 360;
		m_pMapChip->m_MapScrollY += 10;
	}
	//‰º‚ÉˆÚ“®
	if (m_DisplayCharaCoordinate[3].y > 600)
	{
		m_DisplayCharaCoordinate[0].y = 440;
		m_DisplayCharaCoordinate[1].y = 440;
		m_DisplayCharaCoordinate[2].y = 600;
		m_DisplayCharaCoordinate[3].y = 600;
		m_pMapChip->m_MapScrollY -= 10;
	}
	//‰E‚ÉˆÚ“®
	if (m_DisplayCharaCoordinate[1].x > 900)
	{
		m_DisplayCharaCoordinate[0].x = 820;
		m_DisplayCharaCoordinate[1].x = 900;
		m_DisplayCharaCoordinate[2].x = 900;
		m_DisplayCharaCoordinate[3].x = 820;
		m_pMapChip->m_MapScrollX -= 10;
	}
	//¶‚ÉˆÚ“®
	if (m_DisplayCharaCoordinate[0].x < 300)
	{
		m_DisplayCharaCoordinate[0].x = 300;
		m_DisplayCharaCoordinate[1].x = 380;
		m_DisplayCharaCoordinate[2].x = 380;
		m_DisplayCharaCoordinate[3].x = 300;
		m_pMapChip->m_MapScrollX += 10;
	}
>>>>>>> Xåº§æ¨™ã®å½“ãŸã‚Šåˆ¤å®šã‚’ã‚¹ã‚¯ãƒ­ãƒ¼ãƒ«ã«å¯¾å¿œã€yåº§æ¨™ã®ã‚¹ã‚¯ãƒ­ãƒ¼ãƒ«ï¼ˆå½“ãŸã‚Šåˆ¤å®šéå¯¾å¿œï¼‰
}




void GameChara::KeyOperation(KeyDirection vec)
{
<<<<<<< HEAD
	//Key‘€ì‚Å‚Ìˆ—
	switch (vec)
=======
	GameChara::MapScroolCheck();
	MapCharaPositionX = (int)m_WorldCharaCoordinate[3].x / 40;
	MapCharaPositionX2 = (int)(m_WorldCharaCoordinate[2].x) / 40;
	MapCharaPositionY = (int)m_WorldCharaCoordinate[3].y / 40;
	if (m_pMapChip->MapData[MapCharaPositionY][MapCharaPositionX] == 0 && m_pMapChip->MapData[MapCharaPositionY][MapCharaPositionX + 1] == 0)
>>>>>>> Xåº§æ¨™ã®å½“ãŸã‚Šåˆ¤å®šã‚’ã‚¹ã‚¯ãƒ­ãƒ¼ãƒ«ã«å¯¾å¿œã€yåº§æ¨™ã®ã‚¹ã‚¯ãƒ­ãƒ¼ãƒ«ï¼ˆå½“ãŸã‚Šåˆ¤å®šéå¯¾å¿œï¼‰
	{
	case UP:
		CharaMoveOperation(UP, m_WorldCharaCoordinate, m_DisplayCharaCoordinate, 30.0f);
		break;
	case DOWN:
		////¡‚Ì‚Æ‚±‚ë–³‚µ
		CharaMoveOperation(DOWN, m_WorldCharaCoordinate, m_DisplayCharaCoordinate, CharaMoveSpeed);
		break;
	case RIGHT:
		//‰E‚ÉˆÚ“®
		CharaMoveOperation(RIGHT, m_WorldCharaCoordinate, m_DisplayCharaCoordinate, CharaMoveSpeed);
		break;
	case LEFT:
		//¶‚ÉˆÚ“®
		CharaMoveOperation(LEFT, m_WorldCharaCoordinate, m_DisplayCharaCoordinate, CharaMoveSpeed);
		break;

	}
<<<<<<< HEAD
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
=======
	//¶‚Ì•ûŒü‚ÌƒuƒƒbƒN‚ğŠm‚©‚ß‚é
	if (m_pMapChip->MapData[MapCharaPositionY - 1][MapCharaPositionX] != 0 || m_pMapChip->MapData[MapCharaPositionY - 2][MapCharaPositionX] != 0 || m_pMapChip->MapData[MapCharaPositionY - 3][MapCharaPositionX] != 0 || m_pMapChip->MapData[MapCharaPositionY - 4][MapCharaPositionX] != 0)
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
	//‰E•ûŒü‚ÌƒuƒƒbƒN‚ğŠm‚©‚ß‚é
	else if (m_pMapChip->MapData[MapCharaPositionY - 1][MapCharaPositionX2] != 0 || m_pMapChip->MapData[MapCharaPositionY - 2][MapCharaPositionX2] != 0 || m_pMapChip->MapData[MapCharaPositionY - 3][MapCharaPositionX2] != 0 || m_pMapChip->MapData[MapCharaPositionY - 4][MapCharaPositionX2] != 0)
	{
		m_WorldCharaCoordinate[0].x = ((MapCharaPositionX2 -2) * 40);
		m_WorldCharaCoordinate[1].x = ((MapCharaPositionX2 ) * 40);
		m_WorldCharaCoordinate[2].x = ((MapCharaPositionX2 ) * 40);
		m_WorldCharaCoordinate[3].x = ((MapCharaPositionX2 -2) * 40);
		m_DisplayCharaCoordinate[0].x = m_WorldCharaCoordinate[0].x + m_pMapChip->m_MapScrollX;
		m_DisplayCharaCoordinate[1].x = m_WorldCharaCoordinate[1].x + m_pMapChip->m_MapScrollX;
		m_DisplayCharaCoordinate[2].x = m_WorldCharaCoordinate[2].x + m_pMapChip->m_MapScrollX;
		m_DisplayCharaCoordinate[3].x = m_WorldCharaCoordinate[3].x + m_pMapChip->m_MapScrollX;
>>>>>>> Xåº§æ¨™ã®å½“ãŸã‚Šåˆ¤å®šã‚’ã‚¹ã‚¯ãƒ­ãƒ¼ãƒ«ã«å¯¾å¿œã€yåº§æ¨™ã®ã‚¹ã‚¯ãƒ­ãƒ¼ãƒ«ï¼ˆå½“ãŸã‚Šåˆ¤å®šéå¯¾å¿œï¼‰
	}
}


void GameChara::MapScroolCheck()
{
	//ã‚ÉƒXƒNƒ[ƒ‹ˆÚ“®
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
	//‰º‚ÉƒXƒNƒ[ƒ‹ˆÚ“®
	if (m_DisplayCharaCoordinate[3].y > DisplayCharMoveScopeDown)
	{
		m_DisplayCharaCoordinate[0].y = (DisplayCharMoveScopeDown - m_Player.scale_y);
		m_DisplayCharaCoordinate[1].y = (DisplayCharMoveScopeDown - m_Player.scale_y);
		m_DisplayCharaCoordinate[2].y = (DisplayCharMoveScopeDown);
		m_DisplayCharaCoordinate[3].y = (DisplayCharMoveScopeDown);
		m_pMapChip->m_MapScrollY -= CharaMoveSpeed;
	}
	//‰E‚ÉƒXƒNƒ[ƒ‹ˆÚ“®
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
	//¶‚ÉƒXƒNƒ[ƒ‹ˆÚ“®
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
		//d—Í‚ğ–ˆƒtƒŒ[ƒ€‚©‚¯‚é
		for (int i = 0; i < 4; i++)
		{
			m_WorldCharaCoordinate[i].y += Gravity;
			m_DisplayCharaCoordinate[i].y += Gravity;
		}
		//‰º‚Ì•ûŒü‚ğŠm‚©‚ß‚é
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
		//ã‚ÌƒuƒƒbƒN‚ğŠm‚©‚ß‚é
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
			//¶‚Ì•ûŒü‚ÌƒuƒƒbƒN‚ğŠm‚©‚ß‚é
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
			//‰E•ûŒü‚ÌƒuƒƒbƒN‚ğŠm‚©‚ß‚é
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
