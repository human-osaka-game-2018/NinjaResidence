#include "BaseGimmick.h"


BaseGimmick::BaseGimmick(BlockInfo Gimmick, DirectX* pDirectX) :m_GimmickInfo(Gimmick)
{
	for (int i = 0; i < 4; ++i) {
		GimmickVertex[i].color = 0xFFFFFFFF;
	}
}

BaseGimmick::~BaseGimmick()
{

}

