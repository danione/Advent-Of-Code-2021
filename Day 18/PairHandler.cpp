#include "PairHandler.h"
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

PairHandler::PairHandler(bool part1){
  tree = new PairTree();
  if(part1)
    handleInput();
  else
    insertLines();
}

void PairHandler::runSimulation(){
  for(int f = 0; f < lines.size() - 1; f++){
    for(int n = f + 1; n < lines.size(); n++){
      lineTransform(lines[f]);
      lineTransform(lines[n]);
      magnitudes.insert(displayMagnitude());
      delete tree;
      tree = new PairTree();
      lineTransform(lines[n]);
      lineTransform(lines[f]);
      magnitudes.insert(displayMagnitude());
      delete tree;
      tree = new PairTree();
    }
  }
  cout << *magnitudes.rbegin() << endl;
}

void PairHandler::insertLines(){
  ifstream infile("input.txt");
  string line;
  while(getline(infile,line)){
    lines.push_back(line);
  }
  runSimulation();
}

void PairHandler::lineTransform(string line){
  while(line.length() > 0){
    if(contains_pair(line)){
      analyseLine(line);
    } else{
      tree->append(nodes.top());
      nodes.pop();
      break;
    }
  }
}

void PairHandler::handleInput(){
  ifstream infile("input.txt");
  string line;
  while(getline(infile,line)){
    lineTransform(line);
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
      Node* pairNode = new Node((Node){.regular = false, .leftVal = leftVal, .rightVal = rightVal});
      nodes.push(pairNode);
    } else if(right != "a"){
      Node* rightVal = new Node((Node){.regular = true, .val = stoi(right,0,10)});
      Node* pairNode = new Node((Node){.regular = false, .leftVal = nodes.top(), .rightVal = rightVal});
      nodes.pop();
      nodes.push(pairNode);
    } else{
      Node* leftVal = new Node((Node){.regular = true, .val = stoi(left,0,10)});
      Node* pairNode = new Node((Node){.regular = false, .leftVal = leftVal, .rightVal = nodes.top()});
      nodes.pop();
      nodes.push(pairNode);
    }
  } catch (...) { cout << pair << endl;}
}

void PairHandler::insertInTree(){
  Node* rightVal = nodes.top();
  nodes.pop();
  Node* leftVal = nodes.top();
  nodes.pop();
  Node* pairNode = new Node((Node){.regular = false, .leftVal = leftVal, .rightVal = rightVal});
  nodes.push(pairNode);
}

bool PairHandler::contains_number(const string &c){
    return (c.find_first_of("0123456789") != string::npos);
}

bool PairHandler::contains_pair(const string &c){
    return (c.find_first_of(",") != string::npos);
}

int PairHandler::displayMagnitude(){
  return tree->calcMagnitude(tree->getRoot());
}
