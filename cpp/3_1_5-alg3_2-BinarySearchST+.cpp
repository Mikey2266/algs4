/*未实现用foreach顺序迭代访问功能*/
#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;

template<class Key, class Value>
class BinarySearchST {
private:
    Key* keys;
    Value* vals;
    int N;
public:
    BinarySearchST(int capacity);
    ~BinarySearchST();

    bool isEmpty();
    int size();
    void show();
    Key keyMin();
    Key keyMax();
    Key select(int k);
    Key ceiling(Key key);
    Value get(Key key);
    int rank(Key key);
    void put(Key key, Value val);
    void deleteKey(Key key);
};

template<class Key, class Value>
BinarySearchST<Key, Value>::BinarySearchST(int capacity) {
    N = 0;
    keys = new Key[capacity];
    vals = new Value[capacity];
}

template<class Key, class Value>
BinarySearchST<Key, Value>::~BinarySearchST() {
    if (keys) {
        delete[] keys;
    }
    if (vals) {
        delete[] vals;
    }
}

template<class Key, class Value>
bool BinarySearchST<Key, Value>::isEmpty() {
    return N == 0;
}

template<class Key, class Value>
int BinarySearchST<Key, Value>::size() {
    return N;
}

template<class Key, class Value>
void BinarySearchST<Key, Value>::show() {
    for (int i = 0; i < N; i++) {
        cout << keys[i] << " " << vals[i] << endl;
    }
}

template<class Key, class Value>
Key BinarySearchST<Key, Value>::keyMin() {
    return keys[0];
}

template<class Key, class Value>
Key BinarySearchST<Key, Value>::keyMax() {
    return keys[N - 1];
}

template<class Key, class Value>
Key BinarySearchST<Key, Value>::select(int k) {
    return keys[k];
}

template<class Key, class Value>
Key BinarySearchST<Key, Value>::ceiling(Key key) {
    int i = rank(key);
    return keys[i];
}

template<class Key, class Value>
Value BinarySearchST<Key, Value>::get(Key key) {
    Value val;
    if (isEmpty()) {
        return val;
    }
    int i = rank(key);
    if (i < N && keys[i] == key) {
        return vals[i];
    }
    else {
        cout << "not contain this key" << endl;
        return val;
    }
}

template<class Key, class Value>
int BinarySearchST<Key, Value>::rank(Key key) {
    int lo = 0, hi = N - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (key < keys[mid]) {
            hi = mid - 1;
        }
        else if (key > keys[mid]) {
            lo = mid + 1;
        }
        else {
            return mid;
        }
    }
    return lo;
}

template<class Key, class Value>
void BinarySearchST<Key, Value>::put(Key key, Value val) {
    int i = rank(key);
    if (i < N && keys[i] == key) {
        vals[i] = val;
        return;
    }
    for (int j = N; j > i; j--) {
        keys[j] = keys[j - 1];
        vals[j] = vals[j - 1];
    }
    keys[i] = key;
    vals[i] = val;
    N++;
}

template<class Key, class Value>
void BinarySearchST<Key, Value>::deleteKey(Key key) {
    int i = rank(key);
    if (i < N && keys[i] != key) {
        cout << "not contain this key." << endl;
        return;
    }
    for (int j = i; j < N - 1; j++) {
        keys[j] = keys[j + 1];
        vals[j] = vals[j + 1];
    }
    N--;
}

int main() {
    string path = "../../../algs4-data/";
    string filename = "newSearchExample.txt";
    ifstream in(path + filename);
    string item;
    if (in.is_open()) {
        while (getline(in, item)) {
            vector<string> vec;
            int head = 0;
            while (!item.empty()) {
                vec.push_back(item.substr(head, item.find(" ")));
                if (item.find(" ") < item.length()) {
                    item = item.substr(item.find(" ") + 1, item.length());
                }
                else {
                    item.clear();
                }
            }
            BinarySearchST<string, int> st = BinarySearchST<string, int>(vec.size());
            for (int i = 0; i < vec.size(); i++) {
                st.put(vec[i], i);
            }
            st.show();
            cout << st.size() << endl;
            cout << st.keyMax() << endl;
            cout << st.keyMin() << endl;
            st.deleteKey("A");
            st.deleteKey("X");
            cout << st.size() << endl;
            cout << st.keyMax() << endl;
            cout << st.keyMin() << endl;
            st.deleteKey("B");
            cout << st.get("R") << endl;
            cout << st.get("Q") << endl;
        }
    }
    else {
        cout << "no such file!" << endl;
    }
    return 0;
}