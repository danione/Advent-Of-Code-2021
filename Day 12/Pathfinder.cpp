#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

class Pathfinder{
  string start;
  string finish;
  unordered_map<string, vector<string>> vertex;
  vector<string> paths;
public:
  Pathfinder(): start("start"), finish("end"){
    ifstream infile("input.txt");
    string line;
    while(getline(infile, line)){
      string leftVal = line.substr(0, line.find('-'));
      string rightVal = line.substr(line.find('-') + 1, line.length());

      if(vertex[leftVal].empty())
        vertex[leftVal] = vector<string>();
      if(vertex[rightVal].empty())
        vertex[rightVal] = vector<string>();

      vertex[leftVal].push_back(rightVal);
      vertex[rightVal].push_back(leftVal);
    }
  }

  void printConnections(){
    for (auto const &pair: vertex) {
        cout << pair.first << ": ";
        for(string const &str: pair.second)
          cout << str << ", ";
        cout << endl;
    }
  }

  void mapIt(){
    unordered_map<string, bool> visited;

    for(auto const &pair: vertex)
        visited[pair.first] = false;

    traverse(start, visited, string());
  }

  void traverse(string val, unordered_map<string, bool>& visited, string path){

    if(islower(val[0]))
      visited[val] = true;

    if(val == finish){
      paths.push_back(path + ' ' + val);
    } else{
      for(auto const &vert: vertex[val]){
        if(!visited[vert])
          traverse(vert, visited, path + ' ' + val);
      }
    }

    visited[val] = false;
  }

  void printPaths(){
    remove_duplicates();
    for(auto const &vert: paths){
      cout << vert << endl;
    }
    cout << paths.size() << endl;
  }

  void remove_duplicates()
  {
    sort(paths.begin(), paths.end());
    paths.erase(unique(paths.begin(), paths.end()), paths.end());
  }
};

int main(){
  Pathfinder* scanner = new Pathfinder();
  // scanner->printConnections();
  scanner->mapIt();
  scanner->printPaths();
  return 0;
}
