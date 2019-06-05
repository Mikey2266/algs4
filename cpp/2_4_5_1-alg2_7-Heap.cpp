#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;

class Heap {
private:
    void exch(vector<string>& a, int i, int j);
    void sink(vector<string>& a, int k, int N);    
public:
    Heap();
    ~Heap();

    void show(vector<string>& a);
    bool isSorted(vector<string>& a);
    void sort(vector<string>& a);
};

Heap::Heap() {}
Heap::~Heap() {}

void Heap::exch(vector<string>& a, int i, int j) {
    string temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void Heap::show(vector<string>& a) {
    if (a.size() > 0) {
        cout << a[1];
        for (int i = 2; i < a.size(); i++) {
            cout << " " << a[i];
        }
        cout << endl;
    }
}

bool Heap::isSorted(vector<string>& a) {
    for (int i = 2; i < a.size(); i++) {
        if (a[i - 1] > a[i]) {
            return false;
        }
    }
    return true;
}

void Heap::sink(vector<string>& a, int k, int N) {
    while (2 * k <= N) {
        int j = 2 * k;
        if (j < N && a[j] <= a[j + 1]) {
            j++;
        }
        if (!(a[k] < a[j])) {
            break;
        }
        exch(a, k, j);
        k = j;
    }
}

void Heap::sort(vector<string>& a) {
    int N = a.size() - 1;
    for (int k = N / 2; k >= 1; k--) {
        sink(a, k, N);
    }
    while (N > 1) {
        exch (a, 1, N--);
        sink (a, 1, N);
    }
}

int main() {
    string path = "../../../algs4-data/";
    string filename = "newQuickExample.txt";
    ifstream in(path + filename);
    string item;
    if (in.is_open()) {
        while (getline(in, item)) {
            vector<string> vec;
            vec.push_back("-");
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
            Heap sort = Heap();
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