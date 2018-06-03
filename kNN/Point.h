#include <vector>
#include <string>
#include <fstream>
class Point {
	public:
		//std::vector < std::pair < sting , int  > > Data;
		std::string Class;
		std::string Komnata;

		void Output();
};
void Point::Output() {
	std::ofstream fout("ex.txt");
	const std::string PARSED_DATA_PATH = "/home/kadyrbek/Desktop/WiFiLocalization/parsed_data";
	fout << PARSED_DATA_PATH;
}