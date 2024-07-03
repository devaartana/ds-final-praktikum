#include <bits/stdc++.h>
using namespace std;

int find_parent(vector<int> &parent, int v) {
  if (v == parent[v])
    return v;
  return parent[v] = find_parent(parent, parent[v]);
}

void union_set(vector<int> &parent, vector<int> &weight, int vertex1, int vertex2) {
  int parent1 = find_parent(parent, vertex1);
  int parent2 = find_parent(parent, vertex2);

  if (parent1 != parent2) {
    parent[parent2] = parent1;
  }
}

int main() {
  int v, e, start;
  cin >> v >> e >> start;

  vector<int> weight(v + 1), parent(v + 1);
  for (int i = 1; i <= v; i++) {
    cin >> weight[i];
    parent[i] = i;
  }

  int v1, v2;
  for (int i = 0; i < e; i++) {
    cin >> v1 >> v2;
    union_set(parent, weight, v1, v2);
  }

  map<int, map<int, int>> data;
  for (int i = 1; i <= v; i++) {
    data[parent[i]][weight[i]]++;
  }

  int n, cmd, target, x;
  long long cost = 0;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> cmd;

    if (cmd == 1) {
      cin >> target >> x;

      if(data[parent[target]][weight[target]] > 1){
        data[parent[target]][weight[target]]--;
      }else{
        data[parent[target]].erase(weight[target]);
      }
      
      weight[target] = x;

      data[parent[target]][x]++;
    } else if (cmd == 2) {
      cin >> target;
      if (parent[target] != parent[start]) {
        cost += data[parent[start]].begin()->first +
                data[parent[target]].begin()->first;
      }
      start = target;
    }
  }

  cout << cost;
  return 0;
}
