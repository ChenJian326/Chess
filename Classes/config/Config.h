#ifndef __CONFIG_H__
#define __CONFIG_H__
#include <string>
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) 
#include "cocos2d\external\win32-specific\icon\include\iconv.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
#include "iconv.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
#include <iconv.h>
#endif

#define GBKTOUTF8 GBKToUTF8
#define GAME_FONE_NAME ""

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) 
#undef  GBKTOUTF8
#undef  GAME_FONE_NAME
#define GBKTOUTF8 WinGBKToUTF8
#define GAME_FONE_NAME "Microsoft YaHei"  //win10��Ҫ����֧�����ĵ�����ſ���Ŷ
//��ο�https://blogs.msdn.microsoft.com/windows__windows_game_dev_faq_/2014/11/06/ttf-cocos2dx-wp8/
#endif

class Config
{
public:
	Config();
	~Config();
	//��������
	enum OPPONENT
	{
		player,
		pc
	};
	//�ƺ���������Ҳû��ʲô��
	enum CHESS_SIZE
	{
		width = 40,
		height = 40
	};

	enum MAP_SIZE {
		row = 4,
		column = 8,
		w = column * CHESS_SIZE::width,
		h = row * CHESS_SIZE::height,
		len = row * column
	};

	//��������
	enum CHESSTYPE
	{
		nullChessman = -1,//��Ч�ı�����
		handsome,//˧
		finishing,//��
		phase,//��
		horse,//��
		car,//��
		cannon,//��
		soldiers,//��
	};
	//��������
	enum CONFIRM_TYPE
	{
		zero,
		one,
		two,
		three,
		four,
		five,
		six,
		seven,
	};

	enum DIRECTION
	{
		left,
		right,
		top,
		botom
	};

	enum TYPE
	{
		TYPE_CHESS,
		TYPE_OPPONENT
	};
	static const char* GBKToUTF8(const char *strChar);
	static const char* WinGBKToUTF8(const char* strChar);
	static const char* GetChessmanName(int value, int opponetType);
private:


};
#endif