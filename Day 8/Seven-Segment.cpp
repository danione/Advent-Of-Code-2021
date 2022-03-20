#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

vector<string> getInput(string value, char delimeter){
  stringstream ss(value);
  string newVal;
  vector<string> newVect;
  getline(ss, newVal, delimeter);
  while(getline(ss, newVal, delimeter)){
    stringstream space(newVal);
    string singleVal;
    while(getline(space, singleVal, ' ')){
      newVect.push_back(singleVal);
    }
  }
  return newVect;
}

void printVect(vector<string> input){
  short one = 2;
  short four = 4;
  short seven = 3;
  short eight = 7;
  int count = 0;
  for(int i = 0; i < input.size(); i++){
    if(input[i].length() == one || input[i].length() == four
    || input[i].length() == seven || input[i].length() == eight){
      count++;
    }
  }
  cout << count << endl;
}

void handleInput(){
  ifstream infile("input.txt");
  string value;
  vector<string> input;
  while(getline(infile, value)){
    vector<string> temp = getInput(value, '|');
    input.insert(input.end(), temp.begin(), temp.end());
  }

  printVect(input);
}

int main(){
  handleInput();
  return 0;
}
