#pragma once

#include "Singleton.h"

class AppConfigSingleton
{
	friend class CR::Utility::Singleton<AppConfigSingleton>;
public:
	enum EPlatformType
	{
		PHONE,
		IPAD,
		IAD,
		ANDROID
	};
	EPlatformType PlatformType() {return m_platformType;}
	bool IsIpad() const {return m_platformType == IPAD;}
	bool IsIAd() const {return m_platformType == IAD;}
	bool IsAndroid() const {return m_platformType == ANDROID;}
	bool UseScoreloop() const { return m_UseScoreLoop; }
	void DisableScoreloop() { m_UseScoreLoop = false; }

private:
	AppConfigSingleton();
	AppConfigSingleton(const AppConfigSingleton &_other) {}
	~AppConfigSingleton() {}
	EPlatformType m_platformType;
	bool m_UseScoreLoop;
};

typedef CR::Utility::Singleton<AppConfigSingleton> AppConfig;