/**
* @file MapChip.h
* @brief MapChipクラス
* @author Kojiro Kawahara
*/
#pragma once

#include "GAMESCENE.h"
#include "Object.h"
#include "BlockInfo.h"
#include "MapBlock.h"

class BaseTarget;
class GameScene;

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

#define FIELD_LEFT 0.f
#define FIELD_TOP  0.f



class MapChip :public Object
{
public:

	//static std::vector< std::vector<int> > MapData;
	MapChip(DirectX* pDirectX, SoundOperater* pSoundOperater);
	virtual ~MapChip();
	/**
	* @brief マップチップの生成
	* @param filename CSVファイルの相対パス
	* @param MapState 表か裏かの指定
	* @sa enum MapDataState
	*/
	void Create(const char *filename, MapDataState MapState);
	void Activate(int X, int Y);
	void MapDataVectorSet(int MapDataVectorSetY, int MapDataVectorSetX, int GimmickY, int GimmickX);
	void MapDataVectorSet0();
	void MapDataGimmickSearch();
	void MapDataVectorHitSet(int MapDataVectorSetY, int MapDataVectorSetX, int GimmickY, int GimmickX);
	void MapDataVectorZeroSet(int MapDataVectorSetY, int MapDataVectorSetX, int GimmickY, int GimmickX);
	int GimmickMapDataCheck(int y, int x);
	void CheckVector();
	void Render();
	bool Update();
	bool RestrictBottomScroll();
	float GetBottomPoint(int charaLeft, int charRight);
	float GetBottomWorldPoint(int charaLeft, int charRight);
	MapDataState GetMapDataState() {
		return m_MapDataState;
	}
	int SearchBlockX(MapBlock::BLOCKTYPE Block);
	int SearchBlockY(MapBlock::BLOCKTYPE Block);
	CUSTOMVERTEX* GetTargetPosition(int targetType);
	float GetGimmickPosition(bool isAxisX, int MapYPos,int MapXPos);
	bool GetGimmckActive(int MapXPos);

private:
	int m_MapSelected;
	int m_MapSelectedWIDTH;
	int m_MapSelectedHEIGHT;
	CUSTOMVERTEX CELL[4];
	void CellInit();
	static int m_TargetCount;
	static int m_GimmickCount;


	static std::vector<BaseTarget*> pBaseTarget;
	static std::vector<BlockInfo> GimmickVector;
	static std::vector<BlockInfo> TargetVector;

	MapDataState m_MapDataState;
};
