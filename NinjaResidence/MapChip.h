#pragma once

#include "SCENE.h"
#include "GAMESCENE.h"
#include "Object.h"

class GameScene;

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

#define FIELD_LEFT 0
#define FIELD_TOP  0 
#define BLOCK_WIDTH  40.0f/DISPLAY_WIDTH
#define BLOCK_HEIGHT 40.0f/DISPLAY_HEIGHT


class MapChip :public Object
{
private:
	enum BLOCKTYPE//CSVÇÃÉuÉçÉbÉNÇÃî‘çÜ
	{
		NONE,
		ROCK_BLOCK,
		WOOD_BLOCK,
		REVERSE_ZONE,
	};
	int m_MapSelected;
	int m_MapSelectedWIDTH;
	int m_MapSelectedHEIGHT;
	CUSTOMVERTEX CELL[4];
	void CellInit();
	//int MapScrollY;
	//int MapScrollX;
public:
	//static std::vector< std::vector<int> > MapData;
	MapChip(DirectX* pDirectX);
	~MapChip();
	void Create(const char *filename);
	void Render();
	void Update();
};
