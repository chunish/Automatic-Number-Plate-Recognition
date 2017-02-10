#include "DetectRegions.h"

int main(int argc,char** argv)
{
	cout << "Opencv Automatic Number Plate Recognition:"<<endl;
	string inputimage_name = "9588DWV.jpg";
	string inputimage_name_nexe = "9588DWV";
	Mat inputimage = imread(inputimage_name);
	imshow(inputimage_name, inputimage);
	cout << "Working with this file:\n " << inputimage_name_nexe << endl;

	//detect possible plate
	//Detect posibles plate regions  
	DetectRegions detectRegions;
	detectRegions.setfilename(inputimage_name_nexe);
	detectRegions.saveRegions = true;
	detectRegions.showSteps = true;
	vector<Plate> posible_regions = detectRegions.run(inputimage);    //2个  

	//Image classifier











	cout<< "Opencv Automatic Number Plate Recognition has been finished!\n\n"<<"Copyright Reserved!"<<endl;
	waitKey(0);
	return 0;
}
