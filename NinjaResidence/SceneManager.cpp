/**
* @file SceneManager.cpp
* @brief SceneManagerクラス
* @author Kojiro Kawahara
*/
#include "SceneManager.h"
#include "TITLESCENE.h"
#include "STAGESELECTSCENE.h"
#include "GAMESCENE.h"

Scene*	SceneManager::m_pScene = NULL;

SceneManager::SceneManager(DirectX* pDirectX, SoundsManager* pSoundManager)
	:m_CurrentScene(SCENE_NONE),m_NextScene(TITLE_SCENE)
{
	m_pDirectX = pDirectX;
	m_pSoundManager = pSoundManager;
	m_pScene = new TitleScene(m_pDirectX, m_pSoundManager);
	//ゲームシーンへショートカットする
	//m_NextScene = GAME_SCENE;
}

SceneManager::~SceneManager()
{
	delete m_pScene;
	m_pScene = NULL;
}

int SceneManager::Update()
{
	if (m_CurrentScene != m_NextScene)
	{
		int ChosedStage = m_pScene->GetStageNum();
		switch (m_NextScene)
		{
		case TITLE_SCENE:
			if (!isRunOnce) {
				delete m_pScene;
			}
			isThreadActive = true;
			m_pScene = new  TitleScene(m_pDirectX, m_pSoundManager);
			break;
		case STAGESELECT_SCENE:
			if (!isRunOnce) {
				delete m_pScene;
			}
			isThreadActive = true;
			m_pScene = new  StageSelectScene(m_pDirectX, m_pSoundManager);
			break;
		case GAME_SCENE:
			if (!isRunOnce) {
				delete m_pScene;
			}
			isThreadActive = true;
			m_pScene = new  GameScene(m_pDirectX, m_pSoundManager, ChosedStage);
			break;
		}
		m_NextScene = m_pScene->GetNextScene();

	}
	if (!isThreadActive) {
		m_pScene->Update();
		m_NextScene = m_pScene->GetNextScene();
	}
	else LoadAction();

	return m_pScene->GetGameState();
}

void SceneManager::Render()
{
	if (!isThreadActive) {
		m_pScene->Render();
	}
	else {
		LoadAnimation();
		const int ArrayLong = 64;
		RECT testName = { 0, 400, 1280, 720 };
		char TestName[ArrayLong];
		sprintf_s(TestName, ArrayLong, "TIME_%d", LoadTime);
		//m_pDirectX->DrawWord(testName, TestName, "LOAD_FONT", DT_CENTER, 0xffffffff);

	}
}
void SceneManager::LoadResouce()
{
	m_pScene->LoadResouce();
}
DWORD WINAPI SceneManager::Thread(LPVOID *data)
{
	m_pScene->LoadResouce();
	ExitThread(0);
}

void SceneManager::LoadAnimation() {
	m_pScene->LoadAnimation();
}

void SceneManager::LoadAction() {
	++LoadTime;
	//static bool isRunOnce = false;
	if (!isRunOnce) {
	m_threadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, m_pScene, 0, NULL);
	ResumeThread(m_threadHandle);
		isRunOnce = true;
		isThreadActive = true;
	}
	GetExitCodeThread(m_threadHandle, &m_threadResult);
	if (m_threadResult != STILL_ACTIVE && LoadTime >= 20) {
		CloseHandle(m_threadHandle);
		isRunOnce = false;
		LoadTime = 0;
		isThreadActive = false;
		m_CurrentScene = m_NextScene;
	}
}

