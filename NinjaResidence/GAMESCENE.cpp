#include "GAMESCENE.h"

GameScene::GameScene(DirectX* pDirectX, int ChosedStage) :Scene(pDirectX)
{
	m_pDirectX = pDirectX;
	StageNum = ChosedStage;
	pScene = this;
	m_pBusyMapChip = new MapChip(pDirectX);
	m_pBusyMapChip->Create("csv/Book1.csv");
	m_pIdleMapChip = new MapChip(pDirectX);
	m_pIdleMapChip->Create("csv/Book2.csv");
	m_pGameChara = new GameChara(pDirectX, m_pBusyMapChip);
	m_pMapReverse = new MapReverse(pDirectX, m_pGameChara);
	m_pDescriptionBoard = new DescriptionBoard(pDirectX,m_pGameChara, m_pBusyMapChip);
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
	if ((m_pDescriptionBoard->DescriptionNumberdecision == m_pDescriptionBoard->NONE) ||
		(m_pDescriptionBoard->DescriptionNumberdecision == m_pDescriptionBoard->NONE))
	{
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
	}
	//どんでん返しボタン
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_SPACE))
	{
		m_pMapReverse->GoMapReverse(&m_pBusyMapChip, &m_pIdleMapChip);
	}
	//ENTERキー入力で色々な操作
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_RETURN))
	{
		//説明看板を読み
		if ((m_pDescriptionBoard->DescriptionNumberdecision == m_pDescriptionBoard->Number1)||
			(m_pDescriptionBoard->DescriptionNumberdecision == m_pDescriptionBoard->Number2))
		{
			m_pDescriptionBoard->DescriptionNumberdecision = m_pDescriptionBoard->NONE;
		}
		else
		{
			m_pDescriptionBoard->GoDescriptionBoard(m_pBusyMapChip);
		}
	}
	m_pGameChara->Update();
	return GetNextScene();
}

void GameScene::Render()
{
	//private変数を元にキャラクターを描画

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
	if (m_pDescriptionBoard->DescriptionNumberdecision == m_pDescriptionBoard->Number1)
	{
		m_pDirectX->DrawTexture("KANBAN_TEX", m_pDescriptionBoard->DescriptionBoardSIZE);
	}
	if (m_pDescriptionBoard->DescriptionNumberdecision == m_pDescriptionBoard->Number2)
	{
 		m_pDirectX->DrawTexture("KANBAN_TEX2", m_pDescriptionBoard->DescriptionBoardSIZE);
	}

	m_pDirectX->DrawSceneEnd();
	m_pDirectX->PresentsDevice();
}

void GameScene::ReadTexture()
{
	m_pDirectX->LoadTexture("texture/Block_Integration.png", "BLOCK_INTEGRATION_A_TEX");
	m_pDirectX->LoadTexture("texture/Block_IntegrationB.png", "BLOCK_INTEGRATION_B_TEX");
	m_pDirectX->LoadTexture("texture/BKG.jpg", "BACKGROUND_TEX");
	m_pDirectX->LoadTexture("texture/Chara_Integration.png", "CHARA_INTEGRATION_TEX");
	m_pDirectX->LoadTexture("texture/Kanban.png","KANBAN_TEX");
	m_pDirectX->LoadTexture("texture/Kanban2.png", "KANBAN_TEX2");
	m_pDirectX->SetFont(100, 50, "DEBUG_FONT");

}
void GameScene::TextureRender(std::string TextureKey, CUSTOMVERTEX* TextureSize)
{
	m_pDirectX->DrawTexture(TextureKey, TextureSize);
}
