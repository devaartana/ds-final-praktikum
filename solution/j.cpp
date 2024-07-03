#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n;
  cin >> n;

  string command, target, temp;
  map<string, stack<string>> mp;

  for (int i = 0; i < n; i++) {
    cin >> command;

    if (command.compare("CREATE") == 0) {
      cin >> temp;
      cin >> target;
    } else if (command.compare("WRITE") == 0) {
      cin >> target >> temp;

      mp[target].push(temp);
    } else if (command.compare("READ") == 0) {
      cin >> temp;
      cin >> target;

      if (mp[target].empty()) {
        cout << "Topic is empty\n";
      } else {
        cout << mp[target].top() << "\n";
        mp[target].pop();
      }
    }
  }

  return 0;
}
