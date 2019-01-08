#pragma once
//継承関係で面倒なため仮置き、いい置き方あれば教えてほしい
const float CELL_SIZE = 40.f;
const float BLOCK_INTEGRATION_WIDTH = 80.0f / 512.0f;

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
