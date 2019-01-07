#pragma once

enum MapDataState
{
	SURFACE,//表
	REVERSE,//裏
};

struct BlockInfo
{
	int PositionX;//X座標
	int PositionY;//Y座標
	int PairNumber;//下2桁
	int Type;//Targetなら1.2.3、Gimmickなら4.5.6
	MapDataState MapDataState;
};
