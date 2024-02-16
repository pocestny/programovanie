#include <algorithm>
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

void print(Node *p) {
  while(p!=nullptr) {
    cout<<p->val<<" ";
    p=p->nxt;
  }
  cout<<endl;
}

Node *sort(int n, Node *head) {
  if (n == 1) return head;
  Node *a = head;
  for (int i = 0; i < n / 2 - 1; i++) a = a->nxt;
  Node *b = a->nxt;
  a->nxt = nullptr;
  a = sort(n / 2, head);
  b = sort(n - n / 2, b);
  if (a->val > b->val) swap(a, b);
  head = a;
  while (b != nullptr) {
    if (a->nxt == nullptr) {
      a->nxt = b;
      return head;
    }
    if (a->nxt->val < b->val)
      a = a->nxt;
    else {
      Node *p = b;
      while (p->nxt != nullptr && p->nxt->val < a->nxt->val) p = p->nxt;
      Node *tmp = p->nxt;
      p->nxt = a->nxt;
      a->nxt = b;
      b = tmp;
    }
  }
  return head;
}

int main() {
  int n;
  cin >> n;
  Node *head = nullptr;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    head = new Node(x, head);
  }
  head = sort(n,head);
  print(head);
}
