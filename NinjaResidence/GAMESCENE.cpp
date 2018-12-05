#include "GAMESCENE.h"

GameScene::GameScene(DirectX* pDirectX, SoundsManager* pSoundManager, int ChosedStage) :Scene(pDirectX,pSoundManager)
{

	StageNum = ChosedStage;
	pScene = this;

	m_pBusyMapChip = new MapChip(pDirectX, pSoundManager);
	m_pBusyMapChip->Create("csv/Book1.csv");
	m_pIdleMapChip = new MapChip(pDirectX, pSoundManager);
	m_pIdleMapChip->Create("csv/Book2.csv");
	m_pGameChara = new GameChara(pDirectX, pSoundManager, m_pBusyMapChip);
	m_pMapReverse = new MapReverse(pDirectX, pSoundManager, m_pGameChara);
	
	ReadTexture();
	GameBackground[0] = { 0.f,			  0.f,			 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f };
	GameBackground[1] = { DISPLAY_WIDTH,  0.f,			 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f };
	GameBackground[2] = { DISPLAY_WIDTH,  DISPLAY_HEIGHT, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f };
	GameBackground[3] = { 0.f,			  DISPLAY_HEIGHT, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f };
}

GameScene::~GameScene()
{
	delete m_pBusyMapChip;
	m_pBusyMapChip = NULL;
	delete m_pIdleMapChip;
	m_pIdleMapChip = NULL;
	delete m_pGameChara;
	m_pGameChara = NULL;
	m_pDirectX->ClearTexture();
	m_pDirectX->ClearFont();
}

SCENE_NUM  GameScene::Update()
{
	m_pGameChara->prevSaveMapCharaPos();
	if (m_pDirectX->GetKeyStatus(DIK_UP))
	{
		m_pGameChara->KeyOperation(UP);
	}
	if (m_pDirectX->GetKeyStatus(DIK_DOWN))
	{
		m_pGameChara->KeyOperation(DOWN);
	}
	if (m_pDirectX->GetKeyStatus(DIK_LEFT))
	{
		m_pGameChara->KeyOperation(LEFT);
	}
	if (m_pDirectX->GetKeyStatus(DIK_RIGHT))
	{
		m_pGameChara->KeyOperation(RIGHT);
	}
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_SPACE))
	{
		m_pMapReverse->GoMapReverse(&m_pBusyMapChip, &m_pIdleMapChip);
	}
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_L))
	{
		m_pGameChara->KeyOperation(SoundOn);
	}

	m_pGameChara->Update();
	return GetNextScene();
}

void GameScene::Render()
{
	m_pDirectX->DrawSceneBegin();
	m_pDirectX->DrawTexture("BACKGROUND_TEX", GameBackground);

	m_pBusyMapChip->Render();
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
	m_pDirectX->LoadTexture("texture/Block_Integration.png", "BLOCK_INTEGRATION_TEX");
	m_pDirectX->LoadTexture("texture/BKG.jpg", "BACKGROUND_TEX");
	m_pDirectX->LoadTexture("texture/Chara_Integration.png", "CHARA_INTEGRATION_TEX");

	m_pDirectX->SetFont(100, 50, "DEBUG_FONT");

	m_pSoundManager->AddFile("Sound/nc62985.wav", "DECISION");

}
void GameScene::TextureRender(std::string TextureKey, CUSTOMVERTEX* TextureSize)
{
	m_pDirectX->DrawTexture(TextureKey, TextureSize);
}
