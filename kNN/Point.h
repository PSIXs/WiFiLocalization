#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
ofstream fout("ex.txt");
static int to_int(string s) {
	int ans = 0;
	for(int i=0; i<s.size(); i++){
		ans = ans * 10 + s[i] - 48;
	}
	return ans;
}
class Point {
	public:
		vector < pair < string , int  > > Data;
		string Class;
		string Komnata;

		void Input(string point);
		void Output();

};
void Point::Input(string file_name) {
	ifstream file(file_name);
	if (file.fail()) {
    	 cout << "Can't find the file " << file_name << "\n";
    	return;
  	}
  //	int size = 0;
  	string line;
  	while (getline(file, line)) {
	    string mac_address = "";
	    string signal = "";
	    bool is_mac = true;
	    for (size_t i = 0 ; i < line.length() ; ++i) {
		      if(line[i] == ' ') continue;
		      if (line[i] == ',') {
		          is_mac = false;
		          continue;
		      }

		      if (is_mac) {
		        	mac_address += line[i];
		      } 
		      else {
		        signal += line[i];
		      }
		}
		Data.push_back(make_pair(mac_address, to_int(signal)));
//		size++;

	}


}

void Point::Output() {
	
	for(int i=0; i<Data.size(); i++)
		fout << Data[i].first << "        " << Data[i].second << endl;
	fout << "_______________________\n";
}





