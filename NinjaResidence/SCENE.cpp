#include "SCENE.h"

Scene :: Scene()
{
	Scene::ReadTexture();
}

Scene::~Scene()
{

}

void Scene::TextureRender(TEXTURE_NUM TextureID, CUSTOMVERTEX TextureSize[4])
{
	g_pD3Device->BeginScene();
	g_pD3Device->SetTexture(0, g_pTexture[TextureID]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, TextureSize, sizeof(CUSTOMVERTEX));
	g_pD3Device->EndScene();
}

void Scene::ReadTexture()
{

}