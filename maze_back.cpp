#include "maze_back.h"
 


maze_back::maze_back(int si):size(si)
{
	srand(time(NULL));
	counter = 0;

	tab = new int*[size];
	for (int i = 0; i < size; i++)tab[i] = new int[size];
	
}


maze_back::~maze_back()
{
}
void maze_back::fill_the_table()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			tab[i][j] = 0;
		}
	}
}

void maze_back::show_the_table()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << tab[i][j] << " ";
		}
		cout << endl << endl;
	}

}

void maze_back::show_queue()
{
	for (int i = 0; i < queue.size(); i++)
	{
		cout << queue[i] << " ";
		if (i % 10 == 0)cout << endl;
	}
}

int maze_back::make_maze(int x, int y)
{
	history.push_back(cv::Point(x, y));

	int p = rand() % 4;

	for (int i = 0; i < 4; i++)
	{
		p++;
		p = p % 4;
		if (((x - 1 < 0) && (p == 0)) || ((x + 1 > size - 1) && (p == 1)) || ((y - 1 < 0) && (p == 2)) || ((y + 1>size - 1) && (p == 3)))continue;
		if (((p == 0) && (tab[x - 1][y] != 0)) || ((p == 1) && (tab[x + 1][y] != 0)) || ((p == 2) && (tab[x][y - 1] != 0)) || ((p == 3) && (tab[x][y + 1] != 0)))continue;


		switch (p)
		{
		case 0:
		{
			tab[x][y] = -1;
			make_maze(x - 1, y) + 1;
		}break;
		case 1:
		{
			tab[x][y] = -1;
			make_maze(x + 1, y) + 1;
		}break;
		case 2:
		{
			tab[x][y] = -1;
			make_maze(x, y - 1) + 1;
		}break;
		case 3:
		{
			tab[x][y] = -1;
			make_maze(x, y + 1) + 1;
		}break;
		default:
		{
			cout << "something gone wrong" << endl;
		}break;
		}
	}

	tab[x][y] = counter++;
	queue.push_back(cv::Point(x, y));
	if (x == 0 && y == 0)
	{
		cout << "finish" << endl;
		return 1;
	}
}

int ** maze_back::return_tab()
{
	return tab;
}

vector<cv::Point> maze_back::return_queue()
{
	return queue;
}

vector<cv::Point> maze_back::return_history()
{
	return history;
}

int maze_back::return_size()
{
	return size;
}
