struct Node{
  bool regular;
  Node* leftVal;
  Node* rightVal;
  int val;
  int level;
};

class PairTree{
  Node* root;
  int levels;
public:
  PairTree();
  void append(Node*, int);
  void printNode(Node*);
  Node* getRoot();
  void reduce();
};
