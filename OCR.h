#ifndef OCR_H
#define OCR_H
#include <string.h>  
#include <vector>  

#include "Plate.h"  

#include <opencv/cv.h>  
#include <opencv/highgui.h>  
#include <opencv/cvaux.h>  
#include <opencv/ml.h>  

using namespace std;
using namespace cv;


#define HORIZONTAL    1  
#define VERTICAL    0  

class CharSegment{
public:
	CharSegment();
	CharSegment(Mat i, Rect p);
	Mat img;
	Rect pos;
};

class OCR{
public:
	bool DEBUG;
	bool saveSegments;
	string filename;                        //待识别的图像名  
	static const int numCharacters;         //字符总数  
	static const char strCharacters[];      //字符  
	OCR(string trainFile);
	OCR();
	string run(Plate *input);
	int charSize;
	Mat preprocessChar(Mat in);
	int classify(Mat f);
	void train(Mat trainData, Mat trainClasses, int nlayers);
	int classifyKnn(Mat f);
	void trainKnn(Mat trainSamples, Mat trainClasses, int k);
	Mat features(Mat input, int size);

private:
	bool trained;
	vector<CharSegment> segment(Plate input);
	Mat Preprocess(Mat in, int newSize);
	Mat getVisualHistogram(Mat *hist, int type);
	void drawVisualFeatures(Mat character, Mat hhist, Mat vhist, Mat lowData);
	Mat ProjectedHistogram(Mat img, int t);
	bool verifySizes(Mat r);
	CvANN_MLP  ann;
	CvKNearest knnClassifier;
	int K;
};



#endif