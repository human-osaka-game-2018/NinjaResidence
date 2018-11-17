#include "Object.h"



Object::Object()
{
}



Object::~Object()
{
}



void Object::KeyOperation()
{
}

int MapCharaPositionX2;

void Object::Update()
{
}



bool Object::RectToRectCollisionCheak(CUSTOMVERTEX* pObjA, CUSTOMVERTEX* pObjB)
{
	//ŽlŠpŒ`‚Ì“–‚½‚è”»’è
	if ((pObjA[0].x <= pObjB[0].x && pObjB[0].x <= pObjA[1].x) ||
		(pObjA[0].x <= pObjB[1].x && pObjB[1].x <= pObjA[1].x) ||
		(pObjB[0].x <= pObjA[0].x && pObjA[1].x <= pObjB[1].x))
	{
		if ((pObjA[0].y <= pObjB[0].y && pObjB[0].y <= pObjA[3].y) ||
			(pObjA[0].y <= pObjB[3].y && pObjB[3].y <= pObjA[3].y) ||
			(pObjB[0].y <= pObjA[0].y && pObjA[3].y <= pObjB[3].y))
		{
			return true;
		}
	}

	return false;
}



void Object::Render()
{
}