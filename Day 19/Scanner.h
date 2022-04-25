#include <vector>
#include <unordered_map>
using namespace std;

struct Beacon{
  int x;
  int y;
  int z;
};

class Scanner{
  vector<Beacon*> scanned;
  unordered_map<Beacon*, vector<pair<Beacon*, double>>> distance;
public:
  void addBeacon(Beacon*);
  void fillDistances();
  pair<Beacon*, double> calcDistance(Beacon*,Beacon*);
};
