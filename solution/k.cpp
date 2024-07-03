#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct banding {
  bool operator()(const pair<ll, ll> &a, const pair<ll, ll> &b) {
    if (a.first == b.first) {
      return a.second < b.second;
    }
    return a.first > b.first;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  ll n, count, limit, score;
  cin >> n;

  for (int i = 0; i < n; i++) {
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, banding> pq;
    map<ll, ll> countMark;
    map<ll, bool> gone;
    ll totalScore = 0, mark = 0;

    cin >> count;

    for (ll j = 0; j < count; j++) {
      cin >> limit >> score;

      pq.push({limit, score});
    }

    while (!pq.empty()) {

      auto data = pq.top();

      if (!gone[data.first]) {
        totalScore += pq.top().second;
        mark++;
        countMark[data.first]++;
      }

      if (countMark[mark] && !gone[mark]) {
        gone[mark] = true;

        mark -= countMark[mark];

        countMark[mark] = 0;
      }

      pq.pop();
    }

    cout << "Duarr skor maksimumnya " << totalScore << "\n";
  }

  return 0;
}
