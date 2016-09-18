#pragma once               
#include <opencv2/highgui/highgui.hpp>                    
#include "opencv2/imgproc/imgproc.hpp" 
#include <iostream>
#include <string>
#include <windows.h>
using namespace cv;
using namespace std;
class maze_front
{
public:
	maze_front(int **tabbb, vector<cv::Point> que, int sizeee, vector<cv::Point> his,  int marg);
	~maze_front();
	void make_maze();
	void make_board();
	void make_walls();
	void make_walls_step_by_step();
	void make_walls_step_by_step2();
	void destroy_wall(Mat img,int j, Point present, Scalar color = Scalar(255, 255, 255)); //0 -left,1-right,2-top,3-down
	Point find_position(int x);// return position of maze destination
	Point find_cordinates(int x);
	void show_queue();
	int is_neighbour(Point one, Point two);
	Mat return_board();
	int return_cell_size();

private:
	int size;
	int **tab;
	int margin;
	int cell_size;
	Mat board;
	vector<Point> queue;
	vector<Point> history;
	int GetDesktopResolution();
	
	

};

