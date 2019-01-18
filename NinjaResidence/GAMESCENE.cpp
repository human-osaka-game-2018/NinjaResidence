/**
* @file GAMESCENE.cpp
* @brief GAMESCENEクラス
* @author Kojiro Kawahara
*/
#include "GAMESCENE.h"
#include "Shuriken.h"
#include "HighShuriken.h"
#include "FireArt.h"
#include "ClawShot.h"

GameScene::GameScene(DirectX* pDirectX, SoundOperater* pSoundOperater) :Scene(pDirectX,pSoundOperater)
{
	m_pScene = this;
	StageTurning();
	m_pBusyMapChip = new MapChip(pDirectX, pSoundOperater);
	m_pIdleMapChip = new MapChip(pDirectX, pSoundOperater);
	m_pBusyMapChip->Create(StageFilePath_surface, SURFACE);
	m_pIdleMapChip->Create(StageFilePath_reverse,REVERSE);
	m_pGameChara = new GameChara(pDirectX, pSoundOperater, m_pBusyMapChip);
	m_pMapReverse = new MapReverse(pDirectX, pSoundOperater, m_pGameChara);


	m_pShuriken = new Shuriken(pDirectX, pSoundOperater, m_pBusyMapChip, m_pGameChara);
	m_pHighShuriken = new HighShuriken(pDirectX, pSoundOperater, m_pBusyMapChip, m_pGameChara);
	m_pFireArt = new FireArt(pDirectX, pSoundOperater, m_pBusyMapChip, m_pGameChara);
	m_pClawShot =new ClawShot(pDirectX, pSoundOperater, m_pBusyMapChip, m_pGameChara);

	m_SkillSelect = new SkillSelect(pDirectX, pSoundOperater, m_EnableSkill);
	m_pDescriptionBoard = new DescriptionBoard(pDirectX, pSoundOperater, m_pGameChara, m_pBusyMapChip);
	m_pPauseScene = new PauseScene(pDirectX, pSoundOperater);
	CreateSquareVertex(m_BackgroundVertex, DISPLAY_WIDTH, DISPLAY_HEIGHT);

}

GameScene::~GameScene()
{
	m_pSoundOperater->Stop(m_BGMSoundKey);

	delete m_pBusyMapChip;
	m_pBusyMapChip = NULL;
	delete m_pIdleMapChip;
	m_pIdleMapChip = NULL;
	delete m_pGameChara;
	m_pGameChara = NULL;
	delete m_pMapReverse;
	m_pMapReverse = NULL;

	delete m_pHighShuriken;
	m_pHighShuriken = NULL;
	delete m_pShuriken;
	m_pShuriken = NULL;
	delete m_pFireArt;
	m_pFireArt = NULL;
	delete m_pClawShot;
	m_pClawShot = NULL;

	delete m_SkillSelect;
	m_SkillSelect = NULL;
	delete m_pPauseScene;
	m_pPauseScene = NULL;
	delete m_pDescriptionBoard;
	m_pDescriptionBoard = NULL;

	m_pDirectX->ClearTexture();
	m_pDirectX->ClearFont();
}

SCENE_NUM  GameScene::Update()
{
	if (SoundLib::Playing != m_pSoundOperater->GetStatus(m_BGMSoundKey)) {
		bool buff = m_pSoundOperater->Start(m_BGMSoundKey, true);
	}

	if (m_isGameFailure) {
		GameFailureAnime();
		return GetNextScene();
	}
	if (m_isClear) {
		ClearAnime();
		return GetNextScene();
	}
	if (m_pPauseScene->GetSoundSetting()) {
		m_SoundSetting = true;
		m_pPauseScene->InactiveSoundSetting();
		return GetNextScene();
	}
	if (RunPause) {
		m_pPauseScene->Update();
		if (m_pPauseScene->GetExitScene()) {
			m_pPauseScene->InitExitScene();
			RunPause = false;
		}
		m_GameState = m_pPauseScene->GetGameState();
		return m_pPauseScene->GetNextScene();
	}
	CurrentSkill = m_SkillSelect->GetSkillNum();
	m_pXinputDevice->DeviceUpdate();

	NotPushedAnyButton();

	KeyOperation();

	m_isClear = m_pGameChara->Update();
	m_isGameFailure = m_pGameChara->GetGameFailure();
	m_pGameChara->prevSaveMapCharaPos();
	m_pBusyMapChip->Update();
	SkillsUpdate();
	return GetNextScene();
}

void GameScene::KeyOperation() {
	if (KeyPush == m_pDirectX->GetKeyStatus(DIK_W) || PadPush == m_pXinputDevice->GetButton(ButtonY))
	{
		m_pGameChara->KeyOperation(JUMP);
	}
	if (m_pDirectX->GetKeyStatus(DIK_A) || PadOn == m_pXinputDevice->GetAnalogLState(ANALOGLEFT))
	{
		m_pGameChara->KeyOperation(MOVE_LEFT);
	}
	if (m_pDirectX->GetKeyStatus(DIK_D) || PadOn == m_pXinputDevice->GetAnalogLState(ANALOGRIGHT))
	{
		m_pGameChara->KeyOperation(MOVE_RIGHT);
	}
	if (KeyPush == m_pDirectX->GetKeyStatus(DIK_E) || PadPush== m_pXinputDevice->GetButton(ButtonB))
	{
		SkillStart();
	}
	if (KeyOn == m_pDirectX->GetKeyStatus(DIK_E) || PadOn == m_pXinputDevice->GetButton(ButtonB)) {
		m_pGameChara->FireArtAnime();
	}
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_E) || PadRelease == m_pXinputDevice->GetButton(ButtonB)) {
		SkillEND();
	}
	if (m_pDirectX->GetKeyStatus(DIK_UP) || m_pXinputDevice->GetButton(ButtonUP))
	{
		SkillKeyOperation(UP);
	}
	if (m_pDirectX->GetKeyStatus(DIK_DOWN) || m_pXinputDevice->GetButton(ButtonDOWN)) {
		SkillKeyOperation(DOWN);
	}
	if (KeyPush == m_pDirectX->GetKeyStatus(DIK_LEFT) || PadPush == m_pXinputDevice->GetButton(ButtonLEFT))
	{
		if (m_CanChangeSkill) {
			m_SkillSelect->KeyOperation(LEFT);
		}
	}
	if (KeyPush == m_pDirectX->GetKeyStatus(DIK_RIGHT) || PadPush == m_pXinputDevice->GetButton(ButtonRIGHT))
	{
		if (m_CanChangeSkill) {
			m_SkillSelect->KeyOperation(RIGHT);
		}
	}
	if (KeyPush == m_pDirectX->GetKeyStatus(DIK_RETURN) || KeyPush == m_pDirectX->GetKeyStatus(DIK_NUMPADENTER) || PadPush == m_pXinputDevice->GetButton(ButtonA))
	{
		Reverse();
		//説明看板を読む
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
	if (KeyPush == m_pDirectX->GetKeyStatus(DIK_TAB) || PadPush == m_pXinputDevice->GetButton(ButtonStart))
	{
		TransePause();
	}
	if (m_pDirectX->GetKeyStatus(DIK_J) || m_pXinputDevice->GetAnalogRState(ANALOGRIGHT))
	{
		SkillKeyOperation(BIT_LEFT);
	}
	if (m_pDirectX->GetKeyStatus(DIK_L) || m_pXinputDevice->GetAnalogRState(ANALOGLEFT))
	{
		SkillKeyOperation(BIT_RIGHT);
	}
	if (m_pDirectX->GetKeyStatus(DIK_I) || m_pXinputDevice->GetAnalogRState(ANALOGUP))
	{
		SkillKeyOperation(BIT_UP);
	}
	if (m_pDirectX->GetKeyStatus(DIK_K) || m_pXinputDevice->GetAnalogRState(ANALOGDOWN))
	{
		SkillKeyOperation(BIT_DOWN);
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
	if (m_pDirectX->GetKeyStatus(DIK_PGUP) || m_pXinputDevice->GetButton(ButtonRB)) {

	}
	
	//音声のテスト用処理を呼ぶ
	//if (PadRelease == m_pXinputDevice->GetButton(ButtonA))
	//{
	//	m_pGameChara->DebugMove();
	//}

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
	if (m_pDirectX->GetKeyStatus(DIK_E)) {
		return;
	}
	if (m_pXinputDevice->GetButton(ButtonY))
	{
		return;
	}
	if (m_pXinputDevice->GetButton(ButtonB))
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
	if (RunPause) {
		m_pPauseScene->Render();
		return;
	}

	m_pDirectX->DrawTexture("GAME_BG_TEX", m_BackgroundVertex);
 	m_pBusyMapChip->Render();
	m_pGameChara->Render();
	SkillsRender();
	m_SkillSelect->Render();
	if (m_isClear) {
		CUSTOMVERTEX LogoVertex[4];
		CENTRAL_STATE m_Logo = { CENTRAL_X ,300,400,150 };
		CreateSquareVertex(LogoVertex, m_Logo);
		m_pDirectX->DrawTexture("CLEAR_TEX", LogoVertex);
	}
	if (m_isGameFailure) {
		CUSTOMVERTEX LogoVertex[4];
		CENTRAL_STATE m_Logo = { CENTRAL_X ,300,400,150 };
		CreateSquareVertex(LogoVertex, m_Logo);
		m_pDirectX->DrawTexture("FAILURE_TEX", LogoVertex);
	}
#ifdef _DEBUG
	RECT testName = { 0, 100, 1250, 720 };
	char TestName[ArrayLong];
	sprintf_s(TestName, ArrayLong, "STAGE_%d", m_StageNum);
	m_pDirectX->DrawWord(testName, TestName, "DEBUG_FONT", DT_RIGHT, 0xffffffff);
#endif
	if (m_pDescriptionBoard->DescriptionNumberdecision == m_pDescriptionBoard->Number1)
	{
		m_pDirectX->DrawTexture("KANBAN_TEX", m_pDescriptionBoard->DescriptionBoardSIZE);
	}
	if (m_pDescriptionBoard->DescriptionNumberdecision == m_pDescriptionBoard->Number2)
	{
		m_pDirectX->DrawTexture("KANBAN_TEX2", m_pDescriptionBoard->DescriptionBoardSIZE);
	}
}

void GameScene::LoadResouce()
{
	m_pDirectX->LoadTexture("texture/BG.jpg", "GAME_BG_TEX");
	m_pDirectX->LoadTexture("texture/Pause_BG.jpg", "PAUSE_BG_TEX");
	m_pDirectX->LoadTexture("texture/object_a.png", "BLOCK_INTEGRATION_A_TEX");
	m_pDirectX->LoadTexture("texture/Block_IntegrationB.png", "BLOCK_INTEGRATION_B_TEX");
	m_pDirectX->LoadTexture("texture/Chara_Integration.png", "CHARA_INTEGRATION_TEX");
	m_pDirectX->LoadTexture("texture/ninja.png", "CHARA_TEX");
	m_pDirectX->LoadTexture("texture/Arrow.png", "ARROW_TEX");
	m_pDirectX->LoadTexture("texture/Kanban.png", "KANBAN_TEX");
	m_pDirectX->LoadTexture("texture/Kanban2.png", "KANBAN_TEX2");
	m_pDirectX->LoadTexture("texture/Pause.png", "PAUSETITLE_TEX");
	m_pDirectX->LoadTexture("texture/PauseMenu.png", "PAUSEMENU_TEX");
	m_pDirectX->LoadTexture("texture/StageClear.png", "CLEAR_TEX");
	m_pDirectX->LoadTexture("texture/StageFailure.png", "FAILURE_TEX");
	m_pDirectX->SetFont(25, 10, "DEBUG_FONT");

	m_pSoundOperater->AddFile("Sound/nc62985.wav", "DECISION",SE);

}
void GameScene::TextureRender(std::string TextureKey, CUSTOMVERTEX* TextureSize)
{
	m_pDirectX->DrawTexture(TextureKey, TextureSize);
}
void GameScene::StageTurning()
{
	switch (m_StageNum) {
	case 0:
		StageFilePath_surface = "csv/TUTORIAL_A.csv";
		StageFilePath_reverse = "csv/TUTORIAL_B.csv";
		m_BGMSoundKey = "TUTORIAL";
		break;
	case 1:
		StageFilePath_surface = "csv/STAGE1_A.csv";
		StageFilePath_reverse = "csv/STAGE1_B.csv";
		m_BGMSoundKey = "STAGE_1";
		break;
	case 2:
		StageFilePath_surface = "csv/STAGE2_A.csv";
		StageFilePath_reverse = "csv/STAGE2_B.csv";
		m_BGMSoundKey = "STAGE_2";
		break;
	case 3:
		StageFilePath_surface = "csv/STAGE3_A.csv";
		StageFilePath_reverse = "csv/STAGE3_B.csv";
		m_BGMSoundKey = "STAGE_3";
		break;
	case 4:
		StageFilePath_surface = "csv/STAGE4_A.csv";
		StageFilePath_reverse = "csv/STAGE4_B.csv";
		m_BGMSoundKey = "STAGE_4";
		break;
	case 5:
		StageFilePath_surface = "csv/STAGE5_A.csv";
		StageFilePath_reverse = "csv/STAGE5_B.csv";
		m_BGMSoundKey = "STAGE_5";
		break;
	default:
		m_pSoundOperater->BGMSetVolume(0);
		break;
	}
}

void GameScene::Reverse()
{
	m_pMapReverse->GoMapReverse(&m_pBusyMapChip, &m_pIdleMapChip);
	m_pHighShuriken->Reverse(m_pBusyMapChip);
	m_pShuriken->Reverse(m_pBusyMapChip);
	m_pFireArt->Reverse(m_pBusyMapChip);
	m_pClawShot->Reverse(m_pBusyMapChip);
}

void GameScene::SkillsUpdate() {
	m_SkillSelect->Update();
	SkillErase();
	switch (CurrentSkill) {
	case SHURIKEN:
		m_pShuriken->Update();
		break;
	case CLAWSHOT:
		m_pClawShot->Update();
		break;
	case FIRE_ART:
		m_pFireArt->Update();
		break;
	case HIGH_SHURIKEN_ART:
		m_pHighShuriken->Update();
		break;
	}
}
void GameScene::SkillsRender() {
	m_SkillSelect->Render();
	switch (CurrentSkill) {
	case SHURIKEN:
		m_pShuriken->Render();
		break;
	case CLAWSHOT:
		m_pClawShot->Render();
		break;
	case FIRE_ART:
		m_pFireArt->Render();
		break;
	case HIGH_SHURIKEN_ART:
		m_pHighShuriken->Render();
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
		m_pClawShot->KeyOperation(THROW);
		m_CanChangeSkill = false;
		if (m_pClawShot->GetActive()) {
			m_CanChangeSkill = true;
			m_pGameChara->KeyOperation(THROW);
		}
		break;
	case FIRE_ART:
		m_pGameChara->KeyOperation(FIRE);
		m_pFireArt->KeyOperation(FIRE);
		m_CanChangeSkill = false;
		break;
	case HIGH_SHURIKEN_ART:
		m_pHighShuriken->KeyOperation(THROW);
		m_CanChangeSkill = false;
		if (m_pHighShuriken->GetActive()) {
			m_CanChangeSkill = true;
			m_pGameChara->KeyOperation(THROW);
		}
		break;
	}

}
void GameScene::SkillEND() {
	switch (CurrentSkill) {
	case SHURIKEN:
		break;
	case CLAWSHOT:
		break;
	case FIRE_ART:
		m_CanChangeSkill = true;
		m_pFireArt->KeyOperation(END_ART);
		break;
	case HIGH_SHURIKEN_ART:
		break;
	}

}
void GameScene::SkillErase() {
	switch (CurrentSkill) {
	case SHURIKEN:
		m_pFireArt->KeyOperation(END_ART);
		m_pHighShuriken->KeyOperation(END_ART);
		m_pClawShot->KeyOperation(END_ART);
		break;
	case CLAWSHOT:
		m_pHighShuriken->KeyOperation(END_ART);
		m_pShuriken->KeyOperation(END_ART);
		m_pFireArt->KeyOperation(END_ART);
		break;
	case FIRE_ART:
		m_pHighShuriken->KeyOperation(END_ART);
		m_pShuriken->KeyOperation(END_ART);
		m_pClawShot->KeyOperation(END_ART);
		break;
	case HIGH_SHURIKEN_ART:
		m_pFireArt->KeyOperation(END_ART);
		m_pShuriken->KeyOperation(END_ART);
		m_pClawShot->KeyOperation(END_ART);
		break;
	}

}

void GameScene::SkillKeyOperation(KeyDirection vec) {
	switch (CurrentSkill) {
	case SHURIKEN:
		m_pShuriken->KeyOperation(vec);
		break;
	case CLAWSHOT:
		m_pClawShot->KeyOperation(vec);
		break;
	case FIRE_ART:
		m_pFireArt->KeyOperation(vec);
		break;
	case HIGH_SHURIKEN_ART:
		m_pHighShuriken->KeyOperation(vec);
		break;
	}
}

void GameScene::GameFailureAnime()
{
	static int StandbyTime = 0;
	++StandbyTime;
	if (StandbyTime > 120) {
		SetNextScene(STAGESELECT_SCENE);
		StandbyTime = 0;
	}
}


void GameScene::ClearAnime()
{
	static int StandbyTime = 0;
	++StandbyTime;
	if (StandbyTime > 120) {
		SetNextScene(STAGESELECT_SCENE);
		StandbyTime = 0;
	}
}
