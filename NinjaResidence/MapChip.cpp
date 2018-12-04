/**
* @file MapChip.cpp
* @brief MapChipÉNÉâÉX
* @author Kojiro Kawahara
*/
#include "MapChip.h"

using std::vector;
using namespace MapBlock;

MapChip::MapChip(DirectX* pDirectX, SoundOperater* pSoundOperater) :Object(pDirectX,pSoundOperater)
{
	CellInit();
}

MapChip::~MapChip()
{
	for (int i = 0; i < m_colunm; i++)
	{
		MapData[i].clear();
		vector<int>().swap(MapData[i]);
	}
	MapData.clear();
	vector<vector<int>>().swap(MapData);

}

void MapChip::Create(const char *filename)
{
	const int mapMaxWidth = 256;
	FILE *fp = NULL;
	char data[4];
	char buf[mapMaxWidth];
	//int cÇÕâΩÇÇµÇƒÇ¢ÇÈïœêîÅH
	int c, i = 0, x = 0, y = 0;

	if (fopen_s(&fp, filename, "r") != 0)
	{
		exit(1);
	}

	fgets(buf, mapMaxWidth, fp);
	sscanf_s(buf, "%d, %d", &m_row, &m_colunm);

	MapData.resize(m_colunm);

	for (int j = 0; j<m_colunm; j++)
	{
		MapData[j].resize(m_row);
	}


	while ((c = getc(fp)) != EOF || y < m_colunm)
	{
		if (isdigit(c))
		{
			data[i] = (char)c;
			i++;
		}
		else
		{
			data[i] = NULL;
			MapData[y][x] = atoi(data);
			x++;
			i = 0;
			if (x == m_row) {
				y++;
				x = 0;
			}
		}
	}
	fclose(fp);
}

void MapChip::Render()
{
	for (int j = 0; j < m_colunm;j++)
	{
		for (int i = 0;i < m_row;i++)
		{
			if (MapData[j][i] == 0)
			{
				continue;
			}
			int top = FIELD_TOP + (CELL_SIZE * j) + m_MapScrollY;
			int left = FIELD_LEFT + (CELL_SIZE * i) + m_MapScrollX;
			CELL[0].x = left;
			CELL[0].y = top;
			CELL[1].x = (left + CELL_SIZE);
			CELL[1].y = top;
			CELL[2].x = (left + CELL_SIZE);
			CELL[2].y = (top + CELL_SIZE);
			CELL[3].x = left;
			CELL[3].y = (top + CELL_SIZE);

			m_MapSelected = MapData[j][i];
			switch (m_MapSelected)
			{
			case WOOD_BLOCK:
				CELL[0].tu = BLOCK_WIDTH * (m_MapSelected - 1);
				CELL[3].tu = BLOCK_WIDTH * (m_MapSelected - 1);
				CELL[1].tu = BLOCK_WIDTH * m_MapSelected;
				CELL[2].tu = BLOCK_WIDTH * m_MapSelected;
				CELL[0].tv = 0.f;
				CELL[1].tv = 0.f;
				CELL[2].tv = BLOCK_HEIGHT;
				CELL[3].tv = BLOCK_HEIGHT;
				break;
			case ROCK_BLOCK:
				CELL[0].tu = BLOCK_WIDTH * (m_MapSelected - 1);
				CELL[3].tu = BLOCK_WIDTH * (m_MapSelected - 1);
				CELL[1].tu = BLOCK_WIDTH * m_MapSelected;
				CELL[2].tu = BLOCK_WIDTH * m_MapSelected;
				CELL[0].tv = 0.f;
				CELL[1].tv = 0.f;
				CELL[2].tv = BLOCK_HEIGHT;
				CELL[3].tv = BLOCK_HEIGHT;
				break;
			case WOOD_TRACT:
				CELL[0].tu = BLOCK_WIDTH * (m_MapSelected - 1);
				CELL[3].tu = BLOCK_WIDTH * (m_MapSelected - 1);
				CELL[1].tu = BLOCK_WIDTH * m_MapSelected;
				CELL[2].tu = BLOCK_WIDTH * m_MapSelected;
				CELL[0].tv = 0.f;
				CELL[1].tv = 0.f;
				CELL[2].tv = BLOCK_HEIGHT;
				CELL[3].tv = BLOCK_HEIGHT;
				break;
			case ROCK_TRACT:
				CELL[0].tu = BLOCK_WIDTH * (m_MapSelected - 1);
				CELL[3].tu = BLOCK_WIDTH * (m_MapSelected - 1);
				CELL[1].tu = BLOCK_WIDTH * m_MapSelected;
				CELL[2].tu = BLOCK_WIDTH * m_MapSelected;
				CELL[0].tv = 0.f;
				CELL[1].tv = 0.f;
				CELL[2].tv = BLOCK_HEIGHT;
				CELL[3].tv = BLOCK_HEIGHT;
				break;
			case WOOD_REVERSE_ZONE:
				CELL[0].tu = BLOCK_WIDTH * (m_MapSelected - 1);
				CELL[3].tu = BLOCK_WIDTH * (m_MapSelected - 1);
				CELL[1].tu = BLOCK_WIDTH * m_MapSelected;
				CELL[2].tu = BLOCK_WIDTH * m_MapSelected;
				CELL[0].tv = 0.f;
				CELL[1].tv = 0.f;
				CELL[2].tv = BLOCK_HEIGHT;
				CELL[3].tv = BLOCK_HEIGHT;
				break;
			case ROCK_REVERSE_ZONE:
				CELL[0].tu = BLOCK_WIDTH * (m_MapSelected - 1);
				CELL[3].tu = BLOCK_WIDTH * (m_MapSelected - 1);
				CELL[1].tu = BLOCK_WIDTH * m_MapSelected;
				CELL[2].tu = BLOCK_WIDTH * m_MapSelected;
				CELL[0].tv = 0.f;
				CELL[1].tv = 0.f;
				CELL[2].tv = BLOCK_HEIGHT;
				CELL[3].tv = BLOCK_HEIGHT;
				break;
			case DESCRIPTION_BOARD:
				CELL[0].tu = 0.f;
				CELL[3].tu = 0.f;
				CELL[1].tu = 0.24f;
				CELL[2].tu = 0.24f;
				CELL[0].tv = 0.16f;
				CELL[1].tv = 0.16f;
				CELL[2].tv = BLOCK_HEIGHT + 0.16f;
				CELL[3].tv = BLOCK_HEIGHT + 0.16f;
				CELL[1].x += 120.f;
				CELL[2].x += 120.f;
				CELL[3].y += 80.f;
				CELL[2].y += 80.f;
				break;
			case DESCRIPTION_BOARD2:
				CELL[0].tu = 0.f;
				CELL[3].tu = 0.f;
				CELL[1].tu = 0.24f;
				CELL[2].tu = 0.24f;
				CELL[0].tv = 0.16f;
				CELL[1].tv = 0.16f;
				CELL[2].tv = BLOCK_HEIGHT + 0.16f;
				CELL[3].tv = BLOCK_HEIGHT + 0.16f;
				CELL[1].x += 120.f;
				CELL[2].x += 120.f;
				CELL[3].y += 80.f;
				CELL[2].y += 80.f;
				break;
			}
		TextureRender("BLOCK_INTEGRATION_TEX", CELL);
		}
	}
#ifdef _DEBUG

	RECT test = { 0,500,1250,700 };
	char TestText[ArrayLong];
	sprintf_s(TestText, ArrayLong, "MapScroll::X:%d,Y:%d", m_MapScrollX, m_MapScrollY);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_RIGHT, 0xffffffff);
#endif
}

void MapChip::Update() {
	if (m_MapScrollY > 0) {
		m_MapScrollY = 0;
	}
}

bool MapChip::RestrictBottomScroll() {
	float MapBottom = FIELD_TOP + (CELL_SIZE * (m_colunm + 1) )+ m_MapScrollY;
	if (MapBottom < DISPLAY_HEIGHT-20) {
		return true;
	}
	return false;
}

float MapChip::GetBottomPoint(int charaLeft, int charRight)
{
	float MapPosition = 0;
	for (int i = m_colunm - 1; i > 0; --i) {
		if (!MapData[i][charaLeft]) {
			return MapPosition = FIELD_TOP + (CELL_SIZE * (i - 4)) + m_MapScrollY;
		}
		if (!MapData[i][charRight]) {
			return MapPosition = FIELD_TOP + (CELL_SIZE * (i - 4)) + m_MapScrollY;
		}
	}
	return  0;
}
float MapChip::GetBottomWorldPoint(int charaLeft, int charRight)
{
	float MapPosition = 0;
	for (int i = m_colunm - 1; i > 0; --i) {
		if (!MapData[i][charaLeft]) {
			return MapPosition = FIELD_TOP + (CELL_SIZE * (i - 1));
		}
		if (!MapData[i][charRight]) {
			return MapPosition = FIELD_TOP + (CELL_SIZE * (i - 1));
		}
	}
	return  0;
}

void MapChip::CellInit() {
	for (int i = 0; i < 4; i++) {
		CELL[i].z = 1.0f;
		CELL[i].rhw = 1.0f;
		CELL[i].color = 0xFFFFFFFF;
	}
	CELL[0].tv = 0.f;
	CELL[1].tv = 0.f;
	CELL[2].tv = BLOCK_HEIGHT;
	CELL[3].tv = BLOCK_HEIGHT;

}
