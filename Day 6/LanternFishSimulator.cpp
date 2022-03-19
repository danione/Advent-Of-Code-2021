#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

void printTimers(vector<int>& lanternFish){
  for(int i = 0 ; i < lanternFish.size(); i++){
    cout << lanternFish[i] << ((i+1 < lanternFish.size())? "," : "");
  }
  cout << endl;
}

void populateLanternFish(vector<int>& lanternFish){
  string value;
  ifstream InFile("Input.txt");
  while(getline(InFile, value)){
    stringstream ss(value);
    string lantTimer;
    while(getline(ss, lantTimer, ',')){
      lanternFish.push_back(stoi(lantTimer));
    }
  }
}

void dayIterate(vector<int>& lanternFish, int days){
  int day = 1;
  while(day <= days){
    cout << "After " << day << ((day == 1) ? " day: " : " days: ");
    int sizePre = lanternFish.size();
    for(int i = 0; i < sizePre; i++){
      cout << lanternFish[i] << ((i+1 < lanternFish.size())? "," : "");
      if(lanternFish[i] > 0)
        lanternFish[i]--;
      else{
        lanternFish[i] = 6;
        lanternFish.push_back(8);
      }
    }
    cout << endl;
    day++;
  }
}

int main(){
  vector<int> lanternFish;
  populateLanternFish(lanternFish);
  cout << "Initial state: ";
  printTimers(lanternFish);
  dayIterate(lanternFish, 80);
  cout << lanternFish.size() << endl;
  return 0;
}
