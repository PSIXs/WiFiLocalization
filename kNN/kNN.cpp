#include <iostream>
#include "Point.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
using namespace std;

const string PARSED_DATA_PATH = "/Users/tynchtykbekkaldybaev/Desktop/WiFiLocalization/parsed_data/t203/";
vector < Point > parsed_points;

vector < Point > test_points;




/// PUTTING DATAS IN TEXTFILES TO VECTOR POINTS


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

double getDiff(Point test, Point current) {
	double error = 0;
	for(int i=0; i<test.Data.size(); i++) {
		for(int j=0; j<current.Data.size(); j++) {
			if(test.Data[i].first == current.Data[j].first) {
				error += abs(test.Data[i].second - current.Data[j].second);
				break;
			}
		}
	}
	return error;
}


//  GET ERRORS FOR CERTAIN POINT
vector < pair <double, string> > getErrors(Point test) {
	vector < pair <double, string> > errors;
	for(int i=0; i<parsed_points.size(); i++) {
			Point current = parsed_points[i];
			double er = getDiff(test, current);
			errors.push_back(make_pair(er, current.Class));
	}

	return errors;
}




bool cmp(pair <double, string> a, pair <double, string> b) {
	return a.first < b.first;
}

void run_for_one_test(int KNN, string test_name){
	

	Point test1;
	test1.Input(test_name);
	vector < pair <double, string> > Errors;
	Errors = getErrors(test1);
	sort(Errors.begin(), Errors.end(), cmp);
	
	map < string , int > m;
	map < string , int >:: iterator it;
	int size = Errors.size();
	for(int i=0; i<min(KNN, size); i++) {
		string key = "Class " + Errors[i].second;
		m[key] ++;
		cout << Errors[i].first <<  "  " << Errors[i].second << endl;
	}
	it = m.end();
	it--;

	string answer = it->first;

	cout << answer << endl;


}
int main(){
	int number_of_classes = 9;
	int number_of_point_for_each_class = 5;
	//int number_of_points = number_of_classes * number_of_point_for_each_class;
	string komnata = "t203";

	initialize_data(number_of_classes, number_of_point_for_each_class , komnata);
	
	string test_name = "/Users/tynchtykbekkaldybaev/Desktop/WiFiLocalization/parsed_data/tests/1.2.test";

	int KNN = 1;

	run_for_one_test(KNN, test_name);
	

	//for(int i=0; i<parsed_points.size(); i++) {
	//	parsed_points[i].Output();
	//}


}