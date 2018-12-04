#pragma once

#include "MapChip.h"
#include "SCENE.h"
#include "GameChara.h"
#include "MapReverse.h"

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
	CUSTOMVERTEX  GameBackground[4];
	GameChara * m_pGameChara = NULL;
	Object * m_pBusyMapChip = NULL;//�g�p����MapChip
	Object * m_pIdleMapChip = NULL;//��~����MapChip
	MapReverse * m_pMapReverse = NULL;
	Scene * pScene = NULL;
	
public:
	GameScene(DirectX* pDirectX, SoundsManager* pSoundManager, int ChosedStage);
	~GameScene();
	SCENE_NUM Update();     //�Q�[���V�[���i�Ńv���C���[��G�̈ړ��Ƃ��j�̍X�V�֐�
	void Render();       //�Q�[���V�[���i�Ńv���C���[��G�̕`�悵����Ƃ��j�̕`��֐�
	void LoadResouce();
	void TextureRender(std::string TextureKey, CUSTOMVERTEX* TextureSize);

};
