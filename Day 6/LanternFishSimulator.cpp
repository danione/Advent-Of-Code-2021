#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <map>
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

// void dayIterate(vector<int>& lanternFish, int days){
//   int day = 1;
//   while(day <= days){
//     //cout << "After " << day << ((day == 1) ? " day: " : " days: ");
//     int sizePre = lanternFish.size();
//     for(int i = 0; i < sizePre; i++){
//       //cout << lanternFish[i] << ((i+1 < lanternFish.size())? "," : "");
//       if(lanternFish[i] > 0)
//         lanternFish[i]--;
//       else{
//         lanternFish[i] = 6;
//         lanternFish.push_back(8);
//       }
//     }
//     //cout << endl;
//     day++;
//   }
// }

long unsigned dayIterateIt(vector<int>& lanternFish, int days){
  int day = 1;
  long unsigned size = lanternFish.size();
  unordered_map <int,vector<int>> dayIterator;
  for(int i = 0; i < lanternFish.size(); i++){
    dayIterator[lanternFish[i]].push_back(i);
  }

  while(day < days){
    for(int i = 0; i < dayIterator[day].size(); i++){
      int currentFish = dayIterator[day][i];
      dayIterator[day + 7].push_back(currentFish);
      size++;
      dayIterator[day + 9].push_back(size);
    }
    dayIterator.erase(day);
    day++;
  }

  return size;
}

// long unsigned dayIterate(vector<int>& lanternFish, int days){
//   int day = 1;
//   long unsigned size = lanternFish.size();
//   unordered_map <int,int> dayIterator;
//   for(int i = 0; i < lanternFish.size(); i++){
//     if(dayIterator[lanternFish[i]]){
//       dayIterator[lanternFish[i]]++;
//     } else
//       dayIterator[lanternFish[i]] = 1;
//   }
//
//   while(day < days){
//     for(int i = 0; i < dayIterator[day]; i++){
//       if(dayIterator[day + 7]){
//         dayIterator[day + 7]++;
//       } else
//         dayIterator[day + 7] = 1;
//       size++;
//       if(dayIterator[day + 9]){
//         dayIterator[day + 9]++;
//       } else
//         dayIterator[day + 9] = 1;
//     }
//     dayIterator.erase(day);
//     day++;
//   }
//
//   return size;
// }

void init(map<int, long unsigned>& tracker, vector<int> lanternFish){
  for(int i = 0; i <= 8; i++){
    tracker[i] = 0;
  }
  for(int i = 0; i < lanternFish.size(); i++){
    tracker[lanternFish[i]]++;
  }
}

void print(map<int, long unsigned>& tracker){
  for(int i = 0; i <= 8; i++){
    cout << tracker[i] << ", ";
  }
  cout << endl;

}

long unsigned sum(map<int, long unsigned>& tracker){
  long unsigned sum = 0;
  for(int i = 0; i <= 8; i++){
    sum += tracker[i];
  }
  return sum;
}

long unsigned dayIterate(vector<int>& lanternFish, int days){
  map<int, long unsigned> tracker;
  int day = 1;
  init(tracker, lanternFish);
  long unsigned lastFront = 0;
  while(day < days){
    for(int i = 0; i <= 7; i++){
      swap(tracker[i], tracker[i+1]);
    }
    tracker[7] += tracker[0];
    lastFront = tracker[0];
    day++;
  }
  return sum(tracker);
}



int main(){
  vector<int> lanternFish;
  populateLanternFish(lanternFish);
  // cout << "Initial state: ";
  // printTimers(lanternFish);

  cout << dayIterate(lanternFish, 256) << endl;
  // cout << dayIterateIt(lanternFish, 80) << endl;

  return 0;
}
