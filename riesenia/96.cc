#include <iostream>
using namespace std;

struct Node {
  int val;
  Node *nxt;

  Node(int _val = -1, Node *_nxt = nullptr) {
    val = _val;
    nxt = _nxt;
  }
};

int main() {
  int n, m;
  cin >> n >> m;
  Node *head = nullptr;
  for (int i = 0; i < n; i++) 
    head = new Node(n - 1 - i, head);
  while (m > 0) {
    m--;
    int x;
    cin >> x;
    Node *p = head, *prev = nullptr;
    while (p->val != x) {
      cout << p->val << " ";
      prev = p;
      p = p->nxt;
    }
    cout<<"nasiel som "<<x<<"!"<<endl;
    if (prev != nullptr) {
      prev->nxt = p->nxt;
      p->nxt = head;
      head = p;
    }
  }
}
