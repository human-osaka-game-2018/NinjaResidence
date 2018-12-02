#pragma once

#include "SCENE.h"
#include "GAMESCENE.h"
#include "Object.h"

class GameScene;

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

#define FIELD_LEFT 0
#define FIELD_TOP  0 
#define BLOCK_WIDTH  80.0f/512
#define BLOCK_HEIGHT 80.0f/512

class MapChip :public Object
{
private:
	enum BLOCKTYPE//CSVのブロックの番号
	{
		NONE,
		WOOD_BLOCK,//足場
		ROCK_BLOCK,//どんでん返し
		WOOD_TRACT,//スイッチ
		ROCK_TRACT,//扉
		WOOD_REVERSE_ZONE,//仕切り板
		ROCK_REVERSE_ZONE,//槍
				          //移動床
						 //忍術書
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
