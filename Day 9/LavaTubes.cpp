#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int checkBorderCases(int row, int column, vector<vector<char>>& input){
  bool firstRow, firstColumn, lastRow, lastColumn;
  char value = input[row][column];

  if(row == 0){
    firstRow = true;
  }
  else if(row == input[row].size() - 1){
    lastRow = true;
  }
  if(column == 0){
    firstColumn = true;
  } else if(column == input.size() - 1){
    lastColumn = true;
  }

  if(firstRow)
    if(input[row+1][column] < value)
      return 0;
  if(firstColumn)
    if(input[row][column+1] < value)
      return 0;
  if(lastRow)
    if(input[row - 1][column] < value)
      return 0;
  if(lastColumn)
    if(input[row][column - 1] < value)
      return 0;
}

bool checkIfLowestValue(int row, int column, vector<vector<char>>& input){

  if(row == 0){

  } else if(row == input[row].size() - 1){

  }

  if()
  char value = input[row][column];
  if(input[row+1][column] < value || input[row][column+1] < value
    || input[row-1][column] < value || input[row][column-1] < value)
      return false;
  return true;
}

void printInput(vector<vector<char>>& input){
  for(int row = 0; row < input.size(); row++){
    for(int column = 0; column < input[row].size(); column++)
      cout << input[row][column] << ",";
    cout << endl;
  }
}

void handleInput(vector<vector<char>>& input){
  string values;
  ifstream infile("input.txt");
  int row = 0;
  while(getline(infile, values)){
    input.push_back(vector<char>(values.length()));

    for(int i = 0; i < values.length(); i++)
      input[row][i] = values[i];

    row++;
  }
}

int main(){
  vector<vector<char>> input;
  handleInput(input);
  printInput(input);
  return 0;
}
