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
	enum BLOCKTYPE//CSV�̃u���b�N�̔ԍ�
	{
		NONE,
		WOOD_BLOCK,//����
		ROCK_BLOCK,//�ǂ�ł�Ԃ�
		WOOD_TRACT,//�X�C�b�`
		ROCK_TRACT,//��
		WOOD_REVERSE_ZONE,//�d�؂��
		ROCK_REVERSE_ZONE,//��
				          //�ړ���
						 //�E�p��
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
