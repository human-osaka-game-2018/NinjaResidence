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
	
	
	m_pDirectX->DrawTexture("BACKGROUND_TEX", m_TitleBackground);

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
