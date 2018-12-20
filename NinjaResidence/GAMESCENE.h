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
#include "DescriptionBoard.h"
#include "PauseScene.h"
#include "Target.h"
#include "Rope.h"
#include "Switch.h"

#include <algorithm>

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)


enum SCENE_NUM;
class Scene;
class MapChip;
class GameChara;
class MapReverse;
class DescriptionBoard;
class Shuriken;
class SoundManager;

class GameScene : public Scene
{
<<<<<<< HEAD
public:
	GameScene(DirectX* pDirectX, SoundOperater* pSoundOperater, int ChosedStage);
=======
private:
	CUSTOMVERTEX  GameBackground[4];
	GameChara* pGameChara = NULL;
	Object* pBusyMapChip = NULL;//使用中のMapChip
	Object* pIdleMapChip = NULL;//停止中のMapChip
	MapReverse* m_pMapReverse = NULL;
	DescriptionBoard* m_pDescriptionBoard = NULL;
	Scene* pScene = NULL;
	
public:

	GameScene(DirectX* pDirectX, SoundsManager* pSoundManager, int ChosedStage);
>>>>>>> 繧ｿ繝ｼ繧ｲ繝�繝医→繧ｮ繝溘ャ繧ｯ繧定｣上→陦ｨ縺ｮ縺ｩ縺薙↓鄂ｮ縺�縺ｦ繧ゅ＞縺代ｋ讒倥↓縺励◆
	~GameScene();
	SCENE_NUM Update();//ゲームシーン（でプレイヤーや敵の移動とか）の更新関数
	void KeyOperation();
	void NotPushedAnyButton();
	void Render();       //ゲームシーン（でプレイヤーや敵の描画したりとか）の描画関数
	void LoadResouce();
	void TextureRender(std::string TextureKey, CUSTOMVERTEX* TextureSize);
	void TransePause() {
		RunPause = true;
	}
	
private:
	CUSTOMVERTEX  m_GameBackground[4];
	GameChara* m_pGameChara = NULL;
	Object* m_pBusyMapChip = NULL;//使用中のMapChip
	Object* m_pIdleMapChip = NULL;//停止中のMapChip
	Shuriken* m_pShuriken = NULL;
	SkillSelect* m_SkillSelect = NULL;
	DescriptionBoard* m_pDescriptionBoard = NULL;
	MapReverse* m_pMapReverse = NULL;
	PauseScene* m_pPauseScene = NULL;
	Scene* m_pScene = NULL;
	//! 今の選択中忍術
	int CurrentSkill;
	/**
	* @brief どんでん返し処理
	* @author Toshiya Matsuoka
	*/
	void Reverse();
	void SkillsUpdate();
	void SkillStart();
	void SkillKeyOperation(KeyDirection vec);
	void ClearAnime();
	bool m_EnableSkill[MAX_ITEM - 1] = { true,true,true };
	bool m_CanChangeSkill = true;
	bool RunPause = false;
	bool m_isClear = false;
};
