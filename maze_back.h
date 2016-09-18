#pragma once
#include <string> 
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "opencv2/imgproc/imgproc.hpp" 
#include <opencv2/highgui/highgui.hpp>  

using namespace std;

class maze_back
{
public:
	maze_back(int si);
	~maze_back();
	void fill_the_table();
	void show_the_table();
	void show_queue();
	int make_maze(int x, int y);
	int** return_tab();
	vector<cv::Point> return_queue();
	vector<cv::Point> return_history();
	int return_size();
	

private:
	int **tab;
	vector<cv::Point> queue;
	vector <cv::Point> history;
	int size;
	int counter;
};

