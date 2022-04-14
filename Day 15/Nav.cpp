#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <set>
using namespace std;

struct Node{
  long long unsigned index;
  int cost;
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


    void runDistanceAlgo(deque<Node>& que, vector<int>& distance){
      set<long long unsigned> visited;

      while(!que.empty()){
        auto comp = [&](Node a, Node b)-> bool {
          return distance[a.index] < distance[b.index];
        };
        auto nextEl = min_element(que.begin(), que.end(), comp);
        long long unsigned next = nextEl->index;

        que.erase(nextEl);
        visited.insert(next);

        long long unsigned min = UINT_MAX;
        for(auto& connect: adjList[next]){
          if(visited.find(connect.first.index) == visited.end()) {
            int dist = distance[next] + connect.second;
            if(dist < distance[connect.first.index])
              distance[connect.first.index] = dist;
          }
        }
      }
      cout << distance[lRow*lRow - 1] << endl;
    }


    void dijkstra(int start){
      vector<int> distance(nodes.size());
      deque<Node> que;

      if(start >= 0 && start < nodes.size()){
        distance[start] = 0;
        que.push_back(nodes[start]);
      }

      for(int i = 0; i < nodes.size(); i++){
        if(i != start){
          distance[i] = INT_MAX;
          que.push_back(nodes[i]);
        }
      }

      runDistanceAlgo(que, distance);
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
  gr->dijkstra(0);

  return 0;
}
