#include "PairHandler.h"
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

PairHandler::PairHandler(){
  tree = new PairTree();
  handleInput();
  levels = 0;
}

void PairHandler::handleInput(){
  ifstream infile("input.txt");
  string line;
  while(getline(infile,line)){
    while(line.length() > 0){
      if(contains_pair(line)){
        analyseLine(line);
      } else{
        tree->append(nodes.top(), levels);
        nodes.pop();
        break;
      }
    }
  }
  tree->printNode(tree->getRoot());
  cout << endl;
}

void PairHandler::pairH(string& pair){
  if(contains_number(pair)) insertInStack(pair);
  else if(!contains_number(pair)) insertInTree();
}

void PairHandler::analyseLine(string& line){
  for(int i = 0; i < line.length(); i++){
    if(line[i] == '[')
      iPrevPair.push(i);
    else if(line[i] == ']'){
      string pair = line.substr(iPrevPair.top() + 1, i - 1 - iPrevPair.top());
      pairH(pair);
      line.erase(iPrevPair.top(), i - iPrevPair.top() + 1);
      line.insert(line.begin() + iPrevPair.top(), 'a');
      iPrevPair.pop();
      break;
    }
  }
}

void PairHandler::insertInStack(const string& pair){
  string left = pair.substr(0, pair.find(','));
  string right = pair.substr(pair.find(',') + 1, pair.length());
  try {
    if(left != "a" && right != "a"){
      Node* leftVal = new Node((Node){.regular = true, .val = stoi(left,0,10)});
      Node* rightVal = new Node((Node){.regular = true, .val = stoi(right,0,10)});
      Node* pairNode = new Node((Node){.regular = false, .leftVal = leftVal, .rightVal = rightVal, .level = levels});
      nodes.push(pairNode);
    } else if(right != "a"){
      Node* rightVal = new Node((Node){.regular = true, .val = stoi(right,0,10)});
      Node* pairNode = new Node((Node){.regular = false, .leftVal = nodes.top(), .rightVal = rightVal, .level = levels});
      nodes.push(pairNode);
      levels++;
    } else{
      Node* leftVal = new Node((Node){.regular = true, .val = stoi(right,0,10)});
      Node* pairNode = new Node((Node){.regular = false, .leftVal = leftVal, .rightVal = nodes.top(), .level = levels});
      nodes.push(pairNode);
      levels++;
    }
  } catch (...) { cout << pair << endl;}
}

void PairHandler::insertInTree(){
  Node* rightVal = nodes.top();
  nodes.pop();
  Node* leftVal = nodes.top();
  nodes.pop();
  Node* pairNode = new Node((Node){.regular = false, .leftVal = leftVal, .rightVal = rightVal, .level = levels});
  nodes.push(pairNode);
  levels++;
}

bool PairHandler::contains_number(const string &c){
    return (c.find_first_of("0123456789") != string::npos);
}

bool PairHandler::contains_pair(const string &c){
    return (c.find_first_of(",") != string::npos);
}
