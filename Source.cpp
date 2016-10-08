#include <opencv2/highgui/highgui.hpp>            
#include "opencv2/imgproc/imgproc.hpp" 
#include <string> 
#include <iostream> 
#include "maze_back.h"
#include "maze_front.h"
#include "maze_solver.h"

using namespace cv;                       
using namespace std;

int main()
{

	cout << "Set size of maze (max. 84)" << endl;
	int number;
	cin >> number;

	cout << "Step by step mode(y-yes)" << endl;
	char yes_or_no;
	cin >> yes_or_no;

	maze_back back(number);



	back.fill_the_table();
	back.make_maze(number - 1, number / 2);
	int cell_size;
	maze_front* front;
	if(yes_or_no=='y') front = new maze_front(back.return_tab(),back.return_queue(), back.return_size(), back.return_history(),0,true);
	else  front = new maze_front(back.return_tab(), back.return_queue(), back.return_size(), back.return_history(), 0,false);
	front->make_maze();
	maze_solver solver(front->return_board(),front->return_cell_size());
	solver.solving();
	waitKey();                   
	return 0;
}