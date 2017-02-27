#include "DetectRegions.h"
#include "OCR.h"
int main(int argc,char** argv)
{
	cout << "Opencv Automatic Number Plate Recognition:"<<endl;
	string inputimage_name = "0209BMW.jpg";
	string inputimage_name_nexe = "0209BMW";
	Mat inputimage = imread(inputimage_name);
	//imshow(inputimage_name, inputimage);
	cout << "Working with this file:\n " << inputimage_name_nexe <<endl<< "\n------------------------------------------------------------------------\n";

	//detect possible plate
	//Detect posibles plate regions  
	DetectRegions detectRegions;
	detectRegions.setfilename(inputimage_name_nexe);
	detectRegions.saveRegions = true;
	detectRegions.showSteps = true;
	vector<Plate> posible_regions = detectRegions.run(inputimage);    //2¸ö  

	//Image classifier
	FileStorage fs;
	fs.open("SVM.xml", FileStorage::READ);
	Mat SVM_TrainingData;
	Mat SVM_Classes;
	fs["TrainingData"] >> SVM_TrainingData;
	fs["classes"] >> SVM_Classes;
	//Set SVM params  
	CvSVMParams SVM_params;
	SVM_params.svm_type = CvSVM::C_SVC;
	SVM_params.kernel_type = CvSVM::LINEAR; //CvSVM::LINEAR;  
	SVM_params.degree = 0;
	SVM_params.gamma = 1;
	SVM_params.coef0 = 0;
	SVM_params.C = 1;
	SVM_params.nu = 0;
	SVM_params.p = 0;
	SVM_params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 1000, 0.01);
	//Train SVM  
	CvSVM svmClassifier(SVM_TrainingData, SVM_Classes, Mat(), Mat(), SVM_params);

	//For each possible plate, classify with svm if it's a plate or no  
	vector<Plate> plates;
	for (int i = 0; i< posible_regions.size(); i++)
	{
		Mat img = posible_regions[i].plateImg;
		Mat p = img.reshape(1, 1);
		p.convertTo(p, CV_32FC1);

		int response = (int)svmClassifier.predict(p);
		string imgn = format("img%d",i);
		if (response == 1){ plates.push_back(posible_regions[i]); 
		imshow(imgn, img);
		}
			
		else
			cout << "Sorry! No valiable Plate has been detedted in the pic\n";
		
		/*if(response==1)
		*/
		cout << "	****************\n     Possible Plate" << i << ".jpg  Classifier Result£º" << response << endl << endl;
	}

	OCR ocr("OCR.xml");
	ocr.saveSegments = true;
	ocr.DEBUG = false;
	ocr.filename = inputimage_name_nexe;
	for (int i = 0; i< plates.size(); i++){
		Plate plate = plates[i];

		string plateNumber = ocr.run(&plate);
		string licensePlate = plate.str();
		cout << "================================================\n";
		cout << "	License plate number: " << licensePlate << "\n";
		cout << "================================================\n";
		rectangle(inputimage, plate.position, Scalar(0, 0, 200));
		putText(inputimage, licensePlate, Point(plate.position.x, plate.position.y), CV_FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 200), 2);
		if (false){
			imshow("Plate Detected seg", plate.plateImg);
			cvWaitKey(0);
		}

	}
	imshow("Plate Detected", inputimage);
	/*for (;;)
	{
		int c;
		c = cvWaitKey(10);
		if ((char)c == 27)
			break;
	}*/








	cout<< "\n\n\n\n\n\n"<<"---------------------------------------------------------------------------------\n"<<"		Opencv Automatic Number Plate Recognition has been finished!\n\n"<<"				Copyright Reserved!"<<endl;
	waitKey(0);
	return 0;
}