#include "MapChip.h"

int MapChip::MapScrollx = 0;
int MapChip::MapScrolly = 0;

//コンストラクタでマップチップの生成だけ行う
MapChip::MapChip(Scene * pScene)
{
	m_pScene = pScene;
	CELL[0] = { 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0, 0.0f };
	CELL[1] = { 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0, 0.0f };
	CELL[2] = { 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0, BLOCK_HEIGHT };
	CELL[3] = { 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0, BLOCK_HEIGHT };
}

MapChip::~MapChip()
{
	for (int i = 0; i < colunm; i++)
	{
		MapData[i].clear();
		vector<int>().swap(MapData[i]);
	}
	MapData.clear();
	vector<vector<int>>().swap(MapData);

}

void MapChip::MapChipCreate(const char *filename)
{
	const int mapMaxWidth = 256;
	FILE *fp = NULL;
	char data[4];
	char buf[mapMaxWidth];
	int c, i = 0, x = 0, y = 0;

	if (fopen_s(&fp, filename, "r") != 0)
	{
		exit(1);
	}

	fgets(buf, mapMaxWidth, fp);
	sscanf_s(buf, "%d, %d", &row, &colunm);
	
	MapData.resize(colunm);

	for (int j = 0; j<colunm; j++)
	{
		MapData[j].resize(row);
	}
	
	
	while ((c = getc(fp)) != EOF || y < colunm)
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
			if (x == row) {
				y++;
				x = 0;
			}
		}
	}
	fclose(fp);
}

void MapChip::MapChipRender()
{
	for (int j = 0; j < colunm;j++)
	{
		for (int i = 0;i < row;i++)
		{
			if (MapData[j][i] == 0)
			{
				continue;
			}
			int top = FIELD_TOP + CELL_SIZE * j;
			int left = FIELD_LEFT + CELL_SIZE * i;
			CELL[0].x = left + MapScrollx;
			CELL[0].y = top + MapScrolly;
			CELL[1].x = (left + CELL_SIZE) + MapScrollx;
			CELL[1].y = top + MapScrolly;
			CELL[2].x = (left + CELL_SIZE) + MapScrollx;
			CELL[2].y = (top + CELL_SIZE) + MapScrolly;;
			CELL[3].x = left + MapScrollx;
			CELL[3].y = (top + CELL_SIZE) + MapScrolly;;

			m_MapSelected = MapData[j][i];
			switch (m_MapSelected)
			{
			case ROCK_BLOCK:
				CELL[0].tu = BLOCK_WIDTH * (m_MapSelected - 1);
				CELL[3].tu = BLOCK_WIDTH * (m_MapSelected - 1);
				CELL[1].tu = BLOCK_WIDTH * m_MapSelected;
				CELL[2].tu = BLOCK_WIDTH * m_MapSelected;
				break;
			case WOOD_BLOCK:
				CELL[0].tu = BLOCK_WIDTH * (m_MapSelected - 1);
				CELL[3].tu = BLOCK_WIDTH * (m_MapSelected - 1);
				CELL[1].tu = BLOCK_WIDTH * m_MapSelected;
				CELL[2].tu = BLOCK_WIDTH * m_MapSelected;
				break;
			}
			m_pScene->TextureRender("BLOCK_INTEGRATION_TEX", CELL);
		}
	}
}