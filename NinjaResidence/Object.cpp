/**
* @file Object.cpp
* @brief 色々な物体の基底クラス
* @author Toshiya Matsuoka
*/
#include "Object.h"



Object::Object(DirectX* pDirectX, SoundOperater* pSoundOperater):m_pDirectX(pDirectX), m_pSoundManager(pSoundOperater)
{
}



Object::~Object()
{
}



void Object::KeyOperation()
{
}


void Object::Update()
{
}




void Object::TextureRender(std::string TextureKey, CUSTOMVERTEX* TextureSize)
{
	m_pDirectX->DrawTexture(TextureKey, TextureSize);
}


void Object::Render()
{
}


void Object::CreateSquareVertex(CUSTOMVERTEX* Vertex, CENTRAL_STATE Central, DWORD  color, float tu, float tv, float scaleTu, float scaleTv) {
	Vertex[0] = { Central.x - Central.scale_x, Central.y - Central.scale_y, 1.f, 1.f, color, tu, tv };
	Vertex[1] = { Central.x + Central.scale_x, Central.y - Central.scale_y, 1.f, 1.f, color, tu + scaleTu, tv };
	Vertex[2] = { Central.x + Central.scale_x, Central.y + Central.scale_y, 1.f, 1.f, color, tu + scaleTu, tv + scaleTv };
	Vertex[3] = { Central.x - Central.scale_x, Central.y + Central.scale_y, 1.f, 1.f, color, tu, tv + scaleTv };
}
void Object::CreateSquareVertex(CUSTOMVERTEX* Vertex, float x, float y, DWORD  color, float tu, float tv, float scaleTu, float scaleTv) {
	Vertex[0] = { 0,  0, 1.f, 1.f, color, tu, tv };
	Vertex[1] = { x, 0, 1.f, 1.f, color, tu + scaleTu, tv };
	Vertex[2] = { x, y, 1.f, 1.f, color, tu + scaleTu, tv + scaleTv };
	Vertex[3] = { 0,  y, 1.f, 1.f, color, tu, tv + scaleTv };
}
void Object::CreateSquareVertex( CENTRAL_STATE Central,CUSTOMVERTEX* Vertex, DWORD  color, float tu, float tv, float scaleTu, float scaleTv) {
	Vertex[0] = { Central.x , Central.y , 1.f, 1.f, color, tu, tv };
	Vertex[1] = { Central.x + Central.scale_x, Central.y , 1.f, 1.f, color, tu + scaleTu, tv };
	Vertex[2] = { Central.x + Central.scale_x, Central.y + Central.scale_y, 1.f, 1.f, color, tu + scaleTu, tv + scaleTv };
	Vertex[3] = { Central.x , Central.y + Central.scale_y, 1.f, 1.f, color, tu, tv + scaleTv };
}

void Object::TranslateCentral_State(CENTRAL_STATE* Central, CUSTOMVERTEX* Vertex) {
	Central->x = Vertex[0].x;
	Central->y = Vertex[0].y;
	Central->scale_x = Vertex[1].x - Vertex[0].x;
	Central->scale_y = Vertex[3].y - Vertex[0].y;
}

void Object::RevolveZ(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, DWORD  color, float tu, float tv, float scaleTu, float scaleTv) {

	float CharVertexX[4];
	float CharVertexY[4];

	CharVertexX[0] = Central.x - Central.scale_x;
	CharVertexX[1] = Central.x + Central.scale_x;
	CharVertexX[2] = Central.x + Central.scale_x;
	CharVertexX[3] = Central.x - Central.scale_x;

	CharVertexY[0] = Central.y - Central.scale_y;
	CharVertexY[1] = Central.y - Central.scale_y;
	CharVertexY[2] = Central.y + Central.scale_y;
	CharVertexY[3] = Central.y + Central.scale_y;

	for (int RoteCnt = 0; RoteCnt < 4; RoteCnt++) {

		CharVertexX[RoteCnt] -= Central.x;
		CharVertexY[RoteCnt] -= Central.y;

		float KEEPER = CharVertexX[RoteCnt];

		CharVertexX[RoteCnt] = (CharVertexX[RoteCnt] * cos(-Rad)) - (CharVertexY[RoteCnt] * sin(-Rad));
		CharVertexY[RoteCnt] = (CharVertexY[RoteCnt] * cos(-Rad)) + (KEEPER * sin(-Rad));

		CharVertexX[RoteCnt] += Central.x;
		CharVertexY[RoteCnt] += Central.y;

	}

	Vertex[0] = { CharVertexX[0], CharVertexY[0], 1.f, 1.f, color, tu, tv };
	Vertex[1] = { CharVertexX[1], CharVertexY[1], 1.f, 1.f, color, tu + scaleTu, tv };
	Vertex[2] = { CharVertexX[2], CharVertexY[2], 1.f, 1.f, color, tu + scaleTu, tv + scaleTv };
	Vertex[3] = { CharVertexX[3], CharVertexY[3], 1.f, 1.f, color, tu, tv + scaleTv };

}

void Object::RevolveZEX(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, float RevolvingShaftX, float RevolvingShaftY, DWORD  color, float tu, float tv, float scaleTu, float scaleTv) {

	float CharVertexX[4];
	float CharVertexY[4];

	CharVertexX[0] = Central.x - Central.scale_x;
	CharVertexX[1] = Central.x + Central.scale_x;
	CharVertexX[2] = Central.x + Central.scale_x;
	CharVertexX[3] = Central.x - Central.scale_x;

	CharVertexY[0] = Central.y - Central.scale_y;
	CharVertexY[1] = Central.y - Central.scale_y;
	CharVertexY[2] = Central.y + Central.scale_y;
	CharVertexY[3] = Central.y + Central.scale_y;

	for (int RoteCnt = 0; RoteCnt < 4; RoteCnt++) {

		CharVertexX[RoteCnt] -= RevolvingShaftX;
		CharVertexY[RoteCnt] -= RevolvingShaftY;

		float KEEPER = CharVertexX[RoteCnt];

		CharVertexX[RoteCnt] = (CharVertexX[RoteCnt] * cos(-Rad)) - (CharVertexY[RoteCnt] * sin(-Rad));
		CharVertexY[RoteCnt] = (CharVertexY[RoteCnt] * cos(-Rad)) + (KEEPER * sin(-Rad));

		CharVertexX[RoteCnt] += RevolvingShaftX;
		CharVertexY[RoteCnt] += RevolvingShaftY;

	}

	Vertex[0] = { CharVertexX[0], CharVertexY[0], 1.f, 1.f, color, tu, tv };
	Vertex[1] = { CharVertexX[1], CharVertexY[1], 1.f, 1.f, color, tu + scaleTu, tv };
	Vertex[2] = { CharVertexX[2], CharVertexY[2], 1.f, 1.f, color, tu + scaleTu, tv + scaleTv };
	Vertex[3] = { CharVertexX[3], CharVertexY[3], 1.f, 1.f, color, tu, tv + scaleTv };

}

