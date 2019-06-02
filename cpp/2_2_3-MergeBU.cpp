#include<iostream>
#include<fstream>
#include<vector>
#include <algorithm>

using namespace std;

class MergeBU {
private:
    vector<string> aux;
    void merge(vector<string>& a, int lo, int mid, int hi);
public:
    MergeBU(int N);
    ~MergeBU();

    void show(vector<string>& a);
    void sort(vector<string>& a);
    bool isSorted(vector<string>& a);
};

MergeBU::MergeBU(int N) {
    for (int k = 0; k < N; k++) {
        aux.push_back("-");
    }
}

MergeBU::~MergeBU() {}

void MergeBU::show(vector<string>& a) {
    if (a.size() > 0) {
        cout << a[0];
        for (int i = 1; i < a.size(); i++) {
            cout << " " << a[i];
        }
        cout << endl;
    }
}

void MergeBU::sort(vector<string>& a) {
    int N = a.size();
    for (int sz = 1; sz < N; sz = sz + sz) {
        for (int lo = 0; lo < N - sz; lo += sz + sz) {
            merge(a, lo, lo + sz - 1, min(lo + sz + sz - 1, N-1));
        }
    }
}

void MergeBU::merge(vector<string>& a, int lo, int mid, int hi) {
    int i = lo;
    int j = mid + 1;
    for (int k = 0; k < a.size(); k++) {
        aux[k] = a[k];
    }
    for (int k = lo; k <= hi; k++) {
        if (i > mid) {
            a[k] = aux[j++];
        }
        else if (j > hi) {
            a[k] = aux[i++];
        }
        else if (aux[i] < aux[j]) {
            a[k] = aux[i++];
        }
        else {
            a[k] = aux[j++];
        }
    }
}

bool MergeBU::isSorted(vector<string>& a) {
    for (int i = 1; i < a.size(); i++) {
        if (a[i - 1] > a[i]) {
            return false;
        }
    }
    return true;
}


int main() {
    string path = "../../../algs4-data/";
    string filename = "newMergeExample.txt";
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
            MergeBU sort = MergeBU(vec.size());
            sort.show(vec);
            sort.sort(vec);
            if (!sort.isSorted(vec)) {
                cout << "sort error" << endl;
            }
            sort.show(vec);
        }
    }
    else {
        cout << "no such file!" << endl;
    }
    return 0;
}