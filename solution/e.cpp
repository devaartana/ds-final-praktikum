#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

int findRootVal(vector<int> data, int length, bool flag) {

  if (length <= 1) {
    return data.front();
  }

  vector<int> newData;

  for (int i = 0; i < length - 1; i += 2) {
    if (flag) {
      newData.push_back(max(data[i], data[i + 1]));
    } else {
      newData.push_back(min(data[i], data[i + 1]));
    }
  }

  return findRootVal(newData, length / 2, (flag) ? false : true);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n, temp, start = 0;
  cin >> n;

  temp = n;
  while (temp) {
    start++;
    temp /= 2;
  }

  vector<int> data(n);
  for (int i = 0; i < n; i++) {
    cin >> temp;
    data[i] = temp;
  }

  cout << findRootVal(data, n, !(start & 1));

  return 0;
}
