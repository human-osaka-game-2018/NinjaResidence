#include "SCENE.h"

Scene :: Scene(DirectX* pDirectX, SoundsManager* pSoundManager)
{
	m_pDirectX = pDirectX;
	m_pSoundManager = pSoundManager;

	Scene::ReadTexture();
}

Scene::~Scene()
{

}


void Scene::ReadTexture()
{

}
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
