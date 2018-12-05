/**
* @file MapChip.h
* @brief MapChip�N���X
* @author Kojiro Kawahara
*/
#pragma once

#include "SCENE.h"
#include "GAMESCENE.h"
#include "Object.h"

class GameScene;


#define FIELD_LEFT 0
#define FIELD_TOP  0 
#define BLOCK_WIDTH  80.0f/512
#define BLOCK_HEIGHT 80.0f/512

namespace MapBlock
{
	enum BLOCKTYPE//CSV�̃u���b�N�̔ԍ�
	{
		NONE,
		WOOD_BLOCK,
		ROCK_BLOCK,
		WOOD_TRACT,
		ROCK_TRACT,
		WOOD_REVERSE_ZONE,
		ROCK_REVERSE_ZONE,
	};
}

class MapChip :public Object
{
private:
	int m_MapSelected;
	int m_MapSelectedWIDTH;
	int m_MapSelectedHEIGHT;
	CUSTOMVERTEX CELL[4];
	void CellInit();
public:

	//static std::vector< std::vector<int> > MapData;
	MapChip(DirectX* pDirectX, SoundsManager* pSoundManager);
	~MapChip();
	/**
	* @brief �}�b�v�`�b�v�̐���
	* @param filename CSV�t�@�C���̑��΃p�X
	*/
	void Create(const char *filename);
	void Render();
	void Update();
};
