#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

class Selection {
private:
    void exch(vector<string>& a, int i, int j);
public:
    Selection();
    ~Selection();

    void show(vector<string>& a);
    void sort(vector<string>& a);
    bool isSorted(vector<string>& a);
};

Selection::Selection() {}
Selection::~Selection() {}

void Selection::exch(vector<string>& a, int i, int j) {
    string temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void Selection::show(vector<string>& a) {
    if (a.size() > 0) {
        cout << a[0];
        for (int i = 1; i < a.size(); i++) {
            cout << " " << a[i];
        }
        cout << endl;
    }
}

bool Selection::isSorted(vector<string>& a) {
    for (int i = 1; i < a.size(); i++) {
        if (a[i - 1] > a[i]) {
            return false;
        }
    }
    return true;
}

void Selection::sort(vector<string>& a) {
    int N = a.size();
    for (int i = 0; i < N; i++) {
        int min = i;
        for (int j = i + 1; j < N; j++) {
            if (a[min] > a[j]) {
                min = j;
            }
        }
        exch(a, i, min);
    }
}

int main() {
    string path = "C:\\Users\\60187\\Desktop\\ItA\\algs4\\algs4-data\\";
    string filename = "tiny.txt";
    ifstream in(path + filename);
    string item;
    if (in) {
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
            Selection sort = Selection();
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
