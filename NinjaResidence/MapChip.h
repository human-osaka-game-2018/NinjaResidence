#pragma once

#include "SCENE.h"
#include "GAMESCENE.h"
#include "Object.h"

class GameScene;
class Scene;
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

#define FIELD_LEFT 0
#define FIELD_TOP  0 
#define CELL_SIZE 40.f
#define BLOCK_WIDTH  40.0f/DISPLAY_WIDTH
#define BLOCK_HEIGHT 40.0f/DISPLAY_HEIGHT


class MapChip :public Object
{
private:

	Scene * m_pScene;
	enum BLOCKTYPE//CSVÇÃÉuÉçÉbÉNÇÃî‘çÜ
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
	//static std::vector< std::vector<int> > MapData;
	MapChip(Scene * pScene);
	~MapChip();
	void Create(const char *filename);
	void Render();
	void Update();
	void KeyOperation(int vec);
};