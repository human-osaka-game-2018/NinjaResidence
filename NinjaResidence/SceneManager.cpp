#include "SceneManager.h"
#include "TITLESCENE.h"
#include "STAGESERECTSCENE.h"
#include "GAMESCENE.h"

Scene*	SceneManager::m_pScene = NULL;

SceneManager::SceneManager(DirectX* pDirectX, SoundsManager* pSoundManager)
	:m_CurrentScene(SCENE_NONE),m_NextScene(TITLE_SCENE)
{
	m_pDirectX = pDirectX;
	m_pSoundManager = pSoundManager;
	//m_pScene = new TitleScene(m_pDirectX, m_pSoundManager);
	//ゲームシーンへショートカットする
	m_pScene = new GameScene(pDirectX, m_pSoundManager,5);
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
			m_pScene = new  TitleScene(m_pDirectX, m_pSoundManager);
			LoadAction();

			break;
		case STAGESELECT_SCENE:
			if (!isRunOnce) {
				delete m_pScene;
			}

			m_pScene = new  StageSerectScene(m_pDirectX, m_pSoundManager);
			LoadAction();
			break;
		case GAME_SCENE:
			if (!isRunOnce) {
				delete m_pScene;
			}
			m_pScene = new  GameScene(m_pDirectX, m_pSoundManager, ChosedStage);
			LoadAction();
			break;
		}
	}
	if (!isThreadActive) {
		m_pScene->Update();
		m_NextScene = m_pScene->GetNextScene();
	}
	return m_pScene->GetGameState();
}

void SceneManager::Render()
{
	if (!isThreadActive) {
		m_pScene->Render();
	}
	else {
		LoadAnimation();
		RECT testName = { 0, 400, 1280, 720 };
		char TestName[30];
		sprintf_s(TestName, 30, "TIME_%d", LoadTime);
		m_pDirectX->DrawWord(testName, TestName, "LOAD_FONT", DT_CENTER, 0xffffffff);

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
	threadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, m_pScene, 0, NULL);
	ResumeThread(threadHandle);
		isRunOnce = true;
		isThreadActive = true;
	}
	GetExitCodeThread(threadHandle, &threadResult);
	if (threadResult != STILL_ACTIVE && LoadTime >= 20) {
		CloseHandle(threadHandle);
		isRunOnce = false;
		LoadTime = 0;
		isThreadActive = false;
		m_CurrentScene = m_NextScene;
	}
}

