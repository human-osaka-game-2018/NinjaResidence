/**
* @file TITLESCENE.cpp
* @brief タイトルシーン
* @author Toshiya Matsuoka
*/
#include "SCENE.h"
#include "TITLESCENE.h"
#include "TitleCursol.h"

TitleScene::TitleScene(DirectX* pDirectX, SoundsManager* pSoundManager) :Scene(pDirectX,pSoundManager)
{
	m_pScene = this;
	m_pCursol = new TitleCursol(m_pDirectX, m_pSoundManager);

	CreateSquareVertex(m_TitleBackground, DISPLAY_WIDTH, DISPLAY_HEIGHT);
}

TitleScene::~TitleScene()
{
	delete m_pCursol;
	m_pDirectX->ClearTexture();
	m_pDirectX->ClearFont();
}

SCENE_NUM  TitleScene::Update()
{
	m_timecount++;
	m_pXinputDevice->DeviceUpdate();

	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_UP))
	{
		m_pCursol->KeyOperation(UP);
	}
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_DOWN))
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
	if (m_pXinputDevice->GetAnalogL(ANALOGUP))
	{
		m_pCursol->KeyOperation(UP);
	}
	if (m_pXinputDevice->GetAnalogL(ANALOGDOWN))
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
	
	
	m_pDirectX->DrawTexture("BACKGROUND_TEX", m_TitleBackground);
	RECT test = { 0,0,800,500 };
	char TestText[ArrayLong];
	sprintf_s(TestText, ArrayLong, "%d", m_timecount);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT",DT_LEFT,0xffffffff);
	RECT testName = { 0, 200, 1280, 500 };
	char TestName[ArrayLong] = "忍者屋敷";
	m_pDirectX->DrawWord(testName, TestName, "DEBUG_FONT", DT_CENTER, 0xffff0000);
	RECT pushEnter= { 0, 400, 1280, 700 };
	char PUSH_ENTER[ArrayLong] = "開始";
	m_pDirectX->DrawWord(pushEnter, PUSH_ENTER, "MENU_FONT", DT_CENTER, 0xffffffff);
	char SETTING[ArrayLong] = "\n設定";
	m_pDirectX->DrawWord(pushEnter, SETTING, "MENU_FONT", DT_CENTER, 0xffffffff);
	char END_GAME[ArrayLong] = "\n\n終了";
	m_pDirectX->DrawWord(pushEnter, END_GAME, "MENU_FONT", DT_CENTER, 0xffffffff);
	m_pCursol->Render();
}

void TitleScene::LoadResouce()
{
	m_pDirectX->LoadTexture("texture/Shuriken.png", "CURSOL_TEX");
	m_pDirectX->LoadTexture("texture/BKG.jpg", "BACKGROUND_TEX");
	m_pDirectX->SetFont(100, 50, "DEBUG_FONT");
	m_pDirectX->SetFont(75, 40, "MENU_FONT");

}
void TitleScene::ChoseMenu() {
	switch (m_pCursol->getCursolPosition()) {
	case Cursol::START:
		SetNextScene(STAGESELECT_SCENE);
		break;
	case Cursol::OPTION:
		
		break;
	case Cursol::END:
		EndGame();
		break;

	}
}

void TitleScene::EndGame() {
	m_GameState = WM_QUIT;
}
