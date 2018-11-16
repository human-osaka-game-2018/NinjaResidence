#pragma once

#include "MapChip.h"
#include "SCENE.h"
#include "GameChara.h"

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

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
	GameScene(DirectX* pDirectX, int ChosedStage);
	~GameScene();
	SCENE_NUM Update();     //�Q�[���V�[���i�Ńv���C���[��G�̈ړ��Ƃ��j�̍X�V�֐�
	void Render();       //�Q�[���V�[���i�Ńv���C���[��G�̕`�悵����Ƃ��j�̕`��֐�
	void ReadTexture();
	void TextureRender(std::string TextureKey, CUSTOMVERTEX* TextureSize);

};
