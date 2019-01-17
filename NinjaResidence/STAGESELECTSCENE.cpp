/**
* @file STAGESELECTSCENE.cpp
* @brief ステージセレクトシーン
* @author Toshiya Matsuoka
*/
#include "STAGESELECTSCENE.h"

StageSelectScene::StageSelectScene(DirectX* pDirectX, SoundOperater* pSoundOperater) :Scene(pDirectX,pSoundOperater)
{
	m_StageNum = 0;
	m_pScene = this;
	CreateSquareVertex(m_BackgroundVertex, DISPLAY_WIDTH, DISPLAY_HEIGHT);

	m_SelectCursol[0] = {200,100,150,50};

	m_StageImage[0] = {200,100,150,50};
	m_StageImage[1] = {800,100,150,50};
	m_StageImage[2] = {200,300,150,50};
	m_StageImage[3] = {800,300,150,50};
	m_StageImage[4] = {200,500,150,50};
	m_StageImage[5] = {800,500,150,50};

	m_StageImagekey[0] = "StageImageT_TEX";
	m_StageImagekey[1] = "StageImage1_TEX";
	m_StageImagekey[2] = "StageImage2_TEX";
	m_StageImagekey[3] = "StageImage3_TEX";
	m_StageImagekey[4] = "StageImage4_TEX";
	m_StageImagekey[5] = "StageImage5_TEX";
	m_StageImagekey[6] = "Kunai_TEX";
}

StageSelectScene::~StageSelectScene()
{
	m_pDirectX->ClearTexture();
	m_pDirectX->ClearFont();
}

SCENE_NUM  StageSelectScene::Update()
{
	m_pXinputDevice->DeviceUpdate();

	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_RETURN) || KeyRelease == m_pDirectX->GetKeyStatus(DIK_NUMPADENTER)) {
		SetNextScene(GAME_SCENE);		
	}
	if (PadRelease == m_pXinputDevice->GetButton(ButtonA)) {
		SetNextScene(GAME_SCENE);
	}
	if (KeyPush == m_pDirectX->GetKeyStatus(DIK_SPACE)) {
		m_StageNum = 7;
	}
	

	if (PadRelease == m_pXinputDevice->GetButton(ButtonRIGHT))
	{
		//TurnUpStageImage();
		//if (m_StageNum < 5) {
		//	m_StageNum++;
		//}
		//else m_StageNum = 0;
	}
	if (PadRelease == m_pXinputDevice->GetButton(ButtonLEFT))
	{
		//TurnDownStageImage();
		if (m_StageNum > 0) {
			m_StageNum--;
		}
		else m_StageNum = 5;
	}
	if (m_pXinputDevice->GetAnalogL(ANALOGRIGHT))
	{
		//TurnUpStageImage();
		if (m_StageNum < 5) {
			m_StageNum++;
		}
		else m_StageNum = 0;
	}
	if (m_pXinputDevice->GetAnalogL(ANALOGLEFT))
	{
		//TurnDownStageImage();
		if (m_StageNum > 0) {
			m_StageNum--;
		}
		else m_StageNum = 5;
	}

	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_RIGHT)) {
		//TurnDownStageImage();
		if (m_StageNum < 5) {
			m_StageNum++;
		}
		else m_StageNum = 0;
	}
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_LEFT)) {
		//TurnDownStageImage();
		if (m_StageNum > 0) {
			m_StageNum--;
		}
		else m_StageNum = 5;
	}
	return GetNextScene();
}

void StageSelectScene::Render()
{
	
	m_pDirectX->DrawTexture("SELECT_BG_TEX", m_BackgroundVertex);

	m_pDirectX->DrawTexture(m_StageImagekey[6], StageImage);

	CUSTOMVERTEX StageImage[4];
	if (m_StageNum != 7) 
	{
		CreateSquareVertex(StageImage, m_StageImage[0]);
		m_pDirectX->DrawTexture(m_StageImagekey[0], StageImage);

		CreateSquareVertex(StageImage, m_StageImage[1]);
		m_pDirectX->DrawTexture(m_StageImagekey[1], StageImage);

		CreateSquareVertex(StageImage, m_StageImage[2]);
		m_pDirectX->DrawTexture(m_StageImagekey[2], StageImage);

		CreateSquareVertex(StageImage, m_StageImage[3]);
		m_pDirectX->DrawTexture(m_StageImagekey[3], StageImage);

		CreateSquareVertex(StageImage, m_StageImage[4]);
		m_pDirectX->DrawTexture(m_StageImagekey[4], StageImage);

		CreateSquareVertex(StageImage, m_StageImage[5]);
		m_pDirectX->DrawTexture(m_StageImagekey[5], StageImage);

		//CreateSquareVertex(StageImage, m_StageFrame, 0xffffaa00);
		//m_pDirectX->DrawTexture("TEX", StageImage);
	}
	else {
		CreateSquareVertex(StageImage, m_StageImage[0]);
		m_pDirectX->DrawTexture("StageImageD_TEX", StageImage);
	}
}

void StageSelectScene::LoadResouce()
{
	m_pDirectX->LoadTexture(NULL, "TEX");
	m_pDirectX->LoadTexture("texture/BG.jpg", "SELECT_BG_TEX");
	m_pDirectX->LoadTexture("texture/StageImageT.jpg", "StageImageT_TEX");
	m_pDirectX->LoadTexture("texture/StageImage1.jpg", "StageImage1_TEX");
	m_pDirectX->LoadTexture("texture/StageImage2.jpg", "StageImage2_TEX");
	m_pDirectX->LoadTexture("texture/StageImage3.jpg", "StageImage3_TEX");
	m_pDirectX->LoadTexture("texture/StageImage4.jpg", "StageImage4_TEX");
	m_pDirectX->LoadTexture("texture/StageImage5.jpg", "StageImage5_TEX");
	m_pDirectX->LoadTexture("texture/Kunai.png", "Kunai_TEX");
	m_pDirectX->LoadTexture("texture/StageImageD.jpg", "StageImageD_TEX");

	m_pDirectX->SetFont(100, 50, "DEBUG_FONT");

}

void StageSelectScene::TurnUpStageImage() {
	//std::string Buf = m_StageImagekey[0];
	//m_StageImagekey[0] = m_StageImagekey[1];
	//m_StageImagekey[1] = m_StageImagekey[2];
	//m_StageImagekey[2] = m_StageImagekey[3];
	//m_StageImagekey[3] = m_StageImagekey[4];
	//m_StageImagekey[4] = m_StageImagekey[5];
	//m_StageImagekey[5] = Buf;
}
void StageSelectScene::TurnDownStageImage() {
	//std::string Buf = m_StageImagekey[5];
	//m_StageImagekey[5] = m_StageImagekey[4];
	//m_StageImagekey[4] = m_StageImagekey[3];
	//m_StageImagekey[3] = m_StageImagekey[2];
	//m_StageImagekey[2] = m_StageImagekey[1];
	//m_StageImagekey[1] = m_StageImagekey[0];
	//m_StageImagekey[0] = Buf;
}
