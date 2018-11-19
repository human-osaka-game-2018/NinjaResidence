#include "MapChip.h"

using std::vector;

//int MapChip::MapScrollX = 0;
//int MapChip::MapScrollY = 0;
//vector< vector<int> > MapChip::MapData;
//CUSTOMVERTEX MapChip::CELL[4];

//コンストラクタでマップチップの生成だけ行う
MapChip::MapChip(DirectX* pDirectX) :Object(pDirectX)
{
	CellInit();
	//CELL[0] = { 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0, 0.0f };
	//CELL[1] = { 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0, 0.0f };
	//CELL[2] = { 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0, BLOCK_HEIGHT };
	//CELL[3] = { 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0, BLOCK_HEIGHT };
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

void MapChip::Create(const char *filename)
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

void MapChip::Render()
{
	for (int j = 0; j < colunm;j++)
	{
		for (int i = 0;i < row;i++)
		{
			if (MapData[j][i] == 0)
			{
				continue;
			}
			int top = FIELD_TOP + (CELL_SIZE * j) + MapScrollY;
			int left = FIELD_LEFT + (CELL_SIZE * i )+ MapScrollX;
			CELL[0].x = left ;
			CELL[0].y = top ;
			CELL[1].x = (left + CELL_SIZE);
			CELL[1].y = top ;
			CELL[2].x = (left + CELL_SIZE);
			CELL[2].y = (top + CELL_SIZE);
			CELL[3].x = left;
			CELL[3].y = (top + CELL_SIZE);

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
			TextureRender("BLOCK_INTEGRATION_TEX", CELL);
		}
	}
	RECT test = { 0,0,800,500 };
	char TestText[30];
	sprintf_s(TestText, 30, "\n\n\nX:%d,Y:%d", MapScrollX, MapScrollY);
	m_pDirectX->DrowWord(test, TestText, "DEBUG_FONT", DT_LEFT, 0xffffffff);

}
void MapChip::Update() {

}

int MapChip::KeyOperation(KeyDirection vec) {

	switch (vec)
	{
	case UP:
		if (MapScrollY<0) {
			MapScrollY += 10;
		}
		break;
	case DOWN:
		if (MapScrollY > (-20 * colunm)) {
			MapScrollY -= 10;
		}
		break;
	case LEFT:
		//左に移動
		if (MapScrollX < 0) {
			MapScrollX += 10;
		}
		break;
	case RIGHT:
		//右に移動
		if (MapScrollX > (-CELL_SIZE/2 * row)) {
			MapScrollX -= 10;
		}
		break;
	}
	return 0;
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
