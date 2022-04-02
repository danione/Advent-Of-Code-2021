#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

class Polymer{
  string temp;
  unordered_map<string, char> dict;
  unordered_map<char, int> occurances;

  void handleInput();
  void polymerisation();
  void addToOccurances(string);
  int subtr();
public:
  Polymer(){
    handleInput();
    addToOccurances(temp);
  }

  void generate(int);
};

int Polymer::subtr(){
  int maxOcc = INT_MIN;
  int minOcc = INT_MAX;
  for (auto& it: occurances) {
    if(minOcc > it.second)
      minOcc = it.second;
    if(maxOcc < it.second)
      maxOcc = it.second;
  }
  cout << minOcc << ' ' << maxOcc << endl;
  return maxOcc - minOcc;
}

void Polymer::addToOccurances(string str){
  for(int i = 0; i < str.length(); i++){
    if(occurances.find(temp[i]) == occurances.end())
      occurances[str[i]] = 1;
    else
      occurances[str[i]]++;
  }
}

void Polymer::handleInput(){
  string line;
  ifstream infile("input.txt");
  bool insertInDict = false;
  while(getline(infile, line)){
    if(line.size() < 1){
      insertInDict = true;
      continue;
    }

    if(!insertInDict)
      temp = line;
    else{
      string address = line.substr(0, line.find("->") - 1);
      string val = line.substr(line.find("->") + 3, line.length());
      dict[address] = val[0];
    }
  }
}

void Polymer::generate(int cycles){
  for(int i = 0; i < cycles; i++){
    polymerisation();
    cout << "-----" << endl;
    cout << temp << endl;
  }
  cout << subtr() << endl;
}

void Polymer::polymerisation(){
  int start = 0;
  vector <string> tempCont;
  string finished;

  while(start < temp.length() - 1){
    string p;
    p.push_back(temp[start]);
    p.push_back(temp[start+1]);
    tempCont.push_back(p);
    start++;
  }

  for(int i = 0; i < tempCont.size(); i++){
    finished += tempCont[i][0];
    finished += dict[tempCont[i]];
    addToOccurances(string(1,dict[tempCont[i]]));
  }
  finished += tempCont[tempCont.size()-1][1];

  temp = finished;
}

int main(){
  Polymer* pol = new Polymer();
  pol->generate(10);
  delete pol;
  return 0;
}
