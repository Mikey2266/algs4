#include<iostream>
#include<fstream>
#include<vector>
#include<random>
#include<algorithm>
#include<chrono>

using namespace std;

class Quick3way {
private:
    void exch(vector<string>& a, int i, int j);
public:
    Quick3way(vector<string>& a);
    ~Quick3way();

    void show(vector<string>& a);
    bool isSorted(vector<string>& a);
    void sort(vector<string>& a, int lo, int hi);
};

Quick3way::Quick3way(vector<string>& a) {
    // 乱序
    unsigned seed = chrono::system_clock::now ().time_since_epoch ().count ();
    shuffle(a.begin (), a.end (), default_random_engine (seed));    
}
Quick3way::~Quick3way() {}

void Quick3way::show(vector<string>& a) {
    if (a.size() > 0) {
        cout << a[0];
        for (int i = 1; i < a.size(); i++) {
            cout << " " << a[i];
        }
        cout << endl;
    }
}

bool Quick3way::isSorted(vector<string>& a) {
    for (int i = 1; i < a.size(); i++) {
        if (a[i - 1] > a[i]) {
            return false;
        }
    }
    return true;
}

void Quick3way::exch(vector<string>& a, int i, int j) {
    string temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void Quick3way::sort(vector<string>& a, int lo, int hi) {
    if (hi <= lo) {
        return;
    }
    int lt = lo, i = lo + 1, gt = hi;
    string v = a[lo];
    while (i <= gt) {
        if (a[i] < v) {
            exch(a, lt++, i++);
        }
        else if (a[i] > v) {
            exch(a, gt--, i);
        }
        else i++;
    }
    sort(a, lo, lt - 1);
    sort(a, gt + 1, hi);
}

int main() {
    string path = "../../../algs4-data/";
    string filename = "newQuick3WayExample.txt";
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
            Quick3way sort = Quick3way(vec);
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