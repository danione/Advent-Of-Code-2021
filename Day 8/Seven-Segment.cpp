#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

class CodedLine{
  string codes[10];
  vector<string> values;
  vector<string> input;
public:
  CodedLine(){
    for(int i = 0; i < 10; i++){
      codes[i] = ".";
    }
  }

  int lacks(unordered_set<char>& chars, string value){
    for(int i = 0; i < value.size(); i++){
      if(chars.find(value[i]) == chars.end()){
        return 0;
      }
    }
    return -1;
  }

  int contains(unordered_set<char>& chars, string value){
    for(int i = 0; i < value.size(); i++){
      if(chars.find(value[i]) == chars.end()){
        return -1;
      }
    }
    return 0;
  }

  int findNumberLen6(string val){
    if(codes[1] == ".") return -1;

    unordered_set<char> chars;
    for(auto& charV: val){
      chars.insert(charV);
    }

    if(lacks(chars, codes[1]) == 0)
      return 6;

    if(codes[4] == ".") return -1;

    if(contains(chars, codes[4]) == 0)
      return 9;
    else
      return 0;
  }

  int findNumberLen5(string val){
    if(codes[1] == ".") return -1;

    unordered_set<char> chars;
    for(auto& charV: val){
      chars.insert(charV);
    }

    if(contains(chars, codes[1]) == 0)
      return 3;

    if(codes[6] == ".") return -1;
    chars.clear();
    for(auto& charV: codes[6]){
      chars.insert(charV);
    }
    if(contains(chars, val) == 0)
      return 5;
    else
      return 2;
  }

  bool change(int address, string value){
    if(address < 0) return false;

    codes[address] = value;
    return true;
  }

  void decode(){
    int i = 0;
    while(values.size() > 0){
      bool changed;
      switch(values[i].size()){
        case 2: changed = change(1, values[i]); break;
        case 3: changed = change(7, values[i]); break;
        case 4: changed = change(4, values[i]); break;
        case 5: changed = change(findNumberLen5(values[i]), values[i]); break;
        case 6: changed = change(findNumberLen6(values[i]), values[i]); break;
        case 7: changed = change(8, values[i]); break;
      }
      if(!changed && i < values.size())
        i++;
      else if(changed){
        values.erase(values.begin() + i);
        i = 0;
      } else{
        i = 0;
      }
    }
    print();
  }

  void print(){
    cout << "Codes " << endl;
    for(int i = 0; i < 10; i++){
      cout << codes[i] << ' ';
    }
    cout << endl << "Left " << endl;
    for(int i = 0; i < values.size(); i++){
      cout << values[i] << ' ';
    }
    cout << endl << "Right " << endl;
    for(int i = 0; i < input.size(); i++){
      cout << input[i] << ' ';
    }
    cout << endl;
  }

  void getInput(string value){
    string left = value.substr(0, value.find('|'));
    string right = value.substr(value.find('|') + 2, value.length());
    size_t pos = 0;
    stringstream ss(left);
    string word;

    while(ss >> word){
      values.push_back(word);
    }

    ss.clear();
    ss.str(right);

    while(ss >> word){
      input.push_back(word);
    }
  }

  int sum(){
    string sum;

    for(int i = 0; i < input.size(); i++){
      unordered_set<char> chars;
      for(auto& charV: input[i]){
        chars.insert(charV);
      }
      for(int j = 0; j < 10; j++){
        if(input[i].length() == codes[j].length() && contains(chars, codes[j]) == 0){
          sum += to_string(j);
          break;
        }
      }

    }
    return stoi(sum);
  }
};

void handleInput(){
  ifstream infile("input.txt");
  string value;
  long unsigned int sum = 0;

  while(getline(infile, value)){
    CodedLine* line = new CodedLine();
    line->getInput(value);
    line->decode();
    sum += line->sum();
  }
  cout << sum << endl;
}

int main(){
  handleInput();
  return 0;
}
