/**
* @file TITLESCENE.cpp
* @brief タイトルシーン
* @author Toshiya Matsuoka
*/
#include "SCENE.h"
#include "TITLESCENE.h"
#include "TitleCursol.h"

using namespace Cursol;

TitleScene::TitleScene(DirectX* pDirectX, SoundOperater* pSoundOperater) :Scene(pDirectX,pSoundOperater)
{
	m_pScene = this;
	m_pCursol = new TitleCursol(m_pDirectX, m_pSoundOperater);

	CreateSquareVertex(m_BackgroundVertex, DISPLAY_WIDTH, DISPLAY_HEIGHT);
}

TitleScene::~TitleScene()
{
	delete m_pCursol;
	m_pDirectX->ClearTexture();
	m_pDirectX->ClearFont();
}

SCENE_NUM  TitleScene::Update()
{
	if (SoundLib::Playing != m_pSoundOperater->GetStatus("TITLE")) {
		bool buff = m_pSoundOperater->Start("TITLE", true);
	}
	m_pXinputDevice->DeviceUpdate();

	if (KeyPush == m_pDirectX->GetKeyStatus(DIK_UP))
	{
		m_pCursol->KeyOperation(UP);
	}
	if (KeyPush == m_pDirectX->GetKeyStatus(DIK_DOWN))
	{
		m_pCursol->KeyOperation(DOWN);
	}
	if (PadRelease == m_pXinputDevice->GetButton(ButtonUP))
	{
		m_pCursol->KeyOperation(UP);
	}
	if (PadRelease == m_pXinputDevice->GetButton(ButtonDOWN))
	{
		m_pCursol->KeyOperation(DOWN);
	}
	if (PadPush == m_pXinputDevice->GetAnalogLState(ANALOGUP))
	{
		m_pCursol->KeyOperation(UP);
	}
	if (PadPush == m_pXinputDevice->GetAnalogLState(ANALOGDOWN))
	{
		m_pCursol->KeyOperation(DOWN);
	}
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_RETURN) || KeyRelease == m_pDirectX->GetKeyStatus(DIK_NUMPADENTER)) {
		ChoseMenu();
	}
	if (PadRelease == m_pXinputDevice->GetButton(ButtonA)) {
		ChoseMenu();
	}
	m_pCursol->Update();
	return GetNextScene();
}

void TitleScene::Render()
{
	
	
	m_pDirectX->DrawTexture("BACKGROUND_TEX", m_BackgroundVertex);

	CUSTOMVERTEX LogoVertex[4];
	CreateSquareVertex(LogoVertex, m_Logo);
	m_pDirectX->DrawTexture("LOGO_TEX", LogoVertex);

	m_pCursol->Render();

	switch (m_pCursol->m_CursolPos)
	{
	case START:
		m_StartSize.scale_x = 130.f;
		m_StartSize.scale_y = 80.f;

		m_SettingSize.scale_x = 100.f;
		m_SettingSize.scale_y = 50.f;

		m_EndSize.scale_x = 100.f;
		m_EndSize.scale_y = 50.f;
		break;
	case OPTION:
		m_SettingSize.scale_x = 130.f;
		m_SettingSize.scale_y = 80.f;

		m_StartSize.scale_x = 100.f;
		m_StartSize.scale_y = 50.f;

		m_EndSize.scale_x = 100.f;
		m_EndSize.scale_y = 50.f;
		break;
	case END:
		m_EndSize.scale_x = 130.f;
		m_EndSize.scale_y = 80.f;

		m_StartSize.scale_x = 100.f;
		m_StartSize.scale_y = 50.f;

		m_SettingSize.scale_x = 100.f;
		m_SettingSize.scale_y = 50.f;
		break;
	}
	CUSTOMVERTEX StartVertex[4];
	CreateSquareVertex(StartVertex, m_StartSize);
	m_pDirectX->DrawTexture("TITLE_MENU_START_TEX", StartVertex);

	CUSTOMVERTEX SettingVertex[4];
	CreateSquareVertex(SettingVertex, m_SettingSize);
	m_pDirectX->DrawTexture("TITLE_MENU_SETTING_TEX", SettingVertex);

	CUSTOMVERTEX EndVertex[4];
	CreateSquareVertex(EndVertex, m_EndSize);
	m_pDirectX->DrawTexture("TITLE_MENU_END_TEX", EndVertex);
}

void TitleScene::LoadResouce()
{
	m_pDirectX->LoadTexture("texture/TitleLogo.png", "LOGO_TEX");
	m_pDirectX->LoadTexture("texture/Title_Start.png", "TITLE_MENU_START_TEX");
	m_pDirectX->LoadTexture("texture/Title_Setting.png", "TITLE_MENU_SETTING_TEX");
	m_pDirectX->LoadTexture("texture/Title_End.png", "TITLE_MENU_END_TEX");

	m_pDirectX->LoadTexture("texture/Title_BG.jpg", "BACKGROUND_TEX");

	m_pDirectX->SetFont(100, 50, "DEBUG_FONT");
	m_pDirectX->SetFont(100, 40, "MENU_FONT");

	m_pSoundOperater->AddFile("Sound/bgm/title_bgm.mp3", "TITLE", BGM);
	m_pSoundOperater->AddFile("Sound/bgm/tutorial_BGM.mp3", "TUTORIAL", BGM);
	m_pSoundOperater->AddFile("Sound/bgm/stage_bgm_1.mp3", "STAGE_1", BGM);
	m_pSoundOperater->AddFile("Sound/bgm/stage_bgm_2.mp3", "STAGE_2", BGM);
	m_pSoundOperater->AddFile("Sound/bgm/stage_bgm_3.mp3", "STAGE_3", BGM);
	m_pSoundOperater->AddFile("Sound/bgm/stage_bgm_4.mp3", "STAGE_4", BGM);
	m_pSoundOperater->AddFile("Sound/bgm/stage_bgm_5.mp3", "STAGE_5", BGM);

	m_pSoundOperater->AddFile("Sound/se/burning.mp3", "BURNING", SE);
	m_pSoundOperater->AddFile("Sound/se/dash.mp3", "DASH", SE);
	m_pSoundOperater->AddFile("Sound/se/door.mp3", "DOOR", SE);
	m_pSoundOperater->AddFile("Sound/se/drainage.mp3", "DRAINAGE", SE);
	m_pSoundOperater->AddFile("Sound/se/fire.mp3", "FIRE", SE);
	m_pSoundOperater->AddFile("Sound/se/itemget.mp3", "GET_ITEM", SE);
	m_pSoundOperater->AddFile("Sound/se/jump.wav", "JUMP", SE);
	m_pSoundOperater->AddFile("Sound/se/knifes.mp3", "SHURIKEN", SE);
	m_pSoundOperater->AddFile("Sound/se/landingon.mp3", "SET_DOWN", SE);
	m_pSoundOperater->AddFile("Sound/se/metal.mp3", "CLAWSHOT", SE);
	m_pSoundOperater->AddFile("Sound/se/reverse.mp3", "REVERSE", SE);
	m_pSoundOperater->AddFile("Sound/se/slash.mp3", "CUT_OFF", SE);
	m_pSoundOperater->AddFile("Sound/se/switch.mp3", "TARGET_ACTIVE", SE);
	m_pSoundOperater->AddFile("Sound/se/watershoes.mp3", "SET_DOWN_WATER", SE);
}

void TitleScene::ChoseMenu() {
	switch (m_pCursol->getCursolPosition()) {
	case Cursol::START:
		m_pSoundOperater->Stop("TITLE");
		SetNextScene(STAGESELECT_SCENE);
		break;
	case Cursol::OPTION:
		m_SoundSetting = true;
		break;
	case Cursol::END:
		EndGame();
		break;
	}
}
