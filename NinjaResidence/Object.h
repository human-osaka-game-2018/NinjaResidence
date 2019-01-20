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
	FIRE,
	END_ART,
	BIT_UP,
	BIT_DOWN,
	BIT_RIGHT,
	BIT_LEFT,
	SoundOn,
};
struct MapScrollBuffer {
	int ScrollX = 0;
	int ScrollY = -1000;
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

	void TranslateCentral_State(CUSTOMVERTEX * Vertex, CENTRAL_STATE * Central);

	/**
	*@brief CSV読み取りとマップデータ生成
	* @param filename CSVファイルパス
	* @param MapState 表か裏かの指定
	* @sa enum MapDataState
	*/
	virtual void Create(std::string filename, MapDataState MapState) {};


	int GetMapScrollX() { return m_MapScrollX; };
	int GetMapScrollY() { return m_MapScrollY; };

	int getRow() {
		return m_row;
	}
	int getColunm() {
		return m_colunm;
	}
	int getMapChipData(int height, int width) {
		return MapData[height][width];
	}
	virtual float GetGimmickPosition(bool isAxisX,int MapYPos,int MapXPos) { return 0; };
	virtual bool RestrictBottomScroll() { return false; };
	virtual float GetBottomPoint(int charaLeft, int charRight) { return 0; };
	virtual float GetBottomWorldPoint(int charaLeft, int charRight) { return 0; };

	virtual void Reverse(Object* MapChip) {};
	virtual bool GetActive() { return false; };
	float DegToRad(float deg) {
		return deg * (D3DX_PI / 180);
	}
	virtual int SearchBlockX(MapBlock::BLOCKTYPE Block) {return 3;}
	virtual int SearchBlockY(MapBlock::BLOCKTYPE Block) {return 3;}

	void GameCharaInfo(int CharaX, int CharaY);
	virtual bool GetGimmickActive() { return false; };
	virtual CUSTOMVERTEX* GetTargetPosition(int targetType) { return m_WorldCoordinate; };
	bool ContactSpecifyObject(CENTRAL_STATE* object);
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
	virtual MapDataState GetMapDataState() {
		MapDataState State = STATE_FALSE;
		return State;
	}

protected:
	DirectX* m_pDirectX = NULL;
	SoundOperater* m_pSoundOperater = NULL;
	CENTRAL_STATE m_Central;
	static int m_MapScrollX;
	static int m_MapScrollY;

	std::vector< std::vector<int> > MapData;
	
	//!行
	int m_row = 0;
	//!列
	int m_colunm = 0;

	static const int ArrayLong = 64;
	//! Z軸回転
	void RevolveZ(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, DWORD  color = 0xffffffff, float tu = 0, float tv = 0, float scaleTu = 1, float scaleTv = 1);
	//! 回転する中心を指定してZ軸回転
	void RevolveZEX(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, float 	RevolvingShaftX, float 	RevolvingShaftY, DWORD  color = 0xffffffff, float tu = 0, float tv = 0, float scaleTu = 1, float scaleTv = 1);
	/**
	* @brief 貼り付ける画像の回転
	* @param Vertex 回転させる頂点情報
	* @param Deg 90度右に何回転させるか
	*/
	void RevolveTexture(CUSTOMVERTEX * Vertex, int Deg);
	//! テキストファイルに指定の文字列を上書きする
	void WriteLog(std::string Text);

	static std::vector<BlockInfo> ReversePointVector;
	static std::vector<MapScrollBuffer> m_ReverseBuffer;
	static int m_ReverseCount;
private:
	CUSTOMVERTEX m_DisplayCoordinate[4];
	CUSTOMVERTEX m_WorldCoordinate[4];
	int MapChara[5];

};
