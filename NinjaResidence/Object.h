/**
* @file Object.h
* @brief �F�X�ȕ��̂̊��N���X
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
	*�L�[���͎��̓��������֐�
	*/
	virtual void KeyOperation();
	virtual void KeyOperation(KeyDirection vec) {};

	virtual void Update();
	virtual void Render();
	virtual void prevSaveMapCharaPos() {};

	/*
	* @brief �e�N�X�`���̓\��t��
	* @param TextureKey �e�N�X�`���L�[
	* @param TextureSize �\��t�����W�z��̃A�h���X
	*/
	void TextureRender(std::string TextureKey, CUSTOMVERTEX* TextureSize);

	Object(DirectX* pDirectX, SoundsManager* pSoundManager);
	Object(DirectX* pDirectX, SoundsManager* pSoundManager, Object* MapChip) {};
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
	//!�s
	int row = 0;
	//!��
	int colunm = 0;

	const float CELL_SIZE = 40.f;

private:
	//CENTRAL_STATE m_Central = { 400,10,(40 * 2),(40 * 4) };
	CUSTOMVERTEX m_DisplayCoordinate[4];
	CUSTOMVERTEX m_WorldCoordinate[4];
	int MapChara[5];

};
