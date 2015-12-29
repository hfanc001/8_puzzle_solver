#include <iostream>
#include <array>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <chrono>
#include <thread>
#include <cstdlib>
using namespace std;

//functions
//display 8 puzzle
void display(int** puzzle);
int  compare(int** puzzle);
//operators
int up(int i, int j, int** puzzle);
int down(int i, int j, int** puzzle);
int left(int i, int j, int** puzzle);
int right(int i, int j, int** puzzle);
int checkBlank(int &i, int &j, int** puzzle);
//wait
void wait(int sec);

int main()
{
	//variables
	int puzzleChoice = 0;
	int **puzzle = new int*[3];
	for(int i = 0; i < 3; i++)
	{
		puzzle[i] = new int[3];
	}
	int iBlank = 0, jBlank = 0;
	int win = 0;

	//beginning
	cout << "Welcome to my 8 puzzle!" << endl;
	cout << "Please enter your puzzle, use a ZERO to represent blank." << endl;

	for(int i = 0; i < 3; i++)
	{
		cout << "For row " << i << ", please enter your number seperated by space." << endl;
		for(int j = 0; j < 3; j++)
		{
			cin >> puzzle[i][j];
		}
	}
	
	while(win != 1)
	{

		int op = 0;
		display(puzzle);
		
		int findBlank = checkBlank(iBlank, jBlank, puzzle);
			if(findBlank > 0)
				cout << "Error: No blank inserted" << endl;

		cout << "Enter operation: " << endl
		     << "    1. Up" << endl
		     << "    2. Down" << endl
		     << "    3. Left" << endl
		     << "    4. Right" << endl;
		cin >> op;

		if(op == 1)
		{
			int doUp = up(iBlank, jBlank, puzzle);
			if (doUp > 0)
				cout << "Error: UP not allowed" << endl;

		}
		
		else if(op == 2)
		{
			int doDown = down(iBlank, jBlank, puzzle);
			if(doDown > 0)
				cout << "Error: DOWN not allowed" << endl;
		}

		else if(op == 3)
		{
			int doLeft = left(iBlank, jBlank, puzzle);
			if(doLeft > 0)
				cout << "Error: LEFT not allowed" << endl;
		}

		else if(op == 4)
		{
			int doRight = right(iBlank, jBlank, puzzle);
			if(doRight > 0)
				cout << "Error: RIGHT not allowed" << endl;
		}
		
		else 
		{
			cout << "Operation not recognized" << endl;
		}

		win = compare(puzzle);
	}

	cout << "Congratulation!!!!!!!!" << endl
	     << "You just win the 8 puzzle!" << endl;

	string non;
	cout << "Hit any key and ENTER to continue..." << endl;
	cin >> non;

	for(int i = 0; i < 1000; i++)
	{
		cout 
	     << "              ||    || ||||||| ||    || ||||||   ||      ||" << endl
	     << "              ||    || ||      ||||  || ||    ||  ||    || " << endl
         << "              |||||||| ||||||  || || || |||||||    ||  ||  " << endl
	     << "              ||    || ||      ||  |||| ||    ||     ||    " << endl
	     << "              ||    || ||||||| ||    || ||     ||    ||    " << endl
	     << endl
	     << "                        ||||||||   ||||||                  " << endl 
	     << "                           ||     |||    ||                " << endl
	     << "                           ||       ||||                   " << endl
	     << "                           ||    ||    |||                 " << endl
	     << "                        ||||||||   ||||||                  " << endl
		 << endl
	     << "    ||   ||        || |||||||  ||||||    ||||||   ||     || |||||||  |||||||" << endl
	     << "   ||||   ||  ||  ||  ||      |||    || ||    ||  |||| |||| ||       |||||||" << endl
         << "  ||  ||   | |  | |   ||||||    ||||    ||    ||  || ||| || ||||||    ||||| " << endl
	     << " ||||||||  ||    ||   ||     ||    |||  ||    ||  ||     || ||         |||  " << endl
	     << " ||    ||  ||    ||   |||||||  ||||||    ||||||   ||     || |||||||    |||  " << endl;

	     for(int j = 0; j < 15; j++)
	     	 cout << endl;
	}

	return 0;
}

//functions
//display 8 puzzle
void display(int** puzzle)
{
	cout << "-------------------" << endl;

	for(int i = 0; i < 3; i++)
	{
		cout << "|  ";
		for(int j = 0; j < 3; j++)
		{
			if(puzzle[i][j] == 0)
				cout << "   |  ";
			else
				cout << puzzle[i][j] << "  |  ";
		}
		cout << endl << "-------------------" << endl;
	}
}

//comparision b/w curr state and goal state
int compare(int** puzzle)
{
	int pt = 1;

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(pt != 9)
			{
				if(puzzle[i][j] != pt)
				{
					return 0; //fail
				}
			}
			pt++;
		}
	}
	return 1; //success
}

//operators
//i and j are the location of ZERO
//check possible/impossible condition and do the operation
//return 0 for successful operation, else return 1
int up(int i, int j, int** puzzle)
{
	if(i == 0) //cannot move up for the top row
		return 1;

	int tmp = puzzle[i][j];
	puzzle[i][j] = puzzle[i-1][j];
	puzzle[i-1][j] = tmp;
	return 0;
}
int down(int i, int j, int** puzzle)
{
	if(i == 2) //cannot move down for the last row
		return 1;

	int tmp = puzzle[i][j];
	puzzle[i][j] = puzzle[i+1][j];
	puzzle[i+1][j] = tmp;
	return 0;
}
int left(int i, int j, int** puzzle)
{
	if(j == 0) //cannot move left for the first column
		return 1;
	
	int tmp = puzzle[i][j];
	puzzle[i][j] = puzzle[i][j-1];
	puzzle[i][j-1] = tmp;
	return 0;
}
int right(int i, int j, int** puzzle)
{
	if(j == 2) //cannot move right for the last column
		return 1;
	
	int tmp = puzzle[i][j];
	puzzle[i][j] = puzzle[i][j+1];
	puzzle[i][j+1] = tmp;
	return 0;
}


//check where blank is, for initial condition
int checkBlank(int &i, int &j, int** puzzle)
{
	for(int m = 0; m < 3; m++)
	{
		for(int n = 0; n < 3; n++)
		{
			if(puzzle[m][n] == 0)
			{
				i = m;
				j = n;
				return 0;
			}
		}
	}

	return 1;
}

