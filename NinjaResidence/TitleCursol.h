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
	TitleCursol(DirectX* pDirectX, SoundsManager* pSoundManager);
	~TitleCursol();
private:
	CENTRAL_STATE m_Cursol = { 500,0,40,30 };
	Cursol::CursolPosition CursolPos = Cursol::START;
	void MoveUp();
	void MoveDown();
};
