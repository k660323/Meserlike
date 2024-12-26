#pragma once
#include "string"
#include "set"
#include "Define.h"

class SoundManager
{

public:
	SoundManager();
	virtual ~SoundManager();

	void LoadSoundInfoData();

	int PlaySound2D(std::string path, SoundType type = SoundType::Sound, bool roop = false);

	void SetVolume(float val, SoundType type = SoundType::Sound);
	float GetVolume(SoundType type = SoundType::Sound);

	void StopVolumeAll();

	void StopVolume(int id);

	void Clear();

	void SaveSoundData();
private:
	float _bgmVolume;
	float _soundVolume;

	std::set<std::string> soundSet;

	int _bgmID;
	std::set<int> soundIdSet;
};