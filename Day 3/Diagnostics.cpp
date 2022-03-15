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
  vector<string> co2;
  vector<string> oxygen;
public:
  Submarine()
  {
  }

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

    int lines = 0;
    while (getline(infile, line))
    {
      istringstream iss(line);
      string value;

      if (!(iss >> value)) { break; } // error
      if(lines == 0)
      {
        init(value.length());
        lines++;
      }
      oxygen.push_back(value);
      co2.push_back(value);
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

  void getMostCommonBit(vector<string>& meter, int pos, bool oxygenMeter){
    zeros[pos] = 0;
    ones[pos] = 0;
    for(int i = 0; i < meter.size(); i++){
      if(meter[i][pos] == '1')
        ones[pos]++;
      else if(meter[i][pos] == '0')
        zeros[pos]++;
    }
    bool oneIsMajority;
    if(zeros[pos]>ones[pos]){
      oneIsMajority = false;
    } else{oneIsMajority = true;}

    int iterator = 0;

    while(iterator < meter.size() && meter.size() > 2){
      if(oxygenMeter){
        if(oneIsMajority && meter[iterator][pos] != '1'){
          meter.erase(meter.begin() + iterator);
        } else if(!oneIsMajority && meter[iterator][pos] != '0'){
          meter.erase(meter.begin() + iterator);
        } else {
          iterator++;
        }
      } else{
        if(!oneIsMajority && meter[iterator][pos] != '1'){
          meter.erase(meter.begin() + iterator);
        } else if (oneIsMajority && meter[iterator][pos] != '0'){
          meter.erase(meter.begin() + iterator);
        } else{
          iterator++;

        }
      }

    }
  }

  int getLifeSupportRating(){
    int startingOxygenBit = 0;
    int startingCO2Bit = 0;
    while(startingOxygenBit < oxygen[0].length() || startingCO2Bit < co2[0].length()){
      if(startingOxygenBit < oxygen[0].length()){
        getMostCommonBit(oxygen, startingOxygenBit, true);
        startingOxygenBit++;
      }
      if(co2.size() != 1){
        getMostCommonBit(co2, startingCO2Bit, false);
        startingCO2Bit++;
      }
    }
    return stoi(oxygen[0], 0, 2) * stoi(co2[0], 0, 2);
  }
};

int main(){
  Submarine* submarine = new Submarine();
  submarine->processReport("input.txt");
  cout << submarine->getReportResults() << endl;
  submarine->processReport("input.txt");
  cout << submarine->getLifeSupportRating() << endl;
  return 0;
}
