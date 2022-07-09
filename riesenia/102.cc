#include <iostream>
#include <set>
#include <vector>
#include <string>

#include <iomanip>
using namespace std;

struct Node {
  int level, key, size;
  Node *left, *right;

  Node(int k, Node *base) {
    level = 1;
    key = k;
    size = 1;
    left = right = base;
  }

  void destroy(Node *base) {
    if (this == base) return;
    left->destroy(base);
    right->destroy(base);
    delete this;
  }

  void update_size(Node *base) {
    if (this==base) size=0;
    else size = left->size + right->size + 1 ;
  }

  Node *skew(Node *base) {
    if (left->level != level) return this;
    Node *res = left, *tmp = left->right;
    left->right = this;
    left = tmp;
    update_size(base);
    res->update_size(base);
    return res;
  }

  Node *split(Node *base) {
    if (right->right->level != level) return this;
    right->level++;
    Node *res = right;
    right = right->left;
    res->left = this;
    update_size(base);
    res->update_size(base);
    return res;
  }

  Node *insert(int k, Node *base) {
    if (this == base) return new Node(k, base);
    if (k == key) return this;
    if (k < key)
      left = left->insert(k, base);
    else
      right = right->insert(k, base);
    update_size(base);
    return skew(base)->split(base);
  }

  bool find(int k, Node *base) {
    if (this == base) return false;
    if (key == k) return true;
    if (k < key)
      return left->find(k, base);
    else
      return right->find(k, base);
  }
  
  // kolko je mensich
  int rank(int k, Node *base) {
    if (this == base) return 0;
    if (key == k) return left->rank(k,base);
    if (k < key)
      return left->rank(k, base);
    else
      return 1+left->size+right->rank(k, base);
  }


  Node *erase(int k, Node *base, Node *deleted) {
    Node *res;
    if (this == base) return this;

    if (k < key) {
      res = left->erase(k, base, deleted);
      if (res == nullptr) {
        delete left;
        left = base;
      } else
        left = res;
    } else {
      deleted = this;
      res = right->erase(k, base, deleted);
      if (res == nullptr) {
        delete right;
        right = base;
      } else
        right = res;
    }

    update_size(base);

    if (res == base && deleted != base && deleted->key == k) {
      deleted->key = key;
      if (right == base) return nullptr;
      key = right->key;
      delete right;
      right = base;
      update_size(base);
      return this;
    }

    if (left->level < level - 1 || right->level < level - 1) {
      level--;
      if (right->level > level) right->level = level;
      res = skew(base);
      res->right = res->right->skew(base);
      res->right->right = res->right->right->skew(base);
      res = res->split(base);
      res->right = res->right->split(base);
      return res;
    }

    update_size(base);
    return this;
  }

  void dump(int ods, Node *base) {
    if (this == base) return;
    cout << setw(ods) << " "
         << "[key=" << key << " ,level=" << level << " ,size="<<size<<"]\n";
    cout << setw(ods) << " "
         << "left:\n";
    left->dump(ods + 5, base);
    cout << setw(ods) << " "
         << "right:\n";
    right->dump(ods + 5, base);
    cout << setw(ods) << " "
         << "end:\n";
  }
};

struct Tree {
  Node *root;
  Node *base;

  Tree() {
    base = new Node(0, nullptr);
    base->level = 0;
    base->size = 0;
    base->left = base->right = base;
    root = base;
  }

  ~Tree() {
    root->destroy(base);
    delete base;
  }

  void insert(int key) { root = root->insert(key, base); }
  bool find(int key) { return root->find(key, base); }
  void erase(int key) {
    root = root->erase(key, base, base);
    if (!root) root = base;
  }
  int rank(int key) {return root->rank(key,base);}
  void dump() { root->dump(0, base); }
};

int main() { 
  Tree t; 
  string s;
  int x;

  while(true) {
    cin>>s;
    if (s[0]=='!') break;
    else if (s[0]=='d')  t.dump();
    cin>>x;

    if (s[0]=='p') t.insert(x);
    else if (s[0]=='u') t.erase(x);
    else  cout<<t.rank(x)<<endl;
  }

}
