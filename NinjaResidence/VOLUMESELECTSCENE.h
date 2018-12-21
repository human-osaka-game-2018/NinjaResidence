#pragma once

#include "SCENE.h"

enum SCENE_NUM;
class Scene;


class VOLUMESELECTSCENE :public Scene
{
public:
	VOLUMESELECTSCENE(DirectX* pDirectX, SoundsManager* pSoundManager);
	~VOLUMESELECTSCENE();

	SCENE_NUM Update();
	void Render();
	void LoadResouce();
	void SetVolume();
	void IncreaseVolume(int* Volume);
	void DecreaseVolume(int * Volume);
	int DigitCalc(int Value, int DigitNum);
	void ReturnScene() {
		m_ExitScene = true;
	};
	bool GetExitScene() {
		return m_ExitScene;
	}
private:
	int m_BGMvolume = 100;
	int m_SEvolume = 100;
	int m_ALLvolume = 100;

	//! âπó ÇÃç≈ëÂåÖêîÇ∆ê›íËçÄñ⁄êî
	static const int VolumeMaxNum = 3;
	const float NumTu = (102.f / 1024.f);
	const float NumTv = (186.f / 256.f);
	const float MenuHight = (810.f / 1024.f);
	const float TriangleWidth = (137.f / 512.f);
	const float DigitWidth = 75.f;
	const DWORD WHITE = 0xFFFFFFFF;
	const CENTRAL_STATE LeftCursolNeutral = { 850,200,40,30 };
	const CENTRAL_STATE RightCursolNeutral = { 500,200,40,30 };

	CENTRAL_STATE m_LeftCursol[VolumeMaxNum] = { { LeftCursolNeutral },{ LeftCursolNeutral },{ LeftCursolNeutral } };
	CENTRAL_STATE m_RightCursol[VolumeMaxNum] = { { RightCursolNeutral },{ RightCursolNeutral },{ RightCursolNeutral } };
	CENTRAL_STATE m_Menu = { 300,360,100,250 };

	const CENTRAL_STATE VolumeNumNeutral = { 750,0,50,90 };
	CENTRAL_STATE m_BGMVolumeNum[VolumeMaxNum] = { { VolumeNumNeutral },{ VolumeNumNeutral },{ VolumeNumNeutral } };
	CENTRAL_STATE m_SEVolumeNum[VolumeMaxNum] = { { VolumeNumNeutral },{ VolumeNumNeutral },{ VolumeNumNeutral } };
	CENTRAL_STATE m_ALLVolumeNum[VolumeMaxNum] = { { VolumeNumNeutral },{ VolumeNumNeutral },{ VolumeNumNeutral } };
	bool m_ExitScene = false;

};

