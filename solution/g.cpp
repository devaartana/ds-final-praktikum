#include <bits/stdc++.h>
using namespace std;

#define data long
#define tempz pari<pair<data, data>, data>

struct graph {
  long vertexCount, edgeCount;
  vector<vector<pair<data, data>>> adjList;

  void init(data v) {
    vertexCount = v;
    edgeCount = 0;

    for (int i = 0; i < vertexCount; i++) {
      adjList.push_back({}); // inserts V ammount of empty vector
    }
  }

  void add_edge(data vertex1, data vertex2, data weight) {
    adjList[vertex1].push_back(make_pair(vertex2, weight));
    adjList[vertex2].push_back(make_pair(vertex1, weight));
    edgeCount++;
  }

  void dfs(vector<data> &result, data start) {
    vector<bool> visited(vertexCount, false);
    stack<data> st;

    st.push(start);
    visited[start] = true;
    result.push_back(start);

    while (!st.empty()) {
      data temp = st.top();
      st.pop();

      if (!visited[temp]) {
        result.push_back(temp);
        visited[temp] = true;
      }

      for (auto vertex : adjList[temp]) {
        if (!visited[vertex.first])
          st.push(vertex.first);
      }
    }
  }

  void bfs(vector<data> &result, data start) {
    vector<bool> visited(vertexCount, false);
    queue<data> q;

    q.push(start);
    visited[start] = true;
    result.push_back(start);

    while (!q.empty()) {
      data temp = q.front();
      q.pop();

      for (auto vertex : adjList[temp]) {
        if (!visited[vertex.first]) {
          q.push(vertex.first);
          visited[vertex.first] = true;
          result.push_back(vertex.first);
        }
      }
    }
  }

  void dijkstra(vector<data> &result, data start) {
    vector<bool> visited(vertexCount, false);

    priority_queue<pair<data, data>, vector<pair<data, data>>,
                   greater<pair<data, data>>>
        pq;

    result = vector<long>(vertexCount, LONG_MAX);

    pq.push(make_pair(0, start));
    result[start] = 0;

    while (!pq.empty()) {
      auto temp = pq.top();
      pq.pop();

      visited[temp.second] = true;

      for (auto vertex : adjList[temp.second]) {
        long nextVertex = vertex.first;
        long weight = vertex.second;

        if (!visited[nextVertex]) {
          if (temp.first + weight < result[nextVertex]) {
            result[nextVertex] = temp.first + weight;
            pq.push(make_pair(result[nextVertex], nextVertex));
          }
        }
      }
    }
  }
};

int main() {

  int v, e, t, v1, v2;
  cin >> v >> e >> t;

  graph g;
  g.init(v);

  for (int i = 0; i < e; i++) {
    cin >> v1 >> v2;
    g.add_edge(v1, v2, 1);
  }

  for (int i = 0; i < t; i++) {
    cin >> v1 >> v2;

    vector<long> result;

    g.dijkstra(result, v1);

    cout << result[v2] << "\n";
  }
  return 0;
}
