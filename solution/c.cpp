#include <bits/stdc++.h>
#include <functional>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n, temp;
  cin >> n;

  vector<int> ganjil, genap;

  for (int i = 0; i < n; i++) {
    cin >> temp;

    if (temp & 1) {
      ganjil.push_back(temp);
    } else {
      genap.push_back(temp);
    }
  }

  sort(ganjil.begin(), ganjil.end(), greater<int>());
  sort(genap.begin(), genap.end());

  cout << "Angka Genap:\n";
  for (int angka : genap) {
    cout << angka << " ";
  }

  cout << "\nAngka Ganjil:\n";
  for (int angka : ganjil) {
    cout << angka << " ";
  }

  return 0;
}
