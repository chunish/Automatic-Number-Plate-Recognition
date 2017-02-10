#ifndef DETECTREGIONS_H
#define DETECTREGIONS_H
#include <string.h>
#include <vector>

#include "Plate.h"

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cvaux.h>
#include "Plate.h"
using namespace std;
using namespace cv;


class DetectRegions
{
	public:
		DetectRegions();
		string filename;
		void setfilename(string f);
		bool saveRegions;
		bool showSteps;
		vector<Plate> run(Mat input);
	private:
		vector<Plate> segment(Mat input);
		bool VerifySizes(RotatedRect mr);//RotatedRect
		Mat histeq(Mat in);
};
#endif