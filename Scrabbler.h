#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <baseapi.h>
#include <allheaders.h>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "Game.h"

#define T_WIDTH (495/15)

using namespace std;
using namespace cv;

struct BoardImage {
	vector<Point2f> corners;
	Mat image;
	string windowName;
};

class Scrabbler {
private:
	BoardImage prevBoard;
	Mat currBoard;
	Mat homography;
public:
	Scrabbler();
	~Scrabbler();
	vector<Tile> FindNewTiles();
	void CaptureImage();
};


