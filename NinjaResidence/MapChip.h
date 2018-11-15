#pragma once

#include <vector>
#include "SCENE.h"
#include "GAMESCENE.h"

class GameScene;
class Scene;

#define FIELD_LEFT 0
#define FIELD_TOP  0 
#define CELL_SIZE 40.f
#define BLOCK_WIDTH  40.0f/DISPLAY_WIDTH
#define BLOCK_HEIGHT 40.0f/DISPLAY_HIGHT


class MapChip
{
private:
	Scene * pScene;
	enum BLOCKTYPE//CSVのブロックの番号
	{
		NONE,
		ROCK_BLOCK,
		WOOD_BLOCK,
	};
	int row;
	int colunm;
	int m_MapSelected;
	int m_MapSelectedWIDTH;
	int m_MapSelectedHEIGHT;
public:
	static CUSTOMVERTEX CELL[4];
	static int m_MapScrollX;
	static int	m_MapScrollY;
	static std::vector< std::vector<int> > MapData;
	MapChip();
	~MapChip();
	void MapChipCreate(const char *filename);
	void MapChipRender();
};