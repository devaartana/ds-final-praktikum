// ========[AVL Tree]======== //
/*
    Dibuat dan ditulis oleh ABDUR ROCHMAN
    C++ conversion oleh BAYU LAKSANA
    28-03-2020
    Struktur Data 2020
    For C++
*/
#include <bits/stdc++.h>
#include <cstdio>
#include <queue>
using namespace std;

struct AVLNode {
  int data, powerMonster;
  AVLNode *left, *right;
  int height;
};

struct AVL {
private:
  AVLNode *_root;
  unsigned _size;

  AVLNode *_avl_createNode(int value, int power) {
    AVLNode *newNode = (AVLNode *)malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->powerMonster = power;
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
  }

  AVLNode *_search(AVLNode *root, int value) {
    while (root != NULL) {
      if (value < root->data)
        root = root->left;
      else if (value > root->data)
        root = root->right;
      else
        return root;
    }
    return root;
  }

  int _getHeight(AVLNode *node) {
    if (node == NULL)
      return 0;
    return node->height;
  }

  int _max(int a, int b) { return (a > b) ? a : b; }

  AVLNode *_rightRotate(AVLNode *pivotNode) {
    AVLNode *newParrent = pivotNode->left;
    pivotNode->left = newParrent->right;
    newParrent->right = pivotNode;

    pivotNode->height =
        _max(_getHeight(pivotNode->left), _getHeight(pivotNode->right)) + 1;
    newParrent->height =
        _max(_getHeight(newParrent->left), _getHeight(newParrent->right)) + 1;

    return newParrent;
  }

  AVLNode *_leftRotate(AVLNode *pivotNode) {
    AVLNode *newParrent = pivotNode->right;
    pivotNode->right = newParrent->left;
    newParrent->left = pivotNode;

    pivotNode->height =
        _max(_getHeight(pivotNode->left), _getHeight(pivotNode->right)) + 1;
    newParrent->height =
        _max(_getHeight(newParrent->left), _getHeight(newParrent->right)) + 1;

    return newParrent;
  }

  AVLNode *_leftCaseRotate(AVLNode *node) { return _rightRotate(node); }

  AVLNode *_rightCaseRotate(AVLNode *node) { return _leftRotate(node); }

  AVLNode *_leftRightCaseRotate(AVLNode *node) {
    node->left = _leftRotate(node->left);
    return _rightRotate(node);
  }

  AVLNode *_rightLeftCaseRotate(AVLNode *node) {
    node->right = _rightRotate(node->right);
    return _leftRotate(node);
  }

  int _getBalanceFactor(AVLNode *node) {
    if (node == NULL)
      return 0;
    return _getHeight(node->left) - _getHeight(node->right);
  }

  AVLNode *_insert_AVL(AVLNode *node, int value, int power) {

    if (node == NULL)
      return _avl_createNode(value, power);
    if (value < node->data)
      node->left = _insert_AVL(node->left, value, power);
    else if (value > node->data)
      node->right = _insert_AVL(node->right, value, power);

    node->height = 1 + _max(_getHeight(node->left), _getHeight(node->right));

    int balanceFactor = _getBalanceFactor(node);

    if (balanceFactor > 1 && value < node->left->data)
      return _leftCaseRotate(node);
    if (balanceFactor > 1 && value > node->left->data)
      return _leftRightCaseRotate(node);
    if (balanceFactor < -1 && value > node->right->data)
      return _rightCaseRotate(node);
    if (balanceFactor < -1 && value < node->right->data)
      return _rightLeftCaseRotate(node);

    return node;
  }

  AVLNode *_findMinNode(AVLNode *node) {
    AVLNode *currNode = node;
    while (currNode && currNode->left != NULL)
      currNode = currNode->left;
    return currNode;
  }


public:
  map<int, vector<pair<int, int>>> stageData;
  int highestStage = 0;

  void init() {
    _root = NULL;
    _size = 0U;
  }

  bool isEmpty() { return _root == NULL; }

  bool find(int value) {
    AVLNode *temp = _search(_root, value);
    if (temp == NULL)
      return false;

    if (temp->data == value)
      return true;
    else
      return false;
  }

  void insert(int value, int power) {
    if (!find(value)) {
      _root = _insert_AVL(_root, value, power);
      _size++;
    }
  }

  void levelOrderTraversal() {

    if (!_root)
      return;

    AVLNode *node;
    int level;
    queue<pair<AVLNode *, int>> q;
    q.push({_root, 0});

    while (!q.empty()) {

      node = q.front().first;
      level = q.front().second;

      if (node->height > highestStage)
        highestStage = node->height;

      q.pop();

      stageData[level].push_back({node->data, node->powerMonster});

      if (node->left)
        q.push({node->left, level + 1});
      if (node->right)
        q.push({node->right, level + 1});
    }

  }

};

int main(void) {

  string nameT, nameE, nameR;
  int n, power;

  cin >> nameT >> n >> nameE >> power >> nameR;

  AVL set;
  set.init();

  int kode, powerMonster;
  for (int i = 0; i < n; i++) {
    cin >> kode >> powerMonster;

    set.insert(kode, powerMonster);
  }

  set.levelOrderTraversal();

  cout << "********************************************************************"
          "*********\n";
  cout << "Honkai Star Rail Region " << nameR << "\n\n";

  cout << "Trailblazer : " << nameT << "\n";
  cout << "Element : " << nameE << " - " << power << "\n";

  cout << "--------------------------------------------------------------------"
          "--------\n";

  int sum, stageKalah;
  bool flagKalah = false;

  for (int stage = set.highestStage - 1; stage > 0; stage--) {

    auto vec = set.stageData[stage];

    printf("Stage %d:\n", set.highestStage - stage);

    sum = 0;
    for (int i = 0; i < vec.size(); i++) {
      sum += vec[i].second;
      printf("Monster %c%d_%d_%d: %d\n", (char)(i + 'A'), vec[i].first,
             set.highestStage - stage, i + 1, vec[i].second);
    }

    power = ((power & 1) ? power * 115 / 100 : power * 108 / 100) - sum;

    if (power < 0 && !flagKalah) {
      stageKalah = set.highestStage - stage;
      flagKalah = true;
    }

    cout << endl;
  }

  cout << "Final Stage:\n"
       << "Final Boss " << nameR << "_" << set.stageData[0][0].first << ": "
       << set.stageData[0][0].second << "\n";

  power = ((power & 1) ? power * 115 / 100 : power * 108 / 100) -
          set.stageData[0][0].second;

  cout << "\nResult:\n";
  if (power < 0 && flagKalah) {
    cout << nameT << "  kalah dan mati di Region " << nameR << " pada Stage "
         << stageKalah << "\n";
  } else if (power < 0) {
    cout << nameT << " kalah dan mati di Region " << nameR
         << " pada Final Stage\n";
  } else {
    cout << nameT
         << " menang melawan Final Boss dan memenangkan game di Honkai Star "
            "Rail Region "
         << nameR << "\n";
  }

  cout << "********************************************************************"
          "*********";
  return 0;
}
