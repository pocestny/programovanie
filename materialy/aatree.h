struct Node {
  int level, key;
  Node *left, *right;

  Node(int k, Node *base) {
    level = 1;
    key = k;
    left = right = base;
  }

  void destroy(Node *base) {
    if (this == base) return;
    left->destroy(base);
    right->destroy(base);
    delete this;
  }

  Node *skew() {
    if (left->level != level) return this;
    Node *res = left, *tmp = left->right;
    left->right = this;
    left = tmp;
    return res;
  }

  Node *split() {
    if (right->right->level != level) return this;
    right->level++;
    Node *res = right;
    right = right->left;
    res->left = this;
    return res;
  }

  Node *insert(int k, Node *base) {
    if (this == base) return new Node(k, base);
    if (k == key) return this;
    if (k < key)
      left = left->insert(k, base);
    else
      right = right->insert(k, base);
    return skew()->split();
  }

  bool find(int k, Node *base) {
    if (this == base) return false;
    if (key == k) return true;
    if (k < key)
      return left->find(k, base);
    else
      return right->find(k, base);
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

    if (res == base && deleted != base && deleted->key == k) {
      deleted->key = key;
      if (right == base) return nullptr;
      key = right->key;
      delete right;
      right = base;
      return this;
    }

    if (left->level < level - 1 || right->level < level - 1) {
      level--;
      if (right->level > level) right->level = level;
      res = skew();
      res->right = res->right->skew();
      res->right->right = res->right->right->skew();
      res = res->split();
      res->right = res->right->split();
      return res;
    }

    return this;
  }

};

struct Tree {
  Node *root;
  Node *base;

  Tree() {
    base = new Node(0, nullptr);
    base->level = 0;
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
};

