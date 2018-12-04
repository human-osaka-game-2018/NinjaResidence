/**
* @file SCENE.cpp
* @brief SCENEƒNƒ‰ƒX
* @author Kojiro Kawahara
*/
#include "SCENE.h"

Scene :: Scene(DirectX* pDirectX, SoundsManager* pSoundManager):m_pDirectX(pDirectX), m_pSoundManager(pSoundManager)
{
	m_pDirectX = pDirectX;
	m_pXinputDevice = new XinputDevice;
	m_pSoundManager = pSoundManager;
	m_pDirectX->LoadTexture("texture/ninja_tool01_c_01.png", "CROSS_TEX");
	m_pDirectX->SetFont(75, 75, "LOAD_FONT");
}

Scene::~Scene()
{
	delete m_pXinputDevice;
	m_pXinputDevice = NULL;
}


//void Scene::LoadResouce()
//{
//
//}
void Scene::CreateSquareVertex(CUSTOMVERTEX* Vertex, CENTRAL_STATE Central, DWORD  color, float tu, float tv, float scaleTu, float scaleTv) {
	Vertex[0] = { Central.x - Central.scale_x, Central.y - Central.scale_y, 1.f, 1.f, color, tu, tv };
	Vertex[1] = { Central.x + Central.scale_x, Central.y - Central.scale_y, 1.f, 1.f, color, tu + scaleTu, tv };
	Vertex[2] = { Central.x + Central.scale_x, Central.y + Central.scale_y, 1.f, 1.f, color, tu + scaleTu, tv + scaleTv };
	Vertex[3] = { Central.x - Central.scale_x, Central.y + Central.scale_y, 1.f, 1.f, color, tu, tv + scaleTv };
}
void Scene::CreateSquareVertex(CUSTOMVERTEX* Vertex, float x,float y, DWORD  color, float tu, float tv, float scaleTu, float scaleTv) {
	Vertex[0] = { 0,  0, 1.f, 1.f, color, tu, tv };
	Vertex[1] = { x, 0, 1.f, 1.f, color, tu + scaleTu, tv };
	Vertex[2] = { x, y, 1.f, 1.f, color, tu + scaleTu, tv + scaleTv };
	Vertex[3] = { 0,  y, 1.f, 1.f, color, tu, tv + scaleTv };
}
void Scene::GoToOptionScene() {

}

void Scene::RunOptionScene(int BGMvolume,int SEvolume) {

	
}
void RevolveZ(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, DWORD  color = 0xffffffff, float tu = 0, float tv = 0, float scaleTu = 1, float scaleTv = 1);

void Scene::LoadAnimation() {

	static int rad = 0;
	++rad;
	CUSTOMVERTEX closs[4];
	CENTRAL_STATE CLOSS = { CENTRAL_X,CENTRAL_Y,300,300 };
	RevolveZ(closs, rad, CLOSS);
	m_pDirectX->DrawTexture("CROSS_TEX", closs);

}

void Scene::EndGame() {
	GameState = WM_NULL;
}

void RevolveZ(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, DWORD  color, float tu, float tv, float scaleTu, float scaleTv) {

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
