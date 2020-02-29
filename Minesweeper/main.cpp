//   _____ ______   ___  ________   _______   ________  ___       __   _______   _______   ________  _______   ________     
//  |\   _ \  _   \|\  \|\   ___  \|\  ___ \ |\   ____\|\  \     |\  \|\  ___ \ |\  ___ \ |\   __  \|\  ___ \ |\   __  \    
//  \ \  \\\__\ \  \ \  \ \  \\ \  \ \   __/|\ \  \___|\ \  \    \ \  \ \   __/|\ \   __/|\ \  \|\  \ \   __/|\ \  \|\  \   
//   \ \  \\|__| \  \ \  \ \  \\ \  \ \  \_|/_\ \_____  \ \  \  __\ \  \ \  \_|/_\ \  \_|/_\ \   ____\ \  \_|/_\ \   _  _\  
//    \ \  \    \ \  \ \  \ \  \\ \  \ \  \_|\ \|____|\  \ \  \|\__\_\  \ \  \_|\ \ \  \_|\ \ \  \___|\ \  \_|\ \ \  \\  \| 
//     \ \__\    \ \__\ \__\ \__\\ \__\ \_______\____\_\  \ \____________\ \_______\ \_______\ \__\    \ \_______\ \__\\ _\ 
//      \|__|     \|__|\|__|\|__| \|__|\|_______|\_________\|____________|\|_______|\|_______|\|__|     \|_______|\|__|\|__|
//                                              \|_________|                                                                

#include "MenuOptions.h"
using namespace std;

int main()
{
	// Remove scrollbar, console cursor:
	AdditionalFunctions::RemoveScrollbar();
	AdditionalFunctions::ShowConsoleCursor(false);
	SetConsoleTitle("Minesweeper");

	// Disable resizing:
	AdditionalFunctions::DisableResizing();

	// Create Minesweeper object:
	DefaultSize type = MenuOptions::GetSize();
	Minesweeper & obj = AbstractFactory::CreateBySize(type);

	// Take a shoot:
	obj.StartGame();

	return EXIT_SUCCESS;
}
