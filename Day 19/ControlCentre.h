#include <unordered_map>
#include <vector>
#include <set>
#include "Scanner.h"
using namespace std;

class ControlCentre{
  unordered_map<Beacon*, set<Scanner*>> totalBeacons;
  vector<Scanner*> scanners;
public:
  ControlCentre();
  void handleInput();
  void runSimulation();
};
