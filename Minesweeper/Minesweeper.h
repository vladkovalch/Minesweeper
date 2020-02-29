#pragma once
#include "AdditionalFunctions.h"
using namespace std;

// Small field size:
#define SMALL_SIZE 9
#define SMALL_MINES_QUANTITY 10

// Middle field size:
#define MIDDLE_SIZE 16
#define MIDDLE_MINES_QUANTITY 40

// Large field size:
#define LARGE_SIZE 26
#define LARGE_MINES_QUANTITY 99

// Start position:
#define CURSOR_X_POS 4
#define CURSOR_Y_POS 1

class Minesweeper
{
private:
	// Constructor:
	explicit Minesweeper(const short & xSize, const short & ySize, const short & MinesQuantity);

	// Prohibition on copying:
	Minesweeper(Minesweeper const &) = delete;
	Minesweeper & operator= (Minesweeper const &) = delete;
protected:
	short MinesQuantity, OpenCells;
	short xSize, ySize;
	char ** GameField;
	char ** HiddenGameField;
	bool isFirstMove;
public:
	~Minesweeper();
	static Minesweeper & CreateObject(const unsigned short & xSize, const unsigned short & ySize, const unsigned short & MinesQuantity);
	void SetSize(const unsigned short & xSize, const unsigned short & ySize, const unsigned short & MinesQuantity);
	bool CheckPosition(const unsigned short & xPos, const unsigned short & yPos);
	void StartGame(short cursor_x = 0, short cursor_y = 0);
	bool TakeShoot(short & cursor_y, short & cursor_x);
	void SetupMinesField();
	void ClearMinesField();
	void ShowField();
	void ShowMines();
};