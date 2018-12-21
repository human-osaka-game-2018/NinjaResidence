/**
* @file SoundOperater.h
* @brief サウンドキーの管理
* @author Toshiya Matsuoka
*/
#pragma once
#include <vector>
#include "SoundsManager.h"
using SoundLib::SoundsManager;

enum SoundType {
	TYPE_NONE,
	BGM,
	SE,
};

struct SoundKey {
	const char* Key;
	SoundType Type;
};

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

	bool AddFile(const char* pFilePath, const char* pKey, SoundType type);

	bool Start(const char* pKey, bool isLoopPlayback = false);

	bool Stop(const char* pKey);

	bool Pause(const char* pKey);

	bool Resume(const char* pKey);

	bool AllStop();

	bool AllSetVolume(uint8_t volume);

	bool BGMSetVolume(uint8_t volume);

	bool SESetVolume(uint8_t volume);
private:
	SoundsManager* m_pSoundManager = NULL;
	std::vector<SoundKey*> m_SoundKey;

	SoundKey Buff;

	SoundType GetSoundType(int arrayNum) {
		return m_SoundKey[arrayNum]->Type;
	}
};

