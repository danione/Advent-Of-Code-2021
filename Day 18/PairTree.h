#include <stack>
struct Node{
  bool regular;
  Node* leftVal;
  Node* rightVal;
  int val;
};

class PairTree{
  Node* root;
  int levels;
  std::stack<Node*> path;
  bool pathFound;
public:
  PairTree();
  void append(Node*);
  void printNode(Node*);
  Node* getRoot();
  void reduce();
  void explode();
  int getLevels(Node*);
  void leftmost(Node*, int);
  void addThemUp(Node*, Node*, Node*);
  Node* nearest(bool);
  Node* search(Node*, bool);
  void cleanup();


};
