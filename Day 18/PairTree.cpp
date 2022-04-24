#include "PairTree.h"
#include <iostream>
#include <cmath>
using namespace std;

PairTree::PairTree(){
  root = NULL;
  levels = 0;
  pathFound = false;
}

PairTree::~PairTree(){
  delete root;
}

Node* findLeftVal(Node * node){
  if(node->regular && node->val > 9)
    return node;
  else if(node->regular)
    return NULL;

  Node* found = findLeftVal(node->leftVal);
  if(found != NULL) return found;
  else return findLeftVal(node->rightVal);

}

void PairTree::split(Node* node){
  cout << "Splitting..." <<endl;
  node->regular = false;
  node->leftVal = new Node((Node){.regular = true, .val = static_cast<int>(floor((double)node->val / 2))});
  node->rightVal = new Node((Node){.regular = true, .val = static_cast<int>(ceil((double)node->val / 2))});
  node->val = 0;
  cout << "Split complete!" << endl;
}

void PairTree::reduce(){
  while(true){
    Node* node = findLeftVal(root);
    if(levels > 4){
      explode();
      levels = getLevels(root);
    } else if(node != NULL){
      split(node);
      levels = getLevels(root);
    } else break;
  }
}

int PairTree::getLevels(Node* node) {
  if (node == NULL)
    return -1;
  else
  {
    int lDepth = getLevels(node->leftVal);
    int rDepth = getLevels(node->rightVal);
    if (lDepth > rDepth)
      return(lDepth + 1);
    else return(rDepth + 1);
  }
}

void PairTree::addThemUp(Node* saught, Node* nearestLeft, Node* nearestRight){
  int lVal = 0;
  int rVal = 0;

  if(nearestLeft){
    nearestLeft->val += saught->leftVal->val;
    lVal = nearestLeft->val;
  }
  if(nearestRight){
    nearestRight->val += saught->rightVal->val;
    rVal += nearestRight->val;
  }
}

void PairTree::leftmost(Node* node, int level){
  if(level == levels && node->regular == false){
    path.push(node);
    pathFound = true;
    return;
  }
  if(node->regular == true) return;

  path.push(node);
  leftmost(node->leftVal, level + 1);
  if(pathFound) return;
  leftmost(node->rightVal, level + 1);
  if(pathFound) return;
  path.pop();
}

Node* PairTree::search(Node* node, bool left){
  while(!node->regular){
    if(left) node = node->rightVal;
    else node = node->leftVal;
  }
  return node;
}

Node* PairTree::nearest(bool left = true){
  Node* iter;
  stack<Node*> pathCopy = path;
  Node* prev = pathCopy.top();

  pathCopy.pop();

  while(!pathCopy.empty()){
    if(left) iter = pathCopy.top()->leftVal;
    else iter = pathCopy.top()->rightVal;

    if(iter == prev){
      prev = pathCopy.top();
      pathCopy.pop();
    } else return search(iter, left);
  }
  return NULL;
}

void PairTree::cleanup(){
  Node* current = path.top();
  path.pop();
  Node* parent = path.top();
  path.pop();

  if(parent->leftVal == current) parent->leftVal = new Node({.regular = true, .val = 0});
  else parent->rightVal = new Node({.regular = true, .val = 0});

  pathFound = false;

  while(!path.empty())
    path.pop();

  delete current;
}

void PairTree::explode(){
  cout << "Exploding..." << endl;
  leftmost(root, 1);
  Node* saught = path.top();
  Node* nearestLeft = nearest(true);
  Node* nearestRight = nearest(false);
  addThemUp(saught, nearestLeft, nearestRight);
  cleanup();
}

void PairTree::append(Node* node){
  if(root == NULL){
    root = node;
  } else{
    // Might be a problem
    Node* newPair = new Node((Node){.regular = false, .leftVal = root, .rightVal = node});
    root = newPair;
  }
  levels = getLevels(root);
  if(levels > 4){
    reduce();
  }
}

void PairTree::printNode(Node* node){
  if(node == NULL)
    return;

  if(node->leftVal != NULL)
    printNode(node->leftVal);

  if(node->regular){
    cout << node->val << ' ';
  }

  if(node->rightVal != NULL)
    printNode(node->rightVal);
}

Node* PairTree::getRoot(){return root;}

long long PairTree::calcMagnitude(Node* node){
  if(node->regular)
    return node->val;
  return 3*calcMagnitude(node->leftVal) + 2*calcMagnitude(node->rightVal);
}
