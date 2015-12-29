#include <iostream>
#include <array>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <queue>
using namespace std;

//functions
//display 8 puzzle
void display(int** puzzle);
//comparision b/w curr state and goal state
int compare(int** puzzle, int algorithm, int &h);
int location(int i, int j, int num);
//operators
int up(int i, int j, int** puzzle);
int down(int i, int j, int** puzzle);
int left(int i, int j, int** puzzle);
int right(int i, int j, int** puzzle);
int checkBlank(int &i, int &j, int** puzzle);

//declare struct 
struct node
{
	int priority;
	int g;
	int h;
	int** puzzle;
	struct node *link;
};

//class priority queue
class Pri_queue
{
	private:
		node *front;
	
	public:
		Pri_queue()
		{
			front = NULL;
		}

		void insert(int** item, int priority, int g, int h)
		{ 
			node *tmp, *q;
			tmp = new node;
			int** newPuzzle = new int*[3];
			
			for(int i = 0; i < 3; i++)
			{
				newPuzzle[i] = new int[3];
			}

			for(int i = 0; i < 3; i++)
			{
				for(int j = 0; j < 3; j++)
				{
					newPuzzle[i][j] = item[i][j];
				}
			}
			tmp -> puzzle = newPuzzle;
			tmp -> priority = priority;
			tmp -> g = g;
			tmp -> h = h;

			if(front == NULL || priority < front -> priority)
			{
				tmp -> link = front;
				front = tmp;
			}

			else 
			{
				q = front;
				while(q -> link != NULL && q -> link -> priority <= priority)
				{
					q = q -> link;
				}
				tmp -> link = q -> link;
				q -> link = tmp;
			}
		}

		int pop(int** puzzle, int &g, int &h)
		{
			node *tmp;
			if(front == NULL)
			{
				return 1;
			}

			else
			{
				tmp = front;
				for(int i = 0; i < 3; i++)
				{
					for(int j = 0; j < 3; j++)
					{
						int tmpN = tmp -> puzzle[i][j];
						puzzle[i][j] = tmpN;
					}
				}
				g = tmp -> g;
				h = tmp -> h;
				front = front -> link;
				free(tmp);
				return 0;
			}
		}

		int count()
		{
			int num = 0;
			node *tmp;
			if(front != NULL)
			{
				tmp = front;
				do
				{
					num++;
					tmp = tmp -> link;
				}while(tmp != NULL);
			}
			
			return num;
		}

		void display_q()
		{
			cout << "There are " << endl;
			cout << count() << " items in queue" << endl;

			node *tmp;
			tmp = front;
			while(1 == 1) 
			{
				if(tmp != NULL)
				{
					display(tmp -> puzzle);
					tmp = tmp -> link;
				}
				else 
					return;
			}
		}
};

int main()
{
	//variables
	int puzzleChoice = 0, algorithm = 0;
	int totalNode = 0, maxQueue = 0, depth = 0;
	bool success = false;
	int **puzzle = new int*[3];
	for(int i = 0; i < 3; i++)
	{
		puzzle[i] = new int[3];
	}
	int iBlank = 0, jBlank = 0;
	queue<int **> myQueue;

	//beginning
	cout << "Welcome to my 8 puzzle!" << endl;
	do
	{
		cout << "Which puzzle would you like to use?" << endl
			 << "    1. default puzzle" << endl
			 << "    2. self-defined puzzle" << endl;
		cin >> puzzleChoice;
	}while(puzzleChoice != 1 && puzzleChoice != 2);

	if(puzzleChoice == 1)
	{
		puzzle[0][0] = 1;
		puzzle[0][1] = 2;
		puzzle[0][2] = 3;

		puzzle[1][0] = 4;
		puzzle[1][1] = 8;
		puzzle[1][2] = 0;

		puzzle[2][0] = 7;
		puzzle[2][1] = 6;
		puzzle[2][2] = 5;
	}

	if(puzzleChoice == 2)
	{
		cout << "Please enter your puzzle, use a ZERO to represent blank." << endl;

		for(int i = 0; i < 3; i++)
		{
			cout << "For row " << i << ", please enter your number seperated by space." << endl;
			for(int j = 0; j < 3; j++)
			{
				cin >> puzzle[i][j];
			}
		}
	}//run self-define funct

	int findBlank = checkBlank(iBlank, jBlank, puzzle);
	if(findBlank > 0)
		cout << "Error: No blank inserted" << endl;

	//pick algorithm
	cout << "What kind of algorithm would you like to use today?"<< endl;
	cout << "    1. Uniform Cost Search" << endl 
		 << "    2. A* Misplace Tile Heuristic" << endl 
		 << "    3. A* Manhattan Distance Heuristic" << endl;
	cin >> algorithm;

	//start
	cout << "This is your initial state: " << endl;

	//run algorithm
	Pri_queue pq;
	int choice;
	int distance = 0;
	int g = 0, h = 0;
	
	cout << "Expanding state: " << endl;
	distance  = compare(puzzle, algorithm, h);
	pq.insert(puzzle, distance, g, h); //insert initial state
    	
	do
	{
		int popping = pq.pop(puzzle, g, h);
		int suc;
		if(algorithm == 1)
		{
			suc = compare(puzzle, algorithm, h);
		}
		else
			suc = h;
		if(suc != 0)
		{
			cout << "The best state to expand with a g(n) = " << g << " and h(n) = " << h << " is: " << endl;
			display(puzzle);
		
			cout << "Expanding this node..." << endl;
	
			//add operator to queue
			int work = 0;
			//copy puzzle
			int** tmpPuzzleU = new int*[3];
			for(int i = 0; i < 3; i++)
			{
				tmpPuzzleU[i] = new int[3];
			}
			
			for(int i = 0; i < 3; i++)
			{
				for(int j = 0; j < 3; j++)
				{
					int tmp = puzzle[i][j];
					tmpPuzzleU[i][j] = tmp;
				}
			}

			g++;

			//go up operator
			findBlank = checkBlank(iBlank, jBlank, puzzle);
			work = up(iBlank, jBlank, tmpPuzzleU);
			if(work == 0) //success perform the operator
			{
				int here = compare(tmpPuzzleU, algorithm, h); //calculate the heuristic
				if(algorithm == 1)
					h = 0;
				distance = g + h;
				//cout << "Blank up success with g: " << g << " h: " << h << endl;
				//display(tmpPuzzleU);
				pq.insert(tmpPuzzleU, distance, g, h);
				totalNode++;
			}
		 	 
			int** tmpPuzzleD = new int*[3];
			for(int i = 0; i < 3; i++)
			{
				tmpPuzzleD[i] = new int[3];
			}
			

			for(int i = 0; i < 3; i++)
			{
				for(int j = 0; j < 3; j++)
				{
					int tmp = puzzle[i][j];
					tmpPuzzleD[i][j] = tmp;
				}
			}

			//go down operator
			findBlank = checkBlank(iBlank, jBlank, puzzle);
			work = down(iBlank, jBlank, tmpPuzzleD);
			if(work == 0) //success perform the operator
			{
				int here = compare(tmpPuzzleD, algorithm, h); //calculate the heuristic'
				if(algorithm == 1)
					h = 0;
				distance = g + h;
				//cout << "Blank down successi with g: " << g << " h: " << h << endl;
				//display(tmpPuzzleD);
				pq.insert(tmpPuzzleD, distance, g, h);
				totalNode++;
			}
			 	 
			int** tmpPuzzleL = new int*[3];
			for(int i = 0; i < 3; i++)
			{
				tmpPuzzleL[i] = new int[3];
			}
			

			for(int i = 0; i < 3; i++)
			{
				for(int j = 0; j < 3; j++)
				{
					int tmp = puzzle[i][j];
					tmpPuzzleL[i][j] = tmp;
				}
			}

			//go left operator
			findBlank = checkBlank(iBlank, jBlank, puzzle);
			work = left(iBlank, jBlank, tmpPuzzleL);
			if(work == 0) //success perform the operator
			{
				int here = compare(tmpPuzzleL, algorithm, h); //calculate the heuristic
				if(algorithm == 1)
					h = 0;
				distance = g + h;
				//cout << "Blank left success with g: " << g << " h: " << h << endl;
				//display(tmpPuzzleL);
				pq.insert(tmpPuzzleL, distance, g, h);	
				totalNode++;
			}
 	 
			int** tmpPuzzleR = new int*[3];
			for(int i = 0; i < 3; i++)
			{
				tmpPuzzleR[i] = new int[3];
			}

			for(int i = 0; i < 3; i++)
			{
				for(int j = 0; j < 3; j++)
				{
					int tmp = puzzle[i][j];
					tmpPuzzleR[i][j] = tmp;
				}
			}

			//go right operator
			findBlank = checkBlank(iBlank, jBlank, puzzle);
			work = right(iBlank, jBlank, tmpPuzzleR);
			if(work == 0) //success perform the operator
			{
				int here = compare(tmpPuzzleR, algorithm, h); //calculate the heuristic
				if(algorithm == 1)
					h = 0;
				distance = g + h;
				//cout << "Blank right success with g: " << g << " h: " << h << endl;
				//display(tmpPuzzleR);
				pq.insert(tmpPuzzleR, distance, g, h);
				totalNode++;
			}

			depth = g;
			if(maxQueue < pq.count())
			{
				maxQueue = pq.count();
			}
		}

		else
		{
			success = true;
		}

	}while(!success && pq.count() != 0); //if no pending solution or is complete
	
	display(puzzle);
	cout << "Goal!" << endl;
	cout << "To solve this problem, the search algorithm expanded a total of "<< totalNode << " nodes" << endl;
	cout << "The maximum number of nodes in the queue at any one time was " << maxQueue << endl;
	cout << "The depth of the goal node was " << depth << endl;

}

//display function
void display(int** puzzle)
{
	cout << "-------------------" << endl;

	for(int i = 0; i <  3; i++)
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
//if complete, return 0(goal state)
//if uniform search
//      return 1 (h(n) always 0)
//if A* with hamming distance(misplace tile)
//      return # of tiles misplace
//if A* with Manhattan distance
//      return min # of steps to get to goal state
int compare(int** puzzle, int algorithm, int &h)
{
	if(algorithm == 1) //uniform search
	{
		int k = 1;
		h = 0;
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				//if not the last blank tile
				if((i != 2) || ((i == 2) && (j != 2)))
				{
					//if does not match goal state
					if(puzzle[i][j] != k)
					{
						return 1; //fail 
					}
				}
				
				k++;
			}
		}
		//if everything matches
		return 0;
	}

	else if(algorithm == 2) //A* with Hamming distance(misplace)
	{
		int k = 1;
		int misplace = 0;
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				//if not the last blank tile
				if((i != 2) || ((i == 2) && (j != 2)))
				{
					//if not match
					if(puzzle[i][j] != k)
					{
						misplace++;
					}
				}

				k++;
			}
		}
		h = misplace; //if no misplace(0), its success
		return h;
	}

	else if(algorithm == 3) //A* with Manhattan Distance
	{
		int k = 1;
		int manhattan = 0;
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				//if not match  
				if(puzzle[i][j] != k && puzzle[i][j] != 0)
				{
					manhattan += location(i, j, puzzle[i][j]);
				}
				k++;
			
			}
		}
		h = manhattan; //if no distance, its success
		return h;
	}

	return 0;
}
				 
int location(int i, int j, int num)
{

	if(num == 1)
		return i+j;

	else if(num == 2)
		return i + abs(j-1);
	
	else if(num == 3)
		return i + abs(j-2);

	else if(num == 4)
		return abs(i-1) + j;

	else if(num == 5)
		return abs(i-1) + abs(j-1);
	
	else if(num == 6)
		return abs(i-1) + abs(j-2);

	else if(num == 7)
		return abs(i-2) + j;

	else if(num == 8)
		return abs(i-2) + abs(j-1);

	else if(num == 0)
		return abs(i-2) + abs(j-2);
	else 
		return 0;
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
