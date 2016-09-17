#include <opencv2/highgui/highgui.hpp>            //Do³¹czenie potrzebnych nag³ówków 
#include "opencv2/imgproc/imgproc.hpp" 
#include <string> 
#include <iostream> 
#include "maze_back.h"
#include "maze_front.h"
#include "maze_solver.h"

using namespace cv;                        //Przestrzeñ nazw OpenCV 
using namespace std;

int main()
{

	cout << "Set size of maze " << endl;
	int number;
	cin >> number;
	maze_back back(number);



	back.fill_the_table();
	back.make_maze(number - 1, number / 2);
	back.show_the_table(); 

	int cell_size;
	maze_front front(back.return_tab(),back.return_queue(), back.return_size(),0);
	front.make_maze();
	maze_solver solver(front.return_board(),front.return_cell_size());
	solver.solving();
	waitKey();                   
	return 0;
}