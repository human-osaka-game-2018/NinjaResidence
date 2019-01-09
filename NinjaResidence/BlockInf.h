#pragma once

class MapChip;

enum MapDataState
{
	Surface,//表
	Reverse,//裏
};

struct BlockInf
{
	int m_x;//X座標
	int m_y;//Y座標
	int PairNumber;//下2桁
	int m_type;//Targetなら1.2.3、Gimmickなら4.5.6
	MapDataState MapDataState;
	MapChip* m_pMapChip;
};
