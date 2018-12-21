/**
* @file VOLUMESELECTSCENE.cpp
* @brief âπó ê›íË
* @author Toshiya Matsuoka
*/
#include "VOLUMESELECTSCENE.h"
#include <cmath>


VOLUMESELECTSCENE::VOLUMESELECTSCENE(DirectX* pDirectX, SoundOperater* pSoundOperater) :Scene(pDirectX, pSoundOperater)
{
	for (int i = 0; i < VolumeMaxNum; ++i) {
		//! Ç∆ÇËÇ†Ç¶Ç∏âºíuÇ´ÇÃêîéö
		m_BGMVolumeNum[i].y = 200;
		m_SEVolumeNum[i].y = 350;
		m_ALLVolumeNum[i].y = 500;

		m_BGMVolumeNum[i].x = VolumeNumNeutral.x - (i * DigitWidth);
		m_SEVolumeNum[i].x = VolumeNumNeutral.x - (i * DigitWidth);
		m_ALLVolumeNum[i].x = VolumeNumNeutral.x - (i * DigitWidth);

		m_LeftCursol[i].y = LeftCursolNeutral.y + (i * TriangleCursolHeght);
		m_RightCursol[i].y = RightCursolNeutral.y + (i * TriangleCursolHeght);
	}
}


VOLUMESELECTSCENE::~VOLUMESELECTSCENE()
{

}

SCENE_NUM VOLUMESELECTSCENE::Update() {
	bool buff = m_pSoundOperater->Start("TEST", true);

	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_RETURN) || KeyRelease == m_pDirectX->GetKeyStatus(DIK_NUMPADENTER) ||PadRelease == m_pXinputDevice->GetButton(ButtonA))
	{
		ReturnScene();
	}
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_LEFT) || PadRelease == m_pXinputDevice->GetButton(ButtonLEFT))
	{
		DecreaseVolume(&m_BGMvolume);
		m_pSoundOperater->BGMSetVolume(m_BGMvolume);

	}
	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_RIGHT) || PadRelease == m_pXinputDevice->GetButton(ButtonRIGHT))
	{
		IncreaseVolume(&m_BGMvolume);
		m_pSoundOperater->BGMSetVolume(m_BGMvolume);

	}

	--m_ALLvolume;
	if (m_ALLvolume < 0) {
		m_ALLvolume = 100;
	}
	//m_pSoundOperater->AllSetVolume(m_ALLvolume);
	return SCENE_NONE;
}

void VOLUMESELECTSCENE::Render() {
	CUSTOMVERTEX SetVolumeVertex[4];

	CreateSquareVertex(SetVolumeVertex, m_Menu, WHITE, 0, 0, 1, MenuHight);
	m_pDirectX->DrawTexture("SV_MENU_TEX", SetVolumeVertex);

	for (int i = 0; i < VolumeMaxNum; ++i) {
		RevolveZ(SetVolumeVertex, DegToRad(180), m_RightCursol[i], WHITE, TriangleWidth, MenuHight, TriangleWidth, 1 - MenuHight);
		m_pDirectX->DrawTexture("SV_MENU_TEX", SetVolumeVertex);

		CreateSquareVertex(SetVolumeVertex, m_LeftCursol[i], WHITE, TriangleWidth, MenuHight, TriangleWidth, 1 - MenuHight);
		m_pDirectX->DrawTexture("SV_MENU_TEX", SetVolumeVertex);

		int DigitBuff = DigitCalc(m_BGMvolume, i);
		CreateSquareVertex(SetVolumeVertex, m_BGMVolumeNum[i], WHITE, NumTu * DigitBuff, 0, NumTu, NumTv);
		m_pDirectX->DrawTexture("NUMBER_TEX", SetVolumeVertex);

		DigitBuff = DigitCalc(m_SEvolume, i);
		CreateSquareVertex(SetVolumeVertex, m_SEVolumeNum[i], WHITE, NumTu * DigitBuff, 0, NumTu, NumTv);
		m_pDirectX->DrawTexture("NUMBER_TEX", SetVolumeVertex);

		DigitBuff = DigitCalc(m_ALLvolume, i);
		CreateSquareVertex(SetVolumeVertex, m_ALLVolumeNum[i], WHITE, NumTu * DigitBuff, 0, NumTu, NumTv);
		m_pDirectX->DrawTexture("NUMBER_TEX", SetVolumeVertex);
	}
}

void VOLUMESELECTSCENE::LoadResouce() {

}

void  VOLUMESELECTSCENE::SetVolume() {

	m_pSoundOperater->SetVolume("DECISION", m_SEvolume);


}

void VOLUMESELECTSCENE::IncreaseVolume(int* Volume) {
	++(*Volume);
}
void VOLUMESELECTSCENE::DecreaseVolume(int* Volume) {
	--(*Volume);
}
int VOLUMESELECTSCENE::DigitCalc(int Value, int DigitNum) {

	int Buff = (Value / static_cast<int>(std::pow(10, DigitNum)));
	return Buff % 10;
}

