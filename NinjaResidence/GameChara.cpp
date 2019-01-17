/**
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
	m_row = m_pMapChip->getRow();
	m_colunm = m_pMapChip->getColunm();
	m_Central.x = static_cast<float>(m_pMapChip->SearchBlockX(START_ZONE))*CELL_SIZE;
	m_Central.y = static_cast<float>(m_pMapChip->SearchBlockY(START_ZONE))*CELL_SIZE;
	CreateSquareVertex(m_Central, m_WorldCharaCoordinate, 0xFFFFFFFF, 0, 0, m_CollisionTu, m_CollisionTv);
	CreateSquareVertex(m_Central, m_DisplayCharaCoordinate, 0xFFFFFFFF, 0, 0, m_CollisionTu, m_CollisionTv);
	for (int i = 0; i < 4; i++)
	{
		m_DisplayCharaCoordinate[i].x = m_WorldCharaCoordinate[i].x + m_MapScrollX;
		m_DisplayCharaCoordinate[i].y = m_WorldCharaCoordinate[i].y + m_MapScrollY;
	}

	//CreateSquareVertex(m_Central, m_ReverseDisplayCharaCoordinate, 0xFFFFFFFF, 0, 0, m_CollisionTu, m_CollisionTv);
	//CreateSquareVertex(m_Central, m_ReverseWorldCharaCoordinate, 0xFFFFFFFF, 0, 0, m_CollisionTu, m_CollisionTv);
	//CreateSquareVertex(m_Central, m_SurfaceDisplayCharaCoordinate, 0xFFFFFFFF, 0, 0, m_CollisionTu, m_CollisionTv);
	//CreateSquareVertex(m_Central, m_SurfaceWorldCharaCoordinate, 0xFFFFFFFF, 0, 0, m_CollisionTu, m_CollisionTv);
	//do {
	//	MapScroolCheck();
	//	AddGravity();
	//	
	//} while (SetGround());
}

GameChara::~GameChara()
{
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
	m_isInTheAir = !SetGround();
	m_MapLeftDirectionPosition -= 1;
	m_MapRightDirectionPosition += 1;
	m_HeldOntoWallLeft = !LeftCollisionCheck(NONE) && (LeftCollisionCheck(START_ZONE) || !LeftCollisionCheck(START_ZONE));
	m_HeldOntoWallRight = !RightCollisionCheck(NONE) && (RightCollisionCheck(START_ZONE) || !RightCollisionCheck(START_ZONE));


	if (!m_isInTheAir) {
		return true;
	}
	else if (m_HeldOntoWallLeft || m_HeldOntoWallRight) {
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
		m_DisplayCharaCoordinate[i].y -= m_AccelerationY;
		m_WorldCharaCoordinate[i].y -= m_AccelerationY;
	}
	m_MapPositionY = static_cast<int>((m_WorldCharaCoordinate[3].y + 10) / CELL_SIZE);
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
		m_RiseFlameTime++;
		AccelarationControl();
		JumpingLateralMotion();
		return;
	}
	AnimeCount = 0;

	InitJumpParam();
}

void GameChara::JumpingLateralMotion() {

	if (!m_isInTheAir) {
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
			m_WorldCharaCoordinate[i].x += m_AccelerationX;
			m_DisplayCharaCoordinate[i].x += m_AccelerationX;
		}
		RightCollision();
	}
	if (m_isJumpLeft) {
		//左に移動
		for (int i = 0; i < 4; i++)
		{
			m_WorldCharaCoordinate[i].x -= m_AccelerationX;
			m_DisplayCharaCoordinate[i].x -= m_AccelerationX;
		}
		LeftCollision();

	}
}


void GameChara::MoveOperation(KeyDirection vec)
{
	static int AnimeCount = 0;

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
		for (int i = 0;i < 4;i++)
		{
			m_WorldCharaCoordinate[i].x += MOVE_SPEED;
			m_DisplayCharaCoordinate[i].x += MOVE_SPEED;
		}
		RightCollision();
		if (m_isInTheAir) break;
		if (m_ChangeAnimation == WATER_ART) {
			m_TurnAnimation = 3.f;
			break;
		}
		m_ChangeAnimation = DASH;
		++AnimeCount;
		if (AnimeCount > 2) {
			TurnTheAnimation(8);
			AnimeCount = 0;
		}
		break;
	case MOVE_LEFT:
		//左に移動
		m_Facing = FACING_LEFT;
		m_DirectionBias = ONE;
		for (int i = 0;i < 4;i++)
		{
			m_WorldCharaCoordinate[i].x -= MOVE_SPEED;
			m_DisplayCharaCoordinate[i].x -= MOVE_SPEED;
		}
		LeftCollision();
		if (m_isInTheAir) break;
		if (m_ChangeAnimation == WATER_ART) {
			m_TurnAnimation = 3.f;
			break;
		}

		m_ChangeAnimation = DASH;
		++AnimeCount;
		if (AnimeCount > 2) {
			TurnTheAnimation(8);
			AnimeCount = 0;
		}
		break;
	}
}

void GameChara::prevSaveMapCharaPos()
{
	m_PrevMapLeftDirectionPosition = (int)m_WorldCharaCoordinate[3].x;
	m_PrevMapRightDirectionPosition = (int)m_WorldCharaCoordinate[2].x;
	m_PrevMapCharaPositionY = (int)m_WorldCharaCoordinate[3].y + 10;
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

	for (int i = 0; i < ReversePointVector.size(); ++i) {
		bool isSameMapState = ReversePointVector[i].MapDataState == MapState;
		bool isSamePair = PairNumber == ReversePointVector[i].PairNumber;
		if (isSameMapState && isSamePair) {
			BlockY = ReversePointVector[i].PositionY;
			BlockX = ReversePointVector[i].PositionX;
			break;
		}
	}

	m_WorldCharaCoordinate[0].x = (BlockX * CELL_SIZE);
	m_WorldCharaCoordinate[1].x = (BlockX * CELL_SIZE) + m_Central.scale_x;
	m_WorldCharaCoordinate[2].x = (BlockX * CELL_SIZE) + m_Central.scale_x;
	m_WorldCharaCoordinate[3].x = (BlockX * CELL_SIZE);

	m_WorldCharaCoordinate[0].y = (BlockY * CELL_SIZE) - m_Central.scale_y;
	m_WorldCharaCoordinate[1].y = (BlockY * CELL_SIZE) - m_Central.scale_y;
	m_WorldCharaCoordinate[2].y = (BlockY * CELL_SIZE);
	m_WorldCharaCoordinate[3].y = (BlockY * CELL_SIZE);
	do {
		for (int i = 0; i < 4; i++)
		{
			m_DisplayCharaCoordinate[i].y = m_WorldCharaCoordinate[i].y + m_MapScrollY;
			m_DisplayCharaCoordinate[i].x = m_WorldCharaCoordinate[i].x + m_MapScrollX;
		}
		ScrollXBuf = m_MapScrollX;
		ScrollYBuf = m_MapScrollY;

		MapScroolCheck();
	} while ((m_MapScrollX - ScrollXBuf) || (m_MapScrollY - ScrollYBuf));
}

void GameChara::GimmickHitCheck()
{
	//下の方向のブロックを確かめる
	if ((m_pMapChip->getMapChipData(m_MapPositionY, m_MapLeftDirectionPosition) / 100 == BT_SWITCH) ||
		(m_pMapChip->getMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 1) / 100 == BT_SWITCH) ||
		(m_pMapChip->getMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 2) / 100 == BT_SWITCH))
	{
		m_pMapChip->Activate(m_MapRightDirectionPosition, m_MapPositionY);
	}
	//左の方向のブロックを確かめる
	if ((m_pMapChip->getMapChipData(m_MapPositionY - 1, m_MapLeftDirectionPosition) / 100 != BT_PARTITIONBOARD) ||
		(m_pMapChip->getMapChipData(m_MapPositionY - 2, m_MapLeftDirectionPosition) / 100 != BT_PARTITIONBOARD) ||
		(m_pMapChip->getMapChipData(m_MapPositionY - 3, m_MapLeftDirectionPosition) / 100 != BT_PARTITIONBOARD) ||
		(m_pMapChip->getMapChipData(m_MapPositionY - 4, m_MapLeftDirectionPosition) / 100 != BT_PARTITIONBOARD))
	{

	}

	//右方向のブロックを確かめる
	if ((m_pMapChip->getMapChipData(m_MapPositionY - 1, m_MapRightDirectionPosition) != BT_PARTITIONBOARD) ||
		(m_pMapChip->getMapChipData(m_MapPositionY - 2, m_MapRightDirectionPosition) != BT_PARTITIONBOARD) ||
		(m_pMapChip->getMapChipData(m_MapPositionY - 3, m_MapRightDirectionPosition) != BT_PARTITIONBOARD) ||
		(m_pMapChip->getMapChipData(m_MapPositionY - 4, m_MapRightDirectionPosition) != BT_PARTITIONBOARD))
	{

	}
}

void GameChara::CharaInfoSave(Object* MapChip, int PairNumber)
{
	m_pMapChip = MapChip;
	MapReversePointSearch(PairNumber,m_pMapChip->GetMapDataState());
}

void GameChara::MapScroolCheck()
{
	if (m_pMapChip->RestrictBottomScroll()) {
		m_MapScrollY += VERTICAL_SCROLLING_LEVEL - GravityAcceleration;
		m_WorldCharaCoordinate[0].y = m_pMapChip->GetBottomWorldPoint(m_MapLeftDirectionPosition, m_MapRightDirectionPosition);
		m_WorldCharaCoordinate[1].y = m_pMapChip->GetBottomWorldPoint(m_MapLeftDirectionPosition, m_MapRightDirectionPosition);
		m_WorldCharaCoordinate[2].y = m_pMapChip->GetBottomWorldPoint(m_MapLeftDirectionPosition, m_MapRightDirectionPosition) + m_Central.scale_y;
		m_WorldCharaCoordinate[3].y = m_pMapChip->GetBottomWorldPoint(m_MapLeftDirectionPosition, m_MapRightDirectionPosition) + m_Central.scale_y;
		m_DisplayCharaCoordinate[0].y = m_pMapChip->GetBottomPoint(m_MapLeftDirectionPosition, m_MapRightDirectionPosition);
		m_DisplayCharaCoordinate[1].y = m_pMapChip->GetBottomPoint(m_MapLeftDirectionPosition, m_MapRightDirectionPosition);
		m_DisplayCharaCoordinate[2].y = m_pMapChip->GetBottomPoint(m_MapLeftDirectionPosition, m_MapRightDirectionPosition) + m_Central.scale_y;
		m_DisplayCharaCoordinate[3].y = m_pMapChip->GetBottomPoint(m_MapLeftDirectionPosition, m_MapRightDirectionPosition) + m_Central.scale_y;
		m_isScrollingDown = true;

	}
	//下にスクロール移動
	else if (m_DisplayCharaCoordinate[3].y > static_cast<float>(DisplayCharMoveScopeDown))
	{
		m_DisplayCharaCoordinate[0].y = (static_cast<float>(DisplayCharMoveScopeDown) - m_Central.scale_y);
		m_DisplayCharaCoordinate[1].y = (static_cast<float>(DisplayCharMoveScopeDown) - m_Central.scale_y);
		m_DisplayCharaCoordinate[2].y = (static_cast<float>(DisplayCharMoveScopeDown));
		m_DisplayCharaCoordinate[3].y = (static_cast<float>(DisplayCharMoveScopeDown));
		m_MapScrollY -= VERTICAL_SCROLLING_LEVEL;
		SetGround();

		m_isScrollingDown = true;
	}
	else m_isScrollingDown = false;
	//上にスクロール移動
	if (m_DisplayCharaCoordinate[1].y < static_cast<float>(DisplayCharMoveScopeUp))
	{
		if (m_WorldCharaCoordinate[0].y >= static_cast<float>(DisplayCharMoveScopeUp))
		{
			m_DisplayCharaCoordinate[0].y = (static_cast<float>(DisplayCharMoveScopeUp));
			m_DisplayCharaCoordinate[1].y = (static_cast<float>(DisplayCharMoveScopeUp));
			m_DisplayCharaCoordinate[2].y = (static_cast<float>(DisplayCharMoveScopeUp) + m_Central.scale_y);
			m_DisplayCharaCoordinate[3].y = (static_cast<float>(DisplayCharMoveScopeUp) + m_Central.scale_y);
			m_MapScrollY += ScrollSpeed;
		}
	}

	//右にスクロール移動
	if (m_DisplayCharaCoordinate[1].x > static_cast<float>(DisplayCharMoveScopeRight))
	{
		if (m_WorldCharaCoordinate[1].x <= (((m_row-1) * CELL_SIZE) - static_cast<float>(DisplayCharMoveScopeX)))
		{
			m_DisplayCharaCoordinate[0].x = (static_cast<float>(DisplayCharMoveScopeRight) - m_Central.scale_x);
			m_DisplayCharaCoordinate[1].x = (static_cast<float>(DisplayCharMoveScopeRight));
			m_DisplayCharaCoordinate[2].x = (static_cast<float>(DisplayCharMoveScopeRight));
			m_DisplayCharaCoordinate[3].x = (static_cast<float>(DisplayCharMoveScopeRight) - m_Central.scale_x);
			m_MapScrollX -= ScrollSpeed;
		}
	}
	//左にスクロール移動
	if (m_DisplayCharaCoordinate[0].x < static_cast<float>(DisplayCharMoveScopeLeft))
	{
		if (m_WorldCharaCoordinate[0].x >= static_cast<float>(DisplayCharMoveScopeX))
		{
			m_DisplayCharaCoordinate[0].x = (static_cast<float>(DisplayCharMoveScopeLeft));
			m_DisplayCharaCoordinate[1].x = (static_cast<float>(DisplayCharMoveScopeLeft) + m_Central.scale_x);
			m_DisplayCharaCoordinate[2].x = (static_cast<float>(DisplayCharMoveScopeLeft) + m_Central.scale_x);
			m_DisplayCharaCoordinate[3].x = (static_cast<float>(DisplayCharMoveScopeLeft));
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
	m_MapLeftDirectionPosition = static_cast<int>(m_WorldCharaCoordinate[3].x / CELL_SIZE);
	m_MapRightDirectionPosition = static_cast<int>((m_WorldCharaCoordinate[2].x) / CELL_SIZE);
	m_MapPositionY = static_cast<int>((m_WorldCharaCoordinate[3].y + 10) / CELL_SIZE);
	if (m_MapPositionY >= m_colunm) {
		m_MapPositionY = m_colunm - 1;
	}
	m_CollisionHead = TopCollisionAnything();

	MapScroolCheck();
	AddGravity();
	GimmickHitCheck();
	//下の方向を確かめる
	SetGround();
	//上のブロックを確かめる
	if (m_PrevMapCharaPositionY > m_WorldCharaCoordinate[3].y + 10)
	{
		if ((m_pMapChip->getMapChipData(m_MapPositionY - 4, m_MapLeftDirectionPosition) != NONE) ||
			(m_pMapChip->getMapChipData(m_MapPositionY - 4, m_MapLeftDirectionPosition + 1) != NONE) ||
			(m_pMapChip->getMapChipData(m_MapPositionY - 4, m_MapLeftDirectionPosition + 2) != NONE))
		{
			m_WorldCharaCoordinate[0].y = ((m_MapPositionY - 3) * CELL_SIZE);
			m_WorldCharaCoordinate[1].y = ((m_MapPositionY - 3) * CELL_SIZE);
			m_WorldCharaCoordinate[2].y = ((m_MapPositionY + 1) * CELL_SIZE);
			m_WorldCharaCoordinate[3].y = ((m_MapPositionY + 1) * CELL_SIZE);
			for (int i = 0; i < 4; i++)
			{
				m_DisplayCharaCoordinate[i].y = m_WorldCharaCoordinate[i].y + m_MapScrollY;
			}
		}
	}
	SideCollision();

	if (!m_CollisionHead) {
		Jump();
		SideCollision();
		SetGround();
	}
	else if (m_isJump) {
		InitJumpParam();
	}

	if (m_pMapChip->getMapChipData(m_MapPositionY - 2, m_MapRightDirectionPosition) > 100)
	{

		m_pMapChip->Activate(m_MapRightDirectionPosition, m_MapPositionY - 2);

	}
	if (DownCollisionCheck(GOAL_ZONE)) {
		return true;
	}
	if (FailureGame()) {
		m_GameFailure = true;
	}
	return false;
}

bool GameChara::DownCollisionAnything(void) {
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
	bool BlockMax = ((m_pMapChip->getMapChipData(m_MapPositionY, m_MapLeftDirectionPosition) < 100) ||
		(m_pMapChip->getMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 1) < 100) ||
		(m_pMapChip->getMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 2) < 100));
	bool BlockMin = ((m_pMapChip->getMapChipData(m_MapPositionY, m_MapLeftDirectionPosition) > 0) ||
		(m_pMapChip->getMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 1) > 0) ||
		(m_pMapChip->getMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 2) > 0));
	if (BlockMax && BlockMin) {
		return true;
	}
	bool TorchMax = ((m_pMapChip->getMapChipData(m_MapPositionY, m_MapLeftDirectionPosition) < 500) ||
		(m_pMapChip->getMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 1) < 500) ||
		(m_pMapChip->getMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 2) < 500));
	bool TorchMin = ((m_pMapChip->getMapChipData(m_MapPositionY, m_MapLeftDirectionPosition) >= 400) ||
		(m_pMapChip->getMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 1) >= 400) ||
		(m_pMapChip->getMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 2) >= 400));
	if (TorchMax && TorchMin) {
		m_ChangeAnimation = WATER_ART;
		return false;
	}

	bool WaterMax = ((m_pMapChip->getMapChipData(m_MapPositionY, m_MapLeftDirectionPosition) < 800) ||
		(m_pMapChip->getMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 1) < 800) ||
		(m_pMapChip->getMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 2) < 800));
	bool WaterMin = ((m_pMapChip->getMapChipData(m_MapPositionY, m_MapLeftDirectionPosition) >= 700) ||
		(m_pMapChip->getMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 1) >= 700) ||
		(m_pMapChip->getMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 2) >= 700));
	if (WaterMax && WaterMin) {
		m_ChangeAnimation = WATER_ART;
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
	if ((m_pMapChip->getMapChipData(m_MapPositionY, m_MapLeftDirectionPosition) == block) ||
		(m_pMapChip->getMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 1) == block) ||
		(m_pMapChip->getMapChipData(m_MapPositionY, m_MapLeftDirectionPosition + 2) == block)) {
		return true;
	}
	return false;
}
bool GameChara::TopCollisionCheck(int block) {
	if ((m_pMapChip->getMapChipData(m_MapPositionY - 4, m_MapLeftDirectionPosition) == block) ||
		(m_pMapChip->getMapChipData(m_MapPositionY - 4, m_MapLeftDirectionPosition + 1) == block) ||
		(m_pMapChip->getMapChipData(m_MapPositionY - 4, m_MapLeftDirectionPosition + 2) == block)) {
		return true;
	}
	return false;
}

bool GameChara::LeftCollisionCheck(int block) {
	//if (m_MapLeftDirectionPosition <= 0) {
	//	m_MapLeftDirectionPosition = 1;
	//}
	if ((m_pMapChip->getMapChipData(m_MapPositionY - 1, m_MapLeftDirectionPosition) == block) ||
		(m_pMapChip->getMapChipData(m_MapPositionY - 2, m_MapLeftDirectionPosition) == block) ||
		(m_pMapChip->getMapChipData(m_MapPositionY - 3, m_MapLeftDirectionPosition) == block) ||
		(m_pMapChip->getMapChipData(m_MapPositionY - 4, m_MapLeftDirectionPosition) == block)) {
		return true;
	}
	return false;
}
bool GameChara::RightCollisionCheck(int block) {
	if (m_MapRightDirectionPosition >= m_row) {
		m_MapRightDirectionPosition -= 1;
	}
	if ((m_pMapChip->getMapChipData(m_MapPositionY - 1, m_MapRightDirectionPosition) == block) ||
		(m_pMapChip->getMapChipData(m_MapPositionY - 2, m_MapRightDirectionPosition) == block) ||
		(m_pMapChip->getMapChipData(m_MapPositionY - 3, m_MapRightDirectionPosition) == block) ||
		(m_pMapChip->getMapChipData(m_MapPositionY - 4, m_MapRightDirectionPosition) == block)) {
		return true;
	}
	return false;
}
bool GameChara::LookDownWater() {
	bool buf = false;
	for (int i = 0; i < m_colunm - m_MapPositionY; ++i) {
		if (!buf) {
			buf = (BT_WATER == m_pMapChip->getMapChipData(m_MapPositionY + i, m_MapLeftDirectionPosition - 1) / 100);
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
	else return m_WorldCharaCoordinate[2].y;
}
bool GameChara::FailureGame()
{
	if (LeftCollisionCheck(SPEAR)|| TopCollisionCheck(SPEAR) || DownCollisionCheck(SPEAR) || RightCollisionCheck(SPEAR)) {
		return true;
	}
	return false;
}

void GameChara::Render()
{
	TextureRender("CHARA_INTEGRATION_TEX", m_DisplayCharaCoordinate);
	CUSTOMVERTEX TestChar[4];
	CENTRAL_STATE CharCentral = { 0 };
	TranslateCentral_State(&CharCentral, m_DisplayCharaCoordinate);
	CharCentral.x -= 25.f;
	CharCentral.scale_x = 120.f;
	CreateSquareVertex(CharCentral, TestChar, 0xFFFFFFFF,( m_TurnAnimation+m_DirectionBias) * m_CharTu, m_ChangeAnimation * m_CharTv, m_CharTu * m_Facing, m_CharTv);
	TextureRender("CHARA_TEX", TestChar);
#ifdef _DEBUG

	RECT test = { 0,0,1250,500 };
	char TestText[ArrayLong];
	sprintf_s(TestText, ArrayLong, "MapChara::X-L:%d,X-R:%d,Y:%d", m_MapLeftDirectionPosition, m_MapRightDirectionPosition, m_MapPositionY);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_RIGHT, 0xffffffff);
	sprintf_s(TestText, ArrayLong, "\nPrevMapChara::X-L:%d,X-R:%d,Y:%d", m_PrevMapLeftDirectionPosition, m_PrevMapRightDirectionPosition, m_PrevMapCharaPositionY);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_RIGHT, 0xffffffff);
	sprintf_s(TestText, ArrayLong, "\n\nWorldChara::X-L:%.2f,X-R:%.2f,Y:%.2f", m_WorldCharaCoordinate[3].x, m_WorldCharaCoordinate[2].x, m_WorldCharaCoordinate[3].y);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_RIGHT, 0xffffffff);
	sprintf_s(TestText, ArrayLong, "\n\n\nDisplayChara::X-L:%.2f,X-R:%.2f,Y3:%.2f,Y0:%.2f", m_DisplayCharaCoordinate[3].x, m_DisplayCharaCoordinate[2].x, m_DisplayCharaCoordinate[3].y, m_DisplayCharaCoordinate[0].y);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_RIGHT, 0xffffffff);
	sprintf_s(TestText, ArrayLong, "\n\n\n\n\n\nAccelerationY::%.2f", m_AccelerationY);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_RIGHT, 0xffffffff);
#endif

}

void GameChara::AddGravity() {
	//重力を毎フレームかける
	if (m_isScrollingDown) {
		for (int i = 0; i < 4; i++)
		{

			m_WorldCharaCoordinate[i].y += VERTICAL_SCROLLING_LEVEL;
			m_DisplayCharaCoordinate[i].y += VERTICAL_SCROLLING_LEVEL;
		}
		SideCollision();
		SetGround();
		return;
	}
	if (!DownCollisionAnything())
	{
		GravityAcceleration += 0.1f;
	}
	else GravityAcceleration = 0;

	for (int i = 0; i < 4; i++)
	{
		m_WorldCharaCoordinate[i].y += GRAVITY + GravityAcceleration;
		m_DisplayCharaCoordinate[i].y += GRAVITY + GravityAcceleration;
	}
	SideCollision();
	SetGround();
}

void GameChara::DebugMove() {
	for (int i = 0; i < 4; i++)
	{
		m_WorldCharaCoordinate[i].y -= MOVE_SPEED * 1.5f;
		m_DisplayCharaCoordinate[i].y -= MOVE_SPEED * 1.5f;
	}
}

float GameChara::GetPositionX()
{
	switch (m_Facing) {
	case FACING_LEFT:
		return m_DisplayCharaCoordinate[0].x;
	case FACING_RIGHT:
		return m_DisplayCharaCoordinate[0].x + m_Central.scale_x;
	}
	return 0.f;
}

bool GameChara::SetGround() {

	if (DownCollisionAnything())
	{
		m_WorldCharaCoordinate[0].y = ((m_MapPositionY - 4) * CELL_SIZE);
		m_WorldCharaCoordinate[1].y = ((m_MapPositionY - 4) * CELL_SIZE);
		m_WorldCharaCoordinate[2].y = ((m_MapPositionY)* CELL_SIZE);
		m_WorldCharaCoordinate[3].y = ((m_MapPositionY)* CELL_SIZE);
		for (int i = 0; i < 4; i++)
		{
			m_DisplayCharaCoordinate[i].y = m_WorldCharaCoordinate[i].y + m_MapScrollY;
		}
		return true;
	}
	else if (LookDownWater()) {
		if (!m_isJump) {
			float WaterUpperLevel = WaterCollsionCheck();
			if (m_DisplayCharaCoordinate[2].y < WaterUpperLevel) {
				return false;
			}
			m_WorldCharaCoordinate[2].y = WaterUpperLevel - m_MapScrollY;
			m_WorldCharaCoordinate[3].y = WaterUpperLevel - m_MapScrollY;
			m_WorldCharaCoordinate[0].y = WaterUpperLevel - m_MapScrollY - m_Central.scale_y;
			m_WorldCharaCoordinate[1].y = WaterUpperLevel - m_MapScrollY - m_Central.scale_y;
			for (int i = 0; i < 4; i++)
			{
				m_DisplayCharaCoordinate[i].y = m_WorldCharaCoordinate[i].y + m_MapScrollY;
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
		m_TurnAnimation = 5.f;
	}
	else  if (m_isJump && !m_isUsingArt) {
		m_ChangeAnimation = JUMPING;
	}

	return false;
}

bool GameChara::LeftCollision() {
	//左の方向のブロックを確かめる
	if (!LeftCollisionCheck(NONE) && (LeftCollisionCheck(START_ZONE) || !LeftCollisionCheck(START_ZONE)))
	{
		//if (m_MapLeftDirectionPosition <= 0) {
		//	m_MapLeftDirectionPosition = 1;
		//}
		if (m_PrevMapLeftDirectionPosition != m_WorldCharaCoordinate[3].x)
		{
			m_WorldCharaCoordinate[0].x = ((m_MapLeftDirectionPosition+1)* CELL_SIZE);
			m_WorldCharaCoordinate[1].x = ((m_MapLeftDirectionPosition + 3) * CELL_SIZE);
			m_WorldCharaCoordinate[2].x = ((m_MapLeftDirectionPosition + 3) * CELL_SIZE);
			m_WorldCharaCoordinate[3].x = ((m_MapLeftDirectionPosition+1)* CELL_SIZE);
			for (int i = 0; i < 4; i++)
			{
				m_DisplayCharaCoordinate[i].x = m_WorldCharaCoordinate[i].x + m_MapScrollX;
			}
		}
		return true;
	}
	return false;
}
bool GameChara::RightCollision() {
	//右方向のブロックを確かめる
	if ((!RightCollisionCheck(NONE)) && (RightCollisionCheck(START_ZONE) || !RightCollisionCheck(START_ZONE)))
	{
		//if (m_MapRightDirectionPosition + 1 >= m_row) {
		//	m_MapRightDirectionPosition -= 1;
		//}
		if (m_PrevMapRightDirectionPosition != m_WorldCharaCoordinate[2].x)
		{
			m_WorldCharaCoordinate[0].x = ((m_MapRightDirectionPosition - 2) * CELL_SIZE) - 1;
			m_WorldCharaCoordinate[1].x = ((m_MapRightDirectionPosition)* CELL_SIZE) - 1;
			m_WorldCharaCoordinate[2].x = ((m_MapRightDirectionPosition)* CELL_SIZE) - 1;
			m_WorldCharaCoordinate[3].x = ((m_MapRightDirectionPosition - 2) * CELL_SIZE) - 1;
			for (int i = 0; i < 4; i++)
			{
				m_DisplayCharaCoordinate[i].x = m_WorldCharaCoordinate[i].x + m_MapScrollX - 1;
			}
		}
		return true;
	}
	return false;
}

void GameChara::SideCollision() {
	if (m_PrevMapLeftDirectionPosition >= m_WorldCharaCoordinate[3].x)
	{
		LeftCollision();
	}
	if (m_PrevMapRightDirectionPosition <= m_WorldCharaCoordinate[2].x)
	{
		RightCollision();
	}

}
