/**
* @file GameChara.cpp
* @brief GameCharaクラス
* @author Kojiro Kawahara
*/
#include "GameChara.h"

using  namespace MapBlock;
using namespace PlayerAnimation;

GameChara::GameChara(DirectX* pDirectX, SoundsManager* pSoundManager, Object* MapChip) :Object(pDirectX,pSoundManager)
{
	//MapChipの情報を取得するために必要
	m_pMapChip = MapChip;
	row = m_pMapChip->getRow();
	colunm = m_pMapChip->getColunm();
	CreateSquareVertex(m_Player, m_DisplayCharaCoordinate, 0xFFFFFFFF, 0, 0, CharTu, CharTv);
	CreateSquareVertex(m_Player, m_WorldCharaCoordinate, 0xFFFFFFFF, 0, 0, CharTu, CharTv);
	CreateSquareVertex(m_Player, m_WorldCharaCoordinate, 0xFFFFFFFF, 0, 0, CharTu, CharTv);
	CreateSquareVertex(m_Player, m_ReverseDisplayCharaCoordinate, 0xFFFFFFFF, 0, 0, CharTu, CharTv);
	CreateSquareVertex(m_Player, m_ReverseWorldCharaCoordinate, 0xFFFFFFFF, 0, 0, CharTu, CharTv);
	CreateSquareVertex(m_Player, m_SurfaceDisplayCharaCoordinate, 0xFFFFFFFF, 0, 0, CharTu, CharTv);
	CreateSquareVertex(m_Player, m_SurfaceWorldCharaCoordinate, 0xFFFFFFFF, 0, 0, CharTu, CharTv);
}

GameChara::~GameChara()
{
}

void GameChara::InitJumpParam() {
	isJump = false;
	isJumpRight = false;
	isJumpLeft = false;
	AccelerationY = InitialAcceleration;
	//AccelerationX = InitialAcceleration;
	RiseFlameTime = 0;
}
void GameChara::AccelarationControl() {
		AccelerationY -= 2.f;

}
bool GameChara::PermitJumping() {
	isInTheAir = !DownCollisionAnything();
	HeldOntoWallLeft = LeftCollisionCheck(ROCK_BLOCK);
	HeldOntoWallRight = RightCollisionCheck(ROCK_BLOCK);


	if (!isInTheAir) {
		return true;
	}
	else if (HeldOntoWallLeft || HeldOntoWallRight) {
		return true;
	}
	return false;
}
void GameChara::Jump()
{
	if (!isJump) {
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		m_DisplayCharaCoordinate[i].y -= AccelerationY;
		m_WorldCharaCoordinate[i].y -= AccelerationY;
	}
	MapCharaPositionY = (int)(m_WorldCharaCoordinate[3].y + 10) / CELL_SIZE;
	ChangeAnimation = JUMPING;
	if (RiseFlameTime < 15) {
		RiseFlameTime++;
		AccelarationControl();
		JumpingLateralMotion();
		return;
	}

	InitJumpParam();
}

void GameChara::JumpingLateralMotion() {

	if (!isInTheAir) {
		return;
	}

	if (HeldOntoWallLeft) {
		isJumpRight = true;
	}
	if (HeldOntoWallRight) {
		isJumpLeft = true;
	}

	if (isJumpRight) {
		//右に移動
		for (int i = 0; i < 4; i++)
		{
			m_WorldCharaCoordinate[i].x += AccelerationX;
			m_DisplayCharaCoordinate[i].x += AccelerationX;
		}
		//if (AccelerationX > 0) {
		//	AccelerationX -= 0.1f;
		//}

	}
	if (isJumpLeft) {
		//左に移動
		for (int i = 0; i < 4; i++)
		{
			m_WorldCharaCoordinate[i].x -= AccelerationX;
			m_DisplayCharaCoordinate[i].x -= AccelerationX;
		}

	}
}
//bool GameChara::StartJump()
//{
//	if (DownCollisionCheck){
//		return true;
//	}
//	return false;
//}

void GameChara::CharaMoveOperation(KeyInput vec)
{
	switch (vec)
	{
		//上に移動
	case JUMP:

		isJump = PermitJumping();
		break;
	case DOWN:
		//今のところなし

		break;
	case MOVE_RIGHT:
		//右に移動
		ChangeAnimation = DASH;
		Facing = FACING_RIGHT;
		Bias = ZERO;
		for (int i = 0;i < 4;i++)
		{
			m_WorldCharaCoordinate[i].x += CharaMoveSpeed;
			m_DisplayCharaCoordinate[i].x += CharaMoveSpeed;
		}
		break;
	case MOVE_LEFT:
		//左に移動
		ChangeAnimation = DASH;
		Facing = FACING_LEFT;
		Bias = ONE;
		for (int i = 0;i < 4;i++)
		{
			m_WorldCharaCoordinate[i].x -= CharaMoveSpeed;
			m_DisplayCharaCoordinate[i].x -= CharaMoveSpeed;
		}
		break;
	case PUSH_NONE:
		if (!DownCollisionAnything()) {
			ChangeAnimation = STAND;
		}
		break;
	}
}

void GameChara::ValueAllSetCUSTOMVERTEX(CUSTOMVERTEX* Receive, CUSTOMVERTEX* Give)
{
	//Receive[0] = Give[0];
	//Receive[1] = Give[1];
	//Receive[2] = Give[2];
	//Receive[3] = Give[3];
}

void GameChara::prevSaveMapCharaPos()
{
	m_PrevMapLeftDirectionPosition = (int)m_WorldCharaCoordinate[3].x;
	m_PrevMapRightDirectionPosition = (int)m_WorldCharaCoordinate[2].x;
	m_PrevMapCharaPositionY = (int)m_WorldCharaCoordinate[3].y + 10;
}

void GameChara::KeyOperation(KeyInput vec)
{
	static bool isThrowing = false;
	//Key操作での処理
	switch (vec)
	{
	case JUMP:
		CharaMoveOperation(JUMP);
		break;
	case DOWN:
		//今のところ無し
		break;
	case MOVE_RIGHT:
		//右に移動
		CharaMoveOperation(MOVE_RIGHT);
		break;
	case MOVE_LEFT:
		//左に移動
		CharaMoveOperation(MOVE_LEFT);
		break;
	case SoundOn:
		m_pSoundManager->Start("DECISION");
		break;
	case PUSH_NONE:
		CharaMoveOperation(PUSH_NONE);
		break;
	case THROW:
		//if (isThrowing) {
			ChangeAnimation = THROWING;
		//}
		//isThrowing = !isThrowing;
		break;
	}
}

void GameChara::CharaInforSave(int MapReverseSelect,Object* MapChip)
{
	m_pMapChip = MapChip;
	row = m_pMapChip->getRow();
	colunm = m_pMapChip->getColunm();

	if (!MapReverseSelect)
	{
		ValueAllSetCUSTOMVERTEX(m_SurfaceDisplayCharaCoordinate, m_DisplayCharaCoordinate);
		ValueAllSetCUSTOMVERTEX(m_SurfaceWorldCharaCoordinate, m_WorldCharaCoordinate);
		ValueAllSetCUSTOMVERTEX(m_DisplayCharaCoordinate, m_ReverseDisplayCharaCoordinate);
		ValueAllSetCUSTOMVERTEX(m_WorldCharaCoordinate, m_ReverseWorldCharaCoordinate);
	}
	else 
	{
		ValueAllSetCUSTOMVERTEX(m_ReverseDisplayCharaCoordinate, m_DisplayCharaCoordinate);
		ValueAllSetCUSTOMVERTEX(m_ReverseWorldCharaCoordinate, m_WorldCharaCoordinate);
		ValueAllSetCUSTOMVERTEX(m_DisplayCharaCoordinate, m_SurfaceDisplayCharaCoordinate);
		ValueAllSetCUSTOMVERTEX(m_WorldCharaCoordinate, m_SurfaceWorldCharaCoordinate);
	}
}

void GameChara::MapScroolCheck()
{
	//キャラ当たり判定が2段の地面の間に吸われている
	if (m_pMapChip->RestrictBottomScroll()){
		m_pMapChip->m_MapScrollY += VerticalScrollingLevel;
		m_WorldCharaCoordinate[0].y = m_pMapChip->GetBottomWorldPoint(MapLeftDirectionPosition, MapRightDirectionPosition);
		m_WorldCharaCoordinate[1].y = m_pMapChip->GetBottomWorldPoint(MapLeftDirectionPosition, MapRightDirectionPosition);
		m_WorldCharaCoordinate[2].y = m_pMapChip->GetBottomWorldPoint(MapLeftDirectionPosition, MapRightDirectionPosition) + m_Player.scale_y;
		m_WorldCharaCoordinate[3].y = m_pMapChip->GetBottomWorldPoint(MapLeftDirectionPosition, MapRightDirectionPosition) + m_Player.scale_y;
		m_DisplayCharaCoordinate[0].y = m_pMapChip->GetBottomPoint(MapLeftDirectionPosition, MapRightDirectionPosition);
		m_DisplayCharaCoordinate[1].y = m_pMapChip->GetBottomPoint(MapLeftDirectionPosition, MapRightDirectionPosition);
		m_DisplayCharaCoordinate[2].y = m_pMapChip->GetBottomPoint(MapLeftDirectionPosition, MapRightDirectionPosition) + m_Player.scale_y;
		m_DisplayCharaCoordinate[3].y = m_pMapChip->GetBottomPoint(MapLeftDirectionPosition, MapRightDirectionPosition) + m_Player.scale_y;
	}
	//下にスクロール移動
	else if (m_DisplayCharaCoordinate[3].y > DisplayCharMoveScopeDown)
	{
		m_DisplayCharaCoordinate[0].y = (DisplayCharMoveScopeDown - m_Player.scale_y);
		m_DisplayCharaCoordinate[1].y = (DisplayCharMoveScopeDown - m_Player.scale_y);
		m_DisplayCharaCoordinate[2].y = (DisplayCharMoveScopeDown);
		m_DisplayCharaCoordinate[3].y = (DisplayCharMoveScopeDown);
		m_pMapChip->m_MapScrollY -= VerticalScrollingLevel;
		
		isScrollingDown = true;
	}
	else isScrollingDown = false;
	//上にスクロール移動
	if (m_DisplayCharaCoordinate[1].y < DisplayCharMoveScopeUp)
	{
		if (m_WorldCharaCoordinate[0].y >= DisplayCharMoveScopeUp)
		{
			m_DisplayCharaCoordinate[0].y = (DisplayCharMoveScopeUp);
			m_DisplayCharaCoordinate[1].y = (DisplayCharMoveScopeUp);
			m_DisplayCharaCoordinate[2].y = (DisplayCharMoveScopeUp + m_Player.scale_y);
			m_DisplayCharaCoordinate[3].y = (DisplayCharMoveScopeUp + m_Player.scale_y);
			m_pMapChip->m_MapScrollY += CharaMoveSpeed;
		}
	}

	//右にスクロール移動
	if (m_DisplayCharaCoordinate[1].x > DisplayCharMoveScopeRight)
	{
		if (m_WorldCharaCoordinate[1].x <= ((row * CELL_SIZE)- DisplayCharMoveScopeX))
		{
			m_DisplayCharaCoordinate[0].x = (DisplayCharMoveScopeRight - m_Player.scale_x);
			m_DisplayCharaCoordinate[1].x = (DisplayCharMoveScopeRight);
			m_DisplayCharaCoordinate[2].x = (DisplayCharMoveScopeRight);
			m_DisplayCharaCoordinate[3].x = (DisplayCharMoveScopeRight - m_Player.scale_x);
			m_pMapChip->m_MapScrollX -= CharaMoveSpeed;
		}
	}
	//左にスクロール移動
	if (m_DisplayCharaCoordinate[0].x < DisplayCharMoveScopeLeft)
	{
		if(m_WorldCharaCoordinate[0].x >= DisplayCharMoveScopeX)
		{
		m_DisplayCharaCoordinate[0].x = (DisplayCharMoveScopeLeft);
		m_DisplayCharaCoordinate[1].x = (DisplayCharMoveScopeLeft + m_Player.scale_x);
		m_DisplayCharaCoordinate[2].x = (DisplayCharMoveScopeLeft + m_Player.scale_x);
		m_DisplayCharaCoordinate[3].x = (DisplayCharMoveScopeLeft);
		m_pMapChip->m_MapScrollX += CharaMoveSpeed;
		}
	}

}

void GameChara::ThrowAnime() {
	static bool ThrowAnimeOn = false;
	static int AnimationCount = 0;

	if (ChangeAnimation == THROWING) {
		ThrowAnimeOn = true;
	}
	if (ThrowAnimeOn) {
		AnimationCount++;
	}
	else return;
	if (AnimationCount < 20) {
		ChangeAnimation = THROWING;
	}
	else {
		AnimationCount = 0;
		ThrowAnimeOn = false;
		ChangeAnimation = STAND;
	}
}
void GameChara::Update()
{
	ThrowAnime();
	MapLeftDirectionPosition = (int)m_WorldCharaCoordinate[3].x / CELL_SIZE;
	MapRightDirectionPosition = (int)(m_WorldCharaCoordinate[2].x) / CELL_SIZE;
	MapCharaPositionY = (int)(m_WorldCharaCoordinate[3].y + 10) / CELL_SIZE;
	if (MapCharaPositionY >= colunm) {
		MapCharaPositionY = colunm - 1;
	}
	CollisionHead = TopCollisionAnything();

	MapScroolCheck();
	AddGravity();
	//下の方向を確かめる
	if (DownCollisionAnything())
	{
		m_WorldCharaCoordinate[0].y = ((MapCharaPositionY - 4) * CELL_SIZE);
		m_WorldCharaCoordinate[1].y = ((MapCharaPositionY - 4) * CELL_SIZE);
		m_WorldCharaCoordinate[2].y = ((MapCharaPositionY)* CELL_SIZE);
		m_WorldCharaCoordinate[3].y = ((MapCharaPositionY)* CELL_SIZE);
		for (int i = 0; i < 4; i++)
		{
			m_DisplayCharaCoordinate[i].y = m_WorldCharaCoordinate[i].y + m_pMapChip->m_MapScrollY;
		}
		//2段ある地面にめり込んだときの復帰処理
		if (m_pMapChip->getMapChipData(MapCharaPositionY - 1, MapLeftDirectionPosition + 1) != NONE) {
			for (int i = 0; i < 4; i++)
			{
				m_WorldCharaCoordinate[i].y -= CELL_SIZE;
				m_DisplayCharaCoordinate[i].y -= m_WorldCharaCoordinate[i].y + m_pMapChip->m_MapScrollY;
			}

		}
	}
	else 	ChangeAnimation = JUMPING;

	//上のブロックを確かめる
	if (m_PrevMapCharaPositionY > m_WorldCharaCoordinate[3].y + 10)
	{
		if ((m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapLeftDirectionPosition) != NONE) ||
			(m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapLeftDirectionPosition + 1) != NONE) ||
			(m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapLeftDirectionPosition + 2) != NONE))
		{
			m_WorldCharaCoordinate[0].y = ((MapCharaPositionY - 3) * CELL_SIZE);
			m_WorldCharaCoordinate[1].y = ((MapCharaPositionY - 3) * CELL_SIZE);
			m_WorldCharaCoordinate[2].y = ((MapCharaPositionY + 1) * CELL_SIZE);
			m_WorldCharaCoordinate[3].y = ((MapCharaPositionY + 1) * CELL_SIZE);
			for (int i = 0; i < 4; i++)
			{
				m_DisplayCharaCoordinate[i].y = m_WorldCharaCoordinate[i].y + m_pMapChip->m_MapScrollY;
			}
		}
	}
	if (m_PrevMapLeftDirectionPosition >= m_WorldCharaCoordinate[3].x)
	{
		//左の方向のブロックを確かめる
		if ((m_pMapChip->getMapChipData(MapCharaPositionY - 1, MapLeftDirectionPosition) != NONE) ||
			(m_pMapChip->getMapChipData(MapCharaPositionY - 2, MapLeftDirectionPosition) != NONE) ||
			(m_pMapChip->getMapChipData(MapCharaPositionY - 3, MapLeftDirectionPosition) != NONE) ||
			(m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapLeftDirectionPosition) != NONE))
		{
			if (m_PrevMapLeftDirectionPosition != m_WorldCharaCoordinate[3].x)
			{
				m_WorldCharaCoordinate[0].x = ((MapLeftDirectionPosition + 1) * CELL_SIZE);
				m_WorldCharaCoordinate[1].x = ((MapLeftDirectionPosition + 3) * CELL_SIZE);
				m_WorldCharaCoordinate[2].x = ((MapLeftDirectionPosition + 3) * CELL_SIZE);
				m_WorldCharaCoordinate[3].x = ((MapLeftDirectionPosition + 1) * CELL_SIZE);
				for (int i = 0; i < 4; i++)
				{
					m_DisplayCharaCoordinate[i].x = m_WorldCharaCoordinate[i].x + m_pMapChip->m_MapScrollX;
				}
			}
		}
	}
	if (m_PrevMapRightDirectionPosition <= m_WorldCharaCoordinate[2].x)
	{
		//右方向のブロックを確かめる
		if ((m_pMapChip->getMapChipData(MapCharaPositionY - 1, MapRightDirectionPosition) != NONE) ||
			(m_pMapChip->getMapChipData(MapCharaPositionY - 2, MapRightDirectionPosition) != NONE) ||
			(m_pMapChip->getMapChipData(MapCharaPositionY - 3, MapRightDirectionPosition) != NONE) ||
			(m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapRightDirectionPosition) != NONE))
		{
			if (m_PrevMapRightDirectionPosition != m_WorldCharaCoordinate[2].x)
			{
				m_WorldCharaCoordinate[0].x = ((MapRightDirectionPosition - 2) * CELL_SIZE) - 1;
				m_WorldCharaCoordinate[1].x = ((MapRightDirectionPosition)* CELL_SIZE) - 1;
				m_WorldCharaCoordinate[2].x = ((MapRightDirectionPosition)* CELL_SIZE) - 1;
				m_WorldCharaCoordinate[3].x = ((MapRightDirectionPosition - 2) * CELL_SIZE) - 1;
				for (int i = 0; i < 4; i++)
				{
					m_DisplayCharaCoordinate[i].x = m_WorldCharaCoordinate[i].x + m_pMapChip->m_MapScrollX - 1;
				}
			}
		}
	}
	if (!CollisionHead) {
		Jump();
	}
	else if (isJump) {
		InitJumpParam();
	}

}

bool GameChara::DownCollisionAnything(void) {
	if (MapCharaPositionY < 0 && MapLeftDirectionPosition < 0) {
		return false;
	}
	if ((m_pMapChip->getMapChipData(MapCharaPositionY, MapLeftDirectionPosition) != NONE) ||
		(m_pMapChip->getMapChipData(MapCharaPositionY, MapLeftDirectionPosition + 1) != NONE) ||
		(m_pMapChip->getMapChipData(MapCharaPositionY, MapLeftDirectionPosition + 2) != NONE)) {
		return true;
	}
	return false;
}
bool GameChara::TopCollisionAnything(void) {
	if ((m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapLeftDirectionPosition) != NONE) ||
		(m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapLeftDirectionPosition + 1) != NONE) ||
		(m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapLeftDirectionPosition + 2) != NONE)){
		return true;
	}
	return false;
}
bool GameChara::DownCollisionCheck(int block) {
	if ((m_pMapChip->getMapChipData(MapCharaPositionY, MapLeftDirectionPosition) == block) ||
		(m_pMapChip->getMapChipData(MapCharaPositionY, MapLeftDirectionPosition + 1) == block) ||
		(m_pMapChip->getMapChipData(MapCharaPositionY, MapLeftDirectionPosition + 2) == block)) {
		return true;
	}
	return false;
}
bool GameChara::TopCollisionCheck(int block) {
	if ((m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapLeftDirectionPosition) == block) ||
		(m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapLeftDirectionPosition + 1) == block) ||
		(m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapLeftDirectionPosition + 2) == block)) {
		return true;
	}
	return false;
}

bool GameChara::LeftCollisionCheck(int block) {
	if ((m_pMapChip->getMapChipData(MapCharaPositionY - 1, MapLeftDirectionPosition-1) != NONE) ||
		(m_pMapChip->getMapChipData(MapCharaPositionY - 2, MapLeftDirectionPosition-1) != NONE) ||
		(m_pMapChip->getMapChipData(MapCharaPositionY - 3, MapLeftDirectionPosition-1) != NONE) ||
		(m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapLeftDirectionPosition-1) != NONE)) {
		return true;
	}
	return false;
}
bool GameChara::RightCollisionCheck(int block) {
	if ((m_pMapChip->getMapChipData(MapCharaPositionY - 1, MapRightDirectionPosition+1) != NONE) ||
		(m_pMapChip->getMapChipData(MapCharaPositionY - 2, MapRightDirectionPosition+1) != NONE) ||
		(m_pMapChip->getMapChipData(MapCharaPositionY - 3, MapRightDirectionPosition+1) != NONE) ||
		(m_pMapChip->getMapChipData(MapCharaPositionY - 4, MapRightDirectionPosition+1) != NONE)) {
		return true;
	}
	return false;
}

void GameChara::Render()
{
	TextureRender("CHARA_INTEGRATION_TEX", m_DisplayCharaCoordinate);
	CUSTOMVERTEX TestChar[4];
	CENTRAL_STATE CharCentral = {0};
	TranslateCentral_State(&CharCentral, m_DisplayCharaCoordinate);
	CharCentral.x -= 25.f;
	CharCentral.scale_x = 120.f;
	CreateSquareVertex(CharCentral, TestChar, 0xFFFFFFFF, TESTCharBias + (Bias * TESTCharTu), ChangeAnimation * TESTCharTv, TESTCharTu*Facing, TESTCharTv);
	TextureRender("CHARA_TEX", TestChar);
#ifdef _DEBUG

	RECT test = { 0,0,1200,500 };
	char TestText[ArrayLong];
	sprintf_s(TestText, ArrayLong, "MapChara::X-L:%d,X-R:%d,Y:%d", MapLeftDirectionPosition, MapRightDirectionPosition, MapCharaPositionY);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_LEFT, 0xffffffff);
	sprintf_s(TestText, ArrayLong, "\nPrevMapChara::X-L:%d,X-R:%d,Y:%d", m_PrevMapLeftDirectionPosition, m_PrevMapRightDirectionPosition, m_PrevMapCharaPositionY);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_LEFT, 0xffffffff);
	sprintf_s(TestText, ArrayLong, "\n\nWorldChara::X-L:%.2f,X-R:%.2f,Y:%.2f", m_WorldCharaCoordinate[3].x, m_WorldCharaCoordinate[2].x, m_WorldCharaCoordinate[3].y);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_LEFT, 0xffffffff);
	sprintf_s(TestText, ArrayLong, "\n\n\nDisplayChara::X-L:%.2f,X-R:%.2f,Y3:%.2f,Y0:%.2f", m_DisplayCharaCoordinate[3].x, m_DisplayCharaCoordinate[2].x, m_DisplayCharaCoordinate[3].y, m_DisplayCharaCoordinate[0].y);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_LEFT, 0xffffffff);
	sprintf_s(TestText, ArrayLong, "\n\n\n\n\n\nAccelerationY::%.2f", AccelerationY);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_LEFT, 0xffffffff);
#endif

}

void GameChara::AddGravity() {
	//重力を毎フレームかける
	if (isScrollingDown) {
		for (int i = 0; i < 4; i++)
		{
			if (/*m_DisplayCharaCoordinate[3].y < */DisplayCharMoveScopeDown) {
				m_WorldCharaCoordinate[i].y += VerticalScrollingLevel;
			}
			m_DisplayCharaCoordinate[i].y += VerticalScrollingLevel;
		}
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		m_WorldCharaCoordinate[i].y += Gravity;
		m_DisplayCharaCoordinate[i].y += Gravity;
	}
}

void GameChara::DebugMove() {
	for (int i = 0; i < 4; i++)
	{
		m_WorldCharaCoordinate[i].y -= CharaMoveSpeed * 1.5f;
		m_DisplayCharaCoordinate[i].y -= CharaMoveSpeed * 1.5f;
	}
}

float GameChara::GetPositionX()
{
	switch (Facing) {
	case FACING_LEFT:
		return m_DisplayCharaCoordinate[0].x;
	case FACING_RIGHT:
		return m_DisplayCharaCoordinate[0].x+m_Player.scale_x;
	}
}

