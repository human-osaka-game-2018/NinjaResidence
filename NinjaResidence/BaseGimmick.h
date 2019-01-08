#pragma once

#include "BlockInfo.h"
#include "DirectX.h"
#include <string> 

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)


class BaseGimmick
{
public:
	BlockInfo m_GimmickInfo;
	virtual void Activate() = 0;
	virtual void Render(int MapScrollY, int MapScrollX, bool MapDataReverse) = 0;
	BaseGimmick(BlockInfo Gimmick, DirectX* pDirectX);
	virtual ~BaseGimmick();
protected:
	DirectX* m_pDirectX = NULL;

	int m_GimmickPosX;
	int m_GimmickPosY;

	float WorldPosLeft;
	float WorldPosRight;
	float WorldPosTop;
	float WorldPosBottom;
	CUSTOMVERTEX GimmickVertex[4];

	bool m_isActive = false;

};
