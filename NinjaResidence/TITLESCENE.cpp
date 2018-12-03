#include "SCENE.h"
#include "TITLESCENE.h"

TitleScene::TitleScene(DirectX* pDirectX) :Scene(pDirectX)
{
	pScene = this;
	ReadTexture();
	CreateSquareVertex(TitleBackground, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	//TitleBackground[0] = { 0.f,			  0.f,			 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f };
	//TitleBackground[1] = { DISPLAY_WIDTH,  0.f,			 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f };
	//TitleBackground[2] = { DISPLAY_WIDTH,  DISPLAY_HEIGHT, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f };
	//TitleBackground[3] = { 0.f,			  DISPLAY_HEIGHT, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f };
}

TitleScene::~TitleScene()
{
	m_pDirectX->ClearTexture();
	m_pDirectX->ClearFont();
}

SCENE_NUM  TitleScene::Update()
{
	timecount++;
	if (KeyRelease==m_pDirectX->GetKeyStatus(DIK_RETURN)|| KeyRelease == m_pDirectX->GetKeyStatus(DIK_NUMPADENTER)) {
		SetNextScene(STAGESELECT_SCENE);
	}
	return GetNextScene();
}

void TitleScene::Render()
{
	
	m_pDirectX->RenderingBegin();
	//private•Ï”‚ðŒ³‚ÉƒLƒƒƒ‰ƒNƒ^[‚ð•`‰æ
	m_pDirectX->DrawTexture("BACKGROUND_TEX", TitleBackground);
	RECT test = { 0,0,800,500 };
	char TestText[30];
	sprintf_s(TestText, 30, "%d", timecount);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT",DT_LEFT,0xffffffff);
	RECT testName = { 0, 200, 1280, 500 };
	char TestName[20] = "”EŽÒ‰®•~";
	m_pDirectX->DrawWord(testName, TestName, "DEBUG_FONT", DT_CENTER, 0xffff0000);
	RECT pushEnter= { 0, 400, 1280, 700 };
	char PUSH_ENTER[20] = "PUSH ENTER";
	m_pDirectX->DrawWord(pushEnter, PUSH_ENTER, "DEBUG_FONT", DT_CENTER, 0xffff0000);

	m_pDirectX->RenderingEnd();
}

void TitleScene::ReadTexture()
{
	m_pDirectX->LoadTexture("texture/BKG.jpg", "BACKGROUND_TEX");
	m_pDirectX->SetFont(100, 50, "DEBUG_FONT");

}
