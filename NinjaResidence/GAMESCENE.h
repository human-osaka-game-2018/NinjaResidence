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
	Object * m_pBusyMapChip = NULL;//�g�p����MapChip
	Object * m_pIdleMapChip = NULL;//��~����MapChip
	Object * m_pShuriken = NULL;
	SkillSelect* m_SkillSelect = NULL;

	MapReverse * m_pMapReverse = NULL;
	Scene * m_pScene = NULL;

	int CurrentSkill;
	/**
	* @brief �ǂ�ł�Ԃ�����
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
	//�Q�[���V�[���i�Ńv���C���[��G�̈ړ��Ƃ��j�̍X�V�֐�
	void NotPushedAnyButton();
	void Render();       //�Q�[���V�[���i�Ńv���C���[��G�̕`�悵����Ƃ��j�̕`��֐�
	void LoadResouce();
	void TextureRender(std::string TextureKey, CUSTOMVERTEX* TextureSize);

};
