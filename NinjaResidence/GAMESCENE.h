/**
* @file GAMESCENE.h
* @brief GAMESCENEクラス
* @author Kojiro Kawahara
*/
#pragma once

#include "MapChip.h"
#include "SCENE.h"
#include "GameChara.h"
#include "MapReverse.h"
#include "SkillSelect.h"
#include <algorithm>

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)


enum SCENE_NUM;
class Scene;
class MapChip;
class GameChara;
class MapReverse;
class SoundManager;

class GameScene : public Scene
{
private:
	CUSTOMVERTEX  m_GameBackground[4];
	GameChara * m_pGameChara = NULL;
	Object * m_pBusyMapChip = NULL;//使用中のMapChip
	Object * m_pIdleMapChip = NULL;//停止中のMapChip
	Object * m_pShuriken = NULL;
	SkillSelect* m_SkillSelect = NULL;

	MapReverse * m_pMapReverse = NULL;
	Scene * m_pScene = NULL;

	int CurrentSkill;
	/**
	* @brief どんでん返し処理
	* @author Toshiya Matsuoka
	*/
	void Reverse();
	void SkillsUpdate();
	void SkillStart();
	bool m_EnableSkill[MAX_ITEM - 1] = { true,0,1 };

public:
	GameScene(DirectX* pDirectX, SoundsManager* pSoundManager, int ChosedStage);
	~GameScene();
	SCENE_NUM Update();
	void KeyOperation();
	//ゲームシーン（でプレイヤーや敵の移動とか）の更新関数
	void NotPushedAnyButton();
	void Render();       //ゲームシーン（でプレイヤーや敵の描画したりとか）の描画関数
	void LoadResouce();
	void TextureRender(std::string TextureKey, CUSTOMVERTEX* TextureSize);

};
