﻿/**
* @file GameChara.cpp
* @brief GameCharaクラス
* @author Kojiro Kawahara
*/
#include "GameChara.h"

using  namespace MapBlock;
using namespace PlayerAnimation;

GameChara::GameChara(DirectX* pDirectX, SoundOperater* pSoundOperater, Object* MapChip) :Object(pDirectX, pSoundOperater)
{
	m_Central = { 400,200,(CELL_SIZE * 2),(CELL_SIZE * 4) };

	//MapChipの情報を取得するために必要
	m_pMapChip = MapChip;
	m_row = m_pMapChip->GetRow();
	m_colunm = m_pMapChip->GetColunm();
	m_Central.x = static_cast<float>(m_pMapChip->SearchBlockX(START_ZONE))*CELL_SIZE;
	m_Central.y = static_cast<float>(m_pMapChip->SearchBlockY(START_ZONE))*CELL_SIZE;
	CreateSquareVertex(m_Central, m_WorldCoordinate, 0xFFFFFFFF, 0, 0, m_CollisionTu, m_CollisionTv);
	CreateSquareVertex(m_Central, m_DisplayCoordinate, 0xFFFFFFFF, 0, 0, m_CollisionTu, m_CollisionTv);
	int ScrollXBuf = 0;
	int ScrollYBuf = 0;
	int ScrollBehindX = 0;
	int ScrollBehindY = 0;
	do {
		for (int i = 0; i < 4; i++)
		{
			m_DisplayCoordinate[i].y = m_WorldCoordinate[i].y + m_MapScrollY;
			m_DisplayCoordinate[i].x = m_WorldCoordinate[i].x + m_MapScrollX;
		}

		ScrollXBuf = m_MapScrollX;
		ScrollYBuf = m_MapScrollY;

		MapScrool();
		ScrollBehindX = (m_MapScrollX - ScrollXBuf);
		ScrollBehindY = (m_MapScrollY - ScrollYBuf);

	} while (0 != ScrollBehindX || 0 != ScrollBehindY);

}

GameChara::~GameChara()
{
	m_MapScrollX = 0;
	m_MapScrollY = 0;
}

void GameChara::InitJumpParam() {
	m_isJump = false;
	m_isJumpRight = false;
	m_isJumpLeft = false;
	m_AccelerationY = InitialAcceleration;
	//m_AccelerationX = InitialAcceleration;
	m_RiseFlameTime = 0;
}
void GameChara::AccelarationControl() {
	m_AccelerationY -= 2.f;

}
bool GameChara::PermitJumping() {
	//壁ジャンプ判定の為
	m_MapLeftDirectionPosition -= 1;
	m_MapRightDirectionPosition += 1;
	m_HeldOntoWallLeft = !LeftCollisionCheck(NONE) && (LeftCollisionCheck(START_ZONE) || !LeftCollisionCheck(START_ZONE));
	m_HeldOntoWallRight = !RightCollisionCheck(NONE) && (RightCollisionCheck(START_ZONE) || !RightCollisionCheck(START_ZONE));


	if (!m_isInTheAir) {
		m_pSoundOperater->Start("JUMP", false);
		return true;
	}
	else if (m_HeldOntoWallLeft || m_HeldOntoWallRight) {
		m_pSoundOperater->Start("JUMP", false);
		return true;
	}
	return false;
}
void GameChara::Jump()
{
	if (!m_isJump) {
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		m_DisplayCoordinate[i].y -= m_AccelerationY;
		m_WorldCoordinate[i].y -= m_AccelerationY;
	}
	SideCollision();
	TopCollision();

	if (m_DisplayCoordinate[0].y < 0) {
		m_WorldCoordinate[0].y = 0.1f;
		m_WorldCoordinate[1].y = 0.1f;
		m_WorldCoordinate[2].y = m_Central.scale_y + 0.1f;
		m_WorldCoordinate[3].y = m_Central.scale_y + 0.1f;
		InitJumpParam();
		return;
	}
	UpdateMapPos();
	if (!m_isUsingArt) {
		m_ChangeAnimation = JUMPING;
	}
	m_TurnAnimation = 0.f;
	static int AnimeCount = 0;
	++AnimeCount;
	if (AnimeCount > 3) {
		m_TurnAnimation = 1.f;
	}
	if (m_RiseFlameTime < 15) {
		JumpingLateralMotion();
		m_RiseFlameTime++;
		AccelarationControl();
		return;
	}
	AnimeCount = 0;

	InitJumpParam();
}

void GameChara::JumpingLateralMotion() {

	if (!m_isInTheAir) {
		m_HeldOntoWallLeft = m_HeldOntoWallRight = false;
		return;
	}

	if (m_HeldOntoWallLeft) {
		m_isJumpRight = true;
	}
	if (m_HeldOntoWallRight) {
		m_isJumpLeft = true;
	}

	if (m_isJumpRight) {
		//右に移動
		for (int i = 0; i < 4; i++)
		{
			m_WorldCoordinate[i].x += m_AccelerationX;
			m_DisplayCoordinate[i].x += m_AccelerationX;
		}
		SideCollision();
		TopCollision();
	}
	if (m_isJumpLeft) {
		//左に移動
		for (int i = 0; i < 4; i++)
		{
			m_WorldCoordinate[i].x -= m_AccelerationX;
			m_DisplayCoordinate[i].x -= m_AccelerationX;
		}
		SideCollision();
		TopCollision();

	}
}

void GameChara::MoveOperation(KeyDirection vec)
{
	switch (vec)
	{
		//上に移動
	case JUMP:

		m_isJump = PermitJumping();
		break;
	case DOWN:
		//今のところなし

		break;
	case MOVE_RIGHT:
		//右に移動
		m_Facing = FACING_RIGHT;
		m_DirectionBias = ZERO;
		Dash();
		break;
	case MOVE_LEFT:
		//左に移動
		m_Facing = FACING_LEFT;
		m_DirectionBias = ONE;
		Dash();
		break;
	case INERTIA:
		m_isInertiaMoving = true;
		break;
	}
}

void GameChara::Dash()
{
	static int AnimeCount = 0;

	for (int i = 0; i < 4; i++)
	{
		m_WorldCoordinate[i].x += MOVE_SPEED * static_cast<float>(m_Facing);
		m_DisplayCoordinate[i].x += MOVE_SPEED * static_cast<float>(m_Facing);
	}
	SideCollision();
	if (m_isInTheAir) return;
	if (m_ChangeAnimation == WATER_ART) {
		m_TurnAnimation = 3.f;
		return;
	}
	if (SoundLib::Playing != m_pSoundOperater->GetStatus("DASH")) {
		m_pSoundOperater->Start("DASH");
	}
	m_ChangeAnimation = DASH;
	++AnimeCount;
	if (AnimeCount > 2) {
		TurnTheAnimation(8);
		AnimeCount = 0;
	}

}

void GameChara::PrevSaveMapPos()
{
	m_PrevMapLeftDirectionPosition = static_cast<int>(m_WorldCoordinate[3].x);
	m_PrevMapRightDirectionPosition = static_cast<int>(m_WorldCoordinate[2].x);
	m_PrevMapCharaPositionY = static_cast<int>(m_WorldCoordinate[3].y) + 10;
}

void GameChara::KeyOperation(KeyDirection vec)
{
	//Key操作での処理
	switch (vec)
	{
		m_isFire = false;
		m_isUsingArt = false;
	case JUMP:
		MoveOperation(JUMP);
		break;
	case DOWN:
		//今のところ無し
		break;
	case MOVE_RIGHT:
		//右に移動
		MoveOperation(MOVE_RIGHT);
		break;
	case MOVE_LEFT:
		//左に移動
		MoveOperation(MOVE_LEFT);
		break;
	case SoundOn:
		m_pSoundOperater->Start("DECISION");
		break;
	case PUSH_NONE:
		NoOperation();
		break;
	case THROW:
		m_ChangeAnimation = THROWING;
		m_isUsingArt = true;
		break;
	case FIRE:
		m_ChangeAnimation = FIREART;
		m_isUsingArt = true;
		m_isFire = true;
		break;
	case INERTIA:
		m_isInertiaMoving = true;
		break;
	case MAP_RIGHT:
		if (m_DisplayCoordinate[0].x > DisplayCharMoveScopeLeft)
		{
			m_MapScrollX -= 5;
			if ((m_DisplayCoordinate[1].x < DISPLAY_WIDTH))
			{
				for (int i = 0; i < 4; ++i) {
					m_DisplayCoordinate[i].x = m_WorldCoordinate[i].x + m_MapScrollX;
				}
			}
		}
		break;
	case MAP_LEFT:

		if (m_MapScrollX >= 0) {
			m_MapScrollX = 0;
			break;
		}
		if (m_DisplayCoordinate[1].x < DisplayCharMoveScopeRight)
		{
			m_MapScrollX += 5;
			if ((m_DisplayCoordinate[1].x > 0))
			{
				for (int i = 0; i < 4;++i) {
					m_DisplayCoordinate[i].x = m_WorldCoordinate[i].x + m_MapScrollX;
				}
			}
		}
		break; 
	case MAP_DOWN:
		if (m_DisplayCoordinate[0].y < DisplayCharMoveScopeDown)
		{
			m_MapScrollY -= 5;
			if ((m_DisplayCoordinate[1].y < DISPLAY_HEIGHT))
			{
				for (int i = 0; i < 4; ++i) {
					m_DisplayCoordinate[i].y = m_WorldCoordinate[i].y + m_MapScrollY;
				}
			}
			if (m_MapScrollY < static_cast<int>((CELL_SIZE*-m_colunm))) {
				m_MapScrollY = static_cast<int>((CELL_SIZE*-m_colunm));
			}
		}
		break;
	case MAP_UP:
		if (m_DisplayCoordinate[0].y > DisplayCharMoveScopeUp)
		{
			m_MapScrollY += 5;
			if ((m_DisplayCoordinate[1].y > 0))
			{
				for (int i = 0; i < 4; ++i) {
					m_DisplayCoordinate[i].y = m_WorldCoordinate[i].y + m_MapScrollY;
				}
			}
			if (m_MapScrollY >0) {
				m_MapScrollY = 0;
			}
		}
		break;
	}
}

void GameChara::NoOperation() {
	if (DownCollisionAnything()) {
		m_ChangeAnimation = STAND;
		static int AnimeCount = 0;
		++AnimeCount;
		if (AnimeCount > 10) {
			TurnTheAnimation(3);
			AnimeCount = 0;
		}

	}

}

void GameChara::MapReversePointSearch(int PairNumber, MapDataState MapState)
{
	int BlockY = 0;
	int BlockX = 0;
	int ScrollXBuf = 0;
	int ScrollYBuf = 0;
	int ScrollBehindX = 0;
	int ScrollBehindY = 0;
	for (unsigned int i = 0; i < m_ReversePoint.size(); ++i) {
		bool isSameMapState = m_ReversePoint[i].MapDataState == MapState;
		bool isSamePair = PairNumber == m_ReversePoint[i].PairNumber;
		if (isSameMapState && isSamePair) {
			BlockY = m_ReversePoint[i].PositionY;
			BlockX = m_ReversePoint[i].PositionX;
			break;
		}
	}

	m_WorldCoordinate[0].x = (BlockX * CELL_SIZE);
	m_WorldCoordinate[1].x = (BlockX * CELL_SIZE) + m_Central.scale_x;
	m_WorldCoordinate[2].x = (BlockX * CELL_SIZE) + m_Central.scale_x;
	m_WorldCoordinate[3].x = (BlockX * CELL_SIZE);

	m_WorldCoordinate[0].y = (BlockY * CELL_SIZE) - m_Central.scale_y;
	m_WorldCoordinate[1].y = (BlockY * CELL_SIZE) - m_Central.scale_y;
	m_WorldCoordinate[2].y = (BlockY * CELL_SIZE);
	m_WorldCoordinate[3].y = (BlockY * CELL_SIZE);
	UpdateMapPos();

	do {
		for (int i = 0; i < 4; i++)
		{
			m_DisplayCoordinate[i].y = m_WorldCoordinate[i].y + m_MapScrollY;
			m_DisplayCoordinate[i].x = m_WorldCoordinate[i].x + m_MapScrollX;
		}
		ScrollXBuf = m_MapScrollX;
		ScrollYBuf = m_MapScrollY;

		MapScrool();
		SetGround();
		ScrollBehindX = (m_MapScrollX - ScrollXBuf);
		ScrollBehindY = (m_MapScrollY - ScrollYBuf);

	} while (0 != ScrollBehindX || 0 != ScrollBehindY);
}


void GameChara::PositionSave(Object* MapChip, int PairNumber)
{
	m_pMapChip = MapChip;
	m_colunm = m_pMapChip->GetColunm();
	m_row = m_pMapChip->GetRow();
	MapReversePointSearch(PairNumber,m_pMapChip->GetMapDataState());
}


void GameChara::UpdateMapPos()
{
	m_MapLeftDirectionPosition = static_cast<int>(m_WorldCoordinate[3].x / CELL_SIZE);
	m_MapRightDirectionPosition = static_cast<int>((m_WorldCoordinate[2].x) / CELL_SIZE);
	m_MapPositionY = static_cast<int>((m_WorldCoordinate[3].y + 10.f) / CELL_SIZE);
	if (m_MapPositionY >= m_colunm) {
		m_MapPositionY = m_colunm - 1;
	}
}

void GameChara::MapScrool()
{
	//下にスクロール移動
	if (m_DisplayCoordinate[3].y > static_cast<float>(DisplayCharMoveScopeDown))
	{
		m_DisplayCoordinate[0].y = (static_cast<float>(DisplayCharMoveScopeDown) - m_Central.scale_y);
		m_DisplayCoordinate[1].y = (static_cast<float>(DisplayCharMoveScopeDown) - m_Central.scale_y);
		m_DisplayCoordinate[2].y = (static_cast<float>(DisplayCharMoveScopeDown));
		m_DisplayCoordinate[3].y = (static_cast<float>(DisplayCharMoveScopeDown));
		m_MapScrollY -= VERTICAL_SCROLLING_LEVEL;
		UpdateMapPos();
		if (m_MapScrollY < -1 * m_WorldCoordinate[0].y + m_DisplayCoordinate[0].y){
			m_MapScrollY = -1 * m_WorldCoordinate[0].y + m_DisplayCoordinate[0].y;
		}
		m_isScrollingDown = true;
	}
	else m_isScrollingDown = false;
	//上にスクロール移動
	if (m_DisplayCoordinate[1].y < static_cast<float>(DisplayCharMoveScopeUp))
	{
		if (m_WorldCoordinate[0].y >= static_cast<float>(DisplayCharMoveScopeUp))
		{
			m_DisplayCoordinate[0].y = (static_cast<float>(DisplayCharMoveScopeUp));
			m_DisplayCoordinate[1].y = (static_cast<float>(DisplayCharMoveScopeUp));
			m_DisplayCoordinate[2].y = (static_cast<float>(DisplayCharMoveScopeUp) + m_Central.scale_y);
			m_DisplayCoordinate[3].y = (static_cast<float>(DisplayCharMoveScopeUp) + m_Central.scale_y);
			m_MapScrollY += VERTICAL_SCROLLING_LEVEL;
		}
	}

	//右にスクロール移動
	if (m_DisplayCoordinate[1].x > static_cast<float>(DisplayCharMoveScopeRight))
	{
		if ((m_WorldCoordinate[1].x <= (((m_row-1) * CELL_SIZE) - static_cast<float>(DisplayCharMoveScopeX)))||(m_WorldCoordinate[1].x>DISPLAY_WIDTH))
		{
			m_DisplayCoordinate[0].x = (static_cast<float>(DisplayCharMoveScopeRight) - m_Central.scale_x);
			m_DisplayCoordinate[1].x = (static_cast<float>(DisplayCharMoveScopeRight));
			m_DisplayCoordinate[2].x = (static_cast<float>(DisplayCharMoveScopeRight));
			m_DisplayCoordinate[3].x = (static_cast<float>(DisplayCharMoveScopeRight) - m_Central.scale_x);
			m_MapScrollX -= ScrollSpeed;
		}
	}
	//左にスクロール移動
	if (m_DisplayCoordinate[0].x < static_cast<float>(DisplayCharMoveScopeLeft))
	{
		if (m_WorldCoordinate[0].x >= static_cast<float>(DisplayCharMoveScopeX) || (m_WorldCoordinate[1].x<0))
		{
			m_DisplayCoordinate[0].x = (static_cast<float>(DisplayCharMoveScopeLeft));
			m_DisplayCoordinate[1].x = (static_cast<float>(DisplayCharMoveScopeLeft) + m_Central.scale_x);
			m_DisplayCoordinate[2].x = (static_cast<float>(DisplayCharMoveScopeLeft) + m_Central.scale_x);
			m_DisplayCoordinate[3].x = (static_cast<float>(DisplayCharMoveScopeLeft));
			m_MapScrollX += ScrollSpeed;
		}
	}

}

void GameChara::TurnTheAnimation(int AnimationPage)
{
	if (m_TurnAnimation < AnimationPage - 1) {
		m_TurnAnimation += 1.f;
	}
	else m_TurnAnimation = 0;
}

void GameChara::ThrowAnime() {
	static bool AnimeOn = false;
	static int AnimationCount = 0;

	if (m_ChangeAnimation == THROWING) {

		AnimeOn = true;
	}
	if (AnimeOn) {
		AnimationCount++;
		static int AnimeCount = 0;
		++AnimeCount;
		if (AnimeCount > 2) {
			TurnTheAnimation(6);
			AnimeCount = 0;
		}
	}
	else return;
	if (m_TurnAnimation!=0) {
		m_ChangeAnimation = THROWING;
	}
	else {
		m_pSoundOperater->Start("SHURIKEN", false);
		AnimationCount = 0;
		AnimeOn = false;
		m_ChangeAnimation = STAND;
	}
}

void GameChara::FireArtAnime() {
	static bool AnimeOn = false;

	if (m_isFire) {
		static int AnimeCount = 0;
		++AnimeCount;
		if (AnimeCount > 2) {
			if (m_TurnAnimation > 2) {
				static bool anime = true;
				m_TurnAnimation += ((anime) ? 0 : -1);
				anime = !anime;
			}
			else m_TurnAnimation++;
			AnimeCount = 0;
		}
	}
}

bool GameChara::Update()
{
	ThrowAnime();
	UpdateMapPos();
	AddGravity();
	MapScrool();
	SideCollision();
	if (!(m_isInTheAir = !SetGround()) && TopCollision()) {
		m_WorldCoordinate[0].y = static_cast<float>(m_PrevMapCharaPositionY) + 10.f - m_Central.y;
		m_WorldCoordinate[1].y = static_cast<float>(m_PrevMapCharaPositionY) + 10.f - m_Central.y;
		m_WorldCoordinate[2].y = static_cast<float>(m_PrevMapCharaPositionY) + 10.f;
		m_WorldCoordinate[3].y = static_cast<float>(m_PrevMapCharaPositionY) + 10.f;
		SideCollision();
	}
	if (m_isInertiaMoving) {
		MoveInertia();
	}
	if (!m_CollisionHead) {
		Jump();
		MapScrool();
		TopCollision();
		SideCollision();
		SetGround();
	}
	else if (m_isJump) {
		InitJumpParam();
	}

	if (m_pMapChip->GetMapChipData(m_MapPositionY - 2, m_MapRightDirectionPosition) > 100)
	{

		//m_pMapChip->Activate(m_MapRightDirectionPosition, m_MapPositionY - 2);

	}
	if (LeftCollisionCheck(GOAL_ZONE) || TopCollisionCheck(GOAL_ZONE) || DownCollisionCheck(GOAL_ZONE) || RightCollisionCheck(GOAL_ZONE)) {
		return true;
	}
	if (FailureGame()) {
		m_GameFailure = true;
	}
	return false;
}

bool GameChara::DownCollisionAnything(void) {
	int D_Buf = 0;
	if (m_MapPositionY < 0 && m_MapLeftDirectionPosition < 0) {
		return false;
	}
	if (DownCollisionCheck(START_ZONE)) {
		return false;
	}
	//for (NULL; NULL;NULL) {
	//	if (DownCollisionCheck(WOOD_BLOCK)) {
	//		return true;
	//	}
	//}
	bool TorchMin = ((D_Buf = m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition) >= 400) ||
		(m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 1) >= 400) ||
		(m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 2) >= 400));
	bool TorchMax = ((m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition) < 500) ||
		(m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 1) < 500) ||
		(m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 2) < 500));
	if (TorchMax && TorchMin&&D_Buf >100) {
		return false;
	}
	bool TargetMin = ((m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition) >= 100) ||
		(m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 1) >= 100) ||
		((D_Buf = m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 2)) >= 100));
	bool TargetMax = ((m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition) < 300) ||
		(m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 1) < 300) ||
		(m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 2) < 300));
	if (TargetMax && TargetMin&&D_Buf >100&& D_Buf <1100) {
		return false;
	}
	bool ReverseCollLeft = (m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition) < 1300) && (m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition) >= 1100);
	bool ReverseCollRight = (m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 1) < 1300) && (m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 1) >= 1100);
	bool ReverseCollCenter = (m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 2) < 1300) && (m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 2) >= 1100);

	//bool BlockMax = ((D_Buf = m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition)) < 100) ||
	//	(m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 1) < 100) ||
	//	((m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 2)) < 100);
	//bool BlockMin = ((m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition) > 0) ||
	//	(m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 1) > 0) ||
	//	(m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 2) > 0));
	bool CollLeft = (m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition) < 100)&& (m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition) > 0);
	bool CollRight = (m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition+1) < 100)&& (m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition+1) > 0);
	bool CollCenter =(m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition+2) < 100)&& (m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition+2) > 0);
	if ((CollLeft || CollRight || CollCenter)|| (ReverseCollLeft || ReverseCollRight || ReverseCollCenter)){
		return true;
	}

	bool WaterMax = ((m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition) < 800) ||
		(m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 1) < 800) ||
		(m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 2) < 800));
	bool WaterMin = ((m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition) >= 700) ||
		(m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 1) >= 700) ||
		(m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 2) >= 700));
	if (WaterMax && WaterMin) {
		m_ChangeAnimation = WATER_ART;
		if (m_isInTheAir) {
			m_pSoundOperater->Start("SET_DOWN_WATER", false);
		}
		return true;
	}

	if (DownCollisionCheck(NONE)) {
		return false;
	}

	return true;
}
bool GameChara::TopCollisionAnything(void) {
	if (!TopCollisionCheck(NONE)&&
		TopCollisionCheck(START_ZONE)) {
		return true;
	}
	return false;
}
bool GameChara::DownCollisionCheck(int block) {
	if ((m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition) == block) ||
		(m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 1) == block) ||
		(m_pMapChip->GetMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 2) == block)) {
		return true;
	}
	return false;
}
bool GameChara::TopCollisionCheck(int block) {
	if ((m_pMapChip->GetMapChipData(m_MapPositionY - 4, m_MapLeftDirectionPosition) == block) ||
		(m_pMapChip->GetMapChipData(m_MapPositionY - 4, m_MapLeftDirectionPosition + 1) == block) ||
		(m_pMapChip->GetMapChipData(m_MapPositionY - 4, m_MapLeftDirectionPosition + 2) == block)) {
		return true;
	}
	return false;
}

bool GameChara::LeftCollisionCheck(int block) {
	//if (m_MapLeftDirectionPosition <= 0) {
	//	m_MapLeftDirectionPosition = 1;
	//}
	if ((m_pMapChip->GetMapChipData(m_MapPositionY - 1, m_MapLeftDirectionPosition) == block) ||
		(m_pMapChip->GetMapChipData(m_MapPositionY - 2, m_MapLeftDirectionPosition) == block) ||
		(m_pMapChip->GetMapChipData(m_MapPositionY - 3, m_MapLeftDirectionPosition) == block) ||
		(m_pMapChip->GetMapChipData(m_MapPositionY - 4, m_MapLeftDirectionPosition) == block)) {
		return true;
	}
	return false;
}
bool GameChara::RightCollisionCheck(int block) {
	if (m_MapRightDirectionPosition >= m_row) {
		m_MapRightDirectionPosition -= 1;
	}
	if ((m_pMapChip->GetMapChipData(m_MapPositionY - 1, m_MapRightDirectionPosition) == block) ||
		(m_pMapChip->GetMapChipData(m_MapPositionY - 2, m_MapRightDirectionPosition) == block) ||
		(m_pMapChip->GetMapChipData(m_MapPositionY - 3, m_MapRightDirectionPosition) == block) ||
		(m_pMapChip->GetMapChipData(m_MapPositionY - 4, m_MapRightDirectionPosition) == block)) {
		return true;
	}
	return false;
}
bool GameChara::LookDownWater() {
	bool buf = false;
	for (int i = 0; i < m_colunm - m_MapPositionY - 1; ++i) {
		if (!buf) {
			buf = (BT_WATER == m_pMapChip->GetMapChipData(m_MapPositionY + i, m_MapLeftDirectionPosition) / 100);
		}
	}
	return buf;
}
float GameChara::WaterCollsionCheck()
{
	float PosY = 0;
	if (PosY = m_pMapChip->GetGimmickPosition(false, m_MapPositionY, m_MapLeftDirectionPosition)) {
		return PosY;
	}
	else return m_WorldCoordinate[2].y;
}
bool GameChara::FailureGame()
{
	if (LeftCollisionCheck(SPEAR)|| TopCollisionCheck(SPEAR) || DownCollisionCheck(SPEAR) || RightCollisionCheck(SPEAR)) {
		return true;
	}
	if (LeftCollisionCheck(STAGE_DROP_ZONE) || TopCollisionCheck(STAGE_DROP_ZONE) || DownCollisionCheck(STAGE_DROP_ZONE) || RightCollisionCheck(STAGE_DROP_ZONE)) {
		return true;
	}

	return false;
}

void GameChara::Render()
{
	CUSTOMVERTEX DebugColl[4];
#ifdef _DEBUG
	m_DisplayCoordinate[0].color = m_DisplayCoordinate[1].color = m_DisplayCoordinate[2].color = m_DisplayCoordinate[3].color = 0xFF010101;

	TextureRender("TEST_TEX", m_DisplayCoordinate);
	DebugColl[3].y = DebugColl[2].y = m_MapPositionY * CELL_SIZE + m_MapScrollY;
	DebugColl[0].y = DebugColl[1].y = DebugColl[3].y - CELL_SIZE;
	DebugColl[3].x = DebugColl[0].x = m_MapLeftDirectionPosition * CELL_SIZE + m_MapScrollX + CELL_SIZE / 2.f;
	DebugColl[1].x = DebugColl[2].x = m_MapRightDirectionPosition * CELL_SIZE + m_MapScrollX - CELL_SIZE / 2.f;
	DebugColl[0].color = DebugColl[1].color = DebugColl[2].color = DebugColl[3].color = 0xFFEFEFEF;
	TextureRender("TEST_TEX", DebugColl);
#endif
	CUSTOMVERTEX Chara[4];
	CENTRAL_STATE CharCentral = { 0 };
	TranslateCentral_State(&CharCentral, m_DisplayCoordinate);
	CharCentral.x -= 25.f;
	CharCentral.scale_x = 120.f;
	CreateSquareVertex(CharCentral, Chara, 0xFFFFFFFF,( m_TurnAnimation+m_DirectionBias) * TU, m_ChangeAnimation * TV, TU * m_Facing, TV);
	TextureRender("CHARA_TEX", Chara);

#ifdef _DEBUG

	RECT test = { 0,0,1250,500 };
	char TestText[ARRAY_LONG];
	sprintf_s(TestText, ARRAY_LONG, "MapChara::X-L:%d,X-R:%d,Y:%d", m_MapLeftDirectionPosition, m_MapRightDirectionPosition, m_MapPositionY);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_RIGHT, 0xffffffff);
	sprintf_s(TestText, ARRAY_LONG, "\nPrevMapChara::X-L:%d,X-R:%d,Y:%d", m_PrevMapLeftDirectionPosition, m_PrevMapRightDirectionPosition, m_PrevMapCharaPositionY);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_RIGHT, 0xffffffff);
	sprintf_s(TestText, ARRAY_LONG, "\n\nWorldChara::X-L:%.2f,X-R:%.2f,Y:%.2f", m_WorldCoordinate[3].x, m_WorldCoordinate[2].x, m_WorldCoordinate[3].y);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_RIGHT, 0xffffffff);
	sprintf_s(TestText, ARRAY_LONG, "\n\n\nDisplayChara::X-L:%.2f,X-R:%.2f,Y3:%.2f,Y0:%.2f", m_DisplayCoordinate[3].x, m_DisplayCoordinate[2].x, m_DisplayCoordinate[3].y, m_DisplayCoordinate[0].y);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_RIGHT, 0xffffffff);
	sprintf_s(TestText, ARRAY_LONG, "\n\n\n\n\n\nAccelerationY::%.2f", m_AccelerationY);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_RIGHT, 0xffffffff);
#endif

}

void GameChara::AddGravity() {
	//重力を毎フレームかける
	if (m_isScrollingDown) {
		for (int i = 0; i < 4; i++)
		{

			m_WorldCoordinate[i].y += VERTICAL_SCROLLING_LEVEL;
			m_DisplayCoordinate[i].y += VERTICAL_SCROLLING_LEVEL;
		}
		SideCollision();
		SetGround();
		return;
	}
	//if (!DownCollisionAnything()&& !LookDownWater())
	//{
	//	GravityAcceleration += 0.1f;
	//	
	//}
	//else GravityAcceleration = 0;

	for (int i = 0; i < 4; i++)
	{
		m_WorldCoordinate[i].y += GRAVITY + GravityAcceleration;
		m_DisplayCoordinate[i].y += GRAVITY + GravityAcceleration;
	}
}

void GameChara::DebugMove() {
	for (int i = 0; i < 4; i++)
	{
		m_WorldCoordinate[i].y -= MOVE_SPEED * 1.5f;
		m_DisplayCoordinate[i].y -= MOVE_SPEED * 1.5f;
	}
}

float GameChara::GetPositionX()
{
	switch (m_Facing) {
	case FACING_LEFT:
		return m_DisplayCoordinate[0].x;
	case FACING_RIGHT:
		return m_DisplayCoordinate[0].x + m_Central.scale_x;
	}
	return 0.f;
}

bool GameChara::SetGround() {
	static int AnimeCount = 0;

	if (DownCollisionAnything())
	{
		m_WorldCoordinate[0].y = ((m_MapPositionY - 4) * CELL_SIZE);
		m_WorldCoordinate[1].y = ((m_MapPositionY - 4) * CELL_SIZE);
		m_WorldCoordinate[2].y = ((m_MapPositionY)* CELL_SIZE);
		m_WorldCoordinate[3].y = ((m_MapPositionY)* CELL_SIZE);
		for (int i = 0; i < 4; i++)
		{
			m_DisplayCoordinate[i].y = m_WorldCoordinate[i].y + m_MapScrollY;
		}
		if (m_isInTheAir) {
			m_TurnAnimation = 0.f;
			m_pSoundOperater->Start("SET_DOWN", false);
		}
		return true;
	}
	else if (LookDownWater()) {
		if (!m_isJump) {
			float WaterUpperLevel = WaterCollsionCheck();
			if (m_DisplayCoordinate[2].y < WaterUpperLevel) {
				return false;
			}
			m_WorldCoordinate[2].y = WaterUpperLevel - m_MapScrollY;
			m_WorldCoordinate[3].y = WaterUpperLevel - m_MapScrollY;
			m_WorldCoordinate[0].y = WaterUpperLevel - m_MapScrollY - m_Central.scale_y;
			m_WorldCoordinate[1].y = WaterUpperLevel - m_MapScrollY - m_Central.scale_y;
			for (int i = 0; i < 4; i++)
			{
				m_DisplayCoordinate[i].y = m_WorldCoordinate[i].y + m_MapScrollY;
			}
			if (m_isInTheAir) {
				m_pSoundOperater->Start("SET_DOWN_WATER", false);
			}
		}
		m_ChangeAnimation = WATER_ART;
		static int AnimeCount = 0;
		++AnimeCount;
		if (AnimeCount > 10) {
			TurnTheAnimation(3);
			AnimeCount = 0;
		}
		return true;
	}
	else if (!m_isJump && !m_isUsingArt) {
		m_ChangeAnimation = JUMPING;
		if (AnimeCount % 3) {
			m_TurnAnimation = (AnimeCount % 2) ? 4.0f : 5.0f;
		}
		++AnimeCount;
		if (AnimeCount > 1000) {
			AnimeCount = 0;
		}

	}
	else if (m_isJump && !m_isUsingArt) {
		m_ChangeAnimation = JUMPING;
	}

	return false;
}

bool GameChara::TopCollision() {
	if (m_PrevMapCharaPositionY > m_WorldCoordinate[3].y + 10)
	{
		UpdateMapPos();
		bool CollLeft = (m_pMapChip->GetMapChipData(m_MapPositionY - 4, m_MapLeftDirectionPosition) < 100) && (m_pMapChip->GetMapChipData(m_MapPositionY - 4, m_MapLeftDirectionPosition) > 0);
		bool CollRight = (m_pMapChip->GetMapChipData(m_MapPositionY - 4, m_MapLeftDirectionPosition + 1) < 100) && (m_pMapChip->GetMapChipData(m_MapPositionY - 4, m_MapLeftDirectionPosition + 1) > 0);
		bool CollCenter = (m_pMapChip->GetMapChipData(m_MapPositionY - 4, m_MapLeftDirectionPosition + 2) < 100) && (m_pMapChip->GetMapChipData(m_MapPositionY - 4, m_MapLeftDirectionPosition + 2) > 0);
		if ((CollLeft || CollRight || CollCenter)) {
			m_WorldCoordinate[0].y = ((m_MapPositionY - 3) * CELL_SIZE);
			m_WorldCoordinate[1].y = ((m_MapPositionY - 3) * CELL_SIZE);
			m_WorldCoordinate[2].y = ((m_MapPositionY + 1) * CELL_SIZE);
			m_WorldCoordinate[3].y = ((m_MapPositionY + 1) * CELL_SIZE);
			for (int i = 0; i < 4; i++)
			{
				m_DisplayCoordinate[i].y = m_WorldCoordinate[i].y + m_MapScrollY;
			}
			m_CollisionHead = true;
			return true;
		}
	}
	m_CollisionHead = false;
	return false;
}

bool GameChara::LeftCollision() {
	//左の方向のブロックを確かめる
	if (!LeftCollisionCheck(NONE) && (LeftCollisionCheck(START_ZONE) || !LeftCollisionCheck(START_ZONE)))
	{
		float BehindLeftDirection = m_WorldCoordinate[3].x;
		if (m_PrevMapLeftDirectionPosition != m_WorldCoordinate[3].x)
		{
			m_WorldCoordinate[0].x = ((m_MapLeftDirectionPosition + 1)* CELL_SIZE);
			m_WorldCoordinate[1].x = ((m_MapLeftDirectionPosition + 3) * CELL_SIZE);
			m_WorldCoordinate[2].x = ((m_MapLeftDirectionPosition + 3) * CELL_SIZE);
			m_WorldCoordinate[3].x = ((m_MapLeftDirectionPosition + 1)* CELL_SIZE);
			for (int i = 0; i < 4; i++)
			{
				m_DisplayCoordinate[i].x = m_WorldCoordinate[i].x + m_MapScrollX;
			}
		}
		if (BehindLeftDirection == m_WorldCoordinate[3].x) {
			return false;
		}
		return true;
	}
	return false;
}
bool GameChara::RightCollision() {
	//右方向のブロックを確かめる
	if ((!RightCollisionCheck(NONE)) && (RightCollisionCheck(START_ZONE) || !RightCollisionCheck(START_ZONE)))
	{
		float BehindRightDirection = m_WorldCoordinate[2].x;
		if (m_PrevMapRightDirectionPosition != m_WorldCoordinate[2].x)
		{
			m_WorldCoordinate[0].x = ((m_MapRightDirectionPosition - 2) * CELL_SIZE) - 1;
			m_WorldCoordinate[1].x = ((m_MapRightDirectionPosition)* CELL_SIZE) - 1;
			m_WorldCoordinate[2].x = ((m_MapRightDirectionPosition)* CELL_SIZE) - 1;
			m_WorldCoordinate[3].x = ((m_MapRightDirectionPosition - 2) * CELL_SIZE) - 1;
			for (int i = 0; i < 4; i++)
			{
				m_DisplayCoordinate[i].x = m_WorldCoordinate[i].x + m_MapScrollX - 1;
			}
		}
		if (BehindRightDirection == m_WorldCoordinate[2].x) {
			return false;
		}
		return true;
	}
	return false;
}

void GameChara::SideCollision() {
	if (m_PrevMapLeftDirectionPosition >= m_WorldCoordinate[3].x)
	{
		while(LeftCollision());
	}
	if (m_PrevMapRightDirectionPosition <= m_WorldCoordinate[2].x)
	{
		while (RightCollision());
	}
	UpdateMapPos();
}

void GameChara::MoveInertia() {
	static int InertiaTime = 0;
	int InertiaTimeMax = 10;
	if (!m_isJump) {
		++InertiaTime;
	}
	for (int i = 0; i < 4; i++)
	{
		m_WorldCoordinate[i].x += MOVE_SPEED * static_cast<float>(m_Facing);
		m_DisplayCoordinate[i].x += MOVE_SPEED * static_cast<float>(m_Facing);
	}
	SideCollision();
	if (!m_isInTheAir) {
		m_TurnAnimation = 0.f;
		InertiaTimeMax = 5;
	}
	if (InertiaTime > InertiaTimeMax) {
		m_isInertiaMoving = false;
		InertiaTime = 0;
	}
}