#pragma once
//�p���֌W�Ŗʓ|�Ȃ��߉��u���A�����u��������΋����Ăق���
const float CELL_SIZE = 40.f;
const float BLOCK_INTEGRATION_WIDTH = 80.0f / 512.0f;

enum MapDataState
{
	SURFACE,//�\
	REVERSE,//��
};

struct BlockInfo
{
	int PositionX;//X���W
	int PositionY;//Y���W
	int PairNumber;//��2��
	int Type;//Target�Ȃ�1.2.3�AGimmick�Ȃ�4.5.6
	MapDataState MapDataState;
};
