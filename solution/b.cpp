#include <bits/stdc++.h>
#include <iterator>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  list<int> ll;

  int temp, count = 0, target;
  while (true) {

    cin >> temp;

    if (temp == -1)
      break;

    ll.push_back(temp);
    count++;
  }

  cin >> target;

  auto targetAwal = ll.begin(), targetAkhir = ll.begin();

  advance(targetAwal, target - 1);
  advance(targetAkhir, count - target);

  temp = *targetAwal;
  *targetAwal = *targetAkhir;
  *targetAkhir = temp;

  for (auto node : ll) {
    cout << node << " ";
  }

  return 0;
}
