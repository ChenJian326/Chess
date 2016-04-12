#include "Config.h"

Config::Config()
{
}

Config::~Config()
{
}
static char g_GBKConvUTF8Buf[500000];
const char * Config::GBKToUTF8(const char * strChar)
{
	//char g_GBKConvUTF8Buf[50000];
	iconv_t iconvH;
	iconvH = iconv_open("utf-8", "gb2312");
	if (iconvH == 0)
	{
		return NULL;
	}
	size_t strLength = strlen(strChar);
	size_t outLength = strLength << 2;
	size_t copyLength = outLength;
	memset(g_GBKConvUTF8Buf, 0, 5000);

	char* outbuf = (char*)malloc(outLength);
	char* pBuff = outbuf;
	memset(outbuf, 0, outLength);

	if (-1 == iconv(iconvH, &strChar, &strLength, &outbuf, &outLength))
	{
		iconv_close(iconvH);
		return NULL;
	}
	memcpy(g_GBKConvUTF8Buf, pBuff, copyLength);
	free(pBuff);
	iconv_close(iconvH);
	return g_GBKConvUTF8Buf;
}

const char * Config::GetChessmanName(int value, int opponetType)
{
	char *str;
	switch (value)
	{
	case handsome:
		str = opponetType == pc ? "˧" : "��";
		break;
	case finishing:
		str = "��";
		break;
	case phase:
		str = "��";
		break;
	case horse:
		str = "��";
		break;
	case car:
		str = "��";
		break;
	case cannon:
		str = "��";
		break;
	case soldiers:
		str = opponetType == pc ? "��" : "��";
		break;
	default:
		str = opponetType == pc ? "��" : "��";
		break;
	}
	return GBKToUTF8(str);
}