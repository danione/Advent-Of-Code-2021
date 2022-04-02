#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class Mapper{
  vector<char> sheet;
  int maxR_;
  int maxC_;
  void handleInput();
public:
  Mapper(int maxColumns, int maxRows): maxR_(maxRows), maxC_(maxColumns){
    for(int i = 0; i < maxRows*maxColumns; i++)
      sheet.push_back('.');
    handleInput();
  }

  void insert(int x, int y){
    sheet[y*maxC_ + x] = 'X';
  }

  void print(){
    int sum = 0;
    for(int i = 0; i < maxR_; i++){
      for(int j = 0; j < maxC_; j++){
        cout << sheet[i*maxC_ + j];
        if(sheet[i*maxC_ + j] == 'X')
          sum++;
      }
      cout << endl;
    }
    cout << sum << endl;
  }

  void fold(bool, int);

  void cleanse(bool,int);
};

void Mapper::handleInput(){
  ifstream infile("input.txt");
  string line;
  bool folding = false;
  while(getline(infile,line)){
    if(line.size() < 1){
      folding = true;
      continue;
    }

    if(!folding){
      int x = stoi(line.substr(0, line.find(',')));
      int y = stoi(line.substr(line.find(',')+1, line.length()));
      insert(x,y);
    } else{
      bool xFold = line.find('x') != string::npos;
      int foldVal = stoi(line.substr(line.find('=') + 1, line.length()));
      fold(xFold, foldVal);
    }
  }
}

void Mapper::cleanse(bool xFold, int value){

  if(xFold){
    int diff = maxC_ - value;
    int incr = value;

    for(int i = 0; i < maxR_; i++){
      int end = incr + diff;
      sheet.erase(sheet.begin() + incr, sheet.begin() + end);
      incr += value;
    }
  } else{
    int i = (value + 1) * maxC_;
    sheet.erase(sheet.begin() + i, sheet.end());
  }
}

void Mapper::fold(bool xFold, int value){
  int x;
  int y;
  if(xFold){
    x = value + 1;
    y = 0;
  } else{
    x = 0;
    y = value + 1;
  }

  int i = y*maxC_ + x;
  int size = maxR_*maxC_;

  while(i < size){
    if(xFold && (i % maxC_) < value){
      i+=value + 1;
    }

    x = i % maxC_;
    y = i / maxC_;

    if(sheet[i] == 'X' && !xFold){
      sheet[(maxR_ - 1 - y) * maxC_ + x] = sheet[i];
    }
    else if(sheet[i] == 'X'){
      sheet[y * maxC_ + (maxC_ - 1 - x)] = sheet[i];
    }
    i++;
  }
  cleanse(xFold, value);

  if(xFold)
    maxC_ = value;
  else
    maxR_ = value;

  print();
}

int main(){
  ifstream infile("input.txt");
  string line;
  int maxX = INT_MIN;
  int maxY = INT_MIN;
  while(getline(infile,line)){
    if(line.size() < 1){
      break;
    }
    int x = stoi(line.substr(0, line.find(',')));
    int y = stoi(line.substr(line.find(',')+1, line.length()));
    if(maxX < x)
      maxX = x;
    if(maxY < y)
      maxY = y;
  }

  Mapper* map = new Mapper(maxX + 1,maxY + 1);
  return 0;
}
