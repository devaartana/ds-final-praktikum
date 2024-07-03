#include <bits/stdc++.h>
using namespace std;

struct graph {
  long vertexCount, edgeCount;
  map<string, vector<string>> adjList;

  void init(long v) {
    vertexCount = v;
    edgeCount = 0;
  }

  void add_edge(string vertex1, string vertex2) {
    adjList[vertex1].push_back(vertex2);
    adjList[vertex2].push_back(vertex1);
    edgeCount++;
  }

  int dfs(map<string, bool> &visited, string start) {
    stack<string> st;
    int count = 1;

    st.push(start);
    visited[start] = true;

    while (!st.empty()) {
      string temp = st.top();
      st.pop();

      for (auto vertex : adjList[temp]) {
        if (!visited[vertex]) {
          count++;
          st.push(vertex);
          visited[vertex] = true;
        }
      }
    }

    return count;
  }
};

int main() {

  int n, v, e;
  string v1, v2;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> v >> e;

    graph g;
    g.init(v);

    map<string, bool> visited;

    for (int j = 0; j < e; j++) {
      cin >> v1 >> v2;
      visited[v1] = false;
      visited[v2] = false;

      g.add_edge(v1, v2);
    }

    if (g.dfs(visited, v1) < v) {
      cout << "Menyirkel\n";
    } else {
      cout << "Tidak Menyirkel\n";
    }
  }
  return 0;
}
