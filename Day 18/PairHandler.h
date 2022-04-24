#include <stack>
#include <vector>
#include <string>
#include <set>
#include "PairTree.h"

class PairHandler{
  PairTree* tree;
  std::stack<int> iPrevPair;
  std::stack<Node*> nodes;
  std::vector<std::string> lines;
  std::set<int> magnitudes;
public:
  PairHandler(bool);
  void pairH(std::string&);
  void handleInput();
  void analyseLine(std::string&);
  void insertInTree();
  void insertInStack(const std::string &);
  bool contains_number(const std::string &);
  bool contains_pair(const std::string &);
  int displayMagnitude();
  void initArray();
  void insertLines();
  void runSimulation();
  void lineTransform(std::string);
};
