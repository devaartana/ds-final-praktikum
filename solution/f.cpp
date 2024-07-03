#include <bits/stdc++.h>
using namespace std;

typedef struct data {
  pair<int, int> koor;
  int jarak;
} Data;

struct graph {
  int vertexCount, edgeCount, m, n;
  pair<int, int> F, A, N, C;
  vector<vector<char>> adjMatrix;

  void init(int i, int j) {
    m = i;
    n = j;
    adjMatrix = vector<vector<char>>(m, vector<char>(n, '.'));
  }

  bool isTrue(int x, int y, bool block, vector<vector<bool>> &visited) {
    return (x >= 0 && x < m && y >= 0 && y < n &&
            (adjMatrix[x][y] != '#' || !block) && !visited[x][y]);
  }

  vector<int> bfs(pair<int, int> start, int step, bool block) {
    vector<int> result(4, -1);
    vector<vector<bool>> visited(m, vector<bool>(n, false));

    queue<Data> q;

    q.push({start, 0});
    visited[start.first][start.second] = true;

    int row[4] = {0, 0, 1, -1}, col[4] = {1, -1, 0, 0}, found = 0;
    while (!q.empty()) {
      auto posisi = q.front();
      q.pop();

      if (posisi.koor == F && result[0] == -1) {
        result[0] = posisi.jarak;
        found++;
      }

      if (posisi.koor == A && result[1] == -1) {
        result[1] = posisi.jarak;
        found++;
      }

      if (posisi.koor == N && result[2] == -1) {
        result[2] = posisi.jarak;
        found++;
      }

      if (posisi.koor == C && result[3] == -1) {
        result[3] = posisi.jarak;
        found++;
      }

      for (int i = 0; i < 4; i++) {
        int newRow = posisi.koor.first + row[i],
            newCol = posisi.koor.second + col[i];

        if (isTrue(newRow, newCol, block, visited)) {
          q.push({{newRow, newCol}, posisi.jarak + step});
          visited[newRow][newCol] = true;
        }
      }

      if (found >= 4)
        break;
    }

    return result;
  }
};

int main() {

  int m, n;
  cin >> m >> n;

  graph g;
  g.init(m, n);

  char temp;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cin >> temp;

      g.adjMatrix[i][j] = temp;

      switch (temp) {
      case 'F':
        g.F = {i, j};
        break;
      case 'A':
        g.A = {i, j};
        break;
      case 'N':
        g.N = {i, j};
        break;
      case 'C':
        g.C = {i, j};
        break;
      default:
        break;
      }
    }
  }
  // vector result -> 0: F, 1: A, 2: N, 3: C;

  // furina berjalan ke semua tempat
  vector<int> bfs1 = g.bfs(g.F, 2, true);

  // Navia berjalan ke semua tempat
  vector<int> bfs2 = g.bfs(g.N, 2, false);

  // Clorinde berjalan ke semua tempat
  vector<int> bfs3 = g.bfs(g.C, 1, true);

  // lewat Clorinde dulu baru ke Navia
  vector<int> bfs4 = g.bfs(g.N, 1, false);

  // lewat Navia dulu baru ke Clorinde
  vector<int> bfs5 = g.bfs(g.C, 1, false);

  // F -> A
  int result = bfs1[1];
  int route = 1;

  // F -> C -> A
  if (bfs1[3] + bfs3[1] < result) {
    result = bfs1[3] + bfs3[1];
    route = 2;
  }

  // F -> N -> A
  if (bfs1[2] + bfs2[1] < result) {
    result = bfs1[2] + bfs2[1];
    route = 3;
  }

  // F-> C -> N -> A
  if (bfs1[3] + bfs3[2] + bfs4[1] < result) {
    result = bfs1[3] + bfs3[2] + bfs4[1];
    route = 4;
  }

  // F -> N -> C -> A
  if (bfs1[2] + bfs2[3] + bfs5[1] < result) {
    result = bfs1[2] + bfs2[3] + bfs5[1];
    route = 5;
  }

  switch (route) {
  case 2:
    cout << "Clorinde: Hunt them down!\n";
    break;
  case 3:
    cout << "Navia: Fire!!! ...Well, with rocks.\n";
    break;
  case 4:
    cout << "Clorinde: Hunt them down!\n"
         << "Navia: Fire!!! ...Well, with rocks.\n";
    break;
  case 5:
    cout << "Navia: Fire!!! ...Well, with rocks.\n"
         << "Clorinde: Hunt them down!\n";
    break;
  default:
    break;
  }

  cout << "Furina: With " << result << " steps, let my name echo in song!";

  return 0;
}
