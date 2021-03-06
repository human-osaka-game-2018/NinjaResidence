﻿/**
* @file Target.h
* @brief Targetクラス
* @author Kojiro Kawahara
*/
#pragma once

#include "BaseTarget.h"
#include "Object.h"

class MapReverse;

class Target :public BaseTarget
{
public:
	void ActivateTarget();
	void Update();
	void Render(int MapScrollY, int MapScrollX, MapDataState MapDataReverse);
	Target(BlockInfo Target, BlockInfo Gimmick, DirectX* pDirectX, SoundOperater* pSoundOperater);
	virtual ~Target();
private:
	int m_MotionBias = 0;
};
