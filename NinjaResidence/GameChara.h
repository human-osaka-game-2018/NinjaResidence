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
		//! �ǒ͂܂�
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
	//! �A�j���p�̉���
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
	* @brief Debug�p�L�����㏸����
	* @author Toshiya Matsuoka
	*/
	void DebugMove();

	/**
	* @brief �L�����̃f�B�X�v���C��O�[�̎擾
	* @author Toshiya Matsuoka
	*/
	float GetPositionX();
	bool SetGround();
	/**
	* @brief �L�����̃f�B�X�v���C�㒆�SY���W�̎擾
	* @author Toshiya Matsuoka
	*/
	float GetPositionY() {
		return m_DisplayCharaCoordinate[0].y + (CELL_SIZE * 2);
	}

	/**
	* @brief �L�����̌����Ă�������̎擾
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

	int m_PrevMapLeftDirectionPosition;//�O�t���[����m_MapLeftDirectionPosition�̒l
	int m_PrevMapRightDirectionPosition;//�O�t���[����m_MapRightDirectionPosition�̒l
	int m_PrevMapCharaPositionY;//�O�t���[����m_MapPositionY�̒l
	int m_MapLeftDirectionPosition;//�L�����̍�����X���W
	int m_MapRightDirectionPosition;//�L�����̉E����X���W
	int m_MapPositionY;//�L�����̏㑤��x���W

	const float GRAVITY = 15.f;//���t���[��������d�͂̒l
	const float MOVE_SPEED = 15.f;
	const float VERTICAL_SCROLLING_LEVEL = 12.f;
	const int ScrollSpeed = 15;
	const int DisplayCharMoveScopeUp = 100;//m_DisplayCharaCoordinate��Y���W�����̒l�������Ə�ɃX�N���[������
	const int DisplayCharMoveScopeDown = 630;//m_DisplayCharaCoordinate��Y���W�����̒l�𒴂���Ə�ɃX�N���[������
	const int DisplayCharMoveScopeLeft = 300;//m_DisplayCharaCoordinate��X���W�����̒l�������ƍ��ɃX�N���[������
	const int DisplayCharMoveScopeRight = 980;//m_DisplayCharaCoordinate��X���W�����̒l�𒴂���ƉE�ɃX�N���[������
	const int DisplayCharMoveScopeX = 300;//���[�����X���W�̉ғ��͈�


	//void CharaMoveOperation(KeyDirection vec, CUSTOMVERTEX* pWorldCharaCoordinate, CUSTOMVERTEX* pDisplayCharaCoordinate, float MoveQuantity);
	void MapReversePointSearch(int BlockNumber);
	void MapScroolCheck();
	float CharTu = 80 / 512.f;
	float CharTv = 160 / 512.f;
	MapReverse* m_pMapReverse = NULL;
	Object* m_pMapChip = NULL;
	float GravityAcceleration = 0;


	//�������t�@�C���̐؂�����
	float m_TESTCharTu = 233 / 2048.f;
	float m_TESTCharTv = 215 / 2048.f;
	float m_TESTCharBias = 64 / 2024.f;

	PlayerAnimation::MOTION m_ChangeAnimation = PlayerAnimation::STAND;
	PlayerAnimation::DIRECTION m_Facing = PlayerAnimation::FACING_RIGHT;
	//! ���u���ϐ�
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
	* @breaf �W�����v�̋N��
	* @return �W�����v���N�������true
	* @author Toshiya Matsuoka
	*/
	bool PermitJumping();
	/**
	* @breaf �W�����v�̓���
	* @author Toshiya Matsuoka
	*/
	void Jump();
	/**
	* @breaf �ǃW�����v�p���ړ�����
	* @author Toshiya Matsuoka
	*/
	void JumpingLateralMotion();
	/**
	* @breaf �W�����v�̓���ϐ��̏�����
	* @author Toshiya Matsuoka
	*/
	void InitJumpParam();
	/**
	* @breaf �W�����v�̏㏸�ʒ���
	* @author Toshiya Matsuoka
	*/
	void AccelarationControl();

	/**
	* @breaf �����A�j������
	* @author Toshiya Matsuoka
	*/
	void ThrowAnime();

	/**
	* @breaf �ۏd�͏���
	* @author Toshiya Matsuoka
	*/
	void AddGravity();
	/**
	* @breaf ���ɑ΂��鉽������̓����蔻��
	* @return �������Ă����true
	* @author Toshiya Matsuoka
	*/
	bool DownCollisionAnything(void);
	/**
	* @breaf ��ɑ΂��鉽������̓����蔻��
	* @return �������Ă����true
	* @author Toshiya Matsuoka
	*/
	bool TopCollisionAnything(void);
	/**
	* @breaf �������ɑ΂��铖���蔻��
	* @param block �w��̃u���b�N�ԍ�
	* @return �������Ă����true
	* @sa  MapBlock::BLOCKTYPE
	* @author Toshiya Matsuoka
	*/
	bool DownCollisionCheck(int block);
	/**
	* @breaf ������ɑ΂��铖���蔻��
	* @param block �w��̃u���b�N�ԍ�
	* @return �������Ă����true
	* @sa  MapBlock::BLOCKTYPE
	* @author Toshiya Matsuoka
	*/
	bool TopCollisionCheck(int block);
	/**
	* @breaf �E�����ɑ΂��铖���蔻��
	* @param block �w��̃u���b�N�ԍ�
	* @return �������Ă����true
	* @sa  MapBlock::BLOCKTYPE
	* @author Toshiya Matsuoka
	*/
	bool RightCollisionCheck(int block);
	/**
	* @breaf �������ɑ΂��铖���蔻��
	* @param block �w��̃u���b�N�ԍ�
	* @return �������Ă����true
	* @sa  MapBlock::BLOCKTYPE
	* @author Toshiya Matsuoka
	*/
	bool LeftCollisionCheck(int block);

};
