#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

struct Node{
  long long unsigned index;
  int cost;
};

struct Edge{
  long long unsigned src, dest, weight;
};

class Graph{
    vector<Node> nodes;
    map<long long unsigned, vector< pair<Node, int> > > adjList;
    long long unsigned index;
    int lRow;

  public:

    Graph(int length){
      index = 0;
      lRow = length;
    }

    void addNode(char weight){
      long long unsigned x = index % lRow;
      long long unsigned y = index / lRow;

      struct Node newNode = {index, weight - '0'};

      nodes.push_back(newNode);

      if(x != 0)
        addEdge(index, index-1);

      index++;
    }

    void addEdge(int start, int prev){
      Node curNode = nodes[start];
      Node lastNode = nodes[prev];

      adjList[start].push_back(pair<Node, int>(lastNode,lastNode.cost));
      adjList[prev].push_back(pair<Node, int>(curNode,curNode.cost));
    }

    void addExtraEdges(){
      for(int i = 0; i < lRow; i++){
        for(int j = i + lRow; j < lRow*lRow; j += lRow){
          addEdge(j, j-lRow);
        }
      }
    }

    void print(){
      for(int i = 0; i < adjList[4].size(); i++)
      {
        cout << adjList[4][i].first.index << ' ' << adjList[4][i].second << endl;
      }

    }

    void init(){
      ifstream infile("input.txt");
      string value;
      while(getline(infile, value)){
        for(int i = 0; i < value.length(); i++)
          addNode(value[i]);
      }
    }

    void dijkstra(int start){
      vector<int> distance(nodes.size());
      queue<Nodes> que;

      if(start >= 0 && start < nodes.size()){
        distance[start] = 0;
        que.push(node[start]);
      }

      for(int i = 0; i < nodes.size(); i++){
        if(i != start){
          distance[i] = INT_MAX;
          que.push(node[i]);
        }
      }

      while(!que.empty()){
        Node next = que.front();
        que.pop();

        vector<Node> connections;
        for(auto connect: adjList[next.index]){
          
        }

      }

    }
};


int main(){
  ifstream infile("input.txt");
  string value;
  getline(infile,value);
  Graph* gr = new Graph(value.length());
  infile.close();

  gr->init();
  gr->addExtraEdges();
  gr->print();
  return 0;
}
