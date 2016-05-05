#include "Config.h"
Config::Config()
{
}

Config::~Config()
{
}
static char g_GBKConvUTF8Buf[500000];
const char * Config::GBKToUTF8(const char* strChar)
{
	iconv_t iconvH;
	iconvH = iconv_open("utf-8", "gb2312");
	if (iconvH == 0)
	{
		return NULL;
	}
	size_t strLength = strlen(strChar);
	size_t outLength = strLength << 2;
	size_t copyLength = outLength;
	memset(g_GBKConvUTF8Buf, 0, 500000);

	char* outbuf = (char*)malloc(outLength);
	char* pBuff = outbuf;
	memset(outbuf, 0, outLength);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	char* iconvChar = (char*)malloc(strLength);
	memcpy(iconvChar, strChar, strLength);
	if (-1 == iconv(iconvH, &iconvChar, &strLength, &outbuf, &outLength))
	{
		iconv_close(iconvH);
		return NULL;
	}
#else
	if (-1 == iconv(iconvH, &strChar, &strLength, &outbuf, &outLength))
	{
		iconv_close(iconvH);
		return NULL;
	}
#endif
	memcpy(g_GBKConvUTF8Buf, pBuff, copyLength);
	free(pBuff);
	iconv_close(iconvH);
	return g_GBKConvUTF8Buf;
}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) 
const char* Config::WinGBKToUTF8(const char *strGB2312)
{
	memset(g_GBKConvUTF8Buf, 0, 500000);
	int len = MultiByteToWideChar(0, 0, strGB2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(0, 0, strGB2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	memcpy(g_GBKConvUTF8Buf, str, len);
	if (wstr) delete[] wstr;
	if (str) delete[] str;
	CCLOG("g_GBKConvUTF8Buf = %s strGB2312 = %s", g_GBKConvUTF8Buf, strGB2312);
	return g_GBKConvUTF8Buf;
}
#endif
const char * Config::GetChessmanName(int value, int opponetType)
{
	const char *str;
	switch (value)
	{
	case handsome:
		str = opponetType == pc ? "Ë§" : "½«";
		break;
	case finishing:
		str = "ÊË";
		break;
	case phase:
		str = "Ïà";
		break;
	case horse:
		str = "Âí";
		break;
	case car:
		str = "³µ";
		break;
	case cannon:
		str = "ÅÚ";
		break;
	case soldiers:
		str = opponetType == pc ? "±ø" : "×ä";
		break;
	default:
		str = opponetType == pc ? "±ø" : "×ä";
		break;
	}
	return GBKTOUTF8(str);
}