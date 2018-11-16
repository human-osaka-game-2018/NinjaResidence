#include "SceneManager.h"
#include "TITLESCENE.h"
#include "STAGESERECTSCENE.h"
#include "GAMESCENE.h"

SceneManager::SceneManager(DirectX* pDirectX):m_CurrentScene(SCENE_NONE),m_NextScene(TITLE_SCENE)
{
	m_pDirectX = pDirectX;
	m_pScene = new TitleScene(pDirectX);
}

SceneManager::~SceneManager()
{
	delete m_pScene;
	m_pScene = NULL;
}

void SceneManager::Update()
{
	m_NextScene = m_pScene->Getm_NextScene();
	if (m_CurrentScene != m_NextScene)
	{
		switch (m_NextScene)
		{

		case TITLE_SCENE:
			delete m_pScene;
			m_pScene = new  TitleScene(m_pDirectX);
			m_CurrentScene = m_NextScene;
			break;
		case STAGESELECT_SCENE:
			delete m_pScene;
			m_pScene = new  StageSerectScene(m_pDirectX);
			m_CurrentScene = m_NextScene;
			break;

		case GAME_SCENE:
			int ChosedStage = m_pScene->GetStageNum();
			delete m_pScene;
			m_pScene = new  GameScene(m_pDirectX, ChosedStage);
			m_CurrentScene = m_NextScene;
			break;
		}
	}
	m_pScene->Update();
}

void SceneManager::Render()
{
	m_pScene->Render();
}
void SceneManager::ReadTexture()
{
	m_pScene->ReadTexture();
}