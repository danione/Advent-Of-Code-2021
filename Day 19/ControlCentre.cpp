#include "ControlCentre.h"
#include <fstream>
#include <string>
#include <iostream>

ControlCentre::ControlCentre(){
  handleInput();
  runSimulation();
}

void ControlCentre::handleInput(){
  ifstream infile("input.txt");
  string line;
  while(getline(infile,line)){
    if(line.length() == 0)
      continue;
    else if(line.find("---") != string::npos)
      scanners.push_back(new Scanner());
    else{
      int x = stoi(line.substr(0, line.find(',')), 0, 10);
      int y = stoi(line.substr(line.find(',') + 1, line.find(',', line.find(',') + 1)), 0, 10);
      int z = stoi(line.substr(line.find(',', line.find(',') + 1) + 1, line.length()), 0, 10);
      Beacon* b = new Beacon((Beacon){.x = x, .y = y, .z = z});
      scanners.back()->addBeacon(b);
      totalBeacons[b].insert(scanners.back());
    }
  }
}


void ControlCentre::runSimulation(){
  for(int i = 0; i < scanners.size(); i++){
    scanners[i]->fillDistances();
  }
}
