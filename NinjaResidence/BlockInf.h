#pragma once

enum MapDataState
{
	SURFACE,//�\
	REVERSE,//��
};

struct BlockInf
{
	int m_x;//X���W
	int m_y;//Y���W
	int PairNumber;//��2��
	int m_type;//Target�Ȃ�1.2.3�AGimmick�Ȃ�4.5.6
	MapDataState MapDataState;
};
