#include "MenuOptions.h"
using namespace std;

#pragma region Methods
const DefaultSize MenuOptions::GetSize()
{
	// Get size:
	short choice = GetMenuOption();

	// Return size:
	switch (choice)
	{
	case 1:
		return Small;
	case 2:
		return Middle;
	case 3:
		return Large;
	default:
		return Small;
	}
}

void MenuOptions::ChangeFieldSize(Minesweeper * obj)
{
	DefaultSize type = MenuOptions::GetSize();

	switch (type)
	{
	case Small:
		// Set field size to small one:
		obj->SetSize(SMALL_SIZE, SMALL_SIZE, SMALL_MINES_QUANTITY);
		break;
	case Middle:
		// Set field size to middle one:
		obj->SetSize(MIDDLE_SIZE, MIDDLE_SIZE, MIDDLE_MINES_QUANTITY);
		break;
	case Large:
		// Set field size to large one:
		obj->SetSize(LARGE_SIZE, LARGE_SIZE, LARGE_MINES_QUANTITY);
		break;
	default:
		// Set field size to default:
		obj->SetSize(SMALL_SIZE, SMALL_SIZE, SMALL_MINES_QUANTITY);
	}
}

const short MenuOptions::GetMenuOption()
{
	// Variables for storing menu items:
	int menu_item = 1, current_position = 13;

	const char * Levels[]
	{
		"EASY", "MIDDLE", "HARD"
	};

	// Selecting menu options:
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	AdditionalFunctions::SetColor(Black, LightGray);
	AdditionalFunctions::gotoxy(53, 13); cout << Levels[0] << endl;
	AdditionalFunctions::SetColor(LightGray, Black);
	AdditionalFunctions::gotoxy(52, 14); cout << Levels[1] << endl;
	AdditionalFunctions::gotoxy(53, 15); cout << Levels[2] << endl;

	do
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		system("pause>nul");

		// Up button pressed:
		if (GetAsyncKeyState(VK_UP) && current_position != 13)
		{
			if (current_position != 14)
			{
				AdditionalFunctions::gotoxy(53, current_position);
				AdditionalFunctions::SetColor(LightGray, Black);
				cout << Levels[menu_item - 1] << endl;
			}
			else
			{
				AdditionalFunctions::gotoxy(52, current_position);
				AdditionalFunctions::SetColor(LightGray, Black);
				cout << Levels[menu_item - 1] << endl;
			}
			current_position--;	menu_item--;
			AdditionalFunctions::SetColor(Black, LightGray);
			if (current_position != 14)
			{
				AdditionalFunctions::gotoxy(53, current_position);
				cout << Levels[menu_item - 1] << endl;

			}
			else
			{
				AdditionalFunctions::gotoxy(52, current_position);
				cout << Levels[menu_item - 1] << endl;
			}

			AdditionalFunctions::SetColor(LightGray, Black);
			continue;
		}

		// Down button pressed:
		if (GetAsyncKeyState(VK_DOWN) && current_position != 15)
		{
			if (current_position != 14)
			{
				AdditionalFunctions::gotoxy(53, current_position);
				AdditionalFunctions::SetColor(LightGray, Black);
				cout << Levels[menu_item - 1] << endl;
			}
			else
			{
				AdditionalFunctions::gotoxy(52, current_position);
				AdditionalFunctions::SetColor(LightGray, Black);
				cout << Levels[menu_item - 1] << endl;
			}

			current_position++;	menu_item++;
			AdditionalFunctions::SetColor(Black, LightGray);
			if (current_position != 14)
			{
				AdditionalFunctions::gotoxy(53, current_position);
				cout << Levels[menu_item - 1] << endl;
			}
			else
			{
				AdditionalFunctions::gotoxy(52, current_position);
				cout << Levels[menu_item - 1] << endl;
			}
			AdditionalFunctions::SetColor(LightGray, Black);
			continue;
		}

		if (GetAsyncKeyState(VK_ESCAPE) && current_position != 15)
			exit(EXIT_SUCCESS);

	} while (!GetAsyncKeyState(VK_RETURN));

	// Return menu item:
	return menu_item;
}
#pragma endregion


