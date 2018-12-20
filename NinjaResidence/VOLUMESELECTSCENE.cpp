#include "VOLUMESELECTSCENE.h"



VOLUMESELECTSCENE::VOLUMESELECTSCENE(DirectX* pDirectX, SoundLib::SoundsManager* pSoundManager) :Scene(pDirectX, pSoundManager)
{
	LoadResouce();
	for (int i = 0; i < VolumeMaxNum; ++i) {
		m_BGMVolumeNum[i].y = 200;
		m_SEVolumeNum[i].y = 350;
		m_ALLVolumeNum[i].y = 500;

		m_BGMVolumeNum[i].x = VolumeNumNeutral.x + i * 50;
		m_SEVolumeNum[i].x = VolumeNumNeutral.x + i * 50;
		m_ALLVolumeNum[i].x = VolumeNumNeutral.x + i * 50;

		m_LeftCursol[i].y = LeftCursolNeutral.y + (i * 150);
		m_RightCursol[i].y = RightCursolNeutral.y + (i * 150);
	}
}


VOLUMESELECTSCENE::~VOLUMESELECTSCENE()
{

}

SCENE_NUM VOLUMESELECTSCENE::Update() {

	if (KeyRelease == m_pDirectX->GetKeyStatus(DIK_RETURN) || KeyRelease == m_pDirectX->GetKeyStatus(DIK_NUMPADENTER) || PadRelease == m_pXinputDevice->GetButton(ButtonA))
	{
		ReturnScene();
	}

	return SCENE_NONE;
};
void VOLUMESELECTSCENE::Render() {
	CUSTOMVERTEX SetVolumeVertex[4];

	CreateSquareVertex(SetVolumeVertex, m_Menu, 0xFFFFFFFF, 0, 0, 1, (810.f / 1024.f));
	m_pDirectX->DrawTexture("SV_MENU_TEX", SetVolumeVertex);

	for (int i = 0; i < VolumeMaxNum; ++i) {
		CreateSquareVertex(SetVolumeVertex, m_LeftCursol[i]);
		m_pDirectX->DrawTexture("SV_MENU_TEX", SetVolumeVertex);

		CreateSquareVertex(SetVolumeVertex, m_RightCursol[i]);
		m_pDirectX->DrawTexture("SV_MENU_TEX", SetVolumeVertex);

		CreateSquareVertex(SetVolumeVertex, m_BGMVolumeNum[i], 0xFFFFFFFF, 0, 0, NumTu, NumTv);
		m_pDirectX->DrawTexture("NUMBER_TEX", SetVolumeVertex);

		CreateSquareVertex(SetVolumeVertex, m_SEVolumeNum[i], 0xFFFFFFFF, 0, 0, NumTu, NumTv);
		m_pDirectX->DrawTexture("NUMBER_TEX", SetVolumeVertex);

		CreateSquareVertex(SetVolumeVertex, m_ALLVolumeNum[i], 0xFFFFFFFF, 0, 0, NumTu, NumTv);
		m_pDirectX->DrawTexture("NUMBER_TEX", SetVolumeVertex);
	}
};
void VOLUMESELECTSCENE::LoadResouce() {

}

void  VOLUMESELECTSCENE::SetVolume() {

	m_pSoundManager->SetVolume("DECISION", m_SEvolume);


}

void VOLUMESELECTSCENE::ChangeVolume() {
	m_BGMvolume++;
	m_SEvolume++;

}
