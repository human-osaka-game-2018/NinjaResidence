/**
* @file GameChara.cpp
* @brief GameChara�N���X
* @author Kojiro Kawahara
*/
#include "GameChara.h"

using  namespace MapBlock;
using namespace PlayerAnimation;

GameChara::GameChara(DirectX* pDirectX, SoundsManager* pSoundManager, Object* MapChip) :Object(pDirectX,pSoundManager)
{
	//MapChip�̏����擾���邽�߂ɕK�v
	m_pMapChip = MapChip;
	m_row = m_pMapChip->getRow();
	m_colunm = m_pMapChip->getColunm();
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
	m_isInTheAir = !DownCollisionAnything();
	m_HeldOntoWallLeft = LeftCollisionCheck(ROCK_BLOCK);
	m_HeldOntoWallRight = RightCollisionCheck(ROCK_BLOCK);


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
	m_MapCharaPositionY = (int)(m_WorldCharaCoordinate[3].y + 10) / CELL_SIZE;
	m_ChangeAnimation = JUMPING;
	if (m_RiseFlameTime < 15) {
		m_RiseFlameTime++;
		AccelarationControl();
		JumpingLateralMotion();
		return;
	}

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
		//�E�Ɉړ�
		for (int i = 0; i < 4; i++)
		{
			m_WorldCharaCoordinate[i].x += m_AccelerationX;
			m_DisplayCharaCoordinate[i].x += m_AccelerationX;
		}
		//if (m_AccelerationX > 0) {
		//	m_AccelerationX -= 0.1f;
		//}

	}
	if (m_isJumpLeft) {
		//���Ɉړ�
		for (int i = 0; i < 4; i++)
		{
			m_WorldCharaCoordinate[i].x -= m_AccelerationX;
			m_DisplayCharaCoordinate[i].x -= m_AccelerationX;
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
		//��Ɉړ�
	case JUMP:

		m_isJump = PermitJumping();
		break;
	case DOWN:
		//���̂Ƃ���Ȃ�

		break;
	case MOVE_RIGHT:
		//�E�Ɉړ�
		m_ChangeAnimation = DASH;
		m_Facing = FACING_RIGHT;
		m_Bias = ZERO;
		for (int i = 0;i < 4;i++)
		{
			m_WorldCharaCoordinate[i].x += CharaMoveSpeed;
			m_DisplayCharaCoordinate[i].x += CharaMoveSpeed;
		}
		break;
	case MOVE_LEFT:
		//���Ɉړ�
		m_ChangeAnimation = DASH;
		m_Facing = FACING_LEFT;
		m_Bias = ONE;
		for (int i = 0;i < 4;i++)
		{
			m_WorldCharaCoordinate[i].x -= CharaMoveSpeed;
			m_DisplayCharaCoordinate[i].x -= CharaMoveSpeed;
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
	//Key����ł̏���
	switch (vec)
	{
	case JUMP:
		CharaMoveOperation(JUMP);
		break;
	case DOWN:
		//���̂Ƃ��떳��
		break;
	case MOVE_RIGHT:
		//�E�Ɉړ�
		CharaMoveOperation(MOVE_RIGHT);
		break;
	case MOVE_LEFT:
		//���Ɉړ�
		CharaMoveOperation(MOVE_LEFT);
		break;
	case SoundOn:
		m_pSoundManager->Start("DECISION");
		break;
	case PUSH_NONE:
		NoOperation();
		break;
	case THROW:
		//if (isThrowing) {
			m_ChangeAnimation = THROWING;
		//}
		//isThrowing = !isThrowing;
		break;
	}
}

void GameChara::NoOperation() {
	if (DownCollisionAnything()) {
		m_ChangeAnimation = STAND;
	}

}

void GameChara::CharaInforSave(int MapReverseSelect,Object* MapChip)
{
	m_pMapChip = MapChip;
	m_row = m_pMapChip->getRow();
	m_colunm = m_pMapChip->getColunm();

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
	//�L���������蔻�肪2�i�̒n�ʂ̊Ԃɋz���Ă���
	if (m_pMapChip->RestrictBottomScroll()){
		m_pMapChip->m_MapScrollY += VerticalScrollingLevel;
		m_WorldCharaCoordinate[0].y = m_pMapChip->GetBottomWorldPoint(m_MapLeftDirectionPosition, m_MapRightDirectionPosition);
		m_WorldCharaCoordinate[1].y = m_pMapChip->GetBottomWorldPoint(m_MapLeftDirectionPosition, m_MapRightDirectionPosition);
		m_WorldCharaCoordinate[2].y = m_pMapChip->GetBottomWorldPoint(m_MapLeftDirectionPosition, m_MapRightDirectionPosition) + m_Player.scale_y;
		m_WorldCharaCoordinate[3].y = m_pMapChip->GetBottomWorldPoint(m_MapLeftDirectionPosition, m_MapRightDirectionPosition) + m_Player.scale_y;
		m_DisplayCharaCoordinate[0].y = m_pMapChip->GetBottomPoint(m_MapLeftDirectionPosition, m_MapRightDirectionPosition);
		m_DisplayCharaCoordinate[1].y = m_pMapChip->GetBottomPoint(m_MapLeftDirectionPosition, m_MapRightDirectionPosition);
		m_DisplayCharaCoordinate[2].y = m_pMapChip->GetBottomPoint(m_MapLeftDirectionPosition, m_MapRightDirectionPosition) + m_Player.scale_y;
		m_DisplayCharaCoordinate[3].y = m_pMapChip->GetBottomPoint(m_MapLeftDirectionPosition, m_MapRightDirectionPosition) + m_Player.scale_y;
	}
	//���ɃX�N���[���ړ�
	else if (m_DisplayCharaCoordinate[3].y > DisplayCharMoveScopeDown)
	{
		m_DisplayCharaCoordinate[0].y = (DisplayCharMoveScopeDown - m_Player.scale_y);
		m_DisplayCharaCoordinate[1].y = (DisplayCharMoveScopeDown - m_Player.scale_y);
		m_DisplayCharaCoordinate[2].y = (DisplayCharMoveScopeDown);
		m_DisplayCharaCoordinate[3].y = (DisplayCharMoveScopeDown);
		m_pMapChip->m_MapScrollY -= VerticalScrollingLevel;
		
		m_isScrollingDown = true;
	}
	else m_isScrollingDown = false;
	//��ɃX�N���[���ړ�
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

	//�E�ɃX�N���[���ړ�
	if (m_DisplayCharaCoordinate[1].x > DisplayCharMoveScopeRight)
	{
		if (m_WorldCharaCoordinate[1].x <= ((m_row * CELL_SIZE)- DisplayCharMoveScopeX))
		{
			m_DisplayCharaCoordinate[0].x = (DisplayCharMoveScopeRight - m_Player.scale_x);
			m_DisplayCharaCoordinate[1].x = (DisplayCharMoveScopeRight);
			m_DisplayCharaCoordinate[2].x = (DisplayCharMoveScopeRight);
			m_DisplayCharaCoordinate[3].x = (DisplayCharMoveScopeRight - m_Player.scale_x);
			m_pMapChip->m_MapScrollX -= CharaMoveSpeed;
		}
	}
	//���ɃX�N���[���ړ�
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

	if (m_ChangeAnimation == THROWING) {
		ThrowAnimeOn = true;
	}
	if (ThrowAnimeOn) {
		AnimationCount++;
	}
	else return;
	if (AnimationCount < 20) {
		m_ChangeAnimation = THROWING;
	}
	else {
		AnimationCount = 0;
		ThrowAnimeOn = false;
		m_ChangeAnimation = STAND;
	}
}
void GameChara::Update()
{
	ThrowAnime();
	m_MapLeftDirectionPosition = (int)m_WorldCharaCoordinate[3].x / CELL_SIZE;
	m_MapRightDirectionPosition = (int)(m_WorldCharaCoordinate[2].x) / CELL_SIZE;
	m_MapCharaPositionY = (int)(m_WorldCharaCoordinate[3].y + 10) / CELL_SIZE;
	if (m_MapCharaPositionY >= m_colunm) {
		m_MapCharaPositionY = m_colunm - 1;
	}
	m_CollisionHead = TopCollisionAnything();

	MapScroolCheck();
	AddGravity();
	//���̕������m���߂�
	if (DownCollisionAnything())
	{
		m_WorldCharaCoordinate[0].y = ((m_MapCharaPositionY - 4) * CELL_SIZE);
		m_WorldCharaCoordinate[1].y = ((m_MapCharaPositionY - 4) * CELL_SIZE);
		m_WorldCharaCoordinate[2].y = ((m_MapCharaPositionY)* CELL_SIZE);
		m_WorldCharaCoordinate[3].y = ((m_MapCharaPositionY)* CELL_SIZE);
		for (int i = 0; i < 4; i++)
		{
			m_DisplayCharaCoordinate[i].y = m_WorldCharaCoordinate[i].y + m_pMapChip->m_MapScrollY;
		}
		//2�i����n�ʂɂ߂荞�񂾂Ƃ��̕��A����
		if (m_pMapChip->getMapChipData(m_MapCharaPositionY - 1, m_MapLeftDirectionPosition + 1) != NONE) {
			for (int i = 0; i < 4; i++)
			{
				m_WorldCharaCoordinate[i].y -= CELL_SIZE;
				m_DisplayCharaCoordinate[i].y -= m_WorldCharaCoordinate[i].y + m_pMapChip->m_MapScrollY;
			}

		}
	}
	else 	m_ChangeAnimation = JUMPING;

	//��̃u���b�N���m���߂�
	if (m_PrevMapCharaPositionY > m_WorldCharaCoordinate[3].y + 10)
	{
		if ((m_pMapChip->getMapChipData(m_MapCharaPositionY - 4, m_MapLeftDirectionPosition) != NONE) ||
			(m_pMapChip->getMapChipData(m_MapCharaPositionY - 4, m_MapLeftDirectionPosition + 1) != NONE) ||
			(m_pMapChip->getMapChipData(m_MapCharaPositionY - 4, m_MapLeftDirectionPosition + 2) != NONE))
		{
			m_WorldCharaCoordinate[0].y = ((m_MapCharaPositionY - 3) * CELL_SIZE);
			m_WorldCharaCoordinate[1].y = ((m_MapCharaPositionY - 3) * CELL_SIZE);
			m_WorldCharaCoordinate[2].y = ((m_MapCharaPositionY + 1) * CELL_SIZE);
			m_WorldCharaCoordinate[3].y = ((m_MapCharaPositionY + 1) * CELL_SIZE);
			for (int i = 0; i < 4; i++)
			{
				m_DisplayCharaCoordinate[i].y = m_WorldCharaCoordinate[i].y + m_pMapChip->m_MapScrollY;
			}
		}
	}
	if (m_PrevMapLeftDirectionPosition >= m_WorldCharaCoordinate[3].x)
	{
		//���̕����̃u���b�N���m���߂�
		if ((m_pMapChip->getMapChipData(m_MapCharaPositionY - 1, m_MapLeftDirectionPosition) != NONE) ||
			(m_pMapChip->getMapChipData(m_MapCharaPositionY - 2, m_MapLeftDirectionPosition) != NONE) ||
			(m_pMapChip->getMapChipData(m_MapCharaPositionY - 3, m_MapLeftDirectionPosition) != NONE) ||
			(m_pMapChip->getMapChipData(m_MapCharaPositionY - 4, m_MapLeftDirectionPosition) != NONE))
		{
			if (m_PrevMapLeftDirectionPosition != m_WorldCharaCoordinate[3].x)
			{
				m_WorldCharaCoordinate[0].x = ((m_MapLeftDirectionPosition + 1) * CELL_SIZE);
				m_WorldCharaCoordinate[1].x = ((m_MapLeftDirectionPosition + 3) * CELL_SIZE);
				m_WorldCharaCoordinate[2].x = ((m_MapLeftDirectionPosition + 3) * CELL_SIZE);
				m_WorldCharaCoordinate[3].x = ((m_MapLeftDirectionPosition + 1) * CELL_SIZE);
				for (int i = 0; i < 4; i++)
				{
					m_DisplayCharaCoordinate[i].x = m_WorldCharaCoordinate[i].x + m_pMapChip->m_MapScrollX;
				}
			}
		}
	}
	if (m_PrevMapRightDirectionPosition <= m_WorldCharaCoordinate[2].x)
	{
		//�E�����̃u���b�N���m���߂�
		if ((m_pMapChip->getMapChipData(m_MapCharaPositionY - 1, m_MapRightDirectionPosition) != NONE) ||
			(m_pMapChip->getMapChipData(m_MapCharaPositionY - 2, m_MapRightDirectionPosition) != NONE) ||
			(m_pMapChip->getMapChipData(m_MapCharaPositionY - 3, m_MapRightDirectionPosition) != NONE) ||
			(m_pMapChip->getMapChipData(m_MapCharaPositionY - 4, m_MapRightDirectionPosition) != NONE))
		{
			if (m_PrevMapRightDirectionPosition != m_WorldCharaCoordinate[2].x)
			{
				m_WorldCharaCoordinate[0].x = ((m_MapRightDirectionPosition - 2) * CELL_SIZE) - 1;
				m_WorldCharaCoordinate[1].x = ((m_MapRightDirectionPosition)* CELL_SIZE) - 1;
				m_WorldCharaCoordinate[2].x = ((m_MapRightDirectionPosition)* CELL_SIZE) - 1;
				m_WorldCharaCoordinate[3].x = ((m_MapRightDirectionPosition - 2) * CELL_SIZE) - 1;
				for (int i = 0; i < 4; i++)
				{
					m_DisplayCharaCoordinate[i].x = m_WorldCharaCoordinate[i].x + m_pMapChip->m_MapScrollX - 1;
				}
			}
		}
	}
	if (!m_CollisionHead) {
		Jump();
	}
	else if (m_isJump) {
		InitJumpParam();
	}

}

bool GameChara::DownCollisionAnything(void) {
	if (m_MapCharaPositionY < 0 && m_MapLeftDirectionPosition < 0) {
		return false;
	}
	if ((m_pMapChip->getMapChipData(m_MapCharaPositionY, m_MapLeftDirectionPosition) != NONE) ||
		(m_pMapChip->getMapChipData(m_MapCharaPositionY, m_MapLeftDirectionPosition + 1) != NONE) ||
		(m_pMapChip->getMapChipData(m_MapCharaPositionY, m_MapLeftDirectionPosition + 2) != NONE)) {
		return true;
	}
	return false;
}
bool GameChara::TopCollisionAnything(void) {
	if ((m_pMapChip->getMapChipData(m_MapCharaPositionY - 4, m_MapLeftDirectionPosition) != NONE) ||
		(m_pMapChip->getMapChipData(m_MapCharaPositionY - 4, m_MapLeftDirectionPosition + 1) != NONE) ||
		(m_pMapChip->getMapChipData(m_MapCharaPositionY - 4, m_MapLeftDirectionPosition + 2) != NONE)){
		return true;
	}
	return false;
}
bool GameChara::DownCollisionCheck(int block) {
	if ((m_pMapChip->getMapChipData(m_MapCharaPositionY, m_MapLeftDirectionPosition) == block) ||
		(m_pMapChip->getMapChipData(m_MapCharaPositionY, m_MapLeftDirectionPosition + 1) == block) ||
		(m_pMapChip->getMapChipData(m_MapCharaPositionY, m_MapLeftDirectionPosition + 2) == block)) {
		return true;
	}
	return false;
}
bool GameChara::TopCollisionCheck(int block) {
	if ((m_pMapChip->getMapChipData(m_MapCharaPositionY - 4, m_MapLeftDirectionPosition) == block) ||
		(m_pMapChip->getMapChipData(m_MapCharaPositionY - 4, m_MapLeftDirectionPosition + 1) == block) ||
		(m_pMapChip->getMapChipData(m_MapCharaPositionY - 4, m_MapLeftDirectionPosition + 2) == block)) {
		return true;
	}
	return false;
}

bool GameChara::LeftCollisionCheck(int block) {
	if ((m_pMapChip->getMapChipData(m_MapCharaPositionY - 1, m_MapLeftDirectionPosition-1) != NONE) ||
		(m_pMapChip->getMapChipData(m_MapCharaPositionY - 2, m_MapLeftDirectionPosition-1) != NONE) ||
		(m_pMapChip->getMapChipData(m_MapCharaPositionY - 3, m_MapLeftDirectionPosition-1) != NONE) ||
		(m_pMapChip->getMapChipData(m_MapCharaPositionY - 4, m_MapLeftDirectionPosition-1) != NONE)) {
		return true;
	}
	return false;
}
bool GameChara::RightCollisionCheck(int block) {
	if ((m_pMapChip->getMapChipData(m_MapCharaPositionY - 1, m_MapRightDirectionPosition+1) != NONE) ||
		(m_pMapChip->getMapChipData(m_MapCharaPositionY - 2, m_MapRightDirectionPosition+1) != NONE) ||
		(m_pMapChip->getMapChipData(m_MapCharaPositionY - 3, m_MapRightDirectionPosition+1) != NONE) ||
		(m_pMapChip->getMapChipData(m_MapCharaPositionY - 4, m_MapRightDirectionPosition+1) != NONE)) {
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
	CreateSquareVertex(CharCentral, TestChar, 0xFFFFFFFF, m_TESTCharBias + (m_Bias * m_TESTCharTu), m_ChangeAnimation * m_TESTCharTv, m_TESTCharTu*m_Facing, m_TESTCharTv);
	TextureRender("CHARA_TEX", TestChar);
#ifdef _DEBUG

	RECT test = { 0,0,1200,500 };
	char TestText[ArrayLong];
	sprintf_s(TestText, ArrayLong, "MapChara::X-L:%d,X-R:%d,Y:%d", m_MapLeftDirectionPosition, m_MapRightDirectionPosition, m_MapCharaPositionY);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_LEFT, 0xffffffff);
	sprintf_s(TestText, ArrayLong, "\nPrevMapChara::X-L:%d,X-R:%d,Y:%d", m_PrevMapLeftDirectionPosition, m_PrevMapRightDirectionPosition, m_PrevMapCharaPositionY);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_LEFT, 0xffffffff);
	sprintf_s(TestText, ArrayLong, "\n\nWorldChara::X-L:%.2f,X-R:%.2f,Y:%.2f", m_WorldCharaCoordinate[3].x, m_WorldCharaCoordinate[2].x, m_WorldCharaCoordinate[3].y);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_LEFT, 0xffffffff);
	sprintf_s(TestText, ArrayLong, "\n\n\nDisplayChara::X-L:%.2f,X-R:%.2f,Y3:%.2f,Y0:%.2f", m_DisplayCharaCoordinate[3].x, m_DisplayCharaCoordinate[2].x, m_DisplayCharaCoordinate[3].y, m_DisplayCharaCoordinate[0].y);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_LEFT, 0xffffffff);
	sprintf_s(TestText, ArrayLong, "\n\n\n\n\n\nAccelerationY::%.2f", m_AccelerationY);
	m_pDirectX->DrawWord(test, TestText, "DEBUG_FONT", DT_LEFT, 0xffffffff);
#endif

}

void GameChara::AddGravity() {
	//�d�͂𖈃t���[��������
	if (m_isScrollingDown) {
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
	switch (m_Facing) {
	case FACING_LEFT:
		return m_DisplayCharaCoordinate[0].x;
	case FACING_RIGHT:
		return m_DisplayCharaCoordinate[0].x+m_Player.scale_x;
	}
}

