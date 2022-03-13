#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Submarine{
  vector<int> zeros;
  vector<int> ones;
  string gammaRate;
  string epsilonRate;
public:
  Submarine()
  {}

  void init(int size){
    for(int i = 0; i < size; i++)
    {
      zeros.push_back(0);
      ones.push_back(0);
    }
  }

  void executeCommand(string value){
    for(int i = 0; i < value.length(); i++){
      if(value[i] == '1')
        ones[i]++;
      else if(value[i] == '0')
        zeros[i]++;
    }
  }

  void processReport(string filename){
    string line;
    ifstream infile(filename);
    getline(infile, line);
    init(line.length());
    while (getline(infile, line))
    {
      istringstream iss(line);
      string value;

      if (!(iss >> value)) { break; } // error

      executeCommand(value);
    }
  }

  int getReportResults(){
    for(int i = 0; i < zeros.size(); i++){
      if(zeros[i] > ones[i]){
        gammaRate+=('0');
        epsilonRate+=('1');
      } else{
        gammaRate+=('1');
        epsilonRate+=('0');
      }
    }
    return stoi(gammaRate, 0, 2) * stoi(epsilonRate, 0, 2);
  }
};

int main(){
  Submarine* submarine = new Submarine();
  submarine->processReport("input.txt");
  cout << submarine->getReportResults() << endl;
  return 0;
}
