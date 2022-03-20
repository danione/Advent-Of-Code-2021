#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// Iterative Approach
int smallestFuelConsumpt(vector<int>& crabPos){
  int minSum = INT_MAX;
  for(int i = 0; i < crabPos.size(); i++){
    int tempSum = 0;
    for(int j = 0; j < crabPos.size(); j++){
      tempSum += abs(crabPos[i] - crabPos[j]);
    }
    if(tempSum < minSum){
      minSum = tempSum;
    }
  }
  return minSum;
}

void populateCrabPos(vector<int>& crabPos){
  ifstream inFile("input.txt");
  string value;
  while(getline(inFile, value)){
    string coord;
    stringstream ss(value);
    while(getline(ss, coord, ',')){
      crabPos.push_back(stoi(coord));
    }
  }
}

void printVect(vector<int>& crabPos){
  for(int i = 0; i < crabPos.size(); i++){
    cout << crabPos[i] << ((i+1 < crabPos.size()) ? ", " : "");
  }
  cout << endl;
}

int main(){
  vector<int> crabPos;
  populateCrabPos(crabPos);
  printVect(crabPos);
  cout << smallestFuelConsumpt(crabPos) << endl;
  return 0;
}
