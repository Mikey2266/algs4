#include<iostream>
#include<fstream>
#include<vector>
#include<random>
#include<algorithm>
#include<chrono>

using namespace std;

class Quick {
private:
    void exch(vector<string>& a, int i, int j);
    int partition(vector<string>& a, int lo, int hi);
public:
    Quick(vector<string>& a);
    ~Quick();

    void show(vector<string>& a);
    bool isSorted(vector<string>& a);
    void sort(vector<string>& a, int lo, int hi);
};

Quick::Quick(vector<string>& a) {
    // 乱序
    unsigned seed = chrono::system_clock::now ().time_since_epoch ().count ();
    shuffle(a.begin (), a.end (), default_random_engine (seed));    
}
Quick::~Quick() {}

void Quick::show(vector<string>& a) {
    if (a.size() > 0) {
        cout << a[0];
        for (int i = 1; i < a.size(); i++) {
            cout << " " << a[i];
        }
        cout << endl;
    }
}

bool Quick::isSorted(vector<string>& a) {
    for (int i = 1; i < a.size(); i++) {
        if (a[i - 1] > a[i]) {
            return false;
        }
    }
    return true;
}

void Quick::exch(vector<string>& a, int i, int j) {
    string temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void Quick::sort(vector<string>& a, int lo, int hi) {
    if (hi <= lo) {
        return;
    }
    int j = partition(a, lo, hi);
    sort(a, lo, j - 1);
    sort(a, j + 1, hi);
}

int Quick::partition(vector<string>& a, int lo, int hi) {
    int i = lo, j = hi + 1;
    string v = a[lo];
    while (true) {
        while (a[++i] <= v) {
            if (i == hi) {
                break;
            }
        }
        while (a[--j] >= v) {
            if (j == lo) {
                break;
            }
        }
        if (i >= j) {
            break;
        }
        exch(a, i, j);
    }
    exch(a, lo, j);
    return j;
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
            Quick sort = Quick(vec);
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