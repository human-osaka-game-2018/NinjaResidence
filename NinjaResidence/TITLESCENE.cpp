﻿/**
* @file TITLESCENE.cpp
* @brief タイトルシーン
* @author Toshiya Matsuoka
*/
#include "SCENE.h"
#include "TITLESCENE.h"
#include "TitleCursol.h"

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

	CUSTOMVERTEX MenuVertex[4];
	CreateSquareVertex(MenuVertex, m_Menu);
	m_pDirectX->DrawTexture("MENU_TEX", MenuVertex);

}

void TitleScene::LoadResouce()
{
	m_pDirectX->LoadTexture("texture/Kunai.png", "CURSOL_TEX");
	m_pDirectX->LoadTexture("texture/TitleLogo.png", "LOGO_TEX");
	m_pDirectX->LoadTexture("texture/Titlemenu.png", "MENU_TEX");

	m_pDirectX->LoadTexture("texture/Title_BG.jpg", "BACKGROUND_TEX");

	m_pDirectX->SetFont(100, 50, "DEBUG_FONT");
	m_pDirectX->SetFont(75, 40, "MENU_FONT");

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

