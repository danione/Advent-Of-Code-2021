#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>

using namespace std;


class BingoBoard{
private:
	int moves;
	string grid[5][5];
  bool hasBingo;
  string lastVal;

  bool checkForBingo(int row, int column){
		bool rowHasBingo = true;
    bool columnHasBingo = true;

		for(int i = 0; i < 5; i++){
			if(grid[row][i].compare("X") != 0)
				rowHasBingo = false;
      if(grid[i][column].compare("X") != 0)
        columnHasBingo = false;

      if(!rowHasBingo && !columnHasBingo)
        return false;
		}
    if(rowHasBingo || columnHasBingo)
      return true;
    else
      return false;
	}

	public:

	BingoBoard(){
		moves=0;
    hasBingo = false;
	}

	void insert(int row, int column, string value){
		if(row >= 5 || row < 0 || column >= 5 || column < 0){
			return;
		}
		grid[row][column] = value;
	}

	bool bingoCheck(string value){
    if(hasBingo){return true;}
    moves++;
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 5; j++){
				if(grid[i][j] == value){
					grid[i][j] = "X";
          lastVal = value;
          hasBingo = checkForBingo(i, j);
					return hasBingo;
				}
			}
		}
		return hasBingo;
	}

	int checkMoves(){
		return moves;
	}

  string getLastCalledVal(){
    return lastVal;
  }

  void printBoard(){
    for(int i = 0; i < 5; i++){
      for(int j = 0; j < 5; j++){
        cout << grid[i][j] << ' ';
      }
      cout << endl;
    }
  }

  int getSum(){
    int sum = 0;

    for(int i = 0; i < 5; i++){
      for(int j = 0; j < 5; j++){
        if(grid[i][j].compare("X") != 0)
          sum += stoi(grid[i][j]);
      }
    }
    return sum;
  }
};

string populateBoards(vector<BingoBoard*>& boards){
  int row = 0;
  string value;
  string inputArray;
  ifstream ifFile("input.txt");
	getline(ifFile, inputArray);

	while(getline(ifFile, value)){
		if(value.length() == 0){
			boards.push_back(new BingoBoard());
			row = 0;
		}
		else {
			int i = 0;
			int column = 0;
			string splitVal;
      stringstream ss(value);
			while(getline(ss, splitVal, ' ')){
        if(splitVal != "\n" && splitVal.length() != 0){
          boards.back()->insert(row, column, splitVal);
          column++;
        }
			}
      row++;
		}
	}
  return inputArray;
}

class myComparator
{
public:
    int operator() (const pair<int,int>& val1, const pair<int,int>& val2)
    {
        return val1.first < val2.first;
    }
};

int getMaxMoves(vector<BingoBoard*>& boards, vector<string>& inputArray){
  priority_queue<pair<int,int>, vector<pair<int,int>>, myComparator> movesContainer;

  for(int i = 0; i < boards.size(); i++){
    for(int j = 0; j < inputArray.size(); j++){
      if(boards[i]->bingoCheck(inputArray[j])){
        movesContainer.push(pair<int,int>(boards[i]->checkMoves(),i));
        break;
      }
    }
  }
  // int counter = 0;
  // while(!movesContainer.empty()){
  //   cout << movesContainer.top().first << " " << movesContainer.top().second << endl;
  //   movesContainer.pop();
  //   counter++;
  // }
  return movesContainer.top().second;
}

int main(){

	vector<BingoBoard*> boards;
  vector<string> inputVals;
  string val;

  stringstream ss(populateBoards(boards));

  while(getline(ss, val, ',')){
    if(val != "\n" && val.length() != 0){
      inputVals.push_back(val);
    }
  }
  int boardIndex = getMaxMoves(boards, inputVals);
  boards[boardIndex]->printBoard();

  cout << boards[boardIndex]->getSum() << " " << stoi(boards[boardIndex]->getLastCalledVal())<< endl;

  cout << boards[boardIndex]->getSum() * stoi(boards[boardIndex]->getLastCalledVal()) << endl;

  return 0;
}
