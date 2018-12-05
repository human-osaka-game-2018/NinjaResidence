/**
* @file STAGESERECTSCENE.cpp
* @brief ステージセレクトシーン
* @author Toshiya Matsuoka
*/
#include "STAGESERECTSCENE.h"

StageSerectScene::StageSerectScene(DirectX* pDirectX, SoundsManager* pSoundManager) :Scene(pDirectX,pSoundManager)
{
	pScene = this;
	CreateSquareVertex(SerectBackground, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	m_StageImage[0] = {CENTRAL_X,CENTRAL_Y,250,250 };
	m_StageImage[1] = {CENTRAL_X + 250,CENTRAL_Y,200,200 };
	m_StageImage[2] = {CENTRAL_X + 75,CENTRAL_Y ,150,150 };
	m_StageImage[3] = {CENTRAL_X + 75,CENTRAL_Y ,150,150 };
	m_StageImage[4] = {CENTRAL_X - 250,CENTRAL_Y,200,200 };

}

StageSerectScene::~StageSerectScene()
{
	m_pDirectX->ClearTexture();
	m_pDirectX->ClearFont();
}

SCENE_NUM  StageSerectScene::Update()
{
	timecount++;
	m_pXinputDevice->DeviceUpdate();

	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_RETURN) || KeyRelease == m_pDirectX->GetKeyStatus(DIK_NUMPADENTER)) {
		SetNextScene(GAME_SCENE);		
	}
	if (PadRelease == m_pXinputDevice->GetButton(ButtonA)) {
		SetNextScene(GAME_SCENE);
	}
	if (PadRelease == m_pXinputDevice->GetButton(ButtonRIGHT))
	{
		if (StageNum < 5) {
			StageNum++;
		}
		else StageNum = 0;
	}
	if (PadRelease == m_pXinputDevice->GetButton(ButtonLEFT))
	{
		if (StageNum > 0) {
			StageNum--;
		}
		else StageNum = 5;
	}
	if (m_pXinputDevice->GetAnalogL(ANALOGRIGHT))
	{
		if (StageNum < 5) {
			StageNum++;
		}
		else StageNum = 0;
	}
	if (m_pXinputDevice->GetAnalogL(ANALOGLEFT))
	{
		if (StageNum > 0) {
			StageNum--;
		}
		else StageNum = 5;
	}

	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_RIGHT)) {
		if (StageNum < 5) {
			StageNum++;
		}
		else StageNum = 0;
	}
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_LEFT)) {
		if (StageNum > 0) {
			StageNum--;
		}
		else StageNum = 5;
	}
	return GetNextScene();
}

void StageSerectScene::Render()
{
	
	m_pDirectX->DrawTexture("BACKGROUND_TEX", SerectBackground);
	RECT test = { 0,0,800,500 };
	char TestText[ArrayLong];
	sprintf_s(TestText, ArrayLong, "%d", timecount);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_LEFT, 0xffffffff);

	CUSTOMVERTEX StageImage[4];

	CreateSquareVertex(StageImage, m_StageImage[3]);
	m_pDirectX->DrawTexture("BACKGROUND_TEX", StageImage);

	CreateSquareVertex(StageImage, m_StageImage[2]);
	m_pDirectX->DrawTexture("BACKGROUND_TEX", StageImage);

	CreateSquareVertex(StageImage, m_StageImage[4]);
	m_pDirectX->DrawTexture("BACKGROUND_TEX", StageImage);

	CreateSquareVertex(StageImage, m_StageImage[1]);
	m_pDirectX->DrawTexture("BACKGROUND_TEX", StageImage);

	CreateSquareVertex(StageImage, m_StageFrame,0xffffaa00);
	m_pDirectX->DrawTexture("TEX", StageImage);

	CreateSquareVertex(StageImage, m_StageImage[0]);
	m_pDirectX->DrawTexture("BACKGROUND_TEX", StageImage);

	RECT testName = { 0, 400, 1280, 720 };
	char TestName[ArrayLong];
	sprintf_s(TestName, ArrayLong, "STAGE_%d", StageNum);
	m_pDirectX->DrawWord(testName, TestName, "DEBUG_FONT", DT_CENTER, 0xffffffff);

}

void StageSerectScene::LoadResouce()
{
	m_pDirectX->LoadTexture(NULL, "TEX");
	m_pDirectX->LoadTexture("texture/BKG.jpg", "BACKGROUND_TEX");
	m_pDirectX->SetFont(100, 50, "DEBUG_FONT");

}
