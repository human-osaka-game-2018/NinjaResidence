#pragma once

#include <vector>
#include "GAMESCENE.h"
#include "Object.h"


class GameScene;
class MapReverse;
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define CharaMoveSpeed 15


class GameChara :public Object
{
private:
	CENTRAL_STATE m_Player = { 400,200,(CELL_SIZE * 2),(CELL_SIZE * 4) };
	CUSTOMVERTEX m_DisplayCharaCoordinate[4];
	CUSTOMVERTEX m_WorldCharaCoordinate[4];
	CUSTOMVERTEX m_ReverseDisplayCharaCoordinate[4];
	CUSTOMVERTEX m_ReverseWorldCharaCoordinate[4];
	CUSTOMVERTEX m_SurfaceDisplayCharaCoordinate[4];
	CUSTOMVERTEX m_SurfaceWorldCharaCoordinate[4];
	int m_PrevMapLeftDirectionPosition;//�O�t���[����MapLeftDirectionPosition�̒l
	int m_PrevMapRightDirectionPosition;//�O�t���[����MapRightDirectionPosition�̒l
	int m_PrevMapCharaPositionY;//�O�t���[����MapCharaPositionY�̒l
	int MapLeftDirectionPosition;//�L�����̍�����X���W
	int MapRightDirectionPosition;//�L�����̉E����X���W
	int MapCharaPositionY;//�L�����̏㑤��x���W
	float Gravity;//���t���[��������d�͂̒l
	const int DisplayCharMoveScopeUp = 100;//m_DisplayCharaCoordinate��Y���W�����̒l�������Ə�ɃX�N���[������
	const int DisplayCharMoveScopeDown = 630;//m_DisplayCharaCoordinate��Y���W�����̒l�𒴂���Ə�ɃX�N���[������
	const int DisplayCharMoveScopeLeft = 300;//m_DisplayCharaCoordinate��X���W�����̒l�������ƍ��ɃX�N���[������
	const int DisplayCharMoveScopeRight = 980;//m_DisplayCharaCoordinate��X���W�����̒l�𒴂���ƉE�ɃX�N���[������
	const int DisplayCharMoveScopeX = 300;//���[�����X���W�̉ғ��͈�
	void CharaMoveOperation(KeyDirection vec, CUSTOMVERTEX* pWorldCharaCoordinate, CUSTOMVERTEX* pDisplayCharaCoordinate, float MoveQuantity);
	void ValueAllSetCUSTOMVERTEX(CUSTOMVERTEX* Receive, CUSTOMVERTEX* Give);
	void MapScroolCheck();
	MapReverse* m_pMapReverse = NULL;
	Object* m_pMapChip = NULL;
	float CharTu = 80 / 512.f;
	float CharTv = 160 / 512.f;
public:
	CUSTOMVERTEX GetDisplayCharaCoordinate(){return m_DisplayCharaCoordinate[4];}
	int GetMapCharaPositionX() { return MapLeftDirectionPosition; }
	int GetMapCharaPositionY() { return MapCharaPositionY; }
	void prevSaveMapCharaPos();
	void KeyOperation(KeyDirection vec);
	void CharaInforSave(int MapReverse1, Object* MapChip);
	void Update();
	void Render();
	GameChara(DirectX* pDirectX, Object* MapChip);
	~GameChara();
};
