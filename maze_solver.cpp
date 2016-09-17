#include "maze_solver.h"



maze_solver::maze_solver(Mat prim,int cs) : primary(prim),cell_size(cs)
{
	
}


maze_solver::~maze_solver()
{
}

void maze_solver::solving()
{
	Mat temp;
	primary.copyTo(temp);

	cvtColor(temp, temp, CV_BGR2GRAY);
	erode(temp, temp, Mat());
	threshold(temp, temp, 10, 255, CV_THRESH_BINARY_INV);
	imshow("first", temp);
	
	
	std::vector<std::vector<cv::Point> > contours;
	findContours(temp, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	Mat cont = Mat::zeros(primary.size(), CV_8UC1);
	
	int wall_one = 0;
	for (int i = 0; i< contours.size(); i++)
	{
		if (contours[i].size()>wall_one)wall_one = i;
	}
	drawContours(cont, contours, wall_one, CV_RGB(255, 255, 255), CV_FILLED);
	imshow("contours", cont);

	Mat kernel = Mat::ones(cell_size, cell_size, CV_8UC1);
	Mat dil = Mat::zeros(primary.size(), CV_8UC1);
	dilate(cont, dil, kernel);
	imshow("dilate", dil);

	Mat ero = Mat::zeros(primary.size(), CV_8UC1);
	erode(dil, ero, kernel);
	imshow("erode", ero);

	Mat path = Mat::zeros(primary.size(), CV_8UC1);
	absdiff(ero, dil, path);
	imshow("path", path);
	
	Mat path_off = Mat(primary.size(), CV_8UC3,Scalar(0,0,255));
	cvtColor(path, path, CV_GRAY2BGR);
	path_off = path_off&path;
	imshow("path_off", path_off);

	
	primary = primary^path_off;
	imshow("at the end", primary);
	cout<< contours.size();

}


