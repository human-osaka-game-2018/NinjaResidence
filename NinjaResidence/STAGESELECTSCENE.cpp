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

	m_SelectCursol = { 450.f,210.f,140.f,100.f};

	m_StageSelectBack =  {120.f,70.f,80.f,50.f};

	//初期値を決まる関数
	InitPosStageImage();
	InitPosStageSelectNumber();
	InitStageImagekey();
	InitStageSelectNumberkey();
}

StageSelectScene::~StageSelectScene()
{
	m_pDirectX->ClearTexture();
	m_pDirectX->ClearFont();
}

void StageSelectScene::InitPosStageImage()
{
	for (int i = 0;i < 6;i++)
	{
		const float STAGEIMAGE_SCALE_X = 180.f;
		const float STAGEIMAGE_SCALE_Y = 80.f;
		m_StageImage[i].scale_x = STAGEIMAGE_SCALE_X;
		m_StageImage[i].scale_y = STAGEIMAGE_SCALE_Y;
		m_StageImage[i].y = ((i / 2) + 1) * 200;
		if (i % 2)
		{
			m_StageImage[i].x = 840.f;
		}
		else
		{
			m_StageImage[i].x = 200.f;
		}
	}
}

void StageSelectScene::InitPosStageSelectNumber()
{
	for (int i = 0;i < 6;i++)
	{
		const float STAGESELECTNUMBER_SCALE_X = 150.f;
		const float STAGESELECTNUMBER_SCALE_Y = 50.f;
		m_StageSelectNumber[i].scale_x = STAGESELECTNUMBER_SCALE_X;
		m_StageSelectNumber[i].scale_y = STAGESELECTNUMBER_SCALE_Y;
		m_StageSelectNumber[i].y = (((i / 2) + 1) * 200) + 5;
		if (i % 2)
		{
			m_StageSelectNumber[i].x = 840.f;
		}
		else
		{
			m_StageSelectNumber[i].x = 200.f;
		}
	}
}

void StageSelectScene::InitStageImagekey()
{
	m_StageImagekey[0] = "StageImageT_TEX";
	m_StageImagekey[1] = "StageImage1_TEX";
	m_StageImagekey[2] = "StageImage2_TEX";
	m_StageImagekey[3] = "StageImage3_TEX";
	m_StageImagekey[4] = "StageImage4_TEX";
	m_StageImagekey[5] = "StageImage5_TEX";
}


void StageSelectScene::InitStageSelectNumberkey()
{
	m_StageSelectNumberkey[0] = "StageSelectNumberT_TEX";
	m_StageSelectNumberkey[1] = "StageSelectNumber1_TEX";
	m_StageSelectNumberkey[2] = "StageSelectNumber2_TEX";
	m_StageSelectNumberkey[3] = "StageSelectNumber3_TEX";
	m_StageSelectNumberkey[4] = "StageSelectNumber4_TEX";
	m_StageSelectNumberkey[5] = "StageSelectNumber5_TEX";
}


SCENE_NUM  StageSelectScene::Update()
{
	m_pXinputDevice->DeviceUpdate();

	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_RETURN) || KeyRelease == m_pDirectX->GetKeyStatus(DIK_NUMPADENTER)) {
		if (m_StageNum == StageTitle)
		{
			SetNextScene(TITLE_SCENE);
		}
		else
		{
			SetNextScene(GAME_SCENE);
		}
	}
	if (PadRelease == m_pXinputDevice->GetButton(ButtonA)) {
		if (m_StageNum == StageTitle)
		{
			SetNextScene(TITLE_SCENE);
		}
		else
		{
			SetNextScene(GAME_SCENE);
		}
	}
	if (KeyPush == m_pDirectX->GetKeyStatus(DIK_SPACE)) {
		m_StageNum = 8;
	}
	

	if (PadRelease == m_pXinputDevice->GetButton(ButtonRIGHT)){
		ReceiveKeym_StageNumSet(DIK_RIGHT);
	}
	if (PadRelease == m_pXinputDevice->GetButton(ButtonLEFT)){
		ReceiveKeym_StageNumSet(DIK_LEFT);
	}

	if (m_pXinputDevice->GetAnalogL(ANALOGRIGHT)){
		ReceiveKeym_StageNumSet(DIK_RIGHT);
	}
	if (m_pXinputDevice->GetAnalogL(ANALOGLEFT)){
		ReceiveKeym_StageNumSet(DIK_LEFT);
	}

	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_RIGHT)) {
		ReceiveKeym_StageNumSet(DIK_RIGHT);
	}
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_LEFT)) {
		ReceiveKeym_StageNumSet(DIK_LEFT);
	}
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_UP)) {
		ReceiveKeym_StageNumSet(DIK_UP);
	}
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_DOWN)) {
		ReceiveKeym_StageNumSet(DIK_DOWN);
	}
	return GetNextScene();
}

void StageSelectScene::Render()
{
	m_pDirectX->DrawTexture("SELECT_BG_TEX", m_BackgroundVertex);

	if (m_StageNum != 8) 	
	{
		RenderAllStage(m_StageImage, m_StageImagekey);
		RenderAllStage(m_StageSelectNumber, m_StageSelectNumberkey);
	}
	else {
		r(*m_StageImage, "StageImageD_TEX");
	}

	r(m_StageSelectBack, "StagexSelectBack_TEX");

	r(m_SelectCursol, "Kunai_TEX");
	

}

void StageSelectScene::LoadResouce()
{
	m_pDirectX->LoadTexture(NULL, "TEX");
	m_pDirectX->LoadTexture("texture/SelectBG.png", "SELECT_BG_TEX");
	m_pDirectX->LoadTexture("texture/StageImageT.png", "StageImageT_TEX");
	m_pDirectX->LoadTexture("texture/StageImage1.png", "StageImage1_TEX");
	m_pDirectX->LoadTexture("texture/StageImage2.png", "StageImage2_TEX");
	m_pDirectX->LoadTexture("texture/StageImage3.png", "StageImage3_TEX");
	m_pDirectX->LoadTexture("texture/StageImage4.png", "StageImage4_TEX");
	m_pDirectX->LoadTexture("texture/StageImage5.png", "StageImage5_TEX");
	m_pDirectX->LoadTexture("texture/StageSelectNumberT.png", "StageSelectNumberT_TEX");
	m_pDirectX->LoadTexture("texture/StageSelectNumber1.png", "StageSelectNumber1_TEX");
	m_pDirectX->LoadTexture("texture/StageSelectNumber2.png", "StageSelectNumber2_TEX");
	m_pDirectX->LoadTexture("texture/StageSelectNumber3.png", "StageSelectNumber3_TEX");
	m_pDirectX->LoadTexture("texture/StageSelectNumber4.png", "StageSelectNumber4_TEX");
	m_pDirectX->LoadTexture("texture/StageSelectNumber5.png", "StageSelectNumber5_TEX");
	m_pDirectX->LoadTexture("texture/Kunai.png", "Kunai_TEX");
	m_pDirectX->LoadTexture("texture/StagexSelectBack.png", "StagexSelectBack_TEX");
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




void StageSelectScene::RenderAllStage(CENTRAL_STATE CentralState[6], std::string TextureKey[6])
{
	for (int i = 0;i <= Stage5;i++)
	{
		r(CentralState[i], TextureKey[i]);
	}
}


void StageSelectScene::r(const CENTRAL_STATE& CentralState, std::string TextureKey)//ポインタか参照で引数をもらう様にする
{
	CUSTOMVERTEX StageImage[4];
	CreateSquareVertex(StageImage, CentralState);
	m_pDirectX->DrawTexture(TextureKey, StageImage);
}





void StageSelectScene::ReceiveKeym_StageNumSet(int KeyState)
{
	switch (KeyState)
	{
	case DIK_DOWN:
		switch (m_StageNum)
		{
		case Stage3:
			m_StageNum = Stage5;
			m_SelectCursol.y += KUNAI_MOVEMENT_Y;
			break;
		case Stage2:
			m_StageNum = Stage4;
			m_SelectCursol.y += KUNAI_MOVEMENT_Y;
			break;
		case Stage0:
			m_StageNum = Stage2;
			m_SelectCursol.y += KUNAI_MOVEMENT_Y;
			break;
		case Stage1:
			m_StageNum = Stage3;
			m_SelectCursol.y += KUNAI_MOVEMENT_Y;
			break;
		case StageTitle:
			m_StageNum = Stage0;
			m_SelectCursol.y += MOVEMENT_X_TO_BACK;
			m_SelectCursol.x += MOVEMENT_Y_TO_BACK;
			break;
		}
		break;
	case DIK_UP:
		switch (m_StageNum)
		{
		case Stage0:
			m_StageNum = StageTitle;
			m_SelectCursol.y -= MOVEMENT_X_TO_BACK;
			m_SelectCursol.x -= MOVEMENT_Y_TO_BACK;
			break;
		case Stage1:
			m_StageNum = StageTitle;
			m_SelectCursol.y -= MOVEMENT_X_TO_BACK;
			m_SelectCursol.x -= 770;
			break;
		case Stage2:
			m_StageNum = Stage0;
			m_SelectCursol.y -= KUNAI_MOVEMENT_Y;
			break;
		case Stage3:
			m_StageNum = Stage1;
			m_SelectCursol.y -= KUNAI_MOVEMENT_Y;
			break;
		case Stage4:
			m_StageNum = Stage2;
			m_SelectCursol.y -= KUNAI_MOVEMENT_Y;
			break;
		case Stage5:
			m_StageNum = Stage3;
			m_SelectCursol.y -= KUNAI_MOVEMENT_Y;
			break;
		}
		break;
	case DIK_RIGHT:
		switch (m_StageNum)
		{
		case Stage0:
			m_StageNum = Stage1;
			m_SelectCursol.x += KUNAI_MOVEMENT_X;
			break;
		case Stage2:
			m_StageNum = Stage3;
			m_SelectCursol.x += KUNAI_MOVEMENT_X;
			break;
		case Stage4:
			m_StageNum = Stage5;
			m_SelectCursol.x += KUNAI_MOVEMENT_X;
			break;
		}
		break;
	case DIK_LEFT:
		switch (m_StageNum)
		{
		case Stage1:
			m_StageNum = Stage0;
			m_SelectCursol.x -= KUNAI_MOVEMENT_X;
			break;
		case Stage3:
			m_StageNum = Stage2;
			m_SelectCursol.x -= KUNAI_MOVEMENT_X;
			break;
		case Stage5:
			m_StageNum = Stage4;
			m_SelectCursol.x -= KUNAI_MOVEMENT_X;
			break;
		}
		break;
	}
}
