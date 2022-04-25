#include <iostream>
#include <cmath>
#include "Scanner.h"

void Scanner::addBeacon(Beacon* b){
  scanned.push_back(b);
}

void Scanner::fillDistances(){
  for(int f = 0; f < scanned.size() - 1; f++){
    for(int l = f + 1; l < scanned.size(); l++){
      distance[scanned[f]].push_back(calcDistance(scanned[f], scanned[l]));
    }
  }
}

pair<Beacon*, double> Scanner::calcDistance(Beacon* a, Beacon* b){
  double distance = pow((a->x - b->x), 2.0) + pow((a->y - b->y), 2.0) + pow((a->z - b->z), 2.0);
  cout << distance << endl;
  return pair<Beacon*,double>(b, sqrt(distance));
}
