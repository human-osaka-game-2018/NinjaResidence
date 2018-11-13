#include "GAMEMANAGER.h"
#include "SceneManager.h"

GAMEMANAGER::GAMEMANAGER()
{

}

GAMEMANAGER::~GAMEMANAGER()
{



}


int MessageLoop()
{
	MSG msg;
	DWORD SyncOld = timeGetTime();	//	システム時間を取得
	DWORD SyncNow;
	timeBeginPeriod(1);
	ZeroMemory(&msg, sizeof(msg));
	SceneManager* pSceneManager = new SceneManager();
	while (msg.message != WM_QUIT)
	{
		Sleep(1);
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			SyncNow = timeGetTime();
			if (SyncNow - SyncOld >= 1000 / 60)//1秒間に60回この中に入るはず
			{
				pDirectX->CheckKeyStatus();
				pDirectX->ClearDisplay();
				//シーンのUpdateとRender
				pSceneManager->Update();
				pSceneManager->Render();
				SyncOld = SyncNow;
			}
		}
	}
	timeEndPeriod(1);
	delete pSceneManager;
	
	return (int)msg.wParam;
}
