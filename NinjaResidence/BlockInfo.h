#pragma once

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
