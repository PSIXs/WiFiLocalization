#include <iostream>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

const string DATA_PATH = "/home/kadyrbek/Desktop/WiFiLocalization/parsed_data/lg";

const string PURE_DATA_PATH = "/home/kadyrbek/Desktop/WiFiLocalization/pure_data/lg_40_routers_16_classes.txt";


class MACinfo{
public:
    int point_id;
    int class_id;
    int signal;
    MACinfo(int class_id, int point_id, int signal) {
      this->class_id = class_id;
      this->point_id = point_id;
      this->signal = signal;
    }
};

map <string, vector <MACinfo> > H; //

bool parse_data (string file_path, int class_id, int point_id) {
  ifstream file(file_path);
  if (file.fail()) {
    cout << "Can't find the file " << file_path << "\n";
    return false;
  }
  string line;

  while (getline(file, line)) {
    string mac_address = "";
    string signal_str = "";
    bool is_mac = true;
    for (size_t i = 0 ; i < line.length() ; ++i) {
      if (line[i] == ',') {
          is_mac = false;
          continue;
      }
      if (is_mac) {
        mac_address += line[i];
      } else {
        signal_str += line[i];
      }
    }
    int signal = stoi(signal_str);
    H[mac_address].push_back(MACinfo(class_id, point_id, signal));
  }
}

void analyze() {
  int counter = 0;
  ofstream fi;
  fi.open(PURE_DATA_PATH);
  if(!fi.is_open()) {
    cout << "Can't open the file\n";
  }
  const static int POINT_NUMBER = 160;
  std::vector<int> signals[POINT_NUMBER + 2];

  for (pair<string, vector<MACinfo> > info : H) {

    if (info.second.size() <= 140)
      continue;
      cout << info.first << " " << info.second.size() << "\n";

      for (int point = 1 ; point <= POINT_NUMBER ; point ++) {
        MACinfo found(0,0,0);
        bool is_found = false;
        for (MACinfo i : info.second) {
//        cout << (i.class_id - 1) * 16 + i.point_id << " -- " << i.class_id << ", " << i.point_id << "\n";
          if (point == (i.class_id - 1) * 10 + i.point_id) {
            found = i;
            is_found = true;
            break;
          }
        }
        if (is_found)
          signals[point].push_back(found.signal);
        else
          signals[point].push_back(0);

      }

    counter ++;
  }

  for (int point = 1 ; point <= POINT_NUMBER ; point ++) {
    for (int sig : signals[point]) {
      fi << sig << ",";
    }
    fi << (point - 1) / 10 + 1 <<  endl;
  }
  // 382 different
  cout << "Count = " << counter << "\n";

}

void parseForClass(string class_file_name, int class_id) {
  static const int num_files = 10;

  for (int point_id = 1 ; point_id <= num_files ; ++point_id) {
    string file_name = class_file_name + "." + to_string(point_id);
    parse_data(file_name, class_id, point_id);
  }
}

void startParsingData(int num_classes, string data_folder) {
  for (int class_id = 1 ; class_id <= num_classes; ++class_id) {
    string file_class_name = data_folder + "/" + to_string(class_id);
    parseForClass(file_class_name, class_id);
  }
}

int main() {
  const string preffix = "lg";
  const int num_classes = 16;

  startParsingData(num_classes, DATA_PATH);
  analyze();

  return 0;
}
