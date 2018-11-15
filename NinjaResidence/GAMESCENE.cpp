#include "GAMESCENE.h"

GameScene::GameScene()
{
	m_pMapChip = new MapChip;
	m_pMapChip->MapChipCreate("csv/Book1.csv");
	m_pGameChara = new GameChara;
	ReadTexture();
	MapScrollx = 0;
	MapScrolly = 0;
	GameBackground[0] = { 0.f,			  0.f,			 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f };
	GameBackground[1] = { DISPLAY_WIDTH,  0.f,			 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f };
	GameBackground[2] = { DISPLAY_WIDTH,  DISPLAY_HIGHT, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f };
	GameBackground[3] = {0.f,			  DISPLAY_HIGHT, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f };
}

GameScene::~GameScene()
{
	delete m_pMapChip;
}

SCENE_NUM  GameScene::Update()
{
	//ゲームシーンでの操作できる
	HRESULT hr = g_pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		BYTE diks[256];
		g_pKeyDevice->GetDeviceState(sizeof(diks), &diks);
		if (diks[DIK_UP] & 0x80)
		{
			m_pGameChara->abc = UP;
			m_pGameChara->GameCharaKeyOperation();
		}
		if (diks[DIK_DOWN] & 0x80)
		{
			m_pGameChara->abc = DOWN;
			m_pGameChara->GameCharaKeyOperation();
		}
		if (diks[DIK_LEFT] & 0x80)
		{
			m_pGameChara->abc = LEFT;
			m_pGameChara->GameCharaKeyOperation();
		}
		if (diks[DIK_RIGHT] & 0x80)
		{
			m_pGameChara->abc = RIGHT;
			m_pGameChara->GameCharaKeyOperation();
		}
	}
	m_pGameChara->GameCharaUpdate();
	return Getm_NextScene();
}

void GameScene::Render()
{
//private変数を元にキャラクターを描画
	pScene->TextureRender(BACKGROUND_TEX, GameBackground);
	m_pGameChara->GameCharaRender();
	m_pMapChip->MapChipRender();
	g_pD3Device->Present(NULL, NULL, NULL, NULL);
}

void GameScene::ReadTexture()
{
	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/Block_Integration.png",
		&g_pTexture[BLOCK_INTEGRATION_TEX]);
	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/BKG.jpg",
		&g_pTexture[BACKGROUND_TEX]);
	D3DXCreateTextureFromFile(
		g_pD3Device,
		"texture/Chara_Integration.png",
		&g_pTexture[CHARA_INTEGRATION_TEX]);
}