/**
* @file GAMESCENE.cpp
* @brief GAMESCENE�N���X
* @author Kojiro Kawahara
*/
#include "GAMESCENE.h"
#include "Shuriken.h"


GameScene::GameScene(DirectX* pDirectX, SoundsManager* pSoundManager, int ChosedStage) :Scene(pDirectX,pSoundManager)
{

	m_StageNum = ChosedStage;
	m_pScene = this;

	m_pBusyMapChip = new MapChip(pDirectX, pSoundManager);
	m_pBusyMapChip->Create("csv/Book1.csv");
	m_pIdleMapChip = new MapChip(pDirectX, pSoundManager);
	m_pIdleMapChip->Create("csv/Book2.csv");
	m_pGameChara = new GameChara(pDirectX, pSoundManager, m_pBusyMapChip);
	m_pMapReverse = new MapReverse(pDirectX, pSoundManager, m_pGameChara);
<<<<<<< HEAD
	m_pShuriken = new Shuriken(pDirectX, pSoundManager, m_pBusyMapChip, m_pGameChara);
	m_SkillSelect=new SkillSelect(pDirectX, pSoundManager, m_EnableSkill);
	CreateSquareVertex(m_GameBackground, DISPLAY_WIDTH, DISPLAY_HEIGHT);
=======
	m_pDescriptionBoard = new DescriptionBoard(pDirectX, pSoundManager, m_pGameChara, m_pBusyMapChip);

	CreateSquareVertex(GameBackground, DISPLAY_WIDTH, DISPLAY_HEIGHT);
>>>>>>> 元の状態に戻しました
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
	delete m_SkillSelect;
	m_SkillSelect = NULL;
	m_pDirectX->ClearTexture();
	m_pDirectX->ClearFont();
}

SCENE_NUM  GameScene::Update()
{
	CurrentSkill = m_SkillSelect->GetSkillNum();
	m_pXinputDevice->DeviceUpdate();
	NotPushedAnyButton();
	KeyOperation();
	m_pGameChara->Update();
	m_pGameChara->prevSaveMapCharaPos();
	m_pBusyMapChip->Update();
	SkillsUpdate();
	return GetNextScene();
}

void GameScene::KeyOperation() {
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_W) || PadRelease == m_pXinputDevice->GetButton(ButtonY))
	{
		m_pGameChara->KeyOperation(JUMP);
	}
	if (m_pDirectX->GetKeyStatus(DIK_A) || m_pXinputDevice->GetAnalogL(ANALOGLEFT))
	{
		m_pGameChara->KeyOperation(MOVE_LEFT);
	}
	if (m_pDirectX->GetKeyStatus(DIK_D) || m_pXinputDevice->GetAnalogL(ANALOGRIGHT))
	{
		m_pGameChara->KeyOperation(MOVE_RIGHT);
	}
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_E) || PadRelease == m_pXinputDevice->GetButton(ButtonB))
	{
		SkillStart();
	}
	if (m_pDirectX->GetKeyStatus(DIK_UP) || m_pXinputDevice->GetButton(ButtonUP))
	{
		SkillKeyOperation(UP);
	}
<<<<<<< HEAD
	if (m_pDirectX->GetKeyStatus(DIK_DOWN) || m_pXinputDevice->GetButton(ButtonDOWN))
=======
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_RETURN))
	{
		//�����Ŕ�ǂ�
		if ((m_pDescriptionBoard->DescriptionNumberdecision == m_pDescriptionBoard->Number1) ||
			(m_pDescriptionBoard->DescriptionNumberdecision == m_pDescriptionBoard->Number2))
		{
			m_pDescriptionBoard->DescriptionNumberdecision = m_pDescriptionBoard->NONE;
		}
		else
		{
			m_pDescriptionBoard->GoDescriptionBoard(m_pBusyMapChip);
		}
	}

	if (m_pXinputDevice->GetButton(ButtonUP))
>>>>>>> 元の状態に戻しました
	{
		SkillKeyOperation(DOWN);
	}
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_LEFT) || PadRelease == m_pXinputDevice->GetButton(ButtonLEFT))
	{
		if (m_CanChangeSkill) {
			m_SkillSelect->KeyOperation(LEFT);
		}
	}
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_RIGHT) || PadRelease == m_pXinputDevice->GetButton(ButtonRIGHT))
	{
		if (m_CanChangeSkill) {
			m_SkillSelect->KeyOperation(RIGHT);
		}
	}
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_RETURN) || KeyRelease == m_pDirectX->GetKeyStatus(DIK_NUMPADENTER) || PadRelease == m_pXinputDevice->GetButton(ButtonA))
	{
		Reverse();
	}

<<<<<<< HEAD
	//�}�b�v����
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
	//�e�X�g�p����
	if (m_pDirectX->GetKeyStatus(DIK_PGUP) || m_pXinputDevice->GetButton(ButtonRB))
=======
	
	//�����̃e�X�g�p�������Ă�
	if (PadRelease == m_pXinputDevice->GetButton(ButtonA))
>>>>>>> 元の状態に戻しました
	{
		m_pGameChara->DebugMove();
	}
	if (m_pDirectX->GetKeyStatus(DIK_L) || PadRelease == m_pXinputDevice->GetButton(ButtonStart))
	{
		m_pGameChara->KeyOperation(SoundOn);
	}

}
void GameScene::NotPushedAnyButton() {
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
	m_pGameChara->NoOperation();
}

void GameScene::Render()
{
	m_pDirectX->DrawTexture("BACKGROUND_TEX", m_GameBackground);
	m_pBusyMapChip->Render();
	m_pGameChara->Render();
	m_pShuriken->Render();
	m_SkillSelect->Render();

#ifdef _DEBUG
	RECT testName = { 0, 100, 1250, 720 };
	char TestName[ArrayLong];
	sprintf_s(TestName, ArrayLong, "STAGE_%d", m_StageNum);
	m_pDirectX->DrawWord(testName, TestName, "DEBUG_FONT", DT_RIGHT, 0xffffffff);
	RECT test = { 400,0,800,500 };
	char TestText[ArrayLong];
<<<<<<< HEAD
	//sprintf_s(TestText, ArrayLong, "X-L:%d,X-R:%d,Y:%d", m_pGameChara->getMapCharaPositionX(), m_pGameChara->getMapCharaPositionY());
=======
	sprintf_s(TestText, ArrayLong, "X-L:%d,X-R:%d,Y:%d", m_pGameChara->getMapCharaPositionX(), m_pGameChara->getMapCharaPositionY());
	if (m_pDescriptionBoard->DescriptionNumberdecision == m_pDescriptionBoard->Number1)
	{
		m_pDirectX->DrawTexture("KANBAN_TEX", m_pDescriptionBoard->DescriptionBoardSIZE);
	}
	if (m_pDescriptionBoard->DescriptionNumberdecision == m_pDescriptionBoard->Number2)
	{
		m_pDirectX->DrawTexture("KANBAN_TEX2", m_pDescriptionBoard->DescriptionBoardSIZE);
	}
>>>>>>> 元の状態に戻しました
	//m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_LEFT, 0xffffffff);
#endif
}

void GameScene::LoadResouce()
{
	m_pDirectX->LoadTexture("texture/Block_Integration.png", "BLOCK_INTEGRATION_TEX");
	m_pDirectX->LoadTexture("texture/BKG.jpg", "BACKGROUND_TEX");
	m_pDirectX->LoadTexture("texture/Chara_Integration.png", "CHARA_INTEGRATION_TEX");
<<<<<<< HEAD
	m_pDirectX->LoadTexture("texture/nin_s.png", "CHARA_TEX");
	m_pDirectX->LoadTexture("texture/Arrow.png", "ARROW_TEX");
	m_pDirectX->LoadTexture("texture/Scroll.png", "SCROLL_TEX");
=======
	m_pDirectX->LoadTexture("texture/Kanban.png", "KANBAN_TEX");
	m_pDirectX->LoadTexture("texture/Kanban2.png", "KANBAN_TEX2");
>>>>>>> 元の状態に戻しました
	m_pDirectX->SetFont(25, 10, "DEBUG_FONT");

	m_pSoundManager->AddFile("Sound/nc62985.wav", "DECISION");

}
void GameScene::TextureRender(std::string TextureKey, CUSTOMVERTEX* TextureSize)
{
	m_pDirectX->DrawTexture(TextureKey, TextureSize);
}
void GameScene::Reverse()
{
	m_pMapReverse->GoMapReverse(&m_pBusyMapChip, &m_pIdleMapChip);
	m_pShuriken->Reverse();
}

void GameScene::SkillsUpdate() {
	m_SkillSelect->Update();
	switch (CurrentSkill) {
	case SHURIKEN:
		m_pShuriken->Update();
		break;
	case CLAWSHOT:
		break;
	case FIRE_ART:
		break;
	case HIGH_SHURIKEN_ART:
		break;
	}
}

void GameScene::SkillStart() {
	switch (CurrentSkill) {
	case SHURIKEN:
		m_pShuriken->KeyOperation(THROW);
		m_CanChangeSkill = false;
		if (m_pShuriken->GetActive()) {
			m_CanChangeSkill = true;
			m_pGameChara->KeyOperation(THROW);
		}
		break;
	case CLAWSHOT:
		break;
	case FIRE_ART:
		break;
	case HIGH_SHURIKEN_ART:
		break;
	}

}
void GameScene::SkillKeyOperation(KeyInput vec) {
	switch (CurrentSkill) {
	case SHURIKEN:
		m_pShuriken->KeyOperation(vec);
		break;
	case CLAWSHOT:
		break;
	case FIRE_ART:
		break;
	case HIGH_SHURIKEN_ART:
		break;
	}

}
