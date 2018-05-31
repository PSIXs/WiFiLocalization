#include <iostream>
#include <fstream>
#include <map>
#include <set>

using namespace std;

const string PARSED_DATA_PATH = "/home/kadyrbek/Desktop/WiFiLocalization/parsed_data";
const string DATA_PATH = "/home/kadyrbek/Desktop/WiFiLocalization/data";

bool calculateAveragesForPoint (string file_name, int class_id, int point_id, bool is_test = 0) {
  map<string, int> counter;
  map<string, int> signals;
  string line;

  ifstream file(file_name);
  if (file.fail()) {
    // cout << "Can't find the file " << file_name << "\n";
    return false;
  }

  static const string temp_folder_name = "t203";
  string parsed_data_file_path = PARSED_DATA_PATH + "/" + temp_folder_name + "/"
                                 + to_string(class_id)
                                 + "."
                                 + to_string(point_id)
                                 + (is_test ? ".test" : "");
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
      parsed_file << cnt.first << " " << averaged << "\n";
      real_cnt ++;
  }

  parsed_file.close();
  return true;
}


void calculateAveragesForClass(string file_class_name, int class_id, int num_files = 10) {
  // train data
  for (int point_id = 1 ; point_id <= num_files ; ++point_id) {
    string file_name = file_class_name + "." + to_string(point_id) + ".txt";
    calculateAveragesForPoint(file_name, class_id, point_id);
  }

  // test data
  for (int point_id = 1 ; point_id <= num_files ; ++point_id) {
    string file_name = file_class_name + ".test" + to_string(point_id) + ".txt";
    calculateAveragesForPoint(file_name, class_id, point_id, 1);
  }

}


void startAveraging(int num_classes, string data_folder, string file_name_preffix) {
  for (int class_id = 1 ; class_id <= num_classes; ++class_id) {
    string file_class_name = data_folder + "/" + file_name_preffix + "." + to_string(class_id);
    calculateAveragesForClass(file_class_name, class_id);
  }
}

int main(int argc, char const *argv[]) {
  const string preffix = "t202";
  const int num_classes = 9;

  startAveraging(num_classes, DATA_PATH, preffix);
  return 0;
}
