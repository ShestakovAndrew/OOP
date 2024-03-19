#include <Windows.h>
#include "Labyrinth.h"

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try
	{
		Labyrinth labyrinth = GetLabyrinthFromArgv(argc, argv);
		SearchSettings searchSettings = GetSearchSetting(argc, argv);
		Labyrinth labyrinthWithShortestPath = GetLabyrinthWithShortestPath(labyrinth, searchSettings);

		WriteLabyrinthInFile(argv[2], labyrinthWithShortestPath);
	}
	catch (const std::exception& error)
	{
		std::cout << error.what() << std::endl;
		return 1;
	}
}