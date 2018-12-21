/**
* @file SoundOperater.h
* @brief サウンドキーの管理
* @author Toshiya Matsuoka
*/
#pragma once
#include <vector>
#include "SoundsManager.h"
using SoundLib::SoundsManager;

class SoundOperater
{
public:
	SoundOperater();
	~SoundOperater();

	SoundLib::PlayingStatus GetStatus(const char* pKey) const;

	uint8_t GetVolume(const char* pKey) const;

	bool SetVolume(const char* pKey, uint8_t volume);

	float GetFrequencyRatio(const char* pKey) const;

	bool SetFrequencyRatio(const char* pKey, float ratio);

	bool Initialize();

	bool AddFile(const char* pFilePath, const char* pKey);

	bool Start(const char* pKey, bool isLoopPlayback = false);

	bool Stop(const char* pKey);

	bool Pause(const char* pKey);

	bool Resume(const char* pKey);

	bool AllStop();

	bool AllSetVolume();
private:
	SoundsManager* m_pSoundManager;
	std::vector<const char*> SoundKey;
};

