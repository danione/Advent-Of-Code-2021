#include <stack>
#include "PairTree.h"

class PairHandler{
  PairTree* tree;
  std::stack<int> iPrevPair;
  std::stack<Node*> nodes;
  int levels;
public:
  PairHandler();
  void pairH(std::string&);
  void handleInput();
  void analyseLine(std::string&);
  void insertInTree();
  void insertInStack(const std::string &);
  bool contains_number(const std::string &);
  bool contains_pair(const std::string &);
};
