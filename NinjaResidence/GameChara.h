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
	int m_PrevMapLeftDirectionPosition;//前フレームのMapLeftDirectionPositionの値
	int m_PrevMapRightDirectionPosition;//前フレームのMapRightDirectionPositionの値
	int m_PrevMapCharaPositionY;//前フレームのMapCharaPositionYの値
	int MapLeftDirectionPosition;//キャラの左側のX座標
	int MapRightDirectionPosition;//キャラの右側のX座標
	int MapCharaPositionY;//キャラの上側のx座標
	float Gravity;//毎フレームかける重力の値
	const int DisplayCharMoveScopeUp = 100;//m_DisplayCharaCoordinateのY座標がこの値を下回ると上にスクロールする
	const int DisplayCharMoveScopeDown = 630;//m_DisplayCharaCoordinateのY座標がこの値を超えると上にスクロールする
	const int DisplayCharMoveScopeLeft = 300;//m_DisplayCharaCoordinateのX座標がこの値を下回ると左にスクロールする
	const int DisplayCharMoveScopeRight = 980;//m_DisplayCharaCoordinateのX座標がこの値を超えると右にスクロールする
	const int DisplayCharMoveScopeX = 300;//両端からのX座標の稼働範囲
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
