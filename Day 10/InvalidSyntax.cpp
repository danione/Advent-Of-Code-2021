#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
using namespace std;

long unsigned scores(stack<char>& syntaxChecker){
  string completedString;
  long unsigned score = 0;

  while(syntaxChecker.size() > 0){
    char peek = syntaxChecker.top();
    score *= 5;
    if(peek == '('){
      completedString += ')';
      score += 1;
    }
    else if(peek == '['){
      completedString += ']';
      score += 2;
    }
    else if(peek == '{'){
      completedString += '}';
      score += 3;
    }
    else{
      completedString += '>';
      score += 4;
    }
    syntaxChecker.pop();
  }
  return score;
}

int stackChecker(stack<char>& syntaxChecker, char symbol){
  if(symbol == '{' || symbol == '[' || symbol == '<'
    || symbol == '('){
      syntaxChecker.push(symbol);
      return 0;
    }
  char peek = syntaxChecker.top();

  if(symbol == ')' && peek != '(')
    return 3;

  if(symbol == ']' && peek != '[')
    return 57;

  if(symbol == '}' && peek != '{')
    return 1197;

  if(symbol == '>' && peek != '<')
    return 25137;

  syntaxChecker.pop();
  return 0;

}

void handleInput(){
  string line;
  ifstream infile("input.txt");
  long unsigned sum = 0;
  vector<unsigned long> incompletedLines;
  while(getline(infile, line)){
    stack<char> syntaxChecker;
    for(int i = 0; i < line.length(); i++){
      int returnValue = stackChecker(syntaxChecker, line[i]);
      if(returnValue > 0){
        sum += returnValue;
        break;
      }
      if(i + 1 == line.length()){
        incompletedLines.push_back(scores(syntaxChecker));
      }
    }
  }
  sort(incompletedLines.begin(), incompletedLines.end());
  cout << *(incompletedLines.begin() + incompletedLines.size()/2) << endl;
  // cout << sum << endl;
}

int main(){
  handleInput();
  return 0;
}
