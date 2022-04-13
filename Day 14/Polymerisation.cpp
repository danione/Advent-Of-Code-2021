#include <iostream>
#include <unordered_map>
#include <fstream>

using namespace std;

class Polymer{
  unordered_map<string, pair<string,string>> dict;
  unordered_map<string, long long> occurances;

public:

  template<class T, class U>
  void addToMap(T& map, U str, long long times = 1){
    if(map.find(str) == map.end()){
      map[str] = 0;
      map[str] += times;
    }
    else
      map[str] += times;
  }

  void init(string str){
    for(int i = 0; i < str.length() - 1; i++){
      addToMap(occurances, string() + str[i] + str[i + 1]);
    }
  }

  Polymer(){
    string line;
    ifstream infile("input.txt");
    bool getDict = false;

    while(getline(infile,line)){
      if(line.length() < 1){
        getDict = true;
        continue;
      }

      if(!getDict)
        init(line);
      else{
        string address = line.substr(0, line.find("->") - 1);
        string val = line.substr(line.find("->") + 3, line.length());
        dict[address] = pair<string,string>(
                  string() + address[0] + val, string() + val + address[1]);
      }
    }
  }
  long long subtr(unordered_map<char, long long> tempCount){
    long long maxOcc = LLONG_MIN;
    long long minOcc = LLONG_MAX;

    for (auto& it: tempCount) {
      cout << it.first << ' ' << it.second << endl;
      if(minOcc > it.second)
        minOcc = it.second;
      if(maxOcc < it.second)
        maxOcc = it.second;
    }
    return maxOcc - minOcc;
  }

  unordered_map<char, long long> countLetters(){
    unordered_map<char, long long> tempCount;
    for(auto& pair: occurances){
      for(int i = 0; i < pair.first.length(); i++){
        if(pair.second > 0)
          addToMap(tempCount, pair.first[i], pair.second);
      }
    }
    return tempCount;
  }

  void generate(int cycles){
    for(int i = 0; i < cycles; i++){
      unordered_map<string, long long> tempDict;
      for(auto& pair: occurances){
        addToMap(tempDict,dict[pair.first].first, pair.second);
        addToMap(tempDict,dict[pair.first].second, pair.second);
        pair.second--;
      }
      occurances = tempDict;
      unordered_map<char, long long> tempCount = countLetters();
      for(auto& pair: tempCount){
        pair.second = ceil((long double)pair.second/2);
      }
      if(i + 1 == cycles)
        cout << subtr(tempCount) << endl;
    }
  }

};

int main(){
  Polymer* poly = new Polymer();
  poly->generate(40);
  return 0;
}
