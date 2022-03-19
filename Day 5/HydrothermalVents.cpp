#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void iterate(int arr[][1000], pair<int,int> start,pair<int,int> end){
  int diffX = abs(end.first - start.first);
  int diffY = abs(end.second - start.second);
  if(start.first > end.first){
    start.first *= (-1);
  }
  if(start.second > end.second){
    start.second *= (-1);
  }
  int iteratorX = 0;
  int iteratorY = 0;
  bool finished = false;
  while(iteratorX != diffX || iteratorY != diffY){
    int xAdvance = abs(start.first + iteratorX);
    int yAdvance = abs(start.second + iteratorY);

    arr[yAdvance][xAdvance]++;
    if(iteratorX != diffX){
      iteratorX++;
    }
    if(iteratorY != diffY){
      iteratorY++;
    }
  }
  arr[abs(start.second + iteratorY)][abs(start.first + iteratorX)]++;
}

pair<int,int> getPair(string str){
  string x = str.substr(0, str.find(","));
  string y = str.substr(str.find(",") + 1, str.length());

  return pair<int,int>(stoi(x), stoi(y));
}

bool equals(pair<int,int> one, pair<int,int> two){
  return one.first == two.first || one.second == two.second;
}

void populateMap(int arr[][1000]){
  ifstream inFile("input.txt");
  string value;
  while(getline(inFile, value)){
    pair<int,int> startCoordinates = getPair(value.substr(0, value.find("->")));
    pair<int,int> endCoordinates = getPair(value.substr(value.find("->") + 3));
    if(equals(startCoordinates, endCoordinates))
      iterate(arr, startCoordinates, endCoordinates);
  }
}

int printArray(int arr[][1000]){
  int count = 0;
  for(int i = 0; i < 1000; i++){
    for(int j = 0; j < 1000; j++){
      if(arr[i][j] > 0)
        cout << arr[i][j];
      else
        cout << ".";
      if(arr[i][j] > 1)
        count++;
      cout << " ";
    }
    cout << endl;
  }
  return count;
}

int main(){
  int arr[1000][1000];
  fill(arr[0], arr[0] + 1000 * 1000, 0);
  populateMap(arr);
  cout << printArray(arr) << endl;
  return 0;
}
