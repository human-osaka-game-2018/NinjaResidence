/**
* @file MapChip.h
* @brief MapChipクラス
* @author Kojiro Kawahara
*/
#pragma once

#include "GAMESCENE.h"
#include "Object.h"
#include "BlockInf.h"

class BaseTarget;
class GameScene;

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

#define FIELD_LEFT 0
#define FIELD_TOP  0 
#define BLOCK_WIDTH  80.0f/512
#define BLOCK_HEIGHT 80.0f/512

namespace MapBlock
{
	enum BLOCKTYPE//CSVのブロックの番号
	{
		NONE,
		WOOD_BLOCK,
		ROCK_BLOCK,
		WOOD_TRACT,
		ROCK_TRACT,
		WOOD_REVERSE_ZONE,
		ROCK_REVERSE_ZONE,
		DESCRIPTION_BOARD,
		DESCRIPTION_BOARD2,
	};
};

class MapChip :public Object
{
public:

	std::vector<BaseTarget* > pBaseTarget;
	std::vector<BlockInf> GimmickVector;
	std::vector<BlockInf> TargetVector;
	
	//static std::vector< std::vector<int> > MapData;
	MapChip(DirectX* pDirectX, SoundOperater* pSoundOperater);
	~MapChip();
	/**
	* @brief マップチップの生成
	* @param filename CSVファイルの相対パス
	*/
	void Activate();
	void Create(const char *filename);
	void CheckVector();
	void Render();
	void Update();
	bool RestrictBottomScroll();
	float GetBottomPoint(int charaLeft, int charRight);
	float GetBottomWorldPoint(int charaLeft, int charRight);

private:
	int m_MapSelected;
	int m_MapSelectedWIDTH;
	int m_MapSelectedHEIGHT;
	CUSTOMVERTEX CELL[4];
	void CellInit();
	int TargetCount = 0;
	int GimmickCount = 0;
};
