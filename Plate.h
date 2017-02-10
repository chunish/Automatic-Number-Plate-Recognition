#ifndef Plate_h
#define Plate_h
#include"head1.h"
class Plate{
public:
	Plate();
	Plate(Mat img, Rect pos);
	string str();
	Rect position;
	Mat plateImg;
	vector<char> chars;
	vector<Rect> charsPos;
};

#endif
