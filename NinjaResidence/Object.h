﻿/**
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
	virtual void PrevSaveMapPos() {};
	
	/*
	* @brief マップ内ブロックの起動処理
	* @param X 起動するブロックのマップ内X座標
	* @param Y 起動するブロックのマップ内Y座標
	*/
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
	* @brief CUSTOMVERTEXにパラメータを入れる
	* @param Vertex 値を入れる配列
	* @param Central 中心座標情報
	* @param color 色
	* @param tu 切り取り画像の左端
	* @param tv 切り取り画像の上端
	* @param scaleTu 切り取り画像の右端
	* @param scaleTv 切り取り画像の下端
	*/
	void CreateSquareVertex(CUSTOMVERTEX* Vertex, CENTRAL_STATE Central, DWORD  color = 0xffffffff, float tu = 0, float tv = 0, float scaleTu = 1, float scaleTv = 1);
	/**
	* @brief CUSTOMVERTEXにパラメータを入れる
	* @param Vertex 値を入れる配列
	* @param x 原点からのX軸距離
	* @param y 原点からのY軸距離
	* @param color 色
	* @param tu 切り取り画像の左端
	* @param tv 切り取り画像の上端
	* @param scaleTu 切り取り画像の右端
	* @param scaleTv 切り取り画像の下端
	*/
	void CreateSquareVertex(CUSTOMVERTEX* Vertex, float x, float y, DWORD  color = 0xffffffff, float tu = 0, float tv = 0, float scaleTu = 1, float scaleTv = 1);
	/**
	* @brief CUSTOMVERTEXに中心情報を左上としたパラメータの設定
	* @param Central 中心座標情報
	* @param Vertex 値を入れる配列
	* @param color 色
	* @param tu 切り取り画像の左端
	* @param tv 切り取り画像の上端
	* @param scaleTu 切り取り画像の右端
	* @param scaleTv 切り取り画像の下端
	*/
	void CreateSquareVertex(CENTRAL_STATE Central, CUSTOMVERTEX* Vertex, DWORD  color = 0xffffffff, float tu = 0, float tv = 0, float scaleTu = 1, float scaleTv = 1);
	/**
	* @brief CUSTOMVERTEXから中心情報を作成する
	* @param Central [out]
	* @param Vertex [in]
	* @details 関連するCUSTOMVERTEX作成関数の逆動作をする
	*/
	void TranslateCentral_State(CENTRAL_STATE* Central, CUSTOMVERTEX* Vertex);
	void TranslateCentral_State(CUSTOMVERTEX * Vertex, CENTRAL_STATE * Central);

	void SetVertexUV(CUSTOMVERTEX* Vertex, float Tu, float Tv, float scaleTu, float scaleTv);

	/**
	* @brief CSV読み取りとマップデータ生成
	* @param filename CSVファイルパス
	* @param MapState 表か裏かの指定
	* @sa enum MapDataState
	*/
	virtual void Create(std::string filename, MapDataState MapState) {};

	/**
	* @brief ギミックの座標取得
	* @param isAxisX 欲しい軸はX座標であるか
	* @param MapYPos マップY座標
	* @param MapXPos マップX座標
	*/
	virtual float GetGimmickPosition(bool isAxisX,int MapYPos,int MapXPos) { return 0; };

	virtual void Reverse(Object* MapChip) {};
	virtual bool GetActive() { return false; };
	float DegToRad(float deg) {
		return deg * (D3DX_PI / 180);
	}
	virtual int SearchBlockX(MapBlock::BLOCKTYPE Block) {return 3;}
	virtual int SearchBlockY(MapBlock::BLOCKTYPE Block) {return 3;}

	virtual bool GetGimmickActive() { return false; };
	virtual CUSTOMVERTEX* GetTargetPosition(int targetType) { return m_WorldCoordinate; };
	bool ContactSpecifyObject(CENTRAL_STATE* object);
	int GetMapScrollX() { return m_MapScrollX; };
	int GetMapScrollY() { return m_MapScrollY; };

	int GetRow() {
		return m_row;
	}
	int GetColunm() {
		return m_colunm;
	}
	int GetMapChipData(int height, int width) {
		return MapData[height][width];
	}

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

	static const int ARRAY_LONG = 64;
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

	static std::vector<BlockInfo> m_ReversePoint;
	static std::vector<MapScrollBuffer> m_ReverseBuffer;
	static int m_ReverseCount;
	//! ディスプレイ上のキャラの矩形
	CUSTOMVERTEX m_DisplayCoordinate[4];
	//! 全体的なキャラの矩形
	CUSTOMVERTEX m_WorldCoordinate[4];
private:

};
