#include "GAMESCENE.h"

GameScene::GameScene()
{
	pMapChip = new MapChip;
	GameBackground[0]={ 0.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f };
	GameBackground[1] = { 1280.f, 0.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f };
	GameBackground[2] = { 1280.f, 720.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f };
	GameBackground[3] = { 0.f, 720.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f };
}

GameScene::~GameScene()
{
	delete pMapChip;
}

SCENE_NUM  GameScene::Update()
{
	//ゲームシーンでの操作できる
	pMapChip->MapChipCreate("csv/Book1.csv");

	return Getm_NextScene();
}

void GameScene::Render()
{
//private変数を元にキャラクターを描画
	pScene->TextureRender(BACKGROUND_TEX, GameBackground);
	pMapChip->MapChipRender();
}