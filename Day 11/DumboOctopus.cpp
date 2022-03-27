#include <iostream>
#include <fstream>
#include <set>
using namespace std;

class OctopusRadar{
  int octopusR[100];
  set<int> toSimulate;
  set<int> simulated;
  const int width = 10;
  int blinks;
public:

  OctopusRadar(){
    blinks = 0;
    string value;
    ifstream infile("input.txt");
    int row = 0;
    while(getline(infile, value)){
      for(int i = 0; i < value.length(); i++){
        octopusR[row*value.length() + i] = value[i] - '0';
      }
      row++;
    }
  }

  void print(){
    for(int i = 0; i < 100; i++){
      if(i % 10 == 0 && i != 0)
        cout << endl;
      cout << octopusR[i] << " ";
    }
    cout << endl;
  }

  void litUp(int index){
      octopusR[index]++;
      bool existsInToSimulate = toSimulate.find(index) != toSimulate.end();
      bool existsInSimulated = simulated.find(index) != simulated.end();
      if(octopusR[index] > 9 && !existsInSimulated && !existsInToSimulate){
        toSimulate.insert(index);
        blinks++;
      }
  }

  void blinkAdjacent(int index){
    int x = index % width;
    int y = index / width;

    bool lowerColumn = (x - 1 >= 0);
    bool higherColumn = (x + 1 < width);
    bool lowerRow = (y - 1 >= 0);
    bool higherRow = (y + 1 < width);

    if(lowerColumn && lowerRow)
      litUp(x - 1 + width*(y-1));

    if(lowerColumn && higherRow)
      litUp(x - 1 + width*(y+1));

    if(higherColumn && lowerRow)
      litUp(x + 1 + width*(y-1));

    if(higherColumn && higherRow)
      litUp(x + 1 + width*(y+1));

    if(lowerColumn)
      litUp(x - 1 + width*(y));

    if(higherColumn)
      litUp(x + 1 + width*(y));

    if(lowerRow)
      litUp(x + width*(y - 1));

    if(higherRow)
      litUp(x + width*(y + 1));
  }

  void sparkle(){
    auto iterator = toSimulate.begin();
    while(iterator != toSimulate.end()){
      blinkAdjacent(*iterator);
      simulated.insert(*iterator);
      toSimulate.erase(iterator);
      iterator = toSimulate.begin();
    }
    iterator = simulated.begin();
    while(iterator != simulated.end()){
      octopusR[*iterator] = 0;
      simulated.erase(iterator);
      iterator = simulated.begin();
    }
  }

  void simulate(int steps){
    for(int i = 0; i < steps; i++){
      for(int j = 0; j < 100; j++)
        litUp(j);
      sparkle();
    }
  }

  int getBlinks(){return blinks;}
};

int main(){
  OctopusRadar* radar = new OctopusRadar();
  radar->print();
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  radar->simulate(100);
  radar->print();
  cout << radar->getBlinks() << endl;
  return 0;
}
