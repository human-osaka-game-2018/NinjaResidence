/**
* @file MapChip.h
* @brief MapChipクラス
* @author Kojiro Kawahara
*/
#pragma once

#include "GAMESCENE.h"
#include "Object.h"
#include "BlockInf.h"
#include "MapBlock.h"

class BaseTarget;
class GameScene;

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

#define FIELD_LEFT 0
#define FIELD_TOP  0 
#define BLOCK_WIDTH  80.0f/512
#define BLOCK_HEIGHT 80.0f/512



class MapChip :public Object
{
public:

	static std::vector<BaseTarget* > pBaseTarget;
	static std::vector<BlockInf> GimmickVector;
	static std::vector<BlockInf> TargetVector;
	
	//static std::vector< std::vector<int> > MapData;
	MapChip(DirectX* pDirectX, SoundOperater* pSoundOperater);
	~MapChip();
	/**
	* @brief マップチップの生成
	* @param filename CSVファイルの相対パス
	*/
	void Activate();
	void Create(const char *filename, MapDataState MapState);
	void CheckVector();
	void Render(bool MapDataReverse);
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
	static int m_TargetCount;
	static int m_GimmickCount;
};
