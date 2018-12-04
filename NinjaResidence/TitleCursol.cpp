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
	//êîílÇÕâº
	switch (CursolPos) {
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

void TitleCursol::KeyOperation(KeyDirection vec) {

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
	switch (CursolPos) {
	case START:
		CursolPos = END;
		break;
	case OPTION:
		CursolPos = START;
		break;
	case END:
		CursolPos = OPTION;
		break;
	}
}
void TitleCursol::MoveDown() {
	switch (CursolPos) {
	case Cursol::START:
		CursolPos = OPTION;
		break;
	case Cursol::OPTION:
		CursolPos = END;
		break;
	case Cursol::END:
		CursolPos = START;
		break;
	}
}
CursolPosition TitleCursol::getCursolPosition() {
	return CursolPos;
}
