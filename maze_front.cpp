#include "maze_front.h"



maze_front::maze_front(int **tabbb, vector<cv::Point> que, int sizeee, int marg):tab(tabbb), queue(que),size(sizeee),margin(marg)
{
	cell_size = (GetDesktopResolution() - 2 * margin-50) / sizeee;

}


maze_front::~maze_front()
{
}

void maze_front::make_maze()
{

	
	make_board();
	make_walls();
	imshow("image", board);

}
void maze_front::show_queue()
{
	for (int i = 0; i < queue.size(); i++)
	{
		cout << queue[i] << " ";
		if (i % 10 == 0)cout << endl;
	}
}
int maze_front::is_neighbour(Point one, Point two)
{
	if (one.x - two.x == 0 && one.y - two.y == 1)return 0;
	if (one.x - two.x == 0 && one.y - two.y == -1)return 1;
	if (one.x - two.x == 1 && one.y - two.y == 0)return 2;
	if (one.x - two.x == -1 && one.y - two.y == 0)return 3;
	return -1;
}

Mat maze_front::return_board()
{
	return board;
}

int maze_front::GetDesktopResolution()
{
		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktop);
		int vertical = desktop.bottom;

		return vertical;
	
}

int maze_front::return_cell_size()
{
	return cell_size;
}

void maze_front::make_board()
{
	const Scalar white = Scalar(255, 255, 255);
	const Scalar black = Scalar(0, 0, 0);
	board = Mat(Size(margin * 2 + size*cell_size+1, margin * 2 + size * cell_size+1), CV_8UC3, white);
	rectangle(board, Point(margin, margin), Point(board.cols - margin, board.rows - margin), black);
}

void maze_front::make_walls()
{
	int i = 1;
	Point start;
	while (i <= size*size)
	{
		start = find_position(i);
		rectangle(board, start, Point(start.x + cell_size, start.y + cell_size), 0);
		i++;
	}
	int j = size*size;
	Point present;
	while (j > 0)
	{
		present =find_position(j);		
		int temp= is_neighbour(queue[j], queue[j - 1]);
		if(temp!=-1)
		destroy_wall(temp, find_position(tab[queue[j].x][queue[j].y]));
		else
		{
			int k = j;
			int temp2 = is_neighbour(queue[k], queue[j - 1]);
			while (temp2 == -1)
			{
				k++;
				temp2 = is_neighbour(queue[k], queue[j - 1]);
				
			}
			destroy_wall(temp2, find_position(tab[queue[k].x][queue[k].y]));
		}
		j--;
	}
	destroy_wall(3, Point(margin + size / 2 * cell_size, margin + (size-1)  * cell_size));
	destroy_wall(2, Point(margin + size/2*cell_size,margin+ 0));
}

void maze_front::destroy_wall(int j,Point present,Scalar color)
{
	int wall_to_destroy = j;
	switch (wall_to_destroy)
	{
	case 0://left
	{
		line(board, present, Point(present.x, present.y + cell_size), color);

	}break;
	case 1://right
	{
		line(board, Point(present.x + cell_size, present.y), Point(present.x + cell_size, present.y + cell_size), color);

	}break;
	case 2://top
	{
		line(board, present, Point(present.x + cell_size, present.y), color);

	}break;
	case 3://bottom
	{
		line(board, Point(present.x + cell_size, present.y + cell_size), Point(present.x, present.y + cell_size), color);

	}break;



	}
}

Point maze_front::find_position(int x)
{
	Point max;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (tab[i][j] == x)max = Point(margin+j*cell_size,margin+i*cell_size );
		}

	}
	
	return max;
}

Point maze_front::find_cordinates(int x)
{
	Point cord;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (tab[i][j] == x)cord = Point(i,j);
		}

	}

	return cord;
	
}


