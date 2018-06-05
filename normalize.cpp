#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector <int> data[160];
vector <double> new_data[160];

void read(string file_path) {
  ifstream file(file_path);
  if (file.fail()) {
    cout << "yes\n";

    return;
  }
  string line;
  int cnt = 0;
  while (getline(file, line)) {
    int num = 0;
    for (int i = 0 ; i < line.length() ; ++i) {
      if ('0' <= line[i] && line[i] <= '9') {
        num = num * 10 + int(line[i] - '0');
      } else {
        data[cnt].push_back(num);
        num = 0;
      }
    }
    data[cnt].push_back(num);

    cnt ++;
  }
}

int min(int j){
  int ret = data[0][j];
  for (int i = 0 ; i < 160 ; ++i) {
    if (ret > data[i][j])
      ret = data[i][j];
  }
  return ret;
}

int max(int j){
  int ret = data[0][j];
  for (int i = 0 ; i < 160 ; ++i) {
    if (ret < data[i][j])
      ret = data[i][j];
  }
  return ret;
}

double normalize(int i, int j) {
  return double(data[i][j] - min(j)) / double(max(j) - min(j));
}

void normalize() {
  for (int i = 0 ; i < 160 ; ++i) {
    for (int j = 0 ; j < data[i].size() ; ++j) {
      if (j == data[i].size() - 1)
        new_data[i].push_back(data[i][j]);
      else
        new_data[i].push_back(normalize(i,j));
    }
  }
}
void write (string file_path) {
  ofstream fi;
  fi.open(file_path);
  if(!fi.is_open()) {
    cout << "Can't open the file\n";
  }
  for (int i = 0 ; i < 160 ; ++i) {
    fi << new_data[i][0];
    for (int j = 0 ; j < new_data[i].size(); ++j) {
      fi << "," << new_data[i][j];
    }
    fi << "\n";
  }
}

void clear() {
  for (int i = 0 ; i < 160 ; ++i) {
    data[i].clear();
    new_data[i].clear();
  }
}

int main() {
  read("/home/kadyrbek/Desktop/WiFiLocalization/pure_data/lg_40_routers_16_classes.txt");
  normalize();
  write("/home/kadyrbek/Desktop/WiFiLocalization/pure_data/lg_40_routers_16_classes.normalized.txt");
  clear();

  read("/home/kadyrbek/Desktop/WiFiLocalization/pure_data/lg_40_routers_8_classes.txt");
  normalize();
  write("/home/kadyrbek/Desktop/WiFiLocalization/pure_data/lg_40_routers_8_classes.normalized.txt");
  clear();

  read("/home/kadyrbek/Desktop/WiFiLocalization/pure_data/lg_20_routers_8_classes.txt");
  normalize();
  write("/home/kadyrbek/Desktop/WiFiLocalization/pure_data/lg_20_routers_8_classes.normalized.txt");
  clear();

  read("/home/kadyrbek/Desktop/WiFiLocalization/pure_data/lg_20_routers.txt");
  normalize();
  write("/home/kadyrbek/Desktop/WiFiLocalization/pure_data/lg_20_routers.normalized.txt");
  clear();
  return 0;
}
