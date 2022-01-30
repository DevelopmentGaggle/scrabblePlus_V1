#include "Scrabbler.h"

static void MouseCallBack(int event, int x, int y, int flags, void* context) {
	if (event == EVENT_LBUTTONDOWN) {
		BoardImage* board = (BoardImage*)context;
		board->corners.push_back(Point2f(x, y));

		circle(board->image, Point(x, y), 10, Scalar(0, 255, 0), 2, 8, 0);
		imshow(board->windowName, board->image);
	}
}

Scrabbler::Scrabbler() {
	VideoCapture camera(0);
	cv::waitKey(0);
	camera >> prevBoard.image;

	prevBoard.image = imread("init.jpg");
	prevBoard.windowName = "Calibration"; //Name of the window
	resize(prevBoard.image, prevBoard.image, Size(800, 800));

	Mat copyImage = prevBoard.image.clone();
	namedWindow(prevBoard.windowName); // Create a window
	setMouseCallback(prevBoard.windowName, MouseCallBack, &prevBoard);
	imshow(prevBoard.windowName, prevBoard.image); // Show our image inside the created window.
	cv::waitKey(0); // Wait for any keystroke in the window

	prevBoard.image = copyImage;

	if (prevBoard.corners.size() != 4) {
		cout << "Error! Calibration Failed. Exiting...";
	}
	else {
		vector<Point2f> normalCorners;
		normalCorners.push_back(Point2f(0, 0));
		normalCorners.push_back(Point2f(0, 495));
		normalCorners.push_back(Point2f(495, 495));
		normalCorners.push_back(Point2f(495, 0));

		homography = findHomography(prevBoard.corners, normalCorners);
		warpPerspective(prevBoard.image, prevBoard.image, homography, Size(495, 495));

		imshow(prevBoard.windowName, prevBoard.image);
		cv::waitKey(0);

		//for (int i = 0; i < prevBoard.corners.size(); i++) {
		//	cout << "X: " << prevBoard.corners[i].x << " Y: " << prevBoard.corners[i].y << endl;
		//}
	}
}

Scrabbler::~Scrabbler() {
	destroyWindow(prevBoard.windowName); //destroy the created window
}

void Scrabbler::CaptureImage() {
	VideoCapture camera(0);
	cv::waitKey(0);
	prevBoard.image = currBoard;
	camera >> currBoard;
	resize(currBoard, currBoard, Size(800, 800));
	warpPerspective(currBoard, currBoard, homography, Size(495, 495));
}


vector<Tile> Scrabbler::FindNewTiles() {
	Mat delta, thresh, prev_g, curr_g, curr_gb, thresh_cp, curr_cp;
	vector<Tile> newTiles;

	cvtColor(prevBoard.image, prev_g, COLOR_BGR2GRAY);
	cvtColor(currBoard, curr_g, COLOR_BGR2GRAY);

	GaussianBlur(curr_g, curr_gb, Size(15, 15), 0);
	imshow("Calibration", curr_gb);
	cv::waitKey(0);
	GaussianBlur(prev_g, prev_g, Size(15, 15), 0);
	imshow("Calibration", prev_g);
	cv::waitKey(0);
	absdiff(curr_gb, prev_g, delta);
	imshow("Calibration", delta);
	cv::waitKey(0);
	threshold(delta, thresh, 15, 255, THRESH_BINARY);
	imshow("Calibration", thresh);
	cv::waitKey(0);
	dilate(thresh, thresh, Mat());
	dilate(thresh, thresh, Mat());
	//dilate(thresh, thresh, Mat());
	imshow("Calibration", thresh);
	cv::waitKey(0);

	thresh.copyTo(thresh_cp);
	vector<vector<Point>> contours;
	findContours(thresh_cp, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
	api->Init(NULL, "eng", tesseract::OEM_LSTM_ONLY);
	api->SetPageSegMode(tesseract::PSM_SINGLE_CHAR);
	api->SetVariable("debug_file", "tesseract.log");

	api->SetVariable("tessedit_char_whitelist", "QWERTYUIOPASDFGHJKLZXCVBNM");
	api->SetVariable("classify_bln_numeric_mode", "0");
	api->SetVariable("tessedit_write_images", "true");

	for (int i = 0; i < contours.size(); i++) {
		if (contourArea(contours[i]) < 20) {
			continue;
		}

		Rect bound = boundingRect(contours[i]);
		currBoard.copyTo(curr_cp);
		rectangle(curr_cp, bound, Scalar(0, 255, 0));

		for (int j = 0; j < 15; j++) {
			for (int k = 0; k < 15; k++) {
				if (bound.contains(Point((T_WIDTH / 2) + j * T_WIDTH, (T_WIDTH / 2) + k * T_WIDTH))) {
					Mat letter = currBoard(Rect(T_WIDTH * j, T_WIDTH * k, T_WIDTH, T_WIDTH));
					//threshold(letter, letter, 50, 255, 0);

					//Mat testr = imread("t.jpg");
					api->SetImage(letter.data, letter.cols, letter.rows, 3, letter.step);
					string text = string(api->GetUTF8Text());
					cout << "Recognized: " << text << endl;

					imshow("Calibration", letter);
					cv::waitKey(0);

					Tile t;
					t.row = j;
					t.col = k;
					t.letter = text[0];
					newTiles.push_back(t);
				}
			}
		}
	}

	imshow("Calibration", curr_cp);
	cv::waitKey(0);

	return newTiles;
}
