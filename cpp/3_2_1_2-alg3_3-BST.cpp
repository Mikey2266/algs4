/*未实现用foreach顺序迭代访问功能*/
#include<iostream>
#include<queue>

using namespace std;

/*节点结构体*/
template<class Key, class Value>
struct Node {
    Key key;
    Value val;
    Node<Key, Value>* left;
    Node<Key, Value>* right;
    int N;
    Node(Key x, Value y, int n) : key(x), val(y), N(n), left(NULL), right(NULL) {}
};

template<class Key, class Value>
class BST {
private:
    Node<Key, Value>* root;
    int size(Node<Key, Value>* x);
    Value get(Node<Key, Value>* x, Key key);
    Node<Key, Value>* put(Node<Key, Value>* x, Key key, Value val);
    Node<Key, Value>* min(Node<Key, Value>* x);
    Node<Key, Value>* floor(Node<Key, Value>* x, Key key);
    Node<Key, Value>* select(Node<Key, Value>* x, int k);
    int rank(Node<Key, Value>* x, Key key);
    Node<Key, Value>* deleteMin(Node<Key, Value>* x);
    Node<Key, Value>* deleteKey(Node<Key, Value>* x, Key key);
    void keys(Node<Key, Value>* x, queue<Key>& q, Key lo, Key hi);
public:
    BST();
    ~BST();

    int size();
    Value get(Key key);
    void put(Key key, Value val);
    Key min();
    Key floor(Key key);
    Key select(int k);
    int rank(Key key);
    void deleteMin();
    void deleteKey(Key key);
    queue<Key> keys(Key lo, Key hi);
};

template<class Key, class Value>
BST<Key, Value>::BST() {
    root = NULL;
}

template<class Key, class Value>
BST<Key, Value>::~BST() {
    delete root;
}

template<class Key, class Value>
int BST<Key, Value>::size() {
    return size(root);
}

template<class Key, class Value>
int BST<Key, Value>::size(Node<Key, Value>* x) {
    return x ? x->N : 0;
}

template<class Key, class Value>
Value BST<Key, Value>::get(Key key) {
    return get(root, key);
}

template<class Key, class Value>
Value BST<Key, Value>::get(Node<Key, Value>* x, Key key) {
    Value nullVal;
    if (!x) return nullVal;
    if (x->key > key) return get(x->left, key);
    else if (x->key < key) return get(x->right, key);
    else return x->val;
}

template<class Key, class Value>
void BST<Key, Value>::put(Key key, Value val) {
    root = put(root, key, val);
}

template<class Key, class Value>
Node<Key, Value>* BST<Key, Value>::put(Node<Key, Value>* x, Key key, Value val) {
    if (x == NULL) return new Node<Key, Value>(key, val, 1);
    if (x->key > key) x->left = put(x->left, key, val);
    else if (x->key < key) x->right = put(x->right, key, val);
    else x->val = val;
    x->N = size(x->left) + size(x->right) + 1;
    return x;
}

template<class Key, class Value>
Key BST<Key, Value>::min() {
    return min(root)->key;
}

template<class Key, class Value>
Node<Key, Value>* BST<Key, Value>::min(Node<Key, Value>* x) {
    return x->left ? min(x->left) : x;
}

template<class Key, class Value>
Key BST<Key, Value>::floor(Key key) {
    Key nullKey;
    Node<Key, Value>* x = floor(root, key);
    return x ? x->key : nullKey;
}

template<class Key, class Value>
Node<Key, Value>* BST<Key, Value>::floor(Node<Key, Value>* x, Key key) {
    if (!x) return NULL;
    if (x->key > key) return floor(x->left, key);
    if (x->key == key) return x;
    Node<Key, Value>* t = floor(x->right, key);
    return t ? t : x;
}

template<class Key, class Value>
Key BST<Key, Value>::select(int k) {
    return select(root, k)->key;
}

template<class Key, class Value>
Node<Key, Value>* BST<Key, Value>::select(Node<Key, Value>* x, int k) {
    if (!x) return NULL;
    int t = size(x->left);
    if (t > k) return select(x->left, k);
    else if (t < k) return select(x->right, k - t - 1);
    else return x;
}

template<class Key, class Value>
int BST<Key, Value>::rank(Key key) {
    return rank(root, key);
}

template<class Key, class Value>
int BST<Key, Value>::rank(Node<Key, Value>* x, Key key) {
    if (!x) return 0;
    if (x->key > key) return rank(x->left, key);
    else if (x->key < key) return 1 + size(x->left) + rank(x->right, key);
    else return size(x->left);
}

template<class Key, class Value>
void BST<Key, Value>::deleteMin() {
    root = deleteMin(root);
}

template<class Key, class Value>
Node<Key, Value>* BST<Key, Value>::deleteMin(Node<Key, Value>* x) {
    if (!x->left) return x->right;
    x->left = deleteMin(x->left);
    x->N = 1 + size(x->right) + size(x->left);
    return x;
}

template<class Key, class Value>
void BST<Key, Value>::deleteKey(Key key) {
    root = deleteKey(root, key);
}

template<class Key, class Value>
Node<Key, Value>* BST<Key, Value>::deleteKey(Node<Key, Value>* x, Key key) {
    if (!x) return NULL;
    if (x->key > key) x->left = deleteKey(x->left, key);
    else if (x->key < key) x->right = deleteKey(x->right, key);
    else {
        if (!x->right) return x->right;
        if (!x->left) return x->left;
        Node<Key, Value>* t = x;
        x = min(t->right);
        x->left = t->left;
        x->right = deleteMin(t->right);
    }
    x->N = size(x->left) + size(x->right) + 1;
    return x;
}

template<class Key, class Value>
queue<Key> BST<Key, Value>::keys(Key lo, Key hi) {
    queue<Key> q;
    keys(root, q, lo, hi);
    return q;
}

template<class Key, class Value>
void BST<Key, Value>::keys(Node<Key, Value>* x, queue<Key>& q, Key lo, Key hi) {
    if (!x) return;
    if (x->key > lo) keys(x->left, q, lo, hi);
    if (x->key >= lo && x->key <= hi) q.push(x->key);
    if (x->key < hi) keys(x->right, q, lo, hi);
}

int main() {
    vector<char> vec = {'S', 'E', 'A', 'C', 'R', 'H', 'M', 'X'};
    BST<char, int> bst = BST<char, int>();
    for (int i = 0; i < vec.size(); ++i)
        bst.put(vec[i], i);
    cout << bst.size() << endl;
    cout << bst.get('A') << endl;
    cout << bst.min() << endl;
    cout << bst.floor('G') << endl;
    cout << bst.select(3) << endl;
    cout << bst.rank('A') << endl;
    bst.deleteMin();
    cout << bst.size() << endl;
    cout << bst.rank('C') << endl;
    bst.deleteKey('C');
    cout << bst.size() << endl;
    cout << bst.rank('E') << endl;
    queue<char> q = bst.keys('A', 'Z');
    while (q.size()) {
        cout << q.front() << " ";
        q.pop();
    }
    return 0;
}