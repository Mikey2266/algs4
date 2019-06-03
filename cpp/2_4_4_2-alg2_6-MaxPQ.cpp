#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;

template<class T>
class MaxPQ {
private:
    T* pq;
    int N;

    bool less(int i, int j);
    void exch(int i, int j);
    void swim(int k);
    void sink(int k);    
public:
    MaxPQ(int maxN);
    ~MaxPQ();

    void show();
    bool isEmpty();
    int size();
    void insert(T v);
    T delMax();
};

template<class T>
MaxPQ<T>::MaxPQ(int maxN) {
    N = 0;
    pq = new T[maxN + 1];
}

template<class T>
MaxPQ<T>::~MaxPQ() {
    if (pq) {
        delete[] pq;
    }
}

template<class T>
bool MaxPQ<T>::isEmpty() {
    return N == 0;
}

template<class T>
int MaxPQ<T>::size() {
    return N;
}

template<class T>
bool MaxPQ<T>::less(int i, int j) {
    if (pq[i] < pq[j]) {
        return true;
    }
    return false;
}

template<class T>
void MaxPQ<T>::exch(int i, int j) {
    T t = pq[i];
    pq[i] = pq[j];
    pq[j] = t;
}

template<class T>
void MaxPQ<T>::show() {
    for (int i = 1; i < N + 1; i++) {
        cout << pq[i] << " ";
    }
    cout << endl;
}

template<class T>
void MaxPQ<T>::swim(int k) {
    while (k > 1 && less(k / 2, k)) {
        exch(k / 2, k);
        k = k / 2;
    }
}

template<class T>
void MaxPQ<T>::sink(int k) {
    while (2 * k <= N) {
        int j = 2 * k;
        if (j < N && less(j, j + 1)) {
            j++;
        }
        if (!less(k, j)) {
            break;
        }
        exch(k, j);
        k = j;
    }
}

template<class T>
void MaxPQ<T>::insert(T v) {
    pq[++N] = v;
    swim(N);
}

template<class T>
T MaxPQ<T>::delMax() {
    T max = pq[1];
    exch(1, N--);
    sink(1);
    return max;
}

int main() {
    string path = "../../../algs4-data/";
    string filename = "newQuickExample.txt";
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
            MaxPQ<string> pq = MaxPQ<string>(vec.size());
            for (int i = 0; i < vec.size(); i++) {
                pq.insert(vec[i]);
                pq.show();
            }
            cout << pq.delMax() << endl;
        }
    }
    else {
        cout << "no such file!" << endl;
    }
    return 0;
}