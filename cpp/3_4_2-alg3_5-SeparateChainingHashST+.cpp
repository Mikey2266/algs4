#include<iostream>
#include<vector>

using namespace std;

/*节点结构体*/
template<class Key, class Value>
struct Node {
    Key key;
    Value val;
    Node<Key, Value>* next;
    Node(Key x, Value y, Node<Key, Value>* n) : key(x), val(y), next(n) {}
};

// alg3_1 顺序查找
template<class Key, class Value>
class SequentialSearchST {
private:
    Node<Key, Value>* first;
    int N;
public:
    SequentialSearchST();
    ~SequentialSearchST();

    int size();
    void show();
    Value get(Key key);
    void put(Key key, Value val);
};

template<class Key, class Value>
SequentialSearchST<Key, Value>::SequentialSearchST() {
    N = 0;
    first = NULL;
}

template<class Key, class Value>
SequentialSearchST<Key, Value>::~SequentialSearchST() {
    delete first;
}

template<class Key, class Value>
int SequentialSearchST<Key, Value>::size() {
    return N;
}

template<class Key, class Value>
void SequentialSearchST<Key, Value>::show() {
    for (Node<Key, Value>* x = first; x != NULL; x = x->next) {
        cout << x->key << " " << x->val << endl;
    }
}

template<class Key, class Value>
Value SequentialSearchST<Key, Value>::get(Key key) {
    for (Node<Key, Value>* x = first; x != NULL; x = x->next) {
        if (key == x->key) {
            return x->val;
        }
    }
    return ;
}

template<class Key, class Value>
void SequentialSearchST<Key, Value>::put(Key key, Value val) {
    for (Node<Key, Value>* x = first; x != NULL; x = x->next) {
        if (key == x->key) {
            x->val = val;
            return;
        }
    }
    first = new Node<Key, Value>(key, val, first);
    N++;
}

// 基于拉链法的散列表, 只写了初始化，因为JAVA的hashCode()函数要求对常见数据结构都能返回32位整数
template<class Key, class Value>
class SeparateChainingHashST {
private:
    int N;
    int M;
    vector<SequentialSearchST<Key, Value>> st;
public:
    SeparateChainingHashST(int num);
    ~SeparateChainingHashST();
};

template<class Key, class Value>
SeparateChainingHashST<Key, Value>::SeparateChainingHashST(int num) {
    this->M = num;
    for (int i = 0; i < num; ++i) {
        SequentialSearchST<string, int> temp = SequentialSearchST<string, int>();
        this->st.push_back(temp);
    }
}

template<class Key, class Value>
SeparateChainingHashST<Key, Value>::~SeparateChainingHashST() {}

int main() {
    SeparateChainingHashST<string, int> hashTable = SeparateChainingHashST<string, int>(10);
    return 0;
}