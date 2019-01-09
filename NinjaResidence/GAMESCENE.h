/**
* @file GAMESCENE.h
* @brief GAMESCENE�N���X
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
public:
	GameScene(DirectX* pDirectX, SoundOperater* pSoundOperater, int ChosedStage);
	~GameScene();
	SCENE_NUM Update();//�Q�[���V�[���i�Ńv���C���[��G�̈ړ��Ƃ��j�̍X�V�֐�
	void KeyOperation();
	void NotPushedAnyButton();
	void Render();       //�Q�[���V�[���i�Ńv���C���[��G�̕`�悵����Ƃ��j�̕`��֐�
	void LoadResouce();
	void TextureRender(std::string TextureKey, CUSTOMVERTEX* TextureSize);
	void TransePause() {
		RunPause = true;
	}
	
private:
	CUSTOMVERTEX  m_GameBackground[4];
	GameChara* m_pGameChara = NULL;
	Object* m_pBusyMapChip = NULL;//�g�p����MapChip
	Object* m_pIdleMapChip = NULL;//��~����MapChip
	Shuriken* m_pShuriken = NULL;
	SkillSelect* m_SkillSelect = NULL;
	DescriptionBoard* m_pDescriptionBoard = NULL;
	MapReverse* m_pMapReverse = NULL;
	PauseScene* m_pPauseScene = NULL;
	Scene* m_pScene = NULL;
	//! ���̑I�𒆔E�p
	int CurrentSkill;
	/**
	* @brief �ǂ�ł�Ԃ�����
	* @author Toshiya Matsuoka
	*/
	void Reverse();
	void SkillsUpdate();
	void SkillStart();
	void SkillKeyOperation(KeyInput vec);
	bool m_EnableSkill[MAX_ITEM - 1] = { true,true,true };
	bool m_CanChangeSkill = true;
	bool RunPause = false;
};
