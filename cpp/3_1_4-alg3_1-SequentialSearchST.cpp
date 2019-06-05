#include<iostream>
#include<string>
#include<fstream>

using namespace std;

/*节点结构体*/
template<class Key, class Value>
struct Node {
    Key key;
    Value val;
    Node<Key, Value>* next;
    Node(Key x, Value y, Node<Key, Value>* n) : key(x), val(y), next(n) {}
};

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

int main() {
    string path = "../../../algs4-data/";
    string filename = "newSearchExample.txt";
    ifstream in(path + filename);
    string item;
    if (in.is_open()) {
        while (getline(in, item)) {
            int head = 0;
            int order = 0;
            SequentialSearchST<string, int> st = SequentialSearchST<string, int>();
            while (!item.empty()) {
                st.put(item.substr(head, item.find(" ")), order);
                order++;
                if (item.find(" ") < item.length()) {
                    item = item.substr(item.find(" ") + 1, item.length());
                }
                else {
                    item.clear();
                }
            }
            st.show();
            cout << st.size() << endl;
        }
    }
    else {
        cout << "no such file!" << endl;
    }
    return 0;
}
