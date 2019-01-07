/**
* @file TitleCursol.h
* @brief タイトルのカーソル処理
* @author Toshiya Matsuoka
*/
#pragma once

#include "Object.h"

namespace Cursol {
	enum CursolPosition {
		START,
		OPTION,
		END
	};
};

class TitleCursol :public Object
{
public:
	void KeyOperation(KeyDirection vec);
	void Update();
	void Render();
	Cursol::CursolPosition getCursolPosition();
	TitleCursol(DirectX* pDirectX, SoundOperater* pSoundOperater);
	~TitleCursol();
private:
	CENTRAL_STATE m_Cursol = { 480,0,40,30 };
	Cursol::CursolPosition m_CursolPos = Cursol::START;
	void MoveUp();
	void MoveDown();
};
