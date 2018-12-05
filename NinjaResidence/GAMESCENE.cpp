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
	CreateSquareVertex(GameBackground, DISPLAY_WIDTH, DISPLAY_HEIGHT);
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

		if (m_pXinputDevice->GetButton(ButtonUP))
		{
			m_pMapChip->setMapScrollY(m_pGameChara->KeyOperation(UP));
		}
		if (m_pXinputDevice->GetButton(ButtonDOWN))
		{
			m_pMapChip->setMapScrollY(m_pGameChara->KeyOperation(DOWN));
		}
		if (m_pXinputDevice->GetButton(ButtonLEFT))
		{
			m_pMapChip->setMapScrollX(m_pGameChara->KeyOperation(LEFT));
		}
		if (m_pXinputDevice->GetButton(ButtonRIGHT))
		{
			m_pMapChip->setMapScrollX(m_pGameChara->KeyOperation(RIGHT));
		}

	//�}�b�v����
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
		if (PadRelease == m_pXinputDevice->GetButton(ButtonA))
		{
			m_pGameChara->KeyOperation(SoundOn);
		}
		//�����̃e�X�g�p�������Ă�
		if (m_pDirectX->GetKeyStatus(DIK_L)) {
			m_pGameChara->KeyOperation(SoundOn);
		}
	m_pGameChara->Update();
	return GetNextScene();
}

void GameScene::Render()
{
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

void GameScene::LoadResouce()
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
