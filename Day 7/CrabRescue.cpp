#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

// int sumOfInts(int n){
//   static unordered_map<int, int> numbers;
//   if(!numbers[n]){
//     if(n < 2){
//       return n;
//     }
//     numbers[n] += n + sumOfInts(n - 1);
//   }
//   return numbers[n];
// }

int sumOfInts(int n){
  static unordered_map<int, int> numbers;
  if(!numbers[n])
    numbers[n] = n*(1 + n)/2;
    
  return numbers[n];
}


// Iterative Approach
int smallestFuelConsumpt(vector<int>& crabPos){
  int minSum = INT_MAX;
  int max = *max_element(crabPos.begin(), crabPos.end());
  for(int j = 0; j <= max; j++){
    int tempSum = 0;
    for(int i = 0; i < crabPos.size(); i++){
      tempSum += sumOfInts(abs(crabPos[i] - j));
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
  // printVect(crabPos);
  cout << smallestFuelConsumpt(crabPos) << endl;
  return 0;
}
