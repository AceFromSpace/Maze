#include "maze_front.h"



maze_front::maze_front(int **tabbb, vector<cv::Point> que,  int sizeee, vector<cv::Point> his, int marg):tab(tabbb), queue(que),history(his), size(sizeee),margin(marg)
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
	//make_walls_step_by_step();
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
		destroy_wall(board,temp, find_position(tab[queue[j].x][queue[j].y]));
		else
		{
			int k = j;
			int temp2 = is_neighbour(queue[k], queue[j - 1]);
			while (temp2 == -1)
			{
				k++;
				temp2 = is_neighbour(queue[k], queue[j - 1]);
				
			}
			destroy_wall(board,temp2, find_position(tab[queue[k].x][queue[k].y]));
		}
		j--;
	}
	destroy_wall(board,3, Point(margin + size / 2 * cell_size, margin + (size-1)  * cell_size));
	destroy_wall(board,2, Point(margin + size/2*cell_size,margin+ 0));
}

void maze_front::make_walls_step_by_step()
{
	Mat temp_board = Mat::zeros(board.size(), CV_8UC3);
	board.copyTo(temp_board);
	namedWindow("Step_by_step");
	
	int i = 1;
	Point start;

	/*	while (i <= size*size)
	{
		start = find_position(i);
		rectangle(temp_board, start, Point(start.x + cell_size, start.y + cell_size), 0);
		i++;
	}
	*/
	int j = size*size;

	while (j > 0)
	{
		
		

		int temp = is_neighbour(queue[j], queue[j - 1]);
		if (temp != -1) {
			destroy_wall(temp_board, temp, find_position(tab[queue[j].x][queue[j].y]));
			rectangle(temp_board, Point(queue[j].y * cell_size+1, (queue[j].x*cell_size) +1), Point((queue[j].y + 1) *cell_size - 1, (queue[j].x + 1)* cell_size - 1), Scalar(138, 43, 226), -1);
		}
		else
		{
			int k = j;
			int temp2 = is_neighbour(queue[k], queue[j - 1]);
			while (temp2 == -1)
			{
				k++;
				temp2 = is_neighbour(queue[k], queue[j - 1]);
				rectangle(temp_board, Point(queue[k].y * cell_size + 1, (queue[k].x*cell_size + 1)), Point((queue[k].y + 1) *cell_size - 1, (queue[k].x + 1)* cell_size - 1), Scalar(200, 214,48), -1);
				imshow("Step_by_step", temp_board);
				waitKey(10);
			}
			rectangle(temp_board, Point(queue[j].y * cell_size + 1, (queue[j].x*cell_size + 1)), Point((queue[j].y + 1) *cell_size - 1, (queue[j].x + 1)* cell_size - 1), Scalar(170, 43, 226), -1);
			destroy_wall(temp_board,temp2, find_position(tab[queue[k].x][queue[k].y]));
		}
		imshow("Step_by_step", temp_board);
		waitKey(10);
		j--;
	}
	destroy_wall(temp_board,3, Point(margin + size / 2 * cell_size, margin + (size - 1)  * cell_size));
	destroy_wall(temp_board,2, Point(margin + size / 2 * cell_size, margin + 0));
}

void maze_front::make_walls_step_by_step2()
{
	Mat temp_board = Mat::zeros(board.size(), CV_8UC3);
	board.copyTo(temp_board);
	int j=0;
	int k = 0;
	namedWindow("Step_by_step");

	while (j < history.size())
	{
		if (history[j] == queue[k])
		{
			rectangle(temp_board, Point(queue[j].y * cell_size + 1, (queue[j].x*cell_size) + 1), Point((queue[j].y + 1) *cell_size - 1, (queue[j].x + 1)* cell_size - 1), Scalar(200, 214, 48), -1);
			k++;
		}
		else
			rectangle(temp_board, Point(queue[j].y * cell_size + 1, (queue[j].x*cell_size) + 1), Point((queue[j].y + 1) *cell_size - 1, (queue[j].x + 1)* cell_size - 1), Scalar(138, 43, 226), -1);
		imshow("Step_by_step", temp_board);
		waitKey(200);
		j++;
	}
}

void maze_front::destroy_wall(Mat img ,int j,Point present,Scalar color)
{
	int wall_to_destroy = j;
	switch (wall_to_destroy)
	{
	case 0://left
	{
		line(img, present, Point(present.x, present.y + cell_size), color);

	}break;
	case 1://right
	{
		line(img, Point(present.x + cell_size, present.y), Point(present.x + cell_size, present.y + cell_size), color);

	}break;
	case 2://top
	{
		line(img, present, Point(present.x + cell_size, present.y), color);

	}break;
	case 3://bottom
	{
		line(img, Point(present.x + cell_size, present.y + cell_size), Point(present.x, present.y + cell_size), color);

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


