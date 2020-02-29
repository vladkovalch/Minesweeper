#include "Minesweeper.h"
using namespace std;

enum DefaultSize
{
	// All possible sizes:
	Small, Middle, Large
};

class AbstractFactory
{
public:
	// A static method that returns a singleton object:
	static Minesweeper & CreateBySize(const DefaultSize type);
};