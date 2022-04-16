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
      cout << "Adding extra edges..." << endl;
      for(int i = 0; i < lRow; i++)
        for(int j = i + lRow; j < lRow*lRow; j += lRow)
          addEdge(j, j-lRow);

      cout << "Finished!" << endl;
    }

    void print(){
      for(int i = 0; i < adjList[4].size(); i++)
        cout << adjList[4][i].first.index << ' ' << adjList[4][i].second << endl;
    }

    void dissect(string line, int offset, int times = 5){
      int time = 0;
      while(time < times){
        for(int i = 0; i < line.length(); i++){
          int charToInt = line[i] + offset + time;
          if(charToInt <= '9')
            addNode(char(charToInt));
          else
            addNode((char)((charToInt - '0') % 10 + 1 + '0'));
        }
        time++;
      }
    }

    void init(){
      const int grid = 5;
      ifstream infile("input.txt");
      string val;
      vector<string> value;
      cout << "Initing..." << endl;

      while(getline(infile, val))
        value.push_back(val);
      for(int i = 0; i < grid; i++)
        for(int j = 0; j < value.size(); j++)
          dissect(value[j], i);
      cout << "Finished!" << endl;

    }

    void runDistanceAlgo(deque<Node>& que, vector<int>& distance){
      set<long long unsigned> visited;

      while(!que.empty()){
        auto comp = [&](Node a, Node b)-> bool {
          return distance[a.index] < distance[b.index];
        };
        cout << que.size() - 1 << " elements left" << endl;
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

      cout << "Dijkstra initing..." << endl;


      if(start >= 0 && start < nodes.size()){
        distance[start] = 0;
        que.push_back(nodes[start]);
      }

      cout << "Calculating..." << endl;
      for(int i = 0; i < nodes.size(); i++){
        if(i != start){
          distance[i] = INT_MAX;
          que.push_back(nodes[i]);
        }
        cout << i + 1 << "out of " << nodes.size() << " calculated" << endl;
      }

      cout << "Running distance algo..." << endl;

      runDistanceAlgo(que, distance);
      cout << "Finished!" << endl;

    }
};


int main(){
  ifstream infile("input.txt");
  string value;
  getline(infile,value);
  Graph* gr = new Graph(value.length() * 5);
  infile.close();

  gr->init();
  gr->addExtraEdges();
  gr->dijkstra(0);

  return 0;
}
