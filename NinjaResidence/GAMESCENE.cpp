#include "GAMESCENE.h"

GameScene::GameScene()
{
	pMapChip = new MapChip;
	GameBackground[0] = { 0.f,			  0.f,			 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f };
	GameBackground[1] = { DISPLAY_WIDTH,  0.f,			 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f };
	GameBackground[2] = { DISPLAY_WIDTH,  DISPLAY_HIGHT, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f };
	GameBackground[3] = {0.f,			  DISPLAY_HIGHT, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f };
	VertexPlayer[0] = { m_Player.x,						m_Player.y,						1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f };
	VertexPlayer[1] = { m_Player.x + m_Player.scale_x,	m_Player.y,						1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f };
	VertexPlayer[2] = { m_Player.x + m_Player.scale_x,	m_Player.y + m_Player.scale_y,  1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f };
	VertexPlayer[3] = { m_Player.x,						m_Player.y + m_Player.scale_y,  1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f };
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
	//pScene->TextureRender(GAME_PLAYER_TEX, VertexPlayer);
	pMapChip->MapChipRender();
}