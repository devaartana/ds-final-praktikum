#include <bits/stdc++.h>
using namespace std;

#define data long

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

  void dijkstra(vector<data> &result, data start, data capacity) {
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
          if (temp.first + weight < result[nextVertex] && weight <= capacity) {
            result[nextVertex] = temp.first + weight;
            pq.push(make_pair(result[nextVertex], nextVertex));
          }
        }
      }
    }
  }
};

int main() {

  int n, m, k, e, a, b, p;
  cin >> n >> m >> k >> e;

  graph g;
  g.init(n + 1);

  for (int i = 0; i < m; i++) {
    cin >> a >> b >> p;

    g.add_edge(a, b, p);
  }

  vector<data> result;
  g.dijkstra(result, 1, k);

  data waktu = (result[n] - k) * 3;

  if (waktu > e) {
    cout << "muak gweh, butuh heal lagi";
  } else {
    cout << waktu;
  }

  return 0;
}
