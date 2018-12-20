#pragma once

#include "GAMESCENE.h"
#include "MapChip.h"

class GameChara;
class MapChip;

class DescriptionBoard :public Object
{
private:
	GameChara * m_pGameChara = NULL;
	Object * m_pMapChip = NULL;
public:
	CUSTOMVERTEX DescriptionBoardSIZE[4];
	enum DescriptionNumber
	{
		NONE,
		Number1,
		Number2,
	};
	DescriptionNumber DescriptionNumberdecision;
	void GoDescriptionBoard(Object * m_pBusyMapChip);
	DescriptionBoard(DirectX* pDirectX,SoundsManager* pSoundManager, GameChara * GameChara, Object * m_pBusyMapChip);
	~DescriptionBoard();
};