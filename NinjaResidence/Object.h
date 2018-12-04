/**
* @file Object.h
* @brief 色々な物体の基底クラス
* @author Toshiya Matsuoka
*/
#pragma once
#include <vector>

#include "SCENE.h"
#include "SoundsManager.h"

using SoundLib::SoundsManager;

enum KeyDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	SPACE,
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

	virtual void Update();
	virtual void Render();
	virtual void prevSaveMapCharaPos() {};

	/*
	* @brief テクスチャの貼り付け
	* @param TextureKey テクスチャキー
	* @param TextureSize 貼り付け座標配列のアドレス
	*/
	void TextureRender(std::string TextureKey, CUSTOMVERTEX* TextureSize);

	Object(DirectX* pDirectX, SoundsManager* pSoundManager);
	Object(DirectX* pDirectX, SoundsManager* pSoundManager, Object* MapChip) {};
	~Object();

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
	*@brief CSV読み取りとマップデータ生成
	* @param filename CSVファイルパス
	*/
	virtual void Create(const char *filename) {};

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
	int m_MapScrollX = 0;
	int m_MapScrollY = 0;

	void setMapScrollX(int x){};
	void setMapScrollY(int y){};

	int getRow() {
		return row;
	}
	int getColunm() {
		return colunm;
	}
	int getMapChipData(int height,int width) {
		return MapData[height][width];
	}

protected:
	DirectX * m_pDirectX = NULL;
	SoundsManager* m_pSoundManager = NULL;

	/*static */std::vector< std::vector<int> > MapData;
	//!行
	int row = 0;
	//!列
	int colunm = 0;

	const float CELL_SIZE = 40.f;

private:
	//CENTRAL_STATE m_Central = { 400,10,(40 * 2),(40 * 4) };
	CUSTOMVERTEX m_DisplayCoordinate[4];
	CUSTOMVERTEX m_WorldCoordinate[4];
	int MapChara[5];

};
