#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
using namespace std;

class ProbeLauncher{
  pair<int,int> targetXRange, targetYRange;
  int maxY;
public:
  ProbeLauncher(){
    ifstream infile("input.txt");
    string line, str;
    getline(infile,line);
    stringstream ss(line);

    int index = 0;
    while(getline(ss, str, ' ')){
      string first = str.substr(2, str.find("..") - 2);
      string last = str.substr(str.find("..") + 2, str.length());

      if(index == 2)
        targetXRange = pair<int, int>(stoi(first,0,10), stoi(last, 0, 10));
      else if(index == 3)
        targetYRange = pair<int, int>(stoi(first,0,10), stoi(last, 0, 10));

      index++;
    }
  }

  int calc(int steps, int yVel){
    return steps*yVel - steps*(steps - 1)/2;
  }

  bool valid(int x, int y){
    int posX = 0, posY = 0;
    while(true){
      posX += x;
      posY += y;
      if(posX >= targetXRange.first && posX <= targetXRange.second
        && posY >= targetYRange.first && posY <= targetYRange.second)
        return true;

      y--;
      if(x > 0)
        x--;

      if(posX > targetXRange.second || posY < targetYRange.first)
        break;

      if(x == 0 && posX < targetXRange.first)
        break;
    }
    return false;
  }

  void launch(){
    int velYMax = -targetYRange.first - 1;
    int steps = velYMax + 1;
    maxY = calc(steps, velYMax);
    cout << maxY << endl;

    int count = 0;

    for(int y = targetYRange.first; y <= velYMax; y++)
      for(int x = 1; x <= targetXRange.second; x++){
        if(valid(x,y))
          count++;
      }
    cout << count << endl;
  }
};

int main(){
  ProbeLauncher * pr = new ProbeLauncher();
  pr->launch();
  return 0;
}
