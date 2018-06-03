#include <iostream>
#include "Point.h"
#include <vector>
using namespace std;

const string PARSED_DATA_PATH = "/Users/tynchtykbekkaldybaev/Desktop/WiFiLocalization/parsed_data/t203/";
vector < Point > parsed_points;


void initialize_data_points(string class_num, string komnata, int point_per_class){
	for(int i = 1; i <= point_per_class; i++) {
		string point_name = PARSED_DATA_PATH  + class_num + "."  + to_string(i);
		Point sample;
		sample.Input(point_name);
		sample.Class = class_num;
		sample.Komnata = komnata;	
		parsed_points.push_back(sample);
//		sample.Output();
	}



}


void initialize_data(int number_of_classes,int point_per_class, string komnata){
	for(int cl = 1; cl <= number_of_classes; cl++) {
		string class_num = to_string(cl);
		initialize_data_points(class_num, komnata, point_per_class);
	}

}
int main(){
	int number_of_classes = 1;
	int number_of_point_for_each_class = 5;
	//int number_of_points = number_of_classes * number_of_point_for_each_class;
	string komnata = "t203";

	initialize_data(number_of_classes, number_of_point_for_each_class , komnata);

	for(int i=0; i<parsed_points.size(); i++) {
		parsed_points[i].Output();
	}

}