#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  long long n;
  cin >> n;

  long long sum = 1;

  for (long long i = 1; i <= n; i++) {
    sum *= i;
    sum %= 1000000007;
  }

  cout << sum;
  return 0;
}
