#include "SCENE.h"

Scene :: Scene(DirectX* pDirectX)
{
	m_pDirectX = pDirectX;
	Scene::ReadTexture();
}

Scene::~Scene()
{

}

void Scene::TextureRender(std::string TextureKey, CUSTOMVERTEX* TextureSize)
{
	m_pDirectX->DrowSceneBegin();
	m_pDirectX->DrowTexture(TextureKey, TextureSize);
	m_pDirectX->DrowSceneEnd();
}

void Scene::ReadTexture()
{

}