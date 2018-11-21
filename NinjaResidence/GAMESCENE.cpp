#include "GAMESCENE.h"

GameScene::GameScene(DirectX* pDirectX, int ChosedStage) :Scene(pDirectX)
{
	m_pDirectX = pDirectX;
	StageNum = ChosedStage;
	pScene = this;
	m_pMapChip = new MapChip(pDirectX);
	m_pMapChip->Create("csv/Book1.csv");
	m_pGameChara = new GameChara(pDirectX, m_pMapChip);
	ReadTexture();
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
	m_pDirectX->ClearTexture();
	m_pDirectX->ClearFont();
}

SCENE_NUM  GameScene::Update()
{
		if (m_pDirectX->GetKeyStatus(DIK_UP))
		{
			m_pMapChip->setMapScrollY (m_pGameChara->KeyOperation(UP));
		}
		if (m_pDirectX->GetKeyStatus(DIK_DOWN))
		{
			m_pMapChip->setMapScrollY (m_pGameChara->KeyOperation(DOWN));
		}
		if (m_pDirectX->GetKeyStatus(DIK_LEFT))
		{
			m_pMapChip->setMapScrollX (m_pGameChara->KeyOperation(LEFT));
		}
		if (m_pDirectX->GetKeyStatus(DIK_RIGHT))
		{
			m_pMapChip->setMapScrollX (m_pGameChara->KeyOperation(RIGHT));
		}
		if (m_pDirectX->GetKeyStatus(DIK_W))
		{
			m_pMapChip->KeyOperation(UP);
		}
		if (m_pDirectX->GetKeyStatus(DIK_S))
		{
			m_pMapChip->KeyOperation(DOWN);
		}
		if (m_pDirectX->GetKeyStatus(DIK_A))
		{
			m_pMapChip->KeyOperation(LEFT);
		}
		if (m_pDirectX->GetKeyStatus(DIK_D))
		{
			m_pMapChip->KeyOperation(RIGHT);
		}

	m_pGameChara->Update();
	return Getm_NextScene();
}

void GameScene::Render()
{
//private変数を元にキャラクターを描画

	m_pDirectX->DrawSceneBegin();
	m_pDirectX->DrawTexture("BACKGROUND_TEX", GameBackground);

	m_pMapChip->Render();
	m_pGameChara->Render();
	RECT testName = { 0, 100, 1280, 720 };
	char TestName[30];
	sprintf_s(TestName, 30, "STAGE_%d", StageNum);
	m_pDirectX->DrawWord(testName, TestName, "DEBUG_FONT", DT_LEFT, 0xffffffff);
	RECT test = { 0,0,800,500 };
	char TestText[30];
	sprintf_s(TestText, 30, "X:%d,Y:%d", m_pGameChara->getMapCharaPositionX(), m_pGameChara->getMapCharaPositionY());
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_LEFT, 0xffffffff);
	
	m_pDirectX->DrawSceneEnd();
	m_pDirectX->PresentsDevice();
}

void GameScene::ReadTexture()
{
	m_pDirectX->LoadTexture("texture/Block_Integration.png","BLOCK_INTEGRATION_TEX");
	m_pDirectX->LoadTexture("texture/BKG.jpg", "BACKGROUND_TEX");
	m_pDirectX->LoadTexture("texture/Chara_Integration.png", "CHARA_INTEGRATION_TEX");

	m_pDirectX->SetFont(100, 50, "DEBUG_FONT");

}
void GameScene::TextureRender(std::string TextureKey, CUSTOMVERTEX* TextureSize)
{
	m_pDirectX->DrawTexture(TextureKey, TextureSize);
}
