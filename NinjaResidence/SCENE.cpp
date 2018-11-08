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
	g_pD3Device->SetTexture(0, g_pTexture[TextureID]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, TextureSize, sizeof(CUSTOMVERTEX));
}

void Scene::ReadTexture()
{
	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/Block_Integration.png",
		&g_pTexture[BLOCK_INTEGRATION_TEX]);
	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/BKG.jpg",
		&g_pTexture[BACKGROUND_TEX]);
}