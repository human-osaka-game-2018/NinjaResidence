#include "SCENE.h"

Scene :: Scene()
{
	Scene::ReadTexture();
}

Scene::~Scene()
{

}

void Scene::TextureRender(std::string TextureKey, CUSTOMVERTEX TextureSize[4])
{
	pDirectX->DrowSceneBegin();
	pDirectX->DrowTexture(TextureKey,TextureSize);
	pDirectX->DrowSceneEnd();
}

void Scene::ReadTexture()
{

}