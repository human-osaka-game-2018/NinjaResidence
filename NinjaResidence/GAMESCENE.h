#pragma once

#include "MapChip.h"
#include "SCENE.h"
#include "GameChara.h"
enum SCENE_NUM;
class Scene;
class MapChip;
class GameChara;

class GameScene : public Scene
{
private:
	CUSTOMVERTEX  GameBackground[4];
public:
	GameChara * m_pGameChara;
	MapChip * m_pMapChip;
	Scene * pScene;
	int MapScrollx ;
	int MapScrolly ;
	GameScene();
	~GameScene();
	SCENE_NUM Update();     //�Q�[���V�[���i�Ńv���C���[��G�̈ړ��Ƃ��j�̍X�V�֐�
	void Render();       //�Q�[���V�[���i�Ńv���C���[��G�̕`�悵����Ƃ��j�̕`��֐�
	void ReadTexture();
};
