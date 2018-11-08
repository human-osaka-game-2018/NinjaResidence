#include "SceneManager.h"
#include "GAMESCENE.h"

SceneManager::SceneManager()
{
	m_pScene = new GameScene();
}

SceneManager::~SceneManager()
{
	delete m_pScene;
}

void SceneManager::Update()
{
	m_NextScene = m_pScene->Getm_NextScene();
	if (m_CurrentScene != m_NextScene)
	{
		switch (m_NextScene)
		{

		//TITLE_SCENE:
		//	delete m_pScene;
		//	m_pScene = new  TitleScene();
		//	m_CurrentScene = m_NextScene;
		//	break;

		case GAME_SCENE:
			delete m_pScene;
			m_pScene = new  GameScene();
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
