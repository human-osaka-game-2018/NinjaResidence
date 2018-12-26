/**
* @file Object.h
* @brief �F�X�ȕ��̂̊��N���X
* @author Toshiya Matsuoka
*/
#pragma once
#include <vector>

#include "SCENE.h"


enum KeyInput
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
	*�L�[���͎��̓��������֐�
	*/
	virtual void KeyOperation();
	virtual void KeyOperation(KeyInput vec) {};

	virtual void Update();
	virtual void Render();
	virtual void prevSaveMapCharaPos() {};

	/*
	* @brief �e�N�X�`���̓\��t��
	* @param TextureKey �e�N�X�`���L�[
	* @param TextureSize �\��t�����W�z��̃A�h���X
	*/
	void TextureRender(std::string TextureKey, CUSTOMVERTEX* TextureSize);

	Object(DirectX* pDirectX, SoundOperater* pSoundOperater);
	Object(DirectX* pDirectX, SoundOperater* pSoundOperater, Object* MapChip) {};
	~Object();

	/**
	*@brief CUSTOMVERTEX�Ƀp�����[�^������
	* @param Vertex �l������z��
	* @param Central ���S���W���
	* @param color �F
	* @param tu �؂���摜�̍��[
	* @param tv �؂���摜�̏�[
	* @param scaleTu �؂���摜�̉E�[
	* @param scaleTv �؂���摜�̉��[
	*/
	void CreateSquareVertex(CUSTOMVERTEX* Vertex, CENTRAL_STATE Central, DWORD  color = 0xffffffff, float tu = 0, float tv = 0, float scaleTu = 1, float scaleTv = 1);
	void CreateSquareVertex(CUSTOMVERTEX* Vertex, float x, float y, DWORD  color = 0xffffffff, float tu = 0, float tv = 0, float scaleTu = 1, float scaleTv = 1);
	void CreateSquareVertex(CENTRAL_STATE Central, CUSTOMVERTEX* Vertex, DWORD  color = 0xffffffff, float tu = 0, float tv = 0, float scaleTu = 1, float scaleTv = 1);
	/**
	*@brief CUSTOMVERTEX����CENTRAL_STATE���쐬����
	* @param Central [out]
	* @param Vertex [in]
	* @sa CreateSquareVertex(CENTRAL_STATE Central, CUSTOMVERTEX* Vertex, DWORD  color, float tu, float tv, float scaleTu float scaleTv)
	* @details �֘A����CUSTOMVERTEX�쐬�֐��̋t���������
	*/
	void TranslateCentral_State(CENTRAL_STATE* Central, CUSTOMVERTEX* Vertex);

	/**
	*@brief CSV�ǂݎ��ƃ}�b�v�f�[�^����
	* @param filename CSV�t�@�C���p�X
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
		return m_row;
	}
	int getColunm() {
		return m_colunm;
	}
	int getMapChipData(int height,int width) {
		return MapData[height][width];
	}
	virtual bool RestrictBottomScroll() { return false; };
	virtual float GetBottomPoint(int charaLeft, int charRight) { return 0; };
	virtual float GetBottomWorldPoint(int charaLeft, int charRight) { return 0; };

	virtual void Reverse() {};
	virtual bool GetActive() { return false; };
	float DegToRad(float deg) {
		return deg * (D3DX_PI / 180);
	}
protected:
	DirectX* m_pDirectX = NULL;
	SoundOperater* m_pSoundManager = NULL;

	/*static */std::vector< std::vector<int> > MapData;
	//!�s
	int m_row = 0;
	//!��
	int m_colunm = 0;

	const float CELL_SIZE = 40.f;
	static const int ArrayLong = 64;
	void RevolveZ(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, DWORD  color = 0xffffffff, float tu = 0, float tv = 0, float scaleTu = 1, float scaleTv = 1);

	void RevolveZEX(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, float 	RevolvingShaftX, float 	RevolvingShaftY, DWORD  color = 0xffffffff, float tu = 0, float tv = 0, float scaleTu = 1, float scaleTv = 1);

private:
	//CENTRAL_STATE m_Central = { 400,10,(40 * 2),(40 * 4) };
	CUSTOMVERTEX m_DisplayCoordinate[4];
	CUSTOMVERTEX m_WorldCoordinate[4];
	int MapChara[5];

};
