/**
* @file GAMESCENE.cpp
* @brief GAMESCENEクラス
* @author Kojiro Kawahara
*/
#include "GAMESCENE.h"
#include "Shuriken.h"


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
	m_pShuriken = new Shuriken(pDirectX, pSoundManager, m_pBusyMapChip, m_pGameChara);
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
	delete m_pMapReverse;
	m_pMapReverse = NULL;
	delete m_pShuriken;
	m_pShuriken = NULL;
	m_pDirectX->ClearTexture();
	m_pDirectX->ClearFont();
}

SCENE_NUM  GameScene::Update()
{
	m_pXinputDevice->DeviceUpdate();
	CheckPushAnyButton();
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_W))
	{
		m_pGameChara->KeyOperation(JUMP);
	}
	//if (m_pDirectX->GetKeyStatus(DIK_S))
	//{
	//	m_pGameChara->KeyOperation(DOWN);
	//}
	if (m_pDirectX->GetKeyStatus(DIK_A))
	{
		m_pGameChara->KeyOperation(MOVE_LEFT);
	}
	if (m_pDirectX->GetKeyStatus(DIK_D))
	{
		m_pGameChara->KeyOperation(MOVE_RIGHT);
	}
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_E))
	{
		m_pShuriken->KeyOperation(THROW);
		if (m_pShuriken->GetActive()) {
			m_pGameChara->KeyOperation(THROW);
		}
	}
	if (m_pDirectX->GetKeyStatus(DIK_UP))
	{
		m_pShuriken->KeyOperation(UP);
	}
	if (m_pDirectX->GetKeyStatus(DIK_DOWN))
	{
		m_pShuriken->KeyOperation(DOWN);
	}

	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_RETURN) || KeyRelease == m_pDirectX->GetKeyStatus(DIK_NUMPADENTER))
	{
		Reverce();
	}

	if (PadRelease == m_pXinputDevice->GetButton(ButtonY))
	{
		m_pGameChara->KeyOperation(JUMP);
	}
	if (m_pXinputDevice->GetButton(ButtonDOWN))
	{
		m_pGameChara->KeyOperation(DOWN);
	}
	if (m_pXinputDevice->GetAnalogL(ANALOGLEFT))
	{
		m_pGameChara->KeyOperation(MOVE_LEFT);
	}
	if (m_pXinputDevice->GetAnalogL(ANALOGRIGHT))
	{
		m_pGameChara->KeyOperation(MOVE_RIGHT);
	}
	if (PadRelease == m_pXinputDevice->GetButton(ButtonA))
	{
		Reverce();
	}
	if (PadRelease == m_pXinputDevice->GetButton(ButtonB))
	{
		m_pShuriken->KeyOperation(THROW);
		if (m_pShuriken->GetActive()) {
			m_pGameChara->KeyOperation(THROW);
		}
	}
	if (m_pXinputDevice->GetButton(ButtonUP))
	{
		m_pShuriken->KeyOperation(UP);
	}
	if (m_pXinputDevice->GetButton(ButtonDOWN))
	{
		m_pShuriken->KeyOperation(DOWN);
	}

	//マップ動作
		//if (m_pDirectX->GetKeyStatus(DIK_W))
		//{
		//	m_pBusyMapChip->KeyOperation(UP);
		//}
		//if (m_pDirectX->GetKeyStatus(DIK_S))
		//{
		//	m_pBusyMapChip->KeyOperation(DOWN);
		//}
		//if (m_pDirectX->GetKeyStatus(DIK_A))
		//{
		//	m_pBusyMapChip->KeyOperation(LEFT);
		//}
		//if (m_pDirectX->GetKeyStatus(DIK_D))
		//{
		//	m_pBusyMapChip->KeyOperation(RIGHT);
		//}
	//テスト用処理
	if (m_pDirectX->GetKeyStatus(DIK_PGUP))
	{
		m_pGameChara->DebugMove();
	}
	if (m_pXinputDevice->GetButton(ButtonRB))
	{
		m_pGameChara->DebugMove();
	}
	if (PadRelease == m_pXinputDevice->GetButton(ButtonStart))
	{
		m_pGameChara->KeyOperation(SoundOn);
	}
	if (m_pDirectX->GetKeyStatus(DIK_L)) {
		m_pGameChara->KeyOperation(SoundOn);
	}
	m_pGameChara->Update();
	m_pGameChara->prevSaveMapCharaPos();
	m_pBusyMapChip->Update();
	m_pShuriken->Update();
	return GetNextScene();
}

void GameScene::CheckPushAnyButton() {
	if (m_pDirectX->GetKeyStatus(DIK_W)) {
		return;
	}
	if (m_pDirectX->GetKeyStatus(DIK_A)) {
		return;
	}
	if (m_pDirectX->GetKeyStatus(DIK_D)){
		return;
	}

	if (m_pXinputDevice->GetButton(ButtonY))
	{
		return;
	}
	if (m_pXinputDevice->GetAnalogL(ANALOGLEFT))
	{
		return;
	}
	if (m_pXinputDevice->GetAnalogL(ANALOGRIGHT))
	{
		return;
	}
	m_pGameChara->KeyOperation(PUSH_NONE);
}

void GameScene::Render()
{
	m_pDirectX->DrawTexture("BACKGROUND_TEX", GameBackground);
	m_pBusyMapChip->Render();
	m_pGameChara->Render();
	m_pShuriken->Render();
	RECT testName = { 0, 100, 1280, 720 };
	char TestName[ArrayLong];
	sprintf_s(TestName, ArrayLong, "STAGE_%d", StageNum);
	m_pDirectX->DrawWord(testName, TestName, "DEBUG_FONT", DT_LEFT, 0xffffffff);
	RECT test = { 0,0,800,500 };
	char TestText[ArrayLong];
	sprintf_s(TestText, ArrayLong, "X-L:%d,X-R:%d,Y:%d", m_pGameChara->getMapCharaPositionX(), m_pGameChara->getMapCharaPositionY());
	//m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_LEFT, 0xffffffff);

}

void GameScene::LoadResouce()
{
	m_pDirectX->LoadTexture("texture/Block_Integration.png", "BLOCK_INTEGRATION_TEX");
	m_pDirectX->LoadTexture("texture/BKG.jpg", "BACKGROUND_TEX");
	m_pDirectX->LoadTexture("texture/Chara_Integration.png", "CHARA_INTEGRATION_TEX");
	m_pDirectX->LoadTexture("texture/nin_s.png", "CHARA_TEX");
	m_pDirectX->LoadTexture("texture/Arrow.png", "ARROW_TEX");

	m_pDirectX->SetFont(25, 10, "DEBUG_FONT");

	m_pSoundManager->AddFile("Sound/nc62985.wav", "DECISION");

}
void GameScene::TextureRender(std::string TextureKey, CUSTOMVERTEX* TextureSize)
{
	m_pDirectX->DrawTexture(TextureKey, TextureSize);
}
void GameScene::Reverce()
{
	m_pMapReverse->GoMapReverse(&m_pBusyMapChip, &m_pIdleMapChip);
	m_pShuriken->Reverse();
}

