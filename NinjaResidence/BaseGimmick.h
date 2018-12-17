#pragma once

#include "BlockInf.h"
#include "DirectX.h"
#include <string> 

class BaseGimmick
{
protected:
	DirectX * m_pDirectX = NULL;
public:
	BlockInf GimmickInfo;
	virtual void Activate() = 0;
	virtual void Render(int MapScrollY, int MapScrollX, float CELL_SIZE, std::string TextureKey, CUSTOMVERTEX* TextureSize) = 0;
	BaseGimmick(BlockInf Gimmick, DirectX* pDirectX);
	~BaseGimmick();
};
