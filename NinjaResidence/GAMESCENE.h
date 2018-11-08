#pragma once

#include "MapChip.h"
#include "SCENE.h"
enum SCENE_NUM;
class Scene;
class MapChip;


class GameScene : public Scene
{
private:
	OBJECT_STATE m_Player = { 0,0,CELL_SIZE,(CELL_SIZE * 2)};
	CUSTOMVERTEX VertexPlayer[4];
	CUSTOMVERTEX  GameBackground[4];
	MapChip*	pMapChip;
	Scene*	pScene;
public:
	GameScene();
	~GameScene();
	SCENE_NUM Update();     //�Q�[���V�[���i�Ńv���C���[��G�̈ړ��Ƃ��j�̍X�V�֐�
	void Render();       //�Q�[���V�[���i�Ńv���C���[��G�̕`�悵����Ƃ��j�̕`��֐�
};
