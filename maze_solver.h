#pragma once             
#include <opencv2/highgui/highgui.hpp>                    
#include "opencv2/imgproc/imgproc.hpp" 
#include <iostream>
#include <string>
using namespace cv;
using namespace std;
class maze_solver
{
public:
	maze_solver(Mat prim, int cs);
	~maze_solver();
	void solving();
	Point find_two_walls();
private:
	Mat primary;
	int cell_size;
	
};

