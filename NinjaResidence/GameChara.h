/**
* @file GameChara.h
* @brief GameChara�N���X
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
	//Debug�p����
	void DebugMove();


private:
	enum MOTION {
		STANDBY,
		DASH,
		STAND,
		JUMPING,
		WALLHOLD,
		THROW,
	};
	enum DIRECTION {
		FACING_RIGHT = 1,
		FACING_LEFT = -1,
	};
	enum DIRECTION_BIAS {
		ZERO,
		ONE,
	};
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
	const float Gravity = 15.f;//���t���[��������d�͂̒l
	const float CharaMoveSpeed = 15.f;
	const float VerticalScrollingLevel = 5.f;

	const int DisplayCharMoveScopeUp = 100;//m_DisplayCharaCoordinate��Y���W�����̒l�������Ə�ɃX�N���[������
	const int DisplayCharMoveScopeDown = 630;//m_DisplayCharaCoordinate��Y���W�����̒l�𒴂���Ə�ɃX�N���[������
	const int DisplayCharMoveScopeLeft = 300;//m_DisplayCharaCoordinate��X���W�����̒l�������ƍ��ɃX�N���[������
	const int DisplayCharMoveScopeRight = 980;//m_DisplayCharaCoordinate��X���W�����̒l�𒴂���ƉE�ɃX�N���[������
	const int DisplayCharMoveScopeX = 300;//���[�����X���W�̉ғ��͈�

	MapReverse* m_pMapReverse = NULL;
	Object* m_pMapChip = NULL;
	float CharTu = 80 / 512.f;
	float CharTv = 160 / 512.f;

	//�������t�@�C���̐؂�����
	float TESTCharTu = 233 / 2048.f;
	float TESTCharTv = 215 / 2048.f;
	float TESTCharBias = 64 / 2024.f;
	MOTION ChangeAnimetion = STAND;
	DIRECTION Facing = FACING_RIGHT;
	DIRECTION_BIAS Bias = ZERO;

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
	float AccelerationX = CharaMoveSpeed * 1.5f;


	void CharaMoveOperation(KeyDirection vec);
	void ValueAllSetCUSTOMVERTEX(CUSTOMVERTEX* Receive, CUSTOMVERTEX* Give);
	void MapScroolCheck();
	bool PermitJumping();
	void Jump();
	void JumpingLateralMotion();
	void InitJumpParam();

	void WorldPositionModefy();
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
