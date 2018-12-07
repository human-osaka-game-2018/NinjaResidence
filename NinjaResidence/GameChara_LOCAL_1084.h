#pragma once

#include <vector>
#include "GAMESCENE.h"
#include "Object.h"


class GameScene;
class MapChip;
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)


class GameChara :public Object
{
private:
	CENTRAL_STATE m_Player = { 400,10,(CELL_SIZE * 2),(CELL_SIZE * 4) };
	CUSTOMVERTEX m_DisplayCharaCoordinate[4];
	CUSTOMVERTEX m_WorldCharaCoordinate[4];

	float CharTu = 80 / 512.f;
	float CharTv = 160 / 512.f;

	Object* m_pMapChip = NULL;
public:
	int KeyOperation(KeyDirection vec);
	void Update();
	bool RectToRectCollisionCheak(CUSTOMVERTEX* pObjA, CUSTOMVERTEX* pObjB);
	void Render();
	GameChara(DirectX* pDirectX, Object* MapChip);
	~GameChara();
};