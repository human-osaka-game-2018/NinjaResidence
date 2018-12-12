/**
* @file TitleCursol.cpp
* @brief タイトルのカーソル処理
* @author Toshiya Matsuoka
*/
#include "TITLESCENE.h"
#include "TitleCursol.h"

using namespace Cursol;

TitleCursol::TitleCursol(DirectX* pDirectX, SoundsManager* pSoundManager) :Object(pDirectX, pSoundManager)
{

}

TitleCursol::~TitleCursol()
{

}

void TitleCursol::Update() {
	//数値は仮
	switch (m_CursolPos) {
	case START:
		m_Cursol.y = 440;
		break;
	case OPTION:
		m_Cursol.y = 520;
		break;
	case END:
		m_Cursol.y = 580;
		break;
	}

}
void TitleCursol::Render()
{
	CUSTOMVERTEX CursolVertex[4];
	CreateSquareVertex(CursolVertex,m_Cursol);
	TextureRender("CURSOL_TEX", CursolVertex);

}

void TitleCursol::KeyOperation(KeyInput vec) {

	switch (vec)
	{
	case UP:
		MoveUp();
		break;
	case DOWN:
		MoveDown();
		break;
	};
}
void TitleCursol::MoveUp() {
	switch (m_CursolPos) {
	case START:
		m_CursolPos = END;
		break;
	case OPTION:
		m_CursolPos = START;
		break;
	case END:
		m_CursolPos = OPTION;
		break;
	}
}
void TitleCursol::MoveDown() {
	switch (m_CursolPos) {
	case Cursol::START:
		m_CursolPos = OPTION;
		break;
	case Cursol::OPTION:
		m_CursolPos = END;
		break;
	case Cursol::END:
		m_CursolPos = START;
		break;
	}
}
CursolPosition TitleCursol::getCursolPosition() {
	return m_CursolPos;
}
