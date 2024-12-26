#include "SoundManager.h"
#include "AudioEngine.h"
#include "Utils.h"
#include "Define.h"

#include "cocos2d.h"
#include "json/document.h"
#include "json/rapidjson.h"
#include "json/stringbuffer.h"
#include "json/prettywriter.h"

USING_NS_CC;
using namespace experimental;
using namespace std;
using namespace rapidjson;
using namespace cocos2d;

SoundManager::SoundManager()
{
	_soundVolume = 1.0f;
	_bgmVolume = 1.0f;
	_bgmID = -1;

	LoadSoundInfoData();
}

SoundManager::~SoundManager()
{
	SaveSoundData();
}

void SoundManager::LoadSoundInfoData()
{
	// JSON 파일을 관리할 Document 객체
	  // JSON 파일 경로 탐색
	std::string jsonData = FileUtils::getInstance()->getStringFromFile("data/SoundData.json");
	// JSON 파일을 관리할 Document 객체
	Document doc;
	// JSON 파일을 불러온 다음 doc에 저장한다
	doc.Parse<0>(jsonData.c_str());

	// 오류 검사
	if (doc.HasParseError())
	{
		// 오류가 존재하는 경우 콘솔로 출력하고 프로그램 종료
		log("GetParseError : %d", doc.GetParseError());
		return;
	}
	else
	{
		_soundVolume = doc["SoundVolume"].GetFloat();
		_bgmVolume = doc["BgmVolume"].GetFloat();
	}
}

int SoundManager::PlaySound2D(string path, SoundType type, bool roop)
{
	if (soundSet.find(path) == soundSet.end())
	{
		soundSet.insert(path);
		// 사운드를 미리 불러온다
		AudioEngine::preload(path);
	}

	if (type == SoundType::Sound)
	{
		int _soundID = AudioEngine::play2d(path, roop, _soundVolume);
		soundIdSet.insert(_soundID);
		// 콜백 함수를 호출한다
		AudioEngine::setFinishCallback(_soundID, [this](int id, const std::string& filepath) {
			if (soundIdSet.find(id) != soundIdSet.end())
				soundIdSet.erase(id);
			});

		return _soundID;
	}
	else if (type == SoundType::BGM)
	{
		if (AudioEngine::getState(_bgmID) != AudioEngine::AudioState::PLAYING)
		{
			// 재생 중이 아니라면 사운드를 재생합니다.
			_bgmID = AudioEngine::play2d(path, true, _bgmVolume);
			return _bgmID;
		}
	}

	return -1;
}

void SoundManager::SetVolume(float val, SoundType type)
{
	if (type == SoundType::Sound)
	{
		_soundVolume = Utils::Clamp(val, 0.0f, 1.0f);
		
		for (auto& id : soundIdSet)
		{
			if ((int)AudioEngine::getState(id) != 0)
				AudioEngine::setVolume(id, _soundVolume);
		}
	}
	else if (type == SoundType::BGM)
	{
		_bgmVolume = Utils::Clamp(val, 0.0f, 1.0f);
		if ((int)AudioEngine::getState(_bgmID) != 0)
			AudioEngine::setVolume(_bgmID, _bgmVolume);
	}
}

float SoundManager::GetVolume(SoundType type)
{
	return (type == SoundType::Sound) ? _soundVolume : _bgmVolume;
}

void SoundManager::StopVolumeAll()
{
	AudioEngine::stopAll();
}

void SoundManager::StopVolume(int id)
{
	AudioEngine::stop(id);

	if (soundIdSet.find(id) != soundIdSet.end())
		soundIdSet.erase(id);
}

void SoundManager::Clear()
{
	// 오디오 엔진에 할당되었던 여러 정보를 삭제한다
	// AudioEngine::end();
	StopVolumeAll();
	_bgmID = -1;
	soundIdSet.clear();
}

void SoundManager::SaveSoundData()
{
	Document doc;
	doc.SetObject();
	Document::AllocatorType& allocator = doc.GetAllocator();

	doc.AddMember("SoundVolume", _soundVolume, allocator);
	doc.AddMember("BgmVolume", _bgmVolume, allocator);

	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	doc.Accept(writer);

	std::string jsonData = buffer.GetString();

	// 파일에 저장
	bool result = FileUtils::getInstance()->writeStringToFile(jsonData, FileUtils::getInstance()->getDefaultResourceRootPath() + "data/SoundData.json");
}
