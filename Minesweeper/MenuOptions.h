#pragma once
#include "AbstractFactory.h"
using namespace std;

class MenuOptions
{
public:
	static const DefaultSize GetSize();
	static void ChangeFieldSize(Minesweeper * obj);
	static const short GetMenuOption(); 
};