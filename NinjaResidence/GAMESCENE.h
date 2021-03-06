﻿/**
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
#include "Torch.h"

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)


enum SCENE_NUM;
class Scene;
class MapChip;
class GameChara;
class MapReverse;
class DescriptionBoard;
class SoundManager;
class SkillBase;

class GameScene : public Scene
{

public:
	GameScene(DirectX* pDirectX, SoundOperater* pSoundOperater);
	~GameScene();
	SCENE_NUM Update();//ゲームシーン（でプレイヤーや敵の移動とか）の更新関数
	void KeyOperation();
	void NotPushedAnyButton();
	void Render();       //ゲームシーン（でプレイヤーや敵の描画したりとか）の描画関数
	void LoadResouce();
	void TextureRender(std::string TextureKey, CUSTOMVERTEX* TextureSize);
	/**
	* @brief ポーズシーンへの切り替え
	*/
	void TransePause() {
		RunPause = true;
	}
	
private:
	GameChara* m_pGameChara = NULL;
	Object* m_pBusyMapChip = NULL;//使用中のMapChip
	Object* m_pIdleMapChip = NULL;//停止中のMapChip

	SkillBase* m_pClawShot = NULL;
	SkillBase* m_pHighShuriken = NULL;
	SkillBase* m_pShuriken = NULL;
	SkillBase* m_pFireArt = NULL;
	std::string StageFilePath_surface = "csv/Book1.csv";
	std::string StageFilePath_reverse = "csv/Book2.csv";

	SkillSelect* m_SkillSelect = NULL;
	DescriptionBoard* m_pDescriptionBoard = NULL;
	MapReverse* m_pMapReverse = NULL;
	PauseScene* m_pPauseScene = NULL;
	Scene* m_pScene = NULL;
	//! 今の選択中忍術
	int CurrentSkill;
	void StageTurning();
	/**
	* @brief どんでん返し処理
	* @author Toshiya Matsuoka
	*/
	void Reverse();
	void SkillsUpdate();
	void SkillsRender();
	void SkillStart();
	void SkillEND();
	void SkillErase();
	void SkillKeyOperation(KeyDirection vec);
	void GameFailureAnime();
	void ClearAnime();
	bool m_EnableSkill[MAX_SKILL - 1] = { true,true,true };
	bool m_CanChangeSkill = true;
	bool RunPause = false;
	bool m_isClear = false;
	bool m_isGameFailure = false;
	const char* m_BGMSoundKey = "TUTORIAL";
};
