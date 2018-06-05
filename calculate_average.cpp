#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>


using namespace std;

const string PARSED_DATA_PATH = "/home/kadyrbek/Desktop/WiFiLocalization/parsed_data/";
const string DATA_PATH = "/home/kadyrbek/Desktop/WiFiLocalization/data/lg";

bool calculateAveragesForPoint (string file_name, int class_id, int point_id, bool is_test = 0) {
  map<string, int> counter;
  map<string, int> signals;
  string line;

  ifstream file(file_name);
  if (file.fail()) {
    cout << "Can't find the file " << file_name << "\n";
    return false;
  }

  string temp_folder_name = (is_test? "lg/tests" : "lg");
  string parsed_data_file_path = PARSED_DATA_PATH + "/" + temp_folder_name + "/"
                                 + to_string(class_id)
                                 + "."
                                 + to_string(point_id);

  ofstream parsed_file;
  parsed_file.open(parsed_data_file_path);
  if(!parsed_file.is_open()) {
    // cout << "Can't open parsed_data_file " << parsed_data_file_path << "\n";
    return false;
  }


  while (getline(file, line)) {
    string mac_address = "";
    string signal = "";
    bool is_mac = true;
    for (size_t i = 0 ; i < line.length() ; ++i) {
      if(line[i] == ' ') continue;
      if (line[i] == '-') {
          is_mac = false;
          continue;
      }

      if (is_mac) {
        mac_address += line[i];
      } else {
        signal += line[i];
      }
    }
    //cout << "mac_address = " << mac_address << "\n";
    //cout << "signal = " << signal << "\n";
    counter[mac_address] += 1;
    signals[mac_address] += stoi(signal);
  }

  int real_cnt = 0;
  for (pair<string, int> cnt : counter) {
      if (cnt.second <= 1) // biased
        continue;

      int averaged = signals[cnt.first] / cnt.second;
      parsed_file << cnt.first << "," << averaged << "\n";
      real_cnt ++;
  }

  parsed_file.close();
  return true;
}


void calculateAveragesForClass(string file_class_name, int class_id, int num_files = 10) {
  // train data
/*
  vector<int> test_points = {rand() % 10 + 1};
  int rand_num;
  while (test_points.size() < 3){
    while (test_points.back() == (rand_num = (rand() % 10 + 1))); // 30% of data
    test_points.push_back(rand_num);
  }

  for (int point_id : test_points) { // tests
    string file_name = file_class_name + "." + to_string(point_id) + ".txt";
    calculateAveragesForPoint(file_name, class_id, point_id, 1);
  }
  */
  for (int point_id = 1 ; point_id <= num_files ; ++point_id) {
    // if (find(test_points.begin(), test_points.end(), point_id) != test_points.end())
      //continue;
    string file_name = file_class_name + "." + to_string(point_id) + ".txt";
    calculateAveragesForPoint(file_name, class_id, point_id);
  }
}


void startAveraging(int num_classes, string data_folder, string file_name_preffix) {
  for (int class_id = 1 ; class_id <= num_classes; ++class_id) {
    string file_class_name = data_folder + "/" + file_name_preffix + "." + to_string(class_id);
    calculateAveragesForClass(file_class_name, class_id);
  }
}

int main(int argc, char const *argv[]) {
  const string preffix = "lg";
  const int num_classes = 16;
  srand(time(NULL));

  startAveraging(num_classes, DATA_PATH, preffix);
  return 0;
}
