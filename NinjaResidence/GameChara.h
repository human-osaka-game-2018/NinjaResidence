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
/**
* @namespace PlayerAnimation
* @author Toshiya Matsuoka
*/
namespace PlayerAnimation {
	enum MOTION {
		STANDBY,
		DASH,
		STAND,
		JUMPING,
		//! 壁掴まり
		WALLHOLD,
		THROWING,
	};
	enum DIRECTION {
		FACING_NOTHING = 0,
		//! param 1
		FACING_RIGHT = 1,
		//! param -1
		FACING_LEFT = -1,
	};
	//! アニメ用の仮列挙
	enum DIRECTION_BIAS {
		ZERO,
		ONE,
	};
};

class GameChara :public Object
{
public:
	CUSTOMVERTEX GetDisplayCharaCoordinate() { return m_DisplayCharaCoordinate[4]; }
	void prevSaveMapCharaPos();
	void KeyOperation(KeyDirection vec);
	void CharaInfoSave(Object* MapChip, int BlockNumber);
	bool Update();
	void Render();
	GameChara(DirectX* pDirectX, SoundOperater* pSoundOperater, Object* MapChip);
	~GameChara();

	int GetMapLeftDirectionPosition() { return m_MapLeftDirectionPosition; }
	int GetMapPositionY() { return m_MapPositionY; }

	//int GetMapCharaPositionX() { return m_MapLeftDirectionPosition; }

	void GimmickHitCheck();

	void NoOperation();
	/**
	* @brief Debug用キャラ上昇処理
	* @author Toshiya Matsuoka
	*/
	void DebugMove();

	/**
	* @brief キャラのディスプレイ上前端の取得
	* @author Toshiya Matsuoka
	*/
	float GetPositionX();
	bool SetGround();
	/**
	* @brief キャラのディスプレイ上中心Y座標の取得
	* @author Toshiya Matsuoka
	*/
	float GetPositionY() {
		return m_DisplayCharaCoordinate[0].y + (CELL_SIZE * 2);
	}

	/**
	* @brief キャラの向いている方向の取得
	* @sa PlayerAnimation::DIRECTION
	* @author Toshiya Matsuoka
	*/
	PlayerAnimation::DIRECTION GetFacing() {
		return m_Facing;
	}

private:
	CENTRAL_STATE m_Player = { 400,200,(CELL_SIZE * 2),(CELL_SIZE * 4) };
	CUSTOMVERTEX m_DisplayCharaCoordinate[4];
	CUSTOMVERTEX m_WorldCharaCoordinate[4];
	CUSTOMVERTEX m_ReverseDisplayCharaCoordinate[4];
	CUSTOMVERTEX m_ReverseWorldCharaCoordinate[4];
	CUSTOMVERTEX m_SurfaceDisplayCharaCoordinate[4];
	CUSTOMVERTEX m_SurfaceWorldCharaCoordinate[4];

	int m_PrevMapLeftDirectionPosition;//前フレームのm_MapLeftDirectionPositionの値
	int m_PrevMapRightDirectionPosition;//前フレームのm_MapRightDirectionPositionの値
	int m_PrevMapCharaPositionY;//前フレームのm_MapPositionYの値
	int m_MapLeftDirectionPosition;//キャラの左側のX座標
	int m_MapRightDirectionPosition;//キャラの右側のX座標
	int m_MapPositionY;//キャラの上側のx座標

	const float GRAVITY = 15.f;//毎フレームかける重力の値
	const float MOVE_SPEED = 15.f;
	const float VERTICAL_SCROLLING_LEVEL = 12.f;
	const int ScrollSpeed = 15;
	const int DisplayCharMoveScopeUp = 100;//m_DisplayCharaCoordinateのY座標がこの値を下回ると上にスクロールする
	const int DisplayCharMoveScopeDown = 630;//m_DisplayCharaCoordinateのY座標がこの値を超えると上にスクロールする
	const int DisplayCharMoveScopeLeft = 300;//m_DisplayCharaCoordinateのX座標がこの値を下回ると左にスクロールする
	const int DisplayCharMoveScopeRight = 980;//m_DisplayCharaCoordinateのX座標がこの値を超えると右にスクロールする
	const int DisplayCharMoveScopeX = 300;//両端からのX座標の稼働範囲


	//void CharaMoveOperation(KeyDirection vec, CUSTOMVERTEX* pWorldCharaCoordinate, CUSTOMVERTEX* pDisplayCharaCoordinate, float MoveQuantity);
	void MapReversePointSearch(int BlockNumber);
	void MapScroolCheck();
	float CharTu = 80 / 512.f;
	float CharTv = 160 / 512.f;
	MapReverse* m_pMapReverse = NULL;
	Object* m_pMapChip = NULL;
	float GravityAcceleration = 0;


	//仮統合ファイルの切り取り情報
	float m_TESTCharTu = 233 / 2048.f;
	float m_TESTCharTv = 215 / 2048.f;
	float m_TESTCharBias = 64 / 2024.f;

	PlayerAnimation::MOTION m_ChangeAnimation = PlayerAnimation::STAND;
	PlayerAnimation::DIRECTION m_Facing = PlayerAnimation::FACING_RIGHT;
	//! 仮置き変数
	PlayerAnimation::DIRECTION_BIAS m_Bias = PlayerAnimation::ZERO;


	bool m_isScrollingDown = false;
	bool m_isInTheAir = false;
	bool m_isJump = false;
	bool m_HeldOntoWallLeft = false;
	bool m_HeldOntoWallRight = false;
	bool m_CollisionHead = false;

	int m_RiseFlameTime = 0;
	bool m_isJumpRight = false;
	bool m_isJumpLeft = false;

	const float InitialAcceleration = 60.0f;
	float m_AccelerationY = InitialAcceleration;
	float m_AccelerationX = MOVE_SPEED * 1.5f;


	void CharaMoveOperation(KeyDirection vec);
	void ValueAllSetCUSTOMVERTEX(CUSTOMVERTEX* Receive, CUSTOMVERTEX* Give);

	/**
	* @breaf ジャンプの起動
	* @return ジャンプが起動すればtrue
	* @author Toshiya Matsuoka
	*/
	bool PermitJumping();
	/**
	* @breaf ジャンプの動作
	* @author Toshiya Matsuoka
	*/
	void Jump();
	/**
	* @breaf 壁ジャンプ用横移動処理
	* @author Toshiya Matsuoka
	*/
	void JumpingLateralMotion();
	/**
	* @breaf ジャンプの動作変数の初期化
	* @author Toshiya Matsuoka
	*/
	void InitJumpParam();
	/**
	* @breaf ジャンプの上昇量調整
	* @author Toshiya Matsuoka
	*/
	void AccelarationControl();

	/**
	* @breaf 投擲アニメ処理
	* @author Toshiya Matsuoka
	*/
	void ThrowAnime();

	/**
	* @breaf 課重力処理
	* @author Toshiya Matsuoka
	*/
	void AddGravity();
	/**
	* @breaf 下に対する何かしらの当たり判定
	* @return 当たっていればtrue
	* @author Toshiya Matsuoka
	*/
	bool DownCollisionAnything(void);
	/**
	* @breaf 上に対する何かしらの当たり判定
	* @return 当たっていればtrue
	* @author Toshiya Matsuoka
	*/
	bool TopCollisionAnything(void);
	/**
	* @breaf 下方向に対する当たり判定
	* @param block 指定のブロック番号
	* @return 当たっていればtrue
	* @sa  MapBlock::BLOCKTYPE
	* @author Toshiya Matsuoka
	*/
	bool DownCollisionCheck(int block);
	/**
	* @breaf 上方向に対する当たり判定
	* @param block 指定のブロック番号
	* @return 当たっていればtrue
	* @sa  MapBlock::BLOCKTYPE
	* @author Toshiya Matsuoka
	*/
	bool TopCollisionCheck(int block);
	/**
	* @breaf 右方向に対する当たり判定
	* @param block 指定のブロック番号
	* @return 当たっていればtrue
	* @sa  MapBlock::BLOCKTYPE
	* @author Toshiya Matsuoka
	*/
	bool RightCollisionCheck(int block);
	/**
	* @breaf 左方向に対する当たり判定
	* @param block 指定のブロック番号
	* @return 当たっていればtrue
	* @sa  MapBlock::BLOCKTYPE
	* @author Toshiya Matsuoka
	*/
	bool LeftCollisionCheck(int block);

};
