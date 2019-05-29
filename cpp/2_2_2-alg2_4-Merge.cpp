#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

class Merge {
private:
    vector<string> aux;
    void merge(vector<string>& a, int lo, int mid, int hi);
public:
    Merge(int N);
    ~Merge();

    void show(vector<string>& a);
    void sort(vector<string>& a, int lo, int hi);
    bool isSorted(vector<string>& a);
};

Merge::Merge(int N) {
    for (int k = 0; k < N; k++) {
        aux.push_back("-");
    }
}

Merge::~Merge() {}

void Merge::show(vector<string>& a) {
    if (a.size() > 0) {
        cout << a[0];
        for (int i = 1; i < a.size(); i++) {
            cout << " " << a[i];
        }
        cout << endl;
    }
}

void Merge::sort(vector<string>& a, int lo, int hi) {
    if (lo >= hi) {
        return;
    }
    int mid = lo + (hi - lo) / 2;
    sort(a, lo, mid);
    sort(a, mid + 1, hi);
    merge(a, lo, mid, hi);
}

void Merge::merge(vector<string>& a, int lo, int mid, int hi) {
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

bool Merge::isSorted(vector<string>& a) {
    for (int i = 1; i < a.size(); i++) {
        if (a[i - 1] > a[i]) {
            return false;
        }
    }
    return true;
}


int main() {
    string path = "C:\\Users\\60187\\Desktop\\ItA\\algs4\\algs4-data\\";
    string filename = "new_shell.txt";
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
            Merge sort = Merge(vec.size());
            sort.show(vec);
            sort.sort(vec, 0, vec.size() - 1);
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