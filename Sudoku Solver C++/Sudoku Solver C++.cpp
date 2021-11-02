// Sudoku Solver C++.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <utility>

constexpr auto boardSize = 9;

int grid[boardSize][boardSize] = {
	{8,0,0,0,0,0,0,0,0},
	{0,0,3,6,0,0,0,0,0},
	{0,7,0,0,9,0,2,0,0},
	{0,5,0,0,0,7,0,0,0},
	{0,0,0,0,4,5,7,0,0},
	{0,0,0,1,0,0,0,3,0},
	{0,0,1,0,0,0,0,6,8},
	{0,0,8,5,0,0,0,1,0},
	{0,9,0,0,0,0,4,0,0}
};

void printBoard()
{
	for (int i = 0; i < boardSize; i++)
		std::cout << "---";

	std::cout << std::endl;

	for (int row = 0; row < boardSize; row++)
	{
		for (int col = 0; col < boardSize; col++)
		{
			if (col != 0 && col % 3 == 0)
				std::cout << " | ";
			else if (col == 0)
				std::cout << "| ";
			std::cout << grid[row][col] << " ";
			if (col == boardSize - 1)
				std::cout << "| ";
		}
		if (row % 3 == 2)
		{
			std::cout << std::endl;
			for (int i = 0; i < boardSize; i++)
				std::cout << "---";
		}
		std::cout << std::endl;
	}
}

bool findNextEmpty(std::pair<int, int>& gridPos)
{
	for (gridPos.first = 0; gridPos.first < boardSize; gridPos.first++)
	{
		for (gridPos.second = 0; gridPos.second < boardSize; gridPos.second++)
		{
			if (grid[gridPos.first][gridPos.second] == 0)
				return true;
		}
	}

	return false;
}

bool isValid(std::pair<int, int> gridPos, int num)
{
	// Check row
	for (int col = 0; col < boardSize; col++)
	{
		if (grid[gridPos.first][col] == num)
			return false;
	}

	// Check Column
	for (int row = 0; row < boardSize; row++)
	{
		if (grid[row][gridPos.second] == num)
			return false;
	}

	// Check Box
	int box_x = gridPos.first / 3;
	int box_y = gridPos.second / 3;

	for (int i = box_x * 3; i < box_x * 3 + 3; i++)
	{
		for (int j = box_y * 3; j < box_y * 3 + 3; j++)
		{
			if (grid[i][j] == num && (std::make_pair(i, j) != gridPos))
				return false;
		}
	}

	return true;
}

bool solve()
{
	std::pair<int, int> gridPos;

	if (!findNextEmpty(gridPos))
		return true; // All empty squares filled

	for (int num = 0; num < 10; num++)
	{
		if (isValid(gridPos, num))
		{
			grid[gridPos.first][gridPos.second] = num;
			if (solve()) // solve recursively
				return true;
			grid[gridPos.first][gridPos.second] = 0; // Reset if conditions are not met
		}
	}

	return false;
}

int main()
{
	std::cout << "Board to solve:\n\n";
	printBoard();

	solve();

	std::cout << "\nSolved board:\n\n";
	printBoard();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
