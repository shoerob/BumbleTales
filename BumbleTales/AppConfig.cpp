#include "AppConfig.h"
#include "S3e.h"
#include "string.h"

AppConfigSingleton::AppConfigSingleton() : m_UseScoreLoop(false)
{
	char value[S3E_CONFIG_STRING_MAX];
	s3eConfigGetString("crconfig","platform",value);

	if(stricmp(value,"ipad") == 0)
		m_platformType = IPAD;
	else if(stricmp(value,"iad") == 0)
		m_platformType = IAD;
	else if(stricmp(value,"android") == 0)
		m_platformType = ANDROID;
	else
		m_platformType = PHONE;
	
	s3eConfigGetString("crconfig","use_scoreloop",value);
	if(stricmp(value, "true"))
		m_UseScoreLoop = true;
}