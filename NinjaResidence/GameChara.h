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
	int GetMapCharaPositionX() { return MapLeftDirectionPosition; }
	int GetMapCharaPositionY() { return MapCharaPositionY; }
	void prevSaveMapCharaPos();
	void KeyOperation(KeyInput vec);
	void CharaInforSave(int MapReverse1, Object* MapChip);
	void Update();
	void Render();
	GameChara(DirectX* pDirectX, SoundsManager* pSoundManager, Object* MapChip);
	~GameChara();
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
		return Facing;
	}
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

	PlayerAnimation::MOTION ChangeAnimation = PlayerAnimation::STAND;
	PlayerAnimation::DIRECTION Facing = PlayerAnimation::FACING_RIGHT;
	//! ���u���ϐ�
	PlayerAnimation::DIRECTION_BIAS Bias = PlayerAnimation::ZERO;


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


	void CharaMoveOperation(KeyInput vec);
	void ValueAllSetCUSTOMVERTEX(CUSTOMVERTEX* Receive, CUSTOMVERTEX* Give);
	void MapScroolCheck();

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
