#pragma once
#include "STLINCLUDE.h"
using namespace std;

enum Color
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15,
};

class AdditionalFunctions
{
public:
	// Static additional methods:
	static void gotoxy(const short & x = 0, const short & y = 0);
	static void SetColor(const Color & text, const Color & background);
	static void SetWindowSize(const short & xSize, const short & ySize);
	static void ShowConsoleCursor(const bool & showFlag);
	static void DisableResizing();
	static void RemoveScrollbar();
	static short GetWindowWidth();
	static short GetWindowHeight();
};

