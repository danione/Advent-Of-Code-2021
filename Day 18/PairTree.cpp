#include "PairTree.h"
#include <iostream>
using namespace std;

PairTree::PairTree(){
  root = NULL;
  levels = 0;
}

void PairTree::reduce(){
  while(true){
    if(levels >= 4){
      explode();
    } else{
      break;
    }
  }
}

void PairTree::explode(){
  // Explode
}

void PairTree::append(Node* node, int levels_){
  if(root == NULL){
    root = node;
  } else{
    // Might be a problem
    Node* newPair = new Node((Node){.regular = false, .leftVal = root, .rightVal = node, levels_});
    root = newPair;
  }

  levels = levels_;
  if(levels >= 4){
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
