#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

//declare struct 
struct node
{
	int priority;
	int**  puzzle;
	struct node *link;
};

//class priority queue
class Priority_queue
{
	private:
		node *front;

	public:
		Priority_queue()
		{
			front = NULL;
		}

	//insert into priority queue
	void insert(int** item, int priority)
	{
		node *tmp, *q;
		tmp = new node;
		tmp -> puzzle = item;
		tmp -> priority = priority;

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

	//delete from priority queue
	int pop(int** puzzles)
	{
		node *tmp;
		if(front == NULL)
		{
			return 1;
		}

		else 
		{
			tmp = front;
			puzzles = tmp -> puzzle;
			front = front -> link;
			free(tmp);

		}
	}

	//print priority queue
	void display()
	{
		node *ptr;

		ptr = front;

		if(front == NULL)
				cout << "Queue is empty" << endl;

		else 
		{
			cout << "Queue is: " << endl;

			cout << "Priority Item" << endl;

			while(ptr != NULL)
			{
				cout << ptr -> priority << " " << ptr -> puzzle << endl;
				ptr = ptr -> link;
			}
		}
	}
};


//main 
/*
int main()
{
	int choice, item, priority;
	Priority_queue pq;

	do
	{
		cout << "1. Insert" << endl;
		cout << "2. Delete" << endl;
		cout << "3. Display" << endl;
		cout << "4. Quit: " << endl;
		cout << "Your choice: ";
		cin >> choice;

		switch(choice)
		{
			case 1:
				cout << "Input the item value to be added in the queue:";
				cin >> item;
				cout << "Enter its priority: ";
				cin >> priority;
				pq.insert(item, priority);
				break;

			case 2:
				pq.del();
				break;

			case 3: 
				pq.display();
				break;

			case 4:
				break;

			default:
				cout << "Wrong choice" << endl;
			}
	
	}while(choice != 4);

	return 0;
}*/
