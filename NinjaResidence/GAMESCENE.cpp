#include "GAMESCENE.h"

GameScene::GameScene(DirectX* pDirectX, int ChosedStage) :Scene(pDirectX)
{
	StageNum = ChosedStage;
	pScene = this;
	m_pMapChip = new MapChip(pScene);
	m_pGameChara = new GameChara(pScene);
	ReadTexture();
	pDirectX->SetFont(100, 50, "DEBUG_FONT");
	MapScrollx = 0;
	MapScrolly = 0;
	GameBackground[0] = { 0.f,			  0.f,			 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f };
	GameBackground[1] = { DISPLAY_WIDTH,  0.f,			 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f };
	GameBackground[2] = { DISPLAY_WIDTH,  DISPLAY_HEIGHT, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f };
	GameBackground[3] = {0.f,			  DISPLAY_HEIGHT, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f };
}

GameScene::~GameScene()
{
	delete m_pMapChip;
	m_pMapChip = NULL;
	delete m_pGameChara;
	m_pGameChara = NULL;
	pDirectX->ClearTexture();
	pDirectX->ClearFont();
}

SCENE_NUM  GameScene::Update()
{
		if (pDirectX->GetKeyStatus(DIK_UP))
		{
			m_pGameChara->abc = UP;
			m_pGameChara->GameCharaKeyOperation();
		}
		if (pDirectX->GetKeyStatus(DIK_DOWN))
		{
			m_pGameChara->abc = DOWN;
			m_pGameChara->GameCharaKeyOperation();
		}
		if (pDirectX->GetKeyStatus(DIK_LEFT))
		{
			m_pGameChara->abc = LEFT;
			m_pGameChara->GameCharaKeyOperation();
		}
		if (pDirectX->GetKeyStatus(DIK_RIGHT))
		{
			m_pGameChara->abc = RIGHT;
			m_pGameChara->GameCharaKeyOperation();
		}
	}
	m_pGameChara->GameCharaUpdate();
	return Getm_NextScene();
}

void GameScene::Render()
{
//private変数を元にキャラクターを描画
	pScene->TextureRender("BACKGROUND_TEX", GameBackground);
	m_pGameChara->GameCharaRender();
	m_pMapChip->MapChipRender();
	RECT testName = { 0, 100, 1280, 720 };
	char TestName[30];
	sprintf_s(TestName, 30, "STAGE_%d", StageNum);
	m_pDirectX->DrowWord(testName, TestName, "DEBUG_FONT", DT_LEFT, 0xffffffff);

	m_pDirectX->PresentsDevice();
}

void GameScene::ReadTexture()
{
	pDirectX->LoadTexture("texture/Block_Integration.png","BLOCK_INTEGRATION_TEX");
	pDirectX->LoadTexture("texture/BKG.jpg", "BACKGROUND_TEX");
	pDirectX->LoadTexture("texture/Chara_Integration.png", "CHARA_INTEGRATION_TEX");
}