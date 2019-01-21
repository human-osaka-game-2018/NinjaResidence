/**
* @file MapChip.cpp
* @brief MapChipクラス
* @author Kojiro Kawahara
*/
#include "MapChip.h"
#include "TargetandGimmickType.h"

using std::vector;
using namespace MapBlock;

int MapChip::m_TargetCount = 0;
int MapChip::m_GimmickCount = 0;
vector<BaseTarget*> MapChip::pBaseTarget;
vector<BlockInfo> MapChip::GimmickVector;
vector<BlockInfo> MapChip::TargetVector;

MapChip::MapChip(DirectX* pDirectX, SoundOperater* pSoundOperater) :Object(pDirectX,pSoundOperater)
{
	m_TargetCount = 0;
	m_GimmickCount = 0;
	CellInit();
}

MapChip::~MapChip()
{
	for (int i = 0; i < m_colunm; i++)
	{
		MapData[i].clear();
		vector<int>().swap(MapData[i]);
	}
	MapData.clear();
	vector<vector<int>>().swap(MapData);
	GimmickVector.clear();
	TargetVector.clear();
	for (int i = (pBaseTarget.size() - 1); i >= 0; --i)
	{
		delete pBaseTarget[i];
		pBaseTarget[i] = NULL;
	}
	pBaseTarget.clear();
}

void MapChip::Create(std::string filename, MapDataState MapState)
{
	m_MapDataState = MapState;
	int y = 0;

	std::ifstream ifs(filename);
	std::string str;

	getline(ifs, str);
	replace(str.begin(), str.end(), ',', ' ');
	std::stringstream MapSizeStream(str);
	MapSizeStream >> m_row >> m_colunm;


	MapData.resize(m_colunm);

	for (int j = 0; j<m_colunm; j++)
	{
		MapData[j].resize(m_row);
	}

	while (getline(ifs, str))
	{
		replace(str.begin(), str.end(), ',', ' ');
		std::stringstream MapNumsStream(str);
		for (int x = 0; x < static_cast<int>(MapData[y].size());++x) {
			MapNumsStream >> MapData[y][x];
			BlockInfo block;
			int blocktype = MapData[y][x] / 100;
			if (blocktype)
			{
				int PairNum = 0;
				if (blocktype < BT_PARTITIONBOARD)
				{
					PairNum = MapData[y][x] % 100;
					block = { x,y,PairNum,blocktype,MapState,this };
					TargetVector.push_back(block);
					m_TargetCount++;
				}
				else if (blocktype > BT_TORCH && blocktype < WOOD_REVERSE_ZONE)
				{
					PairNum = MapData[y][x] % 100;
					block = { x,y,PairNum,blocktype,MapState,this };
					GimmickVector.push_back(block);
					m_GimmickCount++;
				}
				else  if (blocktype == WOOD_REVERSE_ZONE)
				{
					PairNum = MapData[y][x] % 100;
					block = { x,y,PairNum,blocktype,MapState,this };
					ReversePointVector.push_back(block);
					m_ReverseCount++;
				}
				else if (blocktype == ROCK_REVERSE_ZONE)
				{
					PairNum = MapData[y][x] % 100;
					block = { x,y,PairNum,blocktype,MapState,this };
					ReversePointVector.push_back(block);
					m_ReverseCount++;
				}

			}
		}
		y++;


		if (y > static_cast<int>(MapData.size())) break;
	}

	if (MapState == REVERSE)
	{
		CheckVector();
		m_ReverseBuffer.resize(m_ReverseCount);
	}
}

void MapChip::MapDataVectorHitSet(int MapDataVectorSetY, int MapDataVectorSetX, int GimmickY, int GimmickX)
{
	for (int j = 0;j < GimmickY;j++)
	{
		for (int i = 0;i < GimmickX;i++)
		{
			MapData[MapDataVectorSetY + j][MapDataVectorSetX + i] = 900;
		}
	}
}

void MapChip::MapDataVectorZeroSet(int MapDataVectorSetY, int MapDataVectorSetX, int GimmickY, int GimmickX)
{
	for (int j = -1;j < GimmickY;j++)
	{
		for (int i = 0;i < GimmickX;i++)
		{
			MapData[MapDataVectorSetY + j][MapDataVectorSetX + i] = 0;
		}
	}
}

void MapChip::MapDataGimmickSearch()
{
	for (int i = 0; i < m_colunm; i++)
	{
		for (int j = 0;j < m_row; j++)
		{
			if (MapData[i][j] > 400 && MapData[i][j] < 500)
			{
				MapDataVectorSet(i, j,15,3);
			}
		}
	}
}

void MapChip::MapDataVectorSet(int MapDataVectorSetY,int MapDataVectorSetX,int GimmickY,int GimmickX)
{
	for (int i = 0;i < GimmickX;i++)
	{
		for (int j = 1;j < GimmickY;j++)
		{
			MapData[MapDataVectorSetY + j][MapDataVectorSetX + i] = 900;
		}
	}
}


void MapChip::CheckVector()
{
	BaseTarget* pBuf = NULL;

	for (int i = 0; i < m_TargetCount; i++)
	{
		for (int j = 0; j < m_GimmickCount; j++)
		{
			if (TargetVector[i].PairNumber % 100 != GimmickVector[j].PairNumber % 100) continue;
			switch (TargetVector[i].GimmickType)
			{
			case BT_TARGET://的
			pBuf = new Target(TargetVector[i], GimmickVector[j], m_pDirectX,m_pSoundOperater);
				break;
			case BT_ROPE://ロープ
			pBuf = new Rope(TargetVector[i], GimmickVector[j], m_pDirectX, m_pSoundOperater);
				break;
			case BT_SWITCH://スイッチ
			pBuf = new Switch(TargetVector[i], GimmickVector[j], m_pDirectX, m_pSoundOperater);
				break;
				case BT_TORCH://たいまつ
			pBuf = new Torch(TargetVector[i], GimmickVector[j], m_pDirectX, m_pSoundOperater);
				break;
			}
			pBaseTarget.push_back(pBuf);
		}
	}
	MapDataGimmickSearch();
}


void MapChip::Activate(int X, int Y)
{
	for (auto& ite : pBaseTarget)
	{

		if (X == ite->GetTargetInfo()->PositionX && Y == ite->GetTargetInfo()->PositionY)
		{
			ite->ActivateTarget();
		}
	}
}

int MapChip::GimmickMapDataCheck(int y, int x)
{ 
	if (MapData[y][x] == 0)
	{
		return 0;
	}

	if (MapData[y][x] > 300)
	{
		return 3;
	}
	return 1;
}

void MapChip::Render()
{
	for (int j = 0; j < m_colunm;j++)
	{
		for (int i = 0;i < m_row;i++)
		{
			if (MapData[j][i] == 0)
			{
				continue;
			}
			CellInit();
			float top = FIELD_TOP + (CELL_SIZE * j) + static_cast<float>(m_MapScrollY);
			float left = FIELD_LEFT + (CELL_SIZE * i) + static_cast<float>(m_MapScrollX);
			if (top<-CELL_SIZE || top>DISPLAY_HEIGHT) {
				continue;
			}
			if (left<-CELL_SIZE || left>DISPLAY_WIDTH) {
				continue;
			}

			CELL[0].x = left;
			CELL[0].y = top;
			CELL[1].x = (left + CELL_SIZE);
			CELL[1].y = top;
			CELL[2].x = (left + CELL_SIZE);
			CELL[2].y = (top + CELL_SIZE);
			CELL[3].x = left;
			CELL[3].y = (top + CELL_SIZE);

			m_MapSelected = MapData[j][i];
			if (m_MapSelected < 100)
			{
				switch (m_MapSelected)
				{
				case WOOD_BLOCK:
				case ROCK_BLOCK:
				case WOOD_TRACT:
				case ROCK_TRACT:
					CELL[0].tu = BLOCK_INTEGRATION_WIDTH * (m_MapSelected - 1.f);
					CELL[3].tu = BLOCK_INTEGRATION_WIDTH * (m_MapSelected - 1.f);
					CELL[1].tu = BLOCK_INTEGRATION_WIDTH * m_MapSelected;
					CELL[2].tu = BLOCK_INTEGRATION_WIDTH * m_MapSelected;
					CELL[0].tv = 0.f;
					CELL[1].tv = 0.f;
					CELL[2].tv = BLOCK_INTEGRATION_HEIGHT;
					CELL[3].tv = BLOCK_INTEGRATION_HEIGHT;
					break;
				case GOAL_ZONE:
					CELL[0].tu = BLOCK_INTEGRATION_WIDTH;
					CELL[3].tu = BLOCK_INTEGRATION_WIDTH;
					CELL[1].tu = BLOCK_INTEGRATION_WIDTH * 2.f;
					CELL[2].tu = BLOCK_INTEGRATION_WIDTH * 2.f;
					CELL[0].tv = BLOCK_INTEGRATION_HEIGHT * 3.f;
					CELL[1].tv = BLOCK_INTEGRATION_HEIGHT * 3.f;
					CELL[2].tv = BLOCK_INTEGRATION_HEIGHT * 4.f;
					CELL[3].tv = BLOCK_INTEGRATION_HEIGHT * 4.f;
					break;
				case SPEAR:
					CELL[0].tu = BLOCK_INTEGRATION_WIDTH * 2.f;
					CELL[3].tu = BLOCK_INTEGRATION_WIDTH * 2.f;
					CELL[1].tu = BLOCK_INTEGRATION_WIDTH * 3.f;
					CELL[2].tu = BLOCK_INTEGRATION_WIDTH * 3.f;
					CELL[0].tv = BLOCK_INTEGRATION_HEIGHT * 3.f;
					CELL[1].tv = BLOCK_INTEGRATION_HEIGHT * 3.f;
					CELL[2].tv = BLOCK_INTEGRATION_HEIGHT * 5.f;
					CELL[3].tv = BLOCK_INTEGRATION_HEIGHT * 5.f;
					break;
				case DESCRIPTION_BOARD:
				case DESCRIPTION_BOARD2:
					CELL[0].tu = 0.f;
					CELL[3].tu = 0.f;
					CELL[1].tu = 0.24f;
					CELL[2].tu = 0.24f;
					CELL[0].tv = BLOCK_INTEGRATION_HEIGHT;
					CELL[1].tv = BLOCK_INTEGRATION_HEIGHT;
					CELL[2].tv = BLOCK_INTEGRATION_HEIGHT * 2.f;
					CELL[3].tv = BLOCK_INTEGRATION_HEIGHT * 2.f;
					CELL[1].x += 120.f;
					CELL[2].x += 120.f;
					CELL[3].y += 80.f;
					CELL[2].y += 80.f;
					break;
				default:
					continue;
				}
			}
			else {
				switch (m_MapSelected/100)
				{
				case WOOD_REVERSE_ZONE:
					CELL[0].tu = BLOCK_INTEGRATION_WIDTH * 4.f;
					CELL[3].tu = BLOCK_INTEGRATION_WIDTH * 4.f;
					CELL[1].tu = BLOCK_INTEGRATION_WIDTH * 5.f;
					CELL[2].tu = BLOCK_INTEGRATION_WIDTH * 5.f;
					CELL[0].tv = 0.f;
					CELL[1].tv = 0.f;
					CELL[2].tv = BLOCK_INTEGRATION_HEIGHT;
					CELL[3].tv = BLOCK_INTEGRATION_HEIGHT;
					break;
				case ROCK_REVERSE_ZONE:
					CELL[0].tu = BLOCK_INTEGRATION_WIDTH * 5.f;
					CELL[3].tu = BLOCK_INTEGRATION_WIDTH * 5.f;
					CELL[1].tu = BLOCK_INTEGRATION_WIDTH * 6.f;
					CELL[2].tu = BLOCK_INTEGRATION_WIDTH * 6.f;
					CELL[0].tv = 0.f;
					CELL[1].tv = 0.f;
					CELL[2].tv = BLOCK_INTEGRATION_HEIGHT;
					CELL[3].tv = BLOCK_INTEGRATION_HEIGHT;
					break;
				default:
					continue;
				}
			}
			TextureRender("BLOCK_INTEGRATION_A_TEX", CELL);
		}
	}
	for (BaseTarget* pi : pBaseTarget)
	{
		pi->Render(m_MapScrollY, m_MapScrollX, m_MapDataState);
	}
	
#ifdef _DEBUG

	RECT test = { 0,500,1250,700 };
	char TestText[ArrayLong];
	sprintf_s(TestText, ArrayLong, "MapScroll::X:%d,Y:%d", m_MapScrollX, m_MapScrollY);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_RIGHT, 0xffffffff);
#endif
}

bool MapChip::Update() {
	if (m_MapScrollY > 0) {
		m_MapScrollY = 0;
	}
	for (auto ite : pBaseTarget)
	{
		ite->Update();
	}
	return true;
}

bool MapChip::RestrictBottomScroll() {
	float MapBottom = FIELD_TOP + (CELL_SIZE * (m_colunm + 1) )+ m_MapScrollY;
	if (MapBottom < DISPLAY_HEIGHT-20) {
		return true;
	}
	return false;
}

float MapChip::GetBottomPoint(int charaLeft, int charRight)
{
	float MapPosition = 0;
	for (int i = m_colunm - 1; i > 0; --i) {
		if (!MapData[i][charaLeft]) {
			return MapPosition = FIELD_TOP + (CELL_SIZE * (i - 4)) + m_MapScrollY;
		}
		if (!MapData[i][charRight]) {
			return MapPosition = FIELD_TOP + (CELL_SIZE * (i - 4)) + m_MapScrollY;
		}
	}
	return  0;
}
float MapChip::GetBottomWorldPoint(int charaLeft, int charRight)
{
	float MapPosition = 0;
	for (int i = m_colunm - 1; i > 0; --i) {
		if (!MapData[i][charaLeft]) {
			return MapPosition = FIELD_TOP + (CELL_SIZE * (i - 1));
		}
		if (!MapData[i][charRight]) {
			return MapPosition = FIELD_TOP + (CELL_SIZE * (i - 1));
		}
	}
	return  0;
}

void MapChip::CellInit() {
	for (int i = 0; i < 4; i++) {
		CELL[i].z = 1.0f;
		CELL[i].rhw = 1.0f;
		CELL[i].color = 0xFFFFFFFF;
	}
	CELL[0].tv = 0.f;
	CELL[1].tv = 0.f;
	CELL[2].tv = BLOCK_INTEGRATION_WIDTH;
	CELL[3].tv = BLOCK_INTEGRATION_WIDTH;

}

int MapChip::SearchBlockX(BLOCKTYPE Block) {
	for (int j = 0; j < m_colunm; j++)
	{
		for (int i = 0; i < m_row; i++)
		{
			if (MapData[j][i] == Block)
			{
				return i;
			}
		}
	}
	return 2;
}

int MapChip::SearchBlockY(BLOCKTYPE Block) {
	for (int j = 0; j < m_colunm; j++)
	{
		for (int i = 0; i < m_row; i++)
		{
			if (MapData[j][i] == Block)
			{
				return j;
			}
		}
	}
	return 5;
}

CUSTOMVERTEX* MapChip::GetTargetPosition(int targetType)
{
	CUSTOMVERTEX* Buf = NULL;
	for (auto ite : pBaseTarget)
	{
		BlockInfo* InfoBuf = ite->GetTargetInfo();
		if (InfoBuf->GimmickType!= targetType) {
			continue;
		}
		Buf = ite->GetTargetPosition();
	}
	return Buf;
}

float MapChip::GetGimmickPosition(bool isAxisX, int MapYPos, int MapXPos)
{
	float Buf = 0;
	for (auto ite : pBaseTarget)
	{
		if (!ite->GetGimmickActive(MapXPos)) {
			continue;
		}
		Buf = ite->GetGimmickPosition(isAxisX, m_MapDataState);
		if (Buf != 0) break;
	}
	return Buf;
}

bool MapChip::GetGimmckActive(int MapXPos)
{
	for (auto ite : pBaseTarget)
	{
		return ite->GetGimmickActive(MapXPos);
	}
	return false;
};
