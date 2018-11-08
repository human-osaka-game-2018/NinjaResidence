#pragma once

#include "SCENE.h"
#include<vector>
class Scene;

#define FIELD_LEFT 0
#define FIELD_TOP  0 
#define CELL_SIZE 80
#define BLOCK_WIDTH  80.0f/DISPLAY_WIDTH
#define BLOCK_HEIGHT 80.0f/DISPLAY_HIGHT

using namespace std;

class MapChip
{
private:
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
	Scene*	pScene;
public:
	MapChip();
	~MapChip();
	void MapChipCreate(const char *filename);
	void MapChipRender();
};