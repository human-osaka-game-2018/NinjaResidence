/**
* @file SoundOperater.h
* @brief サウンドキーの管理
* @author Toshiya Matsuoka
*/
#include "SoundOperater.h"

using namespace SoundLib;

SoundOperater::SoundOperater()
{
	m_pSoundManager = new SoundsManager;
}


SoundOperater::~SoundOperater()
{
	delete m_pSoundManager;
	m_pSoundManager = NULL;
}

PlayingStatus SoundOperater::GetStatus(const char* pKey) const
{
	return m_pSoundManager->GetStatus(pKey);
}

uint8_t SoundOperater::GetVolume(const char* pKey) const
{
	return m_pSoundManager->GetVolume(pKey);
}

bool SoundOperater::SetVolume(const char* pKey, uint8_t volume)
{
	return m_pSoundManager->SetVolume(pKey, volume);
}

float SoundOperater::GetFrequencyRatio(const char* pKey) const
{
	return m_pSoundManager->GetFrequencyRatio(pKey);
}

bool SoundOperater::SetFrequencyRatio(const char* pKey, float ratio)
{
	return m_pSoundManager->SetFrequencyRatio(pKey, ratio);
}

bool SoundOperater::Initialize()
{
	return m_pSoundManager->Initialize();
}

bool SoundOperater::AddFile(const char* pFilePath, const char* pKey)
{
	bool SuccessAddFile = false;
	SuccessAddFile = m_pSoundManager->AddFile(pFilePath, pKey);
	if (SuccessAddFile) {
		SoundKey.push_back(pKey);
	}
	return SuccessAddFile;
}

bool SoundOperater::Start(const char* pKey, bool isLoopPlayback)
{
	return m_pSoundManager->Start(pKey,isLoopPlayback);
}

bool SoundOperater::Stop(const char* pKey)
{
	return m_pSoundManager->Stop(pKey);
}

bool SoundOperater::Pause(const char* pKey)
{
	return m_pSoundManager->Pause(pKey);
}

bool SoundOperater::Resume(const char* pKey)
{
	return m_pSoundManager->Resume(pKey);
}

bool SoundOperater::AllStop()
{
	return false;
}

bool SoundOperater::AllSetVolume()
{
	return false;
}
