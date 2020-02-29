#include "Minesweeper.h"
#include "MenuOptions.h"
using namespace std;

#pragma region Constructor
Minesweeper::Minesweeper(const short & xSize, const short & ySize, const short & MinesQuantity)
{
	// Set field size and mines quantity:
	this->xSize = xSize > 0 ? xSize : 0;
	this->ySize = ySize > 0 ? ySize : 0;
	this->MinesQuantity = MinesQuantity;
	OpenCells = xSize * ySize;
	isFirstMove = true;

	// HiddenGameField:
	HiddenGameField = new char *[this->xSize];
	for (int i = 0; i < this->xSize; i++)
		HiddenGameField[i] = new char[this->ySize];

	for (int i = 0; i < this->xSize; i++)
		for (int j = 0; j < this->ySize; j++)
			HiddenGameField[i][j] = '0';

	// GameField:
	GameField = new char *[this->xSize];
	for (int i = 0; i < this->xSize; i++)
		GameField[i] = new char[this->ySize];

	for (int i = 0; i < this->xSize; i++)
		for (int j = 0; j < this->ySize; j++)
			GameField[i][j] = '.';
}
#pragma endregion

#pragma region Destructor
Minesweeper::~Minesweeper()
{
	// GameField:
	for (int i = 0; i < xSize; i++)
		delete GameField[i];
	delete[] GameField;

	// HiddenGameField:
	for (int i = 0; i < xSize; i++)
		delete HiddenGameField[i];
	delete[] HiddenGameField;

	xSize = ySize = 0;
	MinesQuantity = 0;
	isFirstMove = true;
	OpenCells = 0;
}
#pragma endregion

#pragma region Methods
Minesweeper & Minesweeper::CreateObject(const unsigned short & xSize, const unsigned short & ySize, const unsigned short & MinesQuantity)
{
	// Return object:
	static Minesweeper obj(xSize, ySize, MinesQuantity);
	obj.SetupMinesField();
	return obj;
}

void Minesweeper::SetSize(const unsigned short & xSize, const unsigned short & ySize, const unsigned short & MinesQuantity)
{
	if ((xSize == ySize) && (xSize != 0 && ySize != 0))
	{
		// GameField:
		for (int i = 0; i < this->xSize; i++)
			delete GameField[i];
		delete[] GameField;

		// HiddenGameField:
		for (int i = 0; i < this->xSize; i++)
			delete HiddenGameField[i];
		delete[] HiddenGameField;

		this->xSize = this->ySize = 0;
		this->MinesQuantity = 0;
		isFirstMove = true;
		OpenCells = 0;

		// Set field size and mines quantity:
		AdditionalFunctions::gotoxy(CURSOR_X_POS, CURSOR_Y_POS);
		this->xSize = xSize > 0 ? xSize : 0;
		this->ySize = ySize > 0 ? ySize : 0;
		this->MinesQuantity = MinesQuantity;
		OpenCells = xSize * ySize;
		isFirstMove = true;

		// HiddenGameField:
		HiddenGameField = new char *[this->xSize];
		for (int i = 0; i < this->xSize; i++)
			HiddenGameField[i] = new char[this->ySize];

		for (int i = 0; i < this->xSize; i++)
			for (int j = 0; j < this->ySize; j++)
				HiddenGameField[i][j] = '0';

		// GameField:
		GameField = new char *[this->xSize];
		for (int i = 0; i < this->xSize; i++)
			GameField[i] = new char[this->ySize];

		for (int i = 0; i < this->xSize; i++)
			for (int j = 0; j < this->ySize; j++)
				GameField[i][j] = '.';

		SetupMinesField();
		StartGame();
	}
}

void Minesweeper::SetupMinesField()
{
	// Initialize random number generator:
	srand((unsigned)time(NULL));

	// Clear fields:
	ClearMinesField();

	// Set mines:
	short xPos, yPos;

	for (int i = 0; i < MinesQuantity; i++)
	{
		do
		{
			// Generate random position:
			xPos = rand() % xSize;	yPos = rand() % ySize;
		} while (HiddenGameField[xPos][yPos] == '@'); // While the current cell contains a bomb

		// Setting cell value:
		HiddenGameField[xPos][yPos] = '@';
	}

	// Count mines arround:
	for (int i = 0; i < xSize; i++)
	{
		for (int j = 0; j < ySize; j++)
		{
			// If current cell not contain any mines:
			if (HiddenGameField[i][j] == '@')
			{
				for (int xPos = i - 1; xPos <= i + 1; xPos++)
				{
					for (int yPos = j - 1; yPos <= j + 1; yPos++)
					{
						// Setting the number of mines around: 
						if ((xPos >= 0 && xPos <= xSize - 1) && (yPos >= 0 && yPos <= ySize - 1))
						{
							if (HiddenGameField[xPos][yPos] != '@')
								HiddenGameField[xPos][yPos] += 1;
						}
					}
				}
			}
		}
	}
}

void Minesweeper::ClearMinesField()
{
	// HiddenGameField:
	for (int i = 0; i < xSize; i++)
		for (int j = 0; j < ySize; j++)
			HiddenGameField[i][j] = '0';

	// GameField:
	for (int i = 0; i < xSize; i++)
		for (int j = 0; j < ySize; j++)
			GameField[i][j] = '.';
}

bool Minesweeper::CheckPosition(const unsigned short & xPos, const unsigned short & yPos)
{
	// Check coords:
	if ((xPos >= xSize || yPos >= ySize) || HiddenGameField[xPos][yPos] == '@') return false;

	// Open cells:
	if (xPos < ySize && xPos >= 0 && yPos < xSize && yPos >= 0)
	{
		if (HiddenGameField[xPos][yPos] == '0')
		{
			HiddenGameField[xPos][yPos] = ' ';

			if (HiddenGameField[xPos][yPos] == ' ')
			{
				CheckPosition(xPos - 1, yPos - 1);
				CheckPosition(xPos, yPos - 1);
				CheckPosition(xPos + 1, yPos - 1);
				CheckPosition(xPos + 1, yPos);
				CheckPosition(xPos + 1, yPos + 1);
				CheckPosition(xPos, yPos + 1);
				CheckPosition(xPos - 1, yPos + 1);
				CheckPosition(xPos - 1, yPos);
			}
		}
	}

	// Setting the value of cells:
	if (HiddenGameField[xPos][yPos] == '0')
		HiddenGameField[xPos][yPos] = ' ';

	if (GameField[xPos][yPos] == '.')
		OpenCells -= 1;

	GameField[xPos][yPos] = HiddenGameField[xPos][yPos];
	return true;
}

bool Minesweeper::TakeShoot(short & cursor_y, short & cursor_x)
{
	ShowField();
	AdditionalFunctions::SetColor(Black, DarkGray);
	AdditionalFunctions::gotoxy(cursor_x * 2 + CURSOR_X_POS + 1, cursor_y + CURSOR_Y_POS + 1);
	cout << GameField[cursor_y][cursor_x];
	AdditionalFunctions::SetColor(White, Black);

	do
	{
		system("pause>nul");
		AdditionalFunctions::SetColor(Black, DarkGray);
		AdditionalFunctions::gotoxy(cursor_x * 2 + CURSOR_X_POS + 1, cursor_y + CURSOR_Y_POS + 1);
		cout << GameField[cursor_y][cursor_x];
		AdditionalFunctions::SetColor(White, Black);

		// Up button pressed:
		if (GetAsyncKeyState(VK_UP) && cursor_y != 0)
		{
			ShowField();	cursor_y--;
			AdditionalFunctions::SetColor(Black, DarkGray);
			AdditionalFunctions::gotoxy(cursor_x * 2 + CURSOR_X_POS + 1, cursor_y + CURSOR_Y_POS + 1);
			cout << GameField[cursor_y][cursor_x];
			AdditionalFunctions::SetColor(White, Black);
			continue;
		}

		// Down button pressed:
		if (GetAsyncKeyState(VK_DOWN) && cursor_y != ySize - 1)
		{
			ShowField();	cursor_y++;
			AdditionalFunctions::SetColor(Black, DarkGray);
			AdditionalFunctions::gotoxy(cursor_x * 2 + CURSOR_X_POS + 1, cursor_y + CURSOR_Y_POS + 1);
			cout << GameField[cursor_y][cursor_x];
			AdditionalFunctions::SetColor(White, Black);
			continue;
		}

		// Left button pressed:
		if (GetAsyncKeyState(VK_LEFT) && cursor_x != 0)
		{

			ShowField();	cursor_x--;
			AdditionalFunctions::SetColor(Black, DarkGray);
			AdditionalFunctions::gotoxy(cursor_x * 2 + CURSOR_X_POS + 1, cursor_y + CURSOR_Y_POS + 1);
			cout << GameField[cursor_y][cursor_x];
			AdditionalFunctions::SetColor(White, Black);
			continue;
		}

		// Right button pressed:
		if (GetAsyncKeyState(VK_RIGHT) && cursor_x != xSize - 1)
		{
			ShowField();	cursor_x++;
			AdditionalFunctions::SetColor(Black, DarkGray);
			AdditionalFunctions::gotoxy(cursor_x * 2 + CURSOR_X_POS + 1, cursor_y + CURSOR_Y_POS + 1);
			cout << GameField[cursor_y][cursor_x];
			AdditionalFunctions::SetColor(White, Black);
			continue;
		}

		if (GetAsyncKeyState(VK_ESCAPE))
		{
			system("cls");

			// Variables for storing menu items:
			int menu_item = 1, current_position = 13;

			const char * Levels[]
			{
				"CONTINUE", "NEW GAME", "EXIT"
			};

			// Selecting menu options:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			AdditionalFunctions::SetColor(Black, LightGray);
			AdditionalFunctions::gotoxy(51, 13); cout << Levels[0] << endl;
			AdditionalFunctions::SetColor(LightGray, Black);
			AdditionalFunctions::gotoxy(51, 14); cout << Levels[1] << endl;
			AdditionalFunctions::gotoxy(53, 15); cout << Levels[2] << endl;

			do
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				system("pause>nul");

				// Up button pressed:
				if (GetAsyncKeyState(VK_UP) && current_position != 13)
				{
					// Redraw cursor in the new position:
					if (current_position != 15)
					{
						AdditionalFunctions::gotoxy(51, current_position);
						AdditionalFunctions::SetColor(LightGray, Black);
						cout << Levels[menu_item - 1] << endl;
					}
					else
					{
						AdditionalFunctions::gotoxy(53, current_position);
						AdditionalFunctions::SetColor(LightGray, Black);
						cout << Levels[menu_item - 1] << endl;
					}

					current_position--;	menu_item--;
					AdditionalFunctions::SetColor(Black, LightGray);
					if (current_position != 15)
					{
						AdditionalFunctions::gotoxy(51, current_position);
						cout << Levels[menu_item - 1] << endl;

					}
					else
					{
						AdditionalFunctions::gotoxy(53, current_position);
						cout << Levels[menu_item - 1] << endl;
					}
					AdditionalFunctions::SetColor(LightGray, Black);
					continue;
				}

				// Down button pressed:
				if (GetAsyncKeyState(VK_DOWN) && current_position != 15)
				{
					if (current_position != 15)
					{
						AdditionalFunctions::gotoxy(51, current_position);
						AdditionalFunctions::SetColor(LightGray, Black);
						cout << Levels[menu_item - 1] << endl;
					}
					else
					{
						AdditionalFunctions::gotoxy(53, current_position);
						AdditionalFunctions::SetColor(LightGray, Black);
						cout << Levels[menu_item - 1] << endl;
					}

					current_position++;	menu_item++;
					AdditionalFunctions::SetColor(Black, LightGray);
					if (current_position != 15)
					{
						AdditionalFunctions::gotoxy(51, current_position);
						cout << Levels[menu_item - 1] << endl;
					}
					else
					{
						AdditionalFunctions::gotoxy(53, current_position);
						cout << Levels[menu_item - 1] << endl;
					}
					AdditionalFunctions::SetColor(LightGray, Black);
					continue;
				}
			} while (!GetAsyncKeyState(VK_RETURN));

			system("cls");

			// Returning the menu item:
			switch (menu_item)
			{
			case 1:
				break;
			case 2:
				MenuOptions::ChangeFieldSize(this);
				break;
			case 3:
				exit(EXIT_SUCCESS);
				break;
			}

			StartGame(cursor_y, cursor_x);
		}

	} while (!GetAsyncKeyState(VK_RETURN));

	AdditionalFunctions::gotoxy(1, 25);
	if (CheckPosition(cursor_y, cursor_x) && isFirstMove)	isFirstMove = false;
	return CheckPosition(cursor_y, cursor_x);
}

void Minesweeper::StartGame(short cursor_x, short cursor_y)
{
	system("cls");
	
	// Set cursor position:
	cursor_x = cursor_x > xSize ? 0 : cursor_x;
	cursor_y = cursor_y > ySize ? 0 : cursor_y;

	do
	{
		if (!TakeShoot(cursor_x, cursor_y))
		{
			if (isFirstMove)
			{
				do
				{
					SetupMinesField();
				} while (HiddenGameField[cursor_x][cursor_y] == '@');
			}
			else
			{
				// Defeat:
				ShowMines();	Sleep(2000);	system("cls");
				AdditionalFunctions::gotoxy(51, 13); cout << "You Lose!" << endl;
				Sleep(2000);	system("cls");
				if (GetAsyncKeyState(VK_RETURN)) {}
				MenuOptions::ChangeFieldSize(this);
				break;
			}
		}
		else if (GameField[cursor_x][cursor_y] == '.')
			OpenCells--;

		if (OpenCells == MinesQuantity)
		{
			// Victory:
			ShowMines();	Sleep(2000);	system("cls");
			AdditionalFunctions::gotoxy(51, 13); cout << "You Win!" << endl;
			Sleep(2000);	system("cls");
			if (GetAsyncKeyState(VK_RETURN)) {}
			MenuOptions::ChangeFieldSize(this);
			break;
		}
	} while (true);
}

void Minesweeper::ShowField()
{
	// Draw border:
	AdditionalFunctions::gotoxy(CURSOR_X_POS - 1, CURSOR_Y_POS);
	cout << '\xDA';
	for (int i = 0; i <= xSize * 2; i++)
		cout << '\xC4';
	cout << '\xBF';

	for (int i = 0; i <= ySize; i++)
	{
		AdditionalFunctions::gotoxy(CURSOR_X_POS - 1, CURSOR_Y_POS + i + 1);
		i != ySize ? cout << '\xB3' : cout << '\xC0';

		for (int j = 0; j <= ySize; j++)
		{
			AdditionalFunctions::gotoxy(CURSOR_X_POS + xSize * 2 + 1, CURSOR_Y_POS + j + 1);
			j != ySize ? cout << '\xB3' : cout << '\xD9';
		}
	}

	AdditionalFunctions::gotoxy(CURSOR_X_POS, CURSOR_Y_POS + ySize + 1);
	for (int i = 0; i <= xSize * 2; i++)
		cout << '\xC4';

	// Set cell color:
	for (int i = 0; i < xSize; i++)
	{
		AdditionalFunctions::gotoxy(CURSOR_X_POS, CURSOR_Y_POS + i + 2);	cout << endl;
		AdditionalFunctions::gotoxy(CURSOR_X_POS, CURSOR_Y_POS + i + 1);
		AdditionalFunctions::SetColor(White, Black);
		cout << " ";

		for (int j = 0; j < ySize; j++)
		{
			switch (GameField[i][j])
			{
			case '1':
				AdditionalFunctions::SetColor(LightBlue, Black);
				break;
			case '2':
				AdditionalFunctions::SetColor(Green, Black);
				break;
			case '3':
				AdditionalFunctions::SetColor(Red, Black);
				break;
			case '4':
				AdditionalFunctions::SetColor(Blue, Black);
				break;
			case '5':
				AdditionalFunctions::SetColor(Red, Black);
				break;
			case '6':
				AdditionalFunctions::SetColor(Cyan, Black);
				break;
			case '7':
				AdditionalFunctions::SetColor(Magenta, Black);
				break;
			case '8':
				AdditionalFunctions::SetColor(DarkGray, Black);
				break;
			case '@':
				AdditionalFunctions::SetColor(LightRed, Black);
			}
			cout << GameField[i][j] << " ";

			AdditionalFunctions::SetColor(White, Black);
		}
	}
	AdditionalFunctions::SetColor(White, Black);
}

void Minesweeper::ShowMines()
{
	for (int i = 0; i < ySize; i++)
	{
		AdditionalFunctions::gotoxy(CURSOR_X_POS, CURSOR_Y_POS + i + 2);	cout << endl;
		AdditionalFunctions::gotoxy(CURSOR_X_POS, CURSOR_Y_POS + i + 1);
		AdditionalFunctions::SetColor(White, Black);
		cout << " ";

		for (int j = 0; j < xSize; j++)
		{

			if (HiddenGameField[i][j] == '@')
			{
				// Mines around:
				AdditionalFunctions::SetColor(Red, Black);
				GameField[i][j] = HiddenGameField[i][j];
				AdditionalFunctions::SetColor(White, Black);
			}
		}
	}
	AdditionalFunctions::SetColor(White, Black);

	ShowField();
}
#pragma endregion
