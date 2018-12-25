#include "PauseScene.h"



PauseScene::PauseScene(DirectX* pDirectX, SoundOperater* pSoundOperater):Scene(pDirectX, pSoundOperater)
{

}


PauseScene::~PauseScene()
{
}

SCENE_NUM PauseScene::Update() {
	CursorMove();
	//if (SoundLib::Playing != m_pSoundOperater->GetStatus("TEST")) {
	//	bool buff = m_pSoundOperater->Start("TEST", true);
	//}
	//static int CursorAnimeInterval = 0;
	//++CursorAnimeInterval;
	//static bool CursorColorOn = false;
	//if (CursorAnimeInterval > 20) {
	//	if (CursorColorOn) {
	//		m_CursorColor += 0xFF << 24;
	//	}
	//	else m_CursorColor -= 0xFF << 24;
	//	CursorColorOn = !CursorColorOn;
	//	CursorAnimeInterval = 0;
	//}
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_RETURN) || KeyRelease == m_pDirectX->GetKeyStatus(DIK_NUMPADENTER) || PadRelease == m_pXinputDevice->GetButton(ButtonA))
	{
		TransrateScene();
	}
	//if (KeyOn == m_pDirectX->GetKeyStatus(DIK_LEFT) || PadOn == m_pXinputDevice->GetButton(ButtonLEFT))
	//{
	//	static int KeyInterval = 0;
	//	++KeyInterval;
	//	if (KeyInterval > 4) {
	//		DecreaseVolume();
	//		KeyInterval = 0;
	//	}
	//}
	//if (KeyOn == m_pDirectX->GetKeyStatus(DIK_RIGHT) || PadOn == m_pXinputDevice->GetButton(ButtonRIGHT))
	//{
	//	static int KeyInterval = 0;
	//	++KeyInterval;
	//	if (KeyInterval > 4) {
	//		IncreaseVolume();
	//		KeyInterval = 0;
	//	}
	//}
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_UP) || PadRelease == m_pXinputDevice->GetButton(ButtonUP) || PadPush == m_pXinputDevice->GetAnalogLState(ANALOGUP))
	{
		MoveUp();
	}
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_DOWN) || PadRelease == m_pXinputDevice->GetButton(ButtonDOWN) || PadPush == m_pXinputDevice->GetAnalogLState(ANALOGDOWN))
	{
		MoveDown();
	}

	return SCENE_NONE;
}

void PauseScene::Render() {
	CUSTOMVERTEX PauseMenuVertex[4];

	CreateSquareVertex(PauseMenuVertex, m_Menu);
	m_pDirectX->DrawTexture("PAUSEMENU_TEX", PauseMenuVertex);
	CreateSquareVertex(PauseMenuVertex, m_MenuTitle);
	m_pDirectX->DrawTexture("PAUSETITLE_TEX", PauseMenuVertex);
	CreateSquareVertex(PauseMenuVertex, m_Cursor);
	m_pDirectX->DrawTexture("SV_CURSOR_TEX", PauseMenuVertex);

	//for (int i = 0; i < VolumeMaxNum; ++i) {
	//	RevolveZ(PauseMenuVertex, DegToRad(180), m_RightCursol[i], WHITE, TriangleWidth, MenuHight, TriangleWidth, 1 - MenuHight);
	//	m_pDirectX->DrawTexture("SV_MENU_TEX", PauseMenuVertex);

	//	CreateSquareVertex(PauseMenuVertex, m_LeftCursol[i], WHITE, TriangleWidth, MenuHight, TriangleWidth, 1 - MenuHight);
	//	m_pDirectX->DrawTexture("SV_MENU_TEX", PauseMenuVertex);

	//	int DigitBuff = DigitCalc(m_BGMvolume, i);
	//	CreateSquareVertex(PauseMenuVertex, m_BGMVolumeNum[i], WHITE, NumTu * DigitBuff, 0, NumTu, NumTv);
	//	m_pDirectX->DrawTexture("NUMBER_TEX", PauseMenuVertex);

	//	DigitBuff = DigitCalc(m_SEvolume, i);
	//	CreateSquareVertex(PauseMenuVertex, m_SEVolumeNum[i], WHITE, NumTu * DigitBuff, 0, NumTu, NumTv);
	//	m_pDirectX->DrawTexture("NUMBER_TEX", PauseMenuVertex);

	//	DigitBuff = DigitCalc(m_ALLvolume, i);
	//	CreateSquareVertex(PauseMenuVertex, m_ALLVolumeNum[i], WHITE, NumTu * DigitBuff, 0, NumTu, NumTv);
	//	m_pDirectX->DrawTexture("NUMBER_TEX", PauseMenuVertex);
	//}
}

void PauseScene::TransrateScene() {
	ReturnScene();
}

void PauseScene::CursorMove() {
	switch (m_CursolPos) {
	case RETURN_GAME:
		m_Cursor.y = 220;
		break;
	case GOTO_SOUNDSETTING:
		m_Cursor.y = 330;
		break;
	case GOTO_TITLE:
		m_Cursor.y = 450;
		break;
	case END_GAME:
		m_Cursor.y = 560;
		break;
	}
}
void PauseScene::MoveUp() {
	switch (m_CursolPos) {
	case RETURN_GAME:
		m_CursolPos = END_GAME;
		break;
	case GOTO_SOUNDSETTING:
		m_CursolPos = RETURN_GAME;
		break;
	case GOTO_TITLE:
		m_CursolPos = GOTO_SOUNDSETTING;
		break;
	case END_GAME:
		m_CursolPos = GOTO_TITLE;
		break;
	}
}

void PauseScene::MoveDown() {
	switch (m_CursolPos) {
	case RETURN_GAME:
		m_CursolPos = GOTO_SOUNDSETTING;
		break;
	case GOTO_SOUNDSETTING:
		m_CursolPos = GOTO_TITLE;
		break;
	case GOTO_TITLE:
		m_CursolPos = END_GAME;
		break;
	case END_GAME:
		m_CursolPos = RETURN_GAME;
		break;
	}
}

