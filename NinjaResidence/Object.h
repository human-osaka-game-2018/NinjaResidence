#pragma once
#include <vector>

#include "SCENE.h"

enum koujirou
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

class Object
{
private:
	CENTRAL_STATE m_Central = { 400,10,(40 * 2),(40 * 4) };
	CUSTOMVERTEX m_DisplayCoordinate[4];
	CUSTOMVERTEX m_WorldCoordinate[4];
	int MapChara[5];

	int row;
	int colunm;

public:
	koujirou abc;

	virtual void KeyOperation();
	virtual void KeyOperation(int vec) {};
	virtual void KeyOperation(koujirou abc) {};

	virtual void Update();
	virtual bool RectToRectCollisionCheak(CUSTOMVERTEX* pObjA, CUSTOMVERTEX* pObjB);
	virtual void Render();
	Object();
	Object(Scene * pScene) {};
	Object(Scene * pScene, Object* MapChip) {};
	static std::vector< std::vector<int> > MapData;

	~Object();
	int MapScrollX=0;
	int MapScrollY=0;
	virtual void Create(const char *filename) {};

	struct MAPCharPosition {
		int X;
		int Y;
	};

	MAPCharPosition MapCharaPosition;
	int getMapCharaPositionX() {
		return MapCharaPosition.X;
	};
	int getMapCharaPositionY() {
		return MapCharaPosition.Y;
	};

};