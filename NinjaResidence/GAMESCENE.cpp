#include "GAMESCENE.h"

GameScene::GameScene()
{
	m_pMapChip = new MapChip;
	m_pGameChara = new GameChara;
	m_pMapChip->MapChipCreate("csv/Book1.csv");
	ReadTexture();
	MapScrollx = 0;
	MapScrolly = 0;
	GameBackground[0] = { 0.f,			  0.f,			 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f };
	GameBackground[1] = { DISPLAY_WIDTH,  0.f,			 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f };
	GameBackground[2] = { DISPLAY_WIDTH,  DISPLAY_HIGHT, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f };
	GameBackground[3] = {0.f,			  DISPLAY_HIGHT, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f };
}

GameScene::~GameScene()
{
	delete m_pMapChip;
	m_pMapChip = NULL;
	delete m_pGameChara;
	m_pGameChara = NULL;
}

SCENE_NUM  GameScene::Update()
{
		if (GetKeyStatus(DIK_UP))
		{
			m_pGameChara->abc = UP;
			m_pGameChara->GameCharaUpdate();

		}
		if (GetKeyStatus(DIK_DOWN))
		{
			m_pGameChara->abc = DOWN;
			m_pGameChara->GameCharaUpdate();

		}
		if (GetKeyStatus(DIK_LEFT))
		{
			m_pGameChara->abc = LEFT;
			m_pGameChara->GameCharaUpdate();
		}
		if (GetKeyStatus(DIK_RIGHT))
		{
			m_pGameChara->abc = RIGHT;
			m_pGameChara->GameCharaUpdate();
		}
	return Getm_NextScene();
}

void GameScene::Render()
{
//private変数を元にキャラクターを描画
	pScene->TextureRender("BACKGROUND_TEX", GameBackground);
	m_pGameChara->GameCharaRender();
	m_pMapChip->MapChipRender();
	PresentsDevice();
}

void GameScene::ReadTexture()
{
	LoadTexture("texture/Block_Integration.png","BLOCK_INTEGRATION_TEX");
	LoadTexture("texture/BKG.jpg", "BACKGROUND_TEX");
	LoadTexture("texture/Chara_Integration.png", "CHARA_INTEGRATION_TEX");
}