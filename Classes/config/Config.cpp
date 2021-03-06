#include "Config.h"
Config::Config()
{
}

Config::~Config()
{
}


static char g_GBKConvUTF8Buf[500000];
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) 
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
	char *iconvChar = (char*)malloc(strLength);
	memset(outbuf, 0, outLength);
	memcpy(iconvChar, strChar, strLength);
	if (-1 == iconv(iconvH, &iconvChar, &strLength, &outbuf, &outLength))
	{
		iconv_close(iconvH);
		return NULL;
	}
	//free(iconvChar);//传言会自己free如果在这里会free会报错 ARGUMENT IS INVALID HEAP ADDRESS IN dlfree
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
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) 
const char* Config::WinGBKToUTF8(const char *strGB2312)
{
	memset(g_GBKConvUTF8Buf, 0, 500000);
	int len = MultiByteToWideChar(CP_ACP, 0, strGB2312, -1, nullptr, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, strGB2312, -1, wstr, len);

	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
	char* str = new char[len];
	memset(str, 0, len);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len + 1, nullptr, nullptr);
	memcpy(g_GBKConvUTF8Buf, str, len);
	if (wstr) delete[] wstr;
	if (str) delete[] str;
	return g_GBKConvUTF8Buf;
}
#endif
const char * Config::GetChessmanName(int value, int opponetType)
{
	const char *str;
	switch (value)
	{
	case handsome:
		str = opponetType == pc ? "帅" : "将";
		break;
	case finishing:
		str = "仕";
		break;
	case phase:
		str = opponetType == pc ? "象" : "相";
		break;
	case horse:
		str = "马";
		break;
	case car:
		str = "车";
		break;
	case cannon:
		str = "炮";
		break;
	case soldiers:
		str = opponetType == pc ? "兵" : "卒";
		break;
	default:
		str = opponetType == pc ? "兵" : "卒";
		break;
	}
	return GBKTOUTF8(str);
}