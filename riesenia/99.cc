#include <iostream>

#include "aatree.h"
using namespace std;

void print_node(Node *n, Node *base) {
  if (n == base) return;
  print_node(n->left, base);
  cout << n->key << " ";
  print_node(n->right, base);
}

void print(Tree &t) {
  print_node(t.root, t.base);
  cout << endl;
}

int main() {
  Tree t;
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    t.insert(x);
  }
  print(t);
}
