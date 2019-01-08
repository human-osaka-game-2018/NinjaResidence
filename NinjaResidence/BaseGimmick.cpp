#include "BaseGimmick.h"


BaseGimmick::BaseGimmick(BlockInfo Gimmick, DirectX* pDirectX) :m_GimmickInfo(Gimmick)
{
	for (int i = 0; i < 4; ++i) {
		m_GimmickVertex[i].color = 0xFFFFFFFF;
		m_GimmickVertex[i].rhw = 1;
	}
}

BaseGimmick::~BaseGimmick()
{

}

