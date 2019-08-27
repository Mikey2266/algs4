#include<iostream>
#include<vector>

using namespace std;

static bool RED = true;
static bool BLACK = false;

/*节点结构体*/
template<class Key, class Value>
struct Node {
    Key key;
    Value val;
    Node<Key, Value>* left;
    Node<Key, Value>* right;
    int N;
    bool color;
    Node(Key x, Value y, int n, bool c):
    key(x), val(y), N(n), left(NULL), right(NULL), color(c) {}
};

template<class Key, class Value>
class RedBlackBST {
private:
    Node<Key, Value>* root;
    bool isRed(Node<Key, Value>* h);
    Node<Key, Value>* rotateLeft(Node<Key, Value>* h);
    Node<Key, Value>* rotateRight(Node<Key, Value>* h);
    void flipColors(Node<Key, Value>* h);
    int size(Node<Key, Value>* h);
    Node<Key, Value>* put(Node<Key, Value>* h, Key key, Value val);
public:
    RedBlackBST();
    ~RedBlackBST();

    int size();
    void put(Key key, Value val);
};

template<class Key, class Value>
RedBlackBST<Key, Value>::RedBlackBST() { root = NULL; };

template<class Key, class Value>
RedBlackBST<Key, Value>::~RedBlackBST() { delete root; }

template<class Key, class Value>
bool RedBlackBST<Key, Value>::isRed(Node<Key, Value>* h) { return h ? h->color == RED : false; }

template<class Key, class Value>
Node<Key, Value>* RedBlackBST<Key, Value>::rotateLeft(Node<Key, Value>* h) {
    Node<Key, Value>* x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = h->color;
    h->color = RED;
    x->N = h->N;
    h->N = 1 + size(h->left) + size(h->right);
    return x;
}

template<class Key, class Value>
Node<Key, Value>* RedBlackBST<Key, Value>::rotateRight(Node<Key, Value>* h) {
    Node<Key, Value>* x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;
    x->N = h->N;
    h->N = 1 + size(h->left) + size(h->right);
    return x;
}

template<class Key, class Value>
void RedBlackBST<Key, Value>::flipColors(Node<Key, Value>* h) {
    h->left->color = BLACK;
    h->right->color = BLACK;
    h->color = RED;
}

template<class Key, class Value>
int RedBlackBST<Key, Value>::size() {
    return size(root);
}

template<class Key, class Value>
int RedBlackBST<Key, Value>::size(Node<Key, Value>* h) {
    return h ? h->N : 0;
}

template<class Key, class Value>
void RedBlackBST<Key, Value>::put(Key key, Value val) {
    root = put(root, key, val);
    root->color = BLACK; // 根节点每次插入最后置为黑
}

template<class Key, class Value>
Node<Key, Value>* RedBlackBST<Key, Value>::put(Node<Key, Value>* h, Key key, Value val) {
    if (!h) return new Node<Key, Value>(key, val, 1, RED);
    if (h->key > key) h->left = put(h->left, key, val);
    else if (h->key < key) h->right = put(h->right, key, val);
    else h->val = val;

    if (isRed(h->right) && !isRed(h->left)) h = rotateLeft(h);
    if (isRed(h->left) && isRed(h->left->left)) h = rotateRight(h);
    if (isRed(h->left) && isRed(h->right)) flipColors(h);

    h->N = size(h->left) + size(h->right) + 1;
    return h;
}

int main() {
    vector<char> vec = {'S', 'E', 'A', 'R', 'C', 'H', 'X', 'M', 'P', 'L'};
    RedBlackBST<char, int> rbb = RedBlackBST<char, int>();
    for (int i = 0; i < vec.size(); ++i)
        rbb.put(vec[i], i);
    cout << rbb.size() << endl;
    return 0;
}