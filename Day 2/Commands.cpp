#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class Submarine{
  int depth_;
  int horizontalPos_;
  int aim_;
public:
  Submarine(int depth = 0, int horizontalPos = 0, int aim = 0)
  : depth_(depth), horizontalPos_(horizontalPos), aim_(aim){}

  void up(int value){
    aim_ += value;
  }

  void forward(int value){
    horizontalPos_ += value;
    depth_ += (aim_ * value);
  }

  void executeCommand(string command, int value){
    if(command == "forward")
      forward(value);
    else if (command == "up")
      up(-value);
    else if(command == "down")
      up(value);
  }

  void processCommands(string filename){
    string line;
    ifstream infile(filename);
    while (getline(infile, line))
    {
      istringstream iss(line);
      string command;
      int value;

      if (!(iss >> command >> value)) { break; } // error

      executeCommand(command, value);
    }
  }

  int posVal(){return horizontalPos_ * depth_;}
};

int main(){
  Submarine* submarine = new Submarine();
  submarine->processCommands("input.txt");
  cout << submarine->posVal() << endl;
  return 0;
}
