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
	DrowSceneBegin();
	DrowTexture(TextureKey,TextureSize);
	DrowSceneEnd();
}

void Scene::ReadTexture()
{

}