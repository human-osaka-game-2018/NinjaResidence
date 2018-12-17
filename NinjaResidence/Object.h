/**
* @file Object.h
* @brief 色々な物体の基底クラス
* @author Toshiya Matsuoka
*/
#pragma once
#include <vector>

#include "SCENE.h"
#include "BlockInfo.h"
#include "MapBlock.h"


enum KeyDirection
{
	PUSH_NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	JUMP,
	MOVE_LEFT,
	MOVE_RIGHT,
	SPACE,
	THROW,
	SoundOn,
};

class Object
{
public:
	/*
	*キー入力時の内部処理関数
	*/
	virtual void KeyOperation();
	virtual void KeyOperation(KeyDirection vec) {};

	virtual bool Update();

	virtual void Render() {};
	virtual void Render(bool MapDataReverse);
	virtual void prevSaveMapCharaPos() {};
	virtual void Activate(int X,int Y) {};
	/*
	* @brief テクスチャの貼り付け
	* @param TextureKey テクスチャキー
	* @param TextureSize 貼り付け座標配列のアドレス
	*/
	void TextureRender(std::string TextureKey, CUSTOMVERTEX* TextureSize);

	Object(DirectX* pDirectX, SoundOperater* pSoundOperater);
	Object(DirectX* pDirectX, SoundOperater* pSoundOperater, Object* MapChip) {};
	virtual ~Object();

	/**
	*@brief CUSTOMVERTEXにパラメータを入れる
	* @param Vertex 値を入れる配列
	* @param Central 中心座標情報
	* @param color 色
	* @param tu 切り取り画像の左端
	* @param tv 切り取り画像の上端
	* @param scaleTu 切り取り画像の右端
	* @param scaleTv 切り取り画像の下端
	*/
	void CreateSquareVertex(CUSTOMVERTEX* Vertex, CENTRAL_STATE Central, DWORD  color = 0xffffffff, float tu = 0, float tv = 0, float scaleTu = 1, float scaleTv = 1);
	void CreateSquareVertex(CUSTOMVERTEX* Vertex, float x, float y, DWORD  color = 0xffffffff, float tu = 0, float tv = 0, float scaleTu = 1, float scaleTv = 1);
	void CreateSquareVertex(CENTRAL_STATE Central, CUSTOMVERTEX* Vertex, DWORD  color = 0xffffffff, float tu = 0, float tv = 0, float scaleTu = 1, float scaleTv = 1);
	/**
	*@brief CUSTOMVERTEXからCENTRAL_STATEを作成する
	* @param Central [out]
	* @param Vertex [in]
	* @sa CreateSquareVertex(CENTRAL_STATE Central, CUSTOMVERTEX* Vertex, DWORD  color, float tu, float tv, float scaleTu float scaleTv)
	* @details 関連するCUSTOMVERTEX作成関数の逆動作をする
	*/
	void TranslateCentral_State(CENTRAL_STATE* Central, CUSTOMVERTEX* Vertex);

	/**
	*@brief CSV読み取りとマップデータ生成
	* @param filename CSVファイルパス
	*/
	virtual void Create(const char *filename, MapDataState MapState) {};

	struct MAPCharPosition {
		int X;
		int Y;
	};

	MAPCharPosition MapCharaPosition;

	int getMapCharaPositionX() {
		return MapCharaPosition.X;
	};
	int getMapCharaPositionY() {
		return MapCharaPosition.Y;
	};

	void setMapScrollX(int x) {};
	void setMapScrollY(int y) {};

	int getRow() {
		return m_row;
	}
	int getColunm() {
		return m_colunm;
	}
	int getMapChipData(int height, int width) {
		return MapData[height][width];
	}
	virtual bool RestrictBottomScroll() { return false; };
	virtual float GetBottomPoint(int charaLeft, int charRight) { return 0; };
	virtual float GetBottomWorldPoint(int charaLeft, int charRight) { return 0; };

	virtual void Reverse(Object* MapChip) {};
	virtual bool GetActive() { return false; };
	float DegToRad(float deg) {
		return deg * (D3DX_PI / 180);
	}
	virtual int SearchBlockX(MapBlock::BLOCKTYPE Block) {return 0;}
	virtual int SearchBlockY(MapBlock::BLOCKTYPE Block) {return 0;}

	void GameCharaInfo(int CharaX, int CharaY);

	int getm_CharaX()
	{
		return m_CharaX;
	}
	int getm_CharaY()
	{
		return m_CharaY;
	}

	int m_CharaX;
	int m_CharaY;
protected:
	DirectX* m_pDirectX = NULL;
	SoundOperater* m_pSoundOperater = NULL;

	static int m_MapScrollX;
	static int m_MapScrollY;

	std::vector< std::vector<int> > MapData;
	
	//!行
	int m_row = 0;
	//!列
	int m_colunm = 0;

	static const int ArrayLong = 64;
	void RevolveZ(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, DWORD  color = 0xffffffff, float tu = 0, float tv = 0, float scaleTu = 1, float scaleTv = 1);

	void RevolveZEX(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, float 	RevolvingShaftX, float 	RevolvingShaftY, DWORD  color = 0xffffffff, float tu = 0, float tv = 0, float scaleTu = 1, float scaleTv = 1);

private:
	//CENTRAL_STATE m_Central = { 400,10,(40 * 2),(40 * 4) };
	CUSTOMVERTEX m_DisplayCoordinate[4];
	CUSTOMVERTEX m_WorldCoordinate[4];
	int MapChara[5];

};
