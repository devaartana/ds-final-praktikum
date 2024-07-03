#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  string data;
  cin >> data;

  int size = data.size();
  stack<char> st;
  for (int i = 0; i < size; i++) {
    if (st.empty()) {
      st.push(data[i]);
    } else if (st.top() == '<' && data[i] == '>' ||
               st.top() == '(' && data[i] == ')' ||
               st.top() == '[' && data[i] == ']' ||
               st.top() == '{' && data[i] == '}') {
      st.pop();
    } else {
      st.push(data[i]);
    }
  }

  if (st.empty()) {
    cout << "Sudah ditutup";
  } else {
    cout << "Belum ditutup";
  }

  return 0;
}
