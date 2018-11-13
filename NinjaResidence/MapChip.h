#pragma once

#include "SCENE.h"
#include "GAMESCENE.h"
#include<vector>
class GameScene;
class Scene;
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

#define FIELD_LEFT 0
#define FIELD_TOP  0 
#define CELL_SIZE 40
#define BLOCK_WIDTH  40.0f/DISPLAY_WIDTH
#define BLOCK_HEIGHT 40.0f/DISPLAY_HEIGHT

using namespace std;


class MapChip
{
private:
	Scene * pScene;
	CUSTOMVERTEX CELL[4];
	enum BLOCKTYPE//CSVÇÃÉuÉçÉbÉNÇÃî‘çÜ
	{
		NONE,
		ROCK_BLOCK,
		WOOD_BLOCK,
	};
	int row;
	int colunm;
	vector< vector<int> > MapData;
	int m_MapSelected;
	int m_MapSelectedWIDTH;
	int m_MapSelectedHEIGHT;
public:
	static int MapScrollx;
	static int	MapScrolly;
	MapChip();
	~MapChip();
	void MapChipCreate(const char *filename);
	void MapChipRender();
};