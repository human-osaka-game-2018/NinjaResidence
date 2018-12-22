/**
* @file VOLUMESELECTSCENE.h
* @brief âπó ê›íË
* @author Toshiya Matsuoka
*/
#pragma once

#include "SCENE.h"

enum SCENE_NUM;
class Scene;

enum TargetingSoundType {
	Target_BGM,
	Target_SE,
	Target_ALL,
};

class VOLUMESELECTSCENE :public Scene
{
public:
	VOLUMESELECTSCENE(DirectX* pDirectX, SoundOperater* pSoundOperater);
	~VOLUMESELECTSCENE();

	SCENE_NUM Update();
	void Render();
	void LoadResouce();
	void SetVolume();
	void IncreaseVolume();
	void DecreaseVolume();
	int DigitCalc(int Value, int DigitNum);
	void CursorMove();
	void MoveUp();
	void MoveDown();
	void ReturnScene() {
		m_pSoundOperater->Stop("TEST");
		m_ExitScene = true;
	};
	bool GetExitScene() {
		return m_ExitScene;
	}
private:
	unsigned int m_BGMvolume = 100;
	unsigned int m_SEvolume = 100;
	unsigned int m_ALLvolume = 100;

	//! âπó ÇÃç≈ëÂåÖêîÇ∆ê›íËçÄñ⁄êî
	static const int VolumeMaxNum = 3;
	const float NumTu = (102.f / 1024.f);
	const float NumTv = (186.f / 256.f);
	const float MenuHight = (810.f / 1024.f);
	const float TriangleWidth = (137.f / 512.f);
	const float DigitWidth = 75.f;
	const float TriangleCursolHeght = 150.f;
	const DWORD WHITE = 0xFFFFFFFF;
	const CENTRAL_STATE LeftCursolNeutral = { 850,200,40,30 };
	const CENTRAL_STATE RightCursolNeutral = { 500,200,40,30 };
	const float NeutralCursorY = 195;
	TargetingSoundType m_CursolPos = Target_BGM;
	CENTRAL_STATE m_LeftCursol[VolumeMaxNum] = { { LeftCursolNeutral },{ LeftCursolNeutral },{ LeftCursolNeutral } };
	CENTRAL_STATE m_RightCursol[VolumeMaxNum] = { { RightCursolNeutral },{ RightCursolNeutral },{ RightCursolNeutral } };
	CENTRAL_STATE m_Menu = { 300,360,100,250 };
	CENTRAL_STATE m_Cursor = { 675,NeutralCursorY,250,100 };


	const CENTRAL_STATE VolumeNumNeutral = { 750,0,50,90 };
	CENTRAL_STATE m_BGMVolumeNum[VolumeMaxNum] = { { VolumeNumNeutral },{ VolumeNumNeutral },{ VolumeNumNeutral } };
	CENTRAL_STATE m_SEVolumeNum[VolumeMaxNum] = { { VolumeNumNeutral },{ VolumeNumNeutral },{ VolumeNumNeutral } };
	CENTRAL_STATE m_ALLVolumeNum[VolumeMaxNum] = { { VolumeNumNeutral },{ VolumeNumNeutral },{ VolumeNumNeutral } };
	bool m_ExitScene = false;

};

