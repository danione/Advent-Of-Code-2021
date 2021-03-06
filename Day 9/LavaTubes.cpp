#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
using namespace std;

bool checkIfLowestValue(int row, int column, vector<vector<char>>& input){

  bool firstRow = false, firstColumn = false, lastRow = false, lastColumn = false;
  bool equals = false;
  char value = input[row][column];

  if(row == 0){
    firstRow = true;
  }
  else if(row == input.size() - 1){
    lastRow = true;
  }
  if(column == 0){
    firstColumn = true;
  } else if(column == input[row].size() - 1){
    lastColumn = true;
  }

  if(firstRow){
    if(input[row+1][column] < value)
      return 0;
    else if (input[row+1][column] == value)
      equals = true;
  } else if(lastRow){
    if(input[row - 1][column] < value)
      return 0;
    else if (input[row - 1][column] == value)
      equals = true;
  } else{
    if(input[row+1][column] < value || input[row-1][column] < value)
      return 0;
    else if (input[row+1][column] == value || input[row-1][column] == value)
      equals = true;
  }

  if(firstColumn){
    if(input[row][column + 1] < value)
      return 0;
  } else if(lastColumn){
    if(input[row][column - 1] < value)
      return 0;
  } else{
    if(input[row][column + 1] < value || input[row][column - 1] < value)
      return 0;
  }
  if(equals)
    return 0;
  else
    return 1;
}

void checkVectorInput(vector<vector<char>>& input,unordered_set<string>& source){
  int sum = 0;
  for(int row = 0; row < input.size(); row++){
    for(int column = 0; column < input[row].size(); column++){
      if(checkIfLowestValue(row, column, input) == 1){
        //sum += (input[row][column] - '0') + 1;
        source.insert(to_string(row) + ',' + to_string(column));
      }
    }
  }
  // cout << sum << endl;
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

void basin(int row, int column,vector<vector<char>>& input, unordered_set<string>& source){
  string key = to_string(row) + ',' + to_string(column);
  if(input[row][column] == '9' || source.find(key) != source.end())
    return;

  source.insert(key);

  if(row + 1 <= input.size() - 1)
    basin(row + 1,column, input, source);
  if(row - 1 >= 0)
    basin(row - 1,column, input, source);
  if(column + 1 <= input[row].size() - 1)
    basin(row, column+ 1, input, source);
  if(column - 1 >= 0)
    basin(row, column- 1, input, source);

}

int main(){
  vector<vector<char>> input;
  unordered_set<string> source;
  vector<int> sizes;
  handleInput(input);
  checkVectorInput(input, source);
  for (const auto& elem: source) {
    unordered_set<string> basinHold;

    basin(stoi(elem.substr(0,elem.find(','))),stoi(elem.substr(elem.find(',')+1,elem.length())),input, basinHold);
    sizes.push_back(basinHold.size());
  }
  sort(sizes.begin(), sizes.end());
  int sum = sizes[sizes.size() - 1];
  cout << sum<< endl;
  for(int i = sizes.size() - 2; i > sizes.size() - 4; i--){
    sum*=sizes[i];
  }
  cout << sum << endl;
  return 0;
}
