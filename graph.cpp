#include <iostream>

using namespace std;

struct {
  int v; //numbers of vertecies
  vector<vector<int> > adj;
} graph;

void add_edge(vector<vector<int> >& adj, int node1, int node2) {
  adj[node1].push_back(node2);
  adj[node2].push_back(node1);
}

void display_adj_list(const vector<vector<int>>& adj) {
  for (int i = 0; i < adj.size(); i++) {
      cout << i << ": "; // Print the vertex
      for (int j : adj[i]) {
          cout << j << " "; // Print its adjacent
      }
      cout << endl; 
  }
}

void bfs(const vector<vector<int>>& adj, int root) {
  int adj_size = adj.size();
  vector<bool> visited(adj_size, false);
  queue<int> q;

  visited[root] = true;
  q.push(root);

  while (!q.empty()) {
    int node = q.front();
    q.pop();
    cout << node << " ";

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            visited[neighbor] = true;
            q.push(neighbor);
        }
    }
  }
  cout << endl;
}


void dfs(const vector<vector<int>>& adj, int root) {
  int adj_size = adj.size();
  vector<bool> visited(adj_size, false);
  stack<int> s;
  s.push(root);

  while (!s.empty()) {
    int node = s.top();    
    s.pop();
    if (!visited[node]) {
      visited[node] = true;
      cout << node << " ";
    }

    for (int neighbor : adj[node]) {
      if (!visited[neighbor]) {
        s.push(neighbor);
      }
    }
  }
  cout << endl;
}

int main() {
  int v = 6;
  vector<vector<int> > adj(v);

  add_edge(adj, 2, 3);
  add_edge(adj, 2, 5);
  add_edge(adj, 5, 1);
  add_edge(adj, 5, 0);
  add_edge(adj, 3, 4);

  display_adj_list(adj);

  //bfs(adj, 2);
  dfs(adj, 2);

  return 0;
}
