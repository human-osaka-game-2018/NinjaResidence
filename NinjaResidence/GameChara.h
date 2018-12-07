/**
* @file GameChara.h
* @brief GameCharaクラス
* @author Kojiro Kawahara
*/
#pragma once

#include <vector>
#include "GAMESCENE.h"
#include "Object.h"
#include "MapChip.h"

class GameScene;
class MapReverse;


class GameChara :public Object
{
public:
	int GetMapCharaPositionX() { return MapLeftDirectionPosition; }
	int GetMapCharaPositionY() { return MapCharaPositionY; }
	void prevSaveMapCharaPos();
	void KeyOperation(KeyDirection vec);
	void CharaInforSave(int MapReverse1, Object* MapChip);
	void Update();
	void Render();
	GameChara(DirectX* pDirectX, SoundsManager* pSoundManager, Object* MapChip);
	~GameChara();
	//Debug用処理
	void DebugMove();

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
	const float Gravity = 15.f;//毎フレームかける重力の値
	const float CharaMoveSpeed = 15.f;
	const float VerticalScrollingLevel = 5.f;

	const int DisplayCharMoveScopeUp = 100;//m_DisplayCharaCoordinateのY座標がこの値を下回ると上にスクロールする
	const int DisplayCharMoveScopeDown = 630;//m_DisplayCharaCoordinateのY座標がこの値を超えると上にスクロールする
	const int DisplayCharMoveScopeLeft = 300;//m_DisplayCharaCoordinateのX座標がこの値を下回ると左にスクロールする
	const int DisplayCharMoveScopeRight = 980;//m_DisplayCharaCoordinateのX座標がこの値を超えると右にスクロールする
	const int DisplayCharMoveScopeX = 300;//両端からのX座標の稼働範囲

	MapReverse* m_pMapReverse = NULL;
	Object* m_pMapChip = NULL;
	float CharTu = 80 / 512.f;
	float CharTv = 160 / 512.f;

	bool isScrollingDown = false;
	bool isInTheAir = false;
	bool isJump = false;
	bool HeldOntoWallLeft = false;
	bool HeldOntoWallRight = false;
	bool CollisionHead = false;

	int RiseFlameTime = 0;
	bool isJumpRight = false;
	bool isJumpLeft = false;

	const float InitialAcceleration = 60.0f;
	float AccelerationY = InitialAcceleration;
	float AccelerationX = InitialAcceleration - CharaMoveSpeed;


	void CharaMoveOperation(KeyDirection vec);
	void ValueAllSetCUSTOMVERTEX(CUSTOMVERTEX* Receive, CUSTOMVERTEX* Give);
	void MapScroolCheck();
	bool PermitJumping();
	void Jump();
	void JumpingLateralMotion();
	void InitJumpParam();

	void AccelarationControl();
	
	void AddGravity();
	//bool StartJump();
	void BelowCollision();
	bool DownCollisionAnything(void);
	bool TopCollisionAnything(void);
	bool DownCollisionCheck(int block);
	bool TopCollisionCheck(int block);
	bool RightCollisionCheck(int block);
	bool LeftCollisionCheck(int block);
};
