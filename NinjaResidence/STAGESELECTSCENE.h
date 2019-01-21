/**
* @file STAGESELECTSCENE.h
* @brief ステージセレクトシーン
* @author Toshiya Matsuoka
*/
#pragma once

#include "SCENE.h"

enum SCENE_NUM;
class Scene;


class StageSelectScene : public Scene
{
public:
	StageSelectScene(DirectX* pDirectX, SoundOperater* pSoundOperater);
	~StageSelectScene();
	SCENE_NUM Update();
	void Render();
	void LoadResouce();

	void TurnUpStageImage();

	void TurnDownStageImage();

private:
	void InitPosStageImage();
	void InitPosStageSelectNumber();
	void InitStageImagekey();
	void InitStageSelectNumberkey();

	Scene* m_pScene = NULL;
	
	int m_timecount = 0;
	
	float m_SelectCursolPosX;
	float m_SelectCursolPosY;
	
	//ステージ選択時のクナイ（カーソル）の移動量
	const float KUNAI_MOVEMENT_X = 650.f;
	const float KUNAI_MOVEMENT_Y = 200.f;
	//戻るボタンに行き来するクナイの移動量
	const float MOVEMENT_X_TO_BACK = 140.f;
	const float MOVEMENT_Y_TO_BACK = 120.f;


	enum m_StageNumber
	{
		Stage0,
		Stage1,
		Stage2,
		Stage3,
		Stage4,
		Stage5,
		StageTitle,
	};

	CENTRAL_STATE m_SelectCursol;
	CENTRAL_STATE m_StageSelectBack;
	CENTRAL_STATE m_StageImage[6];
	CENTRAL_STATE m_StageSelectNumber[6];
	CENTRAL_STATE m_StageFrame = { DISPLAY_WIDTH / 2,DISPLAY_HEIGHT / 2,270.f,270.f };
	std::string m_CursolImagekey;
	std::string m_BackImagekey;
	std::string m_StageImagekey[6];
	std::string m_StageSelectNumberkey[6];
};
