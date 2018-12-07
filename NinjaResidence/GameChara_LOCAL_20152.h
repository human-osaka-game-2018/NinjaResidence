#pragma once

#include <vector>
#include "GAMESCENE.h"
#include "Object.h"


class GameScene;
class MapReverse;
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define CharaMoveSpeed 15


class GameChara :public Object
{
private:
<<<<<<< HEAD
	CENTRAL_STATE m_Player = { 400,200,(CELL_SIZE * 2),(CELL_SIZE * 4) };
=======
	CENTRAL_STATE m_Player = { 400,210,(40 * 2),(40 * 4) };
>>>>>>> Xåº§æ¨™ã®å½“ãŸã‚Šåˆ¤å®šã‚’ã‚¹ã‚¯ãƒ­ãƒ¼ãƒ«ã«å¯¾å¿œã€yåº§æ¨™ã®ã‚¹ã‚¯ãƒ­ãƒ¼ãƒ«ï¼ˆå½“ãŸã‚Šåˆ¤å®šéå¯¾å¿œï¼‰
	CUSTOMVERTEX m_DisplayCharaCoordinate[4];
	CUSTOMVERTEX m_WorldCharaCoordinate[4];
	CUSTOMVERTEX m_ReverseDisplayCharaCoordinate[4];
	CUSTOMVERTEX m_ReverseWorldCharaCoordinate[4];
	CUSTOMVERTEX m_SurfaceDisplayCharaCoordinate[4];
	CUSTOMVERTEX m_SurfaceWorldCharaCoordinate[4];
	int m_PrevMapLeftDirectionPosition;//‘OƒtƒŒ[ƒ€‚ÌMapLeftDirectionPosition‚Ì’l
	int m_PrevMapRightDirectionPosition;//‘OƒtƒŒ[ƒ€‚ÌMapRightDirectionPosition‚Ì’l
	int m_PrevMapCharaPositionY;//‘OƒtƒŒ[ƒ€‚ÌMapCharaPositionY‚Ì’l
	int MapLeftDirectionPosition;//ƒLƒƒƒ‰‚Ì¶‘¤‚ÌXÀ•W
	int MapRightDirectionPosition;//ƒLƒƒƒ‰‚Ì‰E‘¤‚ÌXÀ•W
	int MapCharaPositionY;//ƒLƒƒƒ‰‚Ìã‘¤‚ÌxÀ•W
	float Gravity;//–ˆƒtƒŒ[ƒ€‚©‚¯‚éd—Í‚Ì’l
	const int DisplayCharMoveScopeUp = 100;//m_DisplayCharaCoordinate‚ÌYÀ•W‚ª‚±‚Ì’l‚ğ‰º‰ñ‚é‚Æã‚ÉƒXƒNƒ[ƒ‹‚·‚é
	const int DisplayCharMoveScopeDown = 630;//m_DisplayCharaCoordinate‚ÌYÀ•W‚ª‚±‚Ì’l‚ğ’´‚¦‚é‚Æã‚ÉƒXƒNƒ[ƒ‹‚·‚é
	const int DisplayCharMoveScopeLeft = 300;//m_DisplayCharaCoordinate‚ÌXÀ•W‚ª‚±‚Ì’l‚ğ‰º‰ñ‚é‚Æ¶‚ÉƒXƒNƒ[ƒ‹‚·‚é
	const int DisplayCharMoveScopeRight = 980;//m_DisplayCharaCoordinate‚ÌXÀ•W‚ª‚±‚Ì’l‚ğ’´‚¦‚é‚Æ‰E‚ÉƒXƒNƒ[ƒ‹‚·‚é
	const int DisplayCharMoveScopeX = 300;//—¼’[‚©‚ç‚ÌXÀ•W‚Ì‰Ò“­”ÍˆÍ
	void CharaMoveOperation(KeyDirection vec, CUSTOMVERTEX* pWorldCharaCoordinate, CUSTOMVERTEX* pDisplayCharaCoordinate, float MoveQuantity);
	void ValueAllSetCUSTOMVERTEX(CUSTOMVERTEX* Receive, CUSTOMVERTEX* Give);
	void MapScroolCheck();
	MapReverse* m_pMapReverse = NULL;
	Object* m_pMapChip = NULL;
	float CharTu = 80 / 512.f;
	float CharTv = 160 / 512.f;
public:
<<<<<<< HEAD
	CUSTOMVERTEX GetDisplayCharaCoordinate(){return m_DisplayCharaCoordinate[4];}
	int GetMapCharaPositionX() { return MapLeftDirectionPosition; }
	int GetMapCharaPositionY() { return MapCharaPositionY; }
	void prevSaveMapCharaPos();
	void KeyOperation(KeyDirection vec);
	void CharaInforSave(int MapReverse1, Object* MapChip);
	void Update();
	void Render();
	GameChara(DirectX* pDirectX, Object* MapChip);
=======
	koujirou abc;
	Scene * m_pScene;
	MapChip * m_pMapChip;
	void GameCharaKeyOperation();
	void MapScroolCheck();
	bool RectToRectCollisionCheak(CUSTOMVERTEX* pObjA, CUSTOMVERTEX* pObjB);
	void GameCharaUpdate();
	void GameCharaRender();
	GameChara(Scene * pScene);
>>>>>>> Xåº§æ¨™ã®å½“ãŸã‚Šåˆ¤å®šã‚’ã‚¹ã‚¯ãƒ­ãƒ¼ãƒ«ã«å¯¾å¿œã€yåº§æ¨™ã®ã‚¹ã‚¯ãƒ­ãƒ¼ãƒ«ï¼ˆå½“ãŸã‚Šåˆ¤å®šéå¯¾å¿œï¼‰
	~GameChara();
};
