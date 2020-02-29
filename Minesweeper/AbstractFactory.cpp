#include "AbstractFactory.h"
using namespace std;

Minesweeper & AbstractFactory::CreateBySize(const DefaultSize type)
{
	switch (type)
	{
	case Small:
		// Return object with small size:
		return Minesweeper::CreateObject(SMALL_SIZE, SMALL_SIZE, SMALL_MINES_QUANTITY);
	case Middle:
		// Return object with middle size:
		return Minesweeper::CreateObject(MIDDLE_SIZE, MIDDLE_SIZE, MIDDLE_MINES_QUANTITY);
	case Large:
		// Return object with large size:
		return Minesweeper::CreateObject(LARGE_SIZE, LARGE_SIZE, LARGE_MINES_QUANTITY);
	}

	// Return object with default size: 
	return Minesweeper::CreateObject(SMALL_SIZE, SMALL_SIZE, SMALL_MINES_QUANTITY);
}